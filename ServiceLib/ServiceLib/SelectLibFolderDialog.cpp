/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\SelectLibFolderDialog.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "SelectLibFolderDialog.h"
#include "ui_SelectLibFolderDialog.h"
#include "XDataInLayer.h"
#include "LibFolderForm.h"

SelectLibFolderDialog::SelectLibFolderDialog(int LibType ,LayersBase * base,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectLibFolderDialog)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);
    pLibFolderForm=new LibFolderForm(LibType,base,ui->frameLibFolder);
    connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
    base->InstallOperationLog(this);
}

SelectLibFolderDialog::~SelectLibFolderDialog()
{
    delete ui;
}

void SelectLibFolderDialog::closeEvent ( QCloseEvent * event )
{
    QDialog::closeEvent (event);
    deleteLater ();
}

void SelectLibFolderDialog::on_pushButtonSelect_clicked()
{
    done((int)true);
}

void SelectLibFolderDialog::on_pushButtonCancel_clicked()
{
    done((int)false);
}

void	SelectLibFolderDialog::SlotSelectLibFolder(int LibFolderID ,QString FolderName)
{
    SelectedLibFolderID	=LibFolderID;
    SelectedFolderName	=FolderName;
}
