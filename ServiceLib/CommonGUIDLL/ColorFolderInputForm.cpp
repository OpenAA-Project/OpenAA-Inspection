#include "CommonGUIDLLResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\CommonGUIDLL\ColorFolderInputForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ColorFolderInputForm.h"
#include "XDataInLayer.h"
#include "XFileRegistry.h"

ColorFolderInputForm::ColorFolderInputForm(LayersBase *base,const QString &folderName ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);

	FolderName	=folderName;
	ui.EditFolderName	->setText(FolderName);
}

ColorFolderInputForm::~ColorFolderInputForm()
{

}

void ColorFolderInputForm::closeEvent ( QCloseEvent * event )
{
	QDialog::closeEvent (event);
	deleteLater ();
}

void ColorFolderInputForm::on_ButtonOK_clicked()
{
	FolderName	=ui.EditFolderName->text();
	done((int)true);

}

void ColorFolderInputForm::on_ButtonCancel_clicked()
{
	done((int)false);
}