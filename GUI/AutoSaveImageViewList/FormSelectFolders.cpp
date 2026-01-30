/*
 * Copyright (C) 2026
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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