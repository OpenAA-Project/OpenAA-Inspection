/*
 * Copyright (C) 2016
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

#if	!defined(XDFSClient_H)
#define	XDFSClient_H

#include "XDFSSocket.h"
#include "XDFS.h"

class	DFSClient: public DFSSocket
{
	Q_OBJECT

public:
	TreeFolderContainer		Folders;
	FileAttrContainer		FileNames;
	QString					DestNetwordFolder;
	QString					DestNetworkFile;
	FileFindAttr			CurrentInfo;

	DFSClient(QObject *parent ,const QString &IPAddress,int PortNumber);

signals:
	void	SignalShowFolders();
	void	SignalShowFiles();

protected:
	virtual	void	Received(int cmd ,QByteArray &data);
};



#endif