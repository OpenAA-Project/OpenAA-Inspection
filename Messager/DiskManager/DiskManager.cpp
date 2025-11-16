#include "DiskManager.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XDIskInfoCommon.h"
#include "SelectFileOperationDialog.h"
#include <QMessageBox>

const	char	*MessagerRegFile=/**/"DiskManager.dat";
extern	QString	LogHeaderFileName;

MRecList::MRecList(int len)
{
	Len=len;
	if(Len!=0){
		Data=new BYTE[Len];
	}
	else{
		Data=NULL;
	}
}

MRecList::~MRecList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}

BYTE	*MRecList::GetPointer(BYTE *p ,QByteArray &ret)
{
	if(p==NULL){
		p=Data;
	}
	QBuffer	Buff;
	Buff.setData((const char *)p,Len);
	Buff.open(QIODevice::ReadOnly);
	ret=Buff.readAll();
	p+=ret.size();
	return(p);
}

SourcePCSocket::SourcePCSocket(DiskManager *parent ,QTcpSocket *s)
{
	Sock=s;
	Parent=parent;

	LastReceivingTime=0;
	NowOnPoint		=0;
	RxState=_NowOnWaiting;
	LastPacketLoadedSize=0;
	FastCommLeafRxReEntrant=0;
	PctLen			=0;
	LastPacketLoadedSize	=0;
	OnRBuff			=NULL;
}
void	SourcePCSocket::Set(void)
{
	connect(Sock,SIGNAL(readyRead())	 ,this,SLOT(SlotReadyRead()));
	connect(Sock,SIGNAL(disconnected())	 ,this ,SLOT(SlotDisconnected()));
	connect(this,SIGNAL(SignalReceived()),this,SLOT(SlotReceived()));
}

bool	SourcePCSocket::Send(QByteArray &data)
{
	if(Sock->state()==QAbstractSocket::ConnectedState){
		int32	Len=data.size();
		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}
		if(Sock->write((const char *)&Len,sizeof(Len))!=sizeof(Len)){
			return false;
		}
		if(Sock->write(data)<=0){
			return false;
		}
		Sock->flush();
		return true;
	}
	return false;
}
void	SourcePCSocket::SlotReadyRead()
{
	FastCommLeafRxReEntrant++;
	do{
		if(RxState==_NowOnWaiting || (RxState==_NowOnReceiving && (time(NULL)-LastReceivingTime>5))){
			int Len=Sock->read(((char *)&PctLen)+LastPacketLoadedSize, sizeof(PctLen)-LastPacketLoadedSize);
			if(Len<0){
				FastCommLeafRxReEntrant--;
				return;
			}
			if(Len+LastPacketLoadedSize!=sizeof(PctLen)){
				LastPacketLoadedSize+=Len;
				FastCommLeafRxReEntrant--;
				return;
			}
			LastPacketLoadedSize=0;
			NowOnXByte	=PctLen	;

			if(OnRBuff!=NULL){
				delete	OnRBuff;
			}
			OnRBuff=new MRecList(NowOnXByte);
			NowOnPoint=0;
		
			int	N=Sock->bytesAvailable();
			if(N!=0){
				if(NowOnXByte>=N){
					Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), N);
					if(Len<0){
						FastCommLeafRxReEntrant--;
						return;
					}
					NowOnPoint+=Len;
				}
				else if(NowOnXByte!=0){
					Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), NowOnXByte);
					if(Len<0){
						FastCommLeafRxReEntrant--;
						return;
					}
					NowOnPoint+=Len;
				}
			}
			RxState=_NowOnReceiving;
		}
		else{
			int	N=Sock->bytesAvailable();
			int	RByte=min(OnRBuff->Len-NowOnPoint,N);
			int	Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint),RByte);
			//int	Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), N);
			if(Len<0){
				FastCommLeafRxReEntrant--;
				return;
			}
			NowOnPoint+=Len;
		}

		LastReceivingTime=time(NULL);
		if(NowOnXByte<=NowOnPoint){
			RxState=_NowOnWaiting;
			MuteRecData.lock();
			RecData.AppendList(OnRBuff);
			OnRBuff=NULL;
			MuteRecData.unlock();
			emit	SignalReceived();
		}
	}while(Sock->bytesAvailable()!=0);
	FastCommLeafRxReEntrant--;
}

