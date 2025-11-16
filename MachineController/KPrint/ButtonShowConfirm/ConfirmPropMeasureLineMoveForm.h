#ifndef CONFIRMPROPMEASURELINEMOVEFORM_H
#define CONFIRMPROPMEASURELINEMOVEFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XConfirmAlgorithm.h"

namespace Ui {
class ConfirmPropMeasureLineMoveForm;
}
class ConfirmForm;
class  ButtonShowConfirm;
class  MeasureLineMoveThreshold;

class ConfirmPropMeasureLineMoveForm : public ConfirmAlgorithm,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit ConfirmPropMeasureLineMoveForm(ConfirmForm *p ,QWidget *parent = 0);
    ~ConfirmPropMeasureLineMoveForm();
    
    virtual	int		GetLibType(void)            override;
    virtual	QString	GetButtonName(void)         override;
    virtual	QWidget	*GetPropertyWidget(void)    override    {   return this;    }
    virtual	void	InitialShow(void)           override;
    virtual	void	SetDrawAttr(AlgorithmLibTypeWithAttrDataContainer &s)   override;
    virtual	void	AlgoMouseLDownWithShift(int ux ,int uy) override;
    virtual	void	CanvasSlotDrawEnd(FlexArea &Area)       override;
    virtual	void	SetProperty(void)           override;
    virtual	void	ForceDraw(void)             override;
    virtual	void	ShowConfirmItem(ConfirmItemList *Item)  override;

private slots:
    void on_doubleSpinBoxMeasureLineMoveDistanceThresholdM_valueChanged(double arg1);
    void on_doubleSpinBoxMeasureLineMoveDistanceThresholdMMM_valueChanged(double arg1);
    void on_doubleSpinBoxMeasureLineMoveDistanceThresholdP_valueChanged(double arg1);
    void on_doubleSpinBoxMeasureLineMoveDistanceThresholdPMM_valueChanged(double arg1);
    void on_checkBoxMeasureLineMoveDistanceModeToSetInInitial_clicked();
    void on_doubleSpinBoxMeasureLineMoveDistanceOKRangeInInitial_valueChanged(double arg1);
    void on_comboBoxMeasureLineMoveDistanceOutputType_currentIndexChanged(int index);
    void on_EditMeasureLineMoveLineSearchDot1_valueChanged(int arg1);
    void on_doubleSpinBoxMeasureLineMoveLineSearchDot1MM_valueChanged(double arg1);
    void on_EditMeasureLineMoveLineEdgeWidth1_valueChanged(int arg1);
    void on_comboBoxMeasureLineMoveLineUsedLayer1_currentIndexChanged(int index);
    void on_EditMeasureLineMoveLineSearchDot2_valueChanged(int arg1);
    void on_doubleSpinBoxMeasureLineMoveLineSearchDot2MM_valueChanged(double arg1);
    void on_EditMeasureLineMoveLineEdgeWidth2_valueChanged(int arg1);
    void on_comboBoxMeasureLineMoveLineUsedLayer2_currentIndexChanged(int index);

private:
    Ui::ConfirmPropMeasureLineMoveForm *ui;

    virtual	void	GetItemsByPoint(int GlobalX, int GlobalY)   override;

    void    ShowThreshold(MeasureLineMoveThreshold *sLine1,MeasureLineMoveThreshold *sLine2,MeasureLineMoveThreshold *sDistance);
    void    ShowItemData(void)  override;
    void    ShowResult(void)    override;
    void    GetThresholdFromWindow(MeasureLineMoveThreshold *sLine1,MeasureLineMoveThreshold *sLine2,MeasureLineMoveThreshold *sDistance);
};

#endif // CONFIRMPROPMEASURELINEMOVEFORM_H
