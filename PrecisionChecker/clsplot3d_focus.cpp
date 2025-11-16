#include "clsplot3d.h"
#include "XImageBufferFunctions.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XFocus.h"
#include <stdio.h>
#include "XGeneralFunc.h"

extern	LayersBase	*Layers;

//#define DEBUG

/// 輝度確認
void clsPlot3D::plotFocus(int nPage) {
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

	/// フォーカスレベル計算
	int nY = 0;
	double zMax = 0;
	double zMin = 9999;
	ImageBuffer *img = &Layers->GetPageData(nPageIdx)->GetLayerData(0)->GetMasterBuff();
	if ( img->IsNull() == true ) return;

	PureFlexAreaList *lst = objCtrl->tblFArea[nPage].GetFirst();
	for( c=objCtrl->tblPadCnt[nPage].GetFirst(); c!=NULL; ) {
		for( int i=0; i<c->cnt; i++ ) {
			int x, y;
			double val;
			lst->GetCenter(x,y);

			//FlexArea *area;
			//area = (FlexArea *)lst;
			val = GetFocusLevel(*img,*lst);

			data[i][nY].x = x;
			data[i][nY].y = -y;
			data[i][nY].z = val;
			if ( zMax < val ) zMax = val;
			if ( zMin > val ) zMin = val;
			lst = lst->GetNext();
		}
		nY ++;
		c = c->GetNext();
	}

	setRotation(nRoteX,nRoteY,nRoteZ);
	setScale(1,1,nZScale_Focus);
	setShift(0.15,0,0);
	setZoom(1);

	bndPlotData(xmesh,ymesh,zMin);
	loadFromData(data,xmesh,ymesh);

	setGraphEnv(zMin,zMax,"Level");

	updateData();
	updateGL();

#ifdef DEBUG
	FILE *fp;
	ForceDirectories("C:/Tmp"); 

	fp = fopen("C:/Tmp/focus_plot.dat","w");
	for( int i=0; i<ymesh; i++ ) {
		for( int j=0; j<xmesh; j++ ) {
			fprintf(fp,"%d,%d,%f,%f,%f\n",i,j,data[i][j].x,data[i][j].y,data[i][j].z);
		}
	}
	fclose(fp);
#endif
}