void	SourcePCSocket::SlotReceived()
{
	MRecList	*r=UnpackTopRxBuff();
	if(r!=NULL){
		QByteArray	ByteArray;
		BYTE	*p=r->GetPointer();
		r->GetPointer(p,ByteArray);
		delete	r;

		QBuffer	ABuff(&ByteArray);
		ABuff.open(QIODevice::ReadOnly);

		int	TypeValue;
		if(::Load(&ABuff,TypeValue)==false)
			return;
		int	GlobalPage;
		if(::Load(&ABuff,GlobalPage)==false)
			return;	
		QString	MessageStr;
		if(::Load(&ABuff,MessageStr)==false)
			return;
		QByteArray	Data;
		if(::Load(&ABuff,Data)==false)
			return;

		if(TypeValue==4){
			int	n1=MessageStr.indexOf(/**/"(");
			int	n2=MessageStr.indexOf(/**/")");
			int	n3=MessageStr.indexOf(/**/"=");
			if(n1>=0 && n2>=0 && n3>=3){
				QString	ComputerName=MessageStr.left(n1);
				QString	Path		=MessageStr.mid(n1+1,n2-n1-1);
				QString	Space		=MessageStr.mid(n3+1);
					
				QString	DiskUnit;
				int	n4=99;
				if((n4=Space.indexOf(/**/"GB"))>=0){
					DiskUnit	=/**/"GB";
				}
				else if((n4=Space.indexOf(/**/"MB"))>=0){
					DiskUnit	=/**/"MB";
				}
				else if((n4=Space.indexOf(/**/"KB"))>=0){
					DiskUnit	=/**/"KB";
				}
				else if((n4=Space.indexOf(/**/"B"))>=0){
					DiskUnit	=/**/"B";
					Space=/**/"1.0";
				}
				QString	NumStr=Space.remove(n4,Space.size()-n4);
				bool	ok=false;
				double	SpaceNum=Space.toDouble(&ok);
				if(ok==true){
					PCName=ComputerName;
					bool	Found=false;
					for(DiskList *d=Disk.GetFirst();d!=NULL;d=d->GetNext()){
						if(d->DiskName==Path){
							Found=true;
							d->DiskUnit	=DiskUnit;
							d->SizeNumb	=SpaceNum;
							Parent->ReviewWatch();
							break;
						}
					}
					if(Found==false){
						DiskList *d=new DiskList();
						d->DiskName	=Path;
						d->DiskUnit	=DiskUnit;
						d->SizeNumb	=SpaceNum;
						Disk.AppendList(d);
						Parent->ReviewWatch();
					}
				}
			}
		}
		else if(TypeValue==2){	//Alarm
			int	n1=MessageStr.indexOf(/**/":");
			int	n2=MessageStr.indexOf(/**/"(");
			int	n3=MessageStr.indexOf(/**/")");
			if(n1>=0 && n2>=0 && n3>=3){
				QString	ComputerName=MessageStr.left(n1);
				QString	Path		=MessageStr.mid(n1+1,n2-n1-1);

				bool	Found=false;
				for(DiskList *d=Disk.GetFirst();d!=NULL;d=d->GetNext()){
					if(d->DiskName==Path){
						Found=true;
						d->Alarm	=true;
						break;
					}
				}
			}
		}
		else if(TypeValue==11){
			QBuffer	Buff(&Data);
			Buff.open(QIODevice::ReadOnly);
			if(Parent->DiskFileInfoData.Load(&Buff)==true){
				Parent->ReviewFileList();
			}
		}
		else if(TypeValue==31){
			QBuffer	Buff(&Data);
			Buff.open(QIODevice::ReadOnly);
			QString		DestPath;
			QString		FileName;
			XDateTime	UpDateTime;
			QByteArray	Data;

			if(::Load(&Buff,DestPath)==false)
				return;
			if(::Load(&Buff,FileName)==false)
				return;
			if(::Load(&Buff,UpDateTime)==false)
				return;
			if(::Load(&Buff,Data)==false)
				return;
			QFile	File(DestPath + GetSeparator() +FileName);
			if(File.open(QIODevice::WriteOnly)==true){
				File.write(Data);
			}
		}
	}
	//Parent->PutMessage(TypeValue,GlobalPage,MessageStr);
}

void	SourcePCSocket::SlotDisconnected()
{
	Parent->SourcePCContainer.RemoveList(this);
}

MRecList	*SourcePCSocket::UnpackTopRxBuff(void)
{
	MuteRecData.lock();
	MRecList	*R=RecData.GetFirst();
	if(R!=NULL){
		RecData.RemoveList(R);
	}
	MuteRecData.unlock();
	return(R);
}

int		SourcePCSocket::GetQueuedCount(void)
{
	MuteRecData.lock();
	int	Ret=RecData.GetCount();
	MuteRecData.unlock();
	return(Ret);
}

//------------------------------------------------------------------------------

