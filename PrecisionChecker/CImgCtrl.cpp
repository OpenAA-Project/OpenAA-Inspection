#include "CImgCtrl.h"
#include "XImageBufferFunctions.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "frm2dline.h"
#include <math.h>
#include <omp.h>

#include <QMessageBox>

extern	LayersBase	*Layers;

CImgCtrl::CImgCtrl()
{
	oImgTbl = NULL;
	dRadEMargin = 0.005;

	nMinPatternByte = 50;
	nMaxPatternByte = 200;

	ImgDevCnt = 8;
}

CImgCtrl::~CImgCtrl()
{

}

void CImgCtrl::setRangePatternByte(int min, int max) {
	nMinPatternByte = min;
	nMaxPatternByte = max;
}

void CImgCtrl::setThreshValue(int min, int max, bool mode) {
	nThreshValueMin = min;
	nThreshValueMax = max;
	bThreshMode     = mode;
}

void CImgCtrl::makeImgTbl(int _nPage, int _nWid, int _nHei) {
	nPage = _nPage;
	nWid  = _nWid;
	nHei  = _nHei;
	nBytWid = (int)(nWid/8);
	if ( nWid%8 > 0 ) nBytWid++;
	nBytHei = nHei;

	oImgTbl = new BYTE**[nPage];
	oFAreaBitBuf = new BYTE**[nPage];
	tblFArea   = new PureFlexAreaListContainer[nPage];
	tblPadCnt  = new NPListPack<clsPadCnt>[nPage];
	tblPadArea = new clsPadAreaPack[nPage];
	for( int i=0; i<nPage; i++ ) {
		oImgTbl[i] = MakeMatrixBuff(nBytWid,nBytHei);
		oFAreaBitBuf[i] = MakeMatrixBuff(nBytWid,nBytHei);
		MatrixBuffClear(oFAreaBitBuf[i],0,nBytWid,nBytHei);
	}


}

void CImgCtrl::setImgTblBuf() {
	for( int i=0; i<nPage; i++ ) {
		setImgTblBuf(i,Layers->GetPageData(i));
	}
}

int CImgCtrl::getThreshHold(ImageBuffer *ibfBuf, int i) {
	int val[3];
	nStartY = 0;
	for( int iy=0; iy<nHei; iy++ ) {
		BYTE *s = ibfBuf->GetY(iy);
		for( int j=0; j<3; j++ ) {
			val[0] = (int)*s;
			s++;
		}
		if ( val[0] > 50 && val[1] > 50 && val[2] > 50 ) {
			nStartY = iy;
			break;
		}
	}

	//nStartY = 2800;
	int unitX = (int)nWid/ImgDevCnt;
	int startX = i*unitX;
	int endX   = (i+1)*unitX;
	if ( startX > nWid ) startX = nWid;
	if ( endX   > nWid ) endX   = nWid;
	return getThreshHold2(ibfBuf,startX, endX, nStartY);
}

