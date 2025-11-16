#include "LEDControl16P16.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XHidCommand.h"
#include "SettingDialog.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

LEDControl16P16Panel::LineValue::LineValue(void)
{
	Pointer		=NULL;
	BoardNumber	=-1;
	LineNumber	=-1;
	Value		=0;
}

bool	LEDControl16P16Panel::LineValue::Save(QIODevice *f)
{
	if(::Save(f,Value)==false)
		return false;
	if(::Save(f,Comment)==false)
		return false;
	return true;
}

bool	LEDControl16P16Panel::LineValue::Load(QIODevice *f)
{
	if(::Load(f,Value)==false)
		return false;
	if(::Load(f,Comment)==false)
		return false;
	return true;
}

//----------------------------------------------------------------

bool	LEDControl16P16Panel::LightPattern::Save(QIODevice *f)
{
	int32	N=sizeof(LineValues)/sizeof(LineValues[0]);
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(LineValues[i].Save(f)==false)
			return false;
	}
	if(::Save(f,Comment)==false)
		return false;
	return true;
}
bool	LEDControl16P16Panel::LightPattern::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	int	i;
	for(i=0;i<N && i<sizeof(LineValues)/sizeof(LineValues[0]);i++){
		if(LineValues[i].Load(f)==false)
			return false;
	}
	for(;i<N;i++){
		LineValue	DummyData;
		if(DummyData.Load(f)==false)
			return false;
	}
	if(::Load(f,Comment)==false)
		return false;
	return true;
}

//----------------------------------------------------------------

LEDControl16P16Panel::PortData::PortData(void)
{
	UsageLines=16;
}


bool	LEDControl16P16Panel::PortData::Save(QIODevice *f)
{
	if(::Save(f,UsageLines)==false)
		return false;
	int32	PatternNumb=sizeof(PatternData)/sizeof(PatternData[0]);
	if(::Save(f,PatternNumb)==false)
		return false;
	for(int i=0;i<PatternNumb;i++){
		if(PatternData[i].Save(f)==false)
			return false;
	}
	if(::Save(f,Comment)==false)
		return false;
	return true;
}
bool	LEDControl16P16Panel::PortData::Load(QIODevice *f)
{
	if(::Load(f,UsageLines)==false)
		return false;
	int32	PatternNumb;
	if(::Load(f,PatternNumb)==false)
		return false;
	int	i;
	for(i=0;i<PatternNumb && i<sizeof(PatternData)/sizeof(PatternData[0]);i++){
		if(PatternData[i].Load(f)==false)
			return false;
	}
	for(;i<PatternNumb;i++){
		LightPattern	DummyData;
		if(DummyData.Load(f)==false)
			return false;
	}
	if(::Load(f,Comment)==false)
		return false;
	return true;
}

//----------------------------------------------------------------

