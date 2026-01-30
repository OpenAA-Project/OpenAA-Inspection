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

#ifndef SELECTBYBindedLIMITEDDIALOG_H
#define SELECTBYBindedLIMITEDDIALOG_H

#include <QDialog>
#include "XMasking.h"
#include "XServiceForLayers.h"
#include "XPropertyMaskingPacket.h"

namespace Ui {
class SelectByBindedLimitedDialog;
}

class LineItemPointer : public NPList<LineItemPointer>
{
public:
	MaskingBindedList::BindedInPage::BindedInLayer	*Pointer;

	LineItemPointer(MaskingBindedList::BindedInPage::BindedInLayer *s){	Pointer=s;	}
};

class LineInfoBinded : public NPList<LineInfoBinded>
{
public:
	NPListPack<LineItemPointer>	PointerInst;
	AlgorithmLibraryListContainer	*LibPointer;
	bool	Selected;

	LineInfoBinded(void):Selected(false){}
};



class SelectByBindedLimitedDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
public:
    MaskingBindedListContainer	InstList;
	NPListPack<LineInfoBinded>	LineInfoInst;

	explicit SelectByBindedLimitedDialog(LayersBase *,QWidget *parent = 0);
    ~SelectByBindedLimitedDialog();
    
private slots:
    void on_toolButtonPage_clicked();
    void on_toolButtonLayer_clicked();
    void on_tableWidgetBinded_itemSelectionChanged();
    void on_pushButtonSelect_clicked();
    void on_pushButtonEdit_clicked();
    void on_pushButtonClose_clicked();
    void on_tableWidgetBinded_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectByBindedLimitedDialog *ui;

	void ShowBindedList(void);
};

#endif // SELECTBYBindedLIMITEDDIALOG_H