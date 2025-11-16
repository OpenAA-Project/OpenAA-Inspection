#ifndef SAVEIMAGEONRECTDIALOG_H
#define SAVEIMAGEONRECTDIALOG_H

#include <QDialog>
#include "ui_SaveImageOnRectDialog.h"

#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "XServiceForLayers.h"

class	DisplayImage;

class SaveImageOnRectDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT
	DisplayImage	*ImageBase;

public:
	SaveImageOnRectDialog(DisplayImage *Base,QWidget *parent);
	~SaveImageOnRectDialog();

private:
	Ui::SaveImageOnRectDialogClass ui;

private slots:
	void on_pushButton_2_clicked();
	void on_pushButtonOK_clicked();
	void on_pushButtonTest_clicked();
};

#endif // SAVEIMAGEONRECTDIALOG_H
