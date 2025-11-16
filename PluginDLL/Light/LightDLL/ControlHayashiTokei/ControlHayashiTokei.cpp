#include "ControlHayashiTokei.h"
#include "XTypeDef.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XLightDLL.h"
#include <QDir.h>
#include <QFile.h>
#include "SettingDialog.h"
#include "XPIOButton.h"
#include "ThreadSequence.h"
#include "XGUIFormBase.h"

//=================================================================================================

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLLightMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="HayashiTokei";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Light DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2007.9";
	return true;
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Control Hayashi Tokei light";
}

LightDLLBaseClass		*_cdecl	DLL_Initial(LayersBase *base,const QString &LightParamStr,bool OutputMode)
//	Initialize Light DLL. 
//		This function must create and open handle. 
//	return:		Light handle(memory block)
//				if proocess fails, return 0
{
	LightControlHayashiTokei	*H=new LightControlHayashiTokei(base,LightParamStr);
	H->Initial(OutputMode);
	return H;
}

bool		_cdecl	DLL_Close(LightDLLBaseClass *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	LightControlHayashiTokei	*H=(LightControlHayashiTokei *)handle;
	if(H!=NULL){
		H->Close();
		delete	H;
	}

	return true;
}

bool		_cdecl	DLL_Load(LightDLLBaseClass *handle ,QIODevice &str)
//	Load light attribution(setting) information of handle
//	This function must load information from stream
//	In this function, light attribution information must be set to a handle
//	if process fails, it returns false
{
	LightControlHayashiTokei	*p=static_cast<LightControlHayashiTokei *>(handle);
	bool	Ret=p->Load(&str);
	if(Ret==true){
		p->Transfer(NULL);
	}
	return Ret;
}

bool		_cdecl	DLL_Save(LightDLLBaseClass *handle ,QIODevice &str)
//	Save light attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	LightControlHayashiTokei	*p=static_cast<LightControlHayashiTokei *>(handle);
	return p->Save(&str);
}

bool		_cdecl	DLL_ShowSetting(LightDLLBaseClass *handle, QWidget *parent)
//	This function shows dialog to set light(handle) information
//	In this dialog in function, it must set followings
//		1: Pattern Count
//		2:Lighting pattern(Which light is on, or level)
//		3:Set these data to a handle
//	if dialog can't be shown, it returns false
{
	LightControlHayashiTokei	*p=static_cast<LightControlHayashiTokei *>(handle);
	SettingDialog	*LightForm=new SettingDialog(p);
	bool	Ret=LightForm->exec();
	delete LightForm;

	return Ret;
}

int		_cdecl	DLL_GetLightPatternCount(LightDLLBaseClass *handle)
//	This function must return Pattern-Count on handle
{
	return 1;
}

bool		_cdecl	DLL_LightOn(LightDLLBaseClass *handle)
//	Turn on handle-light
//	This function must return soon
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	LightControlHayashiTokei	*p=static_cast<LightControlHayashiTokei *>(handle);
	p->SetOnOff(true);
	return true;
}

bool		_cdecl	DLL_LightOff(LightDLLBaseClass *handle)
//	Turn off handle-light
//	This function must return soon
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	LightControlHayashiTokei	*p=static_cast<LightControlHayashiTokei *>(handle);
	p->SetOnOff(false);
	return true;
}

bool		_cdecl	DLL_SetPattern(LightDLLBaseClass *handle ,int PatternNo)
//	This function set Light-pattern
//	This function must return as soon as possible
//	If LightOff was set before this function, Light must be enlightened with this pattern when LightOn function is called
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	return true;
}

bool		_cdecl	DLL_ReqLightError(LightDLLBaseClass *handle ,QStringList &Msg)
//	Request light error from system
//	This function must set error message into Msg when any errors occur
//	this function is called after any functions return false
{
	return true;
}


//=======================================================================================

/*	
	I/O Keyword

	PBit0
	PBit1
	PBit2
	PBit3
	PBit4
	PBit5
	PBit6
	PBit7
	PON

*/

BitPort::BitPort(void)
{
	PIO		=NULL;
	BoardNo	=0;
	Port	=0;
	BitNo	=0;
}
void	BitPort::SetInfo(PIOClass *Pio,int _BoardNo,int _PortNo,int _BitNo)
{
	PIO		=Pio;
	BoardNo	=_BoardNo;
	Port	=_PortNo;
	BitNo	=_BitNo;
}
void	BitPort::Set(bool b)
{
	if(PIO!=NULL){
		PIO->SetBit(BoardNo,Port,BitNo,(b==true)?1:0);
	}
}

bool	BitPort::Get(void)
{
	if(PIO!=NULL){
		int	d=PIO->GetBit(BoardNo,Port,BitNo);
		if(d==0)
			return false;
		else
			return true;
	}
	return false;
}

LightControlHayashiTokei::LightControlHayashiTokei(LayersBase *base,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	Opened=false;
	Param=LightParamStr;
	if(Param.isEmpty()==true)
		CountOfLED=1;
	else{
		CountOfLED=0;
	}

	for(int i=0;i<CountOfLED;i++){
		Brightness[i]	=0;
		OnMode[i]		=true;
	}
	if(LightParamStr.isNull()==false){
		QFile	File(LightParamStr);
		if(File.open(QIODevice::ReadOnly)==true){
			LoadIODefine(&File);
		}
	}
}	

bool	LightControlHayashiTokei::Initial(bool OutputMode)
{
	return true;
}

bool	LightControlHayashiTokei::Close(void)
{
	return true;
}


LightControlHayashiTokei::~LightControlHayashiTokei(void)
{
}

