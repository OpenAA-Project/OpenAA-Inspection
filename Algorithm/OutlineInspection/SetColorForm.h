#ifndef SETCOLORFORM_H
#define SETCOLORFORM_H

#include <QDialog>
#include "ui_SetColorForm.h"
#include "ShowRGBSamples.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XServiceForLayers.h"

class	RGBStock;

class SetColorForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT
	SelectColorSample	RegistPanel;
	ShowRGBSpace		ColorPanel;
public:
	SetColorForm(ColorLogic &data ,LayersBase *Base,QWidget *parent = 0);
	~SetColorForm();

	ColorLogic	Col;
private:
	Ui::SetColorFormClass ui;
	void	SlotSelectCData();
	void	SlotBeforeSave();

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // SETCOLORFORM_H
