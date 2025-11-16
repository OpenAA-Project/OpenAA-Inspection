#ifndef SHOWHIERARCHYFORREVIEW_H
#define SHOWHIERARCHYFORREVIEW_H

#include "ShowHistoryListForReview_global.h"

#include "ui_HistoryListForm.h"
#include "ui_SettingDialog.h"
#include "HistoryListErrorDialog.h"
#include "XReviewStructure.h"

#include "XDLLOnly.h"

// プロパティ宣言開始

class ShowHistoryListForReview;

template<>
class PropertyBase<ShowHistoryListForReview>;

typedef PropertyBase<ShowHistoryListForReview> ShowHistoryListForReviewProperty;

namespace Ui{
class ShowHistoryListForReviewPropertyClass;
}

// プロパティ宣言終了

class SHOWHISTORYLISTFORREVIEW_EXPORT ShowHistoryListForReview : public GUIFormBase
{
	Q_OBJECT

public:
	ShowHistoryListForReview(LayersBase *Base,QWidget *parent);
	~ShowHistoryListForReview();

	int		Width1;
	int		Width2;
	int		Width3;
	int		Width4;
	bool	SameWidth;
	
	virtual	void	Prepare(void)	override;

public:
	class TableData{
	public:
		TableData():EID(-1),InspectedTime(XDateTime()),isAllChecked(false),FrontNGCount(-1),BackNGCount(-1),FrontHalt(false),BackHalt(false){};
	public:
		bool isOK() const {
			bool front_ok;
			bool back_ok;

			if(hasFront()==false){
				front_ok = true;
			}else{
				if(FrontNGCount==0){
					front_ok = true;
				}else{
					front_ok = false;
				}
			}
			if(hasBack()==false){
				back_ok = true;
			}else{
				if(BackNGCount==0){
					back_ok = true;
				}else{
					back_ok = false;
				}
			}

			return ((front_ok==true) && (back_ok==true)); 
		};
		bool hasFront() const { return FrontNGCount>=0; };
		bool hasBack() const { return BackNGCount>=0; };

	public:
		int EID;
		int		InspectedMachine;
		XDateTime InspectedTime;
		bool isAllChecked;
		int		FrontNGNailCount;
		int		FrontNGCount;
		bool	FrontHalt;
		int		BackNGNailCount;
		int		BackNGCount;
		bool	BackHalt;
		bool existFront;
		bool existBack;
	};
public:
	// ShowHistoryListForReviewの送受信
	// [Send]
	// ・NGImageListForReviewへNGリストの更新要求
	// 
	// [Recive]
	// ・履歴リストの更新
	// ・履歴リストの移動
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	
	void ShowHistoryList(OrganizedHistoryListPtr orgHistryListPtr);
	void updateGUI();
	void setGUIEnale(bool enable);
	bool isOKBoardVisible(){ return OKBoardVisible; };

protected:
	void contextMenuEvent(QContextMenuEvent *event);

private:
	void setTableRowItem(int row, TableData data,int &TopNGCount ,int &BackNGCount ,XDateTime &InspectionTime);
	int getTableIndex(int GlobalIndex);
	void createErrorDialog();

public slots:
	void ResizeAction();
	void relativeCellClicked(int currentRow, int currentColumn, int previousRow, int previousColumn);	// リストをクリックしたときの動作
								// クリックした行番号を受け取り、NGImageListForReviewに送る
	void setOKBoardVisible(bool v){ if(ui.cbOKVisible->isChecked()==v)return; ui.cbOKVisible->setChecked(v); updateTable(); };
	void updateTable();
	void reloadData();
	void stateOKViewChanged(int state);

	void showSettingDialog();
	void showErrorDialog();

	void sliderChanged(int value);

private:
	QAction *settingAction;
	QMenu *contextMenu;

private:
	Ui::HistoryListClass ui;
	HistoryListErrorDialog errorDialog;

	QStringList twHorizontalHeaderLabels;
	QString hhlInspectID;
	QString hhlInspectedTime;
	QString hhlFrontInfo;
	QString hhlBackInfo;

	bool OKBoardVisible;// OK基盤を?示するモ?ド
	QList<int> NGIndexAtTableRow;//	?示されているテ?ブルのNG行がReviewStrucrure側におけるどの履歴インデックスかを示すリスト
								//	NGIndexAtTableRow[テ?ブルの行インデックス] == OrgDataListのインデックス

	QList<TableData> OrgDataList;


/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 開始-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// プロパティのメインバッフ?(GUIに使用する情報とUiからの入出力に使用)
private:
	ShowHistoryListForReviewProperty *m_property;

// プロパティ設定?イアログ(外部から(*主にプロパティ設定GUI)の要求で呼び出される)
private:
	Ui::ShowHistoryListForReviewPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// プロパティへのアクセス
public:
	inline const ShowHistoryListForReviewProperty &getProperty() const { return *m_property; };
	ShowHistoryListForReviewProperty *getPropertyPtr() { return m_property; }

private:// 編集可?は内部からのみ
	inline ShowHistoryListForReviewProperty &getProperty() { return *m_property; };

// プロパティのバッフ?とプロパティ設定?イアログへのアクセス関数
private:
	void setProperty(ShowHistoryListForReviewProperty *property){ m_property = property; };
	void setPropertyUi(Ui::ShowHistoryListForReviewPropertyClass *ui){ m_propertyUi = ui; };
	Ui::ShowHistoryListForReviewPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// プロパティ?イアログのシグナルaccepted()に対応するスロット
private slots:
	void slot_propertyModified();

// プロパティのコピ?とUiフ?イルとの連携
public:
	void setProperty(const ShowHistoryListForReviewProperty &property);
private:
	void setPropertyToUi(const ShowHistoryListForReviewProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(ShowHistoryListForReviewProperty &property);
	void setPropertyFromUi();

// コンストラク?で使用するプロパティの初期化
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 終了-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
};

#endif // SHOWHIERARCHYFORREVIEW_H
