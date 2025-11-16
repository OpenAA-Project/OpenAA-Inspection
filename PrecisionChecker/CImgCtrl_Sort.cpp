#include "CImgCtrl.h"
#include "XImageBufferFunctions.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <math.h>
#include <omp.h>

extern	LayersBase	*Layers;

bool CImgCtrl::labelFArea(int nPageIdx) {
	clsPadAreaPack tmpTbl;
	clsPadAreaPack srcTbl = tblPadArea[nPageIdx];

	if ( srcTbl.GetNumber() == 0 ) {
		return false;
	}
	clsPadArea *minFArea;

	// ç≈è¨íléÊìæ
	minFArea = getMinFArea(srcTbl);
	srcTbl.RemoveList(minFArea);
	tmpTbl.AppendList(minFArea);

	int linno = 0;
	while( srcTbl.GetNumber() > 0 ) {
		int nRet = labelFAreaLstLine(srcTbl,tmpTbl,minFArea);
		if ( nRet == -1 ) break;

		clsPadCnt *pcnt = new clsPadCnt(nRet);
		tblPadCnt[nPageIdx].AppendList(pcnt);

		if ( srcTbl.GetNumber() <= 0 ) break;
		minFArea = getMinFArea(srcTbl);
		if ( minFArea == NULL ) break;
		srcTbl.RemoveList(minFArea);
		tmpTbl.AppendList(minFArea);
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
	dbgPrtPadArea(tblPadArea[nPageIdx],tblPadCnt[nPageIdx],nPageIdx);
	dbgPrtPadCnt(tblPadCnt[nPageIdx],nPageIdx);
	return true;
}


int CImgCtrl::labelFAreaLstLine(clsPadAreaPack &lstSrc, clsPadAreaPack &lstDst, clsPadArea *minFArea) {
	int nCnt = 1;
	if ( lstSrc.GetNumber() == 0 ) return -1;

	clsPadArea *c, *s=minFArea;
	while( true ) {
		c = getLabelNextFArea(s,lstSrc);
		if ( c == NULL ) break;
		lstSrc.RemoveList(c);
		lstDst.AppendList(c);
		nCnt ++;
		s = c;
	}
	return nCnt;
}

clsPadArea *CImgCtrl::getLabelNextFArea(clsPadArea *minFArea, clsPadAreaPack &lstSrc) {
	clsPadArea *tmpFArea = NULL;
	double sx = minFArea->FArea->GetMaxX();
	double sy = minFArea->FArea->GetMaxY();//+minFArea->FArea->GetHeight();

	clsPadArea *minXArea = NULL;
	clsPadArea *minYArea = NULL;
	double mmx = 0;
	double mmy = 0;
	double mrad = 0;
	double mlen = 0;

	clsPadArea *cur = lstSrc.GetFirst();
	for( cur=lstSrc.GetFirst(); cur!=NULL; cur=cur->GetNext() ) {
		if ( sx > cur->x ) { // minFAreaÇÊÇËç∂ÇÃÇΩÇﬂèúäO
			continue;
		}
		if ( sy < cur->y ) { // minFAreaÇÊÇËâ∫ÇÃÇΩÇﬂèúäO
			continue;
		}
		double len,rad;
		calcLen(minFArea->x,cur->x,minFArea->y,cur->y,len,rad);
		if ( mlen == 0 ) {
			tmpFArea = cur;
			mlen = len;
		}
		if ( mlen > len ) {
			tmpFArea = cur;
			mlen = len;
		}
	}
	return tmpFArea;
}

int CImgCtrl::getThreshHold1(ImageBuffer *ibfBuf, int startX, int endX, int nStartY) {
	int n = 256;
	int hist[256];
	double max = -1000.0;

	for( int i=0; i<n; i++ ) hist[i] = 0;
	for( int iy=nStartY; iy<nHei; iy++ ) {
		BYTE *s = ibfBuf->GetY(iy);
		for( int ix=0; ix<endX; ix++ ) {
			if ( ix < startX ) {
				s++;
				continue;
			}
			int val = (int)*s;
			hist[val]++;
			s++;
		}
	}

	int th = 0;
	int sa,sb,da,db;
	double ma,mb,mt;
	double wa,wb,wt;
	double kai;
	for( int i=0; i<255; i++ ) {
		da = 0;
		sa = 0;
		for( int j=0; j<i; j++ ) {
			da += (hist[j]*j);
			sa += hist[j];
		}
		db = 0;
		sb = 0;
		for ( int j=i; j<n; j++ ) {
			db += (hist[j]*j);
			sb += hist[j];
		}
		if ( sa != 0 ) {
			ma = (double)da/(double)sa;
		} else {
			ma = 0.0;
		}
		if ( sb != 0 ) {
			mb = (double)db/(double)sb;
		} else {
			mb = 0.0;
		}
		mt = (double)(da+db)/(double)(sa+sb);
		wa = (double)sa/(double)(sa+sb);
		wb = (double)sb/(double)(sa+sb);
		kai = wa*(ma-mt)*(ma-mt)+wb*(mb-mt)*(mb-mt);
		if ( max < kai ) {
			max = kai;
			th = i;
		}
	}
	return th;
}

int CImgCtrl::getThreshHold2(ImageBuffer *ibfBuf, int startX, int endX, int nStart) {
	int n = 256;
	int hist[256];
	double min;

	for( int i=0; i<n; i++ ) hist[i] = 0;
	for( int iy=nStart; iy<nHei; iy++ ) {
		BYTE *s = ibfBuf->GetY(iy);
		for( int ix=0; ix<endX; ix++ ) {
			if ( ix < startX ) {
				s++;
				continue;
			}
			int val = (int)*s;
			hist[val]++;
			s++;
		}
	}

	int th = 0;
	double sa,sb,da,db;
	double ma,mb,mt;
	double oa,ob;
	double wa,wb,wt;
	double kai;
	double oo;

	for( int i=1; i<n-1; i++ ) {
		da = 0;
		sa = 0;
		for( int j=0; j<i; j++ ) {
			da += (hist[j]*j);
			sa += hist[j];
		}
		db = 0;
		sb = 0;
		for ( int j=i; j<n; j++ ) {
			db += (hist[j]*j);
			sb += hist[j];
		}
		if ( sa != 0 ) {
			ma = (double)da/(double)sa;
		} else {
			ma = 0.0;
		}
		if ( sb != 0 ) {
			mb = (double)db/(double)sb;
		} else {
			mb = 0.0;
		}
		mt = (double)(da+db)/(double)(sa+sb);
		wa = (double)sa/(double)(sa+sb);
		wb = (double)sb/(double)(sa+sb);
		if ( wa!=0.0 && wb!=0.0 ) {
			oa = ob = 0.0;
			for( int j=0; j<i; j++ ) {
				oo = (double)(j-ma);
				oo = oo*oo*hist[j];
				oa += oo;
			}
			oa /= ((double)sa);
			for( int j=i+1; j<n; j++ ) {
				oo = (double)(j-mb);
				oo = oo*oo*hist[j];
				ob += oo;
			}
			ob /= ((double)sb);
			kai = wa*log(oa/wa)+wb*log(ob/wb);
			if ( kai > 0.0 && (th==0 || min>kai) ) {
				min = kai;
				th  = i;
			}
		}
	}
	return th;
}

int CImgCtrl::getThreshHold3(ImageBuffer *ibfBuf, int startX, int endX, int nStart) {
	int n = 256;
	int hist[256];
	double min;

	for( int i=0; i<n; i++ ) hist[i] = 0;
	for( int iy=nStart; iy<nHei; iy++ ) {
		BYTE *s = ibfBuf->GetY(iy);
		for( int ix=0; ix<endX; ix++ ) {
			if ( ix < startX ) {
				s++;
				continue;
			}
			int val = (int)*s;
			hist[val]++;
			s++;
		}
	}

	int sum=0;
	for( int i=0; i<n; i++ ) {
		sum +=hist[i];
	}
	int p  = 2;
	int ps = sum*p/100;
	for( int i=0; i<n; i++ ) {
		sum +=hist[i];
		if ( sum>=ps ) return i;
	}
	return n-1;
}

int CImgCtrl::getThreshold_unit(int *hist, int n, double *k) {
	int th;
	int i,j;
	double max,max_mt=0.0;
	int sa,sb,da,db;
	double ma,mb,mt;
	double wa,wb,wt;
	double oo,ot,st,dt;
	double kai;

	max = -1000.0;
	th  = 0;
	for(i=1;i<n-1;i++) {
		da=0;
		sa=0;
		for(j=0;j<i;j++) {
			da+=(hist[j]*j);
			sa+=hist[j];
		}
		db=0;
		sb=0;
		for(j=i;j<n;j++) {
			db+=(hist[j]*j);
			sb+=hist[j];
		}
		if(sa!=0.0)
			ma=(double)da/(double)sa;
		else
			ma=0.0;
		if(sb!=0.0)
			mb=(double)db/(double)sb;
		else
			mb=0.0;
		mt=(double)(da+db)/(double)(sa+sb);
		wa=(double)sa/(double)(sa+sb);
		wb=(double)sb/(double)(sa+sb);
		kai=wa*(ma-mt)*(ma-mt)+wb*(mb-mt)*(mb-mt);
		if(max<kai) {
			max_mt=mt;
			max=kai;
			th=i;
		}
	}
	st=0;
	dt=0;
	for(j=0;j<n;j++) {
		oo=(double)j-max_mt;
		oo=oo*oo*(double)hist[j];
		dt+=oo;
		st+=(double)hist[j];
	}
	ot=dt/st;
	*k=max/ot;
	return th;
}

int CImgCtrl::getThreshold_unit2(int *hist, int n, double *k) {
	int th;
	int i,j;
	double max,max_mt;
	double min;
	int sa,sb,da,db;
	double ma,mb,mt;
	double wa,wb,wt;
	double oa,ob;
	double oo,ot,st,dt;
	double kai;

	max = -1000.0;
	min = 256;
	th  = 0;
	for(i=1;i<n-1;i++) {
		da=0;
		sa=0;
		for(j=0;j<i;j++) {
			da+=(hist[j]*j);
			sa+=hist[j];
		}
		db=0;
		sb=0;
		for(j=i;j<n;j++) {
			db+=(hist[j]*j);
			sb+=hist[j];
		}
		if(sa!=0.0)
			ma=(double)da/(double)sa;
		else
			ma=0.0;
		if(sb!=0.0)
			mb=(double)db/(double)sb;
		else
			mb=0.0;
		mt=(double)(da+db)/(double)(sa+sb);
		wa=(double)sa/(double)(sa+sb);
		wb=(double)sb/(double)(sa+sb);
		if(wa!=0.0 && wb!=0.0) {
			oa=ob=0;
			for(j=0;j<i;j++) {
				oo = (double)(j-ma);
				oo = oo*oo*hist[j];
				oa+=oo;
			}
			oa/=(double)sa;
			for(j=i;j<n;j++){
				oo = (double)(j-mb);
				oo = oo*oo*hist[j];
				ob+=oo;
			}
			ob/=(double)sb;
			kai=wa*log(oa/wa)+wb*log(ob/wb);
			if (kai>0&&(th==0||min>kai)) {
				min=kai;
				th=i;
			}
		}
	}
	st=0;
	dt=0;
	for(j=0;j<n;j++) {
		oo=(double)j-max_mt;
		oo=oo*oo*(double)hist[j];
		dt+=oo;
		st+=(double)hist[j];
	}
	ot=dt/st;
	*k=max/ot;
	return th;
}

bool CImgCtrl::unitThreshold(int nPageIdx, ImageBuffer *ibfBuf) {
	int kpi=70;

	int unit = nWid/ImgDevCnt;
	int lx = nWid/unit;
	int ly = 0;
	int nowth=-1;
	int newth=0;
	int th=-1;
	double kp=(double)(0.7);

	int x1 = 0;
	int y1 = 0;
	int hist[256];
	int hist2[256];
	for(int y=0;y<=ly;y++) {
		for(int x=0;x<lx;x++) {
			int sx=x1+x*unit;
			int ex=x1+(x+1)*unit;
			int sy=1300;//y1+y*ImgDevCnt;
			int ey=nHei;//y1*(y+1)*ImgDevCnt;

			for(int i=0;i<256;i++) {
				hist[i]=0;
				hist2[i]=0;
			}
			for(int yy=sy;yy<ey;yy++) {
				BYTE *s = ibfBuf->GetY(yy);
				s += sx;
				for(int xx=sx;xx<ex;xx++) {
					int val = (int)*s;
					if ( val > 100 ) {
						hist[val]++;
					}
					s++;
				}
			}
			double a;
			newth=getThreshold_unit(hist,256,&a);
			if (a>kp || th<0) {
				nowth=newth;
			}
			if(a>kp) th=nowth;
			else th=(nowth+newth)/2;
			if (x+1==lx) th-=10;
			for(int yy=sy;yy<ey;yy++) {
				BYTE *s = ibfBuf->GetY(yy);
				s += sx;
				BYTE p=oImgTbl[nPageIdx][yy][sx/8];
				if ( sx % 8 > 0 ) {
					for(int i=0;i<sx%8;i++) {
						p = p << 1;
					}
				}
				int xpnt = sx/8;
				int idx  = sx%8;
				for(int xx=sx;xx<ex;xx++) {
					int val = (int)*s;
					if (th<val) {
						p = (p<<1)|0x01;
					} else {
						p = p << 1;
					}
					s++;
					idx++;
					if (idx>=8) {
						oImgTbl[nPageIdx][yy][xpnt] = p;
						xpnt++;
						idx = 0;
						//p = oImgTbl[nPageIdx][yy][xpnt];
						p = 0x00;
					}
				}
				if ( idx > 0 ) {
					p = p<<(8-idx);
					oImgTbl[nPageIdx][yy][xpnt] = p;
				}
			}
		}
	}

	return true;
}
