#include "DFSExplorer.h"
#include <QFileDialog>
#include "XForWindows.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QDateTime>
#include "XGeneralFunc.h"

DFSExplorer::DFSExplorer(QString &IPAddress ,int Address ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,Socket(this,IPAddress ,Address)
{
	ui.setupUi(this);
		
	TM.setInterval(5000);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();

	connect(&Socket,SIGNAL(SignalShowFolders()),this,SLOT(SlotShowFolders()));
	connect(&Socket,SIGNAL(SignalShowFiles()),this,SLOT(SlotShowFiles()));
	ShowFolder();
}

DFSExplorer::~DFSExplorer()
{

}

void	DFSExplorer::SlotTimeOut()
{
}


void	DFSExplorer::SetSubFolder(QTreeWidgetItem *Parent ,TreeFolder *F)
{
	for(TreeFolder *a=F->SubFolders.GetFirst();a!=NULL;a=a->GetNext()){
		QTreeWidgetItem	*Item=new QTreeWidgetItem(Parent);
		Item->setText(0,a->FolderName);
		Parent->addChild(Item);
		SetSubFolder(Item,a);
	}
}

void	DFSExplorer::ShowFolder(void)
{
	Socket.SetReceived(false);
	Socket.Send(DFSCmd_ReqEnumFolders);
	while(Socket.IsReceived()==false){
		QApplication::processEvents();
	}
	ui.treeWidgetFolders->clear();
	QTreeWidgetItem	*RootItem=new QTreeWidgetItem(ui.treeWidgetFolders);
	RootItem->setText(0,"Root");
	ui.treeWidgetFolders->addTopLevelItem(RootItem);

	for(TreeFolder *a=Folders.GetFirst();a!=NULL;a=a->GetNext()){
		QTreeWidgetItem	*Item=new QTreeWidgetItem(RootItem);
		Item->setText(0,a->FolderName);
		SetSubFolder(Item,a);
		RootItem->addChild(Item);
		//ui.treeWidgetFolders->addTopLevelItem(Item);
	}
}
void	DFSExplorer::ShowFiles(void)
{
	QTreeWidgetItem *R=ui.treeWidgetFolders->currentItem ();
	if(R==NULL)
		return;
	QString	RelativePath;
	do{
		QString	Path=R->text(0);
		if(Path==QString("Root"))
			break;
		if(RelativePath.isEmpty()==false)
			RelativePath.insert(0,"/");
		RelativePath.insert(0,Path);
		R=R->parent();
	}while(R!=NULL);

	QBuffer		PathBuff;
	PathBuff.open(QIODevice::WriteOnly);
	::Save(&PathBuff,RelativePath);
	Socket.SetReceived(false);
	Socket.Send(DFSCmd_ReqEnumFiles,PathBuff.buffer());
	while(Socket.IsReceived()==false){
		QApplication::processEvents();
	}
	Files=Socket.FileNames;
	SlotShowFiles();
}

void	DFSExplorer::SlotShowFolders()
{
	Folders=Socket.Folders;

	ui.treeWidgetFolders->clear();
	for(TreeFolder *a=Folders.GetFirst();a!=NULL;a=a->GetNext()){
		QTreeWidgetItem	*Item=new QTreeWidgetItem(ui.treeWidgetFolders);
		Item->setText(0,a->FolderName);
		SetSubFolder(Item,a);
		ui.treeWidgetFolders->addTopLevelItem(Item);
	}

}
void	DFSExplorer::SlotShowFiles()
{
	int	Numb=Files.GetCount();
	ui.tableWidgetFiles	->setRowCount(Numb);
	int	Row=0;
	for(FileAttrList *a=Files.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui.tableWidgetFiles ,0 ,Row ,a->FileName);
		::SetDataToTable(ui.tableWidgetFiles ,1 ,Row ,a->Provider);
		::SetDataToTable(ui.tableWidgetFiles ,2 ,Row ,a->RelativePath);
		QFileInfo	FInfo(a->FileName);
		::SetDataToTable(ui.tableWidgetFiles ,3 ,Row ,FInfo.suffix());
		::SetDataToTable(ui.tableWidgetFiles ,4 ,Row ,QString::number(a->FileSize));
		::SetDataToTable(ui.tableWidgetFiles ,5 ,Row ,a->FileStamp.toString("yy/MM/dd hh:mm:ss"));
	}
}

void DFSExplorer::on_treeWidgetFolders_clicked(const QModelIndex &index)
{
	ShowFiles();
}

void DFSExplorer::on_pushButtonCopyTo_clicked()
{
	QTreeWidgetItem *R=ui.treeWidgetFolders->currentItem ();
	if(R==NULL)
		return;
	QString	RelativePath;
	do{
		QString	Path=R->text(0);
		if(Path==QString("Root"))
			break;
		if(RelativePath.isEmpty()==false)
			RelativePath.insert(0,"/");
		RelativePath.insert(0,Path);
		R=R->parent();
	}while(R!=NULL);

	QString FileName=QFileDialog::getOpenFileName ( NULL, QString("Copy To"), QString(),QString("All files(*.*)"));
	if(FileName.isEmpty()==false){
		FileSaveAttr	A;
		QFileInfo	FInfo(FileName);
		A.SourcePath		=FInfo.absolutePath();
		A.FileName			=FInfo.fileName();
		A.DestRelativePath	=RelativePath;
		A.FileSize			=FInfo.size();
		A.FileStamp			=FInfo.lastModified();

		QBuffer		PathBuff;
		PathBuff.open(QIODevice::WriteOnly);
		A.Save(&PathBuff);
		Socket.SetReceived(false);
		Socket.Send(DFSCmd_ReqSaveFile,PathBuff.buffer());
		while(Socket.IsReceived()==false){
			QApplication::processEvents();
		}
		QString	DestFileName=Socket.DestNetwordFolder + ::GetSeparator()+A.DestRelativePath+::GetSeparator()+FInfo.fileName();
		::MTCopyFile(FileName ,DestFileName ,false);
		ShowFiles();
	}
}

