#ifndef EULERRINGL1PICKUPFORM_H
#define EULERRINGL1PICKUPFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

namespace Ui {
class EulerRingL1PickupForm;
}
class	EulerRingL1ImagePanel;

class EulerRingL1PickupForm : public QWidget
{
    Q_OBJECT

public:
    explicit EulerRingL1PickupForm(FlexArea &area ,EulerRingL1ImagePanel *parentPanel ,int pickupL,int pickupH,QWidget *parent = 0);
    ~EulerRingL1PickupForm();

	mtLineGraph						LGraph;
	mtGStick						GraphColMaster[100];
	mtGStick						GraphThresh;
	FlexArea						GlobalArea;
	EulerRingL1ImagePanel			*ParentPanel;
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
	void	SlotLineGraphDClick(int ,int );
    void on_EditPickupL_valueChanged(int arg1);
    void on_EditPickupH_valueChanged(int arg1);

private:
    Ui::EulerRingL1PickupForm *ui;

	int	MaxY;
};

#endif // EULERRINGL1PICKUPFORM_H
