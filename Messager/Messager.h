#ifndef MESSAGER_H
#define MESSAGER_H

#include <QMainWindow>
#include "ui_Messager.h"
#include "NList.h"
#include <QTcpServer>
#include <QTcpSocket>
#include "XDateTime.h"
#include <QFile>
#include "PopupWindow.h"
#include "DiskReporterForm.h"
#include "XServiceForLayers.h"

class	MStringList : public NPList<MStringList>
{
public:
	QString		Msg;
	XDateTime	EventTime;

	MStringList(void);
};

class Messager : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	QTcpServer	SockServer;
	NPListPack<MStringList>	MStringData;
	NPListPack<MStringList>	MStringDataGeneral;
	QString		LogFileName;

public:
	PopupWindow			*PopupW;
	DiskReporterForm	*PopDiskReporter;

	Messager(LayersBase *base,int Port,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~Messager();

	void	PutMessage(int TypeValue,int GlobalPage,const QString &MessageStr);
	void	PutMessage(int GlobalPage,const QString &MessageStr);

private:
	Ui::MessagerClass ui;
	void	WriteLog(int GlobalPage,const QString &MessageStr);
	void	WriteLog(int TypeValue,int GlobalPage,const QString &MessageStr);
	void	WriteLog(QFile &FL,const QString &MessageStr);

private slots:
	void on_pushButtonClose_clicked();
	void on_pushButtonSequence_clicked();
	void SlotNewConnection();
};

class	MessagePopper : public QObject
{
	Q_OBJECT
public:
	QTcpSocket	*Sv;
	Messager	*Parent;

	MessagePopper(Messager *parent){	Sv=NULL;	Parent=parent;	}

private slots:
	void	SlotReadyRead();
	void	SlotDisconnected();
};


#endif // MESSAGER_H
