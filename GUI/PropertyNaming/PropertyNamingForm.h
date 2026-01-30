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


#ifndef PROPERTYNAMINGFORM_H
#define PROPERTYNAMINGFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyNamingForm.h"
#include "XGUIPacketForDLL.h"
#include "XPropertyNamingPacket.h"

class PropertyNamingForm : public GUIFormBase
{
    Q_OBJECT
	NamingListForPacketPack	NamingInfo;
	NamingGroupContainer	NamingGroupData;
public:
    PropertyNamingForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyNamingForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

	void	ShowGrid(void);
	void	ShowGroupGrid(void);
	void	CreateArea(const QString &AreaName,FlexArea &Area
						,int Column ,int Row
						,int Expand);
private:
    Ui::PropertyNamingFormClass ui;
private slots:
	void on_pushButton_CreateItemFromItsCoordinate_clicked();
	void on_tableWidgetNamingList_clicked(const QModelIndex &);
	void on_pushButtonExecute_clicked();
	void on_tableWidget_cellDoubleClicked(int,int);
    void on_toolButtonAutoCount_clicked();
    void on_toolButtonMakeGroup_clicked();
    void on_listWidgetGroup_clicked(const QModelIndex &index);
    void on_pushButtonClearSelectedGroup_clicked();
	void on_pushButtonGenerateIndex_clicked();
};


#endif // PROPERTYNAMINGFORM_H