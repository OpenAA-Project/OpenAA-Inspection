/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\SelectItemForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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
