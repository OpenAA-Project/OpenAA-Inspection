//#include "CameraXtiumPx8MonoLineTriggerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraGraphinXCM8040\CameraGraphin\camerasettingmono.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "math.h"
#include "CameraSettingMono.h"
#include "CLHS_PX8CommandCreater.h"
#include "sapClassBasic.h"
#include "featureCtrl.h"
#include "CameraXtiumLinearHSColorMonoLineTrigger.h"

CameraSettingMono::CameraSettingMono(CameraXtiumLinearHSMono *s ,featureCtrl *f ,QWidget *parent)
    : QDialog(parent)
{
	Cam		=s;
	Feature		=f;

	ui.setupUi(this);
	//LangSolver.SetUI(this);
	Cam->Setting.LoadFromCam(Feature);

	ui.spinBoxLineRate			->setValue(Cam->Setting.LineRate);
	//ui.doubleSpinBoxExposureTime->setValue(Cam->Setting.ExposureTime);
	ui.checkBoxDirection		->setChecked(Cam->Setting.TDIDirection);
	ui.doubleSpinBoxGainRed		->setValue(Cam->Setting.GainRed);
	ui.spinBoxOffsetRed			->setValue(Cam->Setting.OffsetRed);
	ui.doubleSpinBoxGainRedL	->setValue(Cam->Setting.GainRedL);
	ui.spinBoxOffsetRedL		->setValue(Cam->Setting.OffsetRedL);
	ui.doubleSpinBoxGainRedR	->setValue(Cam->Setting.GainRedR);
	ui.spinBoxOffsetRedR		->setValue(Cam->Setting.OffsetRedR);
	ui.doubleSpinBoxRedMultipleX	->setValue(Cam->Setting.MultipleRed);
	ui.spinBoxRedOffsetX			->setValue(Cam->Setting.OffsetXRed);
	ui.spinBoxRedOffsetY			->setValue(Cam->Setting.OffsetYRed);
	ui.spinBoxHorizontalBinning		->setValue(Cam->Setting.HorizontalBinning);
	ui.spinBoxVerticalBinning		->setValue(Cam->Setting.VerticalBinning);
	ui.checkBoxLeftRight			->setChecked(Cam->Setting.LeftRight);
	ui.checkBoxExternalTrigger		->setChecked(Cam->Setting.ExternalTrigger);
	ui.checkBoxAutoBlackLevel		->setChecked(Cam->Setting.AutoBlackLevel);
	ui.checkBoxCalibrateFPN			->setChecked(Cam->Setting.CalibrateFPN);

	ui.comboBoxAnalogGain			->setCurrentIndex  (Cam->Setting.AnalogGain);

	for(int x=0;x<CamDepth;x++){
		ui.bgRedBrightnessGraph->SetYData	(x,Cam->Setting.RedCustomLut[x]);		//RedGraph
	}

	RedFirstPoint	=0;
	RedSecondPoint	=0;
	RedFirstX		=0;
	RedFirstY		=0;
	RedSecondX		=0;
	RedSecondY		=0;

	//Red
	Cam->Setting.RedApply=false;
	ui.sbRedFirstPoint->setEnabled(false);
	ui.sbRedSecondPoint->setEnabled(false);
	ui.sbRedFirstXCoordinates->setEnabled(false);
	ui.sbRedFirstYCoordinates->setEnabled(false);
	ui.sbRedSecondXCoordinates->setEnabled(false);
	ui.sbRedSecondYCoordinates->setEnabled(false);
	ui.bgRedBrightnessGraph->SetBarColor(QColor(Qt::red));

	//Proof
	ui.leProofFile->setText(Cam->ProofDataFile);


	setUiBuff();

	
	Cam->pbProofFlag=false;
	Cam->pbProofCancelFlag=false;
	connect(ui.pbProofCancel,SIGNAL(clicked()),this,SLOT(pbProofCancel_clicked()));

	ui.checkBoxCameraControl->setChecked(Cam->Setting.CameraControl);
	on_checkBoxCameraControl_clicked();}

CameraSettingMono::~CameraSettingMono()
{

}

void CameraSettingMono::on_pbCancel_clicked()
{
	done(false);
}

