#ifndef SHOWTHUMBNAIL_H
#define SHOWTHUMBNAIL_H

#include "showthumbnail_global.h"
#include "XDLLOnly.h"

#include "XReviewStructure.h"

#include "Thumbnail.h"
#include "ThumbnailPage.h"
#include "ExpandThumbnailForm.h"
#include "SettingDialog.h"
#include "XReviewCommon.h"
#include "../XGUIReviewGlobal.h"

#include "../ControlInfoDialog.h"

#include <QStackedWidget>
#include <QDesktopWidget>
#include <QProgressBar>
#include <QAction>
#include <QMenu>
#include <QLabel>
#include <QTimeLine>
#include <QLabel>

// プロパティ宣言開始
#include "XReviewPropertyBase.h"

class	ShowThumbnail;
class	ControlInfoDialog;

template<>
class PropertyBase<ShowThumbnail>;

typedef PropertyBase<ShowThumbnail> ShowThumbnailProperty;

namespace Ui{
class ShowThumbnailPropertyClass;
}

// プロパティ宣言終了

// サムネイル表示コンポーネント本体
// NGImageListForReviewに取って代わることを前提とする
// これを使用することによりNGImageForReviewが必要無くなるかは不明
// 機能として、ShowHistoryListForReviewからNGリストの送信によりサムネイル表示を行う
// カーソルキーで注目画像を移動し、クリックしたNG画像を選択状態にする
// 選択状態になったNG画像はNGImageForReviewに表示され(準拡大画像扱い？)る。
// サムネイルページの最初のページの最初の列から↑カーソルで前の基板へ、最後のページの下が無い列で↓カーソルで次の基板へ
// 基本は→カーソルキーで順次NG画像が送られ、移動順はラスタ順となる。←カーソルはその逆である。
class SHOWTHUMBNAIL_EXPORT ShowThumbnail : public GUIFormBase
{
	Q_OBJECT

public:
	ShowThumbnail(LayersBase *Base,QWidget *parent);
	~ShowThumbnail();

public:
	enum _moveMode{
		PerThumbnail,
		PerPage
	};
	bool	SkipSamePiece;
	//bool	ModeShowPageByPiece;
public:
	virtual void	Prepare(void)	override;
	
	// ・NGListの更新
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	void updateGUI();
	void updateInfoLabel();
	//void updateHelpLabel();

protected:
	// 上下左右イベント
	virtual	void keyPressEvent(QKeyEvent *event)	override;
	virtual	void keyReleaseEvent(QKeyEvent *event)	override;

private:
	void updateThumbnailList();
	void setThumbnailList(OrganizedHistoryIndex orgHistoryPtr);
	void clearThumbnailList();
	void showThumbnail();
	void createThumbnailBook();
	void createThumbnailPageList();
	void createThumbnailPageListByPiece();
	void createEditerThumbnail();
	QImage createEditerImage(int width, int height, QColor backgroundColor, Review::FKey key);
	void updateFKeyColorList();
	// ページ番号[page]のlocateに移動、locate==Review::Manualの場合はrow,columnを使用
	void showPage(Review::SideType side, int page, Review::ListLocate, int row=-1, int column=-1);// 全指定
	void showPage(Review::SideType side, Review::ListLocate locate);// 表裏と先頭末尾指定
	void showPage(Review::ListLocate locate, int GlobalIndex=-1);// 全NGリストのインデックス指定
	int getLocalIndex(int page, int row, int column, Review::SideType side) const;
	int getGlobalIndex(int page, int row, int column, Review::SideType side) const;

	int calcPage(int localIndex) const;

	// 矢印キーによる移動の変更
	void inputKeyMoveModeChange();

	// 矢印キーによる移動
	void inputKeyUpArrow();
	void inputKeyDownArrow(bool Skip);
	void inputKeyRightArrow(bool Skip);
	void inputKeyLeftArrow();
	void inputKeyFunction(Review::FKey key);
	void inputKeyDelete();
	bool	GetAreaNameAndChecked(int GlobalIndex ,QString &AreaName);

	// Fキーの要素をXMLに記述する.戻り値はキーに対応する色
public:
	QColor setFKey(Review::FKey key);
	// Fキーの要素を削除する
	bool removeFKey(QColor &afterColor);
private:
	bool isMoveHistoryEnable();
	bool moveHistory(Review::Direction direction/*移動する方向:前・後ろ*/, Review::ListLocate NGLocate/* NGNailの位置 */, bool *historyExisted=NULL);

	ThumbnailList *currentThumbnailList();
	ThumbnailPageList *currentThumbnailPageList();

