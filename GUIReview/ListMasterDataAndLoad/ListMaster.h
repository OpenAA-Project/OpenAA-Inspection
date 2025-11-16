#ifndef LISTMASTERFORM_H
#define LISTMASTERFORM_H

#include <QWidget>
#include <QThread>
#include <QComboBox>
#include <QScrollArea>
#include <QSqlTableModel>
#include "ui_ListMaster.h"
#include "XGUIFormBase.h"
#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"
#include "XReviewCommon.h"

// リストを表示するメインフォーム
class ListMasterForm : public GUIFormBase
{
	Q_OBJECT

public:
	ListMasterForm(LayersBase *Base ,QWidget *parent = 0);

	int		WidthID;
	int		WidthName;
	int		WidthLatest;
	bool	SameWidth;
	
	virtual	void	Prepare(void)	override;

public:
	void updateGUI();// リストの更新
	void setGUIEnable(bool enable);// 有効化無効化
	void setMachineIDFilter(const QList<int> &machineIDFilter){
		if(MachineIDFilter!=machineIDFilter){
			MachineIDFilter = machineIDFilter;
			ShowList();
		}
	};

private:
	Ui::ListMasterFormClass ui;	// UI
	QStringList	hHeaderView;	// リストの横方向ヘッダー
	QStringList hHeaderRaw;		// リストの縦方向ヘッダー
	QList<int> MachineIDFilter;

	// マスターデータの読み込み関数
	bool	LoadMasterData(int SelectedMasterCode);

	// マスターデータの一覧表示
	void	ShowList();

	// ロット読み込み
	void	ShowSelectLot(int MasterCode, int MachineID, Review::SideType side);
	void	ShowSelectLot();

	// マスターコードの位置にカレントセルを移動
	void	MoveCellToMasterCode(int MasterCode);

	class ListMasterLocker;
private slots:
	// マスターデータの詳細な選択画面を表示する
	void	ShowLoadMasterDataWindow();
	// リストをダブルクリックした場合のマスターデータ読み込み動作
	void	SlotDoubleClicked(const QModelIndex &index);
	// 選択ボタンをクリックしたときの動作
	void	SlotSelectButtonClicked();
	// 更新ボタンをクリックしたときの動作
	void	SlotUpdateButtonClicked();
};

#endif // PROPERTYREALTIMEGRAPHFORM_H
