#include "CameraXtumiPx8LineTriggerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraGraphinXCM8040\CameraGraphin\camerasetting.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "math.h"
#include "CameraSetting.h"
#include "CLHS_PX8CommandCreater.h"
#include "sapClassBasic.h"
#include "featureCtrl.h"

CameraSetting::CameraSetting(CLHS_PX8Setting *s ,featureCtrl *f ,QWidget *parent)
    : QDialog(parent)
{
	Setting		=s;
	Feature		=f;

	ui.setupUi(this);
	LangSolver.SetUI(this);
	Setting->LoadFromCam(Feature);

	ui.spinBoxLineRate			->setValue(Setting->LineRate);
	ui.doubleSpinBoxExposureTime->setValue(Setting->ExposureTime);
	ui.checkBoxDirection		->setChecked(Setting->TDIDirection);

	ui.doubleSpinBoxGainRed		->setValue(Setting->GainRed);
	ui.spinBoxOffsetRed			->setValue(Setting->OffsetRed);
	ui.doubleSpinBoxGainGreen	->setValue(Setting->GainGreen);
	ui.spinBoxOffsetGreen		->setValue(Setting->OffsetGreen);
	ui.doubleSpinBoxGainBlue	->setValue(Setting->GainBlue);
	ui.spinBoxOffsetBlue		->setValue(Setting->OffsetBlue);

	ui.doubleSpinBoxGainRedL	->setValue(Setting->GainRedL);
	ui.spinBoxOffsetRedL		->setValue(Setting->OffsetRedL);
	ui.doubleSpinBoxGainGreenL	->setValue(Setting->GainGreenL);
	ui.spinBoxOffsetGreenL		->setValue(Setting->OffsetGreenL);
	ui.doubleSpinBoxGainBlueL	->setValue(Setting->GainBlueL);
	ui.spinBoxOffsetBlueL		->setValue(Setting->OffsetBlueL);

	ui.doubleSpinBoxGainRedR	->setValue(Setting->GainRedR);
	ui.spinBoxOffsetRedR		->setValue(Setting->OffsetRedR);
	ui.doubleSpinBoxGainGreenR	->setValue(Setting->GainGreenR);
	ui.spinBoxOffsetGreenR		->setValue(Setting->OffsetGreenR);
	ui.doubleSpinBoxGainBlueR	->setValue(Setting->GainBlueR);
	ui.spinBoxOffsetBlueR		->setValue(Setting->OffsetBlueR);

	ui.doubleSpinBoxRedMultipleX	->setValue(Setting->MultipleRed);
	ui.doubleSpinBoxGreenMultipleX	->setValue(Setting->MultipleGreen);
	ui.doubleSpinBoxBlueMultipleX	->setValue(Setting->MultipleBlue);
	ui.spinBoxRedOffsetX			->setValue(Setting->OffsetXRed);
	ui.spinBoxGreenOffsetX			->setValue(Setting->OffsetXGreen);
	ui.spinBoxBlueOffsetX			->setValue(Setting->OffsetXBlue);
	ui.spinBoxRedOffsetY			->setValue(Setting->OffsetYRed);
	ui.spinBoxGreenOffsetY			->setValue(Setting->OffsetYGreen);
	ui.spinBoxBlueOffsetY			->setValue(Setting->OffsetYBlue);
	ui.spinBoxHorizontalBinning		->setValue(Setting->HorizontalBinning);
	ui.spinBoxVerticalBinning		->setValue(Setting->VerticalBinning);
	ui.checkBoxLeftRight			->setChecked(Setting->LeftRight);
	ui.checkBoxExternalTrigger		->setChecked(Setting->ExternalTrigger);
	ui.checkBoxAutoBlackLevel		->setChecked(Setting->AutoBlackLevel);
	ui.checkBoxCalibrateFPN			->setChecked(Setting->CalibrateFPN);
	ui.spinBoxROIOffset				->setValue(Setting->ROIOffset);
	ui.spinBoxLightOffMilisec		->setValue(Setting->LightOffMilisec);
	ui.spinBoxLightOnMilisec		->setValue(Setting->LightOnMilisec);

	for(int x=0;x<Setting->CamDepth;x++){
		ui.bgRedBrightnessGraph->SetYData	(x,Setting->RedCustomLut[x]);		//RedGraph
		ui.bgGreenBrightnessGraph->SetYData	(x,Setting->GreenCustomLut[x]);	//GreenGraph
		ui.bgBlueBrightnessGraph->SetYData	(x,Setting->BlueCustomLut[x]);		//BlueGraph
	}

	RedFirstPoint	=0;
	RedSecondPoint	=0;
	RedFirstX		=0;
	RedFirstY		=0;
	RedSecondX		=0;
	RedSecondY		=0;

	GreenFirstPoint	=0;
	GreenSecondPoint=0;
	GreenFirstX		=0;
	GreenFirstY		=0;
	GreenSecondX	=0;
	GreenSecondY	=0;

	BlueFirstPoint	=0;
	BlueSecondPoint	=0;
	BlueFirstX		=0;
	BlueFirstY		=0;
	BlueSecondX		=0;
	BlueSecondY		=0;


	//Red
	Setting->RedApply=false;
	ui.sbRedFirstPoint->setEnabled(false);
	ui.sbRedSecondPoint->setEnabled(false);
	ui.sbRedFirstXCoordinates->setEnabled(false);
	ui.sbRedFirstYCoordinates->setEnabled(false);
	ui.sbRedSecondXCoordinates->setEnabled(false);
	ui.sbRedSecondYCoordinates->setEnabled(false);
	ui.bgRedBrightnessGraph->SetBarColor(QColor(Qt::red));
	//Green
	Setting->GreenApply=false;
	ui.sbGreenFirstPoint->setEnabled(false);
	ui.sbGreenSecondPoint->setEnabled(false);
	ui.sbGreenFirstXCoordinates->setEnabled(false);
	ui.sbGreenFirstYCoordinates->setEnabled(false);
	ui.sbGreenSecondXCoordinates->setEnabled(false);
	ui.sbGreenSecondYCoordinates->setEnabled(false);
	ui.bgGreenBrightnessGraph->SetBarColor(QColor(Qt::green));
	//Blue
	Setting->BlueApply=false;
	ui.sbBlueFirstPoint->setEnabled(false);
	ui.sbBlueSecondPoint->setEnabled(false);
	ui.sbBlueFirstXCoordinates->setEnabled(false);
	ui.sbBlueFirstYCoordinates->setEnabled(false);
	ui.sbBlueSecondXCoordinates->setEnabled(false);
	ui.sbBlueSecondYCoordinates->setEnabled(false);
	ui.bgBlueBrightnessGraph->SetBarColor(QColor(Qt::blue));
	//Proof
	ui.leProofFile->setText(ProofDataFile);


	setUiBuff();

	
	pbProofFlag=false;
	pbProofCancelFlag=false;
	connect(ui.pbProofCancel,SIGNAL(clicked()),this,SLOT(pbProofCancel_clicked()));

	ui.checkBoxCameraControl->setChecked(Setting->CameraControl);
	on_checkBoxCameraControl_clicked();
}

