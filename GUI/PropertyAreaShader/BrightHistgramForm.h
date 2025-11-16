#ifndef BRIGHTHISTGRAMFORM_H
#define BRIGHTHISTGRAMFORM_H

#include <QDialog>
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

namespace Ui {
    class BrightHistgramForm;
}

class	AreaShaderImagePanel;

class BrightHistgramForm : public QDialog
{
    Q_OBJECT

public:
    explicit BrightHistgramForm(FlexArea &area ,AreaShaderImagePanel *parentPanel ,int pickupL,int pickupH,QWidget *parent = 0);
    ~BrightHistgramForm();

	mtLineGraph						LGraph;
//	mtGLine							GraphColMaster[100];
	mtGStick						GraphColMaster[100];
	mtGStick						GraphThresh;
	FlexArea						GlobalArea;
	AreaShaderImagePanel			*ParentPanel;
	int								PickupL;
	int								PickupH;

	void	GetDataFromWindow(void);
	void	GetHistogramData(void);
	void	ShowThreshold(void);

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	Reflect(int PickupL ,int PickupH);

private slots:
    void on_EditPickupL_valueChanged(int arg1);
    void on_EditPickupH_valueChanged(int arg1);
    void on_ButtonReflect_clicked();
    void on_ButtonClose_clicked();
	void	SlotLineGraphDClick(int ,int );

private:
    Ui::BrightHistgramForm *ui;

	int	MaxY;
};

#endif // BRIGHTHISTGRAMFORM_H
