#include "clsplot3d.h"
#include "XImageBufferFunctions.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <stdio.h>
#include "XGeneralFunc.h"

extern	LayersBase	*Layers;

//#define DEBUG

/// 輝度確認
void clsPlot3D::plotBrightness(int nPage) {
	nPageIdx = nPage;

	// 座標データ生成
	if ( data != NULL ) {
		for( int i=0; i<xmesh; i++ ) {
			delete(data[i]);
		}
	}
	xmesh = 0;
	ymesh = objCtrl->tblPadCnt[nPage].GetNumber();
	clsPadCnt *c = objCtrl->tblPadCnt[nPage].GetFirst();
	for( int i=0; i<ymesh; i++ ) {
		if ( xmesh < c->cnt ) xmesh = c->cnt;
		c = c->GetNext();
	}

	data = new Triple*[xmesh];
	for( int i=0; i<xmesh; i++ ) {
		data[i] = new Triple[ymesh];
	}

	/// 輝度計算
	int nY = 0;
	int idx = 0;
	double zMax = 0;
	double zMin = 9999;
	clsPadArea *lst = objCtrl->tblPadArea[nPage].GetFirst();
	for( c=objCtrl->tblPadCnt[nPage].GetFirst(); c!=NULL; ) {
		for( int i=0; i<c->cnt; i++ ) {
			int x, y, val=0;
			x = lst->x;
			y = lst->y;
			int xx, yy;
			bool calcFlg = true;
			if ( bBrightMode == true ) {
				if ( i >= c->cnt-1 ) {
					calcFlg = false;
				} else {
					calcFlg = true;
					clsPadArea *nxt = lst->GetNext();
					xx = x+(nxt->x-x)/2;
				}
				if ( c->GetNext() == NULL ) {
					calcFlg = false;
				} else {
					int tidx = idx + c->cnt;
					if ( tidx < 0 || tidx >= objCtrl->tblPadArea[nPage].GetNumber() ) {
						calcFlg = false;
					} else {
						clsPadArea *nxt = objCtrl->tblPadArea[nPage].GetItem(tidx);
						yy = y+(nxt->y-y)/2;
					}
				}
			} else {
				xx = x;
				yy = y;
			}
			if ( calcFlg == true ) {
				val = calcCenterBrightness(lst->FArea,xx,yy);
			}
			data[i][nY].x = x;
			data[i][nY].y = -y;
			data[i][nY].z = val;
			if ( zMax < val ) zMax = val;
			if ( zMin > val ) zMin = val;
			lst = lst->GetNext();
			idx ++;
		}
		nY ++;
		c = c->GetNext();
	}

	setRotation(nRoteX,nRoteY,nRoteZ);
	setScale(1,1,nZScale_Brightness);
	setShift(0.15,0,0);
	setZoom(0.8);

	bndPlotData(xmesh,ymesh,zMin);
	loadFromData(data,xmesh,ymesh);

	setGraphEnv(zMin,zMax,"B");

	updateData();
	updateGL();

#ifdef DEBUG
	FILE *fp;
	ForceDirectories("D:/Tmp"); 
	fp = fopen("D:/Tmp/bright_plot.dat","w");
	for( int i=0; i<xmesh; i++ ) {
		for( int j=0; j<ymesh; j++ ) {
			fprintf(fp,"%d,%d,%f,%f,%f\n",i,j,data[i][j].x,data[i][j].y,data[i][j].z);
		}
	}
	fclose(fp);
#endif
}

int clsPlot3D::calcCenterBrightness(PureFlexAreaList *src, int x, int y) {
	DataInPage *dp = Layers->GetPageData(nPageIdx);

	int val[9], idx=0;
	for( int iy=y-1; iy<=y+1; iy++ ) {
		BYTE *s = dp->GetLayerData(0)->GetMasterBuff().GetY(iy);
		s += (x-1);
		val[idx] = (int)*s;
		idx ++; s++;
		val[idx] = (int)*s;
		idx ++; s++;
		val[idx] = (int)*s;
		idx ++;
	}
	int minVal = 9999, maxVal = 0;
	int sumVal = 0;
	for( int i=0; i<9; i++ ) {
		if ( minVal > val[i] ) minVal = val[i];
		if ( maxVal < val[i] ) maxVal = val[i];
		sumVal += val[i];
	}
	sumVal -= minVal + maxVal;
	return sumVal/7;
}