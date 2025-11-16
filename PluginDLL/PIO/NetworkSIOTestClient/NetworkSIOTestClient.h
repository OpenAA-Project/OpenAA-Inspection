#ifndef NETWORKSIOTESTCLIENT_H
#define NETWORKSIOTESTCLIENT_H

#include <QMainWindow>
#include "ui_NetworkSIOTestClient.h"

class NetworkSIOTestClient : public QMainWindow
{
	Q_OBJECT

public:
	NetworkSIOTestClient(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~NetworkSIOTestClient();

private slots:
    void on_toolButtonOpen_clicked();
    void on_pushButtonTx_clicked();
    void on_pushButtonRx_clicked();

private:
	Ui::NetworkSIOTestClientClass ui;
};

#endif // NETWORKSIOTESTCLIENT_H
