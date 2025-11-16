#ifndef VIRTUALPIOSERVER_H
#define VIRTUALPIOSERVER_H

#include <QMainWindow>
#include "ui_VirtualPIOServer.h"
#include <QWidget>
#include <QTimer>
#include "XVirtualPIOServer.h"
#include "XVirtualPIODirectAccess.h"



class VirtualPIOServer : public QMainWindow
{
	Q_OBJECT

	PIOServer	Server;
	QTimer	Timer;
	XVirtualPIODirectAccessServer	DirectAccessServer;
	QTimer	DirectAccessTimer;
public:
	VirtualPIOServer(int PortNumber ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~VirtualPIOServer();

private:
	Ui::VirtualPIOServerClass ui;

private slots:
	void	SlotTimeout();
	void	SlotDirectAccessTimeout();
	void	SlotStructureChanged();
    void on_listWidgetClientList_clicked(const QModelIndex &index);
};

#endif // VIRTUALPIOSERVER_H