void DFSExplorer::on_pushButtonCopyFrom_clicked()
{
	QTreeWidgetItem *R=ui.treeWidgetFolders->currentItem ();
	if(R==NULL)
		return;
	QString	RelativePath;
	do{
		QString	Path=R->text(0);
		if(Path==QString("Root"))
			break;
		if(RelativePath.isEmpty()==false)
			RelativePath.insert(0,"/");
		RelativePath.insert(0,Path);
		R=R->parent();
	}while(R!=NULL);

	int	Row=ui.tableWidgetFiles->currentRow();
	if(Row<0)
		return;
	FileAttrList	*L=Files[Row];

	QString LoadedPath=QFileDialog::getExistingDirectory ( NULL, QString("Copy To"), QString());
	if(LoadedPath.isEmpty()==false){
		FileLoadAttr	A;
		A.DestPath			=LoadedPath;
		A.Provider			=L->Provider;
		A.FileName			=L->FileName;
		A.SourceRelativePath=RelativePath;
		A.FileSize			=L->FileSize;
		A.FileStamp			=L->FileStamp;

		QBuffer		PathBuff;
		PathBuff.open(QIODevice::WriteOnly);
		A.Save(&PathBuff);
		Socket.SetReceived(false);
		Socket.Send(DFSCmd_ReqLoadFile,PathBuff.buffer());
		while(Socket.IsReceived()==false){
			QApplication::processEvents();
		}
		QString	SourceFileName	=Socket.DestNetworkFile;
		QString	DestFileName	=LoadedPath+::GetSeparator()+L->FileName;

		::MTCopyFile(SourceFileName ,DestFileName ,false);
	}
}

void DFSExplorer::on_pushButtonRemove_clicked()
{
	QTreeWidgetItem *R=ui.treeWidgetFolders->currentItem ();
	if(R==NULL)
		return;
	QString	RelativePath;
	do{
		QString	Path=R->text(0);
		if(Path==QString("Root"))
			break;
		if(RelativePath.isEmpty()==false)
			RelativePath.insert(0,"/");
		RelativePath.insert(0,Path);
		R=R->parent();
	}while(R!=NULL);

	int	Row=ui.tableWidgetFiles->currentRow();
	if(Row<0)
		return;
	FileAttrList	*L=Files[Row];

	if(QMessageBox::question ( NULL, "Delete", "Delete OK?", QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		FileLoadAttr	A;
		A.Provider			=L->Provider;
		A.FileName			=L->FileName;
		A.SourceRelativePath=RelativePath;
		A.FileSize			=L->FileSize;
		A.FileStamp			=L->FileStamp;

		QBuffer		PathBuff;
		PathBuff.open(QIODevice::WriteOnly);
		A.Save(&PathBuff);
		Socket.SetReceived(false);
		Socket.Send(DFSCmd_ReqRemoveFile,PathBuff.buffer());
		while(Socket.IsReceived()==false){
			QApplication::processEvents();
		}
		ShowFiles();
	}
}
void DFSExplorer::on_pushButtonAddFolder_clicked()
{
	QTreeWidgetItem *R=ui.treeWidgetFolders->currentItem ();
	if(R==NULL)
		return;
	QString	RelativePath;
	do{
		QString	Path=R->text(0);
		if(Path==QString("Root"))
			break;
		if(RelativePath.isEmpty()==false)
			RelativePath.insert(0,"/");
		RelativePath.insert(0,Path);
		R=R->parent();
	}while(R!=NULL);

	QString	FolderName=QInputDialog::getText ( NULL, QString("Add new folder in ")+RelativePath
											, "New folder name"
											, QLineEdit::Normal
											, QString());
	if(FolderName.isEmpty()==false){
		AddFolderAttr	A;
		A.SourceRelativePath=RelativePath;
		A.NewFolderName		=FolderName;

		QBuffer		PathBuff;
		PathBuff.open(QIODevice::WriteOnly);
		A.Save(&PathBuff);
		Socket.SetReceived(false);
		Socket.Send(DFSCmd_ReqMakeFolder,PathBuff.buffer());
		while(Socket.IsReceived()==false){
			QApplication::processEvents();
		}

		ShowFolder();
	}
}
void DFSExplorer::on_pushButtonRemoveFolder_clicked()
{
	QTreeWidgetItem *R=ui.treeWidgetFolders->currentItem ();
	if(R==NULL)
		return;
	QString	RelativePath;
	do{
		QString	Path=R->text(0);
		if(Path==QString("Root"))
			break;
		if(RelativePath.isEmpty()==false)
			RelativePath.insert(0,"/");
		RelativePath.insert(0,Path);
		R=R->parent();
	}while(R!=NULL);

	if(QMessageBox::question ( NULL, QString("Delete foler :")+RelativePath
									, "Delete foler OK?", QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		QBuffer		PathBuff;
		PathBuff.open(QIODevice::WriteOnly);
		::Save(&PathBuff,RelativePath);
		Socket.SetReceived(false);
		Socket.Send(DFSCmd_ReqRemoveFolder,PathBuff.buffer());
		while(Socket.IsReceived()==false){
			QApplication::processEvents();
		}
		ShowFolder();
	}
}
