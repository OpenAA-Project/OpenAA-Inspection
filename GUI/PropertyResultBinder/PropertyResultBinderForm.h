/*
 * Copyright (C) 2022
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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