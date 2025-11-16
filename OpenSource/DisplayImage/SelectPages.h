/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\SelectPages.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SELECTPAGES_H
#define SELECTPAGES_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SelectPages;
}

class SelectPages : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectPages(LayersBase *base ,QWidget *parent = 0);
             SelectPages(LayersBase *base ,const IntList &Pages ,QWidget *parent);
    ~SelectPages();

    IntList	SelectedPages;

private slots:
    void on_pushButtonSelect_clicked();
    void on_listWidgetSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonAll_clicked();
    void on_pushButtonRelease_clicked();

private:
    Ui::SelectPages *ui;
};

#endif // SELECTPAGES_H
