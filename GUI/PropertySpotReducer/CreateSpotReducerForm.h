#ifndef CREATESPOTREDUCERFORM_H
#define CREATESPOTREDUCERFORM_H

#include <QDialog>
#include "ui_CreateSpotReducerForm.h"
#include "XServiceForLayers.h"

class CreateSpotReducerForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	CreateSpotReducerForm(LayersBase *base, QWidget *parent = 0);
	~CreateSpotReducerForm();

	int		SpotBrightness;
	double	ReductionLevel;
	int		SpotArea;
	int		SpotCount;

private:
	Ui::CreateSpotReducerFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // CREATESPOTREDUCERFORM_H