CameraSetting::~CameraSetting()
{

}

void CameraSetting::on_pbCancel_clicked()
{
	done(false);
}

void CameraSetting::on_pbOK_clicked()
{
	Setting->CameraControl	=ui.checkBoxCameraControl->isChecked();

	if(Setting->RedApply==true){
		for(int i=0; i<Setting->CamDepth; i++)
			Setting->RedCustomLut[i]=ui.bgRedBrightnessGraph->GetYData(i);
	}
	if(Setting->GreenApply==true){
		for(int i=0; i<Setting->CamDepth; i++)
			Setting->GreenCustomLut[i]=ui.bgGreenBrightnessGraph->GetYData(i);
	}
	if(Setting->BlueApply==true){
		for(int i=0; i<Setting->CamDepth; i++)
			Setting->BlueCustomLut[i]=ui.bgBlueBrightnessGraph->GetYData(i);
	}

	if(pbProofFlag==true || pbProofCancelFlag==true)
		ProofDataFile=wProofDataFile;;

	Setting->LineRate		=ui.spinBoxLineRate				->value();
	Setting->ExposureTime	=ui.doubleSpinBoxExposureTime	->value();
	Setting->TDIDirection	=ui.checkBoxDirection			->isChecked();

	Setting->GainRed		=ui.doubleSpinBoxGainRed		->value();
	Setting->OffsetRed		=ui.spinBoxOffsetRed			->value();
	Setting->GainGreen		=ui.doubleSpinBoxGainGreen		->value();
	Setting->OffsetGreen	=ui.spinBoxOffsetGreen			->value();
	Setting->GainBlue		=ui.doubleSpinBoxGainBlue		->value();
	Setting->OffsetBlue		=ui.spinBoxOffsetBlue			->value();

	Setting->GainRedL		=ui.doubleSpinBoxGainRedL		->value();
	Setting->OffsetRedL		=ui.spinBoxOffsetRedL			->value();
	Setting->GainGreenL		=ui.doubleSpinBoxGainGreenL		->value();
	Setting->OffsetGreenL	=ui.spinBoxOffsetGreenL			->value();
	Setting->GainBlueL		=ui.doubleSpinBoxGainBlueL		->value();
	Setting->OffsetBlueL	=ui.spinBoxOffsetBlueL			->value();

	Setting->GainRedR		=ui.doubleSpinBoxGainRedR		->value();
	Setting->OffsetRedR		=ui.spinBoxOffsetRedR			->value();
	Setting->GainGreenR		=ui.doubleSpinBoxGainGreenR		->value();
	Setting->OffsetGreenR	=ui.spinBoxOffsetGreenR			->value();
	Setting->GainBlueR		=ui.doubleSpinBoxGainBlueR		->value();
	Setting->OffsetBlueR	=ui.spinBoxOffsetBlueR			->value();

	Setting->MultipleRed	=ui.doubleSpinBoxRedMultipleX	->value();
	Setting->MultipleGreen	=ui.doubleSpinBoxGreenMultipleX	->value();
	Setting->MultipleBlue	=ui.doubleSpinBoxBlueMultipleX	->value();
	Setting->OffsetXRed		=ui.spinBoxRedOffsetX			->value();
	Setting->OffsetXGreen	=ui.spinBoxGreenOffsetX			->value();
	Setting->OffsetXBlue	=ui.spinBoxBlueOffsetX			->value();
	Setting->OffsetYRed		=ui.spinBoxRedOffsetY			->value();
	Setting->OffsetYGreen	=ui.spinBoxGreenOffsetY			->value();
	Setting->OffsetYBlue	=ui.spinBoxBlueOffsetY			->value();

	Setting->HorizontalBinning	=ui.spinBoxHorizontalBinning->value();
	Setting->VerticalBinning	=ui.spinBoxVerticalBinning	->value();
	Setting->LeftRight			=ui.checkBoxLeftRight		->isChecked();
	Setting->ExternalTrigger	=ui.checkBoxExternalTrigger	->isChecked();
	Setting->AutoBlackLevel		=ui.checkBoxAutoBlackLevel	->isChecked();
	Setting->CalibrateFPN		=ui.checkBoxCalibrateFPN	->isChecked();
	Setting->ROIOffset			=ui.spinBoxROIOffset		->value();
	Setting->LightOffMilisec	=ui.spinBoxLightOffMilisec	->value();
	Setting->LightOnMilisec		=ui.spinBoxLightOnMilisec	->value();
	Setting->StoreToCam(Feature);
	moveData();

	done(true);
}

