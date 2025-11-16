#include "PrecisionCheckerLib.h"
#include "CImgCtrl.h"
#include "paramset.h"
#include "frm3d.h"
#include "XDataInLayer.h"
#include "XImageBufferFunctions.h"
#include "XPointer.h"

PrecisionCheckerLib::PrecisionCheckerLib()
{
	CurrentPage=0;

	objPrm = new ParamSet();
	objCtrl = new CImgCtrl();
	obj3d = new frm3d(objCtrl);
}

PrecisionCheckerLib::~PrecisionCheckerLib()
{

}


bool	PrecisionCheckerLib::chkBit(int page ,int x ,int y)
{
	return objCtrl->chkBit(page,x,y);
}

int		PrecisionCheckerLib::chkFlexArea(int page ,int x ,int y)
{
	return objCtrl->chkFlexArea(page ,x ,y);
}

void	PrecisionCheckerLib::BuildShow(LayersBase *Base,int page)
{
	obj3d->setPageCnt(Base->GetPageNumb());

	// ２値化ビット列生成
	objCtrl->makeImgTbl(Base->GetPageNumb(),Base->GetDotPerLine(page),Base->GetMaxLines(page));
	/*
	for( int i=0; i<iPageNumb; i++ ) {
		DataInPage *dp = Layers->GetPageData(i);
		objCtrl->setImgTblBuf(i,dp);
	}
	*/
	objCtrl->setImgTblBuf();
}

void PrecisionCheckerLib::on_ParamButton_clicked()
{
	objPrm->show();
}

void PrecisionCheckerLib::setPrm() 
{
	int min, max;
	bool mode;
	objPrm->getPadValueRange(min,max);
	objCtrl->setRangePatternByte(min,max);
	objPrm->getThreshValue(min,max,mode);
	objCtrl->setThreshValue(min,max,mode);
}


void PrecisionCheckerLib::on_GRP_clicked(int x1, int y1, int x2, int y2)
{
	obj3d->drawTestPlot(CurrentPage,x1,y1,x2,y2);
	obj3d->move(0,0);
	obj3d->show();
}

void PrecisionCheckerLib::on_Focus_clicked()
{
	setInitRotation();
	obj3d->setZScale(1,objPrm->getZScale(1),objPrm->getChartType(1));
	obj3d->plotFocus(CurrentPage);
	obj3d->move(0,0);
	obj3d->show();
}

void PrecisionCheckerLib::on_Brightness_clicked()
{
	setInitRotation();
	obj3d->setZScale(2,objPrm->getZScale(2),objPrm->getChartType(2));
	obj3d->plotBrightness(CurrentPage);
	obj3d->move(0,0);
	obj3d->show();
}

void PrecisionCheckerLib::on_Resolution_clicked()
{
	double val;
	bool flg = objPrm->getAxisVal(val);
	setInitRotation();
	obj3d->setZScale(3,objPrm->getZScale(3),objPrm->getChartType(3));
	obj3d->plotResolution(CurrentPage,val,flg);
	obj3d->move(0,0);
	obj3d->show();
}

void PrecisionCheckerLib::on_Angle_clicked()
{
	setInitRotation();
	obj3d->setZScale(4,objPrm->getZScale(4),objPrm->getChartType(4));
	obj3d->plotAngle(CurrentPage);
	obj3d->move(0,0);
	obj3d->show();
}

void PrecisionCheckerLib::setInitRotation() 
{
	int x,y,z;
	objPrm->getInitRotation(x,y,z);
	obj3d->setInitRotation(x,y,z);
	obj3d->setOutDir(objPrm->getOutDir());
	bool mode;
	objPrm->getBrightMode(mode);
	obj3d->setBrightMode(mode);
}

void PrecisionCheckerLib::on_Histgram_clicked(int x1, int y1, int x2, int y2) {
	objCtrl->viewHistgram(CurrentPage,x1,y1,x2,y2);
}

int PrecisionCheckerLib::getImgWid() { 
	return objCtrl->nWid;
}

int PrecisionCheckerLib::getImgHei() {
	return objCtrl->nHei;
}
