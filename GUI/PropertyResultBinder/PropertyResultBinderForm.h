#ifndef PROPERTYRESULTBINDERFORM_H
#define PROPERTYRESULTBINDERFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include"XPropertyResultBinderPacket.h"

namespace Ui {
class PropertyResultBinderForm;
}

class PropertyResultBinderForm : public GUIFormBase
{
    Q_OBJECT
    
	int		ResultBinderItemPage;
	int		ResultBinderItemID;

	ItemIDNameContainer		ResultBinderItemList[100];

public:
    explicit PropertyResultBinderForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyResultBinderForm();
    
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	BuildForShow(void)	override;
	
private slots:
    void on_tableWidgetItemList_itemSelectionChanged();
    void on_pushButtonAddItem_clicked();
    void on_pushButtonModifyItem_clicked();
    void on_pushButtonDeleteItem_clicked();

    void on_toolButtonAlignmentItem_clicked();
    void on_toolButtonAllItemsInLayer_clicked();
    void on_toolButtonAllItemsInPage_clicked();
    void on_toolButtonOperationOR_clicked();
    void on_toolButtonOperationAND_clicked();
    void on_toolButtonOperationXOR_clicked();
    void on_toolButtonOperationNEG_clicked();
    void on_toolButtonOperationConditional_clicked();
    void on_toolButtonNothing_clicked();
    void on_toolButtonLinkArrow_clicked();
    void on_tableWidgetItemList_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyResultBinderForm *ui;

	void	ShowItems(void);
	void	ShowImagePanel(void);
};

#endif // PROPERTYRESULTBINDERFORM_H
