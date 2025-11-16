#include "NetworkSIOServer.h"
#include "XNetworkSIOCommon.h"
#include <QThread>

class	TmpThread : public QThread
{
public:
	void run (){}

	static	void	TmpGSleep(unsigned int milisec){	msleep(milisec);	}
};


void	GSleep(unsigned int milisec)
{
	TmpThread::TmpGSleep(milisec);
}

NetworkSIOServer::NetworkSIOServer(int ComPort ,int PortNumber ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	sio					=NULL;
	SIOInfo.BaudRate	=9600;
	SIOInfo.Character	=8;
	SIOInfo.Parity		=0;
	SIOInfo.StopBit		=1;

	Server.listen(QHostAddress::Any,PortNumber);
	connect(this,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));

	Timer.setSingleShot(false);
	Timer.setInterval(100);
	connect(&Timer,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
	Timer.start();

	ui.comboBoxCOM	->setCurrentIndex(ComPort);
}

NetworkSIOServer::~NetworkSIOServer()
{
	if(sio!=NULL){
		delete	sio;
		sio=NULL;
	}
}

void NetworkSIOServer::on_pushButtonReOpen_clicked()
{
	ComPort=ui.comboBoxCOM->currentIndex();
	OpenPort();
}

void NetworkSIOServer::SlotNewConnection ()
{
	QTcpSocket *p=Server.nextPendingConnection ();
	SocketInServer	*a=new SocketInServer(this,p);
	a->HandleNumber	=SocketContainer.GetCount();
	SocketContainer.AppendList(a);
}

void	NetworkSIOServer::SlotTimeout()
{
}

bool	NetworkSIOServer::OpenPort(void)
{
	if (sio != NULL && sio->isOpen() == false) {
		delete	sio;
		sio = NULL;
	}
	if (sio == NULL) {
		char* portName;
		sio = new QSerialPort();
		/*POSIX(Linux) CODE*/
#ifdef _TTY_POSIX_
		switch (CommPort) {
		case 0:
			portName = "/dev/ttyS0";
			break;
		case 1:
			portName = "/dev/ttyS0";
			break;
		case 2:
			portName = "/dev/ttyS1";
			break;
		case 3:
			portName = "/dev/ttyS2";
			break;
		case 4:
			portName = "/dev/ttyS3";
			break;
		case 5:
			portName = "/dev/ttyS4";
			break;
		case 6:
			portName = "/dev/ttyS5";
			break;
		case 7:
			portName = "/dev/ttyS6";
			break;
		case 8:
			portName = "/dev/ttyS7";
			break;
		case 9:
			portName = "/dev/ttyS8";
			break;
		case 10:
			portName = "/dev/ttyS9";
			break;
		}
		/*MS WINDOWS CODE*/
#else
		switch (ComPort) {
		case 0:
			portName = "COM1";
			break;
		case 1:
			portName = "COM1";
			break;
		case 2:
			portName = "COM2";
			break;
		case 3:
			portName = "COM3";
			break;
		case 4:
			portName = "COM4";
			break;
		case 5:
			portName = "COM5";
			break;
		case 6:
			portName = "COM6";
			break;
		case 7:
			portName = "COM7";
			break;
		case 8:
			portName = "COM8";
			break;
		case 9:
			portName = "COM9";
			break;
		case 10:
			portName = "\\\\.\\COM10";
			break;
		case 11:
			portName = "\\\\.\\COM11";
			break;
		case 12:
			portName = "\\\\.\\COM12";
			break;
		case 13:
			portName = "\\\\.\\COM13";
			break;
		case 14:
			portName = "\\\\.\\COM14";
			break;
		case 15:
			portName = "\\\\.\\COM15";
			break;
		case 16:
			portName = "\\\\.\\COM16";
			break;
		}
#endif
		sio->setPortName(QString(portName));

		switch (SIOInfo.Character) {
		case 5:
			sio->setDataBits(QSerialPort::Data5);
			break;
		case 6:
			sio->setDataBits(QSerialPort::Data6);
			break;
		case 7:
			sio->setDataBits(QSerialPort::Data7);
			break;
		case 8:
			sio->setDataBits(QSerialPort::Data8);
			break;
		}
		switch (SIOInfo.Parity) {
		case 0:
			sio->setParity(QSerialPort::NoParity);
			break;
		case 1:
			sio->setParity(QSerialPort::OddParity);
			break;
		case 2:
			sio->setParity(QSerialPort::EvenParity);
			break;
		}
		switch (SIOInfo.StopBit) {
		case 1:
			sio->setStopBits(QSerialPort::OneStop);
			break;
		case 2:
			sio->setStopBits(QSerialPort::TwoStop);
			break;
		case 3:
			sio->setStopBits(QSerialPort::OneAndHalfStop);
			break;
		}
		sio->setBaudRate(SIOInfo.BaudRate);

		sio->setFlowControl(QSerialPort::NoFlowControl);
		//portSet.Timeout_Sec=0;	//1;
		//portSet.Timeout_Millisec=1;
		//sio->setDtr(true);
		//sio->setRts(true);

		sio->open(QIODevice::ReadWrite);

	}

	return true;
}
//===================================================================================

