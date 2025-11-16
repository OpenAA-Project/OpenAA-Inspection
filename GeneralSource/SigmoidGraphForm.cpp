/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\SigmoidGraphForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "RepairStationResource.h"
#include "SigmoidGraphForm.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "RepairBase.h"
#include "ImageDataUnit.h"

#include "PasswordEventOperator.h"

SigmoidGraphForm::SigmoidGraphForm(RepairBase *ParentClass,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	PasswordEventOperator *peo = new PasswordEventOperator(this);
	peo->addButton(ui.pbCancel);
	peo->addButton(ui.pbOK);

	ui.label_2->setText(LangSolver.GetString(SigmoidGraphForm_LS,LID_49)/*"( 0 - 255 )"*/);
    ui.label_2->setGeometry(QRect(30, 200, 60, 14));
	PClass=ParentClass;

	//?O???t?I?\?|
	SigGraph=new mtLineGraph();
	mtGLine	*GLine			=new mtGLine();
	mtGLine	*GLineStandard	=new mtGLine();
	SigGraph->AddGraph(GLine);
	SigGraph->AddGraph(GLineStandard);
	SigGraph->GraphList[0]->SetLineWidth(3);
	for(int i=0;i<=255;i++){
		SigGraph->GraphList[1]->AddXY(i,i);
	}

	ui.dwSigGraph	->setWidget(SigGraph);
	ui.dwSigGraph	->setGeometry(ui.dwSigGraph->geometry().x(),ui.dwSigGraph->geometry().y(),ui.dwSigGraph->geometry().width(),622);

	if(PClass->GetSigVolume()==-1){
		PClass->SetSigVolume(1);
	}
	if(PClass->GetSigBright()==-1){
		PClass->SetSigBright(127);
	}
	ui.dsbVolume	->setValue(PClass->GetSigVolume());
	ui.sbBrightness	->setValue(PClass->GetSigBright());

	//?O???t?\?|
	dsbVolumeChanged(ui.dsbVolume->value());

	//?F?I?Y?e
	QPalette palette;
	palette.setColor(QPalette::Base,QColor(Qt::cyan));
	ui.leVolume		->setPalette(palette);
	ui.leBrightness	->setPalette(palette);

	//connect
	connect(ui.dsbVolume,	SIGNAL(valueChanged(double)),	this,SLOT(dsbVolumeChanged(double)));
	connect(ui.sbBrightness,SIGNAL(valueChanged(int)),		this,SLOT(sbBrightnessChanged(int)));
	connect(ui.pbOK,		SIGNAL(clicked()),				this,SLOT(pbOKClicked()));
	connect(ui.pbCancel,	SIGNAL(clicked()),				this,SLOT(pbCancelClicked()));
}

SigmoidGraphForm::~SigmoidGraphForm()
{
}

void SigmoidGraphForm::dsbVolumeChanged(double value)
{
	//?O???t?\?|
	SigGraph->GraphList[0]->DeleteXY();
	int Brightness=ui.sbBrightness->value();
	PClass->SetSigmoid(value,Brightness,wBrightness);
	for(int i=0;i<=255;i++){
		SigGraph->GraphList[0]->AddXY(i,wBrightness[i]);
	}
	//value?l?a?P?I???A?O???t?I???u
	if(value==1)
		ui.sbBrightness->setEnabled(false);
	else
		ui.sbBrightness->setEnabled(true);

	ui.dwSigGraph->repaint();
}

void SigmoidGraphForm::sbBrightnessChanged(int value)
{
	//?O???t?\?|
	dsbVolumeChanged(ui.dsbVolume->value());
}

void SigmoidGraphForm::pbOKClicked()
{
	//?P?x?e?[?u???O?l?d?i?[
	for(int i=0;i<=255;i++){
		PClass->Brightness[i]=wBrightness[i];
	}
	for(int i=0;i<PClass->IDataUnit->MImageClassList.count();i++){
		PClass->IDataUnit->MImageClassList[i]->SetMasterBrightness(PClass->Brightness);
	}
	PClass->IDataUnit->NGImagePieceList[0]->SetNGBrightness(PClass->Brightness);
	double Volume;
	if((Volume=ui.dsbVolume->value())==0){
		PClass->SetSigVolume(1);
	}
	else{
		PClass->SetSigVolume(Volume);
	}
	PClass->SetSigBright(ui.sbBrightness->value());
	accept();
}

void SigmoidGraphForm::pbCancelClicked()
{
	reject();
}
