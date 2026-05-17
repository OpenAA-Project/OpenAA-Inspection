#ifndef SETAREACOLORDIALOG_H
#define SETAREACOLORDIALOG_H

#include <QDialog>
#include "ui_SetAreaColorDialog.h"
#include "XServiceForLayers.h"

class	LayersBase;
class	FlexArea;
class	RGBStock;

class SetAreaColorDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SetAreaColorDialog(RGBStock &PickupColor ,FlexArea &Area
						,LayersBase *Base,QWidget *parent = 0);
	~SetAreaColorDialog();

private:
	Ui::SetAreaColorDialogClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonAdd_clicked();
	void on_pushButtonReplace_clicked();
};

#endif // SETAREACOLORDIALOG_H
