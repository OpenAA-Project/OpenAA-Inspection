#ifndef FORCEREBOOTER_H
#define FORCEREBOOTER_H

#include <QMainWindow>
#include "ui_ForceRebooter.h"
#include "XForceRebooter.h"

class ForceRebooter : public QMainWindow
{
	Q_OBJECT

public:
	ForceRebooter(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ForceRebooter();

	RebooterServer	Executer;

private slots:
    void on_pushButtonRebootPrograms_clicked();
    void on_pushButtonRebootPC_clicked();
    void on_pushButtonSetting_clicked();
    void on_pushButtonShutdownPC_clicked();

private:
	Ui::ForceRebooterClass ui;
};

#endif // FORCEREBOOTER_H
