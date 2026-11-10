/*
 * Copyright (C) 2020
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

#include "SelectDirectoryDialog.h"
#include "ui_SelectDirectoryDialog.h"
#include <QStringList>

SelectDirectoryDialog::SelectDirectoryDialog(const QString &Path ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDirectoryDialog)
{
    ui->setupUi(this);

	Model.setFilter(QDir::AllDirs | QDir::Files);

	QStringList	NameList;

	NameList.append(/**/"*");

	Model.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Drives);
	Model.setNameFilters(NameList);
	Model.setNameFilterDisables(false);
	QModelIndex	Index=Model.setRootPath(Path);

	ui->treeView->setModel(&Model);
	ui->treeView->setRootIndex(Index);
	ui->treeView->resizeColumnToContents(1);
	ui->treeView->resizeColumnToContents(2);
}

SelectDirectoryDialog::~SelectDirectoryDialog()
{
    delete ui;
}

void SelectDirectoryDialog::on_pushButtonOK_clicked()
{
	Directory=ui->lineEditDirectory->text();
	done(true);
}

void SelectDirectoryDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SelectDirectoryDialog::on_treeView_clicked(const QModelIndex &index)
{
	QFileInfo	FInfo=Model.fileInfo(index);
	QString	path=FInfo.absoluteFilePath();
	ui->lineEditDirectory->setText(path);
}