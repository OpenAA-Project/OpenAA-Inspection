#ifndef TRANSFILESERVER_H
#define TRANSFILESERVER_H

#include <QMainWindow>
#include "ui_TransFileServer.h"
#include "XTransSocket.h"
#include <QFile>
#include "XNamedPipe.h"

class	TrAppServer;
class	TrAppSocket;
class	TransFileServer;



class	TrFileApp : public QFile
{
public:
	TrFileApp(const QString &filename);

	virtual qint64 bytesAvailable () const;
	virtual qint64 bytesToWrite () const;
	
	virtual bool canReadLine () const;
	virtual void close ();
	virtual bool isSequential () const;
	virtual bool open ( OpenMode mode );
	virtual qint64 pos () const;
	virtual bool reset ();
	virtual bool seek ( qint64 pos );
	virtual qint64 size () const;
	virtual bool waitForBytesWritten ( int msecs );
	virtual bool waitForReadyRead ( int msecs );

	virtual qint64 readData ( char * data, qint64 maxSize );
	virtual qint64 readLineData ( char * data, qint64 maxSize );
	virtual qint64 writeData ( const char * data, qint64 maxSize );

};

class	QWFifo : public NPList<QWFifo>
{
	char	DimBuff[256];
public:
	char	*MemPoint;
	int		MemSize;

	QWFifo(char *buff, int size);
	virtual	~QWFifo(void);
};

class	QWFifoContainer : public QThread ,public NPListPack<QWFifo>
{
	QMutex	Mutex;
public:
	volatile	bool	Terminated;
	TrAppServer	*Parent;
	TrAppSocket	*Sock;

	QWFifoContainer(TrAppSocket *sock ,TrAppServer	*parent);

	virtual void run ();

	QWFifo	*Pop(void);
	void	Push(QWFifo *v);
	bool	Exist(void);
};


class	TrAppSocket : public TrSocketClient
{
    Q_OBJECT

public:
	TrAppServer	*Parent;
private:
	int32		ID;
	QString		RealFileName;
	QString		CachedFileName;
	TrFileApp	*RealFile;
	TrFileApp	*CachedFile;
	bool		RealExist;
	bool		CacheExist;
	bool		SameAsCache;
	int			LogTurn;
	QWFifoContainer	WFifo;
public:
	TrAppSocket(TrAppServer *parent);
	~TrAppSocket(void);

	void	PutLog(int ResultServerID ,const QString &Message ,const QString &Value);
	bool	WriteData(char *Point ,int Size);
private slots:
	void	SlotReceived(int);
signals:
	void	SignalPutLog(const QString &PartnerIP ,int ResultServerID ,const QString &Message ,const QString &Value);
};

class	TrAppServer : public TrSocketServer
{
    Q_OBJECT

	int		BaseID;
	TransFileServer	*Parent;
public:
	TrAppServer(TransFileServer * parent);
	virtual	TrAppSocket	*NewSocket(void);

	int		GetMaxID(void);
	QString	GetChachePath(void);
private slots:
	void	SlotPutLog(const QString &PartnerIP ,int ResultServerID ,const QString &Message ,const QString &Value);
};


class TransFileServer : public QMainWindow
{
	Q_OBJECT

	TrAppServer	TrServer;
	bool LogMode;
	int ServerPort;
	WatchdogInProgram	WDog;
public:
	TransFileServer(bool _LogMode 
					,int ServerPort
					,const QString &CachePath
					,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~TransFileServer();

	QString	CachePath;
	void	PutLog(const QString &PartnerIP ,int ResultServerID ,const QString &Message ,const QString &Value);
private:
	Ui::TransFileServerClass ui;
};

#endif // TRANSFILESERVER_H
