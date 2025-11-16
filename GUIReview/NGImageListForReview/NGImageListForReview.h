#ifndef NGIMAGELISTFORREVIEW_H
#define NGIMAGELISTFORREVIEW_H

#include "NGImageListForReview_global.h"
#include <QTextStream.h>
#include "ui_NGImageListForm.h"
//#include "SettingDialog.h"

#include "XDLLOnly.h"

#include "ReviewStructureItems.h"
#include "../ControlInfoDialog.h"
#include "XReviewPropertyBase.h"

// プロパティ宣言開始

class NGImageListForReview;

template<>
class PropertyBase<NGImageListForReview>;

typedef PropertyBase<NGImageListForReview> NGImageListForReviewProperty;

namespace Ui{
class NGImageListForReviewPropertyClass;
}
class	SignalOperandInt;
// プロパティ宣言終了

////
// NG画像単位でのリストを表示するコンポーネント
// パケット受信による更新要求からReviewStructureのリストを参照して自身のリストを更新する
class NGIMAGELISTFORREVIEW_EXPORT NGImageListForReview : public GUIFormBase
{
	Q_OBJECT

private:
	struct _reqData{
		int32 NextListDelay;
		bool WaitProgressVisible;
	};
	int FrontCount;
	int BackCount;
public:
	NGImageListForReview(LayersBase *Base,QWidget *parent);
	~NGImageListForReview();

	bool	SameWidth;
	int32	WidthXYMatrix;
	int32	WidthLibrary;
	int32	WidthCause;
	int32	WidthCount;
	int32	WidthArea;
	bool	SkipSamePiece;
	int32	WaitMilisecToChangeSurface;

public:
	// 更新要求パケットを受け取ったら、ReviewStructureにNGのリストを要求し、表示リストを更新する
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	void updateGUI();
	void refleshTableRow(int row);
	void setCurrentRow(int row);
	int currentRow();
	virtual	bool eventFilter(QObject *target, QEvent *event)	override;
	virtual	void Prepare()	override;
	int	getNextListDelay();
	int getNextListDelay(const NGNailItem &item) const;
	bool isKeyMoveEnable() const { return ui.progKeyWait->value()==ui.progKeyWait->maximum(); };
	virtual void	Terminated(void)		override;

private:
	// 表示しているリストの内容を更新する
	void setNGList(const OrganizedHistoryItem &history);
	// 表示しているウィンドウ色を変更する
	void setViewColor(const OrganizedHistoryItem &history);
	void addNGList(const HistoryItem &historyPtr, const InsLibraryHash &InsLibHashPtr=InsLibraryHash(), int InsertRow=0);
	void updateVerticalHeader(int FrontCount, int BackCount);
	// Fキーの要素をXMLに記述する.戻り値はキーに対応する色
	QColor setFKey(Review::FKey key);
	// Fキーの要素を削除する
	bool removeFKey(QColor &afterColor);
	void fillBackgraundColorOnTableAtRow(int row, QColor color);
	void setKeyPressedState(bool pressed){ keyPressed = pressed; };
	bool isKeyPressed() const { return keyPressed; };
	QColor getResultColor(const QStringList &resultList, const QColor &defaultColor=QColor(Qt::red));

	// 現在のNGを選択済みにする
	bool setCheckedCurrentNG();
	QColor getCurrentNGColor();

	void inputKeyUPArrow();
	void inputKeyDownArrow(bool Skip);
	void inputKeyRightArrow();
	void inputKeyLeftArrow();
	void inputKeyFunction(Review::FKey key);
	void inputKeyDelete();
	void inputKeyExchangeNGVisible();
	void inputKeyEnter();

	void moveHistory(Review::Direction direction);

	void startKeyWaitTimeLine(int interval);

	void setGUIEnable(bool enable);
	bool	GetAreaNameAndChecked(int row ,QString &AreaName);
	int		GetListCount(void);


private slots:
	void endKeyWaitTimeLine(int value);

protected:
	// カーソルキーや、Fキー、Fキーのクリアキーが押された時の動作
	// カーソルキーの場合左右の動作がShowHistoryListForReviewの移動コマンド送信になる。
	// setFKey() や clearFKey() が実行される
	// また、NGImageForReviewとWholeImageForReviewに更新要求が行われる
	virtual	void keyPressEvent(QKeyEvent *event)			override;
	virtual	void keyReleaseEvent(QKeyEvent *event)			override;
	virtual	void contextMenuEvent(QContextMenuEvent *event)	override;

private slots:
	// UIのリストがクリックされた時のスロット
	// クリックされた行から選択したNGNailItemを決定し、ReviewStructureへ選択状態にするように要求する
	// そのあと、NGImageForReviewとWholeImageForReviewに更新を要求する
	void cellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	//void SlotSetSortOrder();
	void SlotShowKeyAssignInfoDialog();

private:
	Ui::NGImageListClass ui;	// 表示用UI
								// 表示用QTableWidget、NG数表示QLineEdit
	QStringList mainHHeader;
	int32 NextListDelay;
	bool keyPressed;
	QPalette defPalette;

public:
	_reqData reqData;

private:
	//QAction *settingAction;
	QAction *showControlAction;
	QMenu *contextMenu;
	//SettingDialog *settingDialog;
	ControlInfoDialog *controlInfoDialog;

private:
	QString hhlNGPoint;
	QString hhlLibrary;
	QString hhlNGCause;
	QString hhlNGCount;
	QString hhlNGArea;

private:
	QTimeLine *keyWaitTimeLine;
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 開始-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// プロパティのメインバッファ(GUIに使用する情報とUiからの入出力に使用)
private:
	NGImageListForReviewProperty *m_property;

// プロパティ設定ダイアログ(外部から(*主にプロパティ設定GUI)の要求で呼び出される)
private:
	Ui::NGImageListForReviewPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// プロパティへのアクセス
public:
	inline const NGImageListForReviewProperty &getProperty() const { return *m_property; };
	NGImageListForReviewProperty *getPropertyPtr() { return m_property; }

private:// 編集可能は内部からのみ
	inline NGImageListForReviewProperty &getProperty() { return *m_property; };

// プロパティのバッファとプロパティ設定ダイアログへのアクセス関数
private:
	void setProperty(NGImageListForReviewProperty *property){ m_property = property; };
	void setPropertyUi(Ui::NGImageListForReviewPropertyClass *ui){ m_propertyUi = ui; };
	Ui::NGImageListForReviewPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// プロパティダイアログのシグナルaccepted()に対応するスロット
private slots:
	void slot_propertyModified();

// プロパティのコピーとUiファイルとの連携
public:
	void setProperty(const NGImageListForReviewProperty &property);
private:
	void setPropertyToUi(const NGImageListForReviewProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(NGImageListForReviewProperty &property);
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



#endif // NGIMAGELISTFORREVIEW_H
