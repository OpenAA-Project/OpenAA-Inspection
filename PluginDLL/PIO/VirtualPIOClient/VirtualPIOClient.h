#ifndef VIRTUALPIOCLIENT_H
#define VIRTUALPIOCLIENT_H

#include <QMainWindow>
#include "ui_VirtualPIOClient.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTimer>
#include <QCloseEvent>
#include "XVirtualPIOClient.h"

class VirtualPIOClient : public QMainWindow
{
	Q_OBJECT

	QAction	*minimizeAction;
	QAction	*showAction;
	QAction	*quitAction;
	QSystemTrayIcon		*TrayIcon;
	QMenu				*TrayIconMenu;
	QTimer				TM;
	QTimer				CommOpe;

	PIOAdapter			Adapter;
	bool				FirstTimeOut;
public:
	VirtualPIOClient(const QString &IPAddress,int PortNumber ,const QString &AccessMemoryName ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~VirtualPIOClient();

	void	ShowGrid(void);
private:
	Ui::VirtualPIOClientClass ui;
	void	closeEvent( QCloseEvent *ev);
	
private slots:
	void	SlotTimeOut();
	void	SlotTimeOutComm();
};

#endif // VIRTUALPIOCLIENT_H
