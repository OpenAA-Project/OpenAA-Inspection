#include "XCCSControlByPIO2Ch.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XPIOButton.h"
#include "XDataInLayer.h"
#include "ThreadSequence.h"
#include "XGUIFormBase.h"
#include "SettingDialog.h"
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
	PExt
	PWR
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


LightCCSControlByPIO2Ch::LightCCSControlByPIO2Ch(LayersBase *base,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	Opened=false;
	Param=LightParamStr;
	CurrentPattern	=0;
	InData	=0;

	for(int t=0;t<sizeof(Brightness)/sizeof(Brightness[0]);t++){
		Brightness[t]	=0;
		OnMode[t]		=true;
	}
	int	Number=0;
	if(LightParamStr.isNull()==false){
		QFile	File(LightParamStr);
		if(File.open(QIODevice::ReadOnly)==true){
			LoadIODefine(&File);
		}
	}
}

LightCCSControlByPIO2Ch::~LightCCSControlByPIO2Ch(void)
{
}

bool	LightCCSControlByPIO2Ch::Save(QIODevice *f)
{
	int32	N=sizeof(Brightness)/sizeof(Brightness[0]);
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(::Save(f,Brightness[i])==false){
			return false;
		}
		if(::Save(f,OnMode[i])==false){
			return false;
		}
	}
	return true;
}
bool	LightCCSControlByPIO2Ch::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N && i<sizeof(Brightness)/sizeof(Brightness[0]);i++){
		if(::Load(f,Brightness[i])==false){
			return false;
		}
		if(::Load(f,OnMode[i])==false){
			return false;
		}
	}
	Transfer(0,NULL);
	SendOnOff(0,OnMode[0]);
	SendOnOff(1,OnMode[1]);

	return true;
}


bool	LightCCSControlByPIO2Ch::ShowSettingDialog(void)	
	//Don't call directly
{
	SettingDialog	*LightForm=new SettingDialog(this);
	bool	Ret=LightForm->exec();
	delete LightForm;
	return Ret;
}

bool	LightCCSControlByPIO2Ch::InitialPhysical(const QString &Param)
{
	return true;
}

bool	LightCCSControlByPIO2Ch::ReflectPhysical(void)
{
	PON1.Set(OnMode[0]);
	PON2.Set(OnMode[1]);

	SelectCh(0);
	SendWR(1);
	SendOutData(Brightness[0]);
	SendWR(0);
	GSleep(10);
	SendWR(1);

	SelectCh(1);
	SendWR(1);
	SendOutData(Brightness[1]);
	SendWR(0);
	GSleep(10);
	SendWR(1);


	return true;
}

bool	LightCCSControlByPIO2Ch::ReflectPhysicalTurnOn(bool LightOn)
{
	OnMode[0]=LightOn;
	OnMode[1]=LightOn;
	PON1.Set(LightOn);
	PON2.Set(LightOn);

	return true;
}

void	LightCCSControlByPIO2Ch::Transfer(int PatternNumber ,QProgressBar *Bar)
{
	ReflectPhysical();
}

bool	LightCCSControlByPIO2Ch::SendOutData(int n)
{
	PBit0.Set(((n&0x01)!=0)?true:false);
	PBit1.Set(((n&0x02)!=0)?true:false);
	PBit2.Set(((n&0x04)!=0)?true:false);
	PBit3.Set(((n&0x08)!=0)?true:false);
	PBit4.Set(((n&0x10)!=0)?true:false);
	PBit5.Set(((n&0x20)!=0)?true:false);
	PBit6.Set(((n&0x40)!=0)?true:false);
	PBit7.Set(((n&0x80)!=0)?true:false);

	return true;
}

bool	LightCCSControlByPIO2Ch::SendWR(bool n)
{
	PWR.Set(n);
	return true;
}
bool	LightCCSControlByPIO2Ch::SelectCh(int Ch)
{
	if(Ch==0)
		PCH.Set(0);
	else
		PCH.Set(1);
	return true;
}

bool	LightCCSControlByPIO2Ch::SendOnOff(int Ch ,bool onMode)
{
	if(Ch==0)
		PON1.Set(onMode);
	else
		PON2.Set(onMode);

	return true;
}

bool	LightCCSControlByPIO2Ch::SendExt(bool n)
{
	PExt.Set(n);
	return true;
}

void	LightCCSControlByPIO2Ch::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLightSetValue1	*CmdLightSetValue1Var=dynamic_cast<CmdLightSetValue1 *>(packet);
	if(CmdLightSetValue1Var!=NULL){
		SendExt(true);
		Brightness[0]=CmdLightSetValue1Var->Value1;
		Transfer(0,NULL);
		return;
	}
	CmdLightSetValue2	*CmdLightSetValue2Var=dynamic_cast<CmdLightSetValue2 *>(packet);
	if(CmdLightSetValue2Var!=NULL){
		SendExt(true);
		Brightness[1]=CmdLightSetValue2Var->Value2;
		Transfer(0,NULL);
		return;
	}
	CmdLightSetOnOff	*CmdLightSetOnOffVar=dynamic_cast<CmdLightSetOnOff *>(packet);
	if(CmdLightSetOnOffVar!=NULL){
		SendExt(true);
		SendOnOff(0,CmdLightSetOnOffVar->OnMode1);
		SendOnOff(1,CmdLightSetOnOffVar->OnMode2);
		return;
	}
	CmdLightReqData		*CmdLightReqDataVar=dynamic_cast<CmdLightReqData *>(packet);
	if(CmdLightReqDataVar!=NULL){
		SendExt(true);
		CmdLightReqDataVar->OnMode1=OnMode[0];
		CmdLightReqDataVar->Value1=Brightness[0];
		CmdLightReqDataVar->OnMode2=OnMode[1];
		CmdLightReqDataVar->Value2=Brightness[1];
		return;
	}
}

bool	LightCCSControlByPIO2Ch::LoadIODefine(QIODevice *f)
{
	QTextStream	Txt(f);
	while(Txt.atEnd()==false){
		QString	TextLine=Txt.readLine(1000).trimmed();
		if(TextLine.startsWith("#iodefine")==true){
			QString	L1=TextLine.mid(9).trimmed();
			QStringList	LL=L1.split(':');
			QString	KeywordStr=LL[0].trimmed();
			BitPort	*BPort=NULL;
			if(KeywordStr=="PBit0")
				BPort=&PBit0;
			else if(KeywordStr=="PBit1")
				BPort=&PBit1;
			else if(KeywordStr=="PBit2")
				BPort=&PBit2;
			else if(KeywordStr=="PBit3")
				BPort=&PBit3;
			else if(KeywordStr=="PBit4")
				BPort=&PBit4;
			else if(KeywordStr=="PBit5")
				BPort=&PBit5;
			else if(KeywordStr=="PBit6")
				BPort=&PBit6;
			else if(KeywordStr=="PBit7")
				BPort=&PBit7;
			else if(KeywordStr=="PExt")
				BPort=&PExt;
			else if(KeywordStr=="PWR")
				BPort=&PWR;
			else if(KeywordStr=="PON1")
				BPort=&PON1;
			else if(KeywordStr=="PCh")
				BPort=&PCH;
			else if(KeywordStr=="PON2")
				BPort=&PON2;
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
	}
	return true;
}