//Drawing graph
void CameraSetting::GraphDraw(ColorType Color,int gIndex)
{
	this->setCursor(QCursor(Qt::WaitCursor));
	//Red
	switch(Color){
		case Red:
			//Default
			if(gIndex==Default){
				for(int x=0;x<Setting->CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,Setting->RedCustomLut[x]);
			}
			//Straight Line
			else if(gIndex==StraightLine){
				//Error processing
				if(RedSecondX-RedFirstX<=0){
					QMessageBox::critical(this
										,LangSolver.GetString(camerasetting_LS,LID_0)/*"Error"*/
										,LangSolver.GetString(camerasetting_LS,LID_1)/*"Coordinates are not correct!"*/);
					return;
				}
				//Inclination:(RedSecondY-RedFirstY)/(RedSecondX-RedFirstX)
				for(int x=0;x<=RedFirstX;x++)
					ui.bgRedBrightnessGraph->SetYData(x,RedFirstY);
				int RedB=RedFirstY-(RedFirstX*(RedSecondY-RedFirstY)/(RedSecondX-RedFirstX));
				for(int x=RedFirstX+1;x<RedSecondX;x++)
					ui.bgRedBrightnessGraph->SetYData(x,x*(RedSecondY-RedFirstY)/(RedSecondX-RedFirstX)+RedB);
				for(int x=RedSecondX;x<Setting->CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,RedSecondY);
			}
			//Hight Pass
			else if(gIndex==HightPass){
				for(int x=0;x<RedFirstPoint;x++)
					ui.bgRedBrightnessGraph->SetYData(x,0);
				for(int x=RedFirstPoint;x<Setting->CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,255);
			}
			//Low Pass
			else if(gIndex==LowPass){
				for(int x=0;x<RedFirstPoint;x++)
					ui.bgRedBrightnessGraph->SetYData(x,255);
				for(int x=RedFirstPoint;x<Setting->CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,0);
			}
			//UpDown Pass
			else if(gIndex==UpDownPass){
				for(int x=0;x<RedFirstPoint;x++)
					ui.bgRedBrightnessGraph->SetYData(x,0);
				for(int x=RedFirstPoint;x<RedSecondPoint;x++)
					ui.bgRedBrightnessGraph->SetYData(x,255);
				for(int x=RedSecondPoint;x<Setting->CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,0);
			}
			//DownUp Pass
			else if(gIndex==DownUpPass){
				for(int x=0;x<RedFirstPoint;x++)
					ui.bgRedBrightnessGraph->SetYData(x,255);
				for(int x=RedFirstPoint;x<RedSecondPoint;x++)
					ui.bgRedBrightnessGraph->SetYData(x,0);
				for(int x=RedSecondPoint;x<Setting->CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,255);
			}
			//Shigmoid Curve
			else if(gIndex==ShigmoidCurve){
				for(int x=0;x<Setting->CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,256/(1+exp((double)(RedFirstPoint-x))));
			}
			//Logarithm
			else if(gIndex==Logarithm){
				for(int x=1;x<Setting->CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x-1,46*log((double)x));
				ui.bgRedBrightnessGraph->SetYData(255,255);
			}
			break;
		case Green:
			//Default
			if(gIndex==Default){
				for(int x=0;x<Setting->CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,Setting->GreenCustomLut[x]);
			}
			//Straight Line
			if(gIndex==StraightLine){
				//Error processing
				if(GreenSecondX-GreenFirstX<=0){
					QMessageBox::critical(this
										,LangSolver.GetString(camerasetting_LS,LID_2)/*"Error"*/
										,LangSolver.GetString(camerasetting_LS,LID_3)/*"Coordinates are not correct!"*/);
					return;
				}
				//Inclination:(GreenSecondY-GreenFirstY)/(GreenSecondX-GreenFirstX)
				for(int x=0;x<=GreenFirstX;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,GreenFirstY);
				int GreenB=GreenFirstY-(GreenFirstX*(GreenSecondY-GreenFirstY)/(GreenSecondX-GreenFirstX));
				for(int x=GreenFirstX+1;x<GreenSecondX;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,x*(GreenSecondY-GreenFirstY)/(GreenSecondX-GreenFirstX)+GreenB);
				for(int x=GreenSecondX;x<Setting->CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,GreenSecondY);
			}
			//Hight Pass
			else if(gIndex==HightPass){
				for(int x=0;x<GreenFirstPoint;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,0);
				for(int x=GreenFirstPoint;x<Setting->CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,255);
			}
			//Low Pass
			else if(gIndex==LowPass){
				for(int x=0;x<GreenFirstPoint;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,255);
				for(int x=GreenFirstPoint;x<Setting->CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,0);
			}
			//UpDown Pass
			else if(gIndex==UpDownPass){
				for(int x=0;x<GreenFirstPoint;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,0);
				for(int x=GreenFirstPoint;x<GreenSecondPoint;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,255);
				for(int x=GreenSecondPoint;x<Setting->CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,0);
			}
			//DownUp Pass
			else if(gIndex==DownUpPass){
				for(int x=0;x<GreenFirstPoint;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,255);
				for(int x=GreenFirstPoint;x<GreenSecondPoint;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,0);
				for(int x=GreenSecondPoint;x<Setting->CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,255);
			}
			//Shigmoid Curve
			else if(gIndex==ShigmoidCurve){
				for(int x=0;x<Setting->CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,256/(1+exp((double)(GreenFirstPoint-x))));
			}
			//Logarithm
			else if(gIndex==Logarithm){
				for(int x=1;x<Setting->CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x-1,46*log((double)x));
				ui.bgGreenBrightnessGraph->SetYData(255,255);
			}
			break;
		case Blue:
			//Default
			if(gIndex==Default){
				for(int x=0;x<Setting->CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,Setting->BlueCustomLut[x]);
			}
			//Straight Line
			if(gIndex==StraightLine){
				//Error processing
				if(BlueSecondX-BlueFirstX<=0){
					QMessageBox::critical(this
										,LangSolver.GetString(camerasetting_LS,LID_4)/*"Error"*/
										,LangSolver.GetString(camerasetting_LS,LID_5)/*"Coordinates are not correct!"*/);
					return;
				}
				//Inclination:(BlueSecondY-BlueFirstY)/(BlueSecondX-BlueFirstX)
				for(int x=0;x<=BlueFirstX;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,BlueFirstY);
				int BlueB=BlueFirstY-(BlueFirstX*(BlueSecondY-BlueFirstY)/(BlueSecondX-BlueFirstX));
				for(int x=BlueFirstX+1;x<BlueSecondX;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,x*(BlueSecondY-BlueFirstY)/(BlueSecondX-BlueFirstX)+BlueB);
				for(int x=BlueSecondX;x<Setting->CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,BlueSecondY);
			}
			//Hight Pass
			else if(gIndex==HightPass){
				for(int x=0;x<BlueFirstPoint;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,0);
				for(int x=BlueFirstPoint;x<Setting->CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,255);
			}
			//Low Pass
			else if(gIndex==LowPass){
				for(int x=0;x<BlueFirstPoint;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,255);
				for(int x=BlueFirstPoint;x<Setting->CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,0);
			}
			//UpDown Pass
			else if(gIndex==UpDownPass){
				for(int x=0;x<BlueFirstPoint;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,0);
				for(int x=BlueFirstPoint;x<BlueSecondPoint;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,255);
				for(int x=BlueSecondPoint;x<Setting->CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,0);
			}
			//DownUp Pass
			else if(gIndex==DownUpPass){
				for(int x=0;x<BlueFirstPoint;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,255);
				for(int x=BlueFirstPoint;x<BlueSecondPoint;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,0);
				for(int x=BlueSecondPoint;x<Setting->CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,255);
			}
			//Shigmoid Curve
			else if(gIndex==ShigmoidCurve){
				for(int x=0;x<Setting->CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,256/(1+exp((double)(BlueFirstPoint-x))));
			}
			//Logarithm
			else if(gIndex==Logarithm){
				for(int x=1;x<Setting->CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x-1,46*log((double)x));
				ui.bgBlueBrightnessGraph->SetYData(255,255);
			}
			break;
	}
	this->setCursor(QCursor(Qt::ArrowCursor));
}

