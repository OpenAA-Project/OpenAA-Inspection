#pragma once

#include <QThread>
#include <QIODevice>
#include <QMutex>
#include <QByteArray>
#include <QString>
#include <QFile>
#include <QChar>
#include <QStringList>
#include <QDateTime>
#include <QByteArrayList>
#include <QPoint>
#include "XServiceForLayers.h"
#include "NList.h"
#include "XTypeDef.h"
#include "XYCross.h"

class XDateTime;

#define	MaxBufferedFileList		10000

class FileThread : public ServiceForLayers
{
	friend	class FileThreadListContainer;

	QString		FileName;
	QByteArray	Data;
	QIODevice::OpenMode Mode;
public:
	FileThread(LayersBase *Base ,const QString &FileName);
	~FileThread();

	bool	open(QIODevice::OpenMode mode);
	qint64	write(const char *data, qint64 maxSize);
	qint64	write(const QByteArray &byteArray);
	bool	flush();	//Move data into thread-writeer
	const	QByteArray	&GetData(void)	const	{	return Data;	}	//This must be called before flush

	bool	Save(int8 d);
	bool	Save(int32 d);
	bool	Save(uint32 d);
	bool	Save(int64 d);
	bool	Save(short d);
	bool	Save(WORD d);
	bool	Save(DWORD d);
	bool	Save(float d);
	bool	Save(double d);
	bool	Save(BYTE d);
	bool	Save(const QChar& d);
	bool	Save(char d);
	bool	Save(bool d);
	bool	Save(bool3 d);
	bool	Save(const char* d, int64 len);
	//bool	Save(const char* d);
	bool	Save(const QString& d);
	bool	Save(const QStringList& d);
	bool	Save(const XYData& d);
	bool	Save(const QDateTime& d);
	bool	Save(const QDate& d);
	bool	Save(const QTime& d);
	bool	Save(const XDateTime& d);
	//bool	Save(QRgb &d);
	bool	Save(const QByteArray& d);
	bool	Save(const QByteArrayList& d);
	bool	Save(BYTE** Point, int XLen, int YLen);
	bool	SaveText(char* s);
	bool	Save(const QPoint& d);

};

class DirectoryThread : public ServiceForLayers
{
	friend	class FileThreadListContainer;

	QString		FileName;
	QByteArray	Data;
public:
	DirectoryThread(LayersBase *Base);
	~DirectoryThread();

	bool ForceDirectories( const QString &path );

};
//===========================================================

class FileStatusList : public NPList<FileStatusList>
{
public:
	QString	FileName;
	QFile	*File;
	QIODevice::OpenMode Mode;
	bool	Opened;
	bool	Flushed;
	DWORD	LastAccessTime;

	FileStatusList(void);
	virtual	~FileStatusList(void);
};

//===========================================================
class FileThreadList
{
public:
	int			Command;	//0:File	1:Directory
	QString		FileName;
	QByteArray	Data;
	QIODevice::OpenMode Mode;

	FileThreadList(void);
};

class FileThreadListContainer :  public QThread 
								,public ServiceForLayers 
{
	friend	class FileThreadList;
	friend	class FileThread;
	friend	class DirectoryThread;

	FileThreadList		*FileThreadListDim[MaxBufferedFileList];
	volatile	int		StockedCount;
	int					WPoint;
	int					RPoint;
	volatile	bool	Terminated;
	QMutex	Mutex;

	NPListPack<FileStatusList>	FileStatusContainer;

public:
	FileThreadListContainer(LayersBase *Base);
	virtual	~FileThreadListContainer(void);

	void	SetTerminate(bool b);
	virtual	void	run()	override;

private:
	bool	Append(FileThread *f);
	bool	Append(DirectoryThread *f);
};