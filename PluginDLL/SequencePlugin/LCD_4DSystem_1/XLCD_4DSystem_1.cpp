#include "qextserialport.h"
#include "XCriticalFunc.h"
#include "LCD_4DSystem_1.h"

#include <QRegularExpression>
#include <Windows.h>

LCD_4DSystem::LCD_4DSystem(ThreadComm* Owner,const QString &_Param)
{
	Motion = Owner;
	sio = NULL;
	Param = _Param;
	Recieved = false;
}
LCD_4DSystem::~LCD_4DSystem(void)
{
	delete sio;
	sio = NULL;
}

bool    LCD_4DSystem::Initial(void)
{
	if(sio==NULL){
		QStringList argList = Param.split(QChar(','));

		int	CommPort = 1;
		if(argList.count()>0){
			QRegularExpression exp("COM(\\d+)");

			if(exp.exactMatch(argList[0])==true){
				CommPort = exp.cap(1).toInt();
			}else{
				CommPort = 1;
			}
		}

		int	BPS	=9600;
		if(argList.count()>1){
			bool ok;
			int tmp = argList[1].toInt(&ok);
			if(ok==true){
				BPS = tmp;
			}
		}

		int	Character=8;
		int	Parity=0;
		int	Stopbit=1;
		QString portName;
		PortSettings portSet;

		if(CommPort==0){
			CommPort = 1;
		}

		if(CommPort<10){
			portName = QString("COM%1").arg(CommPort);
		}else{
			portName = QString("\\\\.\\COM%1").arg(CommPort);
		}

		switch(Character){
			case 5:
				portSet.DataBits=DATA_5;
				break;
			case 6:
				portSet.DataBits=DATA_6;
				break;
			case 7:
				portSet.DataBits=DATA_7;
				break;
			case 8:
				portSet.DataBits=DATA_8;
				break;
			default:
				return false;
				break;
		}
		switch(Parity){
			case 0:
				portSet.Parity=PAR_NONE;
				break;
			case 1:
				portSet.Parity=PAR_ODD;
				break;
			case 2:
				portSet.Parity=PAR_EVEN;
				break;
			default:
				return false;
				break;
		}
		switch(Stopbit){
			case 1:
				portSet.StopBits=STOP_1;
				break;
			case 2:
				portSet.StopBits=STOP_2;
				break;
			case 3:
				portSet.StopBits=STOP_1_5;
				break;
			default:
				return false;
				break;
		}
		switch(BPS){
			case 110:
				portSet.BaudRate=BAUD110;
				break;
			case 300:
				portSet.BaudRate=BAUD300;
				break;
			case 600:
				portSet.BaudRate=BAUD600;
				break;
			case 1200:
				portSet.BaudRate=BAUD1200;
				break;
			case 2400:
				portSet.BaudRate=BAUD2400;
				break;
			case 4800:
				portSet.BaudRate=BAUD4800;
				break;
			case 9600:
				portSet.BaudRate=BAUD9600;
				break;
			case 14400:
				portSet.BaudRate=BAUD14400;
				break;
			case 19200:
				portSet.BaudRate=BAUD19200;
				break;
			case 38400:
				portSet.BaudRate=BAUD38400;
				break;
			case 56000:
				portSet.BaudRate=BAUD56000;
				break;
			case 57600:
				portSet.BaudRate=BAUD57600;
				break;
			case 115200:
				portSet.BaudRate=BAUD115200;
				break;
			default:
				return false;
				break;
		}
		portSet.FlowControl = FLOW_OFF;
		portSet.Timeout_Sec = 0;
		portSet.Timeout_Millisec = 1;
		sio = new QextSerialPort(portName, portSet);
		sio->setDtr(true);
		sio->setRts(true);

		if(sio->open(QIODevice::ReadWrite)==false){
			return false;
		}

		Initialed=true;
	}

	return true;
}

void	LCD_4DSystem::Uninitialize(void)
{
	if(sio!=NULL){
		delete sio;
		sio = NULL;
	}

	Initialed = false;
}

