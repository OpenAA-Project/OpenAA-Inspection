/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\GeneralSettingForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "RepairStationResource.h"
#include "GeneralSettingForm.h"
#include <QFileDialog>
#include "RepairBase.h"
#include "ImageDataUnit.h"
#include "SigmoidGraphForm.h"
#include <QColorDialog>
#include <XGeneralFunc.h>

#include "PasswordEventOperator.h"

GeneralSettingForm::GeneralSettingForm(RepairBase *ParentClass,QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	PasswordEventOperator *peo = new PasswordEventOperator(this);
	peo->addButton(ui.pbCancel);
	peo->addButton(ui.pbMasterDir);
	peo->addButton(ui.pbMMCSetting);
	peo->addButton(ui.pbOK);
	peo->addButton(ui.pbReturnDefault);
	peo->addButton(ui.pbReturnSetting);
	peo->addButton(ui.pbSaveDirNGImage);
	peo->addButton(ui.pbSetColor);
	peo->addButton(ui.pbShowSigGraph);

	PClass		=ParentClass;
	ApplySigmoid=false;
	ui.pbSetColor->setVisible(false);
	ui.pbMMCSetting->setVisible(false);

	//?V?O?i???E?X???b?g
	connect(ui.pbMasterDir,		SIGNAL(clicked()),		this,SLOT(pbMasterDirClicked()));
	connect(ui.chNGBlinkEnable,	SIGNAL(toggled(bool)),	this,SLOT(chNGBlinkEnableToggled(bool)));
	connect(ui.pbReturnSetting,	SIGNAL(clicked()),		this,SLOT(pbReturnSettingClicked()));
	connect(ui.pbReturnDefault,	SIGNAL(clicked()),		this,SLOT(pbReturnDefaultClicked()));
	connect(ui.pbSaveDirNGImage,SIGNAL(clicked()),		this,SLOT(pbSaveDirNGImageClicked()));
	connect(ui.pbShowSigGraph,	SIGNAL(clicked()),		this,SLOT(pbShowSigGraphClicked()));
	connect(ui.tbPieceColor,	SIGNAL(clicked()),		this,SLOT(tbPieceColorClicked()));
	connect(ui.tbOnlyFColor,	SIGNAL(clicked()),		this,SLOT(tbOnlyFColorClicked()));
	connect(ui.tbOnlyBColor,	SIGNAL(clicked()),		this,SLOT(tbOnlyBColorClicked()));
	connect(ui.tbFBColor,		SIGNAL(clicked()),		this,SLOT(tbFBColorClicked()));
	connect(ui.pbOK,			SIGNAL(clicked()),		this,SLOT(pbOKClicked()));
	connect(ui.pbCancel,		SIGNAL(clicked()),		this,SLOT(pbCancelClicked()));

	//save-r.dat?I?C?Y???Y
	SaveDatPath=/**/"./save-r.dat";
	if(PClass->LoadFile(SaveDatPath,SaveDatList)){
		ui.leHost->setText(SaveDatList.at(0));		//hostname
		ui.lePath->setText(SaveDatList.at(1));		//DataBase
	}

	//XmlConnect-r.dat?I?C?Y???Y
	XmlConnectDatPath=/**/"./XmlConnect-r.dat";
	if(PClass->LoadFile(XmlConnectDatPath,XmlConnectDatList)){
		ui.leXMLHost->setText(XmlConnectDatList.at(0));		//hostname
		ui.leXMLPath->setText(XmlConnectDatList.at(2));		//XMLDataBase
	}

	//RepairSetting.dat
	ui.leMasterDir		->setText(PClass->GetMasterDir());									//MasterData Directory
	ui.chNGBlinkEnable	->setChecked(PClass->GetNGBlink());									//NG Blink Enable Check
	ui.sbNGBlinkTime	->setValue(PClass->tNGBlink.BlinkTime);								//NG Blink Time
	ui.sbNGMarkSize		->setValue(PClass->IDataUnit->NGImagePieceList[0]->NGMarkSize);		//NG Mark Size
	if(PClass->GetCheckedNumb()==PClass->TopToBottom){
		ui.rbTopBottom	->setChecked(true);													//NG Sort Top to Bottom Check
	}
	else if(PClass->GetCheckedNumb()==PClass->BottomToTop){
		ui.rbBottomTop	->setChecked(true);													//NG Sort Bottom to Top Check
	}
	else if(PClass->GetCheckedNumb()==PClass->LeftToRight){
		ui.rbLeftRight	->setChecked(true);													//NG Sort Left to Right Check
	}
	else if(PClass->GetCheckedNumb()==PClass->RightToLeft){
		ui.rbRightLeft	->setChecked(true);													//NG Sort Right to Left Check
	}
	ui.chShowOK			->setChecked(PClass->GetShowOK());									//NG Show OK Check
	ui.cbResolution		->setCurrentIndex(PClass->GetImgRate());							//Master Image Resolution
	ui.sbNGWaitTime		->setValue(PClass->GetNGWaitTime());								//NG Wait Time
	ui.chEachPieces		->setChecked(PClass->GetEachPieces());								//Each Pieces Check
	if(PClass->GetMImageSplitter()==Qt::Vertical){
		ui.rbVertical	->setChecked(true);													//Master Image Splitter Vertical
	}
	else{
		ui.rbHorizontal	->setChecked(true);													//Master Image Splitter Horizontal
	}
	QPalette P;
	P.setColor(QPalette::Button,QColor(PClass->GetPieceColorString()));
	ui.tbPieceColor				->setPalette(P);											//Piece Color
	ui.chEnableNGPieceChange	->setChecked(PClass->GetEnableNGPieceChange());				//Enable NG Piece Change Check
	ui.leSaveDirNGImage			->setText	(PClass->GetSaveDirNGImage());					//Save NG Image Directory
	ui.gbOutputDebugLog			->setChecked(PClass->GetOutputDebugLog());					//Output Debug Log Check
	ui.chOutputXMLData			->setChecked(PClass->GetOutputXMLData());					//Output XML Data Check
	ui.chShowInsDataMsg			->setChecked(PClass->GetShowInsDataMsg());					//Show Inspection Data Message Check
	ui.sbListScrollRow			->setValue	(PClass->GetListScrollRowCnt());				//List Scroll Row Count
	P.setColor(QPalette::Button,QColor(PClass->GetOnlyFColor()));
	ui.tbOnlyFColor				->setPalette(P);											//Only F Color
	P.setColor(QPalette::Button,QColor(PClass->GetOnlyBColor()));
	ui.tbOnlyBColor				->setPalette(P);											//Only B Color
	P.setColor(QPalette::Button,QColor(PClass->GetFBColor()));
	ui.tbFBColor				->setPalette(P);											//FB Color
	ui.chNextCheck				->setChecked(PClass->GetNextCheck());						//Next Key Enable Check
	ui.chEnterCheck				->setChecked(PClass->GetEnterCheck());						//Enter Key Enable Check
	ui.sbNGImageOffset			->setValue	(PClass->GetNGImageOffset());					//NGImage Offset
	ui.sbPlusRed				->setValue	(PClass->GetPlusRed());							//Plus Red
	ui.sbPlusGreen				->setValue	(PClass->GetPlusGreen());						//Plus Green
	ui.sbPlusBlue				->setValue	(PClass->GetPlusBlue());						//Plus Blue

	QLibrary myLib(/**/"./ReparMarkingColor.dll");
	if(myLib.isLibrary(/**/"./ReparMarkingColor.dll")==true){
		if(myLib.load()==true){
			if(myLib.isLoaded()==true){
				DLL_GetName	=NULL;
				DLL_FormShow=NULL;
				DLL_GetName	=(bool (*)(QString &str))myLib.resolve(/**/"DLL_GetName");
				DLL_FormShow=(void (*)(void))myLib.resolve(/**/"DLL_FormShow");
				if(DLL_GetName!=NULL){
					if(DLL_FormShow!=NULL){
						ui.pbSetColor->setVisible(true);
					}
				}
			}
		}
	}
	else{
		//?v???O?C??DLL?iOutputLog.dll?FMMC?pDLL(?Y?e?O?W?I?O???I?Y??}??}?A?I??E??)?j
		QLibrary myLib1(/**/"./OutputLog.dll");
		if(myLib1.isLibrary(/**/"./OutputLog.dll")==true){
			if(myLib1.load()==true){
				if(myLib1.isLoaded()==true){
					DLL_MMCSettingFormShow=NULL;
					DLL_MMCSettingFormShow=(bool (*)(QStringList &List))myLib1.resolve(/**/"DLL_MMCSettingFormShow");
					if(DLL_MMCSettingFormShow!=NULL){
						ui.pbMMCSetting->setVisible(true);
						connect(ui.pbMMCSetting,SIGNAL(clicked()),this,SLOT(pbMMCSettingClicked()));
					}
				}
			}
		}
	}
//	if(!PClass->chEditEnable->isChecked()){
//		ui.pbReturnSetting->setEnabled(false);
//		ui.pbReturnDefault->setEnabled(false);
//	}
}

