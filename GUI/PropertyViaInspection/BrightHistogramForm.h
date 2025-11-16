#ifndef BRIGHTHISTOGRAMFORM_H
#define BRIGHTHISTOGRAMFORM_H

#include <QDialog>
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

class	VIAInspectionImagePanel;
namespace Ui {
class BrightHistogramForm;
}

class BrightHistogramForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit BrightHistogramForm(FlexArea &area ,VIAInspectionImagePanel *parentPanel ,int pickupL,int pickupH,QWidget *parent = 0);
    ~BrightHistogramForm();
    
	mtLineGraph						LGraph;
//	mtGLine							GraphColMaster[100];
	mtGStick						GraphColMaster[100];
	mtGStick						GraphThresh;
	FlexArea						GlobalArea;
	VIAInspectionImagePanel			*ParentPanel;
	int								PickupL;
	int								PickupH;

	void	GetDataFromWindow(void);
	void	GetHistogramData(void);
	void	ShowThreshold(void);

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	Reflect(int PickupL ,int PickupH);

private slots:
    void on_ButtonReflect_clicked();
    void on_ButtonClose_clicked();
    void on_EditPickupL_valueChanged(int arg1);
    void on_EditPickupH_valueChanged(int arg1);
	void	SlotLineGraphDClick(int ,int );

private:
    Ui::BrightHistogramForm *ui;

	int	MaxY;
};

#endif // BRIGHTHISTOGRAMFORM_H
