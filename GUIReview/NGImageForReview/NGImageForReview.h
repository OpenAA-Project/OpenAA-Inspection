#ifndef NGIMAGEFORREVIEW_H
#define NGIMAGEFORREVIEW_H

#include <QLayout>
#include <QLabel>
#include "ngimageforreview_global.h"

#include "XDLLOnly.h"

#include "ImageDataUnit.h"

#include "XReviewCommon.h"
#include "ReviewStructureItems.h"
#include "PieceDisplay.h"

// プロパティ宣言開始
#include "XReviewPropertyBase.h"

class NGImageForReview;

template<>
class PropertyBase<NGImageForReview>;

typedef PropertyBase<NGImageForReview> NGImageForReviewProperty;

namespace Ui{
class NGImageForReviewPropertyClass;
}

// プロパティ宣言終了

class NGIMAGEFORREVIEW_EXPORT NGImageForReview : public GUIFormBase
{
	Q_OBJECT

public:
	// コンストラクタで画面の表示を整える
	NGImageForReview(LayersBase *Base,QWidget *parent);
	~NGImageForReview();

public:
	// NGとマスター画像の更新要求を受け取り、画面を更新する
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	void setOrientation(Qt::Orientation orient);// 縦か横並びの設定
	//void setMasterSide(Review::SideType side);
	void adjustImageSize(void);// NG画像サイズと表示エリアサイズからNG画像とマスター画像の大きさを調整し、NG画像のマスター画像位置の情報からマスター画像のシフト移動も行う画像全般の調整動作

	void updateGUI(void);
	virtual	void Prepare(void)	override;

private:
	// check～
	// EditGUIで変更されたプロパティに対して動的に変更するための関数
	// プロパティのパネルの数値などが変更されて決定された場合に実行される
	// 実際に実行されるのはGUIFormBaseのChangedValue()でPrepareが呼ばれ、以下の関数が呼ばれる
	void checkOrientation();

public:
	int32 reqOrientation;
	bool isMasterView;
	bool isNGImageView;

private:
	//Review::SideType	currentMasterSide;	// 現在表示中の画像サイド
	//
	//MasterImagePiece	*FrontMasterImage;	// マスター画像拡大図(表 //
	//MasterImagePiece	*BackMasterImage;	// マスター画像拡大図(裏
	//NGImagePiece		*NGNailImage;			// NG画像

	MasterPieceDisplay		MasterPImage;
	NGNailDisplay			NGNailImage;
	QLabel					MasterLabel;
	QLabel					NGNailLabel;

	QGridLayout *mainLayout;// レイアウト
	QVBoxLayout *vLayout;	// 縦並び用レイアウト
	QHBoxLayout *hLayout;	// 横並び用レイアウト

	Qt::Orientation			viewType;			// 並び方向

	NGNailItemRef NGNailInfo;

	QColor DefaultNGNailLabelWindowColor;
	QColor DefaultMasterLabelWindowColor;

public slots:
	void	ResizeAction();//ウィンドウサイズ変更時の動作

	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 開始-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// プロパティのメインバッファ(GUIに使用する情報とUiからの入出力に使用)
private:
	NGImageForReviewProperty *m_property;

// プロパティ設定ダイアログ(外部から(*主にプロパティ設定GUI)の要求で呼び出される)
private:
	Ui::NGImageForReviewPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// プロパティへのアクセス
public:
	inline const NGImageForReviewProperty &getProperty() const { return *m_property; };
	NGImageForReviewProperty *getPropertyPtr() { return m_property; }

private:// 編集可能は内部からのみ
	inline NGImageForReviewProperty &getProperty() { return *m_property; };

// プロパティのバッファとプロパティ設定ダイアログへのアクセス関数
private:
	void setProperty(NGImageForReviewProperty *property){ m_property = property; };
	void setPropertyUi(Ui::NGImageForReviewPropertyClass *ui){ m_propertyUi = ui; };
	Ui::NGImageForReviewPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// プロパティダイアログのシグナルaccepted()に対応するスロット
private slots:
	void slot_propertyModified();

// プロパティのコピーとUiファイルとの連携
public:
	void setProperty(const NGImageForReviewProperty &property);
private:
	void setPropertyToUi(const NGImageForReviewProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(NGImageForReviewProperty &property);
	void setPropertyFromUi();

// コンストラクタで使用するプロパティの初期化
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 終了-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
};

#endif // NGIMAGEFORREVIEW_H
