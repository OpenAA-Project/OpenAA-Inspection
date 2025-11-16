#include "XDFSServer.h"
#include "DFSServer.h"

	
DFSServerToProvider::DFSServerToProvider(void)
{
	Parent=NULL;
	connect(this,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
}
void	DFSServerToProvider::SetParent(DFSServer *parent)
{
	Parent=parent;
	setParent(parent);
}
void	DFSServerToProvider::SendEnumFolders(void)
{
	for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
		a->Send(DFSCmd_ReqEnumFolders);
		a->SetReceived(false);
		a->SetAccessed(false);
	}
}

void	DFSServerToProvider::GatherEnumFolders(TreeFolderContainer &FolderData)
{
	bool	Flag;
	do{
		Flag=true;
		for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsAccessed()==false){
				if(a->IsReceived()==true){
					a->SetAccessed(true);
					DFSClientSocketInProvider	*p=dynamic_cast<DFSClientSocketInProvider *>(a);
					FolderData.Merge(p->Folders);
				}
				else{
					Flag=false;
				}
			}
		}
		QApplication::processEvents();
	}while(Flag==false);
}
	
void	DFSServerToProvider::SendEnumFiles(QByteArray &RelativePathArray)
{
	for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
		a->Send(DFSCmd_ReqEnumFiles,RelativePathArray);
		a->SetReceived(false);
		a->SetAccessed(false);
	}
}

void	DFSServerToProvider::GatherEnumFiles(FileAttrContainer &FilesData)
{
	bool	Flag;
	do{
		Flag=true;
		for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsAccessed()==false){
				if(a->IsReceived()==true){
					a->SetAccessed(true);
					DFSClientSocketInProvider	*p=dynamic_cast<DFSClientSocketInProvider *>(a);
					FilesData+=p->FilesData;
				}
				else{
					Flag=false;
				}
			}
		}
		QApplication::processEvents();
	}while(Flag==false);
}
	
void	DFSServerToProvider::SendFolderToSaveFile(QByteArray &SaveAttr)
{
	for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
		a->Send(DFSCmd_ReqSaveFile,SaveAttr);
		a->SetReceived(false);
		a->SetAccessed(false);
	}
}

void	DFSServerToProvider::GatherFolderToSaveFile(QString &DestFolder,int32 &DestPriority)
{
	bool	Flag;
	QString tDestFolder;
	int32	tDestPriority=99999999;
	do{
		Flag=true;
		for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsAccessed()==false){
				if(a->IsReceived()==true){
					a->SetAccessed(true);
					DFSClientSocketInProvider	*p=dynamic_cast<DFSClientSocketInProvider *>(a);
					if(p->DestPriority>=0 && p->DestPriority<tDestPriority){
						tDestFolder	=p->DestFolder;
						tDestPriority=p->DestPriority;
					}
				}
				else{
					Flag=false;
				}
			}
		}
		QApplication::processEvents();
	}while(Flag==false);

	if(tDestPriority==99999999){
		DestPriority=-1;
	}
	else{
		DestFolder	=tDestFolder;
		DestPriority=tDestPriority;
	}
}
	
void	DFSServerToProvider::SendFileToLoad(QByteArray &LoadedAttr)
{
	for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
		a->Send(DFSCmd_ReqLoadFile,LoadedAttr);
		a->SetReceived(false);
		a->SetAccessed(false);
	}
}

void	DFSServerToProvider::GatherFileToLoad(QString &DestNetworkFile)
{
	bool	Flag;
	do{
		Flag=true;
		for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsAccessed()==false){
				if(a->IsReceived()==true){
					a->SetAccessed(true);
					DFSClientSocketInProvider	*p=dynamic_cast<DFSClientSocketInProvider *>(a);
					DestNetworkFile=p->DestNetworkFile;
				}
				else{
					Flag=false;
				}
			}
		}
		QApplication::processEvents();
	}while(Flag==false);
}

void	DFSServerToProvider::ReqRemoveFile(QByteArray &data)
{
	for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
		a->Send(DFSCmd_ReqRemoveFile,data);
		a->SetReceived(false);
		a->SetAccessed(false);
	}
	bool	Flag;
	do{
		Flag=true;
		for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsAccessed()==false){
				if(a->IsReceived()==true){
					a->SetAccessed(true);
				}
				else{
					Flag=false;
				}
			}
		}
		QApplication::processEvents();
	}while(Flag==false);
}
void	DFSServerToProvider::ReqMakeFolder(QByteArray &data)
{
	for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
		a->Send(DFSCmd_ReqMakeFolder,data);
		a->SetReceived(false);
		a->SetAccessed(false);
	}
	bool	Flag;
	do{
		Flag=true;
		for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsAccessed()==false){
				if(a->IsReceived()==true){
					a->SetAccessed(true);
				}
				else{
					Flag=false;
				}
			}
		}
		QApplication::processEvents();
	}while(Flag==false);
}
void	DFSServerToProvider::ReqRemoveFolder(QByteArray &data)
{
	for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
		a->Send(DFSCmd_ReqRemoveFolder,data);
		a->SetReceived(false);
		a->SetAccessed(false);
	}
	bool	Flag;
	do{
		Flag=true;
		for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsAccessed()==false){
				if(a->IsReceived()==true){
					a->SetAccessed(true);
				}
				else{
					Flag=false;
				}
			}
		}
		QApplication::processEvents();
	}while(Flag==false);
}

