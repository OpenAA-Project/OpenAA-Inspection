#ifndef CLSPLOT3D_H
#define CLSPLOT3D_H

#include <QObject>
#include <QFrame>
#include <QGridLayout>
#include "CImgCtrl.h"

#include "qwt3d_surfaceplot.h"
#include "qwt3d_function.h"
#include "qwt3d_plot.h"


using namespace Qwt3D;

class clsCalc : public Function {
public :
	clsCalc() : Function() {
	}

	clsCalc(SurfacePlot *pw) : Function(pw) {
	}

	clsCalc(CImgCtrl *_obj, SurfacePlot *pw) : Function(pw) {
		objCtrl = _obj;
		nPageIdx = 0;
	}

	~clsCalc() {
	}
	void setPageIdx(int _page) {
		nPageIdx = _page;
	}

	double operator() (double x, double y);

private :
	int nPageIdx;
	CImgCtrl *objCtrl;
};

class Bar : public VertexEnrichment {
public :
	Bar();
	Bar(double rad, double level);

	Enrichment *clone() const {return new Bar(*this);}

	void configure(double rad, double level);
	void drawBegin();
	void drawEnd();
	void draw(Triple const&);

private :
	double level_, radius_;
	double diag_;
};

class  Label3D
{
public:
  void draw(Qwt3D::Triple const&, double w, double h);
};

class clsYAxisScale : public LinearScale {
public :
	Scale* clone() const {return new clsYAxisScale;}

	QString ticLabel(unsigned int idx) const {
		double val = majors_p[idx];
		if ( val ) {
			val *= -1;
			return QString::number(val);
		}
		return QString("");
	}
};

class clsPlot3D : public SurfacePlot {
public :
	clsPlot3D(CImgCtrl *_obj, QWidget *parent=0);
	~clsPlot3D();

	void drawTest(int nPage, int x1, int y1, int x2, int y2);

	/// フォーカスプロット
	void plotFocus(int nPage);

	/// 輝度確認プロット
	void setBrightMode(bool mode);
	void plotBrightness(int nPage);

	/// 分解能プロット
	void plotResolution(int nPage, double _val, bool flg=false);

	/// 直行確認プロット
	void plotAngle(int nPage);

	Bar *bar;

	//----------
	// Z軸スケール
	int nZScale_Brightness;
	int nZScale_Resolution;
	int nZScale_Angle;
	int nZScale_Focus;

	//---------
	// 標準ローテーション
	int nRoteX;
	int nRoteY;
	int nRoteZ;

	bool chartType;

	/// ポイント数取得
	void getAxisCnt(int &x, int &y);
	QString sOutDir;

	/// CSV出力
	bool outCsvX(int nPnt, QString fnam);
	bool outCsvY(int nPnt, QString fnam);

	bool outAxisValueX(int nPnt, int idx, double &x, double &y);
	bool outAxisValueY(int nPnt, int idx, double &x, double &y);

	/// 平均値出力
	double **getAverageValue(int x, int y);

private :
	clsCalc  calc;
	
	CImgCtrl *objCtrl;

	void InitGrp();
	void drawGrp();

	Triple **data;
	int xmesh;
	int ymesh;

	//-----------------------
	// 分解能関連
	//-----------------------
	/// パット間距離
	double dPatVal;

	/// 軸方向
	/**
	 * true:Y軸方向
	 * false:X軸方向
	 */
	bool dAxisFlg;

	//-----------------------
	// 輝度確認関連
	//-----------------------
	bool bBrightMode;
	int calcCenterBrightness(PureFlexAreaList *src, int x, int y);

	//-----------------------
	// 直行確認関連
	//-----------------------
	double calcAngleFArea(clsPadArea *src, 
						  clsPadArea *top, 
						  clsPadArea *btom, 
					      clsPadArea *right,
					      clsPadArea *left  );

	double calcAngle(double x1, double y1, double x2, double y2, double x3, double y3 );

	/// グラフ設定
	void setGraphEnv(double dZMin, double dZMax, char *sZLabel);

	/// ３Ｄグラフデータ補正
	void bndPlotData(int xmesh, int ymesh, double dZMin);

	/// ページインデックス
	int nPageIdx;

	/// 平均値配列
	double **dAvgVal;
	int nAvgX;
	int nAvgY;
	void MakeAvgVal(int x, int y);
	double calcAverage(int startX, int startY, int endX, int endY);
};
#endif // CLSPLOT3D_H