LEDControl16P16Panel::LEDControl16P16Panel(LayersBase *base ,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	Commander=HidCommand::Create((QWidget *)this);

	Opened=false;
	StopInput	=false;
	LightForm	=NULL;

	Param=LightParamStr;
	CurrentPattern	=0;
	LightDataNumb	=1;
	BoardCount		=0;
	Number			=0;
	ContinuousMode	=10000;

	QStringList	List=LightParamStr.split(QRegularExpression("[, ]"));
	int	MaxValue	=1000;

	if(List.count()>0){
		if(List[0].isNull()==false){
			LightDataNumb=List[0].toInt();
		}
	}
	if(LightDataNumb==0)
		LightDataNumb=1;

	if(List.count()>1){
		if(List[1].isNull()==false){
			MaxValue=List[1].toInt();
		}
	}

	BoardData[1].BaseCounter				=1023;
	BoardData[1].EPROMData[0].UsageLines	=32;
	BoardData[1].EPROMData[0].LineData[0].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[0].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[1].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[1].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[2].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[2].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[3].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[3].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[4].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[4].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[5].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[5].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[6].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[6].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[7].ColorType		=0;
	BoardData[1].EPROMData[0].LineData[7].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[8].ColorType		=1;
	BoardData[1].EPROMData[0].LineData[8].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[9].ColorType		=1;
	BoardData[1].EPROMData[0].LineData[9].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[10].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[10].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[11].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[11].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[12].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[12].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[13].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[13].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[14].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[14].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[15].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[15].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[16].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[16].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[17].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[17].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[18].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[18].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[19].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[19].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[20].ColorType	=0;
	BoardData[1].EPROMData[0].LineData[20].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[21].ColorType	=0;
	BoardData[1].EPROMData[0].LineData[21].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[22].ColorType	=0;
	BoardData[1].EPROMData[0].LineData[22].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[23].ColorType	=0;
	BoardData[1].EPROMData[0].LineData[24].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[24].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[24].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[25].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[25].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[26].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[26].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[27].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[27].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[28].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[28].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[29].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[29].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[30].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[30].MaxCurrent	=MaxValue;
	BoardData[1].EPROMData[0].LineData[31].ColorType	=1;
	BoardData[1].EPROMData[0].LineData[31].MaxCurrent	=MaxValue;

	BoardData[0].BaseCounter				=1023;
	BoardData[0].EPROMData[0].UsageLines	=16;
	BoardData[0].EPROMData[0].LineData[0].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[0].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[1].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[1].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[2].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[2].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[3].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[3].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[4].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[4].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[5].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[5].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[6].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[6].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[7].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[7].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[8].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[8].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[9].ColorType		=2;
	BoardData[0].EPROMData[0].LineData[9].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[10].ColorType	=2;
	BoardData[0].EPROMData[0].LineData[10].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[11].ColorType	=2;
	BoardData[0].EPROMData[0].LineData[11].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[12].ColorType	=2;
	BoardData[0].EPROMData[0].LineData[12].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[13].ColorType	=2;
	BoardData[0].EPROMData[0].LineData[13].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[14].ColorType	=2;
	BoardData[0].EPROMData[0].LineData[14].MaxCurrent	=MaxValue;
	BoardData[0].EPROMData[0].LineData[15].ColorType	=2;
	BoardData[0].EPROMData[0].LineData[15].MaxCurrent	=MaxValue;


	if(Open()==true){
		GetVersion();
	}
	/*
	TM.setInterval(10);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
	*/
}
LEDControl16P16Panel::~LEDControl16P16Panel(void)
{
	delete	Commander;
	Commander=NULL;
}


bool	LEDControl16P16Panel::Initial(bool OutputMode)
{	
	return true;
}
bool	LEDControl16P16Panel::Open(void)
{
	if(Commander->OpenHid(0x1255, 0x0009,Number)==false){
		return false;
	}
	return true;
}
bool	LEDControl16P16Panel::Close(void)
{	
	return true;
}

void	LEDControl16P16Panel::GetVersion(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		Commander->SendStr((BYTE *)"V",1);
		BYTE	RecData[256];
		int		ReceivedLen;
		GSleep(100);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			VersionStr=((char *)RecData);
		}
		BYTE	TxBuff[64];
		TxBuff[0]='A';
		TxBuff[1]=3;
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
			
		Commander->SendStr((BYTE *)"a",1);
		GSleep(100);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			BoardCount=RecData[0];
		}
		Commander->CloseHid();
		GSleep(10);
	}
	AccessHID.unlock();
	ReEntrant=false;
}

void	LEDControl16P16Panel::Transfer(int PatternNumber,QProgressBar *Bar)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	int	LEDCountInSheet=0;
	int	PatternNumb=sizeof(LightData[0].PatternData)/sizeof(LightData[0].PatternData[0]);
	for(int i=0;i<LightDataNumb;i++){
		for(int p=0;p<PatternNumb;p++){
			for(int j=0;j<LightData[i].UsageLines;j++){
				LEDCountInSheet++;
			}
		}
	}

	if(Bar!=NULL){
		Bar->setMaximum(LEDCountInSheet);
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
		/*
		TxBuff[0]='C';
		int		BaseCounter=1023;
		for(int i=0;i<BoardCount;i++){
			TxBuff[1]=i;
			TxBuff[2]=BaseCounter&0xFF;
			TxBuff[3]=(BaseCounter>>8)&0xFF;

			Commander->SendStr(TxBuff,64);
			for(int i=0;i<10;i++){
				GSleep(10);
				Commander->ReceiveStr(RecData,ReceivedLen);
				if(RecData[0]==0x0a){
					break;
				}
			}
			GSleep(10);
		}
		GSleep(10);
		*/

		TxBuff[0]='B';
		for(int L=0;L<LightDataNumb;L++){
			for(int p=0;p<PatternNumb;p++){
				for(int j=0;j<LightData[L].UsageLines;j++){
					int	BoardNumber	=L;
					int	Addr		=j;
					int	Value		=LightData[L].PatternData[p].LineValues[j].Value;

					//int	MaxValue	=LightData[L].PatternData[0].LineValues[j].Pointer->MaxCurrent;
					//if(Value>MaxValue)
					//	Value=MaxValue;
						
					TxBuff[1]=BoardNumber;
					TxBuff[2]=p;
					TxBuff[3]=Addr;
					TxBuff[4]=Value;
					TxBuff[5]=Value>>8;

					Commander->SendStr(TxBuff,64);
					for(int h=0;h<10;h++){
						GSleep(10);
						Commander->ReceiveStr(RecData,ReceivedLen);
						if(RecData[0]==0x0a){
							break;
						}
					}
					if(Bar!=NULL){
						Bar->setValue(Bar->value()+1);
					}
					GSleep(10);
				}
			}
		}
		Commander->CloseHid();
	}
	AccessHID.unlock();
	
	ReEntrant=false;
}