void CameraSetting::on_pbRedApply_clicked()
{
	Setting->RedApply=true;
}

void CameraSetting::on_pbGreenApply_clicked()
{
	Setting->GreenApply=true;
}

void CameraSetting::on_pbBlueApply_clicked()
{
	Setting->BlueApply=true;
}

void CameraSetting::on_pbRedUpdate_clicked()
{
	//Acquisition of value
	RedFirstPoint=ui.sbRedFirstPoint->value();
	RedSecondPoint=ui.sbRedSecondPoint->value();
	RedFirstX=ui.sbRedFirstXCoordinates->value();
	RedFirstY=ui.sbRedFirstYCoordinates->value();
	RedSecondX=ui.sbRedSecondXCoordinates->value();
	RedSecondY=ui.sbRedSecondYCoordinates->value();
	//Re-Drawing graph
	GraphDraw(Red,ui.cbRedGraphType->currentIndex());
}

void CameraSetting::on_pbGreenUpdate_clicked()
{
	//Acquisition of value
	GreenFirstPoint=ui.sbGreenFirstPoint->value();
	GreenSecondPoint=ui.sbGreenSecondPoint->value();
	GreenFirstX=ui.sbGreenFirstXCoordinates->value();
	GreenFirstY=ui.sbGreenFirstYCoordinates->value();
	GreenSecondX=ui.sbGreenSecondXCoordinates->value();
	GreenSecondY=ui.sbGreenSecondYCoordinates->value();
	//Re-Drawing graph
	GraphDraw(Green,ui.cbGreenGraphType->currentIndex());
}

