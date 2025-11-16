#include "XTypeDef.h"
#include "LEDControl16G.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XHidCommand.h"
#include "LEDControl16GDialog.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"



QString	LEDControl16GPanel::DefFileName=/**/"LEDControl16GDef.dat";

//----------------------------------------------------------------
	
bool	LEDControl16GPanel::LoadDef(void)
{
	QFile	DefFile(DefFileName);
	if(DefFile.open(QIODevice::ReadOnly)==true){
		return LoadDef(&DefFile);
	}
	return false;
}
	
bool	LEDControl16GPanel::SaveDef(void)
{
	QFile	DefFile(DefFileName);
	if(DefFile.open(QIODevice::WriteOnly)==true){
		return SaveDef(&DefFile);
	}
	return false;
}

LEDControl16GPanel::LEDControl16GPanel(LayersBase *base ,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base),Sock(base->GetMainWidget())
{
	Opened=false;
	LightForm	=NULL;

	Param=LightParamStr;
	CurrentPattern	=0;

	AccessIPAddress			=/**/"Pi";
	AccessPort				=LEDControllerPort;

	LoadDef();

	QStringList	List=LightParamStr.split(QRegularExpression("[, ]"));

	if(List.count()>0){
		if(List[0].isEmpty()==false){
			AccessIPAddress=List[0];
		}
	}
	if(List.count()>1){
		if(List[1].isEmpty()==false){
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

	bool	Ret=(connect(&Sock,SIGNAL(readyRead()),this,SLOT(SlotReadyRead())))?true:false;


	if(Open()==true){
		GetVersion();
	}

	Transfer(0,NULL);
}
LEDControl16GPanel::~LEDControl16GPanel(void)
{
}



bool	LEDControl16GPanel::Initial(bool OutputMode)
{	
	return true;
}
bool	LEDControl16GPanel::Open(void)
{
	Sock.connectToHost(AccessIPAddress,AccessPort);
	Sock.waitForConnected(3000);
	if(Sock.state()==QAbstractSocket::ConnectedState)
		return true;
	return false;
}
bool	LEDControl16GPanel::Close(void)
{	
	return true;
}

void	LEDControl16GPanel::GetVersion(void)
{
	BYTE	Data[100];

	Data[0]=0;
	Data[1]=0x20;
	int ReceivedByte;
	if(ReadRegister (0,Data ,2,ReceivedByte ,sizeof(Data))==true){
		VersionStr=QString((char *)Data);
	}

	Data[0]=0;
	Data[1]=0x21;
	if(ReadRegister (0,Data ,2,ReceivedByte ,sizeof(Data))==true){
		BoardCount=Data[0];
		for(int k=0;k<BoardCount;k++){
			BoardData[k].DipSW=Data[1+k];
		}
	}
}

void	LEDControl16GPanel::Transfer(int PatternNumber,QProgressBar *Bar)
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

void	LEDControl16GPanel::TransmitDirectly(GUIDirectMessage *packet)
{

}

bool	LEDControl16GPanel::SaveDef(QIODevice *f)
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
	
bool	LEDControl16GPanel::LoadDef(QIODevice *f)
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

bool	LEDControl16GPanel::Save(QIODevice *f)
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
	return true;
}
bool	LEDControl16GPanel::Load(QIODevice *f)
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
	return true;
}

bool	LEDControl16GPanel::SetOnOff(bool OnMode)
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

bool	LEDControl16GPanel::ShowSettingDialog(void)
{
	LightForm=new LEDControl16GDialog(this);
	bool	Ret=LightForm->exec();
	delete LightForm;
	LightForm=NULL;

	return Ret;
}

	//Don't call directly
bool	LEDControl16GPanel::InitialPhysical(const QString &Param)
{
	Initial(true);
	return true;
}

bool	LEDControl16GPanel::ReflectPhysical(void)
{
	if(LightForm!=NULL){
		Transfer(0,LightForm->GetBar());
	}
	else{
		Transfer(0,NULL);
	}

	return true;
}
bool	LEDControl16GPanel::ReflectPhysicalTurnOn(bool LightOn)
{
	SetOnOff(LightOn);
	return true;
}

bool	LEDControl16GPanel::WriteRegister(int DipSW ,BYTE Data[] ,int DataLen)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	BYTE	RecData[256];
	int		ReceivedLen;

	AccessHID.lock();
	if(Sock.state()!=QAbstractSocket::ConnectedState)
		Open();
	if(Sock.state()==QAbstractSocket::ConnectedState){
	
		Sock.write((const char *)&DipSW,1);
		Sock.write((const char *)Data,DataLen);
		Sock.waitForReadyRead(2000);

		GSleep(10);
	}
	AccessHID.unlock();
	ReEntrant=false;
	return true;
}
bool	LEDControl16GPanel::ReadRegister (int DipSW ,BYTE Data[] ,int DataLen,int &ReceivedByte ,int MaxDataLen)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return false;
	ReEntrant=true;

	BYTE	TxBuff[100000];
	BYTE	RecData[256];
	int		ReceivedLen;
	bool	Ret=false;

	AccessHID.lock();
	if(Sock.state()!=QAbstractSocket::ConnectedState)
		Open();
	if(Sock.state()==QAbstractSocket::ConnectedState){

		Sock.write((const char *)&DipSW,1);
		Sock.write((const char *)Data,DataLen);

		Sock.waitForReadyRead(2000);
		if(Received==true && ReceivedData.length()>=2){
			BYTE	*fp=(BYTE *)ReceivedData.data();
			ReceivedByte	=*((int16 *)fp);
			fp+=2;
			for(int i=0;i<ReceivedByte && i<MaxDataLen;i++,fp++){
				Data[i]=*fp;
			}
			Ret=true;
		}
		GSleep(10);
	}
	AccessHID.unlock();
	ReEntrant=false;
	return Ret;
}


void	LEDControl16GPanel::SlotTimeOut()
{
}

void    LEDControl16GPanel::SlotReadyRead()
{
    if(Sock.read((char *)&ReceivedCmd,sizeof(ReceivedCmd))!=sizeof(ReceivedCmd))
        return;

	ReceivedData=Sock.readAll();
	Received=true;

}