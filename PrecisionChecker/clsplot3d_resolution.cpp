#include "clsplot3d.h"
#include "XImageBufferFunctions.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <stdio.h>
#include "XGeneralFunc.h"

extern	LayersBase	*Layers;

//#define DEBUG

/// 分解能
void clsPlot3D::plotResolution(int nPage, double _val, bool flg) {
	nPageIdx = nPage;
	dPatVal  = _val;
	dAxisFlg = flg;

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

	// 分解能計算
	int nY = 0;
	double zMax = 0;
	double zMin = 9999;
	PureFlexAreaList *lst = objCtrl->tblFArea[nPage].GetFirst();
	for( c = objCtrl->tblPadCnt[nPage].GetFirst(); c!=NULL; ) {
		for( int i=0; i<c->cnt; i++ ) {
			double x, y;
			double px=0, py=0;
			lst->GetWeightCenter(x,y);
			if ( dAxisFlg == false ) { // X軸方向
				if ( i < c->cnt-1 ) {
					PureFlexAreaList *plst = lst->GetNext();
					if ( plst != NULL ) {
						plst->GetWeightCenter(px,py);
					}
				} else {
					PureFlexAreaList *plst = lst->GetPrev();
					if ( plst != NULL ) {
						plst->GetWeightCenter(px,py);
					}
				}
			} else { // Y軸方向
				PureFlexAreaList *plst = lst;
				int j;
				for( j=0; j<=c->cnt; j++ ) {
					plst = plst->GetNext();
					if ( plst == NULL ) break;
				}
				if ( plst != NULL ) {
					plst->GetWeightCenter(px,py);
				} else {
					px = x;
					py = y;
				}
			}
			double val = sqrt((x-px)*(x-px)+(y-py)*(y-py));
			double z = 0;
			if ( val != 0 ) z = dPatVal/val;
			data[i][nY].x = x;
			data[i][nY].y = -y;
			data[i][nY].z = z;
			if ( zMax < z ) zMax = z;
			if ( zMin > z ) zMin = z;
			lst = lst->GetNext();
		}
		nY ++;
		c = c->GetNext();
	}

	// 3Dグラフ表示
	setRotation(nRoteX,nRoteY,nRoteZ);
	setScale(1,1,nZScale_Resolution);
	setShift(0.15,0,0);
	setZoom(0.8);

	bndPlotData(xmesh,ymesh,zMin);
	loadFromData(data,xmesh,ymesh);

	setGraphEnv(zMin, zMax,"Z(um)");

	updateData();
	updateGL();

#ifdef DEBUG
	ForceDirectories("D:/Tmp"); 
	FILE *fp = fopen("D:/Tmp/resolution_plot.dat","w");
	for( int i=0; i<ymesh; i++ ) {
		for( int j=0; j<xmesh; j++ ) {
			fprintf(fp,"%d,%d,%f,%f,%f\n",i,j,data[i][j].x,data[i][j].y,data[i][j].z);
		}
	}
	fclose(fp);
#endif
}
