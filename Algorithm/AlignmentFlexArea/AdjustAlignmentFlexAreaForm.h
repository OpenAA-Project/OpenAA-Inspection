#ifndef ADJUSTALIGNMENTFLEXAREAFORM_H
#define ADJUSTALIGNMENTFLEXAREAFORM_H

#include <QWidget>
#include <QToolBar>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XAlignmentFlexArea.h"

namespace Ui {
class AdjustAlignmentFlexAreaForm;
}

class AdjustAlignmentFlexAreaForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

public:
    int GlobalPage;

    explicit AdjustAlignmentFlexAreaForm(LayersBase *Base,QWidget *parent = 0);
    ~AdjustAlignmentFlexAreaForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);
    void	ShowDataToWindow(void);

	AlgorithmItemIndependentPack	*IData;
	HistgramTypeListInAlgoContainer	HContainer;

private slots:
    void on_pushButtonSetOne_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonHistogramX_clicked();
    void on_pushButtonHistogramY_clicked();
    void on_pushButtonClose_clicked();
    void on_spinBoxSearchDot_valueChanged(int arg1);
    void on_doubleSpinBoxSearchDotUnit_valueChanged(double arg1);
    void on_spinBoxGlobalSearchDot_valueChanged(int arg1);
    void on_doubleSpinBoxGlobalSearchDotUnit_valueChanged(double arg1);
    void on_pushButtonSaveLibrary_clicked();
    void on_pushButtonLoadLibrary_clicked();

    void on_EditSmallSearch_valueChanged(int arg1);

    void on_doubleSpinBoxSmallSearchUnit_valueChanged(double arg1);

private:
    Ui::AdjustAlignmentFlexAreaForm *ui;

	bool	OnChanging;
};

#endif // ADJUSTALIGNMENTFLEXAREAFORM_H
