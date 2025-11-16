#ifndef BOOTER_H
#define BOOTER_H

#include <QMainWindow>
#include "ui_Booter.h"
#include "XSocketClient.h"
#include "NListComp.h"
#include "XBooter.h"

class	Booter;

class	ConnectionList : public SocketClient
{
	Q_OBJECT

public:
	QString		AccessName;
	QString		IPAddress;
	int			PortNumber;

	ConnectionList(QObject *parent=NULL);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	bool	OpenConnection(void);
	bool	IsOpenConnection(void);
	bool	SendOK(void);

public slots:
	void	SlotReceived(int);
};

class	ConnectionContainer : public NPListPack<SocketClient>
{
	Booter	*Parent;
public:
	ConnectionContainer(Booter *parent):Parent(parent){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	BooterServer : public SocketServer
{
};

class Booter : public QMainWindow
{
	Q_OBJECT

public:
	SocketServer		Server;
	ConnectionContainer	Connections;
	QString				SettingFileName;
	BooterParameter		BooterData;

	Booter(const QString &settingFile ,int OpePort ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~Booter();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonSetting_clicked();

private:
	Ui::BooterClass ui;
};

#define	CmdOK	0x10

#endif // BOOTER_H
