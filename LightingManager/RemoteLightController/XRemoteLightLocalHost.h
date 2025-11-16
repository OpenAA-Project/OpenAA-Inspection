#if	!defined(XRemoteLightLocalHost_H)
#define	XRemoteLightLocalHost_H

#include <QLocalSocket>
#include <QLocalServer>
#include <QObject>
#include "XTypeDef.h"

class	FromProgram;
class	RemoteLightController;

class	FromProgramInstance : public QObject
{
	Q_OBJECT

	FromProgram	*Parent;
	QLocalSocket	*Socket;
public:
	FromProgramInstance(FromProgram *parent ,QLocalSocket *s);

signals:
	void	SignalLightID(int lightID);
	void	SignalLightON(bool lightON);
	void	SignalLightRequest();

private slots:
	void	SlotReadyRead();
};

class	FromProgram : public QLocalServer
{
	Q_OBJECT
	RemoteLightController	*RParent;
public:
	BYTE					*ReqData;
	int						ReqDataLength;
public:
	FromProgram ( RemoteLightController * parent = 0 );
	~FromProgram(void);

	void	Start(void);
private slots:
	void	SlotNewConnection ();
	void	SlotLightID(int lightID);
	void	SlotLightON(bool lightON);
	void	SlotLightRequest();
};

#endif