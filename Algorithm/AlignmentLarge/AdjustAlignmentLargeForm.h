#ifndef ADJUSTALIGNMENTLARGEFORM_H
#define ADJUSTALIGNMENTLARGEFORM_H

#include <QDialog>
#include <QWidget>
#include <QToolBar>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XAlignmentLarge.h"

namespace Ui {
class AdjustAlignmentLargeForm;
}

class AdjustAlignmentLargeForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT
    
    int HistgramPage;

public:
    explicit AdjustAlignmentLargeForm(LayersBase *Base,QWidget *parent = 0);
    ~AdjustAlignmentLargeForm();
    
	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);

	AlgorithmItemIndependentPack	*IData;
	HistgramTypeListInAlgoContainer	HContainer;

private slots:
    void on_pushButtonSetOne_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonHistogramX_clicked();
    void on_pushButtonHistogramY_clicked();
    void on_spinBoxSearchDot_valueChanged(int arg1);
    void on_doubleSpinBoxSearchDotUnit_valueChanged(double arg1);
    void on_spinBoxSearchDotY_valueChanged(int arg1);
    void on_doubleSpinBoxSearchDotUnitY_valueChanged(double arg1);
    void on_spinBoxSearchDot2_valueChanged(int arg1);
    void on_doubleSpinBoxSearchDot2Unit_valueChanged(double arg1);
    void on_spinBoxSearchDot2Y_valueChanged(int arg1);
    void on_doubleSpinBoxSearchDot2UnitY_valueChanged(double arg1);

    void on_listWidgetHistList_doubleClicked(const QModelIndex &index);

private:
    Ui::AdjustAlignmentLargeForm *ui;
	bool	OnChanging;
};

#endif // ADJUSTALIGNMENTLARGEFORM_H
