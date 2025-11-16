#ifndef EULERRINGL1PICKUPDIALOG_H
#define EULERRINGL1PICKUPDIALOG_H

#include <QDialog>
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

namespace Ui {
class EulerRingL1PickupDialog;
}
class	EulerRingL1ImagePanel;

class EulerRingL1PickupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EulerRingL1PickupDialog(FlexArea &area ,EulerRingL1ImagePanel *parentPanel ,int pickupL,int pickupH,QWidget *parent = 0);
    ~EulerRingL1PickupDialog();

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
    void on_EditPickupL_valueChanged(int arg1);
    void on_EditPickupH_valueChanged(int arg1);
	void	SlotLineGraphDClick(int ,int );
private:
    Ui::EulerRingL1PickupDialog *ui;
	int	MaxY;
};

#endif // EULERRINGL1PICKUPDIALOG_H
