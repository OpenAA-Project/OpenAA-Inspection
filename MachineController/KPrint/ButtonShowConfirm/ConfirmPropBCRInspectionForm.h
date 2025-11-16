#ifndef CONFIRMPROPBCRINSPECTIONFORM_H
#define CONFIRMPROPBCRINSPECTIONFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XConfirmAlgorithm.h"
#include "XFlexArea.h"
#include "XPropPacketBCRInspection.h"

namespace Ui {
class ConfirmPropBCRInspectionForm;
}
class ConfirmForm;
class  ButtonShowConfirm;
class  BCRInspectionThreshold;
class  BCRGradeListContainer;

class ConfirmPropBCRInspectionForm : public ConfirmAlgorithm,public ServiceForLayers
{
    Q_OBJECT

    BCodeItemListContainer  BCodeItemListContainerData;
public:
    explicit ConfirmPropBCRInspectionForm(ConfirmForm *p ,QWidget *parent = 0);
    ~ConfirmPropBCRInspectionForm();
    
    virtual	int		GetLibType(void)            override;
    virtual	QString	GetButtonName(void)         override;
    virtual	QWidget	*GetPropertyWidget(void)    override    {   return this;    }
    virtual	void	InitialShow(void)           override;
    virtual	void	AlgoMouseLDownWithShift(int ux ,int uy) override;
    virtual	void	SetDrawAttr(AlgorithmLibTypeWithAttrDataContainer &s)   override;
    virtual	void	CanvasSlotDrawEnd(FlexArea &Area)   override;
    virtual	void	SetProperty(void)           override;
    virtual	void	ForceDraw(void)             override;
    virtual	void	ShowConfirmItem(ConfirmItemList *Item)  override;

private slots:
    void on_tableWidgetBCRInspectionItem_itemSelectionChanged();
    void on_comboBoxBCRInspectionCheckType_currentIndexChanged(int index);
    void on_doubleSpinBoxBCRInspectionQuilityGrade_valueChanged(double arg1);
    void on_pushButtonBCRInspectionLoad_clicked();
    void on_pushButtonBCRInspectionSave_clicked();
    void on_pushButtonBCRInspectionAdd_clicked();
    void on_pushButtonBCRInspectionSub_clicked();
    void on_tableWidgetBCRInspectionItem_clicked(const QModelIndex &index);

private:
    Ui::ConfirmPropBCRInspectionForm *ui;

    void    ShowThreshold(BCRInspectionThreshold *s);
    void    ShowItemData(void)  override;
    void    ShowResult(void)    override;
    void    GetThresholdFromWindow(BCRInspectionThreshold *s);

    void    ShowGradeList(BCRGradeListContainer &List);
    void    LoadGradeListFromWindow(BCRGradeListContainer &List);
};

#endif // CONFIRMPROPBCRINSPECTIONFORM_H