void CImgCtrl::setImgTblBuf(int nPageIdx, DataInPage *dp) {
	startTimeLog();
	wrtTimeLog("start");
	ImageBuffer *ibfBuf = &dp->GetLayerData(0)->GetMasterBuff();

	/*
	// 閾値計算
	int *nThreshVal;
	nThreshVal = (int *)malloc(sizeof(int)*ImgDevCnt);
	for( int i=0; i<ImgDevCnt; i++ ) nThreshVal[i] = 0;
	if ( bThreshMode == false ) {
		for( int i=0; i<ImgDevCnt; i++ ) {
			nThreshVal[i] = getThreshHold(ibfBuf,i)-10;
		}
	}

	// 二値化処理
	int unitX = (int)nWid/ImgDevCnt;
	for( int iy=nStartY; iy<nHei; iy++ ) {
		BYTE *s = ibfBuf->GetY(iy);
		int iXPnt = 0;
		int idx = 0;
		BYTE p = 0x00;
		for( int ix=0; ix<nWid; ix++ ) {
			int val = (int)*s;
			bool bitFlg = false;
			if ( bThreshMode == false ) {
				if ( *s >= nThreshVal[(int)(ix/unitX)] ) {
					bitFlg = true;
				}
			} else {
				if ( nThreshValueMin <= *s && *s <= nThreshValueMax ) {
					bitFlg = true;
				}
			}
			if ( bitFlg == true ) {
				p = (p<<1)|0x01;
			} else {
				p = p << 1;
			}
			s++;
			idx ++;
			if ( idx >= 8 ) {
				//memcpy( &oImgTbl[nPageIdx][iy][iXPnt], &p, sizeof(BYTE) );
				oImgTbl[nPageIdx][iy][iXPnt] = p;
				iXPnt ++;
				idx = 0;
				p = 0x00;
			}
		}
		if ( idx > 0 ) {
			p = p<<(8-idx);
			memcpy( &oImgTbl[nPageIdx][iy][iXPnt], &p, sizeof(BYTE) );
		}
	}
	free( nThreshVal );
	*/
	unitThreshold(nPageIdx,ibfBuf);
	wrtTimeLog("end binary");

	// ノイズ除去
	BYTE **tmp = MakeMatrixBuff(nBytWid,nBytHei);
	for( int i=0; i<3; i++ ) {
		ThinArea(oImgTbl[nPageIdx],tmp,nBytWid,nBytHei);
	}
	for( int i=0; i<3; i++ ) {
		FatArea(oImgTbl[nPageIdx],tmp,nBytWid,nBytHei);
	}
	DeleteMatrixBuff(tmp,nBytHei);

	// 仮措置
	//MatrixBuffClear(oImgTbl[nPageIdx],0x00,nBytWid,2000);
	//MatrixBuffBlockClear(oImgTbl[nPageIdx],nBytWid,nBytHei,(int)(600/8),0,nBytWid,nBytHei);
	//MatrixBuffBlockClear(oImgTbl[nPageIdx],nBytWid,nBytHei,0,900,nBytWid,nBytHei);
	wrtTimeLog("end Nose Delete");

	// 領域抽出
	setFlexArea(nPageIdx);
	wrtTimeLog("end FlexArea");

	// らべりんぐ
	//sortFAreaLst(nPageIdx);
	if ( labelFArea(nPageIdx) == false ) {
		return;
	}
	wrtTimeLog("end sort FlexArea");

	setFAreaBitBuf(nPageIdx);
	wrtTimeLog("end BitBuf FlexArea");
	endTimeLog();
}

// 領域抽出
bool CImgCtrl::setFlexArea(int nPageIdx) {
	BYTE **tmp = MakeMatrixBuff(nBytWid,nBytHei);
	MatrixBuffCopy(tmp,nBytWid,nBytHei,(const BYTE **)(oImgTbl[nPageIdx]),nBytWid,nBytHei);
	if ( PickupFlexArea(tmp,0,nBytWid*8,nBytHei,tblFArea[nPageIdx]) == false ) {
		return false;
	}
	DeleteMatrixBuff(tmp,nBytHei);

	for( PureFlexAreaList *c=tblFArea[nPageIdx].GetFirst(); c!=NULL; ) {
		int nByte = c->GetPatternByte();
		int nLeng = abs((c->GetMaxX()-c->GetMinX())-(c->GetMaxY()-c->GetMinY()));
		double x, y;
		c->GetCenter(x,y);
		//if ( nByte < nMinPatternByte || nByte > nMaxPatternByte ) {
		if ( nByte > nMaxPatternByte ) {
			PureFlexAreaList *tmp = c->GetNext();
			tblFArea[nPageIdx].RemoveList(c);
			c = tmp;
		} else if ( x < 10.0 ) {
			PureFlexAreaList *tmp = c->GetNext();
			tblFArea[nPageIdx].RemoveList(c);
			c = tmp;
			/*
		} else if ( nLeng > 10) {
			PureFlexAreaList *tmp = c->GetNext();
			tblFArea[nPageIdx].RemoveList(c);
			c = tmp;
			*/
		} else {
			c = c->GetNext();
		}
	}
		
	for( PureFlexAreaList *c=tblFArea[nPageIdx].GetFirst(); c!=NULL; ) {
		clsPadArea *area = new clsPadArea(c);
		area->val = floor(sqrt(area->x*area->x+area->y*area->y));
		tblPadArea[nPageIdx].AppendList(area);
		c = c->GetNext();
	}
	//dbgPrtPadArea(tblPadArea[nPageIdx],nPageIdx);

	return true;
}

