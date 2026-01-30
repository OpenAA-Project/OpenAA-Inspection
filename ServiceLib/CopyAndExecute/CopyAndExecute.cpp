/*
 * Copyright (C) 2021
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

#include "CopyAndExecute.h"
#include <QDir>

CopyAndExecute::CopyAndExecute(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

CopyAndExecute::~CopyAndExecute()
{

}
void CopyAndExecute::resizeEvent ( QResizeEvent * event )
{
	ui.listWidget->setGeometry(0,0,width(),height());
}
void	CopyAndExecute::Initial(QString	&_SourcePath)
{
	SourcePath=_SourcePath;
}
void	CopyAndExecute::DeleteFiles	(const QString &TargetFile)
{
	QFileInfo	FInfo(TargetFile);
	QString		SPath=FInfo.absolutePath();
	QDir	cd(SPath);
	QStringList	List;
	List.append(FInfo.fileName());
	QStringList	FileList=cd.entryList(List,QDir::Files);
	for(int i=0;i<FileList.count();i++){
		QString	FileName=FInfo.absolutePath()+QString(/**/"\\")+FileList[i];
		if(QFile::remove(FileName)==true){
			ui.listWidget->insertItem(0,QString(/**/"Del ")+FileName);
			ui.listWidget->update();
			QApplication::processEvents();
		}
	}
}

void	CopyAndExecute::CopyFiles	(const QString &SourceFile,const QString &DestinationPath)
{
	QFileInfo	FInfo(SourcePath+QString(/**/"\\")+SourceFile);
	QString		SPath=FInfo.absolutePath();
	QDir	cd(SPath);
	QStringList	List;
	List.append(FInfo.fileName());
	QStringList	FileList=cd.entryList(List,QDir::Files);
	for(int i=0;i<FileList.count();i++){
		QString	SFileName=FInfo.absolutePath()+QString(/**/"\\")+FileList[i];
		QFileInfo	DInfo(DestinationPath+((DestinationPath.isEmpty()==true)?QString(/**/""):QString(/**/"\\"))+FileList[i]);
		QString	DFileName=DInfo.absoluteFilePath();
		if(QFile::exists (DFileName)==true){
			QFile::remove(DFileName);
		}
		if(QFile::copy ( SFileName, DFileName )==true){
			ui.listWidget->insertItem(0,QString(/**/"Copy ")+SFileName);
			ui.listWidget->update();
			QApplication::processEvents();
		}
	}
}