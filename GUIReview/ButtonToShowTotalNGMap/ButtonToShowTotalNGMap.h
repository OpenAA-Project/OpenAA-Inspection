#ifndef BUTTONTOSHOWTOTALNGMAP_H
#define BUTTONTOSHOWTOTALNGMAP_H

#include <QPushButton>

#include "TotalNGMap.h"
#include "buttontoshowtotalngmap_global.h"
#include "ui_TotalNGMapForm.h"
#include "XDLLOnly.h"
#include "ReviewStructureItems.h"
//#include "StretchImageWidget.h"

// プロパティ宣言開始
#include "XReviewPropertyBase.h"

class ButtonToShowTotalNGMap;
class ReviewPIBase;

template<>
class PropertyBase<ButtonToShowTotalNGMap>;

typedef PropertyBase<ButtonToShowTotalNGMap> ButtonToShowTotalNGMapProperty;

namespace Ui{
class ButtonToShowTotalNGMapPropertyClass;
}
// プロパティ宣言終了

// ボタンだけあるGUI
// パケットによる更新命令があるまで更新しない
// 更新命令が発生するのは以下の通り
//
//  ListMasterDataAndLoad
//    マスターデータを読み込んだとき
//  SelectLotForReview
//    ロットを選択(変更)したとき
//  
class BUTTONTOSHOWTOTALNGMAP_EXPORT ButtonToShowTotalNGMap : public GUIFormBase
{
	Q_OBJECT

public:
	ButtonToShowTotalNGMap(LayersBase *Base, QWidget *parent);
	~ButtonToShowTotalNGMap();

	virtual void	Prepare(void)	override;
public:
	// 更新要求を受け取り、m_mapを更新する
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;

public:
	void updateGUI();// ReviewStructureからデータを取得してm_mapの情報を更新する

public slots:
	// ボタンをクリックした時の動作
	void clicked(void);
	void ResizeAction(void);
	void updateMapImage();

protected:
	virtual	void paintEvent(QPaintEvent *event)	override;

private:
	QPushButton m_Btn;// m_mapを表示するボタン
	TotalNGMap m_map;// NGマップ(情報更新→表示する)初期状態で表示されていない
	//Ui::TotalNGMapClass ui;
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 開始-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// プロパティのメインバッファ(GUIに使用する情報とUiからの入出力に使用)
private:
	ButtonToShowTotalNGMapProperty *m_property;

// プロパティ設定ダイアログ(外部から(*主にプロパティ設定GUI)の要求で呼び出される)
private:
	Ui::ButtonToShowTotalNGMapPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// プロパティへのアクセス
public:
	inline const ButtonToShowTotalNGMapProperty &getProperty() const { return *m_property; };
	ButtonToShowTotalNGMapProperty *getPropertyPtr() { return m_property; }

private:// 編集可能は内部からのみ
	inline ButtonToShowTotalNGMapProperty &getProperty() { return *m_property; };

// プロパティのバッファとプロパティ設定ダイアログへのアクセス関数
private:
	void setProperty(ButtonToShowTotalNGMapProperty *property){ m_property = property; };
	void setPropertyUi(Ui::ButtonToShowTotalNGMapPropertyClass *ui){ m_propertyUi = ui; };
	Ui::ButtonToShowTotalNGMapPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// プロパティダイアログのシグナルaccepted(),rejected()に対応するスロット
private slots:
	void slot_propertyModified();
	void slot_propertyRejected();

private slots:
	void slot_tbNGColor_clicked();

// プロパティのコピーとUiファイルとの連携
public:
	void setProperty(const ButtonToShowTotalNGMapProperty &property);
private:
	void setPropertyToUi(const ButtonToShowTotalNGMapProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(ButtonToShowTotalNGMapProperty &property);
	void setPropertyFromUi();

// コンストラクタで使用するプロパティの初期化
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
};


#endif // BUTTONTOSHOWTOTALNGMAP_H
