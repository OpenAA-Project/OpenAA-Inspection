#include <cmath>
#include "DFSLibrary.h"
#include "XDFSClient.h"
#include <QFileInfo>
#include <QApplication>
#include "XGeneralFunc.h"
#include "XForWindows.h"

DFSGate::DFSGate(const QString &FileName
			,QObject *parent,const QString &IPAddress,int PortNumber)
{
	Client=new DFSClient(parent,IPAddress,PortNumber);

	QFileInfo	FInfo(FileName);
	QString	RelativePath=FInfo.filePath();

	QBuffer		PathBuff;
	PathBuff.open(QIODevice::WriteOnly);
	::Save(&PathBuff,RelativePath);
	::Save(&PathBuff,FInfo.fileName());
	Client->SetReceived(false);
	Client->Send(DFSCmd_ReqFindFile,PathBuff.buffer());
	while(Client->IsReceived()==false){
		QApplication::processEvents();
	}
	CurrentInfo	=Client->CurrentInfo;

	File=new QFile(CurrentInfo.NetworkPath+::GetSeparator()+CurrentInfo.FileName);
}

DFSGate::~DFSGate(void)
{
	delete	File;
	File=NULL;
	delete	Client;
	Client=NULL;
}

qint64 DFSGate::bytesAvailable () const
{
	return File->bytesAvailable ();
}
qint64 DFSGate::bytesToWrite () const
{
	return File->bytesToWrite ();
}
	
bool DFSGate::canReadLine () const
{
	return File->canReadLine ();
}
void DFSGate::close ()
{
	File->close();
}
bool DFSGate::isSequential () const
{
	return File->isSequential ();
}
bool DFSGate::open ( OpenMode mode )
{
	return File->open (mode);
}
	//virtual qint64 pos () const;
bool DFSGate::reset ()
{
	return File->reset ();
}
	//virtual bool seek ( qint64 pos );
qint64 DFSGate::size () const
{
	return File->size ();
}
bool DFSGate::waitForBytesWritten ( int msecs )
{
	return File->waitForBytesWritten (msecs);
}
bool DFSGate::waitForReadyRead ( int msecs )
{
	return File->waitForReadyRead (msecs);
}
	
bool DFSGate::atEnd () const
{
	return File->atEnd ();
}

bool DFSGate::remove ()
{
	return File->remove ();
}
bool DFSGate::rename ( const QString & newName )
{
	return File->rename (newName);
}
bool DFSGate::resize ( qint64 sz )
{
	return File->resize (sz);
}
bool DFSGate::exists () const
{
	return File->exists ();
}
QString DFSGate::fileName () const
{
	return File->fileName ();
}
bool DFSGate::flush ()
{
	return File->flush ();
}

qint64 DFSGate::readData ( char * data, qint64 maxSize )
{
	return File->read( data, maxSize );
}

qint64 DFSGate::readLineData ( char * data, qint64 maxSize )
{
	return File->read( data, maxSize );
}

qint64 DFSGate::writeData ( const char * data, qint64 maxSize )
{
	return File->write( data, maxSize );
}


bool	DFSGate::MtCopyFileFrom	(const QString &DFSSourceFilePath , const QString &DestFilePath
									,QObject *parent,const QString &IPAddress,int PortNumber)
{
	DFSClient	Client(parent,IPAddress,PortNumber);

	QFileInfo	FInfo(DFSSourceFilePath);
	QString	RelativePath=FInfo.filePath();

	QBuffer		PathBuff;
	PathBuff.open(QIODevice::WriteOnly);
	::Save(&PathBuff,RelativePath);
	::Save(&PathBuff,FInfo.fileName());
	Client.SetReceived(false);
	Client.Send(DFSCmd_ReqFindFile,PathBuff.buffer());
	while(Client.IsReceived()==false){
		QApplication::processEvents();
	}
	QString	SourceFileName	=Client.CurrentInfo.NetworkPath+::GetSeparator()+FInfo.fileName();
	QString	DestFileName	=DestFilePath;
	return ::MTCopyFile(SourceFileName ,DestFileName ,false);
}

bool	DFSGate::MtCopyFileTo	(const QString &SourceFilePath , const QString &DFSDestFilePath
									,QObject *parent,const QString &IPAddress,int PortNumber)
{
	DFSClient	Socket(parent,IPAddress,PortNumber);

	FileSaveAttr	A;
	QFileInfo	DFInfo(DFSDestFilePath);
	QFileInfo	SFInfo(SourceFilePath);
	A.SourcePath		=SFInfo.absolutePath();
	A.FileName			=DFInfo.fileName();
	A.DestRelativePath	=DFInfo.filePath();
	A.FileSize			=DFInfo.size();
	A.FileStamp			=DFInfo.lastModified();

	QBuffer		PathBuff;
	PathBuff.open(QIODevice::WriteOnly);
	A.Save(&PathBuff);
	Socket.SetReceived(false);
	Socket.Send(DFSCmd_ReqSaveFile,PathBuff.buffer());
	while(Socket.IsReceived()==false){
		QApplication::processEvents();
	}
	QString	DestFileName=Socket.DestNetwordFolder 
						+::GetSeparator()
						+A.DestRelativePath
						+::GetSeparator()
						+A.FileName;
	return ::MTCopyFile(SourceFilePath ,DestFileName ,false);
}