void	LEDControl16P16Panel::TransmitDirectly(GUIDirectMessage *packet)
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;
}

bool	LEDControl16P16Panel::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,LightDataNumb)==false)
		return false;
	int32	N=sizeof(LightData)/sizeof(LightData[0]);
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(LightData[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	LEDControl16P16Panel::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,LightDataNumb)==false)
		return false;
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N && i<sizeof(LightData)/sizeof(LightData[0]);i++){
		if(LightData[i].Load(f)==false)
			return false;
	}
	return true;
}

bool	LEDControl16P16Panel::SetOnOff(bool OnMode)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='I';
		if(OnMode==true)
			TxBuff[1]='1';
		else
			TxBuff[1]='0';

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		GSleep(10);
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}

bool	LEDControl16P16Panel::LoadADData(int BoardNumber ,int ADNumber)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='h';
		TxBuff[1]=BoardNumber;
		TxBuff[2]=ADNumber;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				BoardData[BoardNumber].ADData[ADNumber]=RecData[1]+(RecData[2]<<8);
				break;
			}
		}
		GSleep(10);
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}

bool	LEDControl16P16Panel::LoadInputData(int BoardNumber)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='j';
		TxBuff[1]=BoardNumber;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				BoardData[BoardNumber].InputData[0]=RecData[1];
				BoardData[BoardNumber].InputData[1]=RecData[2];
				BoardData[BoardNumber].InputData[2]=RecData[3];
				BoardData[BoardNumber].InputData[3]=RecData[4];
				break;
			}
		}
		GSleep(10);
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}

bool	LEDControl16P16Panel::SetTestLED(bool ONMode)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		for(int BoardNo=0;BoardNo<16;BoardNo++){
			TxBuff[0]='N';
			TxBuff[1]=BoardNo;					//Board number
			TxBuff[2]=(ONMode==true)?1:0;

			Commander->SendStr(TxBuff,64);
			for(int i=0;i<10;i++){
				GSleep(10);
				Commander->ReceiveStr(RecData,ReceivedLen);
				if(RecData[0]==0x0a){
					break;
				}
			}
			GSleep(10);
		}
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;

}

bool	LEDControl16P16Panel::ShowPattern(int PatternNo)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='P';
		TxBuff[1]=PatternNo;					//Board number

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		GSleep(10);
	}
	Commander->CloseHid();

	AccessHID.unlock();
	ReEntrant=false;
	return true;
}



bool	LEDControl16P16Panel::ShowSettingDialog(void)
{
	LightForm=new SettingDialog(this);
	bool	Ret=LightForm->exec();
	delete LightForm;
	LightForm=NULL;

	return Ret;
}

	//Don't call directly
bool	LEDControl16P16Panel::InitialPhysical(const QString &Param)
{
	Initial(true);
	return true;
}

bool	LEDControl16P16Panel::ReflectPhysical(void)
{
	if(LightForm!=NULL){
		Transfer(0,LightForm->GetBar());
	}
	else{
		Transfer(0,NULL);
	}

	return true;
}
bool	LEDControl16P16Panel::ReflectPhysicalTurnOn(bool LightOn)
{
	SetOnOff(LightOn);
	return true;
}



void	LEDControl16P16Panel::SlotTimeOut()
{
}