void CImgCtrl::setFAreaBitBuf(int nPageIdx) {
	for( PureFlexAreaList *c=tblFArea[nPageIdx].GetFirst(); c!=NULL; ) {
		for( int i=0; i<c->GetFLineLen(); i++ ) {
			int x1 = c->GetFLineLeftX(i);
			int x2 = c->GetFLineRightX(i);
			int y = c->GetFLineAbsY(i);
			if ( i == 0 || i == c->GetFLineLen()-1 ) {
				setFAreaBitBufOnRange(nPageIdx,x1,x2,y);
			} else {
				setFAreaBitBufOnBit(nPageIdx,x1,y);
				setFAreaBitBufOnBit(nPageIdx,x2,y);
			}
		}
		double x=0;
		double y=0;
		c->GetWeightCenter(x,y);
		int cx = (int)x;
		int cy = (int)y;
		setFAreaBitBufOnBit(nPageIdx,cx,cy);
		c = c->GetNext();
	}
	//dbgOutImgTblBuf(oFAreaBitBuf[nPageIdx],nPageIdx);
}

void CImgCtrl::setFAreaBitBufOnBit(int nPageIdx, int nXPnt, int nYPnt) {
	int nBytXPnt = (int)(nXPnt/8);
	int nBitPnt  = nXPnt % 8;
	BYTE p = 0x00;
	BYTE d = 128;
	p = oFAreaBitBuf[nPageIdx][nYPnt][nBytXPnt] | d>>nBitPnt;
	memcpy(&oFAreaBitBuf[nPageIdx][nYPnt][nBytXPnt],&p,sizeof(BYTE));
}

void CImgCtrl::setFAreaBitBufOnRange(int nPageIdx, int nXPnt1, int nXPnt2, int nYPnt ) {
	int nBytXPnt1 = (int)(nXPnt1/8);
	int nBytXPnt2 = (int)(nXPnt2/8);
	int nBitPnt1 = nXPnt1 % 8;
	int nBitPnt2 = nXPnt2 % 8;
	int nBytLen = nBytXPnt2-nBytXPnt1+1;

	BYTE *pbuf = new BYTE[nBytLen];
	BYTE *p = pbuf;
	memset(p,0x00,nBytLen);
	if ( nBytLen == 1 ) {
		BYTE d1 = 0xFF;
		d1 = d1>>nBitPnt1;
		BYTE d2 = 0xFF;
		d2 = d2<<(7-nBitPnt2);
		*p = d1&d2;
	} else {
		for( int i=0; i<nBytLen; i++ ) {
			if ( i==0 ) {
				BYTE d = 0xFF;
				d = d>>nBitPnt1;
				memcpy(p,&d,1);
			} else if ( i+1==nBytLen ) {
				BYTE d = 0xFF;
				d = d<<(7-nBitPnt2);
				memcpy(p,&d,1);
			} else {
				memset(p,0xFF,1);
			}
			p++;
		}
	}
	BYTE *ptmp = new BYTE[nBytLen];
	for( int i=0; i<nBytLen; i++ ) {
		ptmp[i] = oFAreaBitBuf[nPageIdx][nYPnt][nBytXPnt1+i] | pbuf[i];
	}
	memcpy(&oFAreaBitBuf[nPageIdx][nYPnt][nBytXPnt1],ptmp,nBytLen);
}

