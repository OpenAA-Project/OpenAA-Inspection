/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\SelectByLibraryDialog.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "SelectByLibraryDialog.h"
#include "ui_SelectByLibraryDialog.h"
#include "XDataInLayer.h"
#include "XRememberer.h"

SelectByLibraryDialog::SelectByLibraryDialog(int libType ,LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,Libs(libType ,Base)
    ,ui(new Ui::SelectByLibraryDialog)
    
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);
    Libs.setParent(ui->frameLibrary);
    Libs.move(0,0);
    Libs.resize(ui->frameLibrary->width(),ui->frameLibrary->height());

    ControlRememberer::RestoreForm(this);

    Base->InstallOperationLog(this);
}

SelectByLibraryDialog::~SelectByLibraryDialog()
{
    delete ui;
}

void SelectByLibraryDialog::on_ButtonSelect_clicked()
{
    ControlRememberer::SaveForm(this);
    done(true);
}

void SelectByLibraryDialog::on_ButtonCancel_clicked()
{
    done(false);
}
