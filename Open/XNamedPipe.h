#if	!defined(XNamePipe_H)
#define	XNamePipe_H

#include <QObject>
#include <QLocalSocket>
#include <QLocalServer>

class	WatchdogInProgram;

class	WatchdogInstance : public QObject
{
	Q_OBJECT

	WatchdogInProgram	*Parent;
	QLocalSocket	*Socket;
public:
	WatchdogInstance(WatchdogInProgram *parent ,QLocalSocket *s);

private slots:
	void	SlotReadyRead();
};


class	WatchdogInProgram : public QLocalServer
{
	Q_OBJECT
public:
	WatchdogInProgram ( QObject * parent = 0 );

	void	Start(void);
private slots:
	void	SlotNewConnection ();

};




#endif