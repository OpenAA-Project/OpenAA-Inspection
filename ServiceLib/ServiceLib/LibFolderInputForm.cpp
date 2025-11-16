/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\LibFolderInputForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "LibFolderInputForm.h"
#include "ui_LibFolderInputForm.h"
#include "XDataInLayer.h"

LibFolderInputForm::LibFolderInputForm(LayersBase *lbase ,const QString &folderName ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LibFolderInputForm)
{
    ui->setupUi(this);

    //LangDISolver.SetLanguage(lbase->GetLanguagePackageData(),lbase->GetLanguageCode());
    //LangDISolver.SetUI(this);
    lbase->InstallOperationLog(this);

    FolderName	=folderName;

    ui->EditFolderName	->setText(FolderName);}

LibFolderInputForm::~LibFolderInputForm()
{
    delete ui;
}

void LibFolderInputForm::on_ButtonOK_clicked()
{
    FolderName	=ui->EditFolderName->text();
    done((int)true);
}

void LibFolderInputForm::on_ButtonCancel_clicked()
{
    done((int)false);
}