// チェックビット
bool CImgCtrl::chkBit(int nPageIdx, int nXPnt, int nYPnt) {
	if ( nPageIdx >= nPage || nXPnt >= nWid || nYPnt >= nHei ) {
		return false;
	}
	if ( oImgTbl == NULL ) return false;

	int nBytXPnt = (int)(nXPnt/8);
	int nBitIdx  = nXPnt % 8;
	BYTE s;
	memcpy(&s,&oImgTbl[nPageIdx][nYPnt][nBytXPnt],sizeof(BYTE));
	BYTE p = 128;
	p = p>>nBitIdx;
	s = s & p;
	if ( s == p ) {
		return true;
	}
	return false;
}

/*
bool CImgCtrl::chkFlexArea(int nPageIdx, int nXPnt, int nYPnt) {
	if ( nPageIdx >= nPage || nXPnt >= nWid || nYPnt >= nHei ) {
		return false;
	}
	if ( oFAreaBitBuf == NULL ) return false;

	int nBytXPnt = (int)(nXPnt/8);
	int nBitIdx  = nXPnt % 8;
	BYTE s;
	memcpy(&s,&oFAreaBitBuf[nPageIdx][nYPnt][nBytXPnt],sizeof(BYTE));
	BYTE p = 128;
	p = p>>nBitIdx;
	s = s & p;
	if ( s == p ) {
		return true;
	}
	return false;
}
*/

int CImgCtrl::chkFlexArea(int nPageIdx, int nXPnt, int nYPnt) {
	if ( nPageIdx >= nPage || nXPnt >= nWid || nYPnt >= nHei ) {
		return false;
	}
	if ( oFAreaBitBuf == NULL ) return 0;

	/*
	if ( 4840 <= nXPnt && nXPnt <= 4880 && 4940 <= nYPnt && nYPnt <= 4980 ) {
		if ( chkIllFlexArea(nXPnt,nYPnt,9,nPageIdx) == true ) {
			return 2;
		}
	}
	*/
	int nBytXPnt = (int)(nXPnt/8);
	int nBitIdx  = nXPnt % 8;
	BYTE s;
	memcpy(&s,&oFAreaBitBuf[nPageIdx][nYPnt][nBytXPnt],sizeof(BYTE));
	BYTE p = 128;
	p = p>>nBitIdx;
	s = s & p;
	if ( s == p ) {
		return 1;
	}
	return 0;
}

bool CImgCtrl::chkIllFlexArea(int x, int y, int cnt, int nPage) {
	PureFlexAreaList *c = tblFArea[nPage].GetLast();
	for( int i=0; i<cnt; i++ ) {
		if ( c->GetMinX() <= x && x <= c->GetMaxX() &&
			c->GetMinY() <= y && y <= c->GetMaxY() ) {
				return true;
		}
		c = c->GetPrev();
	}
	return false;
}

