#ifndef MTIMAGESLIDERBASE_H
#define MTIMAGESLIDERBASE_H

#include <QWidget>
#include <QImage>

#include "XFlexArea.h"
#include "XYCross.h"
#include "XDataInLayer.h"
#include "NList.h"

/**
 * @brief 画像スライダー基底クラス
 * 
 * 画像スライダーの基本処理を行う。
 */
class mtImageSliderBase {
public:
	mtImageSliderBase();
	~mtImageSliderBase();

protected:
	/**
	 * @brief スライダー画像
	 */
	QImage imgSld;
	
	/**
	 * @brief 背景画像
	 */
	QImage imgBack;
	
	/**
	 * @brief 描画用背景画像
	 */
	QImage imgDrawBack;
	
	/**
	 * @brief 描画用スライダー画像
	 */
	QImage imgDrawSld;

	/**
	 * @brief 画像描画変換<br>
	 * 背景画像およびスライダー画像の背景部分に透過処理を行いそれぞれの描画用画像を作成する。
	 */
	void setImage();

	/**
	 * @brief 背景画像フレックスエリア
	 */
	PureFlexAreaListContainer fAreaList;
	
	/**
	 * @brief 背景画像選択エリア
	 */
	XYClassCluster xyArea;

	/**
	 * @brief 背景画像２値化<br>
	 * 背景画像を２値化し、透過部分を検出する。
	 */
	bool calcThresholdBack();
	
	/**
	 * @brief 背景画像透過チェック<br>
	 * 指定された座標が背景画像の透過になる箇所かチェックする。
	 * @param int x
	 * @param int y
	 */
	bool chkBit(int x, int y);

	/**
	 * @brief スライダー画像フレックスエリア
	 */
	PureFlexAreaListContainer fAreaListSld;

	/**
	 * @brief スライダー画像選択エリア
	 */
	XYClassCluster xyAreaSld;

	/**
	 * @brief スライダー画像２値化<br>
	 * スライダー画像を２値化し、透過部分を検出する。
	 */
	bool calcThresholdSld();

	/**
	 * @brief スライダー画像透過チェック<br>
	 * 指定された座標がスライダー画像の透過になる箇所かチェックする。
	 * @param int x
	 * @param int y
	 */
	bool chkBitSld(int x, int y);

private:
};

#endif // MTIMAGESLIDERBASE_H
