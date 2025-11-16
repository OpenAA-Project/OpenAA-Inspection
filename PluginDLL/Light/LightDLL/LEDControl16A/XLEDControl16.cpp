#include "LEDControl16A.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XHidCommand.h"
#include "SettingDialog.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"


//----------------------------------------------------------------

LEDControl16APanel::LEDControl16APanel(LayersBase *base ,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	Commander=HidCommand::Create((QWidget *)this);

	Opened=false;
	StopInput	=false;
	LightForm	=NULL;

	Param=LightParamStr;
	CurrentPattern	=0;
	LightDataNumb	=3;
	BoardCount		=0;
	Number			=0;
	ContinuousMode	=10000;

	InitialEPRom();

	QStringList	List=LightParamStr.split(QRegularExpression("[, ]"));
	int	MaxValue	=1000;

	if(List.count()>0){
		if(List[0].isNull()==false){
			Number=List[0].toInt();
		}
	}
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


	if(List.count()>2){
		QString	AllocationFileName;
		AllocationFileName=List[2];
		QFile	File(AllocationFileName);
		if(File.open(QIODevice::ReadOnly)==true){
			LoadAllocationFile(&File);
		}
	}

	BuildDataFromEPRom();


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
LEDControl16APanel::~LEDControl16APanel(void)
{
	delete	Commander;
	Commander=NULL;
}


void	LEDControl16APanel::InitialEPRom(void)
{
	for(int i=0;i<sizeof(BoardData)/sizeof(BoardData[0]);i++){
		BoardData[i].BaseCounter=0;
		BoardData[i].PortSel	=0;
		BoardData[i].PWMSelector=0;
		BoardData[i].ADSel		=0;
		for(int j=0;j<sizeof(BoardData[0].EPROMData)/sizeof(BoardData[0].EPROMData[0]);j++){
			BoardData[i].EPROMData[j].UsageLines	=0;
			for(int k=0;k<sizeof(BoardData[i].EPROMData[j].LineData)/sizeof(BoardData[i].EPROMData[j].LineData[0]);k++){
				BoardData[i].EPROMData[j].LineData[k].ColorType	=0xFF;
				BoardData[i].EPROMData[j].LineData[k].MaxCurrent=0;
			}
		}
		for(int j=0;j<sizeof(BoardData[0].ADData)/sizeof(BoardData[0].ADData[0]);j++){
			BoardData[i].ADData[j]=0;
		}
	}
}

void	LEDControl16APanel::BuildDataFromEPRom(void)
{
	LightDataNumb	=0;
	for(int i=0;i<sizeof(BoardData)/sizeof(BoardData[0]);i++){
		for(int j=0;j<sizeof(BoardData[0].EPROMData)/sizeof(BoardData[0].EPROMData[0]);j++){
			if(BoardData[i].EPROMData[j].UsageLines==0)
				continue;
			int	ColorTypeDim[256];
			int	ColorTypeDimNumb=0;
			for(int k=0;k<BoardData[i].EPROMData[j].UsageLines;k++){
				int	d=BoardData[i].EPROMData[j].LineData[k].ColorType;
				int	h=0;
				for(h=0;h<ColorTypeDimNumb;h++){
					if(ColorTypeDim[h]==d)
						break;
				}
				if(h>=ColorTypeDimNumb){
					ColorTypeDim[ColorTypeDimNumb]=d;
					ColorTypeDimNumb++;
				}
			}
			for(int h=0;h<ColorTypeDimNumb;h++){
				LightData[LightDataNumb].UsageLines=0;
				for(int k=0;k<BoardData[i].EPROMData[j].UsageLines;k++){
					int	d=BoardData[i].EPROMData[j].LineData[k].ColorType;
					if(d==ColorTypeDim[h]){
						int	n=LightData[LightDataNumb].UsageLines;
						LightData[LightDataNumb].PatternData[0].LineValues[n].Pointer		=&BoardData[i].EPROMData[j].LineData[k];
						LightData[LightDataNumb].PatternData[0].LineValues[n].BoardNumber	=i + (k/16);
						LightData[LightDataNumb].PatternData[0].LineValues[n].LineNumber	=k%16;
						LightData[LightDataNumb].UsageLines++;
					}
				}
				LightDataNumb++;
			}
		}
	}
}

bool	LEDControl16APanel::Initial(bool OutputMode)
{	
	return true;
}
bool	LEDControl16APanel::Open(void)
{
	if(Commander->OpenHid(0x1255, 0x000A,Number)==false){
		return false;
	}
	return true;
}
bool	LEDControl16APanel::Close(void)
{	
	return true;
}

void	LEDControl16APanel::GetVersion(void)
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

	int	ADID;
	LoadAD_Register(0,9,ADID);
	int	ADCIO;
	LoadAD_Register(0,7,ADCIO);
	int	ADDIO;
	LoadAD_Register(0,8,ADDIO);

	ReEntrant=false;
}
void	LEDControl16APanel::Transfer(int PatternNumber,QProgressBar *Bar)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	int	LEDCountInSheet=0;
	for(int i=0;i<LightDataNumb;i++){
		for(int p=0;p<sizeof(LightData[0].PatternData)/sizeof(LightData[0].PatternData[0]);p++){
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

		TxBuff[0]='B';
		for(int p=0;p<sizeof(LightData[0].PatternData)/sizeof(LightData[0].PatternData[0]);p++){
			for(int i=0;i<LightDataNumb;i++){
				for(int j=0;j<LightData[i].UsageLines;j++){
					int	BoardNumber	=LightData[i].PatternData[0].LineValues[j].BoardNumber;
					int	Addr		=LightData[i].PatternData[0].LineValues[j].LineNumber;
					int	Value		=LightData[i].PatternData[0].LineValues[j].Value;

					int	MaxValue	=LightData[i].PatternData[0].LineValues[j].Pointer->MaxCurrent;
					if(Value>MaxValue)
						Value=MaxValue;
						
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

void	LEDControl16APanel::TransmitDirectly(GUIDirectMessage *packet)
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	/*
	CmdReqInput	*CmdReqInputVar=dynamic_cast<CmdReqInput *>(packet);
	if(CmdReqInputVar!=NULL){
		CmdReqInputVar->Data=LastInput;

		return;
	}
	CmdSetMode	*CmdSetModeVar=dynamic_cast<CmdSetMode *>(packet);
	if(CmdSetModeVar!=NULL){
		AccessHID.lock();
		if(Commander->IsOpened()==false)
			Open();
		if(Commander->IsOpened()==true){
			TxBuff[0]='C';
			TxBuff[1]=CmdSetModeVar->LightMode;

			Commander->SendStr(TxBuff,64);
			for(int i=0;i<10;i++){
				GSleep(10);
				Commander->ReceiveStr(RecData,ReceivedLen);
				if(RecData[0]==0x0a){
					break;
				}
			}
		}
		Commander->CloseHid();
		AccessHID.unlock();
		return;
	}
	CmdStopMode	*CmdStopModeVar=dynamic_cast<CmdStopMode *>(packet);
	if(CmdStopModeVar!=NULL){
		StopInput=true;
		return;
	}
	CmdRestartMode	*CmdRestartModeVar=dynamic_cast<CmdRestartMode *>(packet);
	if(CmdRestartModeVar!=NULL){
		StopInput=false;
		return;
	}
	*/
}

bool	LEDControl16APanel::Save(QIODevice *f)
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
bool	LEDControl16APanel::Load(QIODevice *f)
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

bool	LEDControl16APanel::SetOnOff(bool OnMode)
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

bool	LEDControl16APanel::SetTemporaryON(int32 ContinuousCount)
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
		TxBuff[0]='O';
		TxBuff[1]=ContinuousCount;
		TxBuff[2]=ContinuousCount>>8;
		TxBuff[3]=ContinuousCount>>16;
		TxBuff[4]=ContinuousCount>>24;

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

bool	LEDControl16APanel::LoadADData(int BoardNumber ,int ADNumber)
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

bool	LEDControl16APanel::LoadAD_Register(int BoardNumber ,int adr ,int &RegData)
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
		TxBuff[1]=BoardNumber;
		TxBuff[2]=adr;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				RegData=RecData[1];
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

bool	LEDControl16APanel::LoadInputData(int BoardNumber)
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

bool	LEDControl16APanel::SetTestLED(bool ONMode)
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

bool	LEDControl16APanel::ReadEPRom(int BoardNumber ,int PortNumber ,struct LightUnit &Data)
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

		//Read EPROM data to buffer
		TxBuff[0]='M';
		TxBuff[1]=BoardNumber;					//Board number
		TxBuff[2]=PortNumber;
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		for(int k=0;k<sizeof(Data.LineData)/sizeof(Data.LineData[0]);k++){
			TxBuff[0]='k';
			TxBuff[1]=BoardNumber;					//Board number
			TxBuff[2]=PortNumber;
			TxBuff[3]=k;
			Commander->SendStr(TxBuff,64);
			for(int i=0;i<10;i++){
				GSleep(10);
				Commander->ReceiveStr(RecData,ReceivedLen);
				if(RecData[0]==0x0a){
					Data.UsageLines				=RecData[1];
					Data.LineData[k].ColorType  =RecData[2];
					Data.LineData[k].MaxCurrent	=RecData[3] + (RecData[4]<<8);
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

bool	LEDControl16APanel::WriteEPRom(int BoardNumber ,int PortNumber ,struct LightUnit &Data)
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

		for(int k=0;k<sizeof(Data.LineData)/sizeof(Data.LineData[0]);k++){
			TxBuff[0]='K';
			TxBuff[1]=BoardNumber;					//Board number
			TxBuff[2]=PortNumber;
			TxBuff[3]=Data.UsageLines;
			TxBuff[4]=k;
			TxBuff[5]=Data.LineData[k].ColorType;
			TxBuff[6]=Data.LineData[k].MaxCurrent & 0xFF;
			TxBuff[7]=(Data.LineData[k].MaxCurrent>>8) & 0xFF;
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

		//Write EPROM data to buffer
		TxBuff[0]='L';
		TxBuff[1]=BoardNumber;					//Board number
		TxBuff[2]=PortNumber;
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
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

int		LEDControl16APanel::ReadEPRomStatus(int BoardNumber ,int PortNumber)
{
	static	bool	ReEntrant=false;
	int	Ret=0;

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
		TxBuff[0]='l';
		TxBuff[1]=BoardNumber;
		TxBuff[2]=PortNumber;

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(10);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				Ret=RecData[1];
				break;
			}
		}
		GSleep(10);
		Commander->CloseHid();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}

bool	LEDControl16APanel::ShowSettingDialog(void)
{
	LightForm=new SettingDialog(this);
	bool	Ret=LightForm->exec();
	delete LightForm;
	LightForm=NULL;

	return Ret;
}

	//Don't call directly
bool	LEDControl16APanel::InitialPhysical(const QString &Param)
{
	Initial(true);
	return true;
}

bool	LEDControl16APanel::ReflectPhysical(void)
{
	if(LightForm!=NULL){
		Transfer(0,LightForm->GetBar());
	}
	else{
		Transfer(0,NULL);
	}

	return true;
}
bool	LEDControl16APanel::ReflectPhysicalTurnOn(bool LightOn)
{
	SetOnOff(LightOn);
	return true;
}



void	LEDControl16APanel::SlotTimeOut()
{
}


