#include "clsplot3d.h"
#include "XImageBufferFunctions.h"
#include "XPointer.h"
#include "XImageProcess.h"

#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <stdio.h>

extern	LayersBase	*Layers;

double clsCalc::operator ()(double x, double y) {
	double ret = 0;

	DataInPage *dp = Layers->GetPageData(nPageIdx);
	int nXPnt = x;
	int nYPnt = y;

	BYTE *s = dp->GetLayerData(0)->GetMasterBuff().GetY(nYPnt);
	s += nXPnt;
	int nVal = (int)*s;
	ret = nVal;
	return ret;
}

clsPlot3D::clsPlot3D(CImgCtrl *_obj, QWidget *parent)
	: SurfacePlot(parent)
{
	objCtrl = _obj;
	nPageIdx = 0;
	data = NULL;
	xmesh = 0;
	ymesh = 0;

	nZScale_Brightness = 50;
	nZScale_Resolution = 10;
	nZScale_Angle      = 50;
	nZScale_Focus      = 10;

	nRoteX = 30;
	nRoteY = 0;
	nRoteZ = 15;

	chartType = false;

	nAvgX = 0;
	nAvgY = 0;

	bBrightMode = false;
}

clsPlot3D::~clsPlot3D()
{

}

void clsPlot3D::drawTest(int nPage,int x1, int y1, int x2, int y2) {
	calc = clsCalc(objCtrl,this);
	calc.setPageIdx(nPage);
	
	if ( x2 >= objCtrl->nWid ) x2 = objCtrl->nWid-1;
	if ( y2 >= objCtrl->nHei ) y2 = objCtrl->nHei-1;
	int xwid = x2-x1;
	int yhei = y2-y1;
	calc.setMesh(xwid,yhei);
	calc.setDomain(x1,x2,y1,y2);
	calc.setMinZ(0.0);
	calc.setMaxZ(255.0);
	calc.create();

	setRotation(30,0,15);
	setScale(1,1,10);
	setShift(0.15,0,0);
	setZoom(0.9);

	for( int i=0; i!=coordinates()->axes.size(); i++ ) {
		coordinates()->axes[i].setMajors(7);
		coordinates()->axes[i].setMinors(4);
	}

	coordinates()->axes[X1].setLabelString("x-axis");
	coordinates()->axes[Y1].setLabelString("y-axis");
	coordinates()->axes[Z1].setLabelString("z-axis");

	setCoordinateStyle(FRAME);
	drawGrp();
}

void clsPlot3D::InitGrp() {
	calc.setMesh(objCtrl->nWid/10,objCtrl->nHei/10);
	calc.setDomain(0,objCtrl->nWid-1,0,objCtrl->nHei-1);
	calc.setMinZ(0.0);
	calc.setMaxZ(255.0);
	calc.create();

	setRotation(30,0,15);
	setScale(1,1,10);
	setShift(0.15,0,0);
	setZoom(0.9);

	for( int i=0; i!=coordinates()->axes.size(); i++ ) {
		coordinates()->axes[i].setMajors(7);
		coordinates()->axes[i].setMinors(4);
	}

	coordinates()->axes[X1].setLabelString("x-axis");
	coordinates()->axes[Y1].setLabelString("y-axis");
	coordinates()->axes[Z1].setLabelString("z-axis");

	setCoordinateStyle(FRAME);
}

void clsPlot3D::drawGrp() {
	updateData();
	updateGL();
}

void clsPlot3D::getAxisCnt(int &x, int &y) {
	x = xmesh;
	y = ymesh;
}

bool clsPlot3D::outCsvX(int nPnt, QString fnam) {
	if ( nPnt >= xmesh || nPnt < 0 ) return false;
	
	QFile file(fnam);
	if ( !file.open(QIODevice::WriteOnly|QIODevice::Text) ) return false;
	QTextStream out(&file);
	for( int i=0; i<ymesh; i++ ) {
		QString tmp;
		QString buf = tmp.sprintf("%f,%f\n",-data[nPnt][i].y,data[nPnt][i].z);
		out << buf;
	}
	file.close();
	return true;
}

bool clsPlot3D::outAxisValueX(int nPnt, int idx, double &x, double &y) {
	if ( nPnt >= xmesh || nPnt < 0 ) return false;
	if ( idx >= ymesh ) return false;
	x = (-1)*data[nPnt][idx].y;
	y = data[nPnt][idx].z;
	return true;
}

