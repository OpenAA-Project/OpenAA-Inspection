#ifndef SHOWTOTALHISTGRAMGRAPHFORM_H
#define SHOWTOTALHISTGRAMGRAPHFORM_H

#include <QDialog>
#include "XShowHistgramTotalPacket.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

namespace Ui {
    class ShowTotalHistgramGraphForm;
}

class ShowTotalHistgramGraphForm : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
	HistgramTypeList	HistPoint;
	LibraryItemList		LibPoint;
	HistStepClass		GraphData;
	double	ThresholdA,ThresholdB;

	mtLineGraph			LGraph;
	mtGStick			GraphHistgram;
	mtGStick			GraphThresh;

	double				Average;
	double				Dispersion;

public:
    explicit ShowTotalHistgramGraphForm(HistgramTypeList &PointH ,LibraryItemList &PointL,LayersBase *base,QWidget *parent = 0);
    ~ShowTotalHistgramGraphForm();

private slots:
    void on_pushButtonCalc2_clicked();
    void on_pushButtonClose_clicked();
	void	SlotLineGraphDClick(int X,int Y);
    void on_pushButtonCalc_clicked();
    void on_pushButtonCalcD_clicked();
    void on_pushButtonCalcU_clicked();

private:
    Ui::ShowTotalHistgramGraphForm *ui;

	void Initial(void);
	void ShowGrah(void);
	void ShowCalculated(void);
};

#endif // SHOWTOTALHISTGRAMGRAPHFORM_H
