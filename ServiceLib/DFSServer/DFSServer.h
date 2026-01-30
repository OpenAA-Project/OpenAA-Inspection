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

#ifndef DFSSERVER_H
#define DFSSERVER_H

#include <QMainWindow>
#include "ui_DFSServer.h"
#include "XDFSServer.h"
#include "XDFSSocket.h"


class DFSServer : public QMainWindow
{
	Q_OBJECT

	DFSServerToProvider	ServerProvider[16];
	DFSServerToClient	ServerClient[16];
public:
	DFSServer(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~DFSServer();

	void	ReqEnumFolders(TreeFolderContainer &FolderData);
	void	ReqEnumFiles(QByteArray &RelativePathArray,FileAttrContainer &FileNames);
	bool	ReqFolderToSaveFile(QByteArray &data,QString &DestFolder);
	bool	ReqFileToLoad(QByteArray &data,QString &DestNetworkFile);
	void	ReqRemoveFile(QByteArray &data);
	void	ReqMakeFolder(QByteArray &data);
	void	ReqRemoveFolder(QByteArray &data);
	bool	ReqFindFile(QByteArray &data,FileFindAttr &FileInfo);

	void	ShowClient(void);
	void	ShowProvider(void);

	void	RemoveProvider	(DFSClientSocketInProvider *s);
	void	RemoveClient	(DFSClientSocketInServer *s);
private slots:

private:
	Ui::DFSServerClass ui;
};

#endif // DFSSERVER_H