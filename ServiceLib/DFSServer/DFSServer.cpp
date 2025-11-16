#include "DFSServer.h"
#include "XGeneralFunc.h"

DFSServer::DFSServer(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		ServerProvider[i].SetParent(this);
		ServerProvider[i].listen(QHostAddress::Any,DFSProviderPort+i);
	}
	for(int i=0;i<sizeof(ServerClient)/sizeof(ServerClient[0]);i++){
		ServerClient[i].SetParent(this);
		ServerClient[i].listen(QHostAddress::Any,DFSClientPort+i);
	}
}

DFSServer::~DFSServer()
{

}
	
void	DFSServer::ShowClient(void)
{
	int	Numb=0;
	for(int i=0;i<sizeof(ServerClient)/sizeof(ServerClient[0]);i++){
		Numb+=ServerClient[i].Client.GetCount();
	}

	ui.tableWidgetClients->setRowCount(Numb);
	int	Row=0;
	for(int i=0;i<sizeof(ServerClient)/sizeof(ServerClient[0]);i++){
		for(DFSSocket *c=ServerClient[i].Client.GetFirst();c!=NULL;c=c->GetNext()){
			::SetDataToTable(ui.tableWidgetClients ,0 ,Row ,c->GetPeerIPAddress());
			::SetDataToTable(ui.tableWidgetClients ,1 ,Row ,QString::number(c->GetPeerPort()));
		}
	}
}
	
void	DFSServer::ShowProvider(void)
{
	int	Numb=0;
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		Numb+=ServerProvider[i].Client.GetCount();
	}

	ui.tableWidgetDFSProviderList->setRowCount(Numb);
	int	Row=0;
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		for(DFSSocket *c=ServerProvider[i].Client.GetFirst();c!=NULL;c=c->GetNext()){
			::SetDataToTable(ui.tableWidgetDFSProviderList ,0 ,Row ,c->GetPeerIPAddress());
			::SetDataToTable(ui.tableWidgetDFSProviderList ,1 ,Row ,QString::number(c->GetPeerPort()));
		}
	}
}

void	DFSServer::ReqEnumFolders(TreeFolderContainer &FolderData)
{
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		ServerProvider[i].SendEnumFolders();
	}
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		ServerProvider[i].GatherEnumFolders(FolderData);
	}
}
	
void	DFSServer::ReqEnumFiles(QByteArray &RelativePathArray,FileAttrContainer &FileNames)
{
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		ServerProvider[i].SendEnumFiles(RelativePathArray);
	}
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		ServerProvider[i].GatherEnumFiles(FileNames);
	}
}

bool	DFSServer::ReqFolderToSaveFile(QByteArray &data,QString &FinalDestFolder)
{
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		ServerProvider[i].SendFolderToSaveFile(data);
	}
	int	MaxDestPriority=99999999;
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		int32	DestPriority;
		QString	DestFolder;
		ServerProvider[i].GatherFolderToSaveFile(DestFolder,DestPriority);
		if(DestPriority>=0 && DestPriority<MaxDestPriority){
			FinalDestFolder=DestFolder;
			MaxDestPriority=DestPriority;
		}
	}

	return true;
}
bool	DFSServer::ReqFileToLoad(QByteArray &data,QString &DestNetworkFile)
{
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		ServerProvider[i].SendFileToLoad(data);
	}
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		ServerProvider[i].GatherFileToLoad(DestNetworkFile);
		if(DestNetworkFile.isEmpty()==false){
			return true;
		}
	}

	return false;
}
void	DFSServer::ReqRemoveFile(QByteArray &data)
{
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		ServerProvider[i].ReqRemoveFile(data);
	}
}
void	DFSServer::ReqMakeFolder(QByteArray &data)
{
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		ServerProvider[i].ReqMakeFolder(data);
	}
}
void	DFSServer::ReqRemoveFolder(QByteArray &data)
{
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		ServerProvider[i].ReqRemoveFolder(data);
	}
}

void	DFSServer::RemoveProvider	(DFSClientSocketInProvider *s)
{
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		if(ServerProvider[i].Client.IsExist(s)==true){
			ServerProvider[i].Client.RemoveList(s);
			break;
		}
	}
	ShowProvider();
}

void	DFSServer::RemoveClient	(DFSClientSocketInServer *s)
{
	for(int i=0;i<sizeof(ServerClient)/sizeof(ServerClient[0]);i++){
		if(ServerClient[i].Client.IsExist(s)==true){
			ServerClient[i].Client.RemoveList(s);
			break;
		}
	}
	ShowClient();
}

bool	DFSServer::ReqFindFile(QByteArray &data,FileFindAttr &FileInfo)
{
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		ServerProvider[i].SendFindFile(data);
	}
	for(int i=0;i<sizeof(ServerProvider)/sizeof(ServerProvider[0]);i++){
		FileInfo.FileName.clear();
		ServerProvider[i].GatherFindFile(FileInfo);
		if(FileInfo.FileName.isEmpty()==false){
			return true;
		}
	}

	return false;
}