void CImgCtrl::sortFAreaLst(int nPageIdx) {
	dbgPrtFlexAreaList(nPageIdx,true);
	clsPadAreaPack tmpTbl;
	clsPadAreaPack srcTbl = tblPadArea[nPageIdx];
	clsPadArea *minFArea, *minFArea2;

	// 最小値取得
	minFArea = getMinFArea(srcTbl);
	srcTbl.RemoveList(minFArea);
	tmpTbl.AppendList(minFArea);


	int linno = 0;
	while( srcTbl.GetNumber() > 0 ) {
		int nRet = sortFAreaLstLine(srcTbl,tmpTbl,minFArea);
		if ( nRet == -1 ) break;

		clsPadCnt *pcnt = new clsPadCnt(nRet);
		tblPadCnt[nPageIdx].AppendList(pcnt);

#ifndef DEBUG
		char pp[50];
		sprintf( pp, "\tline[%d] sort end",linno);
		wrtTimeLog(pp);
		linno++;
		if ( linno ==3 ) {
			int pa = 1;
		}
#endif
		if ( srcTbl.GetNumber() <= 0 ) break;
		minFArea = getMinFArea(srcTbl);
		if ( minFArea == NULL ) break;
		srcTbl.RemoveList(minFArea);
		tmpTbl.AppendList(minFArea);
		//minFArea->Remove();
	}

	wrtTimeLog("\tend sort");
	tblFArea[nPageIdx].InitialList();
	tblPadArea[nPageIdx].InitialList();
	clsPadArea *c, *p;
	for( c=tmpTbl.GetFirst(); c!=NULL; ) {
		c->FArea->SetNext(NULL);
		c->FArea->SetPrev(NULL);
		tblFArea[nPageIdx].AppendList(c->FArea);
		p = c->GetNext();
		tmpTbl.RemoveList(c);
		tblPadArea[nPageIdx].AppendList(c);
		c = p;
	}
	wrtTimeLog("\tend sorttbl moved");
	dbgPrtFlexAreaList(nPageIdx);
	dbgPrtPadCnt(tblPadCnt[nPageIdx],nPageIdx);
}

clsPadArea *CImgCtrl::getMinFArea(clsPadAreaPack &lst) {
	clsPadArea *minFArea = NULL;

	double minVal=0;
	for( clsPadArea *c=lst.GetFirst(); c!=NULL; ) {
		if ( minVal == 0 ) {
			minVal = c->val;
			minFArea = c;
		}
		if ( floor(minVal/10) == floor(c->val/10) ) {
			if ( minFArea->x > c->x ) {
				minFArea = c;
			}
		} else if ( minVal > c->val ) {
			minVal = c->val;
			minFArea = c;
		}
		c = c->GetNext();
	}
	return minFArea;
}

int CImgCtrl::sortFAreaLstLine(clsPadAreaPack &lstSrc, clsPadAreaPack &lstDst, clsPadArea *minFArea) {
	int nCnt = 1;
	if ( lstSrc.GetNumber() == 0 ) return -1;

	clsPadArea *c, *s=minFArea;
	while( true ) {
		c = getNextFArea(lstSrc,s);
		if ( c == NULL ) break;
		lstSrc.RemoveList(c);
		lstDst.AppendList(c);
		nCnt ++;
		s = c;
	}
	return nCnt;
}

clsPadArea *CImgCtrl::getNextFArea(clsPadAreaPack &lst, clsPadArea *minFArea) {
	clsPadArea *tmpFArea = NULL;
	double sx  = minFArea->x;
	double sy  = minFArea->y;
	double mmx = minFArea->FArea->GetMaxX();//+(minFArea->FArea->GetMaxX()-minFArea->FArea->GetMinX());
	double mmy = minFArea->FArea->GetMaxY()+(minFArea->FArea->GetMaxY()-minFArea->FArea->GetMinY());
	double minVal = 0;

	clsPadArea *c;
	for( c=lst.GetFirst(); c!=NULL; ) {
		if ( mmx > c->x ) {
			c = c->GetNext();
			continue;
		}
		if ( minVal == 0 ) {
			minVal = c->val;
			tmpFArea = c;
		}
		if ( minVal > c->val ) {
			if ( chkYAxis(minFArea,c) == true ) {
				minVal = c->val;
				tmpFArea = c;
			} else {
				clsPadArea *tmp = c;
				lst.RemoveList(c);
				c = tmp->GetNext();
				continue;
			}
		}
		c = c->GetNext();
	}
	return tmpFArea;
}

bool CImgCtrl::chkYAxis(clsPadArea *minFArea, clsPadArea *cur ) {
	double len, srad;

	calcLen( minFArea->x, minFArea->y, cur->x, cur->y, len, srad );
	double slen = (minFArea->FArea->GetMaxX()-minFArea->FArea->GetMinX())*3;
	if ( len > slen ) {
		return false;
	}
	return true;
}

