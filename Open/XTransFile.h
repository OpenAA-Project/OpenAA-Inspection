#if	!defined(XTransFile_h)
#define	XTransFile_h

#include <QIODevice>
#include "XTransSocket.h"
#include "XDateTime.h"
#include "XTypeDef.h"
#include "NList.h"
#include <QThread>


#define	CMD_Constructor				1
#define	CMD_bytesAvailable			2
#define	CMD_bytesToWrite			3
#define	CMD_canReadLine				4
#define	CMD_close					5
#define	CMD_isSequential			6
#define	CMD_open					7
#define	CMD_pos						8
#define	CMD_reset					9
#define	CMD_seek					10
#define	CMD_size					11
#define	CMD_waitForBytesWritten		12
#define	CMD_waitForReadyRead		13
#define	CMD_readData				14
#define	CMD_readLineData			15
#define	CMD_writeData				16
#define	CMD_atEnd					17
#define	CMD_remove					18
#define	CMD_rename					19
#define	CMD_resize					20
#define	CMD_exists					21
#define	CMD_filename				22
#define	CMD_flush					23

class	TrFile;
class	TrFileSocket;
const	int	SWFifoSize=16384;

class	SWFifoContainer
{
	BYTE	*Buffer;
	int		CurrentPointer;
public:
	TrFile			*Parent;

	SWFifoContainer(TrFile	*parent);
	SWFifoContainer(const SWFifoContainer &src);
	~SWFifoContainer(void);

	int		GetCurrentSize(void){	return CurrentPointer;	}

	SWFifoContainer &operator=(const SWFifoContainer &src);
	int		Push(BYTE *s ,int size);
	void	ForceWrite(void);
};

class	TrFileSocket : public TrSocketClient
{
    Q_OBJECT

	TrFile	*Parent;
public:
	TrFileSocket(TrFile *parent);

	BYTE	RootCmd;
	bool3	Ack;
	bool	AckBool;
	int		AckID;
	qint64	RetBytesAvailable;
	qint64	AckPos;
	qint64	AckSize;
	qint64	WAckSize;
	char	*ReadPointer;
	QString	AckFileName;
private slots:
	void	SlotReceived(int);
};


class	TrFile : public QIODevice
{
	TrFileSocket	*Sock;
	mutable	SWFifoContainer	WFifo;
	mutable	QMutex	AccessSock;

public:
	TrFile(const QString &FileName
		, const QString &TransFileHost="127.1.1.1"
		, int TransFilePort=15700);
	virtual	~TrFile(void);

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


	qint64	RWriteData(char *Point ,int Size);

protected:
	virtual qint64 readData ( char * data, qint64 maxSize );
	virtual qint64 readLineData ( char * data, qint64 maxSize );
	virtual qint64 writeData ( const char * data, qint64 maxSize );
};


#endif