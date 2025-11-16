#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ControllerAccessor.h"
#include <QTcpSocket>
#include <QString>
#include <QWidget>
#include "XControllerHeader.h"

#define	PortNoOfController	17780


class ControllerAccessor : public QMainWindow
{
    Q_OBJECT

	struct ControllerInfo	CInfo;
	QString	AddressOfController;
public:
	QTcpSocket	Socket;

public:
    ControllerAccessor(QWidget *parent = Q_NULLPTR);

private slots:
    void on_pushButtonSend_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonSignal_clicked();

private:
    Ui::ControllerAccessorClass ui;

	void	ShowInfo(void);
	void	GetInfoFromWindow(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
