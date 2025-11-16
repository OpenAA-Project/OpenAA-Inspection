#include "ListMasterDataAndLoadResource.h"
#include "ListMaster.h"
#include "XDataInLayer.h"
#include "XReviewStructure.h"
#include "XDataAlgorithm.h"
#include "XGeneralFunc.h"

#include "LoadMasterDataWindow.h"
#include "ListMasterDataAndLoadPacket.h"

#include "XGeneralDialog.h"
#include "XGUI.h"

#include "..\XGUICmdReviewCommon.h"

#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "../SelectLotForReview/SelectLotForReviewPacket.h"
#include "../WholeImageForReview/WholeImageForReview.h"

#include "../WholeImageForReview/WholeImageForReviewPacket.h"
#include "XSequenceRepairLocal.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QScrollBar>

extern	char	*sRoot;
extern	char	*sName;

class ListMasterForm::ListMasterLocker : public GUILockerBase
{
public:
	ListMasterLocker(Ui::ListMasterFormClass *_ui, QWidget *updateWidget=NULL){
		ui = _ui;
		stack++;
		if(updateWidget!=NULL){
			updateWidget->update();
			qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		setGUIEnable(false);
	};
	~ListMasterLocker(){
		stack--;
		if(stack==0){
			setGUIEnable(true);
		}
	};
public:
	void setGUIEnable(bool enable){
		if(ui!=NULL){
			ui->pbSelect->setEnabled(enable);
			ui->pushButtonOpneInDetail->setEnabled(enable);
			ui->tbDataTable->setEnabled(enable);
			//ui->pbUpdate->setEnabled(enable);
		}
	};

private:
	Ui::ListMasterFormClass *ui;

	static int stack;
};

int ListMasterForm::ListMasterLocker::stack = 0;


ListMasterForm::ListMasterForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	setFrameStyle(QFrame::WinPanel | QFrame::Raised);
	setLineWidth(2);
	LangSolver.SetUI(this);
	
	WidthID		=48;
	WidthName	=100;
	WidthLatest	=100;
	SameWidth	=true;

	ListMasterLocker locker(&ui);

	// テーブル名
	//MasterTableName = /**/"MASTERDATA";

	// データベースの名前と表示ラベルの対応
	hHeaderRaw	<< /**/"MASTERCODE" << /**/"MASTERNAME" << /**/"LASTEDITTIME";
	hHeaderView	<< LangSolver.GetString(ListMaster_LS,LID_0)/*"ID"*/			<< LangSolver.GetString(ListMaster_LS,LID_1)/*"Name"*/		<< LangSolver.GetString(ListMaster_LS,LID_2)/*"LatestEdition"*/;

	// 選択モードの設定
	ui.tbDataTable->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tbDataTable->setSelectionBehavior(QAbstractItemView::SelectRows);

	ui.tbDataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	
	// 表示
	if(GetEditMode()==false){
		ShowList();

		connect(ui.pushButtonOpneInDetail, SIGNAL(clicked()), this, SLOT(ShowLoadMasterDataWindow()));
		connect(ui.tbDataTable, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(SlotDoubleClicked(const QModelIndex &)));
		connect(ui.pbSelect, SIGNAL(clicked()), this, SLOT(SlotSelectButtonClicked()));
	}
}

void	ListMasterForm::Prepare(void)
{
	if(SameWidth==false){
		ui.tbDataTable	->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Fixed);
		ui.tbDataTable	->setColumnWidth(0,WidthID);
		ui.tbDataTable	->setColumnWidth(1,WidthName);
		ui.tbDataTable	->setColumnWidth(2,WidthLatest);
	}
}
void ListMasterForm::SlotSelectButtonClicked()
{
	if(ui.tbDataTable->currentItem()!=NULL){
		ListMasterLocker locker(&ui, this);
		qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		SlotDoubleClicked(ui.tbDataTable->currentIndex());
	}
}

void ListMasterForm::SlotUpdateButtonClicked()
{
	ListMasterLocker locker(&ui, this);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
	ShowList();
}

