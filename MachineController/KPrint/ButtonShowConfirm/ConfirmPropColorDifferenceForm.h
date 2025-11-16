#ifndef CONFIRMPROPCOLORDIFFERENCEFORM_H
#define CONFIRMPROPCOLORDIFFERENCEFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XConfirmAlgorithm.h"
#include "XFlexArea.h"

namespace Ui {
class ConfirmPropColorDifferenceForm;
}
class ConfirmForm;
class  ButtonShowConfirm;
class  ColorDifferenceThreshold;

class ConfirmPropColorDifferenceForm : public ConfirmAlgorithm,public ServiceForLayers
{
    Q_OBJECT

    bool                OutputConstantlyInItem;
public:
    explicit ConfirmPropColorDifferenceForm(ConfirmForm *p ,QWidget *parent = 0);
    ~ConfirmPropColorDifferenceForm();
    
    virtual	int		GetLibType(void)            override;
    virtual	QString	GetButtonName(void)         override;
    virtual	QWidget	*GetPropertyWidget(void)    override    {   return this;    }
    virtual	void	InitialShow(void)           override;
    virtual	void	AlgoMouseLDownWithShift(int ux ,int uy) override;
    virtual	void	CanvasSlotDrawEnd(FlexArea &Area)       override;
    virtual	void	SetDrawAttr(AlgorithmLibTypeWithAttrDataContainer &s)   override;
    virtual	void	SetProperty(void)           override;
    virtual	void	ForceDraw(void)             override;
    virtual	void	ShowConfirmItem(ConfirmItemList *Item)  override;
private slots:
    void on_doubleSpinBoxColorDifferenceAdoptedRate_valueChanged(double arg1);
    void on_checkBoxColorDifferenceOutputConstantly_clicked();
    void on_comboBoxColorDifferenceJudgeMethod_currentIndexChanged(int index);
    void on_doubleSpinBoxColorDifferenceTHDeltaE_valueChanged(double arg1);
    void on_doubleSpinBoxColorDifferencedH_valueChanged(double arg1);
    void on_doubleSpinBoxColorDifferencedSL_valueChanged(double arg1);
    void on_doubleSpinBoxColorDifferencedSH_valueChanged(double arg1);
    void on_doubleSpinBoxColorDifferencedVL_valueChanged(double arg1);
    void on_doubleSpinBoxColorDifferencedVH_valueChanged(double arg1);

private:
    Ui::ConfirmPropColorDifferenceForm *ui;

    void    ShowThreshold(int LibID,ColorDifferenceThreshold *s);
    void    ShowItemData(void)  override;
    void    ShowResult(void)    override;
    void    GetThresholdFromWindow(ColorDifferenceThreshold *s);
};

#endif // CONFIRMPROPCOLORDIFFERENCEFORM_H