void	DFSServerToProvider::SendFindFile(QByteArray &FileAttr)
{
	for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
		a->Send(DFSCmd_ReqFindFile,FileAttr);
		a->SetReceived(false);
		a->SetAccessed(false);
	}
}
void	DFSServerToProvider::GatherFindFile(FileFindAttr &FileInfo)
{
	bool	Flag;
	do{
		Flag=true;
		for(DFSSocket *a=Client.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsAccessed()==false){
				if(a->IsReceived()==true){
					a->SetAccessed(true);
					DFSClientSocketInProvider	*p=dynamic_cast<DFSClientSocketInProvider *>(a);
					if(p->FFindInfo.FileName.isEmpty()==false){
						FileInfo=p->FFindInfo;
						return;
					}
					Flag=true;
				}
				else{
					Flag=false;
				}
			}
		}
		QApplication::processEvents();
	}while(Flag==false);
}

void DFSServerToProvider::SlotNewConnection ()
{
	DFSClientSocketInProvider	*a=new DFSClientSocketInProvider(Parent,nextPendingConnection ());
	Client.AppendList(a);
	Parent->ShowProvider();
}

	
DFSServerToClient::DFSServerToClient(void)
{
	Parent=NULL;
	connect(this,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
}

void	DFSServerToClient::SetParent(DFSServer *parent)
{
	Parent=parent;
	setParent(parent);
}

void DFSServerToClient::SlotNewConnection ()
{
	DFSClientSocketInServer	*a=new DFSClientSocketInServer(Parent,nextPendingConnection ());
	Client.AppendList(a);
	Parent->ShowClient();
}

//==================================================================================
DFSClientSocketInProvider::DFSClientSocketInProvider(DFSServer *parent ,QTcpSocket *sv)
	:DFSSocket(parent,sv)
	,Parent(parent)
{
}

void	DFSClientSocketInProvider::Received(int cmd ,QByteArray &data)
{
	if(cmd==DFSCmd_AckEnumFolders){
		Folders.RemoveAll();
		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		Folders.Load(&RBuff);
		SetReceived(true);
	}
	else if(cmd==DFSCmd_AckEnumFiles){
		FilesData.RemoveAll();
		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		FilesData.Load(&RBuff);
		SetReceived(true);
	}
	else if(cmd==DFSCmd_AckSaveFile){
		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		::Load(&RBuff,DestFolder);
		::Load(&RBuff,DestPriority);
		SetReceived(true);
	}
	else if(cmd==DFSCmd_AckLoadFile){
		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		::Load(&RBuff,DestNetworkFile);
		SetReceived(true);
	}
	else if(cmd==DFSCmd_AckRemoveFile){
		SetReceived(true);
	}
	else if(cmd==DFSCmd_AckMakeFolder){
		SetReceived(true);
	}
	else if(cmd==DFSCmd_AckRemoveFolder){
		SetReceived(true);
	}
	else if(cmd==DFSCmd_AckFindFile){
		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		FFindInfo.Load(&RBuff);
		SetReceived(true);
	}
}


void	DFSClientSocketInProvider::SlotDisconnected()
{
	Parent->RemoveProvider(this);
}


DFSClientSocketInServer::DFSClientSocketInServer(DFSServer *parent ,QTcpSocket *sv)
	:DFSSocket(parent,sv)
	,Parent(parent)
{
}

void	DFSClientSocketInServer::Received(int cmd ,QByteArray &data)
{
	if(cmd==DFSCmd_ReqEnumFolders){
		TreeFolderContainer FolderData;
		Parent->ReqEnumFolders(FolderData);

		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		FolderData.Save(&Buff);
		Send(DFSCmd_AckEnumFolders,Buff.buffer());
	}
	else if(cmd==DFSCmd_ReqEnumFiles){
		FileAttrContainer	FileNames;
		Parent->ReqEnumFiles(data,FileNames);

		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		FileNames.Save(&Buff);
		Send(DFSCmd_AckEnumFiles,Buff.buffer());
	}
	else if(cmd==DFSCmd_ReqSaveFile){
		QString		DestFolder;
		Parent->ReqFolderToSaveFile(data,DestFolder);

		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		::Save(&Buff,DestFolder);
		Send(DFSCmd_AckSaveFile,Buff.buffer());
	}
	else if(cmd==DFSCmd_ReqLoadFile){
		QString		DestNetworkFile;
		Parent->ReqFileToLoad(data,DestNetworkFile);

		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		::Save(&Buff,DestNetworkFile);
		Send(DFSCmd_AckLoadFile,Buff.buffer());
	}
	else if(cmd==DFSCmd_ReqRemoveFile){
		Parent->ReqRemoveFile(data);
		Send(DFSCmd_AckRemoveFile);
	}
	else if(cmd==DFSCmd_ReqMakeFolder){
		Parent->ReqMakeFolder(data);
		Send(DFSCmd_AckMakeFolder);
	}
	else if(cmd==DFSCmd_ReqRemoveFolder){
		Parent->ReqRemoveFolder(data);
		Send(DFSCmd_AckRemoveFolder);
	}
	else if(cmd==DFSCmd_ReqFindFile){
		FileFindAttr		FileInfo;
		Parent->ReqFindFile(data,FileInfo);

		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		FileInfo.Save(&Buff);
		Send(DFSCmd_AckFindFile,Buff.buffer());
	}
}

void	DFSClientSocketInServer::SlotDisconnected()
{
	Parent->RemoveClient(this);
}