int		LCD_4DSystem::GetChar(void)
{
	char	buff[1];
	if(sio!=NULL && sio->bytesAvailable()>0){
		sio->read(buff,1);
		return (unsigned char)buff[0];
	}
	else{
		return -1;
	}
}

void	LCD_4DSystem::SendChar(unsigned char d)
{
	//sio->write((char *)&d,sizeof(d));
	sio->putChar((char)d);
}

unsigned int	LCD_4DSystem::GetCPUMilisec(void)
{
    return GetComputerMiliSec();
}

void	LCD_4DSystem::Loop(void)
{
	unsigned char data[1024];
	if(GetRxStopless(data,sizeof(data))!=0){
		AnalizeReceivedData(data ,sizeof(data));
	}
}

int		LCD_4DSystem::GetRxStopless(unsigned char *data ,int buffsize)
{
	int d;
	int	RxNumb=0;
	
	while((d=GetChar())>=0){
		data[RxNumb]=d;
		RxNumb++;
		if(RxNumb>=buffsize){
			break;
		}
	}

	return RxNumb;
}

QByteArray derim(const QByteArray &str){
	QByteArray ary = str;
	ary.append(QChar(0x00));
	return ary;
}

void	LCD_4DSystem::AnalizeReceivedData(unsigned char *data ,int buffsize)
{
	//受信データを分析し、スタートボタンが押されていれば　Motion->ModePushedCalcStart=trueにする
	//受信データを分析し、高精度モードが押されていれば　Motion->ModePushedDetail=trueにする
	if(buffsize<1)return;

	if(data[0]=='D'){
		Motion->ModePushedCalcStart = true;
		Motion->ModePushedDetail = false;
		Motion->ModePushedLightAdjust = false;
		Motion->ModeMirrorCheck = false;
		Motion->ModePushedShutdown = false;
		sio->write(derim("A"));
	}else if(data[0]=='H'){
		Motion->ModePushedCalcStart = true;
		Motion->ModePushedDetail = true;
		Motion->ModePushedLightAdjust = false;
		Motion->ModeMirrorCheck = false;
		Motion->ModePushedShutdown = false;
		sio->write(derim("A"));
	}else if(data[0]=='S'){
		shutdown();
		Motion->ModePushedShutdown = true;
		qApp->quit();
		return;
	}else if(data[0]=='A'){
		Recieved = true;
	}else if(data[0]=='L'){
		Motion->ModePushedCalcStart = false;
		Motion->ModePushedDetail = false;
		Motion->ModePushedLightAdjust = true;
		Motion->ModeMirrorCheck = false;
		Motion->ModePushedShutdown = false;
		sio->write(derim("A"));
	}else if(data[0]=='C'){
		Motion->ModePushedCalcStart = false;
		Motion->ModePushedDetail = false;
		Motion->ModePushedLightAdjust = false;
		Motion->ModeMirrorCheck = true;
		Motion->ModePushedShutdown = false;
		sio->write(derim("A"));
	}else{
		Motion->ModePushedCalcStart = false;
		Motion->ModePushedDetail = false;
		Motion->ModePushedLightAdjust = false;
		Motion->ModeMirrorCheck = false;
		Motion->ModePushedShutdown = false;
		return;
	}
}

void	LCD_4DSystem::shutdown()
{
	StopThread();

	//QStringList args;
	//args << /**/"/s" << /**/"/hybrid" << /**/"/t" << /**/"0";
	//
	//QProcess::execute(/**/"shutdown", args);

	//HANDLE hToken;
	//TOKEN_PRIVILEGES tokenPriv;

	////アクセストークンを開く
	//OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

	////シャットダウン権限のLUIDを取得する
	//LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &(tokenPriv.Privileges[0].Luid));
	//tokenPriv.PrivilegeCount = 1;
	//tokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	////シャットダウン権限のLUIDで、シャットダウン権限を有効にする
	//AdjustTokenPrivileges(hToken, false, &tokenPriv, 0, NULL, NULL);

	////システムをシャットダウンさせる
	//ExitWindowsEx(EWX_SHUTDOWN, 0);
}

