/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Proofreader\WhiteBalanceForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include "WhiteBalanceForm.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include <omp.h>

WhiteBalanceForm::WhiteBalanceForm(QList<int> *RDataList,QList<int> *GDataList,QList<int> *BDataList,int Offset)
{
	ui.setupUi(this);

	//グラフの設定
	LineGraph=new mtLineGraph();
	LineGraph->SetBackgroundColor(QColor(Qt::lightGray));
	mtGLine	*RLine=new mtGLine();
	mtGLine	*GLine=new mtGLine();
	mtGLine	*BLine=new mtGLine();
	RLine->SetLineColor(QColor(Qt::red));
	GLine->SetLineColor(QColor(Qt::green));
	BLine->SetLineColor(QColor(Qt::blue));
//	GLine->SetLineWidth(4);
	LineGraph->AddGraph(RLine);
	LineGraph->AddGraph(GLine);
	LineGraph->AddGraph(BLine);

	int MinRedValue,MaxRedValue;
	MinRedValue=MaxRedValue		=RDataList->at(0);
	int MinGreenValue,MaxGreenValue;
	MinGreenValue=MaxGreenValue	=GDataList->at(0);
	int MinBlueValue,MaxBlueValue;
	MinBlueValue=MaxBlueValue	=BDataList->at(0);
	for(int Index=0,i=Offset;Index<RDataList->count();Index++,i++){
		LineGraph->GraphList[0]->AddXY(i,RDataList->at(Index));
		LineGraph->GraphList[1]->AddXY(i,GDataList->at(Index));
		LineGraph->GraphList[2]->AddXY(i,BDataList->at(Index));
	}
	ui.dwRGBGraph->setWidget(LineGraph);

	for(int i=0;i<3;i++){
		if(LineGraph->GraphList[i]->SortXY()==NULL)
			continue;
	}
	MinRedValue=LineGraph	->GraphList[0]->uMinY;
	MaxRedValue=LineGraph	->GraphList[0]->uMaxY;
	MinGreenValue=LineGraph	->GraphList[1]->uMinY;
	MaxGreenValue=LineGraph	->GraphList[1]->uMaxY;
	MinBlueValue=LineGraph	->GraphList[2]->uMinY;
	MaxBlueValue=LineGraph	->GraphList[2]->uMaxY;

	//スピンボックスの入力制限の設定
	ui.sbRedAdjustNumb	->setMinimum(-MinRedValue);
	ui.sbRedAdjustNumb	->setMaximum(255-MaxRedValue);
	ui.sbGreenAdjustNumb->setMinimum(-MinGreenValue);
	ui.sbGreenAdjustNumb->setMaximum(255-MaxGreenValue);
	ui.sbBlueAdjustNumb	->setMinimum(-MinBlueValue);
	ui.sbBlueAdjustNumb	->setMaximum(255-MaxBlueValue);
	QString strRedRange		="( " + QString::number(-MinRedValue) + " ～ " + QString::number(255-MaxRedValue) + " )";
	ui.lbRedRange		->setText(strRedRange);
	QString strGreenRange	="( " + QString::number(-MinGreenValue) + " ～ " + QString::number(255-MaxGreenValue) + " )";
	ui.lbGreenRange		->setText(strGreenRange);
	QString strBlueRange	="( " + QString::number(-MinBlueValue) + " ～ " + QString::number(255-MaxBlueValue) + " )";
	ui.lbBlueRange		->setText(strBlueRange);

	RGBDataList[0]	=RDataList;
	RGBDataList[1]	=GDataList;
	RGBDataList[2]	=BDataList;
	OffsetNumb=Offset;

	//connect
	connect(ui.sbRedAdjustNumb,		SIGNAL(valueChanged(int)),	this,SLOT(sbRedAdjustNumb_valueChanged(int)));
	connect(ui.sbGreenAdjustNumb,	SIGNAL(valueChanged(int)),	this,SLOT(sbGreenAdjustNumb_valueChanged(int)));
	connect(ui.sbBlueAdjustNumb,	SIGNAL(valueChanged(int)),	this,SLOT(sbBlueAdjustNumb_valueChanged(int)));
	connect(ui.pbShading,			SIGNAL(clicked()),			this,SLOT(pbShading_clicked()));
	connect(ui.pbSave,				SIGNAL(clicked()),			this,SLOT(pbSave_clicked()));
	connect(ui.pbClose,				SIGNAL(clicked()),			this,SLOT(pbClose_clicked()));
}

WhiteBalanceForm::~WhiteBalanceForm()
{
}

