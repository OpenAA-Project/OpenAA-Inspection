#include "Booter.h"
#include "XGeneralFunc.h"
#include <QBuffer>
#include "SettingDialog.h"
#include <QMessageBox>

ConnectionList::ConnectionList(QObject *parent)
	:SocketClient(parent)
{	
	PortNumber	=29100;
	connect(this,SIGNAL(SignalReceived(int)),this,SLOT(SlotReceived(int)),Qt::QueuedConnection);
}

bool	ConnectionList::Save(QIODevice *f)
{
	if(::Save(f,AccessName)==false)
		return false;
	if(::Save(f,IPAddress)==false)
		return false;
	if(::Save(f,PortNumber)==false)
		return false;
	return true;
}
bool	ConnectionList::Load(QIODevice *f)
{
	if(::Load(f,AccessName)==false)
		return false;
	if(::Load(f,IPAddress)==false)
		return false;
	if(::Load(f,PortNumber)==false)
		return false;
	return true;
}

bool	ConnectionList::OpenConnection(void)
{
	if(IsConnected()==false){
		Set(parent(),IPAddress,PortNumber);
		if(StartConnect()==true){
			return true;
		}
	}
	else{
		return true;
	}
	return false;
}
bool	ConnectionList::IsOpenConnection(void)
{
	if(IsConnected()==true){
		return true;
	}
	return false;
}
bool	ConnectionList::SendOK(void)
{
	if(IsConnected()==true){
		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
	
		BYTE	Cmd=CmdOK;
		if(::Save(&Buff,Cmd)==false)
			return false;
		if(TxData(&Buff)==true){
			return true;
		}
	}
	return false;
}

void	ConnectionList::SlotReceived(int id)
{
	RecList	*R=UnpackTopRxBuff();
	if(R!=NULL){
		BYTE	*p=R->GetPointer();
		QBuffer ret;
		p=R->GetPointer(p ,ret);
		ret.open(QIODevice::ReadWrite);
		BYTE	Cmd=0;
		::Load(&ret,Cmd);
		if(Cmd==CmdOK){
			QObject	*p=parent();
			Booter	*PL=dynamic_cast<Booter *>(p);
			if(PL!=NULL){
				PL->close();
			}
		}
		delete	R;
	}
}


bool	ConnectionContainer::Save(QIODevice *f)
{
	int32	N=GetCount();

	if(::Save(f,N)==false){
		return false;
	}
	for(SocketClient *c=GetFirst();c!=NULL;c=c->GetNext()){
		ConnectionList	*CL=dynamic_cast<ConnectionList *>(c);
		if(CL!=NULL){
			if(CL->Save(f)==false){
				return false;
			}
		}
	}
	return true;
}

bool	ConnectionContainer::Load(QIODevice *f)
{
	int32	N;

	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ConnectionList *c=new ConnectionList(Parent);
		if(c->Load(f)==false){
			return false;
		}
		AppendList(c);
	}
	return true;
}

//===================================================

Booter::Booter(const QString &settingFile ,int OpePort ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags) ,Server(this),Connections(this)
{
	ui.setupUi(this);
	Server.StartServer(OpePort);

	SettingFileName=settingFile;
	QFile	file(SettingFileName);
	if(file.open(QIODevice::ReadOnly)==true){
		Connections.Load(&file);
	}
}

Booter::~Booter()
{

}

void Booter::on_pushButtonOK_clicked()
{
	QStringList	ErrorList;
	for(SocketClient *c=Connections.GetFirst();c!=NULL;c=c->GetNext()){
		ConnectionList	*CL=dynamic_cast<ConnectionList *>(c);
		if(CL!=NULL){
			if(CL->OpenConnection()==false){
				ErrorList.append(CL->AccessName);
			}
		}
	}
	if(ErrorList.count()!=0){
		QString	Msg;
		for(int i=0;i<ErrorList.count();i++){
			Msg+=ErrorList[i];
			if((i+1)<ErrorList.count()){
				Msg+=QString(",");
			}
		}
		Msg += QString(" : not connected. OK?");
		if(QMessageBox::warning(NULL,"Not connected",Msg,QMessageBox::Yes,QMessageBox::No)==QMessageBox::No)
			return;
	}
	for(SocketClient *c=Connections.GetFirst();c!=NULL;c=c->GetNext()){
		ConnectionList	*CL=dynamic_cast<ConnectionList *>(c);
		if(CL!=NULL){
			if(CL->IsOpenConnection()==true){
				CL->SendOK();
			}
		}
	}
	close();
}

void Booter::on_pushButtonSetting_clicked()
{
	SettingDialog	D(BooterData);
	if(D.exec()==(int)true){
		BooterData	=D.BooterData;
	}
}
