#ifndef TRIGGERCONTROLLER_H
#define TRIGGERCONTROLLER_H

#include <QMainWindow>
#include "ui_TriggerController.h"

class TriggerController : public QMainWindow
{
	Q_OBJECT

public:
	TriggerController(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~TriggerController();

private slots:
    void on_pushButtonReceiveEIO_clicked();

    void on_pushButtonSendFrameTrigger_clicked();

    void on_toolButtonFlapOK_clicked();

    void on_toolButtonFlapNG_clicked();

    void on_pushButtonSaveSetting_clicked();

    void on_pushButtonReset_clicked();

private:
	Ui::TriggerControllerClass ui;
};

#endif // TRIGGERCONTROLLER_H
