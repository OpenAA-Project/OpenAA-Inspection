#include "LEDControl32.h"
#include "XTypeDef.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XLightDLL.h"
#include <QDir.h>
#include <QFile.h>
#include "SettingDialog.h"
#include "XCriticalFunc.h"
#include "XGUIFormBase.h"
#include "XHidCommand.h"

LEDControl32::LEDPattern::LEDPattern(void)
{
	for(int i=0;i<LEDCountInSheet;i++){
		Brightness[i]	=0;
	}
}
LEDControl32::LEDPattern	&LEDControl32::LEDPattern::operator=(LEDControl32::LEDPattern &src)
{
	for(int i=0;i<LEDCountInSheet;i++){
		Brightness[i]	=src.Brightness[i];
	}
	return *this;
}
bool	LEDControl32::LEDPattern::Save(QIODevice *f)
{
	int32	N=LEDCountInSheet;
	if(::Save(f,N)==false)
		return false;
	if(f->write((const char *)Brightness,sizeof(Brightness))!=sizeof(Brightness))
		return false;
	return true;
}
bool	LEDControl32::LEDPattern::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	if(N==LEDCountInSheet){
		if(f->read((char *)Brightness,sizeof(Brightness))!=sizeof(Brightness))
			return false;
	}
	else if(N<LEDCountInSheet){
		int	Len=N*sizeof(Brightness[0]);
		if(f->read((char *)Brightness,Len)!=Len){
			return false;
		}
	}
	else{
		short	*Tmp=new short[N];
		int	Len=N*sizeof(Brightness[0]);
		if(f->read((char *)Tmp,Len)!=Len){
			delete	[]Tmp;
			return false;
		}
		for(int i=0;i<N && i<LEDCountInSheet;i++){
			Brightness[i]=Tmp[i];
		}
		delete	[]Tmp;
	}
	return true;
}

LEDControl32::LEDBoard	&LEDControl32::LEDBoard::operator=(LEDControl32::LEDBoard &src)
{
	BoardName	=src.BoardName;
	for(int i=0;i<LEDCountInSheet;i++){
		Text[i]=src.Text[i];
	}
	for(int j=0;j<LEDPatternCount;j++){
		Pattern[j]	=src.Pattern[j];
	}
	return *this;
}

bool	LEDControl32::LEDBoard::Save(QIODevice *f)
{
	if(::Save(f,BoardName)==false)
		return false;
	int32	N=LEDCountInSheet;
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<LEDCountInSheet;i++){
		if(::Save(f,Text[i])==false)
			return false;
	}
	int32	L=LEDPatternCount;
	if(::Save(f,L)==false)
		return false;
	for(int j=0;j<LEDPatternCount;j++){
		if(Pattern[j].Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	LEDControl32::LEDBoard::Load(QIODevice *f)
{
	if(::Load(f,BoardName)==false)
		return false;
	int32	N;
	if(::Load(f,N)==false)
		return false;
	int	i;
	for(i=0;i<LEDCountInSheet && i<N;i++){
		if(::Load(f,Text[i])==false)
			return false;
	}
	QString	Temp;
	for(;i<N;i++){
		if(::Load(f,Temp)==false)
			return false;
	}

	int32	L;
	if(::Load(f,L)==false)
		return false;
	int	j;
	for(j=0;j<LEDPatternCount && j<L;j++){
		if(Pattern[j].Load(f)==false){
			return false;
		}
	}
	LEDPattern	TmpPatern;
	for(;j<L;j++){
		if(TmpPatern.Load(f)==false){
			return false;
		}
	}

	return true;
}

LEDControl32::LEDDataStruct	&LEDControl32::LEDDataStruct::operator=(LEDControl32::LEDDataStruct &src)
{
	for(int i=0;i<LEDBoardCount;i++){
		Board[i]=src.Board[i];
	}
	return *this;
}

bool	LEDControl32::LEDDataStruct::Save(QIODevice *f)
{
	int32	N=LEDBoardCount;
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<LEDBoardCount;i++){
		if(Board[i].Save(f)==false);
	}
	return true;
}

bool	LEDControl32::LEDDataStruct::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	int	i;
	for(i=0;i<LEDBoardCount && i<N;i++){
		if(Board[i].Load(f)==false);
	}
	LEDBoard	TmpBoard;
	for(;i<N;i++){
		if(TmpBoard.Load(f)==false);
	}
	return true;
}


