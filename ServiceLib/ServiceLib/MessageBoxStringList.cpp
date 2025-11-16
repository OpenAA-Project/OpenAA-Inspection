/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\MessageBoxStringList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "MessageBoxStringList.h"
#include "ui_MessageBoxStringList.h"
#include "XDataInLayer.h"


MessageBoxStringList::MessageBoxStringList(LayersBase *lbase ,QStringList &Msg ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(lbase)
    ,ui(new Ui::MessageBoxStringList)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);

    LangLibSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangLibSolver.SetUI(this);
    ui->listWidgetMsg->addItems(Msg);
    InstallOperationLog(this);
}

MessageBoxStringList::~MessageBoxStringList()
{
    delete ui;
}

void MessageBoxStringList::closeEvent ( QCloseEvent * event )
{
    QDialog::closeEvent (event);
    deleteLater ();
}

void MessageBoxStringList::on_pushButtonOK_clicked()
{
    close();
}
