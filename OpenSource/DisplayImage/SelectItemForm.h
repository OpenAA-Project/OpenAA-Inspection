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

#ifndef SELECTITEMFORM_H
#define SELECTITEMFORM_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntClass.h"
#include <QModelIndex>

namespace Ui {
class SelectItemForm;
}

class	AlgorithmBase;

class SelectItemForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    int GlobalPage;
    ListLayerIDLibNamePack	ItemIDList;
public:
    explicit SelectItemForm(AlgorithmBase *Algo ,ListLayerIDLibNamePack &itemIDList ,QWidget *parent ,int globalPage=-1);
    ~SelectItemForm();

    ListLayerAndIDPack	SelectedItems;

private slots:
    void on_ButtonOK_clicked();
    void on_tableWidgetItem_clicked(const QModelIndex &index);
    void on_tableWidgetItem_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectItemForm *ui;
};

//---------------------------------------------------------------
class	LibIDNameList : public NPList<LibIDNameList>
{
public:
    int		LibID;
    QString	LibName;

    LibIDNameList(void){	LibID=-1;	}
};

class	LibIDNameContainer : public NPListPack<LibIDNameList>
{
public:
    LibIDNameContainer(void){}

    LibIDNameList	*IsInclude(int LibID);
};

inline	LibIDNameList	*LibIDNameContainer::IsInclude(int LibID)
{
    for(LibIDNameList *s=GetFirst();s!=NULL;s=s->GetNext()){
        if(s->LibID==LibID){
            return s;
        }
    }
    return NULL;
}

#endif // SELECTITEMFORM_H