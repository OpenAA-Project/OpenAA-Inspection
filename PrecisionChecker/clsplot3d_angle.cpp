#include "clsplot3d.h"
#include "XImageBufferFunctions.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <stdio.h>
#include <math.h>
#include "XGeneralFunc.h"

extern	LayersBase	*Layers;

//#define DEBUG

/// 直行確認
void clsPlot3D::plotAngle(int nPage) {
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
		for( int j=0; j<ymesh; j++ ) {
			data[i][j].z = NULL;
		}
	}

	/// 直行計算
	int nY = 0;
	int idx = 0;
	double zMax = 0;
	double zMin = 9999;
	clsPadArea *lst = objCtrl->tblPadArea[nPage].GetFirst();
	for( c=objCtrl->tblPadCnt[nPage].GetFirst(); c!=NULL; ) {
		for( int i=0; i<c->cnt; i++ ) {
			double x, y, val;
			x = lst->x;
			y = lst->y;
			
			int tidx;
			clsPadArea *top, *btom, *right, *left;
			if ( nY >= 105 ) {
				int pppp = 10;
			}

			if ( nY == 0 ) {
				top = NULL;
			} else {
				tidx = idx - c->GetPrev()->cnt;
				if ( tidx < 0 || tidx >= objCtrl->tblPadArea[nPage].GetNumber() ) top = NULL;
				else top = objCtrl->tblPadArea[nPage].GetItem(tidx);
				if ( c->cnt != c->GetPrev()->cnt && top != NULL ) {
					if ( abs(x-top->x) > 50 ) {
						if ( x > top->x ) {
							clsPadArea *tmp = top;
							top = NULL;
							for( int k=0; k<abs(c->cnt-c->GetPrev()->cnt); k++ ) {
								tmp = tmp->GetNext();
								if ( tmp == NULL ) break;
								if ( abs(x-tmp->x) <= 50 ) {
									top = tmp;
									break;
								}
							}
						} else {
							clsPadArea *tmp = top;
							for( int k=0; k<abs(c->cnt-c->GetPrev()->cnt); k++ ) {
								tmp = tmp->GetPrev();
								if ( tmp == NULL ) break;
								if ( abs(x-tmp->x) <= 50 ) {
									top = tmp;
									break;
								}
							}
						}
					}
				}
			}
			if ( c->GetNext() == NULL ) {
				btom = NULL;
			} else {
				tidx = idx + c->cnt;
				if ( tidx < 0 || tidx >= objCtrl->tblPadArea[nPage].GetNumber() ) btom = NULL;
				else btom = objCtrl->tblPadArea[nPage].GetItem(tidx);
				if ( c->cnt != c->GetNext()->cnt && btom != NULL ) {
					if ( abs(x-btom->x) > 50 ) {
						if ( x > btom->x ) {
							clsPadArea *tmp = btom;
							btom = NULL;
							for( int k=0; k<abs(c->cnt-c->GetNext()->cnt); k++ ) {
								tmp = tmp->GetNext();
								if ( tmp == NULL ) break;
								if ( abs(x-tmp->x) <= 50 ) {
									btom = tmp;
									break;
								}
							}
						} else {
							clsPadArea *tmp = btom;
							btom = NULL;
							for( int k=0; k<abs(c->cnt-c->GetNext()->cnt); k++ ) {
								tmp = tmp->GetPrev();
								if ( tmp == NULL ) break;
								if ( abs(x-tmp->x) <= 50 ) {
									btom = tmp;
									break;
								}
							}
						}
					}
				}
			}				
			if ( i == 0 ) {
				right = NULL;
			} else {
				if ( idx-1 < 0 ) right = NULL;
				else right = objCtrl->tblPadArea[nPage].GetItem(idx-1);
			}
			if ( i+1 >= c->cnt ) {
				left = NULL;
			} else {
				if ( idx+1 >= objCtrl->tblPadArea[nPage].GetNumber() ) left = NULL;
				else left = objCtrl->tblPadArea[nPage].GetItem(idx+1);
			}
			val = calcAngleFArea(lst,top,btom,right,left);

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
	setScale(1,1.3,(double)nZScale_Angle);
	setShift(0.15,0,0);
	setZoom(0.8);

	bndPlotData(xmesh,ymesh,zMin);
	loadFromData(data,xmesh,ymesh);

	setGraphEnv(zMin,zMax,"RAD");

	updateData();
	updateGL();

#ifdef DEBUG
	FILE *fp;
	ForceDirectories("D:/Tmp"); 
	fp = fopen("D:/Tmp/angle_plot.dat","w");
	for( int i=0; i<ymesh; i++ ) {
		for( int j=0; j<xmesh; j++ ) {
			fprintf(fp,"%d,%d,%f,%f,%f\n",i,j,data[i][j].x,data[i][j].y,data[i][j].z);
		}
	}
	fclose(fp);
#endif
}

double clsPlot3D::calcAngleFArea(clsPadArea *src, 
					 clsPadArea *top, 
					 clsPadArea *btom, 
					 clsPadArea *right,
					 clsPadArea *left  ) {
	if ( src == NULL ) return 0;
	double minRad = 9999;
	double val[4];

	double x, y;
	double cx[4], cy[4];
	clsPadArea *arrFArea[4];
	for( int i=0; i<4; i++ ) {
		cx[i] = -1;
		cy[i] = -1;
	}
	arrFArea[0] = top;
	arrFArea[1] = left;
	arrFArea[2] = btom;
	arrFArea[3] = right;

	x = src->x;
	y = src->y;
	for( int i=0; i<4; i++ ) {
		if ( arrFArea[i] != NULL ) {
			cx[i] = arrFArea[i]->x;
			cy[i] = arrFArea[i]->y;
		}
	}

	for( int i=0; i<4; i++ ) {
		if ( i == 3 ) {
			if ( cx[i] < 0 || cx[0] < 0 ) {
				val[i] = 9999;
			} else {
				val[i] = calcAngle(x,y,cx[i],cy[i],cx[0],cy[0]);
			}
		} else {
			if ( cx[i] < 0 || cx[i+1] < 0 ) {
				val[i] = 9999;
			} else {
				val[i] = calcAngle(x,y,cx[i],cy[i],cx[i+1],cy[i+1]);
			}
		}
	}

	for( int i=0; i<4; i++ ) {
		if ( minRad > val[i] ) {
			minRad = val[i];
		}
	}

	if ( minRad == 9999 ) return 0;
	return minRad;
}

double clsPlot3D::calcAngle(double x1, double y1, double x2, double y2, double x3, double y3) {
	double vax, vay, vbx, vby;

	vax = x2 - x1;
	vay = y2 - y1;
	vbx = x3 - x1;
	vby = y3 - y1;

	double s, t;
	s = vax*vby - vay*vbx;
	t = vax*vbx + vay*vby;
	double ret = atan2(s,t);
	return fabs(ret*180/PI);
}

