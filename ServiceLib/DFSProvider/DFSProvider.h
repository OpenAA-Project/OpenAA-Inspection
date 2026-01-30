/*
 * Copyright (C) 2025
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

#ifndef DFSPROVIDER_H
#define DFSPROVIDER_H

#include <QMainWindow>
#include "ui_DFSProvider.h"
#include "XDFSProvider.h"

class DFSProvider : public QMainWindow
{
	Q_OBJECT

	DFSProviderClass	DFSProviderData;
	DFSClientInProvider	Socket;
public:
	DFSProvider(QString &IPAddress , int Address ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~DFSProvider();

	void	ReqEnumFolders(TreeFolderContainer &FolderData);
	void	ReqEnumFiles(const QString &RelativePath ,FileAttrContainer &FilesData);
	void	ReqSaveFile(FileSaveAttr &SaveAttr,QString &DestFolder,int32 &Priority);
	void	ReqLoadFile(FileLoadAttr &LoadedAttr,QString &DestNetworkFile);
	void	ReqRemoveFile(FileLoadAttr &LoadedAttr);
	bool	ReqAddFolder(AddFolderAttr &AddedAttr);
	bool	ReqRemoveFolder(const QString &RelativeFolder);
	bool	ReqFindFile(const QString &RelativeFolder,const QString &FileName,FileFindAttr &FFindInfo);

private slots:
    void on_pushButtonAddRoute_clicked();
    void on_pushButtonDeleteRoute_clicked();

    void on_tableWidgetRoute_doubleClicked(const QModelIndex &index);

private:
	Ui::DFSProviderClass ui;

	bool	Save(void);
	bool	Load(void);
	void	ShowDFSProviderList(void);

};

#endif // DFSPROVIDER_H