#if	!defined(XWatchdogRebooter_h)
#define	XWatchdogRebooter_h

#include "NListComp.h"
#include <QIODevice.h>
#include <QLocalSocket>
#include "XDateTime.h"

class	WatchdogPack;

class	WatchdogTarget : public QObject ,public NPListSaveLoad<WatchdogTarget>
{
	Q_OBJECT

	WatchdogPack	*Parent;
	qint64			PID;
	QLocalSocket	*Sock;
	QString			ArgStr;
public:
	QString		PathFileName;
	QString		Arguments;
	QString		WorkingPath;
	int			WatchTerm;
	XDateTime	LastAccessed;

	WatchdogTarget(WatchdogPack *p,QObject * parent=0);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	bool	StartUp(void);
	int		GetPID(void)	{	return PID;	}
	bool	IsAlive(void);
	void	TimerFunc(void);
	void	Kill(void);
	bool	IsOpen(void);
	bool	IsConnected(void);
	bool	TryConnection(DWORD ProcessID);

	WatchdogTarget	&operator=(WatchdogTarget &src);
private:
	bool	SearchProcess(void);

signals:
	void	SignalShow();
	void	SignalWatchdogEvent(const QString &ErrorType,const QString &FileName ,int pid);
private slots:
	
	void SlotReadyRead ();

};


class	WatchdogPack : public QObject ,public NPListPackSaveLoad<WatchdogTarget>
{
	Q_OBJECT
public:
	WatchdogPack(void){}

	virtual	WatchdogTarget	*Create(void);

signals:
	void	SignalShow();
	void	SignalWatchdogEvent(const QString &ErrorType,const QString &FileName ,int pid);

private slots:
	void	SlotShow();
	void	SlotWatchdogEvent(const QString &ErrorType,const QString &FileName ,int pid);
};


#endif