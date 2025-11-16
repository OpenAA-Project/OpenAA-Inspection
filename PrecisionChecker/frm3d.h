#ifndef FRM3D_H
#define FRM3D_H

#include "CImgCtrl.h"
#include <QWidget>
#include "ui_frm3d.h"
#include "clsplot3d.h"

#include "qwt3d_surfaceplot.h"
#include "qwt3d_function.h"
#include "qwt3d_plot.h"

#include "frm2dline.h"
#include "frmaverage.h"

using namespace Qwt3D;

class frm3d : public QWidget
{
	Q_OBJECT

public:
	frm3d(CImgCtrl *_obj, QWidget *parent = 0);
	~frm3d();

	void drawTestPlot(int _nPageIdx,int x1, int y1, int x2, int y2);

	/// ピント解析
	void plotFocus(int _nPageIdx);

	/// 輝度確認
	void setBrightMode(bool mode);
	void plotBrightness(int _nPageIdx);

	/// 分解能
	void plotResolution(int _nPageIdx, double _dPadVal, bool _bFlg=false);

	/// 直行確認
	void plotAngle(int _nPaegIdx);

	/// ページ数セット
	void setPageCnt(int _page);

	/// ローテーション初期値セット
	void setInitRotation(int x, int y, int z);

	/// Zスケールセット
	void setZScale(int idx, int scale, bool type);

	void setOutDir(QString dir);

	void setAvgXY(int x, int y);

protected :
	void keyPressEvent( QKeyEvent *evt );

private:
	Ui::frm3dClass ui;

	clsPlot3D *objPlt;
	CImgCtrl  *objCtrl;

	/// グラフモード
	/**
	 * 1:ピント
	 * 2:輝度
	 * 3:分解能
	 * 4:直行
	 */
	int nDrawMode;

	/// ページ数
	int nMaxPage;

	/// カレントページ
	int nPageIdx;

	//-------------
	// 分解能パラメータ
	double dPadVal;
	bool   bFlg;

	/// 座標コンボボックスセット
	void setCmbAxis();

	QString sOutDir;

	QString make2DGraphTitle();

private slots:
	void on_pushButton_2_clicked();
	void on_btnLine_2_clicked();
	void on_btnLine_1_clicked();
	void on_pushButton_clicked();
};

#endif // FRM3D_H