void WhiteBalanceForm::sbRedAdjustNumb_valueChanged(int value)
{
	//グラフの移動
	int DataListCount=RGBDataList[0]->count();
	for(int Index=0,i=OffsetNumb;Index<DataListCount;Index++,i++){
		LineGraph->GraphList[0]->ReplaceXY(i,RGBDataList[0]->at(Index)+value);
	}
	double MinY,MaxY;
	if((MinY=LineGraph->GraphList[0]->uMinY+value)<LineGraph->GetMinY())
		LineGraph->SetMinY(MinY);
	if((MaxY=LineGraph->GraphList[0]->uMaxY+value)>LineGraph->GetMaxY())
		LineGraph->SetMaxY(MaxY);
	LineGraph->repaint();
}

void WhiteBalanceForm::sbGreenAdjustNumb_valueChanged(int value)
{
	//グラフの移動
	int DataListCount=RGBDataList[1]->count();
	for(int Index=0,i=OffsetNumb;Index<DataListCount;Index++,i++){
		LineGraph->GraphList[1]->ReplaceXY(i,RGBDataList[1]->at(Index)+value);
	}
	double MinY,MaxY;
	if((MinY=LineGraph->GraphList[1]->uMinY+value)<LineGraph->GetMinY())
		LineGraph->SetMinY(MinY);
	if((MaxY=LineGraph->GraphList[1]->uMaxY+value)>LineGraph->GetMaxY())
		LineGraph->SetMaxY(MaxY);
	LineGraph->repaint();
}

void WhiteBalanceForm::sbBlueAdjustNumb_valueChanged(int value)
{
	//グラフの移動
	int DataListCount=RGBDataList[2]->count();
	for(int Index=0,i=OffsetNumb;Index<DataListCount;Index++,i++){
		LineGraph->GraphList[2]->ReplaceXY(i,RGBDataList[2]->at(Index)+value);
	}
	double MinY,MaxY;
	if((MinY=LineGraph->GraphList[2]->uMinY+value)<LineGraph->GetMinY())
		LineGraph->SetMinY(MinY);
	if((MaxY=LineGraph->GraphList[2]->uMaxY+value)>LineGraph->GetMaxY())
		LineGraph->SetMaxY(MaxY);
	LineGraph->repaint();
}

void WhiteBalanceForm::pbShading_clicked()
{
	//シェーディング補正
	int DataListCount=RGBDataList[0]->count();
	if(ui.pbShading->isChecked()){
		//グラフの移動
		int ShadingBrightness=ui.sbShading->value();
		#pragma omp parallel
		{
			#pragma omp for
			for(int RGB=0;RGB<3;RGB++){
				for(int Index=0,i=OffsetNumb;Index<DataListCount;Index++,i++){
					LineGraph->GraphList[RGB]->ReplaceXY(i,ShadingBrightness);
				}
			}
		}
	}
	else{
		double WhiteBlance[3];
		WhiteBlance[0]	=ui.sbRedAdjustNumb		->value();
		WhiteBlance[1]	=ui.sbGreenAdjustNumb	->value();
		WhiteBlance[2]	=ui.sbBlueAdjustNumb	->value();
		#pragma omp parallel
		{
			#pragma omp for
			for(int RGB=0;RGB<3;RGB++){
				for(int Index=0,i=OffsetNumb;Index<DataListCount;Index++,i++){
					LineGraph->GraphList[RGB]->ReplaceXY(i,RGBDataList[RGB]->at(Index)+WhiteBlance[RGB]);
				}
			}
		}
	}
	LineGraph->repaint();
}

void WhiteBalanceForm::pbSave_clicked()
{
	//ホワイトバランス調整ファイルの出力
	//画像校正データをファイルに保存
	QString WhiteBlanceData=QFileDialog::getSaveFileName(
							this,tr("Save File"),"","Data (*.dat)");
	if(WhiteBlanceData=="")
		return;

	double WhiteBlance[3];
	WhiteBlance[0]	=ui.sbRedAdjustNumb		->value();
	WhiteBlance[1]	=ui.sbGreenAdjustNumb	->value();
	WhiteBlance[2]	=ui.sbBlueAdjustNumb	->value();

	QFile file(WhiteBlanceData);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
		QMessageBox::warning(this,tr("Message"),tr("This file not open!\n") + WhiteBlanceData);
		return;
	}

	QTextStream out(&file);
	int DataListCount=RGBDataList[0]->count();
	for(int RGB=0;RGB<3;RGB++){
		for(int Index=0,i=-1;Index<DotPerLine;Index++){
			if(Index<OffsetNumb){
				out << QString::number(LineGraph->GraphList[RGB]->GetPointY(0)/RGBDataList[RGB]->at(0)) << "\n";
			}
			else{
				if(i<(DataListCount-1))
					i++;
				out << QString::number(LineGraph->GraphList[RGB]->GetPointY(i)/RGBDataList[RGB]->at(i)) << "\n";
			}
		}
	}

	file.close();
	QMessageBox::information(this,tr("Message"),tr("Save Complete."));
}

void WhiteBalanceForm::pbClose_clicked()
{
	close();
}
