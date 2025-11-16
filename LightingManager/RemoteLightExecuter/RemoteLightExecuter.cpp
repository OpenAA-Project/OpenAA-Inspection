#include "RemoteLightExecuterResource.h"
#include "RemoteLightExecuter.h"
#include "XRemoteLightCommon.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "XLightClass.h"
#include "XRemoteLightCommon.h"
#include <QIODevice>

RemoteLightSocket::RemoteLightSocket(LayersBase *Base ,RemoteLightExecuter *parent)
	:ServiceForLayers(Base)
{
	Parent=parent;
	connect(this,SIGNAL(SignalReceived(int)),this,SLOT(SlotReceived(int)),Qt::QueuedConnection);
}

void	RemoteLightSocket::SlotReceived(int id)
{
	RecList	*R=UnpackTopRxBuff();
	if(R!=NULL){
		BYTE	*p=R->GetPointer();
		QBuffer ret;
		p=R->GetPointer(p ,ret);
		ret.open(QIODevice::ReadWrite);
		int32	Cmd;
		::Load(&ret,Cmd);
		if(Cmd==CmdInitialAfterLoad){
			QString	InitialStr;
			if(::Load(&ret,InitialStr)==false)
				goto	NextPoint;
			//Parent->SetInitialStrAfterOpen(InitialStr);
		}
		else if(Cmd==CmdLightOnOff){
			bool	OnMode;
			if(::Load(&ret,OnMode)==false)
				goto	NextPoint;
			if(OnMode==true)
				Parent->LightPointer->LightOn();
			else
				Parent->LightPointer->LightOff();
		}
		else if(Cmd==CmdLightSetData){
			Parent->LightPointer->Load(&ret);
			if(Parent->LightPointer->GetHandle()!=NULL){
				Parent->LightPointer->GetHandle()->ReflectPhysical();
			}
		}
		else if(Cmd==CmdLightReqData){
			QBuffer		Buff;
			Buff.open(QIODevice::WriteOnly);
			int	AckCmd=CmdLightAckData;
			if(::Save(&Buff,AckCmd)==false)
				goto	NextPoint;
			if(Parent->LightPointer->Save(&Buff)==false)
				goto	NextPoint;

			QByteArray	Data=Buff.buffer();
			TxData(&Data);
		}
		else if(Cmd==CmdLightSendCommand){
			int32	DataLen;
			if(::Load(&ret,DataLen)==false)
				goto	NextPoint;
			BYTE	*Data=new BYTE[DataLen];
			ret.read((char *)Data,DataLen);
			CmdSendRequestLight	RCmd(GetLayersBase());
			RCmd.BytesOfAnyData	=DataLen;
			RCmd.AnyData		=Data;
			Parent->LightPointer->TransmitDirectly(&RCmd);
			delete	[]Data;
		}
NextPoint:;
		delete	R;
	}
}
RemoteLightServer::RemoteLightServer(LayersBase *Base ,QObject * parent)
	:SocketServer(parent),ServiceForLayers(Base)
{}
SocketClient	*RemoteLightServer::NewSocket(void)
{
	RemoteLightExecuter	*p=dynamic_cast<RemoteLightExecuter *>(parent());
	return new RemoteLightSocket(GetLayersBase(),p);
}

//--------------------------------------------------------------------------------

