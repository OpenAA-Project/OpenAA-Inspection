/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\CommonGUIDLL\ColorFolderInputForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "SelectColorSampleResource.h"
#include "XTypeDef.h"
#include "DisplayImageResource.h"
#include "ColorFolderInputForm.h"
#include "ui_ColorFolderInputForm.h"
#include "XDataInLayer.h"
#include "XFileRegistry.h"



ColorFolderInputForm::ColorFolderInputForm(LayersBase *base,const QString &folderName ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::ColorFolderInputForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	LangCGSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
	LangCGSolver.SetUI(this);
	InstallOperationLog(this);

	FolderName	=folderName;
	ui->EditFolderName	->setText(FolderName);
}

ColorFolderInputForm::~ColorFolderInputForm()
{
    delete ui;
}

void ColorFolderInputForm::closeEvent ( QCloseEvent * event )
{
	QDialog::closeEvent (event);
	deleteLater ();
}

void ColorFolderInputForm::on_ButtonOK_clicked()
{
	FolderName	=ui->EditFolderName->text();
	done((int)true);
}

void ColorFolderInputForm::on_ButtonCancel_clicked()
{
	done((int)false);
}