SocketInServer::SocketInServer(NetworkSIOServer *parent,QTcpSocket *sv)
	:SoESocket(parent,sv),Parent(parent)
{
	if(sv!=NULL){
		ClientIP		=sv->peerAddress ().toString();
		ClientPortNumber=sv->peerPort();
	}
	else{
		ClientIP			=/**/"DirectAccess";
		ClientPortNumber	=-1;
	}
}

void	SocketInServer::Received(int cmd ,QByteArray &data)
{
	if(cmd==CmdComm_Open){
		struct	CommOpenInfo	Data;

		QBuffer	Buff(&data);
		Buff.open(QIODevice::ReadOnly);
		if(Buff.read((char *)&Data,sizeof(Data))==sizeof(Data)){
			Parent->SIOInfo=Data;
			if(Parent->OpenPort()==true){
				QByteArray	Array;
				Send(CmdComm_Ack_OK ,Array);
			}
			else{
				QByteArray	Array;
				Send(CmdComm_Ack_NG ,Array);
			}
		}
		else{
			QByteArray	Array;
			Send(CmdComm_Ack_NG ,Array);
		}
	}
	else if(cmd==CmdComm_Tx){
		int	Count=data.count();
		char	*fp=data.data();
		for(int i=0;i<Count;i++){
			Parent->sio->write(fp,1);
			Parent->sio->flush();
		}
		QByteArray	Array;
		Send(CmdComm_Ack_OK ,Array);
	}
	else if(cmd==CmdComm_Rx){
		int	Count=data.count();
		char	*fp=data.data();
		if(Count>=sizeof(int32)){
			int	MaxRxLen=*((int32 *)fp);
			char	*Buff=new char[MaxRxLen];
			int		RxLen;
			for(RxLen=0;Parent->sio->bytesAvailable()>0 && RxLen<MaxRxLen;RxLen++){
				if(Parent->sio->read(&Buff[RxLen],1)!=1)
					break;
			}
			QByteArray	Array(Buff,RxLen);
			Send(CmdComm_Ack_Received ,Array);
		}
		else{
			QByteArray	Array;
			Send(CmdComm_Ack_NG ,Array);
		}
	}
	else if(cmd==CmdComm_RxByte){
		int	Count=Parent->sio->bytesAvailable();
			
		QByteArray	Array((char *)&Count,sizeof(Count));
		Send(CmdComm_Ack_RxByte ,Array);
	}
}

void	SocketInServer::SlotDisconnected()
{
	Parent->SocketContainer.RemoveList(this);
	SoESocket::SlotDisconnected();
	deleteLater();
}
