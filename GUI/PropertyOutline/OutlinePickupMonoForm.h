#ifndef OUTLINEPICKUPMONOFORM_H
#define OUTLINEPICKUPMONOFORM_H

#include <QDialog>
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

namespace Ui {
class OutlinePickupMonoForm;
}
class	OutlineImagePanel;

class OutlinePickupMonoForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit OutlinePickupMonoForm(FlexArea& area, OutlineImagePanel* parentPanel, int pickupL, int pickupH, QWidget *parent = 0);
    ~OutlinePickupMonoForm();

	mtLineGraph						LGraph;
	mtGStick						GraphColMaster;
	mtGStick						GraphThresh;
	FlexArea						GlobalArea;
	OutlineImagePanel* ParentPanel;
	int								PickupL;
	int								PickupH;

	void	GetDataFromWindow(void);
	void	GetHistogramData(void);
	void	ShowThreshold(void);

	void	Initial(AlgorithmBase* InstBase, AlgorithmItemIndependentPack& Data);
	void	Reflect(int PickupL, int PickupH);

private slots:
    void on_EditPickupL_valueChanged(int arg1);
    void on_EditPickupH_valueChanged(int arg1);
    void on_ButtonReflect_clicked();
    void on_ButtonClose_clicked();
	void	SlotLineGraphDClick(int, int);
private:
    Ui::OutlinePickupMonoForm *ui;
	int	MaxY;
};

#endif // OUTLINEPICKUPMONOFORM_H
