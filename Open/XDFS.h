/*
 * Copyright (C) 2023
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

#if	!defined(XDFS_H)
#define	XDFS_H

#include "XTypeDef.h"
#include "XDateTime.h"
#include <QString>
#include <QIODevice>
#include <QBuffer>
#include <QMutex>
#include <QObject>
#include <QFile>
#include "NListComp.h"

class	TreeFolder;

class	TreeFolderContainer : public NPListPackSaveLoad<TreeFolder>
{
public:
	TreeFolderContainer(void){}

	virtual	TreeFolder	*Create(void);
	void	AddPath(const QString &RelativePath);
	void	Merge(TreeFolderContainer &Src);

	bool	operator==(TreeFolderContainer &src)	const;
	bool	operator!=(TreeFolderContainer &src)	const{	return !operator==(src);	}
private:
	bool	AddRecursive(int Index,const QStringList &List);
	bool	SearchRecursive(int Index,const QStringList &List);
};

class	TreeFolder : public NPListSaveLoad<TreeFolder>
{
	TreeFolderContainer	*Parent;
public:
	TreeFolderContainer		SubFolders;
	QString					FolderName;	//Relative path
	QString					IPAddress;

	TreeFolder(TreeFolderContainer *parent);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	TreeFolder	&operator=(TreeFolder &src);
	bool	IsEqualOnly(TreeFolder &src)const;
	bool	operator==(TreeFolder &src)	const;
	bool	operator!=(TreeFolder &src)	const	{	return !operator==(src);	}
};

//=============================================================================
class	FileAttrList;

class	FileAttrContainer : public NPListPackSaveLoad<FileAttrList>
{
public:
	FileAttrContainer(void){}

	virtual	FileAttrList	*Create(void);
};

class	FileAttrList : public NPListSaveLoad<FileAttrList>
{
public:
	QString		RelativePath;
	QString		FileName;
	QString		Provider;
	int64		FileSize;
	XDateTime	FileStamp;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	FileSaveAttr
{
public:
	QString		SourcePath;
	QString		DestRelativePath;
	QString		FileName;
	int64		FileSize;
	XDateTime	FileStamp;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	FileLoadAttr
{
public:
	QString		DestPath;
	QString		Provider;
	QString		SourceRelativePath;
	QString		FileName;
	int64		FileSize;
	XDateTime	FileStamp;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};


class	FileFindAttr
{
public:
	QString		SourceRelativePath;
	QString		Provider;
	QString		NetworkPath;
	QString		FileName;
	int64		FileSize;
	XDateTime	FileStamp;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	AddFolderAttr
{
public:
	QString		SourceRelativePath;
	QString		NewFolderName;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

//=============================================================================
class	DFSClient;

class	DFSGate : public QIODevice
{
	DFSClient	*Client;
	QString		AbsSourceFileName;
	FileFindAttr	CurrentInfo;
	QFile		*File;
public:
	DFSGate(const QString &FileName
			,QObject *parent,const QString &IPAddress,int PortNumber);
	~DFSGate(void);

	virtual qint64 bytesAvailable () const;
	virtual qint64 bytesToWrite () const;
	
	virtual bool canReadLine () const;
	virtual void close ();
	virtual bool isSequential () const;
	virtual bool open ( OpenMode mode );
	//virtual qint64 pos () const;
	virtual bool reset ();
	//virtual bool seek ( qint64 pos );
	virtual qint64 size () const;
	virtual bool waitForBytesWritten ( int msecs );
	virtual bool waitForReadyRead ( int msecs );
	
	virtual bool atEnd () const;

	bool remove ();
	bool rename ( const QString & newName );
	bool resize ( qint64 sz );
	bool exists () const;
	QString fileName () const;
	bool flush ();


	static	bool	MtCopyFileFrom	(const QString &DFSSourceFilePath , const QString &DestFilePath
										,QObject *parent,const QString &IPAddress,int PortNumber);
	static	bool	MtCopyFileTo	(const QString &SourceFilePath , const QString &DFSDestFilePath
										,QObject *parent,const QString &IPAddress,int PortNumber);

protected:
	virtual qint64 readData ( char * data, qint64 maxSize );
	virtual qint64 readLineData ( char * data, qint64 maxSize );
	virtual qint64 writeData ( const char * data, qint64 maxSize );
};

#endif