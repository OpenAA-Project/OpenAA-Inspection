/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Proofreader\ProofGraph.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "ProofGraph.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "math.h"

ProofGraph::ProofGraph(QList<double> XYDataList,int Line)
{
	ui.setupUi(this);

	LineGraph=new mtLineGraph();
	LineGraph->SetBackgroundColor(QColor(Qt::lightGray));
	mtGLine	*GLine=new mtGLine();
//	mtGStick	*GLine=new mtGStick();
//	GLine->SetLineWidth(4);
//	GLine->SetLineColor(QColor(Qt::yellow));
//	GLine->SetOffsetX(1);
	LineGraph->AddGraph(GLine);
//	LineGraph->GraphList[0]->SetLineColor(QColor((Qt::cyan)));
//	LineGraph->GraphList[0]->SetLineWidth(5);

//	for(int i=1;i<XYDataList.count();i++)
	for(int i=2;i<XYDataList.count()-1;i++)
		LineGraph->GraphList[0]->AddXY(i-2,XYDataList.at(i));

	ui.dwShowGraph->setWidget(LineGraph);
	ui.dsbAverageY->setValue(LineGraph->GraphList[0]->GetAverageY());

	wXYDataList=XYDataList;
	DotPerLine=Line;
	connect(ui.pbSave,	SIGNAL(clicked()),this,SLOT(pbSave_clicked()));
	connect(ui.pbClose,	SIGNAL(clicked()),this,SLOT(pbClose_clicked()));
}

ProofGraph::~ProofGraph()
{
	delete LineGraph;
}

void ProofGraph::pbSave_clicked()
{
	//画像校正データをファイルに保存
	QString ProofData=QFileDialog::getSaveFileName(
							this,tr("Save File"),"","Data (*.dat)");
	if(ProofData=="")
		return;

	double Calibration=ui.dsbCalibration->value();
	QFile file(ProofData);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
		QMessageBox::warning(this,tr("Message"),tr("This file not open!\n") + ProofData);
		return;
	}
	QTextStream out(&file);
	double SumXYDataList=0;
	double dkx=0;
	int wdkx=0;
	double end,differ;
//	for(int i=0,j=1,k=1,kk=1,index=2;i<DotPerLine;i++)
	for(int i=0,j=2,k=1,kk=1,index=2;i<DotPerLine;i++){
//		if(i<=wXYDataList.at(0) || dkx==-1)
//		if(i<=wXYDataList.at(0))
//		if(i<=wXYDataList.at(0) || i<=wXYDataList.at(1))
		if(i<(wXYDataList.at(0)+wXYDataList.at(1)))
			out << 0 << "," << 0 << "\n";
		else if(wdkx==1){
//			out << end+(differ*index++) << "\n";
//			out << (SumXYDataList+wXYDataList.at(j)*(dkx+kk/wXYDataList.at(j)))-Calibration*(j-1+dkx+kk/wXYDataList.at(j)) << "\n";
			out << OutputString((SumXYDataList+wXYDataList.at(j)*(dkx+kk/wXYDataList.at(j)))-Calibration*(j-2+dkx+kk/wXYDataList.at(j))) << "\n";
			kk++;
		}
		else{
			double dk;
			if((dk=k-(SumXYDataList+wXYDataList.at(j)))>0){
				if(j+2==wXYDataList.count()){
//					end=(SumXYDataList+wXYDataList.at(j)*(dkx+kk/wXYDataList.at(j)))-Calibration*(j-1+dkx+kk/wXYDataList.at(j));
//					differ=(SumXYDataList+wXYDataList.at(j)*(dkx+kk/wXYDataList.at(j)))-Calibration*(j-1+dkx+kk/wXYDataList.at(j))-(SumXYDataList+wXYDataList.at(j)*(dkx+(kk-1)/wXYDataList.at(j)))-Calibration*(j-1+dkx+(kk-1)/wXYDataList.at(j));
//					out << end+differ << "\n";
//					out << (SumXYDataList+wXYDataList.at(j)*(dkx+kk/wXYDataList.at(j)))-Calibration*(j-1+dkx+kk/wXYDataList.at(j)) << "\n";
					out << OutputString((SumXYDataList+wXYDataList.at(j)*(dkx+kk/wXYDataList.at(j)))-Calibration*(j-2+dkx+kk/wXYDataList.at(j))) << "\n";
					kk++;
					wdkx=1;
					continue;
				}
				SumXYDataList+=wXYDataList.at(j);
				dkx=dk/wXYDataList.at(++j);
				kk=0;
			}
//			out << LineGraph->GetYValue(0,j-1+dkx+(kk++)/wXYDataList.at(j)) << "\n";
//			out << Calibration*(j-1+dkx+kk/wXYDataList.at(j)) << "\n";
///			double AXX=j-1+dkx+kk/wXYDataList.at(j);
///			double AAA=Calibration*(j-1+dkx+kk/wXYDataList.at(j));
///			double BXX=dkx+kk/wXYDataList.at(j);
///			double BBB=SumXYDataList+wXYDataList.at(j)*(dkx+kk/wXYDataList.at(j));
//			out << Calibration*(j-1+dkx+kk/wXYDataList.at(j))-(SumXYDataList+wXYDataList.at(j)*(dkx+kk/wXYDataList.at(j))) << "\n";
//			out << (SumXYDataList+wXYDataList.at(j)*(dkx+kk/wXYDataList.at(j)))-Calibration*(j-1+dkx+kk/wXYDataList.at(j)) << "\n";
			out << OutputString((SumXYDataList+wXYDataList.at(j)*(dkx+kk/wXYDataList.at(j)))-Calibration*(j-2+dkx+kk/wXYDataList.at(j))) << "\n";
			k++;
			kk++;
		}
/*
		if(i<=(SumXYDataList+wXYDataList.at(j)))
			out << 0 << "\n";
		else if(i>(SumXYDataList+wXYDataList.at(j))){
			SumCalibration+=wXYDataList.at(++j)-Calibration;
			SumXYDataList+=wXYDataList.at(j);
			if(SumCalibration>1){
				out << 1 << "\n";
				SumCalibration-=1;
			}
			else if(SumCalibration<-1){
				out << -1 << "\n";
				SumCalibration+=1;
			}
			else
				out << 0 << "\n";
		}
*/
	}
	file.close();
}

void ProofGraph::pbClose_clicked()
{
	accept();
}

QString ProofGraph::OutputString(double output)
{
	double woutput=fabs(output);
	int intNum=(int)floor(woutput);
	int intDecim=(int)floor((woutput-intNum)*1024.0);

	if(output<0){
		intDecim=-intDecim;
		if(intDecim==0)
			intNum=-intNum;
	}
	return QString().setNum(intNum) + "," + QString().setNum(intDecim);
}
