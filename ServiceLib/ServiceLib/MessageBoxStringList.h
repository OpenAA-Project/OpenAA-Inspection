/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\MessageBoxStringList.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef MESSAGEBOXSTRINGLIST_H
#define MESSAGEBOXSTRINGLIST_H

#include <QDialog>
#include <QStringList>
#include "XServiceForLayers.h"

namespace Ui {
class MessageBoxStringList;
}

class MessageBoxStringList : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit MessageBoxStringList(LayersBase *lbase ,QStringList &Msg ,QWidget *parent = 0);
    ~MessageBoxStringList();
    
private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::MessageBoxStringList *ui;
    virtual	void closeEvent ( QCloseEvent * event ) 	override;
};

#endif // MESSAGEBOXSTRINGLIST_H