DiskManager::DiskManager(int Port,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),SockServer(this)
{
	ui.setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	QFile	File(MessagerRegFile);
	if(File.open(QIODevice::ReadOnly)==true){
		if(LoadSetting(&File)==true){
			ui.checkBoxAutoMode	->setChecked(AutoMode);
			ui.spinBoxYear		->setValue(PassedTime.year());
			ui.spinBoxMonth		->setValue(PassedTime.month());
			ui.spinBoxDay		->setValue(PassedTime.day());
			ui.spinBoxHour		->setValue(PassedTime.hour());
			ui.spinBoxMinute	->setValue(PassedTime.minute());
			ui.spinBoxSecond	->setValue(PassedTime.second());
			ui.checkBoxExecuteDelete	->setChecked(RemoveMode);
			//ui.listWidgetDestination	->addItems(Destinations);
		}
	}

	connect(&SockServer,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));

	SockServer.listen ( QHostAddress::Any, Port );
	setWindowState(Qt::WindowMinimized);

	ui.tableWidgetSourceDrive->setColumnWidth(0,150);
	ui.tableWidgetSourceDrive->setColumnWidth(1,50);
	ui.tableWidgetSourceDrive->setColumnWidth(2,90);

	ui.tableWidgetFileList	->setColumnWidth(0,250);
	ui.tableWidgetFileList	->setColumnWidth(1,300);
	ui.tableWidgetFileList	->setColumnWidth(2,90);
	ui.tableWidgetFileList	->setColumnWidth(3,120);
}

DiskManager::~DiskManager()
{

}

/*
void DiskManager::on_pushButtonAddDestination_clicked()
{
	QString	s=QFileDialog::getExistingDirectory(NULL,"Add destination folder");
	if(s.isEmpty()==false){
		Destinations.append(s);
		ui.listWidgetDestination	->addItems(Destinations);
	}
}

void DiskManager::on_pushButtonDeleteDestination_clicked()
{
	int	Row=ui.listWidgetDestination->currentRow();
	if(Row<0)
		return;
	Destinations.removeAt(Row);
	ui.listWidgetDestination	->addItems(Destinations);
}
*/

void DiskManager::on_pushButtonSaveSetting_clicked()
{
	AutoMode	=ui.checkBoxAutoMode	->isChecked();
	int	year	=ui.spinBoxYear		->value();
	int	month	=ui.spinBoxMonth		->value();
	int	day		=ui.spinBoxDay		->value();
	int	hour	=ui.spinBoxHour		->value();
	int	minute	=ui.spinBoxMinute	->value();
	int second	=ui.spinBoxSecond	->value();
	PassedTime.set(year,month,day ,hour,minute,second);
	RemoveMode	=ui.checkBoxExecuteDelete	->isChecked();

	QFile	File(MessagerRegFile);
	if(File.open(QIODevice::WriteOnly)==false){
		QMessageBox::warning(NULL
							,"Error"
							,"Can not save setting data");
		return;
	}
	if(SaveSetting(&File)==false){
		QMessageBox::warning(NULL
							,"Error"
							,"Can not save setting data");
		return;
	}
}

void DiskManager::on_checkBoxAutoMode_clicked()
{
	if(ui.checkBoxAutoMode->isChecked()==true){
		ui.frame->setDisabled(false);
	}
	else{
		ui.frame->setDisabled(true);
	}
}
void	DiskManager::ReviewWatch(void)
{
	int	Count=0;
	for(SourcePCSocket *a=SourcePCContainer.GetFirst();a!=NULL;a=a->GetNext()){
		Count+=a->Disk.GetCount();
	}
	ui.tableWidgetSourceDrive->setRowCount(Count);
	int	row=0;
	for(SourcePCSocket *a=SourcePCContainer.GetFirst();a!=NULL;a=a->GetNext()){
		for(DiskList *d=a->Disk.GetFirst();d!=NULL;d=d->GetNext()){
			::SetDataToTable(ui.tableWidgetSourceDrive ,0 ,row ,a->PCName);
			::SetDataToTable(ui.tableWidgetSourceDrive ,1 ,row ,d->DiskName);
			::SetDataToTable(ui.tableWidgetSourceDrive ,2 ,row ,QString::number(d->SizeNumb,'f',3)+d->DiskUnit);
			row++;
		}
	}
}
void	DiskManager::ReviewFileList(void)
{
	ui.tableWidgetFileList	->setRowCount(DiskFileInfoData.GetCount());
	int	row=0;
	for(DiskFileInfo *a=DiskFileInfoData.GetFirst();a!=NULL;a=a->GetNext()){
		::SetDataToTable(ui.tableWidgetFileList ,0 ,row ,a->Path);
		::SetDataToTable(ui.tableWidgetFileList ,1 ,row ,a->FileName);
		::SetDataToTable(ui.tableWidgetFileList ,2 ,row ,QString::number(a->Size));
		::SetDataToTable(ui.tableWidgetFileList ,3 ,row ,a->UpdatedTime.toString(/**/"yy/MM/dd hh:mm:ss"));
		row++;
	}
}