RemoteLightExecuter::RemoteLightExecuter(LayersBase *Base 
										,const QString &DLLFileName ,int PortNumber ,QString &InitialStr
										,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,ServiceForLayers(Base)
	,SockerServer(Base,this)
{
	ui.setupUi(this);

	SockerServer.StartServer(PortNumber);

	minimizeAction	=new QAction(LangSolver.GetString(RemoteLightExecuter_LS,LID_0)/*"Minimize"*/,this);
	connect(minimizeAction	,SIGNAL(triggered()),this,SLOT(hide()));
	showAction		=new QAction(DLLFileName+QString(/**/"-")+QString::number(PortNumber),this);
	connect(showAction		,SIGNAL(triggered()),this,SLOT(showNormal()));
	DialogAction		=new QAction(QString(/**/"Show dialog"),this);
	connect(DialogAction		,SIGNAL(triggered()),this,SLOT(SlotShowDialog()));
	quitAction		=new QAction(LangSolver.GetString(RemoteLightExecuter_LS,LID_1)/*"quit"*/,this);
	connect(quitAction		,SIGNAL(triggered()),qApp,SLOT(quit()));

	TrayIconMenu=new QMenu(this);
	TrayIconMenu->addAction(minimizeAction);
	TrayIconMenu->addAction(showAction);
	TrayIconMenu->addAction(DialogAction);
	TrayIconMenu->addAction(quitAction);

	TrayIcon	=new QSystemTrayIcon(this);
	TrayIcon->setContextMenu(TrayIconMenu);
	TrayIcon->setIcon(QIcon(QPixmap(/**/":Resources/RemoteLightExecuter.png")));
	TrayIcon->show();

	LightPointer=new LightAccessList(GetLayersBase());
	DLLPathName=DLLFileName;
	int32 ErrorCode;
	bool	InitialState=LightPointer->InitialStraightPath(DLLPathName,InitialStr,ErrorCode ,true);
	if(LightPointer->GetHandle()!=NULL && InitialState==true){
		if(LightPointer->GetHandle()->InitialPhysical(InitialStr)==false)
			InitialState=false;
	}

	ui.lineEditPortNumber	->setText(QString::number(PortNumber));
	ui.lineEditFileName		->setText(DLLFileName);

	if(InitialState==true){
		QPalette	P=ui.lineEditFileName->palette();
		P.setColor(QPalette::Base,Qt::cyan);
		ui.lineEditFileName->setPalette(P);
	}
	else{
		QPalette	P=ui.lineEditFileName->palette();
		P.setColor(QPalette::Base,Qt::red);
		ui.lineEditFileName->setPalette(P);
	}

	QString	FileName=GetPositionFileName();
	QFile	F(FileName);
	if(F.open(QIODevice::ReadOnly)==true){
		int	PosX,PosY,W,H;
		if(::Load(&F,PosX)==true){
			if(::Load(&F,PosY)==true){
				if(::Load(&F,W)==true){
					if(::Load(&F,H)==true){
						//move(PosX,PosY);
						setGeometry(PosX,PosY,W,H);
					}
				}
			}
		}
	}
	TM.setInterval(2000);
	TM.setSingleShot(true);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}

RemoteLightExecuter::~RemoteLightExecuter()
{
	delete	LightPointer;
}

void RemoteLightExecuter::moveEvent ( QMoveEvent * event )
{
	SavePosition();
}
void RemoteLightExecuter::resizeEvent ( QResizeEvent * event )
{
	SavePosition();
}

void RemoteLightExecuter::SavePosition(void)
{
	QString	FileName=GetPositionFileName();
	QFile	F(FileName);
	if(F.open(QIODevice::WriteOnly)==true){
		int32	PosX=geometry().left();
		int32	PosY=geometry().top();
		int32	W=geometry().width();
		int32	H=geometry().height();
		if(::Save(&F,PosX)==false){
			return;
		}
		if(::Save(&F,PosY)==false){
			return;
		}
		if(::Save(&F,W)==false){
			return;
		}
		if(::Save(&F,H)==false){
			return;
		}
	}
}

void	RemoteLightExecuter::SlotTimeOut()
{
	hide();
}
void	RemoteLightExecuter::closeEvent(QCloseEvent *ev)
{
	if(TrayIcon->isVisible()==true){
		hide();
		ev->ignore();
	}
}
void	RemoteLightExecuter::SlotShowDialog()
{
	LightPointer->ShowSetting(NULL);
}

