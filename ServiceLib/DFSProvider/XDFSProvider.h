/*
 * Copyright (C) 2022
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

#if	!defined(XDFSProvider_H)
#define	XDFSProvider_H

#include "XTypeDef.h"
#include "NListComp.h"
#include <QLibrary>
#include <QIODevice>
#include <QBuffer>
#include <QMutex>
#include <QObject>
#include <QTcpServer>
#include "XDFSSocket.h"
#include "XDFSFilterBase.h"
#include "XDFS.h"

class	DFSProvider;

class	PathClass : public NPListSaveLoad<PathClass>
{
	WORD	(*DLL_GetDLLType)(void);
	bool	(*DLL_GetName)(QString &str);
	WORD	(*DLL_GetVersion)(void);
	const char	*(*DLL_GetSystemVersion)(VersionType vtype);
	const char	*(*DLL_GetExplain)(void);
	bool	(*DLL_CheckCopyright)(QString &CopyrightString);
	XDFSFilterBase		*(*DLL_Initial)(const QString &ParamStr);
	bool	(*DLL_Close)(XDFSFilterBase *handle);
	bool	(*DLL_Load)(XDFSFilterBase *handle ,QIODevice &str);
	bool	(*DLL_Save)(XDFSFilterBase *handle ,QIODevice &str);
	bool	(*DLL_ShowSetting)(XDFSFilterBase *handle, QWidget *parent);
	bool	(*DLL_ExecuteSaveFileInDFS)(XDFSFilterBase *handle ,FileSaveAttr *SavedAttr 
														,const QString &Provider ,const QString &LocalPath
														,int &Permit);
	QLibrary 	DllLib;
	XDFSFilterBase	*DFSFilterInst;
	QString		Copyright;
	QString		FilterName;
public:
	QString	Path;
	QString	NetworkPath;	//For the path to save/load from outer PC through LAN
	int		Priority;
	QString	DFSFilterDLLFileName;
	QString	DFSFilterParameter;

	PathClass(void);
	~PathClass(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	bool	LoadDLL(int32 &ErrorCode);

	void	ReqEnumFolders(TreeFolderContainer &FolderData);
	void	ReqEnumFiles(const QString &RelativePath ,FileAttrContainer &FilesData);
	int		GetPriorityToSaveFile(FileSaveAttr &SaveAttr);
	void	ReqLoadFile(FileLoadAttr &LoadedAttr,QString &DestNetworkFile);
	void	ReqRemoveFile(FileLoadAttr &LoadedAttr);
	bool	ReqAddFolder(AddFolderAttr &AddedAttr);
	bool	ReqRemoveFolder(const QString &RelativeFolder);
	bool	ReqFindFile(const QString &RelativeFolder,const QString &FileName,FileFindAttr &FFindInfo);
};

class	DFSProviderClass : public NPListPackSaveLoad<PathClass>
{
public:
	virtual	PathClass	*Create(void){	return new PathClass();	}
};

//-------------------------------------------------------

class	DFSClientInProvider : public DFSSocket
{
	DFSProvider	*Parent;
public:
	DFSClientInProvider(QObject *parent ,const QString &IPAddress,int PortNumber);

protected:
	virtual	void	Received(int cmd ,QByteArray &data);
};


#endif