void CameraSetting::on_pbBlueUpdate_clicked()
{
	//Acquisition of value
	BlueFirstPoint=ui.sbBlueFirstPoint->value();
	BlueSecondPoint=ui.sbBlueSecondPoint->value();
	BlueFirstX=ui.sbBlueFirstXCoordinates->value();
	BlueFirstY=ui.sbBlueFirstYCoordinates->value();
	BlueSecondX=ui.sbBlueSecondXCoordinates->value();
	BlueSecondY=ui.sbBlueSecondYCoordinates->value();
	//Re-Drawing graph
	GraphDraw(Blue,ui.cbBlueGraphType->currentIndex());
}

void CameraSetting::on_pbProof_clicked()
{
	wProofDataFile=QFileDialog::getOpenFileName(
							this
							,LangSolver.GetString(camerasetting_LS,LID_6)/*"Please choose a '.dat' file."*/
							,LangSolver.GetString(camerasetting_LS,LID_7)/*""*/
							,LangSolver.GetString(camerasetting_LS,LID_8)/*"ProofDataFile (*.dat)"*/);
	if(wProofDataFile==LangSolver.GetString(camerasetting_LS,LID_9)/*""*/)
		return;
	ui.leProofFile->setText(wProofDataFile);
	pbProofFlag=true;
	pbProofCancelFlag=false;
}

void CameraSetting::on_pbProofCancel_clicked()
{
	wProofDataFile=LangSolver.GetString(camerasetting_LS,LID_10)/*""*/;
	ui.leProofFile->setText(wProofDataFile);
	pbProofCancelFlag=true;
	pbProofFlag=false;
}