//===================================================================
LEDControl32::LEDControl32(LayersBase *base ,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	BaseCounter	=1023;
	IDNumber	=0;
	BoardCount	=1;
	MaxValue	=1023;
	IndexBuffer1	=0;
	IndexBuffer2	=1;
	OutputNumber	=0;	//0 or 1

	QStringList	ParamList=LightParamStr.split(QChar(' '));
	for(int i=0;i<ParamList.count();i++){
		QString	c=ParamList[i].left(1);
		if(c==QString("N") || c==QString("n")){
			QString	Str=ParamList[i].mid(1);
			IDNumber	=Str.toInt();
		}
		if(c==QString("B") || c==QString("b")){
			QString	Str=ParamList[i].mid(1);
			BoardCount	=Str.toInt();
		}
		if(c==QString("M") || c==QString("m")){
			QString	Str=ParamList[i].mid(1);
			MaxValue	=Str.toInt();
		}
	}
	Commander=HidCommand::Create((QWidget *)this);

	Opened=false;
	StopInput	=false;

	Param=LightParamStr;

	if(Open()==true){
		CommGetVersion();
		for(int b=0;b<BoardCount;b++){
			CommSendBaseCounter(b,BaseCounter);
		}
	}
	/*
	TM.setInterval(10);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
	*/
}

LEDControl32::~LEDControl32(void)
{
	delete	Commander;
	Commander=NULL;
}

bool	LEDControl32::Initial(bool OutputMode)
{	
	return true;
}

bool	LEDControl32::Open(void)
{
	if(Commander->OpenHid(0x1255, 0x0006,IDNumber)==false){
		return false;
	}
	return true;
}

bool	LEDControl32::Close(void)
{	
	return true;
}


bool	LEDControl32::Save(QIODevice *f)
{
	QString	s=GetClassName();
	int32	Ver=1;

	if(::Save(f,s)==false)
		return false;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,BaseCounter)==false)
		return false;
	if(LEDData.Save(f)==false)
		return false;

	if(::Save(f,IndexBuffer1)==false)
		return false;
	if(::Save(f,IndexBuffer2)==false)
		return false;
	if(::Save(f,OutputNumber)==false)
		return false;

	return true;
}
bool	LEDControl32::Load(QIODevice *f)
{
	QString	s;
	int32	Ver;

	if(::Load(f,s)==false)
		return false;
	if(s!=GetClassName())
		return false;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,BaseCounter)==false)
		return false;
	if(LEDData.Load(f)==false)
		return false;

	if(::Load(f,IndexBuffer1)==false)
		return false;
	if(::Load(f,IndexBuffer2)==false)
		return false;
	if(::Load(f,OutputNumber)==false)
		return false;
	return true;
}


void	LEDControl32::Transfer(int PatternNumber ,QProgressBar *Bar)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	if(Bar!=NULL){
		Bar->setMaximum(BoardCount*LEDPatternCount);
	}

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	if(Bar!=NULL){
		Bar->setValue(0);
	}

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		for(int b=0;b<BoardCount;b++){
			if(CommSendData(b,Bar)==false){
				break;
			}
		}
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;

	for(int b=0;b<BoardCount;b++){
		CommTransferAll(b,IndexBuffer1,0);
		CommTransferAll(b,IndexBuffer2,1);
	}
}


bool	LEDControl32::ShowSettingDialog(void)
{
	SettingDialog	*LightForm=new SettingDialog(this);
	bool	Ret=LightForm->exec();
	delete LightForm;
	return Ret;
}

	//Don't call directly
bool	LEDControl32::InitialPhysical(const QString &Param)
{
	Initial(true);
	return true;
}
bool	LEDControl32::ReflectPhysical(void)
{
	Transfer(0,NULL);
	return true;
}
bool	LEDControl32::ReflectPhysicalTurnOn(bool LightOn)
{
	if(CommOutEnableAll(LightOn)==false)
		return false;
	return true;
}


void	LEDControl32::TransmitDirectly(GUIDirectMessage *packet)
{
}
//==================================================================


bool	LEDControl32::CommGetVersion(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return false;
	bool	Ret=false;
	ReEntrant=true;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		Commander->SendStr((BYTE *)"V",1);
		BYTE	RecData[256];
		int		ReceivedLen;
		GSleep(20);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			VersionStr=((char *)RecData);
			Ret=true;
		}
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}

bool	LEDControl32::CommSetBoardCount(int n)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return false;
	ReEntrant=true;
	bool	Ret=false;
	BYTE	TxBuff[64];

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='A';
		TxBuff[1]=n;

		Commander->SendStr(TxBuff,64);

		BYTE	RecData[256];
		int		ReceivedLen;
		for(int i=0;i<10;i++){
			GSleep(20);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				Ret=true;
				break;
			}
		}
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}

bool	LEDControl32::CommOutEnable(int BoardNo ,bool OnMode)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return false;
	ReEntrant=true;
	bool	Ret=false;
	BYTE	TxBuff[64];

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='B';
		TxBuff[1]=BoardNo;
		TxBuff[2]=(OnMode==true)?1:0;

		Commander->SendStr(TxBuff,64);

		BYTE	RecData[256];
		int		ReceivedLen;
		for(int i=0;i<10;i++){
			GSleep(20);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				Ret=true;
				break;
			}
		}
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}

