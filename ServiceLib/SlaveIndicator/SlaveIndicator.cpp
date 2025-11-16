#include "SlaveIndicatorResource.h"
#include "SlaveIndicator.h"
#include "XSlaveIndicator.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include <QFile>
#include <QMenu>

SocketList::SocketList(SlaveIndicator *parent)
:Parent(parent)
{
	ID	=-1;
	Sock=NULL;
	Received=false;
}

void	SocketList::SetFromServer(QTcpSocket *sock)
{
	Sock=sock;
	connect(Sock,SIGNAL(readyRead())	,this,SLOT(SlotReadyRead()));
	connect(Sock,SIGNAL(disconnected())	,this,SLOT(SlotDisconnected()));
}


void	SocketList::SlotReadyRead()
{
	LastTime=GetComputerMiliSec();
	int	N=Sock->bytesAvailable();
	struct	SlaveInfo	RxData;
	if(N>=sizeof(RxData)){
		char	d;
		Sock->read((char *)&d,1);
		if(d==1){
			Sock->read((char *)&RxData,sizeof(RxData));
			ID			=RxData.GlobalPage;
			MachineID	=RxData.MachineID;
			::Load(Sock,ComputerName);
			Received=true;
		}
	}
}

void	SocketList::SlotDisconnected()
{
	for(SocketList *s=Parent->Slaves.GetFirst();s!=NULL;s=s->GetNext()){
		if(s==this){
			Parent->Slaves.RemoveList(s);
			deleteLater();
		}
	}
}
	
void	SocketList::SendRebootCommand(void)
{
	if(Sock!=NULL && Sock->isOpen()==true){
		char	d=10;
		Sock->write((const char *)&d,1);
		Sock->flush();
	}
}

bool	SocketList::IsSlaveAlive(void)
{
	if(Sock!=NULL && Sock->isOpen()==true){
		Received=false;
		char	d=12;
		Sock->write((const char *)&d,1);
		Sock->flush();
		Sock->waitForReadyRead(2000);
		if(Received==true)
			return true;
	}
	return false;
}

//============================================================================

ColorFrameWithClick::ColorFrameWithClick(int number ,QWidget * parent, Qt::WindowFlags f)
	:mtColorFrame(parent,f)
{
	Number=number;
	//grabMouse();
}

void	ColorFrameWithClick::mousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::RightButton){
		SlaveIndicator	*p=dynamic_cast<SlaveIndicator *>(parent());
		if(p!=NULL && p->GetSlaveState(Number)==true){
			QMenu	Menu(this);
			Menu.addAction (LangSolver.GetString(SlaveIndicator_LS,LID_3)/*"Reboot program"*/, this, SLOT(SlotReboot()));
			Menu.addAction (LangSolver.GetString(SlaveIndicator_LS,LID_4)/*"Check"*/			, this, SLOT(SlotCheck()));
			Menu.addSeparator();
			Menu.addAction (LangSolver.GetString(SlaveIndicator_LS,LID_5)/*"Reboot all"*/	, this, SLOT(SlotRebootAll()));

			QPoint	Q=mapToGlobal(QPoint(10,10));
			Menu.exec(Q);
		}
	}
}

void	ColorFrameWithClick::SlotReboot()
{
	SlaveIndicator	*p=dynamic_cast<SlaveIndicator *>(parent());
	if(p!=NULL){
		p->SlaveReboot(Number);
	}
}
void	ColorFrameWithClick::SlotCheck()
{
	SlaveIndicator	*p=dynamic_cast<SlaveIndicator *>(parent());
	if(p!=NULL){
		p->SlaveCheck(Number);
	}
}
void	ColorFrameWithClick::SlotRebootAll()
{
	SlaveIndicator	*p=dynamic_cast<SlaveIndicator *>(parent());
	if(p!=NULL){
		p->RebootAllSlaves();
	}
}


//============================================================================

SlaveIndicator::SlaveLine::SlaveLine(int n,SlaveIndicator *parent)
	:Frame(n,parent)
{
	Number=n;
	//Frame.setParent(parent);
	Frame.setGeometry(0,n*16,15,15);
	Label.setParent(parent);
	Label.setGeometry(16,n*16,80,15);
	Label.setText(/**/LangSolver.GetString(SlaveIndicator_LS,LID_0)/*"Slave"*/+QString::number(n+1));
	Show(false,0,0,/**/"");
}
void	SlaveIndicator::SlaveLine::Show(bool state ,int MachineID ,int ID ,const QString &ComputerName)
{
	State=state;
	if(state==true){
		if(ComputerName.isEmpty()==true){
			Label.setText(LangSolver.GetString(SlaveIndicator_LS,LID_1)/*"MAC"*/
						+QString::number(MachineID)
						+QString(/**/" ")
						+LangSolver.GetString(SlaveIndicator_LS,LID_2)/*" Slave"*/
						+QString::number(ID));
		}
		else{
			Label.setText(ComputerName);
		}
		Frame.SetColor(Qt::green);
	}
	else{
		Label.setText(/**/"");
		Frame.SetColor(Qt::gray);
	}
}