double CImgCtrl::getLineRadian(clsPadArea *minFArea, clsPadAreaPack &lst) {
	clsPadArea *tmpFArea = NULL;

	double sx, sy;
	sx = minFArea->x;
	sy = minFArea->y;
	double mmx = minFArea->FArea->GetMaxX()+(minFArea->FArea->GetMaxX()-minFArea->FArea->GetMinX());
	double minVal = 0;
	
	for( clsPadArea *c=lst.GetFirst(); c!=NULL; ) {
		if ( mmx > c->x ) {
			c = c->GetNext();
			continue;
		}
		if ( minVal == 0 ) {
			minVal = c->val;
			tmpFArea = c;
		}
		if ( minVal > c->val ) {
			tmpFArea = c;
			minVal = c->val;
		}
		c = c->GetNext();
	}

	double mx, my;
	mx = tmpFArea->x;
	my = tmpFArea->y;
	double len, rad;
	calcLen(sx,mx,sy,my,len,rad);
	return rad;
}

bool CImgCtrl::chkFAreaRadian(clsPadArea *area, double x1, double y1, double srad ) {
	double x2, y2;
	x2 = area->x;
	y2 = area->y;
	double len, rad;
	calcLen(x1,x2,y1,y2,len,rad);

	double dxRad = fabs(srad-rad);
	if ( dxRad < dRadEMargin ) {
		return true;
	}
	return false;	
}

void CImgCtrl::calcLen(double x1, double x2, double y1, double y2, double &len, double &rad) {
	double dx = x1-x2;
	double dy = y1-y2;
	if ( dx < 0 ) dx *= -1;
	if ( dy < 0 ) dy *= -1;
	len = sqrt(dx*dx+dy*dy);
	rad = atan2(dy,dx);
}

void CImgCtrl::dbgOutImgTblBuf(BYTE **bitBuff, int nPageIdx) {
	char cFnam[50];
	sprintf( cFnam,"D:/Tmp/imgbuf%d.dat",nPageIdx);
	FILE *fp = fopen(cFnam,"w");
	for( int iy=0; iy<nBytHei; iy++ ) {
		for( int ix=0; ix<nBytWid; ix++ ) {
			BYTE s;
			memcpy(&s,&bitBuff[iy][ix],sizeof(BYTE));
			BYTE p = 128;
			for( int i=0; i<8; i++ ) {
				BYTE tmp = s;
				BYTE q = p>>i;
				tmp = tmp & q;
				if ( q == tmp ) {
					fprintf(fp,"1");
				} else {
					fprintf(fp,"0");
				}
			}
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}

void CImgCtrl::viewHistgram(int nPageIdx,int x1, int y1, int x2, int y2) {
	QList<double> arrX;
	QList<double> arrY;

	int th = calcHistgram(nPageIdx,x1,y1,x2,y2,arrX,arrY);
	frm2DLine frm2D(arrX,arrY,"bright","histgram","histgram plot");
	frm2D.setThreshold(th);
	frm2D.exec();

}

int CImgCtrl::calcHistgram(int nPageIdx, int x1, int y1, int x2, int y2, QList<double> &arrX, QList<double> &arrY) {
	int hist[256];
	for( int i=0; i<256; i++ ) hist[i] = 0;
	DataInPage *dp = Layers->GetPageData(nPageIdx);
	ImageBuffer *ibfBuf = &dp->GetLayerData(0)->GetMasterBuff();
	for( int iy=y1; iy<y2; iy++ ) {
		BYTE *s = ibfBuf->GetY(iy);
		for(int i=0; i<x1; i++ ) s++;
		for( int ix=x1; ix<x2; ix++ ) {
			int val = (int)*s;
			if ( val < 256 ) {
				hist[val] ++;
			}
			s++;
		}
	}

	arrX.clear();
	arrY.clear();
	for( int i=0; i<256; i++ ) {
		arrX.append((double)i);
		arrY.append((double)hist[i]);
	}

	double d;
	int th = getThreshold_unit(hist,256,&d);
	return th;
}