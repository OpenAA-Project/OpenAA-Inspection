#ifndef PIODEVICER_H
#define PIODEVICER_H

#include <QMainWindow>
#include <QTimer>
#include <QTcpSocket>
#include <QTcpServer>

#include "ui_PIODevicer.h"
#include "XTypeDef.h"

class PIODevicer;

class	ClientSocket : public QObject
{
	Q_OBJECT
		
	PIODevicer	*Parent;
	QTcpSocket	*Client;
public:
	ClientSocket(PIODevicer *parent);

	void	SetClient(QTcpSocket *client);
	bool	Send(BYTE *data,int len);

public slots:
	void	Disconnected();
	void	ReadyRead ();
};


class PIODevicer : public QMainWindow
{
	Q_OBJECT
	QTcpServer	Server;
	QTimer		TM;

	ClientSocket	*Client[1000];

	int		InportBitCount;
	int		OutportBitCount;
	BYTE	InData[16];

	short BoardId;
	bool	CameNew;

public:
	PIODevicer(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~PIODevicer();

	void	DeleteClient(ClientSocket *c);

	void	OutPort(int port ,BYTE data);
	void	InPort(int port ,BYTE &data);
	void	OutPort(BYTE data[]);

private:
	Ui::PIODevicerClass ui;

public slots:
	void NewConnection ();
	void TimeOut ();
};

#endif // PIODEVICER_H