void CameraSettingMono::on_pbOK_clicked()
{
	Cam->Setting.CameraControl	=ui.checkBoxCameraControl->isChecked();

	if(Cam->Setting.RedApply==true){
		for(int i=0; i<CamDepth; i++)
			Cam->Setting.RedCustomLut[i]=ui.bgRedBrightnessGraph->GetYData(i);
	}

	if(Cam->pbProofFlag==true || Cam->pbProofCancelFlag==true)
		Cam->ProofDataFile=wProofDataFile;

	Cam->Setting.LineRate		=ui.spinBoxLineRate				->value();
	//Cam->Setting.ExposureTime	=ui.doubleSpinBoxExposureTime	->value();
	Cam->Setting.TDIDirection	=ui.checkBoxDirection			->isChecked();

	Cam->Setting.GainRed		=ui.doubleSpinBoxGainRed		->value();
	Cam->Setting.OffsetRed		=ui.spinBoxOffsetRed			->value();

	Cam->Setting.GainRedL		=ui.doubleSpinBoxGainRedL		->value();
	Cam->Setting.OffsetRedL		=ui.spinBoxOffsetRedL			->value();

	Cam->Setting.GainRedR		=ui.doubleSpinBoxGainRedR		->value();
	Cam->Setting.OffsetRedR		=ui.spinBoxOffsetRedR			->value();

	Cam->Setting.MultipleRed	=ui.doubleSpinBoxRedMultipleX	->value();
	Cam->Setting.OffsetXRed		=ui.spinBoxRedOffsetX			->value();
	Cam->Setting.OffsetYRed		=ui.spinBoxRedOffsetY			->value();

	Cam->Setting.HorizontalBinning	=ui.spinBoxHorizontalBinning->value();
	Cam->Setting.VerticalBinning	=ui.spinBoxVerticalBinning	->value();
	Cam->Setting.LeftRight			=ui.checkBoxLeftRight		->isChecked();
	Cam->Setting.ExternalTrigger	=ui.checkBoxExternalTrigger	->isChecked();
	Cam->Setting.AutoBlackLevel		=ui.checkBoxAutoBlackLevel	->isChecked();
	Cam->Setting.CalibrateFPN		=ui.checkBoxCalibrateFPN	->isChecked();
	Cam->Setting.AnalogGain			=ui.comboBoxAnalogGain		->currentIndex ();

	Cam->Setting.StoreToCam(Feature);
	moveData();

	done(true);
}

//Drawing graph
void CameraSettingMono::GraphDraw(ColorType Color,int gIndex)
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
	}
	this->setCursor(QCursor(Qt::ArrowCursor));
}

void CameraSettingMono::on_pbRedApply_clicked()
{
	Cam->Setting.RedApply=true;
}

void CameraSettingMono::on_pbRedUpdate_clicked()
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

void CameraSettingMono::on_pbProof_clicked()
{
	wProofDataFile=QFileDialog::getOpenFileName(
							this,"Please choose a '.dat' file."
								,""
								,"ProofDataFile (*.dat)");
	if(wProofDataFile=="")
		return;
	ui.leProofFile->setText(wProofDataFile);
	Cam->pbProofFlag=true;
	Cam->pbProofCancelFlag=false;
}

void CameraSettingMono::on_pbProofCancel_clicked()
{
	wProofDataFile="";
	ui.leProofFile->setText(wProofDataFile);
	Cam->pbProofCancelFlag=true;
	Cam->pbProofFlag=false;
}

//When the kind of the graph changes(Red)
void CameraSettingMono::on_cbRedGraphType_currentIndexChanged(int cIndex)
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

void CameraSettingMono::moveData(void)
{
	Cam->Setting.RedBrightness		=ui.lnRedBrightness->value();
	Cam->Setting.RedContrast		=ui.lnRedContrast->value();
	Cam->Setting.RedGamma			=ui.lnRedGamma->value();
	Cam->Setting.RedFloor			=ui.sbRedFloor->value();
	Cam->Setting.RedCeiling			=ui.sbRedCeiling->value();

	RedFirstPoint	=ui.sbRedFirstPoint->value();
	RedSecondPoint	=ui.sbRedSecondPoint->value();
}

void CameraSettingMono::setUiBuff(void)
{
	ui.hsRedBrightness			->setValue(Cam->Setting.RedBrightness);
	ui.hsRedContrast			->setValue(Cam->Setting.RedContrast);
	ui.hsRedGamma				->setValue(Cam->Setting.RedGamma);
	ui.sbRedFloor				->setValue(Cam->Setting.RedFloor);
	ui.sbRedCeiling				->setValue(Cam->Setting.RedCeiling);
	ui.sbRedFirstPoint			->setValue(RedFirstPoint);
	ui.sbRedSecondPoint			->setValue(RedSecondPoint);
}

void CameraSettingMono::on_checkBoxCameraControl_clicked()
{
    ui.spinBoxLineRate				->setVisible(ui.checkBoxCameraControl->isChecked());
    //ui.doubleSpinBoxExposureTime	->setVisible(ui.checkBoxCameraControl->isChecked());
    ui.checkBoxDirection			->setVisible(ui.checkBoxCameraControl->isChecked());
    ui.doubleSpinBoxGainRed			->setVisible(ui.checkBoxCameraControl->isChecked());
    ui.spinBoxOffsetRed				->setVisible(ui.checkBoxCameraControl->isChecked());
    ui.spinBoxHorizontalBinning		->setVisible(ui.checkBoxCameraControl->isChecked());
    ui.spinBoxVerticalBinning		->setVisible(ui.checkBoxCameraControl->isChecked());
    ui.checkBoxExternalTrigger		->setVisible(ui.checkBoxCameraControl->isChecked());
    ui.checkBoxAutoBlackLevel		->setVisible(ui.checkBoxCameraControl->isChecked());
    ui.checkBoxCalibrateFPN			->setVisible(ui.checkBoxCameraControl->isChecked());
}