bool ListMasterForm::LoadMasterData(int SelectedMasterCode)
{
	SeqControlParam	*Param=NULL;
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			Param	->MasterID	=SelectedMasterCode;
		}
	}

	GetLayersBase()->SetMasterCode(SelectedMasterCode);
	ListMasterLocker locker(&ui, this);
	ReviewPIBase *RBase = GetReviewAlgorithm();

	CmdLoadMaster cmdLoadMaster(GetLayersBase());
	cmdLoadMaster.MasterCode = SelectedMasterCode;
	RBase->TransmitDirectly( &cmdLoadMaster );

	GUIFormBase *WForm = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::WholeImageForReview, /**/"");

	if(WForm!=NULL){
		GUICmdLoadMasterImage WholeMLoadCmd(GetLayersBase());

		WholeMLoadCmd.side = Review::Front;
		WForm->TransmitDirectly(&WholeMLoadCmd);

		WholeMLoadCmd.side = Review::Back;
		WForm->TransmitDirectly(&WholeMLoadCmd);
	}

	ReviewGUI::ReviewGUIAllUpdate(GetLayersBase(), true);

	GUIFormBase *NGLForm = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::NGImageListForReview, /**/"");
	if(NGLForm!=NULL){
		GUICmdSetFocus SetFocusCmd(GetLayersBase());

		NGLForm->TransmitDirectly(&SetFocusCmd);
	}else{
		GUIFormBase *TForm = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::ShowThumbnail,/**/"");
		if(TForm!=NULL){
			GUICmdSetFocus SetFocusCmd(GetLayersBase());
			TForm->TransmitDirectly(&SetFocusCmd);
		}
	}
	
	ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::WholeImageForReview);

	ExecuteInitialAfterEditInfo EInfo;
	GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
	#ifdef _MSC_VER
	_CrtCheckMemory();
	#endif
	
	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());

	GetLayersBase()->CloseInformed();

	return true;
}

void ListMasterForm::ShowList()
{
	if(GetEditMode()==true)return;

	ListMasterLocker locker(&ui);
	ui.tbDataTable->setRowCount(0);
	ui.tbDataTable->setColumnCount(hHeaderView.count());
	QSqlQuery query( GetLayersBase()->GetDatabase() );
	if(query.exec(/**/"select MACHINEID from MACHINE ORDER BY MACHINEID")==false){
		while(query.next()){
			int id = query.record().value(0).toInt();
			if(MachineIDFilter.contains(id)==false){
				MachineIDFilter.removeAll(id);
			}
		}
	}

	if(MachineIDFilter.isEmpty()==true){
		if(query.exec(/**/"SELECT MASTERCODE,MASTERNAME,LASTEDITTIME FROM MASTERDATA ORDER BY MASTERCODE")==false){
			return;
		}
	}else{
		QStringList MachineOrderList;
		for(int i=0; i<MachineIDFilter.count(); i++){
			MachineOrderList << QString(/**/"MACHINEID=%1").arg(MachineIDFilter[i]);
		}
		QString filterStr = MachineOrderList.join(/**/" OR ");
		QString queryStr = QString(/**/"SELECT MASTERCODE,MASTERNAME,LASTEDITTIME FROM MASTERDATA WHERE %1 ORDER BY MASTERCODE").arg(filterStr);
		if(query.exec(queryStr)==false){
			return;
		}
	}

	ui.tbDataTable->setHorizontalHeaderLabels(hHeaderView);

	for(int row=0; query.next(); row++){
		ui.tbDataTable->insertRow(row);
		QStringList list;
		QList<QPoint> pList;
		for(int i=0; i<hHeaderRaw.count(); i++){
			QString currentStr = hHeaderRaw[i];
			int recordIndex = query.record().indexOf(currentStr);
			QString viewTable = query.value(recordIndex).toString();

			QTableWidgetItem *item = new QTableWidgetItem();
			item->setText(viewTable);
			ui.tbDataTable->setItem(row, i, item);

			pList << QPoint(row, i);
			list << viewTable;
		}
		//qDebug() << pList;
		//qDebug() << list;
	}
	
	ui.tbDataTable->verticalHeader()->setHidden(true);
	//ui.tbDataTable->sortByColumn(0, Qt::SortOrder::DescendingOrder);
}

void ListMasterForm::SlotDoubleClicked(const QModelIndex &index)
{
	ListMasterLocker locker(&ui, this);
	int MasterCode = ui.tbDataTable->item(index.row(), 0)->text().toInt();// マスターコード

	// マスターデータの読み込み
	LoadMasterData(MasterCode);

	// 読み込んだマスターコードへカレントセルを移動
	MoveCellToMasterCode(MasterCode);

	GUICmdLoadMasterImage Cmd(GetLayersBase());
	Cmd.side = Review::Front;
	ReviewGUI::ReviewGUICmdSend(GetLayersBase(), &Cmd, ReviewGUI::Name::WholeImageForReview);
	Cmd.side = Review::Back;
	ReviewGUI::ReviewGUICmdSend(GetLayersBase(), &Cmd, ReviewGUI::Name::WholeImageForReview);
}