//============================================================================

SlaveIndicator::SlaveIndicator(int _SlaveCount ,QWidget *parent, Qt::WindowFlags flags)
: QMainWindow(parent, flags | Qt::WindowStaysOnTopHint)
{
	ui.setupUi(this);
	setWindowFlags(Qt::WindowTitleHint);
	SlaveCount=_SlaveCount;

	Server.setParent(this);
	connect(&Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
	Server.listen(QHostAddress::Any,SlaveIndicatorPort);
	TM.setInterval(SlaveIndicatorInterval);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()),Qt::QueuedConnection);
	TM.start();
	SetSlaveCount(SlaveCount);

	QString	FileName=GetPositionFileName();
	QFile	F(FileName);
	if(F.open(QIODevice::ReadOnly)==true){
		int	PosX,PosY;
		if(::Load(&F,PosX)==true){
			if(::Load(&F,PosY)==true){
				//move(PosX,PosY);
				setGeometry(PosX,PosY,width(),height());
			}
		}
	}
}

SlaveIndicator::~SlaveIndicator()
{
}

void SlaveIndicator::moveEvent ( QMoveEvent * event )
{
	QString	FileName=GetPositionFileName();
	QFile	F(FileName);
	if(F.open(QIODevice::WriteOnly)==true){
		int	PosX=geometry().left();
		int	PosY=geometry().top();
		if(::Save(&F,PosX)==false){
			return;
		}
		if(::Save(&F,PosY)==false){
			return;
		}
	}
}

QString	SlaveIndicator::GetPositionFileName(void)
{
	return QString(/**/"SlaveIndicator.dat");
}

void	SlaveIndicator::SlotNewConnection ()
{
	SocketList	*s=new SocketList(this);
	s->SetFromServer(Server.nextPendingConnection());
	Slaves.AppendList(s);
}

void	SlaveIndicator::SetSlaveCount(int n)
{
	SlaveLines.RemoveAll();
	SlaveCount=n;
	for(int i=0;i<SlaveCount;i++){
		SlaveLine	*p=new SlaveLine(i,this);
		SlaveLines.AppendList(p);
	}
	resize(70,SlaveCount*16+2);
}


void	SlaveIndicator::Show(void)
{
	HNext:;
	for(SocketList *d=Slaves.GetFirst();d!=NULL;d=d->GetNext()){
		SocketList *e=d->GetNext();
		if(e!=NULL){
			if(d->ComputerName==e->ComputerName){
				Slaves.RemoveList(d);
				delete	d;
				goto	HNext;
			}
		}
	}

	for(SocketList *d=Slaves.GetFirst();d!=NULL;d=d->GetNext()){
		d->Shown=false;
	}
	int	MaxMachineID=100;
	int	N=Slaves.GetCount();
	for(int i=0;i<SlaveCount;i++){
		SlaveLine	*L=SlaveLines[i];
		if(L!=NULL){
			SocketList *MinD=NULL;
			int	MinID=9999999;
			int	MinMac=99999999;
			QString	ComputerName;
			for(SocketList *d=Slaves.GetFirst();d!=NULL;d=d->GetNext()){
				if(d->Shown==false){
					if(MinMac>d->MachineID){
						MinMac		=d->MachineID;
						ComputerName=d->ComputerName;
						MinID		=d->ID;
						MinD		=d;
					}
					else if(MinMac==d->MachineID){
						if(MinID>d->ID){
							MinID		=d->ID;
							ComputerName=d->ComputerName;
							MinD		=d;
						}
					}
				}
			}
			if(MinD!=NULL){
				MinD->Shown=true;
				L->Show(true,MinMac,MinID,ComputerName);
			}
			else{
				L->Show(false,99,0,/**/"");
			}
		}
	}
}

void	SlaveIndicator::SlotTimeout()
{
	Show();
}
bool	SlaveIndicator::GetSlaveState(int number)
{
	for(SlaveLine *s=SlaveLines.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->GetNumber()==number){
			return s->GetState();
		}
	}
	return false;
}
void	SlaveIndicator::SlaveReboot(int number)
{
	for(SocketList *d=Slaves.GetFirst();d!=NULL;d=d->GetNext()){
		if(d->Shown==true && d->ID==number){
			d->SendRebootCommand();
		}
	}
}

void	SlaveIndicator::SlaveCheck(int number)
{
	ReTry:;
	for(SocketList *d=Slaves.GetFirst();d!=NULL;d=d->GetNext()){
		if(d->ID==number){
			if(d->Shown==true && d->IsSlaveAlive()==false){
				Slaves.RemoveList(d);
				d->deleteLater();
				goto	ReTry;
			}
		}
	}
	Show();
}

void	SlaveIndicator::RebootAllSlaves(void)
{
	for(SocketList *d=Slaves.GetFirst();d!=NULL;d=d->GetNext()){
		d->SendRebootCommand();
	}
}