#include "XTypeDef.h"
#include "LEDControl16KDSBelt.h"
#include "LEDControl16KDSBeltCommon.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XHidCommand.h"
#include "LEDControl16KDSBeltDialog.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include <QMessageBox>
#include <QApplication>

QString	LEDControl16KDSBeltPanel::DefFileName		=/**/"LEDControl16GPrnDef.dat";
QString	LEDControl16KDSBeltPanel::DefaultFileName	=/**/"LEDControl16GPrnDefault.dat";

//----------------------------------------------------------------
	
bool	LEDControl16KDSBeltPanel::LoadDef(void)
{
	QFile	DefFile(DefFileName);
	if(DefFile.open(QIODevice::ReadOnly)==true){
		return LoadDef(&DefFile);
	}
	return false;
}
	
bool	LEDControl16KDSBeltPanel::SaveDef(void)
{
	QFile	DefFile(DefFileName);
	if(DefFile.open(QIODevice::WriteOnly)==true){
		return SaveDef(&DefFile);
	}
	return false;
}

bool	LEDControl16KDSBeltPanel::SaveDefault(void)
{
	QFile	DFile(DefaultFileName);
	if(DFile.open(QIODevice::WriteOnly)==true){
		return Save(&DFile);
	}
	return false;
}

bool	LEDControl16KDSBeltPanel::LoadDefault(void)
{
	QFile	DFile(DefaultFileName);
	if(DFile.open(QIODevice::ReadOnly)==true){
		return Load(&DFile);
	}
	return false;
}

LEDControl16KDSBeltPanel::LEDControl16KDSBeltPanel(LayersBase *base ,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
	,Sock((base->GetMainWidget()!=NULL)?base->GetMainWidget():QApplication::activeWindow())
{
	Opened=false;
	GIOForm		=NULL;
	BoardCount	=0;

	Param=LightParamStr;
	CurrentPattern	=0;

	AllocTimingDim	=100000000;
	TimingDim		=new struct  TimingData[AllocTimingDim];
	WPointTiming	=0;

	ReceivedMaxLen=1000000;
	ReceivedData=new BYTE[ReceivedMaxLen];

	AccessIPAddress			=/**/"192.168.0.100";
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
	}

	bool	Ret=(connect(&Sock,SIGNAL(readyRead()),this,SLOT(SlotReadyRead())))?true:false;


	if(Open()==true){
		GetVersion();
	}
	else{
		QMessageBox::warning(NULL,"停止"
							 ,"コントローラーと通信できません");
	}

	Transfer(0,NULL);
}
LEDControl16KDSBeltPanel::~LEDControl16KDSBeltPanel(void)
{
	delete	[]ReceivedData;
	ReceivedData=NULL;
	delete	[]TimingDim;
	TimingDim=NULL;
}



bool	LEDControl16KDSBeltPanel::Initial(bool OutputMode)
{	
	return true;
}
bool	LEDControl16KDSBeltPanel::Open(void)
{
	Sock.connectToHost(AccessIPAddress,AccessPort);
	Sock.waitForConnected(10000);
	if(Sock.state()==QAbstractSocket::ConnectedState)
		return true;
	return false;
}
bool	LEDControl16KDSBeltPanel::Close(void)
{	
	return true;
}

void	LEDControl16KDSBeltPanel::GetVersion(void)
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

void	LEDControl16KDSBeltPanel::Transfer(int PatternNumber,QProgressBar *Bar)
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

void	LEDControl16KDSBeltPanel::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqIsConnected	*CmdReqIsConnectedVar=dynamic_cast<CmdReqIsConnected *>(packet);
	if(CmdReqIsConnectedVar!=NULL){
		if(Sock.state()==QAbstractSocket::ConnectedState){
			CmdReqIsConnectedVar->Connected=true;
		}
		else{
			CmdReqIsConnectedVar->Connected=false;
		}
		return;
	}
	CmdStartSequence	*CmdStartSequenceVar=dynamic_cast<CmdStartSequence *>(packet);
	if(CmdStartSequenceVar!=NULL){
		GIOStructData.RegStartSequence=true;
		SendGio();
		return;
	}
	CmdEndSequence	*CmdEndSequenceVar=dynamic_cast<CmdEndSequence *>(packet);
	if(CmdEndSequenceVar!=NULL){
		GIOStructData.RegStartSequence=false;
		SendGio();
		return;
	}
	CmdReqEncoderPulse	*CmdReqEncoderPulseVar=dynamic_cast<CmdReqEncoderPulse *>(packet);
	if(CmdReqEncoderPulseVar!=NULL){
		RequireGio();
		CmdReqEncoderPulseVar->EncoderPulse=GIOStructData.MotorPulseCounter;
		return;
	}
}

