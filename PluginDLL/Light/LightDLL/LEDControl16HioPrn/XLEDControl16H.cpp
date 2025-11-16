#include "XTypeDef.h"
#include "LEDControl16HioPrn.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XHidCommand.h"
#include "LEDControl16HDialog.h"
#include "LEDControl16HPrnDialog.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "TimingChartForm.h"
#include "swap.h"
#include <QApplication>

QString	LEDControl16HioPanel::DefFileName		=/**/"LEDControl16HioPrnDef.dat";
QString	LEDControl16HioPanel::DefaultFileName	=/**/"LEDControl16HioPrnDefault.dat";

//----------------------------------------------------------------
	
bool	LEDControl16HioPanel::LoadDef(void)
{
	QFile	DefFile(DefFileName);
	if(DefFile.open(QIODevice::ReadOnly)==true){
		return LoadDef(&DefFile);
	}
	return false;
}
	
bool	LEDControl16HioPanel::SaveDef(void)
{
	QFile	DefFile(DefFileName);
	if(DefFile.open(QIODevice::WriteOnly)==true){
		return SaveDef(&DefFile);
	}
	return false;
}

bool	LEDControl16HioPanel::SaveDefault(void)
{
	QFile	DFile(DefaultFileName);
	if(DFile.open(QIODevice::WriteOnly)==true){
		return Save(&DFile);
	}
	return false;
}

bool	LEDControl16HioPanel::LoadDefault(void)
{
	QFile	DFile(DefaultFileName);
	if(DFile.open(QIODevice::ReadOnly)==true){
		return Load(&DFile);
	}
	return false;
}

LEDControl16HioPanel::LEDControl16HioPanel(LayersBase *base ,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
	,Sock((base->GetMainWidget()!=NULL)?base->GetMainWidget():QApplication::activeWindow())
{
	Opened=false;
	LightForm	=NULL;
	GIOForm		=NULL;
	TimingChart	=NULL;
	BoardCount	=0;

	Param=LightParamStr;
	CurrentPattern	=0;

	AllocTimingDim	=100000000;
	TimingDim		=new struct  TimingData[AllocTimingDim];
	WPointTiming	=0;

	ReceivedMaxLen=1000000;
	ReceivedData=new BYTE[ReceivedMaxLen];

	AccessIPAddress			=/**/"RaspberryPi";
	AccessPort				=LEDControllerPort;

	LoadDef();

	if(LightParamStr.isEmpty()==false){
		QStringList	List=LightParamStr.split(QRegularExpression("[, ]"));

		if(List.count()>0){
			if(List[0].isEmpty()==false){
				AccessIPAddress=List[0];
			}
		}
		if(List.count()>1){
			if(List[1].isNull()==false){
				AccessPort=List[1].toInt();
			}
		}

		if(List.count()>2){
			QString	AllocationFileName;
			AllocationFileName=List[2];
			QFile	File(AllocationFileName);
			if(File.open(QIODevice::ReadOnly)==true){
				LoadAllocationFile(&File);
			}
		}
	}

	bool	Ret=(connect(&Sock,SIGNAL(readyRead()),this,SLOT(SlotReadyRead())))?true:false;


	if(Open()==true){
		GetVersion();
	}

	Transfer(0,NULL);

	TM.setSingleShot(false);
	TM.setInterval(1000);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}
LEDControl16HioPanel::~LEDControl16HioPanel(void)
{
	delete	[]ReceivedData;
	ReceivedData=NULL;
	delete	[]TimingDim;
	TimingDim=NULL;
}



bool	LEDControl16HioPanel::Initial(bool OutputMode)
{	
	return true;
}
bool	LEDControl16HioPanel::Open(void)
{
	Sock.connectToHost(AccessIPAddress,AccessPort);
	Sock.waitForConnected(10000);
	if(Sock.state()==QAbstractSocket::ConnectedState)
		return true;
	return false;
}
bool	LEDControl16HioPanel::Close(void)
{	
	return true;
}

void	LEDControl16HioPanel::GetVersion(void)
{
	BYTE	Data[100];

	int ReceivedByte;
	BYTE	RecCmd;
	if(ReadRegister (-1,'V',Data ,0,RecCmd,ReceivedByte ,sizeof(Data))==true){
		VersionStr=QString((char *)Data);
	}

	if(ReadRegister (-1,'U',Data ,0,RecCmd,ReceivedByte ,sizeof(Data))==true){
		BoardCount=Data[0];
		for(int k=0;k<BoardCount;k++){
			BoardData[k].DipSW=Data[1+k];
		}
	}
}

void	LEDControl16HioPanel::Transfer(int PatternNumber,QProgressBar *Bar)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	int	LEDCountInSheet=0;


	if(Bar!=NULL){
		Bar->setMaximum(BoardCount);
	}

	if(Bar!=NULL){
		Bar->setValue(0);
	}

	AccessHID.lock();

	for(int i=0;i<BoardCount;i++){
		if(BoardData[i].SetLightData(PatternNumber)==false)
			break;

		if(Bar!=NULL){
			Bar->setValue(Bar->value()+1);
		}
	}

	AccessHID.unlock();

	ReEntrant=false;

	//int		RegData=-1;
	//GetRegisterData(0 ,1 ,2 ,RegData);
}