	bool isCurrentPageAllChecked();
	bool isPageAllChecked(int GlobalPage);
	bool isPageAllChecked(Review::SideType side, int LocalPage);
	bool isCurrentHistoryAllChecked();

private:// currentXXXを直接変更する関数
	bool setCurrentNG(Review::SideType side, int page, int row, int column);

protected:
	virtual	void paintEvent(QPaintEvent *event)				override;
	virtual	void contextMenuEvent(QContextMenuEvent *event)	override;
	virtual	void mousePressEvent(QMouseEvent *event)		override;

private:
	void setRowCount(int size);
	void setColumnCount(int size);
	void setNGSignSize(int size);
	void setViewMaster(bool view);
	void setCurrentSide(Review::SideType side);
	void setCurrentPage(int page);
	void setCurrentRow(int row);
	void setCurrentColumn(int column);
	void setCurrentThumbnail(Thumbnail *thumbnail);
	void setMoveMode(_moveMode mode);
	void setExpandThumbnail(Thumbnail *thumbnail);
	void setExpandThumbnailVisible(bool v);
	void setMoveDelay(int miliSec);
	void setKeyPressedState(bool pressed);
	void setEnableExpandThumbnal(bool enable);
	void setModeShowPageByPiece (bool enable);
	void setFKeyList(const QList<QColor> &list);
	void setCurrentEID(int id);

public:
	int getRowCount() const;
	int getColumnCount() const;
	int getNGSignSize() const;
	bool isViewMaster() const;
	Review::SideType getCurrentSide() const;
	int getCurrentPage() const;
	int getCurrentRow() const;
	int getCurrentColumn() const;

	Thumbnail *getCurrentThumbnail() const;
	Thumbnail *getThumbnail(Review::SideType side, int page, int row, int column);
	Thumbnail *getThumbnail(Review::SideType side, int LocalIndex);
	Thumbnail *getThumbnail(int GlobalIndex);
private:
	int getThumbnailCount(Review::SideType side) const;
	int getThumbnailCountAll() const;
	int getCurrentThumbnailCount() const;
	int getCurrentThumbnailTotalNumb() const;
	_moveMode getMoveMode() const;
	int getThumbnailCountInPage() const;
	Thumbnail *getExpandThumbnail() const;
	bool getExpandThumbnailVisible() const;
	bool isEnableExpandThumbnal() const;
	bool isModeShowPageByPiece () const;
	int getCurrentEID() const;

	ThumbnailList &getThumbnailList(Review::SideType side);
	const ThumbnailList &getThumbnailList(Review::SideType side) const;
	ThumbnailPageList &getThumbnailPageList(Review::SideType side);
	const ThumbnailPageList &getThumbnailPageList(Review::SideType side) const;
	ThumbnailList &getCurrentThumbnailList();
	const ThumbnailList &getCurrentThumbnailList() const;
	ThumbnailPageList &getCurrentThumbnailPageList();
	const ThumbnailPageList &getCurrentThumbnailPageList() const;

	int getPageCount(Review::SideType side);
	int getCurrentPageCount();
	int getCurrentPageLastIndex();
	int getCurrentThumbnailCountInLastPage();
	int getLastRow(Review::SideType side);
	int getLastColumn(Review::SideType side);
	int getCurrentLastRow();
	int getCurrentLastColumn();
	int getCurrentThumbnailLastGlobalIndex();
	int getMoveDelay();
	int getPageDelay(const ThumbnailPage *pageWidget);
	bool isKeyPressed() const;
	bool existCurrentThumbnail() const;
	void startPageWaitTimeLine(int interval);

public slots:
	void ResizeAction();
	void slotSetCurrentThumbnail(Thumbnail *thumbnail);

private:
	//struct _reqData{
	//	int32 rowCount;
	//	int32 columnCount;
	//	int32 NGSignSize;
	//	int32 viewMaster;
	//	int32 delayMSec;
	//	int32 moveMode;
	//	bool enableExpandDialog;
	//};

private:
	// EditGUIで指定することが出来る縦横の表示数の最大値
	//int rowCount;		// 縦列最大値
	//int columnCount;	// 横列最大値
	//int NGSignSize; // NG描画サイズ
	//bool viewMaster;// マスター画像を表示するかどうか
	//bool enableExpandThumbnal;// 拡大サムネイル有効判定

	QList<QColor> m_FKeyColorList;

	Review::SideType m_currentSide;// 現在表示中のサイド Front or Back
	int m_currentPage;// 現在表示中のページ。１ページ中に最大 rowMax * columnMax のNG画像が表示される
	int m_currentRow;		// 非選択状態では-1(NG画像無しなど)
	int m_currentColumn;	// 非選択状態では-1(NG画像無しなど)
	Thumbnail *m_currentThumbnail;// 現在選択中のNG画像

	int m_delayMSec;

	ThumbnailList m_FrontThumbnailList;	// 全サムネイルアイテムのリストバッファ(表)
	ThumbnailList m_BackThumbnailList;		// 全サムネイルアイテムのリストバッファ(裏)

	ThumbnailPageList m_FrontThumbnailPageList;	// 表側ページリスト
	ThumbnailPageList m_BackThumbnailPageList;	// 裏側ページリスト

	_moveMode m_moveMode;

	//QVector<QGridLayout*> pageLayouts;
	//QGridLayout *mainLayout;
	
	//QWidget		*layoutWidget;