bool	LEDControl16KDSBeltPanel::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	BYTE	Data[sizeof(GIOStructData)];
	GIOStructData.KDSBeltPIOFixedData.LineCountInFrame=NewMaxLines;
	memcpy(Data,&GIOStructData,sizeof(GIOStructData));
	int	Len=sizeof(GIOStructData);
	if(WriteRegister(-1,'F',Data,Len)==true){
		return true;
	}
	return false;
}

bool	LEDControl16KDSBeltPanel::SaveDef(QIODevice *f)
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
	
bool	LEDControl16KDSBeltPanel::LoadDef(QIODevice *f)
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

bool	LEDControl16KDSBeltPanel::Save(QIODevice *f)
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
	if(GIOStructData.Save(f)==false)
		return false;

	return true;
}
bool	LEDControl16KDSBeltPanel::Load(QIODevice *f)
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
	if(GIOStructData.Load(f)==false)
		return false;

	return true;
}

bool	LEDControl16KDSBeltPanel::SetOnOff(bool OnMode)
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
	ReEntrant=false;

	AccessHID.unlock();
	if(OnMode==true){
		WriteRegister(-1,'L',NULL,0);
	}
	else{
		WriteRegister(-1,'l',NULL,0);
	}

	return true;
}

bool	LEDControl16KDSBeltPanel::ShowSettingDialog(void)
{
	//LightForm=new LEDControl16GDialog(this);
	//bool	Ret=LightForm->exec();
	//delete LightForm;
	//LightForm=NULL;

	GIOForm=new LEDControl16KDSBeltDialog(this);
	bool	Ret=GIOForm->exec();
	delete GIOForm;
	GIOForm=NULL;

	return Ret;
}

	//Don't call directly
bool	LEDControl16KDSBeltPanel::InitialPhysical(const QString &Param)
{
	Initial(true);
	return true;
}

bool	LEDControl16KDSBeltPanel::ReflectPhysical(void)
{
	Transfer(0,NULL);
	return true;
}
bool	LEDControl16KDSBeltPanel::ReflectPhysicalTurnOn(bool LightOn)
{
	SetOnOff(LightOn);
	return true;
}

bool	LEDControl16KDSBeltPanel::WriteRegister(BYTE DipSW,BYTE Cmd ,BYTE Data[] ,unsigned short DataLen)
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
bool	LEDControl16KDSBeltPanel::ReadRegister (BYTE DipSW,BYTE Cmd ,BYTE Data[] ,unsigned short SendDataLen
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

void    LEDControl16KDSBeltPanel::SlotReadyRead()
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

bool	LEDControl16KDSBeltPanel::SendGio(void)
{
	BYTE	Data[sizeof(GIOStructData)];
	memcpy(Data,&GIOStructData,sizeof(GIOStructData));
	int	Len=sizeof(GIOStructData);
	if(WriteRegister(-1,'A',Data,Len)==true){
		return true;
	}
	return false;
}

bool	LEDControl16KDSBeltPanel::RequireGio(void)
{
	BYTE	Data[sizeof(GIOStructData)];
	int ReceivedByte;
	BYTE	RecCmd;
	unsigned long	MotorPulseCounter;
	ReadRegister (-1,'B',Data ,1,RecCmd,ReceivedByte ,sizeof(Data));
	if(RecCmd=='B' && ReceivedByte==sizeof(MotorPulseCounter)){
		memcpy(&MotorPulseCounter,Data,sizeof(MotorPulseCounter));
		GIOStructData.MotorPulseCounter=MotorPulseCounter;
		return true;
	}
	return false;
}