void	LEDControl16HioPanel::TransmitDirectly(GUIDirectMessage *packet)
{

}

bool	LEDControl16HioPanel::SaveDef(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,UsageLines)==false)
		return false;
	int32	N=sizeof(LineData)/sizeof(LineData[0]);
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N && i<UsageLines;i++){
		if(f->write((const char *)&LineData[i],sizeof(LineData[0]))==sizeof(LineData[0]))
			return false;
	}
	return true;
}
	
bool	LEDControl16HioPanel::LoadDef(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,UsageLines)==false)
		return false;
	int32	tN=sizeof(LineData)/sizeof(LineData[0]);
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N && i<tN && i<UsageLines;i++){
		if(f->read((char *)&LineData[i],sizeof(LineData[0]))==sizeof(LineData[0]))
			return false;
	}
	return true;
}

bool	LEDControl16HioPanel::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,BoardCount)==false)
		return false;
	for(int i=0;i<BoardCount;i++){
		if(BoardData[i].Save(f)==false)
			return false;
	}
	if(HIOFixedData.Save(f)==false)
		return false;
	if(HIOPortName.Save(f)==false)
		return false;
	return true;
}
bool	LEDControl16HioPanel::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N && i<BoardCount;i++){
		if(BoardData[i].Load(f)==false)
			return false;
	}
	if(HIOFixedData.Load(f)==false)
		return false;
	if(HIOPortName.Load(f)==false)
		return false;
	return true;
}

bool	LEDControl16HioPanel::SetOnOff(bool OnMode)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	AccessHID.lock();
	for(int i=0;i<BoardCount;i++){
		if(BoardData[i].SetAllON(OnMode)==false)
			return false;
	}
	AccessHID.unlock();

	ReEntrant=false;
	return true;
}

bool	LEDControl16HioPanel::ShowSettingDialog(void)
{
	//LightForm=new LEDControl16HDialog(this);
	//bool	Ret=LightForm->exec();
	//delete LightForm;
	//LightForm=NULL;

	GIOForm=new LEDControl16HPrnDialog(this);
	bool	Ret=GIOForm->exec();
	delete GIOForm;
	GIOForm=NULL;

	return Ret;
}

	//Don't call directly
bool	LEDControl16HioPanel::InitialPhysical(const QString &Param)
{
	Initial(true);
	return true;
}

bool	LEDControl16HioPanel::ReflectPhysical(void)
{
	if(LightForm!=NULL){
		Transfer(0,LightForm->GetBar());
	}
	else{
		Transfer(0,NULL);
	}

	return true;
}
bool	LEDControl16HioPanel::ReflectPhysicalTurnOn(bool LightOn)
{
	SetOnOff(LightOn);
	return true;
}