bool	LEDControl32::CommSendBaseCounter(int BoardNo ,int BaseCounter)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return false;
	ReEntrant=true;
	bool	Ret=false;
	BYTE	TxBuff[64];

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='H';
		TxBuff[1]=BoardNo;
		TxBuff[2]=BaseCounter&0xFF;
		TxBuff[3]=BaseCounter>>8;

		Commander->SendStr(TxBuff,64);

		BYTE	RecData[256];
		int		ReceivedLen;
		for(int i=0;i<10;i++){
			GSleep(20);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				Ret=true;
				break;
			}
		}
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}


bool	LEDControl32::CommOutEnableAll(bool OnMode)
{
	return CommOutEnable(255,OnMode);
}

bool	LEDControl32::CommSendData(int BoardNo,QProgressBar *bar)
{
	for(int P=0;P<LEDPatternCount;P++){
		if(CommSendData(BoardNo,P)==false){
			return false;
		}
		if(bar!=NULL){
			bar->setValue(bar->value()+1);
		}
	}

	return true;
}

bool	LEDControl32::CommTransferAll(int BoardNo,int PatternNo ,int OutputNumber)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return false;
	bool	Ret=false;
	ReEntrant=true;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){

		BYTE	TxBuff[64];
		TxBuff[0]='D';
		TxBuff[1]=BoardNo;
		TxBuff[2]=PatternNo;
		TxBuff[3]=OutputNumber;

		Commander->SendStr(TxBuff,64);

		BYTE	RecData[256];
		int		ReceivedLen;
		for(int i=0;i<10;i++){
			GSleep(20);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				Ret=true;
				break;
			}
		}
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}


bool	LEDControl32::CommSendData(int BoardNo,int PatternNo)
{
	BYTE	TxBuff[64];
	int	N=LEDCountInSheet/16;
	for(int i=0;i<N;i++){
		int	CountOfTry;
		for(CountOfTry=0;CountOfTry<5;CountOfTry++){
			TryAgain:;
			TxBuff[0]='C';
			TxBuff[1]=BoardNo;
			TxBuff[2]=PatternNo;
			TxBuff[3]=i*16;
			for(int j=0;j<16;j++){
				short	d=0;
				if(PatternNo<LEDPatternCount)
					d=LEDData.Board[BoardNo].Pattern[PatternNo].Brightness[i*16+j];
				TxBuff[4+j*2+0]=d;
				TxBuff[4+j*2+1]=d>>8;
			}
		
			Commander->SendStr(TxBuff,64);

			BYTE	RecData[256];
			int		ReceivedLen;
			int		LoopCount;
			for(LoopCount=0;LoopCount<10;LoopCount++){
				GSleep(20);
				Commander->ReceiveStr(RecData,ReceivedLen);
				if(RecData[0]==0x0a){
					break;
				}
			}
			if(LoopCount<10){
				break;
			}
		}
		if(CountOfTry>=5){
			return false;
		}

	}
	return true;
}

bool	LEDControl32::CommGetPWMData(int BoardNo,int PatternNo ,int Addr, int Data[])
{
	bool	Ret=false;
	if(Commander->IsOpened()==true){
		BYTE	TxBuff[64];
		TxBuff[0]='I';
		TxBuff[1]=BoardNo;
		TxBuff[2]=PatternNo;
		TxBuff[3]=Addr;

		Commander->SendStr(TxBuff,64);
		BYTE	RecData[256];
		int		ReceivedLen;
		GSleep(20);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			for(int i=0;i<16;i++){
				Data[i] =RecData[i*2  ]
						+(RecData[i*2+1]<<8);
			}
			Ret=true;
		}
	}
	return Ret;

}


bool	LEDControl32::CommGetAD(int BoardNo ,int SelectNo,int &Data)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return false;
	bool	Ret=false;
	ReEntrant=true;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		BYTE	TxBuff[64];
		TxBuff[0]='E';
		TxBuff[1]=BoardNo;
		TxBuff[2]=SelectNo;

		Commander->SendStr(TxBuff,64);
		BYTE	RecData[256];
		int		ReceivedLen;
		GSleep(20);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			Data= RecData[1]
				+(RecData[2]<<8);
			Ret=true;
		}
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}

bool	LEDControl32::CommRequireData(int BoardNo ,int addr ,int Cmd ,int &Data)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return false;
	bool	Ret=false;
	ReEntrant=true;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		BYTE	TxBuff[64];
		TxBuff[0]='G';
		TxBuff[1]=BoardNo;
		TxBuff[2]=addr;
		TxBuff[3]=Cmd;

		Commander->SendStr(TxBuff,64);
		BYTE	RecData[256];
		int		ReceivedLen;
		GSleep(20);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			Data= RecData[1]
				+(RecData[2]<<8);
			Ret=true;
		}
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}

bool	LEDControl32::CommSetOutputNumber(int SelectNo)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return false;
	ReEntrant=true;
	bool	Ret=false;
	BYTE	TxBuff[64];

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='J';
		TxBuff[1]=SelectNo;

		Commander->SendStr(TxBuff,64);

		BYTE	RecData[256];
		int		ReceivedLen;
		for(int i=0;i<10;i++){
			GSleep(20);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				Ret=true;
				break;
			}
		}
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}