//When the kind of the graph changes(Red)
void CameraSetting::on_cbRedGraphType_currentIndexChanged(int cIndex)
{
	//Default
	if(cIndex==Default){
		ui.sbRedFirstPoint->setEnabled(false);
		ui.sbRedSecondPoint->setEnabled(false);
		ui.sbRedFirstXCoordinates->setEnabled(false);
		ui.sbRedFirstYCoordinates->setEnabled(false);
		ui.sbRedSecondXCoordinates->setEnabled(false);
		ui.sbRedSecondYCoordinates->setEnabled(false);
	}
	//Straight Line
	else if(cIndex==StraightLine){
		ui.sbRedFirstPoint->setEnabled(false);
		ui.sbRedSecondPoint->setEnabled(false);
		ui.sbRedFirstXCoordinates->setEnabled(true);
		ui.sbRedFirstYCoordinates->setEnabled(true);
		ui.sbRedSecondXCoordinates->setEnabled(true);
		ui.sbRedSecondYCoordinates->setEnabled(true);
	}
	//Hight Pass
	else if(cIndex==HightPass){
		ui.sbRedFirstPoint->setEnabled(true);
		ui.sbRedSecondPoint->setEnabled(false);
		ui.sbRedFirstXCoordinates->setEnabled(false);
		ui.sbRedFirstYCoordinates->setEnabled(false);
		ui.sbRedSecondXCoordinates->setEnabled(false);
		ui.sbRedSecondYCoordinates->setEnabled(false);
	}
	//Low Pass
	else if(cIndex==LowPass){
		ui.sbRedFirstPoint->setEnabled(true);
		ui.sbRedSecondPoint->setEnabled(false);
		ui.sbRedFirstXCoordinates->setEnabled(false);
		ui.sbRedFirstYCoordinates->setEnabled(false);
		ui.sbRedSecondXCoordinates->setEnabled(false);
		ui.sbRedSecondYCoordinates->setEnabled(false);
	}
	//UpDown Pass
	else if(cIndex==UpDownPass){
		ui.sbRedFirstPoint->setEnabled(true);
		ui.sbRedSecondPoint->setEnabled(true);
		ui.sbRedFirstXCoordinates->setEnabled(false);
		ui.sbRedFirstYCoordinates->setEnabled(false);
		ui.sbRedSecondXCoordinates->setEnabled(false);
		ui.sbRedSecondYCoordinates->setEnabled(false);
	}
	//DownUp Pass
	else if(cIndex==DownUpPass){
		ui.sbRedFirstPoint->setEnabled(true);
		ui.sbRedSecondPoint->setEnabled(true);
		ui.sbRedFirstXCoordinates->setEnabled(false);
		ui.sbRedFirstYCoordinates->setEnabled(false);
		ui.sbRedSecondXCoordinates->setEnabled(false);
		ui.sbRedSecondYCoordinates->setEnabled(false);
	}
	//Shigmoid Curve
	else if(cIndex==ShigmoidCurve){
		ui.sbRedFirstPoint->setEnabled(false);
		ui.sbRedSecondPoint->setEnabled(false);
		ui.sbRedFirstXCoordinates->setEnabled(false);
		ui.sbRedFirstYCoordinates->setEnabled(false);
		ui.sbRedSecondXCoordinates->setEnabled(false);
		ui.sbRedSecondYCoordinates->setEnabled(false);
	}
	//Logarithm
	else if(cIndex==Logarithm){
		ui.sbRedFirstPoint->setEnabled(false);
		ui.sbRedSecondPoint->setEnabled(false);
		ui.sbRedFirstXCoordinates->setEnabled(false);
		ui.sbRedFirstYCoordinates->setEnabled(false);
		ui.sbRedSecondXCoordinates->setEnabled(false);
		ui.sbRedSecondYCoordinates->setEnabled(false);
	}
}

//When the kind of the graph changes(Green)
void CameraSetting::on_cbGreenGraphType_currentIndexChanged(int cIndex)
{
	//Default
	if(cIndex==Default){
		ui.sbGreenFirstPoint->setEnabled(false);
		ui.sbGreenSecondPoint->setEnabled(false);
		ui.sbGreenFirstXCoordinates->setEnabled(false);
		ui.sbGreenFirstYCoordinates->setEnabled(false);
		ui.sbGreenSecondXCoordinates->setEnabled(false);
		ui.sbGreenSecondYCoordinates->setEnabled(false);
	}
	//Straight Line
	else if(cIndex==StraightLine){
		ui.sbGreenFirstPoint->setEnabled(false);
		ui.sbGreenSecondPoint->setEnabled(false);
		ui.sbGreenFirstXCoordinates->setEnabled(true);
		ui.sbGreenFirstYCoordinates->setEnabled(true);
		ui.sbGreenSecondXCoordinates->setEnabled(true);
		ui.sbGreenSecondYCoordinates->setEnabled(true);
	}
	//Hight Pass
	else if(cIndex==HightPass){
		ui.sbGreenFirstPoint->setEnabled(true);
		ui.sbGreenSecondPoint->setEnabled(false);
		ui.sbGreenFirstXCoordinates->setEnabled(false);
		ui.sbGreenFirstYCoordinates->setEnabled(false);
		ui.sbGreenSecondXCoordinates->setEnabled(false);
		ui.sbGreenSecondYCoordinates->setEnabled(false);
	}
	//Low Pass
	else if(cIndex==LowPass){
		ui.sbGreenFirstPoint->setEnabled(true);
		ui.sbGreenSecondPoint->setEnabled(false);
		ui.sbGreenFirstXCoordinates->setEnabled(false);
		ui.sbGreenFirstYCoordinates->setEnabled(false);
		ui.sbGreenSecondXCoordinates->setEnabled(false);
		ui.sbGreenSecondYCoordinates->setEnabled(false);
	}
	//UpDown Pass
	else if(cIndex==UpDownPass){
		ui.sbGreenFirstPoint->setEnabled(true);
		ui.sbGreenSecondPoint->setEnabled(true);
		ui.sbGreenFirstXCoordinates->setEnabled(false);
		ui.sbGreenFirstYCoordinates->setEnabled(false);
		ui.sbGreenSecondXCoordinates->setEnabled(false);
		ui.sbGreenSecondYCoordinates->setEnabled(false);
	}
	//DownUp Pass
	else if(cIndex==DownUpPass){
		ui.sbGreenFirstPoint->setEnabled(true);
		ui.sbGreenSecondPoint->setEnabled(true);
		ui.sbGreenFirstXCoordinates->setEnabled(false);
		ui.sbGreenFirstYCoordinates->setEnabled(false);
		ui.sbGreenSecondXCoordinates->setEnabled(false);
		ui.sbGreenSecondYCoordinates->setEnabled(false);
	}
	//Shigmoid Curve
	else if(cIndex==ShigmoidCurve){
		ui.sbGreenFirstPoint->setEnabled(false);
		ui.sbGreenSecondPoint->setEnabled(false);
		ui.sbGreenFirstXCoordinates->setEnabled(false);
		ui.sbGreenFirstYCoordinates->setEnabled(false);
		ui.sbGreenSecondXCoordinates->setEnabled(false);
		ui.sbGreenSecondYCoordinates->setEnabled(false);
	}
	//Logarithm
	else if(cIndex==Logarithm){
		ui.sbGreenFirstPoint->setEnabled(false);
		ui.sbGreenSecondPoint->setEnabled(false);
		ui.sbGreenFirstXCoordinates->setEnabled(false);
		ui.sbGreenFirstYCoordinates->setEnabled(false);
		ui.sbGreenSecondXCoordinates->setEnabled(false);
		ui.sbGreenSecondYCoordinates->setEnabled(false);
	}
}

