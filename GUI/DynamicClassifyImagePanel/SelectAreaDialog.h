#ifndef SELECTAREADIALOG_H
#define SELECTAREADIALOG_H

#include <QDialog>
#include "ui_SelectAreaDialog.h"
#include "XDynamicClassify.h"

class SelectAreaDialog : public QDialog
{
	Q_OBJECT

public:
	SelectAreaDialog(QWidget *parent = 0);
	~SelectAreaDialog();

	SelectAreaMode	Mode;

private:
	Ui::SelectAreaDialogClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonCopy_clicked();
};

#endif // SELECTAREADIALOG_H