	QStackedWidget *m_ThumbnailBook;
	QLabel *m_InfoLabel;
	//QLabel *HelpLabel;
	QVBoxLayout *m_mainLayout;

	int m_currentEID;
	bool m_keyPressed;
	bool m_drawNGSingEnable;

protected:
	void setFKeyColorList(const QList<QColor> &list){ m_FKeyColorList = list; Review::resize(13, m_FKeyColorList); };

	QList<QColor> getFKeyColorList() const { return m_FKeyColorList; };
	//Review::SideType currentSide() const { return m_currentSide; };
	//int currentPage() const { return m_currentPage; };
	//int currentRow() const { return m_currentRow; };
	//int currentColumn() const { return m_currentColumn; };
	//Thumbnail *currentThumbnail() const { return m_currentThumbnail; };
	int delayMSec() const { return m_delayMSec; };

protected:
	void setThumbnailBook(QStackedWidget *book){ m_ThumbnailBook = book; };
	void clearThumbnailBook(){ if(m_ThumbnailBook!=NULL)delete m_ThumbnailBook; m_ThumbnailBook = NULL; };

	QStackedWidget *thumbnailBook() const { return m_ThumbnailBook; };
	QLabel *infoLabel() const { return m_InfoLabel; };
	QVBoxLayout *mainLayout() const { return m_mainLayout; };

private:
	QAction *m_settingAction;
	QMenu *m_contextMenu;
	SettingDialog *m_settingDialog;
	ControlInfoDialog *m_controlInfoDialog;
	QAction *m_controlInfoAction;
	QProgressBar *m_pageWaitProgressBar;
	QLabel		*LabelInfo;
	QTimeLine *m_pageWaitTimeLine;

	ExpandThumbnailDialog *m_ExpandDialog;

protected:
	QAction *settingAction() const { return m_settingAction; };
	QMenu *contextMenu() const { return m_contextMenu; };
	SettingDialog *settingDialog() const { return m_settingDialog; };
	ControlInfoDialog *controlInfoDialog() const { return m_controlInfoDialog; };
	QAction *controlInfoAction() const { return m_controlInfoAction; };
	QProgressBar *pageWaitProgressBar() const { return m_pageWaitProgressBar; };
	QTimeLine *pageWaitTimeLine() const { return m_pageWaitTimeLine; };
	ExpandThumbnailDialog *expandDialog() const { return m_ExpandDialog; };

	void setSettingDialog(SettingDialog *dialog){ m_settingDialog = dialog; };

private slots:
	void showSettingDialog();
	void changedRowColumnCount(int rowCount, int columnCount);
	void changedNGSignSize(int size);
	void slotSetMasterVisible(int state);
	void slotSortOrderChanged(int index);
	
// プロパティのメインバッファ(GUIに使用する情報とUiからの入出力に使用)
private:
	ShowThumbnailProperty *m_property;

// プロパティ設定ダイアログ(外部から(*主にプロパティ設定GUI)の要求で呼び出される)
private:
	Ui::ShowThumbnailPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// プロパティへのアクセス
public:
	inline const ShowThumbnailProperty &getProperty() const { return *m_property; };
	ShowThumbnailProperty *getPropertyPtr() { return m_property; }

	ReviewPIBase *GetReviewBase(void);
	void	ShowLabelInfo(const QString &Message);
	void	SetFKeyIndex(int GlobalIndex ,Review::FKey key);
private:// 編集可能は内部からのみ
	inline ShowThumbnailProperty &getProperty() { return *m_property; };

// プロパティのバッファとプロパティ設定ダイアログへのアクセス関数
private:
	void setProperty(ShowThumbnailProperty *property){ m_property = property; };
	void setPropertyUi(Ui::ShowThumbnailPropertyClass *ui){ m_propertyUi = ui; };
	Ui::ShowThumbnailPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// プロパティダイアログのシグナルaccepted()に対応するスロット
private slots:
	void slot_propertyModified();
    void on_pushButtonColorNoChecked_clicked();
    void on_pushButtonColorChecked_clicked();
    void on_pushButtonColorF1_clicked();
    void on_pushButtonColorF2_clicked();
    void on_pushButtonColorF3_clicked();
    void on_pushButtonColorF4_clicked();
    void on_pushButtonColorF5_clicked();
    void on_pushButtonColorF6_clicked();
    void on_pushButtonColorF7_clicked();
    void on_pushButtonColorF8_clicked();
    void on_pushButtonColorF9_clicked();
    void on_pushButtonColorF10_clicked();
    void on_pushButtonColorF11_clicked();
    void on_pushButtonColorF12_clicked();
// プロパティのコピーとUiファイルとの連携
public:
	void setProperty(const ShowThumbnailProperty &property);
private:
	void setPropertyToUi(const ShowThumbnailProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(ShowThumbnailProperty &property);
	void setPropertyFromUi();

// コンストラクタで使用するプロパティの初期化
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
};

#endif // SHOWTHUMBNAIL_H
