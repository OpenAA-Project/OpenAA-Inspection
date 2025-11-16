#ifndef REMOTELIGHTEXECUTER_H
#define REMOTELIGHTEXECUTER_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include "ui_RemoteLightExecuter.h"
#include "XSocketClient.h"
#include "XServiceForLayers.h"

class	RemoteLightExecuter;
class	LightAccessList;


class	RemoteLightSocket : public SocketClient,public ServiceForLayers
{
    Q_OBJECT
public:
	RemoteLightExecuter	*Parent;

	RemoteLightSocket(LayersBase *Base ,RemoteLightExecuter *parent);

private slots:
	void	SlotReceived(int);
};

class	RemoteLightServer : public SocketServer,public ServiceForLayers
{
public:
	RemoteLightServer(LayersBase *Base ,QObject * parent);
	virtual	SocketClient	*NewSocket(void);
};


class RemoteLightExecuter : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	QString				DLLPathName;
	RemoteLightServer	SockerServer;

	QSystemTrayIcon		*TrayIcon;
	QMenu				*TrayIconMenu;
	QTimer				TM;
public:
	LightAccessList		*LightPointer;

	RemoteLightExecuter(LayersBase *Base 
						,const QString &DLLFileName ,int PortNumber ,QString &InitialStr
						,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~RemoteLightExecuter();

protected:
	virtual	void	moveEvent ( QMoveEvent * event )		override;
	virtual	void 	resizeEvent ( QResizeEvent * event )	override;
	QString	GetPositionFileName(void)	{	return QString(/**/"RemoteLightExecuterPosition.dat");	}
	void	SavePosition(void);

	virtual	void	closeEvent(QCloseEvent *ev)	override;

private:
	Ui::RemoteLightExecuterClass ui;

	QAction	*minimizeAction;
	QAction	*showAction;
	QAction	*DialogAction;
	QAction	*quitAction;

private slots:
	void	SlotTimeOut();
	void	SlotShowDialog();
};

#endif // REMOTELIGHTEXECUTER_H
