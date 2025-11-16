#ifndef CHANGESERVER_H
#define CHANGESERVER_H

#include <QMainWindow>
#include "ui_ChangeServer.h"
#include "XChangeServer.h"

class ChangeServer : public QMainWindow
{
	Q_OBJECT

public:
	ChangeServer(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ChangeServer();

	ChangeServerContainer	ServerContainer;

	void	ShowCurrent(void);
	void	ShowGrid(void);
	bool	SaveContainer(void);

private:
	Ui::ChangeServerClass ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButtonEdit_clicked();
	void on_pushButtonSelect_clicked();
	void on_tableWidgetServers_doubleClicked(QModelIndex);
};

#endif // CHANGESERVER_H