//void DiskManager::on_listWidgetDestination_doubleClicked(const QModelIndex &index)
//{

//}

void DiskManager::on_tableWidgetSourceDrive_clicked(const QModelIndex &index)
{
	int	Row=ui.tableWidgetSourceDrive->currentRow();
	if(Row<0)
		return;
	int	row=0;
	for(SourcePCSocket *a=SourcePCContainer.GetFirst();a!=NULL;a=a->GetNext()){
		for(DiskList *d=a->Disk.GetFirst();d!=NULL;d=d->GetNext()){
			if(row==Row){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				int32	Cmd=10;
				::Save(&Buff,Cmd);
				::Save(&Buff,d->DiskName);
				a->Send(Buff.buffer());
				return;
			}
			row++;
		}
	}
}

void DiskManager::on_tableWidgetFileList_doubleClicked(const QModelIndex &index)
{
	int	PCRow=ui.tableWidgetSourceDrive->currentRow();
	if(PCRow<0)
		return;
	int	row=0;
	SourcePCSocket	*DestPC=NULL;
	for(SourcePCSocket *a=SourcePCContainer.GetFirst();a!=NULL;a=a->GetNext()){
		for(DiskList *d=a->Disk.GetFirst();d!=NULL;d=d->GetNext()){
			if(row==PCRow){
				DestPC=a;
				goto	Found;
			}
			row++;
		}
	}
	return;
Found:;

	int	Row=ui.tableWidgetFileList->currentRow();
	if(Row<0)
		return;
	DiskFileInfo *a=DiskFileInfoData[Row];
	if(a==NULL)
		return;
	SelectFileOperationDialog	D(a);
	int	ret=D.exec();
	if(ret==1){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		int32	Cmd=21;
		::Save(&Buff,Cmd);
		::Save(&Buff,a->Path);
		::Save(&Buff,a->FileName);
		::Save(&Buff,D.DestPath);
		DestPC->Send(Buff.buffer());

		DiskFileInfoData.RemoveList(a);
		delete	a;
		ReviewFileList();
	}
	else if(ret==2){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		int32	Cmd=22;
		::Save(&Buff,Cmd);
		::Save(&Buff,a->Path);
		::Save(&Buff,a->FileName);
		DestPC->Send(Buff.buffer());

		DiskFileInfoData.RemoveList(a);
		delete	a;
		ReviewFileList();
	}

}

bool DiskManager::SaveSetting(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,AutoMode)==false)
		return false;
	if(::Save(f,PassedTime)==false)
		return false;
	if(::Save(f,RemoveMode)==false)
		return false;
	if(::Save(f,Destinations)==false)
		return false;
	return true;
}

bool DiskManager::LoadSetting(QIODevice *f)
{
	int32	Ver=1;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,AutoMode)==false)
		return false;
	if(::Load(f,PassedTime)==false)
		return false;
	if(::Load(f,RemoveMode)==false)
		return false;
	if(::Load(f,Destinations)==false)
		return false;
	return true;
}

void DiskManager::SlotNewConnection()
{
	SourcePCSocket	*s=new SourcePCSocket(this,SockServer.nextPendingConnection());
	s->Set();
	SourcePCContainer.AppendList(s);
	//connect(s->Sv,SIGNAL(readyRead())	,s,SLOT(SlotReadyRead()));
	//connect(s->Sv,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
	//s->Sv->setTextModeEnabled(true);
}

void DiskManager::on_pushButtonTransmitSetting_clicked()
{
	AutoMode	=ui.checkBoxAutoMode	->isChecked();
	int	year	=ui.spinBoxYear		->value();
	int	month	=ui.spinBoxMonth		->value();
	int	day		=ui.spinBoxDay		->value();
	int	hour	=ui.spinBoxHour		->value();
	int	minute	=ui.spinBoxMinute	->value();
	int second	=ui.spinBoxSecond	->value();
	PassedTime.set(year,month,day ,hour,minute,second);
	RemoveMode	=ui.checkBoxExecuteDelete	->isChecked();

	QBuffer	File;
	if(File.open(QIODevice::WriteOnly)==false){
		QMessageBox::warning(NULL
							,"Error"
							,"Can not save setting data");
		return;
	}
	if(SaveSetting(&File)==false){
		QMessageBox::warning(NULL
							,"Error"
							,"Can not save setting data");
		return;
	}
	for(SourcePCSocket *a=SourcePCContainer.GetFirst();a!=NULL;a=a->GetNext()){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		int32	Cmd=25;
		::Save(&Buff,Cmd);
		::Save(&Buff,File.buffer());

		a->Send(Buff.buffer());
	}
}
