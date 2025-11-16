#ifndef MTIMAGESLIDER_H
#define MTIMAGESLIDER_H

#include <QWidget>
#include "mtImageSliderBase.h"

/**
 * @brief 画像スライダークラス<br>
 * 画像を用いたスライダーを作成する。
 */
class mtImageSlider : public QWidget, public mtImageSliderBase
{
	Q_OBJECT

public:
	/**
	 * @brief コンストラクタ
	 *
	 * @param QImage img1 スライダー画像
	 * @param QImage img2 背景画像
	 * @param QWidget *parent
	 */
	mtImageSlider(const QImage &img1, const QImage &img2, QWidget *parent);

	/**
	 * @brief コンストラクタ
	 *
	 * @param int _minValue 最小値
	 * @param int _maxValue 最大値
	 * @param QImage img1 スライダー画像
	 * @param QImage img2 背景画像
	 * @param QWidget *parent
	 */
	mtImageSlider(int _minValue, int _maxValue, const QImage &img1, const QImage &img2, QWidget *parent);

	/**
	 * @brief コンストラクタ
	 *
	 * @param int _minValue 最小値
	 * @param int _maxValue 最大値
	 * @param int _nSideDiv 目盛り（スライダー有効範囲）と背景画像の両端との距離(ピクセル）
	 * @param int _nStartX  背景画像の左端から左端の目盛りとの距離（ピクセル）
	 * @param int _nDivX    目盛り間の距離(ピクセル)
	 * @param QImage img1 スライダー画像
	 * @param QImage img2 背景画像
	 * @param QWidget *parent
	 */
	mtImageSlider(int _minValue, int _maxValue, int _nSideDiv, int _nStartX, int _nDivX, const QImage &img1, const QImage &img2, QWidget *parent);
	~mtImageSlider();

	/**
	 * @brief 最小値設定<br>
	 * スライダーの最小値を設定する。
	 * @param int _minValue 最小値
	 */
	void setMinimum(int _minValue)	{	minValue = _minValue;	}
	int  getMinimum()				{	return minValue;		}
	
	/**
	 * @brief 最大値設定<br>
	 * スライダーの最大値を設定する。
	 * @param int _maxValue 最大値
	 */
	void setMaximum(int _maxValue)	{	maxValue = _maxValue;	}
	int  getMaximum()				{	return maxValue;		}
	
	/**
	 * @brief スライダー値設定<br>
	 * スライダーの現在の値を設定する。
	 * @param int _value スライダー値
	 */
	void setValue(int _value);
	
	/**
	 * @brief スライダー値取得<br>
	 * スライダーの現在の値を設定する。
	 * @return int スライダー値
	 */
	int getValue()	{	return value;	}

	/**
	 * @brief 背景画像パラメータ設定<br>
	 * 背景画像のパラメータを設定し、<br>
	 * スライダーの動作およびスライダー値の計算を制御する。
	 * @param int _nStart 背景の左端から最初の目盛りまでのピクセル値
	 * @param int _nDiv 背景の目盛り１つの幅のピクセル値
	 */
	void setImgAxis(int _nStart, int _nDiv);

protected:
	/**
	 * @brief スライダー描画
	 */
	virtual	void 	paintEvent ( QPaintEvent * event )		override;

	/**
	 * @brief マウス移動フラグ<br>
	 * true:スライダー移動中、false:スライダー停止中
	 */
	bool bMouse;
	
	/**
	 * @brief マウスプレスイベントハンドラ
	 */
	virtual void mousePressEvent(QMouseEvent *evt)	override;
	
	/**
	 * @brief マウス移動イベントハンドラ
	 */
	virtual void mouseMoveEvent(QMouseEvent *evt)	override;
	
	/**
	 * @brief マウスリリースイベントハンドラ
	 */
	virtual void mouseReleaseEvent(QMouseEvent *evt)	override;

private:
	/**
	 * @brief スライダー描画位置Ｘ座標
	 */
	int nDrawX;
	
	/**
	 * @brief スライダー値最小値
	 */
	int minValue;
	
	/**
	 * @brief スライダー値最大値
	 */
	int maxValue;
	
	/**
	 * @brief スライダー値
	 */
	int value;

	/**
	 * @brief 目盛り（スライダー有効範囲）と背景画像の両端との距離(ピクセル）
	 */
	int nSideDiv;
	
	/**
	 * @brief 背景画像の左端から左端の目盛りとの距離（ピクセル）
	 */
	int nStartX;
	
	/**
	 * @brief 目盛り間の距離(ピクセル)
	 */
	int nDivX;

	/**
	 * @brief マウス移動チェック<br>
	 * マウス移動時にスライダーの目盛りの両端を越えるかどうかチェックする
	 * @param int x 移動後のマウスの位置のX座標
	 * @return bool true：範囲内、false:範囲外
	 */
	bool chkMoveSize(int x);
	
	/**
	 * @brief スライダー描画位置決定<br>
	 * スライダー値からスライダーの描画位置を決定する。
	 */
	void chgValueTick();
	
	
	/**
	 * @brief スライダー値計算<br>
	 * スライダーの描画位置からスライダー値を計算する。
	 */
	void calcValueTick();

signals:
	void valueChanged();
};

#endif // MTIMAGESLIDER_H
