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

#ifndef PROPERTYTREEMASTERFORM_H
#define PROPERTYTREEMASTERFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XTreeMasterPacket.h"


namespace Ui {
    class PropertyTreeMasterForm;
}

class PropertyTreeMasterForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyTreeMasterForm(LayersBase *base,QWidget *parent = 0);
    ~PropertyTreeMasterForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	
	void ShowGridList(void);
private slots:
    void on_pushButtonAddNewCat_clicked();
    void on_tableWidgetCatList_clicked(const QModelIndex &index);
    void on_tableWidgetCatList_doubleClicked(const QModelIndex &index);
	void	SlotSelectLine(void);
	void	SlotRemoveLine(void);
	void	SlotViewLine(void);

private:
    Ui::PropertyTreeMasterForm *ui;
	TreeMasterBase	*GetTreeMasterBase(void);

	TreeMasterListForPacketPack	TreeMasterInfo;

};

//=================================================================================



#endif // PROPERTYTREEMASTERFORM_H