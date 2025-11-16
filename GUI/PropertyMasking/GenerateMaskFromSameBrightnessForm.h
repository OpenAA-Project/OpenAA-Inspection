#ifndef GENERATEMASKFROMSAMEBRIGHTNESSFORM_H
#define GENERATEMASKFROMSAMEBRIGHTNESSFORM_H

#include <QDialog>
#include "ui_GenerateMaskFromSameBrightnessForm.h"
#include "mtColorFrame.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"


class GenerateMaskFromSameBrightnessForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	GenerateMaskFromSameBrightnessForm(LayersBase *Base,QWidget *parent = 0);
	~GenerateMaskFromSameBrightnessForm();

	int		PickupL;
	int		PickupH;
	bool	Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	int		MinPickupSize;
	int		MaxPickupSize;
	int		MinPickupDots;
	int		MaxPickupDots;
	int		Erosion;

private:
	Ui::GenerateMaskFromSameBrightnessFormClass ui;

	void GetParamFromWindow(void);
	void SetParamToWindow(void);

private slots:
	void on_pushButtonLimited_clicked();
	void on_pushButton_clicked();
	void on_ButtonCancel_clicked();
	void on_ButtonNotEffective_clicked();
	void on_ButtonEffective_clicked();
};

#endif // GENERATEMASKFROMSAMEBRIGHTNESSFORM_H
