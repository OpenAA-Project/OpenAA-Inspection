/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUILib\EditFilterBank.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef EDITFILTERBANK_H
#define EDITFILTERBANK_H

#include <QWidget>
#include <QModelIndex>
#include"XParamGlobal.h"
#include "XServiceForLayers.h"
#include "WEditParameterTab.h"

namespace Ui {
class EditFilterBank;
}

class EditFilterBank : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    WEditParameterTab	*WTab;
public:
    explicit EditFilterBank(LayersBase *base ,QWidget *parent = 0);
    ~EditFilterBank();

    QStringList		FilterFileNames;

signals:
    void	SignalClose();
private slots:
    void on_tableWidgetFilter_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonLoadFiles_clicked();
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();
    void on_pushButtonDelete_clicked();

private:
    Ui::EditFilterBank *ui;

    void	ShowGrid(void);};

#endif // EDITFILTERBANK_H
