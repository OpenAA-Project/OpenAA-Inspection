#include "AutoSaveImageViewListResource.h"
#include "FormSelectFolders.h"
#include <QFileSystemModel>
#include <QDir>
#include <QFileInfo>

FormSelectFolders::FormSelectFolders(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	QFileSystemModel *model = new QFileSystemModel();
	model->setFilter(QDir::Drives | QDir::Dirs);
	ui.treeViewFolders->setModel(model);
	//ui.treeViewFolders->setRootIndex(model->index(QDir::currentPath()));

	InstallOperationLog(this);
}

FormSelectFolders::~FormSelectFolders()
{

}


void FormSelectFolders::on_pushButtonOK_clicked()
{
	PathLists.clear();
	QItemSelectionModel *SelectedItemsmodel=ui.treeViewFolders->QAbstractItemView::selectionModel();
	QModelIndexList SIndex=SelectedItemsmodel->selectedIndexes();
	QFileSystemModel *DModel = (QFileSystemModel *)ui.treeViewFolders->model();
	for(int i=0;i<SIndex.count();i++){
		QModelIndex Index=SIndex[i];
		if(Index.column()==0){
			QFileInfo FInfo=DModel->fileInfo(Index);
			PathLists.append(FInfo.absoluteFilePath());
		}
	}

	done(true);
}

void FormSelectFolders::on_pushButtonCancel_clicked()
{
	done(false);
}