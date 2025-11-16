#include "DFSProvider.h"
#include "AddRouteDialog.h"
#include<QMessageBox>
#include "XGeneralFunc.h"

extern	QString	DefaultSettingFileName;
extern	QString	ProviderName;

DFSProvider::DFSProvider(QString &IPAddress , int Address ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,Socket(this,IPAddress ,Address)
{
	ui.setupUi(this);
	Load();
}

DFSProvider::~DFSProvider()
{

}
	
bool	DFSProvider::Save(void)
{
	QFile	File(DefaultSettingFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		if(DFSProviderData.Save(&File)==false){
			return false;
		}
		return true;
	}
	return false;
}

bool	DFSProvider::Load(void)
{
	QFile	File(DefaultSettingFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		if(DFSProviderData.Load(&File)==false){
			return false;
		}
		ShowDFSProviderList();
		return true;
	}
	return false;
}
void DFSProvider::ShowDFSProviderList(void)
{
	ui.tableWidgetRoute->setRowCount(DFSProviderData.GetCount());
	int	row=0;
	for(PathClass *a=DFSProviderData.GetFirst();a!=NULL;a=a->GetNext()){
		::SetDataToTable(ui.tableWidgetRoute,0,row ,a->Path);
		::SetDataToTable(ui.tableWidgetRoute,1,row ,QString::number(a->Priority));
		row++;
	}
}

void DFSProvider::on_pushButtonAddRoute_clicked()
{
	AddRouteDialog	D;
	if(D.exec()==(int)true){
		PathClass	*a=new PathClass();
		a->Path		=D.Path;
		a->Priority	=D.Priority;
		a->NetworkPath	=D.NetworkPath;
		a->DFSFilterDLLFileName	=D.DFSFilterDLLFileName;
		a->DFSFilterParameter	=D.DFSFilterParameter;
		DFSProviderData.AppendList(a);

		int32 ErrorCode;
		a->LoadDLL(ErrorCode);

		Save();
		ShowDFSProviderList();
	}
}

void DFSProvider::on_pushButtonDeleteRoute_clicked()
{
	int	R=ui.tableWidgetRoute->currentRow();
	if(R<0)
		return;
	if(QMessageBox::question ( NULL, "Delete", "Delete line?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes)==QMessageBox::Yes){
		PathClass	*a=DFSProviderData[R];
		if(a!=NULL){
			DFSProviderData.RemoveList(a);
			delete	a;
			Save();
			ShowDFSProviderList();
		}
	}
}

void DFSProvider::on_tableWidgetRoute_doubleClicked(const QModelIndex &index)
{
	int	R=ui.tableWidgetRoute->currentRow();
	if(R<0)
		return;

	AddRouteDialog	D;
	D.Initial(*DFSProviderData[R]);
	if(D.exec()==(int)true){
		PathClass	*a=DFSProviderData[R];
		a->Path		=D.Path;
		a->Priority	=D.Priority;
		a->NetworkPath			=D.NetworkPath;
		a->DFSFilterDLLFileName	=D.DFSFilterDLLFileName;
		a->DFSFilterParameter	=D.DFSFilterParameter;
		int32 ErrorCode;
		a->LoadDLL(ErrorCode);
		Save();
		ShowDFSProviderList();
	}
}

void	DFSProvider::ReqEnumFolders(TreeFolderContainer &FolderData)
{
	for(PathClass *p=DFSProviderData.GetFirst();p!=NULL;p=p->GetNext()){
		p->ReqEnumFolders(FolderData);
	}
}

void	DFSProvider::ReqEnumFiles(const QString &RelativePath ,FileAttrContainer &FilesData)
{
	for(PathClass *p=DFSProviderData.GetFirst();p!=NULL;p=p->GetNext()){
		p->ReqEnumFiles(RelativePath ,FilesData);
	}
}

struct	PathClassWithPriority
{
	PathClass	*Point;
	int			Priority;
};


static	int	SortFunc(const void *a ,const void *b)
{
	struct	PathClassWithPriority *pa=((struct	PathClassWithPriority*)a);
	struct	PathClassWithPriority *pb=((struct	PathClassWithPriority*)b);
	int	r=pa->Priority-pb->Priority;
	return r;
}

void	DFSProvider::ReqSaveFile(FileSaveAttr &SaveAttr,QString &DestFolder,int32 &Priority)
{
	struct	PathClassWithPriority	*Dim;
	Dim=new struct	PathClassWithPriority[DFSProviderData.GetCount()];
	int	N=0;
	Priority=-1;
	for(PathClass *p=DFSProviderData.GetFirst();p!=NULL;p=p->GetNext()){
		Dim[N].Priority=p->GetPriorityToSaveFile(SaveAttr);
		if(Dim[N].Priority>=0){
			Dim[N].Point=p;
			N++;
		}
	}
	QSort(Dim,N,sizeof(Dim[0]),SortFunc);

	for(int i=0;i<N;i++){
		if(Dim[i].Point->NetworkPath.isEmpty()==false){
			DestFolder	=Dim[i].Point->NetworkPath;
			Priority	=Dim[i].Priority;
			break;
		}
	}
	delete	[]Dim;
}

void	DFSProvider::ReqLoadFile(FileLoadAttr &LoadedAttr,QString &DestNetworkFile)
{
	for(PathClass *p=DFSProviderData.GetFirst();p!=NULL;p=p->GetNext()){
		QString iDestNetworkFile;
		p->ReqLoadFile(LoadedAttr,iDestNetworkFile);
		if(iDestNetworkFile.isEmpty()==false){
			DestNetworkFile=iDestNetworkFile;
			break;
		}
	}
}

void	DFSProvider::ReqRemoveFile(FileLoadAttr &LoadedAttr)
{
	for(PathClass *p=DFSProviderData.GetFirst();p!=NULL;p=p->GetNext()){
		p->ReqRemoveFile(LoadedAttr);
	}
}
bool	DFSProvider::ReqAddFolder(AddFolderAttr &AddedAttr)
{
	bool	Ret=false;
	for(PathClass *p=DFSProviderData.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->ReqAddFolder(AddedAttr)==true)
			Ret=true;
	}
	return Ret;
}

bool	DFSProvider::ReqRemoveFolder(const QString &RelativeFolder)
{
	bool	Ret=false;
	for(PathClass *p=DFSProviderData.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->ReqRemoveFolder(RelativeFolder)==true)
			Ret=true;
	}
	return Ret;
}

bool	DFSProvider::ReqFindFile(const QString &RelativeFolder,const QString &FileName,FileFindAttr &FFindInfo)
{
	FileFindAttr	tInfo;
	for(PathClass *p=DFSProviderData.GetFirst();p!=NULL;p=p->GetNext()){
		QString iDestNetworkFile;
		p->ReqFindFile(RelativeFolder,FileName,tInfo);
		if(tInfo.FileName.isEmpty()==false){
			FFindInfo=tInfo;
			return true;
		}
	}
	return false;
}