//When the kind of the graph changes(Blue)
void CameraSetting::on_cbBlueGraphType_currentIndexChanged(int cIndex)
{
	//Default
	if(cIndex==Default){
		ui.sbBlueFirstPoint->setEnabled(false);
		ui.sbBlueSecondPoint->setEnabled(false);
		ui.sbBlueFirstXCoordinates->setEnabled(false);
		ui.sbBlueFirstYCoordinates->setEnabled(false);
		ui.sbBlueSecondXCoordinates->setEnabled(false);
		ui.sbBlueSecondYCoordinates->setEnabled(false);
	}
	//Straight Line
	else if(cIndex==StraightLine){
		ui.sbBlueFirstPoint->setEnabled(false);
		ui.sbBlueSecondPoint->setEnabled(false);
		ui.sbBlueFirstXCoordinates->setEnabled(true);
		ui.sbBlueFirstYCoordinates->setEnabled(true);
		ui.sbBlueSecondXCoordinates->setEnabled(true);
		ui.sbBlueSecondYCoordinates->setEnabled(true);
	}
	//Hight Pass
	else if(cIndex==HightPass){
		ui.sbBlueFirstPoint->setEnabled(true);
		ui.sbBlueSecondPoint->setEnabled(false);
		ui.sbBlueFirstXCoordinates->setEnabled(false);
		ui.sbBlueFirstYCoordinates->setEnabled(false);
		ui.sbBlueSecondXCoordinates->setEnabled(false);
		ui.sbBlueSecondYCoordinates->setEnabled(false);
	}
	//Low Pass
	else if(cIndex==LowPass){
		ui.sbBlueFirstPoint->setEnabled(true);
		ui.sbBlueSecondPoint->setEnabled(false);
		ui.sbBlueFirstXCoordinates->setEnabled(false);
		ui.sbBlueFirstYCoordinates->setEnabled(false);
		ui.sbBlueSecondXCoordinates->setEnabled(false);
		ui.sbBlueSecondYCoordinates->setEnabled(false);
	}
	//UpDown Pass
	else if(cIndex==UpDownPass){
		ui.sbBlueFirstPoint->setEnabled(true);
		ui.sbBlueSecondPoint->setEnabled(true);
		ui.sbBlueFirstXCoordinates->setEnabled(false);
		ui.sbBlueFirstYCoordinates->setEnabled(false);
		ui.sbBlueSecondXCoordinates->setEnabled(false);
		ui.sbBlueSecondYCoordinates->setEnabled(false);
	}
	//DownUp Pass
	else if(cIndex==DownUpPass){
		ui.sbBlueFirstPoint->setEnabled(true);
		ui.sbBlueSecondPoint->setEnabled(true);
		ui.sbBlueFirstXCoordinates->setEnabled(false);
		ui.sbBlueFirstYCoordinates->setEnabled(false);
		ui.sbBlueSecondXCoordinates->setEnabled(false);
		ui.sbBlueSecondYCoordinates->setEnabled(false);
	}
	//Shigmoid Curve
	else if(cIndex==ShigmoidCurve){
		ui.sbBlueFirstPoint->setEnabled(false);
		ui.sbBlueSecondPoint->setEnabled(false);
		ui.sbBlueFirstXCoordinates->setEnabled(false);
		ui.sbBlueFirstYCoordinates->setEnabled(false);
		ui.sbBlueSecondXCoordinates->setEnabled(false);
		ui.sbBlueSecondYCoordinates->setEnabled(false);
	}
	//Logarithm
	else if(cIndex==Logarithm){
		ui.sbBlueFirstPoint->setEnabled(false);
		ui.sbBlueSecondPoint->setEnabled(false);
		ui.sbBlueFirstXCoordinates->setEnabled(false);
		ui.sbBlueFirstYCoordinates->setEnabled(false);
		ui.sbBlueSecondXCoordinates->setEnabled(false);
		ui.sbBlueSecondYCoordinates->setEnabled(false);
	}
}

