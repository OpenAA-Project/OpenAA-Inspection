/*
 * Copyright (C) 2023
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

#ifndef PROPERTYDYNAMICMASKINGPIFORM_H
#define PROPERTYDYNAMICMASKINGPIFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyDynamicMaskingPIForm.h"
#include "XGUIPacketForDLL.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "XDynamicMaskingPI.h"

class PropertyDynamicMaskingPIForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyDynamicMaskingPIForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyDynamicMaskingPIForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

	ShowRGBSpace	MaskingColor;
	DynamicMaskingPIInfoListContainer	List;

private:
	Ui::PropertyDynamicMaskingPIFormClass ui;

	DynamicMaskingPIBase	*GetDynamicMaskingPIBase(void);
	void	ShowInfoList(void);
	bool	ShowItemProperty(int ShownRow);
	void	SetLayersFromLib(IntList &LayerList);

private slots:
	void on_tableWidgetMaskingList_doubleClicked(QModelIndex);
	void on_tableWidgetMaskingList_clicked(const QModelIndex &);
    void on_pushButtonSet_clicked();
    void on_radioButtonPickupMask_clicked();
    void on_radioButtonDrawMask_clicked();
};

#endif // PROPERTYDYNAMICMASKINGPIFORM_H