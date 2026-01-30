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


#ifndef PROPERTYALIGNMENTFORM_H
#define PROPERTYALIGNMENTFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyAlignmentForm.h"
#include "WMultiGrid.h"
#include "PropertyAlignmentPacket.h"

class PropertyAlignmentForm : public GUIFormBase
{
    Q_OBJECT

public:
    PropertyAlignmentForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyAlignmentForm();

	ReqAlignmentAreaListPack	AreaListFromMaster;
	AlignmentAreaListPack	AreaList;
	AlignmentPointListPack	PointList;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	BuildForShow(void)		override;
	void	CreateAndShowPointGrid(void);
	virtual void	StartPage	(void)		override;

	void	CreateAlignmentArea(FlexArea &area);
	void	CreateAlignmentPoint(FlexArea &area ,int MoveDot ,int Threshold ,bool AlignmentOnOutline);

private:
    Ui::PropertyAlignmentFormClass ui;
	void	ShowAreaGrid(void);
	void	ShowPointGrid(AlignmentAreaList *A);
	void	ShowPointGridRaw(void);
	void	CreatePointList(AlignmentAreaList *A);
	GUIFormBase	*GetImageControlToolsPointer(void);

private slots:
	void on_toolButtonGroup_clicked();
	void on_toolButtonPoint_clicked();
	void on_toolButtonArea_clicked();
	void on_tableWidgetPoint_itemDoubleClicked(QTableWidgetItem*);
	void on_tableWidgetArea_doubleClicked(QModelIndex);
	void on_tableWidgetArea_clicked(const QModelIndex &);
};
//===========================================================================

#endif // PROPERTYALIGNMENTFORM_H