bool	LightControlHayashiTokei::Save(QIODevice *f)
{
	for(int i=0;i<MaxCountOfLED;i++){
		if(::Save(f,Brightness[i])==false){
			return false;
		}
		if(::Save(f,OnMode[i])==false){
			return false;
		}
	}
	return true;
}
bool	LightControlHayashiTokei::Load(QIODevice *f)
{
	for(int i=0;i<MaxCountOfLED;i++){
		if(::Load(f,Brightness[i])==false){
			return false;
		}
		if(::Load(f,OnMode[i])==false){
			return false;
		}
	}

	Transfer(NULL);
	for(int i=0;i<CountOfLED;i++){
		SetOnOff(i,OnMode[i]);
	}

	return true;
}


bool	LightControlHayashiTokei::SetOnOff(int number ,bool d)
{
	if(0<=number && number<CountOfLED){
		OnMode[number]=d;
	}
	BitDim[number].PON.Set(!d);
	return true;
}
bool	LightControlHayashiTokei::SetOnOff(bool __OnMode)
{
	for(int i=0;i<CountOfLED;i++){
		SetOnOff(i,__OnMode);
	}
	return true;
}

void	LightControlHayashiTokei::Transfer(QProgressBar *Bar)
{
	for(int i=0;i<CountOfLED;i++){
		BitDim[i].PBit0.Set(((Brightness[i]&0x01)!=0)?true:false);
		BitDim[i].PBit1.Set(((Brightness[i]&0x02)!=0)?true:false);
		BitDim[i].PBit2.Set(((Brightness[i]&0x04)!=0)?true:false);
		BitDim[i].PBit3.Set(((Brightness[i]&0x08)!=0)?true:false);
		BitDim[i].PBit4.Set(((Brightness[i]&0x10)!=0)?true:false);
		BitDim[i].PBit5.Set(((Brightness[i]&0x20)!=0)?true:false);
		BitDim[i].PBit6.Set(((Brightness[i]&0x40)!=0)?true:false);
		BitDim[i].PBit7.Set(((Brightness[i]&0x80)!=0)?true:false);
	}
}


void	LightControlHayashiTokei::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLightSetValue	*CmdLightSetValueVar=dynamic_cast<CmdLightSetValue *>(packet);
	if(CmdLightSetValueVar!=NULL){
		Brightness[CmdLightSetValueVar->Number]=CmdLightSetValueVar->Value;
		Transfer(NULL);
		return;
	}
	CmdLightSetOnOff	*CmdLightSetOnOffVar=dynamic_cast<CmdLightSetOnOff *>(packet);
	if(CmdLightSetOnOffVar!=NULL){
		SetOnOff(CmdLightSetOnOffVar->Number,CmdLightSetOnOffVar->OnMode);
		return;
	}
	CmdLightReqData		*CmdLightReqDataVar=dynamic_cast<CmdLightReqData *>(packet);
	if(CmdLightReqDataVar!=NULL){
		CmdLightReqDataVar->OnMode=OnMode[CmdLightReqDataVar->Number];
		CmdLightReqDataVar->Value=Brightness[CmdLightReqDataVar->Number];
		return;
	}
}


bool	LightControlHayashiTokei::LoadIODefine(QIODevice *f)
{
	QTextStream	Txt(f);
	CountOfLED=0;
	while(Txt.atEnd()==false){
		QString	TextLine=Txt.readLine(1000).trimmed();
		if(TextLine.startsWith("#iodefine")==true){
			QString	L1=TextLine.mid(9).trimmed();
			QStringList	LL=L1.split(':');
			BitPort	*BPort=NULL;
			QString	KeywordStr=LL[0].trimmed();
			if(KeywordStr=="PBit0")
				BPort=&BitDim[CountOfLED].PBit0;
			else if(KeywordStr=="PBit1")
				BPort=&BitDim[CountOfLED].PBit1;
			else if(KeywordStr=="PBit2")
				BPort=&BitDim[CountOfLED].PBit2;
			else if(KeywordStr=="PBit3")
				BPort=&BitDim[CountOfLED].PBit3;
			else if(KeywordStr=="PBit4")
				BPort=&BitDim[CountOfLED].PBit4;
			else if(KeywordStr=="PBit5")
				BPort=&BitDim[CountOfLED].PBit5;
			else if(KeywordStr=="PBit6")
				BPort=&BitDim[CountOfLED].PBit6;
			else if(KeywordStr=="PBit7")
				BPort=&BitDim[CountOfLED].PBit7;
			else if(KeywordStr=="PON")
				BPort=&BitDim[CountOfLED].PON;
			if(BPort!=NULL){
				QStringList	LNum=LL[1].split(',');
				bool	ok1,ok2,ok3;
				int	BoardNo	=LNum[0].toInt(&ok1);
				int	PortNo	=LNum[1].toInt(&ok2);
				int	BitNo	=LNum[2].toInt(&ok3);
				if(ok1==true && ok2==true && ok3==true){
					ThreadSequence	*S=GetLayersBase()->GetSequenceInstance();
					PIOClass	*Pio=S->FindPIO(/**/"");
					BPort->SetInfo(Pio,BoardNo,PortNo,BitNo);
				}
			}
		}
		else if(TextLine.startsWith("#Board")==true){
			QString	L1=TextLine.mid(6).trimmed();
			CountOfLED=L1.toInt();
		}
	}
	CountOfLED++;
	return true;
}

bool	LightControlHayashiTokei::ShowSettingDialog(void)	
{
	return true;
}
	//Don't call directly
bool	LightControlHayashiTokei::InitialPhysical(const QString &Param)
{
	Initial(true);
	return true;
}
bool	LightControlHayashiTokei::ReflectPhysical(void)		
{
	Transfer(NULL);
	return true;
}
bool	LightControlHayashiTokei::ReflectPhysicalTurnOn(bool LightOn)
{
	SetOnOff(LightOn);
	return true;
}