bool clsPlot3D::outCsvY(int nPnt, QString fnam) {
	if ( nPnt >= ymesh || nPnt < 0 ) return false;
	
	QFile file(fnam);
	if ( !file.open(QIODevice::WriteOnly|QIODevice::Text) ) return false;
	QTextStream out(&file);
	for( int i=0; i<xmesh; i++ ) {
		QString tmp;
		QString buf = tmp.sprintf("%f,%f\n",data[i][nPnt].x,data[i][nPnt].z);
		out << buf;
	}
	file.close();
	return true;
}

bool clsPlot3D::outAxisValueY(int nPnt, int idx, double &x, double &y) {
	if ( nPnt >= ymesh || nPnt < 0 ) return false;
	if ( idx >= xmesh ) return false;
	x = data[idx][nPnt].x;
	y = data[idx][nPnt].z;
	return true;
}

void clsPlot3D::setGraphEnv(double dZMin, double dZMax, char *sZLabel) {
	createCoordinateSystem(Triple(0,0,dZMin),Triple(objCtrl->nWid,-objCtrl->nHei,dZMax));
	setCoordinateStyle(FRAME);
	if ( chartType == true ) {
		bar = (Bar *)setPlotStyle(Bar(0.001,0.001));
	} else {
		setPlotStyle(FILLEDMESH);
	}

	for( int i=0; i!=coordinates()->axes.size(); i++ ) {
		coordinates()->axes[i].setMajors(10);
		coordinates()->axes[i].setMinors(5);
	}

	coordinates()->axes[Y1].setScale(new clsYAxisScale);
	coordinates()->axes[Y2].setScale(new clsYAxisScale);
	coordinates()->axes[Y3].setScale(new clsYAxisScale);
	coordinates()->axes[Y4].setScale(new clsYAxisScale);

	coordinates()->axes[X1].setLabelString("X");
	coordinates()->axes[X4].setLabelString("X");
	coordinates()->axes[Y1].setLabelString("Y");
	coordinates()->axes[Y2].setLabelString("Y");
	coordinates()->axes[Z1].setLabelString(sZLabel);
	coordinates()->axes[Z2].setLabelString(sZLabel);
	coordinates()->axes[Z3].setLabelString(sZLabel);
	coordinates()->axes[Z4].setLabelString(sZLabel);

	coordinates()->adjustNumbers(10);
	coordinates()->adjustLabels(15);
}

void clsPlot3D::bndPlotData(int xmesh, int ymesh, double dZMin) {
	clsPadCnt *c = objCtrl->tblPadCnt[nPageIdx].GetFirst();
	for( int i=0; i<ymesh; i++ ) {
		if ( xmesh > c->cnt ) {
			for( int j=c->cnt; j<xmesh; j++ ) {
				data[j][i].y = data[j-1][i].y;
				for( int k=0; k<ymesh; k++ ) {
					if ( data[j][k].x != 0 ) {
						data[j][i].x = data[j][k].x;
						data[j][i].z = dZMin;
					}
				}
			}
		}
		c = c->GetNext();
	}
}

double **clsPlot3D::getAverageValue(int x, int y) {
	MakeAvgVal(x,y);

	int xdiv = (int)(xmesh/x);
	int ydiv = (int)(ymesh/y);

	int startX = 0;
	int startY = 0;
	int endX = xdiv;
	int endY = ydiv;
	for( int i=0; i<x; i++ ) {
		startY = 0;
		endY = ydiv;
		for( int j=0; j<y; j++ ) {
			dAvgVal[i][j] = calcAverage(startX,startY,endX,endY);
			startY += ydiv;
			endY += ydiv;
		}
		startX += xdiv;
		endX += xdiv;
	}

	return dAvgVal;
}

double clsPlot3D::calcAverage(int startX, int startY, int endX, int endY) {
	double dAvg = 0;
	double dSum = 0;
	int    nCnt = 0;

	for( int i=startX; i<endX; i++ ) {
		for( int j=startY; j<endY; j++ ) {
			dSum += data[i][j].z;
			nCnt ++;
		}
	}
	dAvg = dSum/nCnt;
	return dAvg;
}

void clsPlot3D::MakeAvgVal(int x, int y) {
	if ( nAvgX > 0 && nAvgY > 0 ) {
		for( int i=0; i<nAvgX; i++ ) {
			delete dAvgVal[i];
		}
		delete dAvgVal;
	}

	nAvgX = x;
	nAvgY = y;
	dAvgVal = new double *[nAvgX];
	for( int i=0; i<nAvgX; i++ ) {
		dAvgVal[i] = new double[nAvgY];
	}
}

void clsPlot3D::setBrightMode(bool mode) {
	bBrightMode = mode;
}