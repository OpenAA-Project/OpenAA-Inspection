#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include <QDialog>
#include "ui_StartupDialog.h"
#include "XServiceForLayers.h"

class StartupDialog : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	StartupDialog(LayersBase *Base,QWidget *parent = 0);
	~StartupDialog();

private:
	Ui::StartupDialogClass ui;

private slots:
	void on_pushButtonOK_clicked();
};

#endif // STARTUPDIALOG_H
