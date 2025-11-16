/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\VeisionInfoForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "VeisionInfoForm.h"
#include "ui_VeisionInfoForm.h"
#include "XDataInLayer.h"
#include "Regulus64Version.h"


VeisionInfoForm::VeisionInfoForm(LayersBase *lbase ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(lbase)
    ,ui(new Ui::VeisionInfoForm)   
{
    ui->setupUi(this);
    //LangLibSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    //LangLibSolver.SetUI(this);
    //ui->labelDate->setText(VersionDate);
    ui->labelRevision->setText(RegulusVersionRevision);
}

VeisionInfoForm::~VeisionInfoForm()
{
    delete ui;
}

void VeisionInfoForm::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}

void VeisionInfoForm::on_pushButton_clicked()
{
    emit	SignalClose();
}