bool	LEDControl16HioPanel::WriteRegister(BYTE DipSW,BYTE Cmd ,BYTE Data[] ,unsigned short DataLen)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	AccessHID.lock();
	if(Sock.state()!=QAbstractSocket::ConnectedState)
		Open();
	if(Sock.state()==QAbstractSocket::ConnectedState){
		BYTE    Header[4];
		Header[0]=DipSW;
		Header[1]=Cmd;
		Header[2]=DataLen&0xFF;
		Header[3]=DataLen>>8;
		Sock.write((const char *)Header,4);
		if(DataLen>0){
			Sock.write((const char *)Data,DataLen);
		}
		Sock.flush();
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}
bool	LEDControl16HioPanel::ReadRegister (BYTE DipSW,BYTE Cmd ,BYTE Data[] ,unsigned short SendDataLen
										,BYTE &RecCmd ,int &ReceivedDataByte ,int MaxDataLen
										,int WaitingMilisec)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return false;
	ReEntrant=true;
	bool	Ret=false;

	AccessHID.lock();
	if(Sock.state()!=QAbstractSocket::ConnectedState)
		Open();
	if(Sock.state()==QAbstractSocket::ConnectedState){
		BYTE    Header[4];
		Header[0]=DipSW;
		Header[1]=Cmd;
		Header[2]=SendDataLen&0xFF;
		Header[3]=SendDataLen>>8;
		Sock.write((const char *)Header,4);
		if(SendDataLen>0){
			Sock.write((const char *)Data,SendDataLen);
		}
		Sock.flush();

		Sock.waitForReadyRead(WaitingMilisec);
		if(Received==true){
			RecCmd			=ReceivedCmd;
			int	Len=min(ReceivedLen,MaxDataLen);
			if(Len>0){
				memcpy(Data,ReceivedData,Len);
			}
			ReceivedDataByte=Len;
			Ret=true;
		}
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}

void    LEDControl16HioPanel::SlotReadyRead()
{
    BYTE    Header[4];

    if(Sock.read((char *)Header,4)!=4){
        QByteArray A=Sock.readAll();
        return;
    }
    ReceivedDipSW=Header[0];
    ReceivedCmd  =Header[1];
    ReceivedLen=(unsigned short)(Header[2] + (Header[3]<<8));

	int	RLen=min(ReceivedLen,ReceivedMaxLen);
	if(Sock.read((char *)ReceivedData,RLen)==RLen){
		ReceivedLen=RLen;
		Received=true;
	}
}

void	LEDControl16HioPanel::SlotTimeOut()
{
	if(WPointTiming<AllocTimingDim){
		BYTE	Data[12*256+1];
		int ReceivedByte;
		BYTE	RecCmd;
		ReadRegister (-1,'C',Data ,0,RecCmd,ReceivedByte ,sizeof(Data));
		if(RecCmd=='C' && ReceivedByte>0){
			int	LNumb=Data[0];
			int	WNumb=0;
			int TimingDataSize=sizeof(struct TimingData);
			for(int i=1
			;(i+TimingDataSize)<=ReceivedByte && WNumb<LNumb
			;i+=TimingDataSize,WNumb++){
				struct TimingData	*p=(struct TimingData *)&Data[i];
				TimingDim[WPointTiming]=*p;
				WPointTiming++;
				if(WPointTiming>=AllocTimingDim){
					break;
				}
			}
		}
	}
}

bool	LEDControl16HioPanel::SendGio(void)
{
	BYTE	Data[100];
	memcpy(Data,&HIOFixedData,sizeof(HIOFixedData));
	int	Len=sizeof(HIOFixedData);
	if(WriteRegister(-1,'A',Data,Len)==true){
		return true;
	}
	return false;
}

bool	LEDControl16HioPanel::RequireGio(void)
{
	BYTE	Data[100];
	int ReceivedByte;
	BYTE	RecCmd;
	ReadRegister (-1,'B',Data ,1,RecCmd,ReceivedByte ,sizeof(Data));
	if(RecCmd=='B' && ReceivedByte==sizeof(HIOFixedData)){
		memcpy(&HIOFixedData,Data,sizeof(HIOFixedData));
		return true;
	}
	return false;
}
void	LEDControl16HioPanel::ShowTimingChart(void)
{
	if(TimingChart!=NULL){
		TimingChart->show();
	}
	else{
		TimingChart=new TimingChartForm(this);
		TimingChart->show();
	}
}
	
int	LEDControl16HioPanel::FindTiming(DWORD st)	//stÇÊÇËëÂÇ´Ç¢ç≈èâÇÃóvëfÇãÅÇﬂÇÈ
{
	for(int i=0;i<WPointTiming;i++){
		if(st<=TimingDim[i].CurrentMiliSec){
			return i;
		}
	}
	return -1;
}

struct  TimingData	*LEDControl16HioPanel::GetTiming(int point)
{
	return &TimingDim[point];
}
