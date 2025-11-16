#if	!defined(XSingleExecuteBySocket_h)
#define	XSingleExecuteBySocket_h

#include <QLocalServer>
#include <QLocalSocket>
#include <QString>
#include <QObject>

class	CheckSingleExecution : public QObject
{
	Q_OBJECT

	QLocalServer	Server;
	QLocalSocket	Client;
	QLocalSocket	*ClientInServer;
	QString	IdentifiedName;

public:
	CheckSingleExecution(const QString &IdentifiedName,QObject *parent);
	~CheckSingleExecution(void);

	bool	CheckDoubleBoot(void);
	bool	RequireTerminate(void);

public slots:
	void	SlotNewConnection ();
	void	SlotReadyReadInServer();
signals:
	void	SignalTerminateFromOther();
};

class	ClassSingleExecution
{
	CheckSingleExecution	Execution;
public:
	explicit	ClassSingleExecution(QObject *parent);
};


#endif