void ListMasterForm::ShowSelectLot(int MasterCode, int MachineID, Review::SideType side)
{
	ListMasterLocker locker(&ui);
	// アルゴリズムにマスターコードに該当するロットの一覧を要求
	ReviewPIBase *Base = GetReviewAlgorithm();
	CmdServerSelectLotList Send(GetLayersBase());

	Send.MasterCode = MasterCode;
	Send.MachineID = MachineID;
	
	Base->TransmitDirectly(&Send);

	if(Send.Ret==false){
		return;
	}
	if(Send.list.count()==0)return;

	// ロット名(ファイル名)を抜き出し
	GUICmdReviewLotList GUISend(GetLayersBase());
	GUISend.lotList = Send.list;

	// マスターコード、マシンIDと裏表をセット
	GUISend.MasterCode = MasterCode;
	GUISend.MachineID = MachineID;
	GUISend.side = side;

	// SelectLotForReviewのGUIを検索、あればそれに情報を送信。なければGUIのDLLから直接起動。DLLが無ければそこで終了。
	GUIFormBase *TagGUI = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::SelectLotForReview, /**/"");
	if(TagGUI!=NULL){
		TagGUI->TransmitDirectly(&GUISend);
	}else{
	}
}

void ListMasterForm::ShowSelectLot()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	GUIFormBase *Base = GetReviewGUIForm(ReviewGUI::Name::SelectLotForReview);
	if(Base==NULL)return;

	CmdUpdateLotInfoList doUpdateLotInfo(GetLayersBase());
	RBase->TransmitDirectly(&doUpdateLotInfo);

	CmdReqCurrentLotAllList reqLotList(GetLayersBase());
	RBase->TransmitDirectly(&reqLotList);

	CmdReqMasterDataInfo reqMasterInfo(GetLayersBase());
	RBase->TransmitDirectly(&reqMasterInfo);

	// 表 //
	// ロット名(ファイル名)を抜き出し
	GUICmdReviewLotList GUISend(GetLayersBase());
	GUISend.lotList = reqLotList.FrontLotList;

	// マスターコード、マシンIDと裏表をセット
	GUISend.MasterCode = reqMasterInfo.FrontMasterDataInfo.MasterCode;
	GUISend.MachineID = reqMasterInfo.FrontMasterDataInfo.MachineID;
	GUISend.side = Review::Front;
	
	// 送信
	Base->TransmitDirectly(&GUISend);

	// 裏
	// ロット名(ファイル名)を抜き出し
	GUISend.lotList = reqLotList.BackLotList;

	// マスターコード、マシンIDと裏表をセット
	GUISend.MasterCode = reqMasterInfo.BackMasterDataInfo.MasterCode;
	GUISend.MachineID = reqMasterInfo.BackMasterDataInfo.MachineID;
	GUISend.side = Review::Back;

	// 送信
	Base->TransmitDirectly(&GUISend);

}

void ListMasterForm::MoveCellToMasterCode(int MasterCode)
{
	ListMasterLocker locker(&ui);
	// リストの同マスターコードの行を選択する
	// リストの全行数とマスターコードの列を取得
	int rowMax = ui.tbDataTable->rowCount();
	int CodeIndex = hHeaderRaw.indexOf(/**/"MASTERCODE");

	// 読み込んだマスターコードを検索して選択状態にする
	QList<QTableWidgetItem *> pItems = ui.tbDataTable->findItems(QString::number(MasterCode), Qt::MatchExactly);
	if(pItems.size()==0)return;
	ui.tbDataTable->setCurrentItem(pItems.first());
	ui.tbDataTable->verticalScrollBar()->setValue(pItems.first()->row());
}

void ListMasterForm::ShowLoadMasterDataWindow()
{
	ListMasterLocker locker(&ui);
	// マスター選択フォーム表示
	LoadMasterDataWindow *form = new LoadMasterDataWindow(GetLayersBase(), sRoot, sName, this);
	GeneralDialog *D = new GeneralDialog(GetLayersBase(), form, this);
	
	// 実行
	D->exec();

	// Loadチェック
	if(form->isAccepted()==false){
		delete form;
		delete D;
		return;
	}

	int		MasterCode	= form->SelectedMasterCode;// マスターコード
	int		MachineID	= form->currentMachineID();// マシンID
	
	delete form;
	delete D;

	//// 表か裏かの問いかけ
	//Review::SideType side = Review::ShowMessageFrontOrBack();

	//// フェイズコード(Front:0 or Back:1)
	//SendData.PhaseCode = 0;// とりあえず表 //

	// マスターデータの読み込み
	LoadMasterData(MasterCode);

	// 読み込んだマスターコードへカレントセルを移動
	MoveCellToMasterCode(MasterCode);

	ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::WholeImageForReview);
}

void ListMasterForm::updateGUI()
{
	ListMasterLocker locker(&ui);
	//ShowList();
}

void ListMasterForm::setGUIEnable(bool enable)
{
	ui.pbSelect->setEnabled(enable);
	ui.pushButtonOpneInDetail->setEnabled(enable);
	ui.tbDataTable->setEnabled(enable);
}

//=======================================================================================================