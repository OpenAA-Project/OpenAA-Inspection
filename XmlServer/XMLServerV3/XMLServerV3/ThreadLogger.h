#if	!defined(THREADLOGGER_H)
#define	THREADLOGGER_H

#include <QThread>
#include "XDateTime.h"
#include <QStringList>
#include <QMutex>
#include "XTypeDef.h"
#include "NList.h"

class	ThreadLogger;
class	XMLServerComm;

class	LogLeaf : public NPList<LogLeaf>
{
	ThreadLogger	*Parent;
	XDateTime		CurrentTime;
	int				OpeCode;
	QStringList		Messages;
	bool			Result;

public:
	LogLeaf(ThreadLogger *parent);

	bool	WriteLog(void);
	void	SetLog(int OpeCode ,QStringList &Msg,bool Result);
private:
	QString	GetFileName(void);
};

class ThreadLogger : public QThread
{
	Q_OBJECT
	XMLServerComm		*Parent;
	volatile	bool	CloseMode;

	NPListPack<LogLeaf>	LogQueue;
	QMutex				LogMutex;
public:
	ThreadLogger(XMLServerComm * parent);

	void run();
	XMLServerComm	*GetParent(void)	{	return Parent;	}
	void	Close(void);
	void	AddLog(int OpeCode ,QStringList &Msg);
	void	AddLog(int OpeCode ,QStringList &Msg,bool Result);
};

#endif