#include "frm3d.h"
#include "XImageBufferFunctions.h"
#include "XPointer.h"
#include "XImageProcess.h"

#include <QScrollArea>
#include <QMessageBox>

extern	LayersBase	*Layers;

frm3d::frm3d(CImgCtrl *_obj, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QGridLayout *grid = new QGridLayout(ui.frame);
	objPlt  = new clsPlot3D(_obj,ui.frame);
	grid->addWidget(objPlt,0,0);

	nDrawMode = 0;
	nMaxPage  = 0;
	nPageIdx  = 0;
}

frm3d::~frm3d()
{

}

void frm3d::setPageCnt(int _page) {
	nMaxPage = _page;
}

void frm3d::keyPressEvent(QKeyEvent *evt) {
	//if ( evt->key() == Qt::Key_Tab ) {
	if ( evt->key() == Qt::Key_F1 ) {
		nPageIdx ++;
		if ( nPageIdx >= nMaxPage ) nPageIdx = 0;
		ui.txtPageIdx->setText(QString::number(nPageIdx));

		switch( nDrawMode ) {
		case 1 : // ピント解析
			objPlt->plotFocus(nPageIdx);
			break;

		case 2 : // 輝度確認
			objPlt->plotBrightness(nPageIdx);
			break;

		case 3 : // 分解能
			objPlt->plotResolution(nPageIdx,dPadVal,bFlg);
			break;

		case 4 : // 直行確認
			objPlt->plotAngle(nPageIdx);
			break;

		case 0 :
			//objPlt->drawTest(nPageIdx);
			break;
		}
	}
}

void frm3d::drawTestPlot(int nPageIdx,int x1, int y1, int x2, int y2) {
	objPlt->drawTest(nPageIdx,x1,y1,x2,y2);
	nDrawMode = 0;
}

void frm3d::plotFocus(int _nPageIdx) {
	nDrawMode = 1;
	this->setWindowTitle(make2DGraphTitle());
	nPageIdx  = _nPageIdx;
	ui.txtPageIdx->setText(QString::number(nPageIdx));
	objPlt->plotFocus(nPageIdx);
	setCmbAxis();
}

void frm3d::plotBrightness(int _nPageIdx) {
	nDrawMode = 2;
	this->setWindowTitle(make2DGraphTitle());
	nPageIdx = _nPageIdx;
	ui.txtPageIdx->setText(QString::number(nPageIdx));
	objPlt->plotBrightness(nPageIdx);
	setCmbAxis();
}

void frm3d::plotResolution(int _nPageIdx,double _dPadVal, bool _flg) {
	nDrawMode = 3;
	this->setWindowTitle(make2DGraphTitle());
	dPadVal   = _dPadVal;
	bFlg      = _flg;
	nPageIdx  = _nPageIdx;
	ui.txtPageIdx->setText(QString::number(nPageIdx));
	objPlt->plotResolution(nPageIdx,dPadVal,bFlg);
	setCmbAxis();
}

void frm3d::plotAngle(int _nPageIdx) {
	nDrawMode = 4;
	this->setWindowTitle(make2DGraphTitle());
	nPageIdx = _nPageIdx;
	ui.txtPageIdx->setText(QString::number(nPageIdx));
	objPlt->plotAngle(nPageIdx);
	setCmbAxis();
}

void frm3d::setInitRotation(int x, int y, int z) {
	objPlt->nRoteX = x;
	objPlt->nRoteY = y;
	objPlt->nRoteZ = z;
}

void frm3d::setZScale(int idx, int scale, bool type) {
	switch( idx ) {
	case 1 :
		objPlt->nZScale_Focus = scale;
		break;
	case 2 :
		objPlt->nZScale_Brightness = scale;
		break;
	case 3 :
		objPlt->nZScale_Resolution = scale;
		break;
	case 4 :
		objPlt->nZScale_Angle = scale;
		break;
	}
	objPlt->chartType = type;
}

QString frm3d::make2DGraphTitle() {
	QString title = "";
	switch(nDrawMode) {
	case 1 :
		title = tr("Focus");
		break;
	case 2 :
		title = tr("Brightness");
		break;
	case 3 :
		title = tr("Resolution");
		break;
	case 4 :
		title = tr("Angle");
		break;
	}
	return title;
}

void frm3d::setOutDir(QString dir) {
	sOutDir = dir;
	objPlt->sOutDir = dir;
}

void frm3d::on_pushButton_clicked()
{
	close();
}

void frm3d::setCmbAxis() {
	int x, y;
	objPlt->getAxisCnt(x,y);

	ui.cmbLine_1->clear();
	ui.cmbLine_2->clear();

	for( int i=1; i<=x; i++ ) {
		ui.cmbLine_1->addItem(QString::number(i),i);
	}
	for( int i=1; i<=y; i++ ) {
		ui.cmbLine_2->addItem(QString::number(i),i);
	}
	ui.avgx->setMaximum(x);
	ui.avgy->setMaximum(y);
}

void frm3d::setAvgXY(int x, int y) {
	ui.avgx->setValue(x);
	ui.avgy->setValue(y);
}

void frm3d::setBrightMode(bool mode) {
	objPlt->setBrightMode(mode);
}

void frm3d::on_btnLine_1_clicked()
{
	QString fnm = sOutDir+"/ydata.csv";
	QString tmp = ui.cmbLine_1->currentText();
	int cnt = tmp.toInt()-1;
	if ( objPlt->outCsvX(cnt,fnm) == false ) {
		QMessageBox::critical(this,"outcsv","output csv Error");
		return;
	}
	double x,y;
	int cnt1, cnt2;
	objPlt->getAxisCnt(cnt1,cnt2);
	QList<double> arrX;
	QList<double> arrY;
	for( int i=0; i<cnt2; i++ ) {
		objPlt->outAxisValueX(cnt,i,x,y);
		arrX.append(x);
		arrY.append(y);
	}
	frm2DLine frm2D(arrX,arrY,tr("Y"),tr("Z"),make2DGraphTitle()+"-"+tr("Y Line"));
	frm2D.exec();
	//QMessageBox::information(this,"outcsv","output csv "+fnm);
}

void frm3d::on_btnLine_2_clicked()
{
	QString fnm = sOutDir+"/xdata.csv";
	QString tmp = ui.cmbLine_2->currentText();
	int cnt = tmp.toInt()-1;
	if ( objPlt->outCsvY(cnt,fnm) == false ) {
		QMessageBox::critical(this,"outcsv","output csv Error");
		return;
	}
	double x,y;
	int cnt1, cnt2;
	QList<double> arrX;
	QList<double> arrY;
	objPlt->getAxisCnt(cnt1,cnt2);
	for( int i=0; i<cnt1; i++ ) {
		objPlt->outAxisValueY(cnt,i,x,y);
		arrX.append(x);
		arrY.append(y);
	}
	frm2DLine frm2D(arrX,arrY,tr("X"),tr("Z"),make2DGraphTitle()+"-"+tr("X Line"));
	frm2D.exec();
	//QMessageBox::information(this,"outcsv","output csv "+fnm);
}

void frm3d::on_pushButton_2_clicked()
{
	double **dAvgVal;
	int x = ui.avgx->text().toInt();
	int y = ui.avgy->text().toInt();

	dAvgVal = objPlt->getAverageValue(x,y);

	frmAverage frmAvg;
	frmAvg.setAvgValue(x,y,dAvgVal);
	frmAvg.exec();
}
