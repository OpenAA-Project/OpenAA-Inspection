//#include "CameraXtumiPx8LineTriggerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraGraphinXCM8040\CameraGraphin\camerasettingcolor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "math.h"
#include "CameraSettingColor.h"
#include "CLHS_PX8CommandCreater.h"
#include "sapClassBasic.h"
#include "featureCtrl.h"
#include "CameraXtiumLinearHSColorMonoLineTrigger.h"

CameraSettingColor::CameraSettingColor(CameraXtiumLinearHSColor *s ,featureCtrl *f ,QWidget *parent)
    : QDialog(parent)
{
	Cam		=s;
	Feature		=f;

	ui.setupUi(this);
	//LangSolver.SetUI(this);
	Cam->Setting.LoadFromCam(Feature);

	ui.spinBoxLineRate			->setValue  (Cam->Setting.LineRate);
	//ui.doubleSpinBoxExposureTime->setValue  (Cam->Setting.ExposureTime);
	ui.checkBoxDirection		->setChecked(Cam->Setting.TDIDirection);

	ui.doubleSpinBoxGainRed		->setValue(Cam->Setting.GainRed);
	ui.spinBoxOffsetRed			->setValue(Cam->Setting.OffsetRed);
	ui.doubleSpinBoxGainGreen	->setValue(Cam->Setting.GainGreen);
	ui.spinBoxOffsetGreen		->setValue(Cam->Setting.OffsetGreen);
	ui.doubleSpinBoxGainBlue	->setValue(Cam->Setting.GainBlue);
	ui.spinBoxOffsetBlue		->setValue(Cam->Setting.OffsetBlue);

	ui.doubleSpinBoxGainRedL	->setValue(Cam->Setting.GainRedL);
	ui.spinBoxOffsetRedL		->setValue(Cam->Setting.OffsetRedL);
	ui.doubleSpinBoxGainGreenL	->setValue(Cam->Setting.GainGreenL);
	ui.spinBoxOffsetGreenL		->setValue(Cam->Setting.OffsetGreenL);
	ui.doubleSpinBoxGainBlueL	->setValue(Cam->Setting.GainBlueL);
	ui.spinBoxOffsetBlueL		->setValue(Cam->Setting.OffsetBlueL);

	ui.doubleSpinBoxGainRedR	->setValue(Cam->Setting.GainRedR);
	ui.spinBoxOffsetRedR		->setValue(Cam->Setting.OffsetRedR);
	ui.doubleSpinBoxGainGreenR	->setValue(Cam->Setting.GainGreenR);
	ui.spinBoxOffsetGreenR		->setValue(Cam->Setting.OffsetGreenR);
	ui.doubleSpinBoxGainBlueR	->setValue(Cam->Setting.GainBlueR);
	ui.spinBoxOffsetBlueR		->setValue(Cam->Setting.OffsetBlueR);

	ui.doubleSpinBoxRedMultipleX	->setValue  (Cam->Setting.MultipleRed);
	ui.doubleSpinBoxGreenMultipleX	->setValue  (Cam->Setting.MultipleGreen);
	ui.doubleSpinBoxBlueMultipleX	->setValue  (Cam->Setting.MultipleBlue);
	ui.spinBoxRedOffsetX			->setValue  (Cam->Setting.OffsetXRed);
	ui.spinBoxGreenOffsetX			->setValue  (Cam->Setting.OffsetXGreen);
	ui.spinBoxBlueOffsetX			->setValue  (Cam->Setting.OffsetXBlue);
	ui.spinBoxRedOffsetY			->setValue  (Cam->Setting.OffsetYRed);
	ui.spinBoxGreenOffsetY			->setValue  (Cam->Setting.OffsetYGreen);
	ui.spinBoxBlueOffsetY			->setValue  (Cam->Setting.OffsetYBlue);
	ui.spinBoxHorizontalBinning		->setValue  (Cam->Setting.HorizontalBinning);
	ui.spinBoxVerticalBinning		->setValue  (Cam->Setting.VerticalBinning);
	ui.checkBoxLeftRight			->setChecked(Cam->Setting.LeftRight);
	ui.checkBoxExternalTrigger		->setChecked(Cam->Setting.ExternalTrigger);
	ui.checkBoxAutoBlackLevel		->setChecked(Cam->Setting.AutoBlackLevel);
	ui.checkBoxCalibrateFPN			->setChecked(Cam->Setting.CalibrateFPN);
	ui.spinBoxROIOffset				->setValue  (Cam->Setting.ROIOffset);
	ui.comboBoxAnalogGain			->setCurrentIndex  (Cam->Setting.AnalogGain);

	for(int x=0;x<CamDepth;x++){
		ui.bgRedBrightnessGraph->SetYData	(x,Cam->Setting.RedCustomLut[x]);		//RedGraph
		ui.bgGreenBrightnessGraph->SetYData	(x,Cam->Setting.GreenCustomLut[x]);	//GreenGraph
		ui.bgBlueBrightnessGraph->SetYData	(x,Cam->Setting.BlueCustomLut[x]);		//BlueGraph
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
	Cam->Setting.RedApply=false;
	ui.sbRedFirstPoint->setEnabled(false);
	ui.sbRedSecondPoint->setEnabled(false);
	ui.sbRedFirstXCoordinates->setEnabled(false);
	ui.sbRedFirstYCoordinates->setEnabled(false);
	ui.sbRedSecondXCoordinates->setEnabled(false);
	ui.sbRedSecondYCoordinates->setEnabled(false);
	ui.bgRedBrightnessGraph->SetBarColor(QColor(Qt::red));
	//Green
	Cam->Setting.GreenApply=false;
	ui.sbGreenFirstPoint->setEnabled(false);
	ui.sbGreenSecondPoint->setEnabled(false);
	ui.sbGreenFirstXCoordinates->setEnabled(false);
	ui.sbGreenFirstYCoordinates->setEnabled(false);
	ui.sbGreenSecondXCoordinates->setEnabled(false);
	ui.sbGreenSecondYCoordinates->setEnabled(false);
	ui.bgGreenBrightnessGraph->SetBarColor(QColor(Qt::green));
	//Blue
	Cam->Setting.BlueApply=false;
	ui.sbBlueFirstPoint->setEnabled(false);
	ui.sbBlueSecondPoint->setEnabled(false);
	ui.sbBlueFirstXCoordinates->setEnabled(false);
	ui.sbBlueFirstYCoordinates->setEnabled(false);
	ui.sbBlueSecondXCoordinates->setEnabled(false);
	ui.sbBlueSecondYCoordinates->setEnabled(false);
	ui.bgBlueBrightnessGraph->SetBarColor(QColor(Qt::blue));
	//Proof
	ui.leProofFile->setText(Cam->ProofDataFile);


	setUiBuff();

	
	Cam->pbProofFlag=false;
	Cam->pbProofCancelFlag=false;
	connect(ui.pbProofCancel,SIGNAL(clicked()),this,SLOT(pbProofCancel_clicked()));

	ui.checkBoxCameraControl->setChecked(Cam->Setting.CameraControl);
	on_checkBoxCameraControl_clicked();
}

CameraSettingColor::~CameraSettingColor()
{

}

void CameraSettingColor::on_pbCancel_clicked()
{
	done(false);
}

void CameraSettingColor::on_pbOK_clicked()
{
	Cam->Setting.CameraControl	=ui.checkBoxCameraControl->isChecked();

	if(Cam->Setting.RedApply==true){
		for(int i=0; i<CamDepth; i++)
			Cam->Setting.RedCustomLut[i]=ui.bgRedBrightnessGraph->GetYData(i);
	}
	if(Cam->Setting.GreenApply==true){
		for(int i=0; i<CamDepth; i++)
			Cam->Setting.GreenCustomLut[i]=ui.bgGreenBrightnessGraph->GetYData(i);
	}
	if(Cam->Setting.BlueApply==true){
		for(int i=0; i<CamDepth; i++)
			Cam->Setting.BlueCustomLut[i]=ui.bgBlueBrightnessGraph->GetYData(i);
	}

	if(Cam->pbProofFlag==true || Cam->pbProofCancelFlag==true)
		Cam->ProofDataFile=wProofDataFile;;

	Cam->Setting.LineRate		=ui.spinBoxLineRate				->value();
	//Cam->Setting.ExposureTime	=ui.doubleSpinBoxExposureTime	->value();
	Cam->Setting.TDIDirection	=ui.checkBoxDirection			->isChecked();

	Cam->Setting.GainRed		=ui.doubleSpinBoxGainRed		->value();
	Cam->Setting.OffsetRed		=ui.spinBoxOffsetRed			->value();
	Cam->Setting.GainGreen		=ui.doubleSpinBoxGainGreen		->value();
	Cam->Setting.OffsetGreen	=ui.spinBoxOffsetGreen			->value();
	Cam->Setting.GainBlue		=ui.doubleSpinBoxGainBlue		->value();
	Cam->Setting.OffsetBlue		=ui.spinBoxOffsetBlue			->value();

	Cam->Setting.GainRedL		=ui.doubleSpinBoxGainRedL		->value();
	Cam->Setting.OffsetRedL		=ui.spinBoxOffsetRedL			->value();
	Cam->Setting.GainGreenL		=ui.doubleSpinBoxGainGreenL		->value();
	Cam->Setting.OffsetGreenL	=ui.spinBoxOffsetGreenL			->value();
	Cam->Setting.GainBlueL		=ui.doubleSpinBoxGainBlueL		->value();
	Cam->Setting.OffsetBlueL	=ui.spinBoxOffsetBlueL			->value();

	Cam->Setting.GainRedR		=ui.doubleSpinBoxGainRedR		->value();
	Cam->Setting.OffsetRedR		=ui.spinBoxOffsetRedR			->value();
	Cam->Setting.GainGreenR		=ui.doubleSpinBoxGainGreenR		->value();
	Cam->Setting.OffsetGreenR	=ui.spinBoxOffsetGreenR			->value();
	Cam->Setting.GainBlueR		=ui.doubleSpinBoxGainBlueR		->value();
	Cam->Setting.OffsetBlueR	=ui.spinBoxOffsetBlueR			->value();

	Cam->Setting.MultipleRed	=ui.doubleSpinBoxRedMultipleX	->value();
	Cam->Setting.MultipleGreen	=ui.doubleSpinBoxGreenMultipleX	->value();
	Cam->Setting.MultipleBlue	=ui.doubleSpinBoxBlueMultipleX	->value();
	Cam->Setting.OffsetXRed		=ui.spinBoxRedOffsetX			->value();
	Cam->Setting.OffsetXGreen	=ui.spinBoxGreenOffsetX			->value();
	Cam->Setting.OffsetXBlue	=ui.spinBoxBlueOffsetX			->value();
	Cam->Setting.OffsetYRed		=ui.spinBoxRedOffsetY			->value();
	Cam->Setting.OffsetYGreen	=ui.spinBoxGreenOffsetY			->value();
	Cam->Setting.OffsetYBlue	=ui.spinBoxBlueOffsetY			->value();

	Cam->Setting.HorizontalBinning	=ui.spinBoxHorizontalBinning->value();
	Cam->Setting.VerticalBinning	=ui.spinBoxVerticalBinning	->value();
	Cam->Setting.LeftRight			=ui.checkBoxLeftRight		->isChecked();
	Cam->Setting.ExternalTrigger	=ui.checkBoxExternalTrigger	->isChecked();
	Cam->Setting.AutoBlackLevel		=ui.checkBoxAutoBlackLevel	->isChecked();
	Cam->Setting.CalibrateFPN		=ui.checkBoxCalibrateFPN	->isChecked();
	Cam->Setting.ROIOffset			=ui.spinBoxROIOffset		->value();
	Cam->Setting.AnalogGain			=ui.comboBoxAnalogGain		->currentIndex ();
	Cam->Setting.StoreToCam(Feature);

	moveData();

	done(true);
}

//Drawing graph
void CameraSettingColor::GraphDraw(ColorType Color,int gIndex)
{
	this->setCursor(QCursor(Qt::WaitCursor));
	//Red
	switch(Color){
		case Red:
			//Default
			if(gIndex==Default){
				for(int x=0;x<CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,Cam->Setting.RedCustomLut[x]);
			}
			//Straight Line
			else if(gIndex==StraightLine){
				//Error processing
				if(RedSecondX-RedFirstX<=0){
					QMessageBox::critical(this
										,"Error"
										,"Coordinates are not correct!");
					return;
				}
				//Inclination:(RedSecondY-RedFirstY)/(RedSecondX-RedFirstX)
				for(int x=0;x<=RedFirstX;x++)
					ui.bgRedBrightnessGraph->SetYData(x,RedFirstY);
				int RedB=RedFirstY-(RedFirstX*(RedSecondY-RedFirstY)/(RedSecondX-RedFirstX));
				for(int x=RedFirstX+1;x<RedSecondX;x++)
					ui.bgRedBrightnessGraph->SetYData(x,x*(RedSecondY-RedFirstY)/(RedSecondX-RedFirstX)+RedB);
				for(int x=RedSecondX;x<CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,RedSecondY);
			}
			//Hight Pass
			else if(gIndex==HightPass){
				for(int x=0;x<RedFirstPoint;x++)
					ui.bgRedBrightnessGraph->SetYData(x,0);
				for(int x=RedFirstPoint;x<CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,255);
			}
			//Low Pass
			else if(gIndex==LowPass){
				for(int x=0;x<RedFirstPoint;x++)
					ui.bgRedBrightnessGraph->SetYData(x,255);
				for(int x=RedFirstPoint;x<CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,0);
			}
			//UpDown Pass
			else if(gIndex==UpDownPass){
				for(int x=0;x<RedFirstPoint;x++)
					ui.bgRedBrightnessGraph->SetYData(x,0);
				for(int x=RedFirstPoint;x<RedSecondPoint;x++)
					ui.bgRedBrightnessGraph->SetYData(x,255);
				for(int x=RedSecondPoint;x<CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,0);
			}
			//DownUp Pass
			else if(gIndex==DownUpPass){
				for(int x=0;x<RedFirstPoint;x++)
					ui.bgRedBrightnessGraph->SetYData(x,255);
				for(int x=RedFirstPoint;x<RedSecondPoint;x++)
					ui.bgRedBrightnessGraph->SetYData(x,0);
				for(int x=RedSecondPoint;x<CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,255);
			}
			//Shigmoid Curve
			else if(gIndex==ShigmoidCurve){
				for(int x=0;x<CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x,256/(1+exp((double)(RedFirstPoint-x))));
			}
			//Logarithm
			else if(gIndex==Logarithm){
				for(int x=1;x<CamDepth;x++)
					ui.bgRedBrightnessGraph->SetYData(x-1,46*log((double)x));
				ui.bgRedBrightnessGraph->SetYData(255,255);
			}
			break;
		case Green:
			//Default
			if(gIndex==Default){
				for(int x=0;x<CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,Cam->Setting.GreenCustomLut[x]);
			}
			//Straight Line
			if(gIndex==StraightLine){
				//Error processing
				if(GreenSecondX-GreenFirstX<=0){
					QMessageBox::critical(this
										,"Error"
										,"Coordinates are not correct!");
					return;
				}
				//Inclination:(GreenSecondY-GreenFirstY)/(GreenSecondX-GreenFirstX)
				for(int x=0;x<=GreenFirstX;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,GreenFirstY);
				int GreenB=GreenFirstY-(GreenFirstX*(GreenSecondY-GreenFirstY)/(GreenSecondX-GreenFirstX));
				for(int x=GreenFirstX+1;x<GreenSecondX;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,x*(GreenSecondY-GreenFirstY)/(GreenSecondX-GreenFirstX)+GreenB);
				for(int x=GreenSecondX;x<CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,GreenSecondY);
			}
			//Hight Pass
			else if(gIndex==HightPass){
				for(int x=0;x<GreenFirstPoint;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,0);
				for(int x=GreenFirstPoint;x<CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,255);
			}
			//Low Pass
			else if(gIndex==LowPass){
				for(int x=0;x<GreenFirstPoint;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,255);
				for(int x=GreenFirstPoint;x<CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,0);
			}
			//UpDown Pass
			else if(gIndex==UpDownPass){
				for(int x=0;x<GreenFirstPoint;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,0);
				for(int x=GreenFirstPoint;x<GreenSecondPoint;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,255);
				for(int x=GreenSecondPoint;x<CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,0);
			}
			//DownUp Pass
			else if(gIndex==DownUpPass){
				for(int x=0;x<GreenFirstPoint;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,255);
				for(int x=GreenFirstPoint;x<GreenSecondPoint;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,0);
				for(int x=GreenSecondPoint;x<CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,255);
			}
			//Shigmoid Curve
			else if(gIndex==ShigmoidCurve){
				for(int x=0;x<CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x,256/(1+exp((double)(GreenFirstPoint-x))));
			}
			//Logarithm
			else if(gIndex==Logarithm){
				for(int x=1;x<CamDepth;x++)
					ui.bgGreenBrightnessGraph->SetYData(x-1,46*log((double)x));
				ui.bgGreenBrightnessGraph->SetYData(255,255);
			}
			break;
		case Blue:
			//Default
			if(gIndex==Default){
				for(int x=0;x<CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,Cam->Setting.BlueCustomLut[x]);
			}
			//Straight Line
			if(gIndex==StraightLine){
				//Error processing
				if(BlueSecondX-BlueFirstX<=0){
					QMessageBox::critical(this
										,"Error"
										,"Coordinates are not correct!");
					return;
				}
				//Inclination:(BlueSecondY-BlueFirstY)/(BlueSecondX-BlueFirstX)
				for(int x=0;x<=BlueFirstX;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,BlueFirstY);
				int BlueB=BlueFirstY-(BlueFirstX*(BlueSecondY-BlueFirstY)/(BlueSecondX-BlueFirstX));
				for(int x=BlueFirstX+1;x<BlueSecondX;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,x*(BlueSecondY-BlueFirstY)/(BlueSecondX-BlueFirstX)+BlueB);
				for(int x=BlueSecondX;x<CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,BlueSecondY);
			}
			//Hight Pass
			else if(gIndex==HightPass){
				for(int x=0;x<BlueFirstPoint;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,0);
				for(int x=BlueFirstPoint;x<CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,255);
			}
			//Low Pass
			else if(gIndex==LowPass){
				for(int x=0;x<BlueFirstPoint;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,255);
				for(int x=BlueFirstPoint;x<CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,0);
			}
			//UpDown Pass
			else if(gIndex==UpDownPass){
				for(int x=0;x<BlueFirstPoint;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,0);
				for(int x=BlueFirstPoint;x<BlueSecondPoint;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,255);
				for(int x=BlueSecondPoint;x<CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,0);
			}
			//DownUp Pass
			else if(gIndex==DownUpPass){
				for(int x=0;x<BlueFirstPoint;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,255);
				for(int x=BlueFirstPoint;x<BlueSecondPoint;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,0);
				for(int x=BlueSecondPoint;x<CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,255);
			}
			//Shigmoid Curve
			else if(gIndex==ShigmoidCurve){
				for(int x=0;x<CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x,256/(1+exp((double)(BlueFirstPoint-x))));
			}
			//Logarithm
			else if(gIndex==Logarithm){
				for(int x=1;x<CamDepth;x++)
					ui.bgBlueBrightnessGraph->SetYData(x-1,46*log((double)x));
				ui.bgBlueBrightnessGraph->SetYData(255,255);
			}
			break;
	}
	this->setCursor(QCursor(Qt::ArrowCursor));
}

void CameraSettingColor::on_pbRedApply_clicked()
{
	Cam->Setting.RedApply=true;
}

void CameraSettingColor::on_pbGreenApply_clicked()
{
	Cam->Setting.GreenApply=true;
}

void CameraSettingColor::on_pbBlueApply_clicked()
{
	Cam->Setting.BlueApply=true;
}

void CameraSettingColor::on_pbRedUpdate_clicked()
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

void CameraSettingColor::on_pbGreenUpdate_clicked()
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

void CameraSettingColor::on_pbBlueUpdate_clicked()
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

void CameraSettingColor::on_pbProof_clicked()
{
	wProofDataFile=QFileDialog::getOpenFileName(
							this
							,"Please choose a '.dat' file."
							,""
							,"ProofDataFile (*.dat)");
	if(wProofDataFile=="")
		return;
	ui.leProofFile->setText(wProofDataFile);
	Cam->pbProofFlag=true;
	Cam->pbProofCancelFlag=false;
}

void CameraSettingColor::on_pbProofCancel_clicked()
{
	wProofDataFile="";
	ui.leProofFile->setText(wProofDataFile);
	Cam->pbProofCancelFlag=true;
	Cam->pbProofFlag=false;
}

//When the kind of the graph changes(Red)
void CameraSettingColor::on_cbRedGraphType_currentIndexChanged(int cIndex)
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
void CameraSettingColor::on_cbGreenGraphType_currentIndexChanged(int cIndex)
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
void CameraSettingColor::on_cbBlueGraphType_currentIndexChanged(int cIndex)
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

void CameraSettingColor::moveData(void)
{
	Cam->Setting.RedBrightness		=ui.lnRedBrightness->value();
	Cam->Setting.RedContrast		=ui.lnRedContrast->value();
	Cam->Setting.RedGamma			=ui.lnRedGamma->value();
	Cam->Setting.RedFloor			=ui.sbRedFloor->value();
	Cam->Setting.RedCeiling			=ui.sbRedCeiling->value();

	RedFirstPoint	=ui.sbRedFirstPoint->value();
	RedSecondPoint	=ui.sbRedSecondPoint->value();


	Cam->Setting.GreenBrightness	=ui.lnGreenBrightness->value();
	Cam->Setting.GreenContrast		=ui.lnGreenContrast->value();
	Cam->Setting.GreenGamma			=ui.lnGreenGamma->value();
	Cam->Setting.GreenFloor			=ui.sbGreenFloor->value();
	Cam->Setting.GreenCeiling		=ui.sbGreenCeiling->value();
	GreenFirstPoint	=ui.sbGreenFirstPoint->value();
	GreenSecondPoint=ui.sbGreenSecondPoint->value();


	Cam->Setting.BlueBrightness		=ui.lnBlueBrightness->value();
	Cam->Setting.BlueContrast		=ui.lnBlueContrast->value();
	Cam->Setting.BlueGamma			=ui.lnBlueGamma->value();
	Cam->Setting.BlueFloor			=ui.sbBlueFloor->value();
	Cam->Setting.BlueCeiling		=ui.sbBlueCeiling->value();
	BlueFirstPoint	=ui.sbBlueFirstPoint->value();
	BlueSecondPoint	=ui.sbBlueSecondPoint->value();
}

void CameraSettingColor::setUiBuff(void)
{
	ui.hsRedBrightness			->setValue(Cam->Setting.RedBrightness);
	ui.hsRedContrast			->setValue(Cam->Setting.RedContrast);
	ui.hsRedGamma				->setValue(Cam->Setting.RedGamma);
	ui.sbRedFloor				->setValue(Cam->Setting.RedFloor);
	ui.sbRedCeiling				->setValue(Cam->Setting.RedCeiling);
	ui.sbRedFirstPoint			->setValue(RedFirstPoint);
	ui.sbRedSecondPoint			->setValue(RedSecondPoint);

	ui.hsGreenBrightness		->setValue(Cam->Setting.GreenBrightness);
	ui.hsGreenContrast			->setValue(Cam->Setting.GreenContrast);
	ui.hsGreenGamma				->setValue(Cam->Setting.GreenGamma);
	ui.sbGreenFloor				->setValue(Cam->Setting.GreenFloor);
	ui.sbGreenCeiling			->setValue(Cam->Setting.GreenCeiling);
	ui.sbGreenFirstPoint		->setValue(GreenFirstPoint);
	ui.sbGreenSecondPoint		->setValue(GreenSecondPoint);

	ui.hsBlueBrightness			->setValue(Cam->Setting.BlueBrightness);
	ui.hsBlueContrast			->setValue(Cam->Setting.BlueContrast);
	ui.hsBlueGamma				->setValue(Cam->Setting.BlueGamma);
	ui.sbBlueFloor				->setValue(Cam->Setting.BlueFloor);
	ui.sbBlueCeiling			->setValue(Cam->Setting.BlueCeiling);
	ui.sbBlueFirstPoint			->setValue(BlueFirstPoint);
	ui.sbBlueSecondPoint		->setValue(BlueSecondPoint);
}
bool	CameraSettingColor::SetQuickProperty(CameraQuickProperty Attr, double RelativeValue)
{
	return Cam->Setting.SetQuickProperty(Feature ,Attr, RelativeValue);
}
void CameraSettingColor::on_checkBoxCameraControl_clicked()
{
	ui.spinBoxLineRate				->setVisible(ui.checkBoxCameraControl->isChecked());
	//ui.doubleSpinBoxExposureTime	->setVisible(ui.checkBoxCameraControl->isChecked());
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