void	LCD_4DSystem::ShowPCBCount(int pcbCount)
{
	//pcbCountを計数結果として表示する
	sio->flush();
	sio->write(QString(derim("R%1")).arg(pcbCount).toLocal8Bit().data().data());
}

void	LCD_4DSystem::ShowMirrorState(bool state)
{
	// ミラー状況を送信する
	sio->flush();
	QByteArray str;
	if(state==true){
		str = derim("RT");
	}else{
		str = derim("RF");
	}
	sio->write(str);
}

void	LCD_4DSystem::ShowUnknown(void)
{
	//計数結果で不明と表示する
	SendChar('U');
}

void	LCD_4DSystem::SendBooted(void)
{
	// 起動完了の通信
	SendChar('B');
}

void	LCD_4DSystem::SendEnd(void)
{
	SendChar('F');
}

void	LCD_4DSystem::StopThread(void)
{
	Motion->stop();
}

//==============================================================

ThreadComm::ThreadComm(SeqControl *seq,const QString &Param)
{
	ModePushedCalcStart	=false;
	ModePushedDetail	=false;
	
	ModeShowPCBCount	=false;
	ModeShowUnknown		=false;
	PCBCount			=0;
	ModeShowMirrorState = false;
	MirrorState			=false;

	ModePushedLightAdjust =false;
	ModeMirrorCheck		=false;
	Initialized			=false;
	m_stop = false;
	m_isStopped = true;

	Motioner=new LCD_4DSystem(this,Param);
}

bool	ThreadComm::IsCalcStartPushed(void)
{
	return ModePushedCalcStart;
}

bool	ThreadComm::IsDetailButtonPushed(void)
{
	return ModePushedDetail;
}

bool	ThreadComm::IsLightAdjustPushed(void)
{
	return ModePushedLightAdjust;
}

bool	ThreadComm::IsMirrorCheckPushed(void)
{
	return ModeMirrorCheck;
}

void	ThreadComm::uninitialize(void)
{
	Motioner->Uninitialize();
}

void	ThreadComm::ShowPCBCount(int pcbCount)
{
	if(ModeShowPCBCount==true){
		msleep(10);
	}
	//Motioner->ShowPCBCount(pcbCount);
	PCBCount=pcbCount;
	ModeShowPCBCount=true;
	ModeShowUnknown=false;
	ModeShowMirrorState=false;

	while(ModeShowPCBCount==true)
		msleep(1);
}

void	ThreadComm::ShowUnknown(void)
{
	if(ModeShowUnknown==true){
		msleep(10);
	}
	//Motioner->ShowUnknown();
	ModeShowPCBCount=false;
	ModeShowUnknown=true;
	ModeShowMirrorState=false;

	while(ModeShowUnknown==true)
		msleep(1);
}

void	ThreadComm::ShowMirrorState(bool state)
{
	if(ModeShowMirrorState==true){
		msleep(10);
	}
	MirrorState = state;
	//Motioner->ShowMirrorState(state);
	ModeShowPCBCount=false;
	ModeShowUnknown=false;
	ModeShowMirrorState=true;

	while(ModeShowMirrorState==true)
		msleep(1);
}

void	ThreadComm::SendBooted(void)
{
	Motioner->SendBooted();
}

void	ThreadComm::SendEnd(void)
{
	Motioner->SendEnd();
}

void	ThreadComm::run()
{
	Motioner->Initial();
	Initialized=true;
	m_stop = false;
	m_isStopped = false;
	while(m_stop==false){
		msleep(10);
		Motioner->Loop();

		if(ModeShowPCBCount==true){
			Motioner->ShowPCBCount(PCBCount);
			ModeShowPCBCount=false;
		}
		if(ModeShowUnknown==true){
			Motioner->ShowUnknown();
			ModeShowUnknown=false;
		}
		if(ModeShowMirrorState==true){
			Motioner->ShowMirrorState(MirrorState);
			ModeShowMirrorState=false;
		}
	}
	m_isStopped = true;
}