GeneralSettingForm::~GeneralSettingForm()
{
}

void GeneralSettingForm::pbMasterDirClicked()
{
	QString MasterDir=QFileDialog::getExistingDirectory(this, LangSolver.GetString(GeneralSettingForm_LS,LID_14)/*"Select Directory"*/,
                                                 LangSolver.GetString(GeneralSettingForm_LS,LID_15)/*"/home"*/,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
	if(MasterDir==/**/"")
		return;
	ui.leMasterDir->setText(MasterDir);
}

void GeneralSettingForm::chNGBlinkEnableToggled(bool Tog)
{
	ui.sbNGBlinkTime->setEnabled(Tog);
}

void GeneralSettingForm::pbReturnSettingClicked()
{
	PClass->LoadLocation();
	PClass->SetCheckEditEnable(false);
}

void GeneralSettingForm::pbReturnDefaultClicked()
{
	PClass->WindowDefault();
	PClass->MainFrameDefault();
	PClass->dwMasterImage1Default();
	PClass->dwMasterImage2Default();
	PClass->dwNGMasterPixDefault();
	PClass->dwNGInspectionPixDefault();
	PClass->dwHistoryListDefault();
	PClass->dwNGListDefault();
	PClass->SetCheckEditEnable(false);
}

void GeneralSettingForm::pbSaveDirNGImageClicked()
{
	QString SaveDirNGImage=QFileDialog::getExistingDirectory(this, LangSolver.GetString(GeneralSettingForm_LS,LID_14)/*"Select Directory"*/,
                                                 LangSolver.GetString(GeneralSettingForm_LS,LID_15)/*"/home"*/,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
	if(SaveDirNGImage==/**/"")
		return;
	ui.leSaveDirNGImage->setText(SaveDirNGImage);
}

void GeneralSettingForm::pbShowSigGraphClicked()
{
	//?V?O???C?h?O???t?a?E?I?\?|
//	SigmoidGraphForm SigmoidGrahDialog(PClass,1000);
	SigmoidGraphForm SigmoidGrahDialog(PClass,0);
	if(!SigmoidGrahDialog.exec())
		return;
	ApplySigmoid=true;
}

void GeneralSettingForm::tbPieceColorClicked()
{
	QColor	C=QColorDialog::getColor(QColor(PClass->GetPieceColorString()));
	if(C.isValid()){
		QPalette P;
		P.setColor(QPalette::Button,C);
		ui.tbPieceColor->setPalette(P);
	}
}

void GeneralSettingForm::tbOnlyFColorClicked()
{
	QColor	C=QColorDialog::getColor(QColor(PClass->GetOnlyFColor()));
	if(C.isValid()){
		QPalette P;
		P.setColor(QPalette::Button,C);
		ui.tbOnlyFColor->setPalette(P);
	}
}

void GeneralSettingForm::tbOnlyBColorClicked()
{
	QColor	C=QColorDialog::getColor(QColor(PClass->GetOnlyBColor()));
	if(C.isValid()){
		QPalette P;
		P.setColor(QPalette::Button,C);
		ui.tbOnlyBColor->setPalette(P);
	}
}

void GeneralSettingForm::tbFBColorClicked()
{
	QColor	C=QColorDialog::getColor(QColor(PClass->GetFBColor()));
	if(C.isValid()){
		QPalette P;
		P.setColor(QPalette::Button,C);
		ui.tbFBColor->setPalette(P);
	}
}

void GeneralSettingForm::pbOKClicked()
{
	//save-r.dat?I????a???Y
	SaveDatList.clear();
	SaveDatList << ui.leHost->text();		//hostname
	SaveDatList << ui.lePath->text();		//DataBase
	SaveDatList << /**/"SYSDBA";				//user
	SaveDatList << /**/"masterkey";				//password
	PClass->SaveFile(SaveDatPath,&SaveDatList);

	//XmlConnect-r.dat?I????a???Y
	XmlConnectDatList.clear();
	XmlConnectDatList << ui.leXMLHost->text();		//hostname
	XmlConnectDatList << /**/"12345";					//port
	XmlConnectDatList << ui.leXMLPath->text();		//XMLDataBase
	PClass->SaveFile(XmlConnectDatPath,&XmlConnectDatList);

	//RepairSetting.dat?I????a???Y?O????o
	PClass->SetMasterDir(ui.leMasterDir->text());
	PClass->SetNGBlink(ui.chNGBlinkEnable->isChecked());
	PClass->tNGBlink.BlinkTime=ui.sbNGBlinkTime->value();
	PClass->IDataUnit->NGImagePieceList[0]->NGMarkSize=ui.sbNGMarkSize->value();
	if(ui.rbTopBottom		->isChecked()){
		PClass->SetCheckedNumb(PClass->TopToBottom);
		PClass->SetNGSortXY(/**/"Y");
		PClass->SetNGSortOrder(/**/"A");
	}
	else if(ui.rbBottomTop	->isChecked()){
		PClass->SetCheckedNumb(PClass->BottomToTop);
		PClass->SetNGSortXY(/**/"Y");
		PClass->SetNGSortOrder(/**/"D");
	}
	else if(ui.rbLeftRight	->isChecked()){
		PClass->SetCheckedNumb(PClass->LeftToRight);
		PClass->SetNGSortXY(/**/"X");
		PClass->SetNGSortOrder(/**/"A");
	}
	else if(ui.rbRightLeft	->isChecked()){
		PClass->SetCheckedNumb(PClass->RightToLeft);
		PClass->SetNGSortXY(/**/"X");
		PClass->SetNGSortOrder(/**/"D");
	}
	PClass->SetShowOK(ui.chShowOK->isChecked());
	PClass->SetImgRate(ui.cbResolution->currentIndex());	//Master Image Resolution
	PClass->SetNGWaitTime(ui.sbNGWaitTime->value());
	PClass->SetEachPieces(ui.chEachPieces->isChecked());
	if(ui.rbVertical->isChecked()){
		PClass->SetMImageSplitter(Qt::Vertical);
	}
	else{
		PClass->SetMImageSplitter(Qt::Horizontal);
	}
	PClass->SetPieceColorString		(ui.tbPieceColor->palette().color(QPalette::Button).name());	//Piece Color
	PClass->SetEnableNGPieceChange	(ui.chEnableNGPieceChange->isChecked());
	PClass->SetSaveDirNGImage		(ui.leSaveDirNGImage->text());
	PClass->SetOutputDebugLog		(ui.gbOutputDebugLog->isChecked());
	PClass->SetOutputXMLData		(ui.chOutputXMLData->isChecked());
	PClass->SetShowInsDataMsg		(ui.chShowInsDataMsg->isChecked());
	PClass->SetListScrollRowCnt		(ui.sbListScrollRow->value());
	PClass->SetOnlyFColor			(ui.tbOnlyFColor->palette().color(QPalette::Button).name());
	PClass->SetOnlyBColor			(ui.tbOnlyBColor->palette().color(QPalette::Button).name());
	PClass->SetFBColor				(ui.tbFBColor	->palette().color(QPalette::Button).name());
	PClass->SetNextCheck			(ui.chNextCheck->isChecked());
	PClass->SetEnterCheck			(ui.chEnterCheck->isChecked());
	PClass->SetNGImageOffset		(ui.sbNGImageOffset->value());
	PClass->SetPlusRed				(ui.sbPlusRed->value());
	PClass->SetPlusGreen			(ui.sbPlusGreen->value());
	PClass->SetPlusBlue				(ui.sbPlusBlue->value());

	//Save RepairSetting.dat
	PClass->WriteRepairSetting();

	if(ui.chShowOK->isChecked()){
		PClass->SetRes(/**/"ALL");
	}
	else{
		PClass->SetRes(/**/"OK");
	}

	PClass->SetWaitTime(PClass->GetNGWaitTime());

	//NG?u?????N?X???b?h?I????a
	if(ui.chNGBlinkEnable->isChecked()){
		PClass->tNGBlink.StopFlag=false;
		PClass->tNGBlink.start();
	}
	else{
		PClass->tNGBlink.StopFlag=true;
	}

	//twHistoryColor
	if(PClass->GetOnlyFColor()==ui.pbShowSigGraph->palette().color(QPalette::Button).name()){
		PClass->twHistoryFrontColor	=PClass->twNGListFrontColor	=QColor(Qt::green);
	}
	else{
		PClass->twHistoryFrontColor	=PClass->twNGListFrontColor	=QColor(PClass->GetOnlyFColor());
	}
	if(PClass->GetOnlyBColor()==ui.pbShowSigGraph->palette().color(QPalette::Button).name()){
		PClass->twHistoryBackColor	=PClass->twNGListBackColor	=QColor(Qt::blue);
	}
	else{
		PClass->twHistoryBackColor	=PClass->twNGListBackColor	=QColor(PClass->GetOnlyBColor());
	}
	if(PClass->GetFBColor()==ui.pbShowSigGraph->palette().color(QPalette::Button).name()){
		PClass->twHistoryBothColor	=QColor(Qt::magenta);
	}
	else{
		PClass->twHistoryBothColor	=QColor(PClass->GetFBColor());
	}

	accept();
}

void GeneralSettingForm::pbCancelClicked()
{
	if(ApplySigmoid){
		pbOKClicked();
		ApplySigmoid=false;
		accept();
	}
	reject();
}

void GeneralSettingForm::pbMMCSettingClicked()
{
	QStringList MMCSettingList;
	if(DLL_MMCSettingFormShow(MMCSettingList)==false){
		return;
	}
	//?t?@?C???E?U?÷
	PClass->SaveFile(LangSolver.GetString(GeneralSettingForm_LS,LID_450)/*"./MMCSetting.dat"*/,&MMCSettingList);
	PClass->DLL_SetMMCParameter(PClass->GetHistoryList(),PClass->GetHFieldNames());

	//NG???X?g?I?˜?a
	PClass->GetNGList()->SetEnableListControl(MMCSettingList.at(9).toInt());
}

void GeneralSettingForm::on_pbSetColor_clicked()
{
	DLL_FormShow();
}