void CameraSetting::moveData(void)
{
	Setting->RedBrightness		=ui.lnRedBrightness->value();
	Setting->RedContrast		=ui.lnRedContrast->value();
	Setting->RedGamma			=ui.lnRedGamma->value();
	Setting->RedFloor			=ui.sbRedFloor->value();
	Setting->RedCeiling			=ui.sbRedCeiling->value();

	RedFirstPoint	=ui.sbRedFirstPoint->value();
	RedSecondPoint	=ui.sbRedSecondPoint->value();


	Setting->GreenBrightness	=ui.lnGreenBrightness->value();
	Setting->GreenContrast		=ui.lnGreenContrast->value();
	Setting->GreenGamma			=ui.lnGreenGamma->value();
	Setting->GreenFloor			=ui.sbGreenFloor->value();
	Setting->GreenCeiling		=ui.sbGreenCeiling->value();
	GreenFirstPoint	=ui.sbGreenFirstPoint->value();
	GreenSecondPoint=ui.sbGreenSecondPoint->value();


	Setting->BlueBrightness		=ui.lnBlueBrightness->value();
	Setting->BlueContrast		=ui.lnBlueContrast->value();
	Setting->BlueGamma			=ui.lnBlueGamma->value();
	Setting->BlueFloor			=ui.sbBlueFloor->value();
	Setting->BlueCeiling		=ui.sbBlueCeiling->value();
	BlueFirstPoint	=ui.sbBlueFirstPoint->value();
	BlueSecondPoint	=ui.sbBlueSecondPoint->value();
}

void CameraSetting::setUiBuff(void)
{
	ui.hsRedBrightness			->setValue(Setting->RedBrightness);
	ui.hsRedContrast			->setValue(Setting->RedContrast);
	ui.hsRedGamma				->setValue(Setting->RedGamma);
	ui.sbRedFloor				->setValue(Setting->RedFloor);
	ui.sbRedCeiling				->setValue(Setting->RedCeiling);
	ui.sbRedFirstPoint			->setValue(RedFirstPoint);
	ui.sbRedSecondPoint			->setValue(RedSecondPoint);

	ui.hsGreenBrightness		->setValue(Setting->GreenBrightness);
	ui.hsGreenContrast			->setValue(Setting->GreenContrast);
	ui.hsGreenGamma				->setValue(Setting->GreenGamma);
	ui.sbGreenFloor				->setValue(Setting->GreenFloor);
	ui.sbGreenCeiling			->setValue(Setting->GreenCeiling);
	ui.sbGreenFirstPoint		->setValue(GreenFirstPoint);
	ui.sbGreenSecondPoint		->setValue(GreenSecondPoint);

	ui.hsBlueBrightness			->setValue(Setting->BlueBrightness);
	ui.hsBlueContrast			->setValue(Setting->BlueContrast);
	ui.hsBlueGamma				->setValue(Setting->BlueGamma);
	ui.sbBlueFloor				->setValue(Setting->BlueFloor);
	ui.sbBlueCeiling			->setValue(Setting->BlueCeiling);
	ui.sbBlueFirstPoint			->setValue(BlueFirstPoint);
	ui.sbBlueSecondPoint		->setValue(BlueSecondPoint);
}
bool	CameraSetting::SetQuickProperty(CameraQuickProperty Attr, double RelativeValue)
{
	return Setting->SetQuickProperty(Feature ,Attr, RelativeValue);
}
void CameraSetting::on_checkBoxCameraControl_clicked()
{
	ui.spinBoxLineRate				->setVisible(ui.checkBoxCameraControl->isChecked());
	ui.doubleSpinBoxExposureTime	->setVisible(ui.checkBoxCameraControl->isChecked());
	ui.checkBoxDirection			->setVisible(ui.checkBoxCameraControl->isChecked());
	ui.doubleSpinBoxGainRed			->setVisible(ui.checkBoxCameraControl->isChecked());
	ui.spinBoxOffsetRed				->setVisible(ui.checkBoxCameraControl->isChecked());
	ui.doubleSpinBoxGainGreen		->setVisible(ui.checkBoxCameraControl->isChecked());
	ui.spinBoxOffsetGreen			->setVisible(ui.checkBoxCameraControl->isChecked());
	ui.doubleSpinBoxGainBlue		->setVisible(ui.checkBoxCameraControl->isChecked());
	ui.spinBoxOffsetBlue			->setVisible(ui.checkBoxCameraControl->isChecked());
	ui.spinBoxHorizontalBinning		->setVisible(ui.checkBoxCameraControl->isChecked());
	ui.spinBoxVerticalBinning		->setVisible(ui.checkBoxCameraControl->isChecked());
	ui.checkBoxExternalTrigger		->setVisible(ui.checkBoxCameraControl->isChecked());
	ui.checkBoxAutoBlackLevel		->setVisible(ui.checkBoxCameraControl->isChecked());
	ui.checkBoxCalibrateFPN			->setVisible(ui.checkBoxCameraControl->isChecked());
}
