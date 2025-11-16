#ifndef PICKUPMONOFORM_H
#define PICKUPMONOFORM_H

#include <QDialog>
#include "ui_PickupMonoForm.h"
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XServiceForLayers.h"
#include "XDynamicClassifyPacket.h"

class PickupMonoForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	PickupMonoForm(LayersBase *Base,FlexArea &area 
					,int pickupL,int pickupH
					,QWidget *parent = 0);
	~PickupMonoForm();

	mtLineGraph						LGraph;
//	mtGLine							GraphColMaster[100];
	mtGStick						GraphColMaster[100];
	mtGStick						GraphThresh;
	FlexArea						GlobalArea;
	int								PickupL;
	int								PickupH;

	void	GetDataFromWindow(void);
	void	GetHistogramData(void);
	void	ShowThreshold(void);

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	Reflect(int PickupL ,int PickupH);

private:
	Ui::PickupMonoFormClass ui;
	int	MaxY;


private slots:
	void on_EditPickupH_valueChanged(int);
	void on_EditPickupL_valueChanged(int);
	void on_ButtonClose_clicked();
	void on_ButtonReflect_clicked();
	void	SlotLineGraphDClick(int ,int );
};

#endif // PICKUPMONOFORM_H
