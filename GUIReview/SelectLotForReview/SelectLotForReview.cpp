#include "SelectLotForReviewResource.h"
#include "SelectLotForReview.h"
#include "../XGUIReviewGlobal.h"
#include "XReviewCommon.h"
#include "ReviewStructurePacket.h"
#include "..\XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "XReviewCommonPacket.h"
#include "ResultLotLoadForm.h"
#include "SelectLotForReviewProperty.h"
#include "XSelectMachineForReviewPacket.h"

#include "../WholeImageForReview/WholeImageForReviewPacket.h"
#include "XSequenceRepairLocal.h"



static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"SelectLotForReview";


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Export Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show SelectLotForm");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new SelectLotForReview(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);

	Data[0].Type = /**/"bool";
	Data[0].VariableNameWithRoute=/**/"SameWidth";
	Data[0].Pointer	=&((SelectLotForReview *)Instance)->SameWidth;
	Data[1].Type = /**/"int32";
	Data[1].VariableNameWithRoute=/**/"WidthFileName";
	Data[1].Pointer	=&((SelectLotForReview *)Instance)->WidthFileName;
	Data[2].Type = /**/"int32";
	Data[2].VariableNameWithRoute=/**/"WidthLotName";
	Data[2].Pointer	=&((SelectLotForReview *)Instance)->WidthLotName;

	return(3);
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	RootNameList *item = new RootNameList(/**/"Review", /**/"ReviewStructure");
	List.AppendList(item);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SelectLotForReview.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SelectLotForReview
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SelectLotForReview::SelectLotForReviewLocker : public GUILockerBase
{
public:
	SelectLotForReviewLocker(Ui::SelectLotFormClass *_ui, QWidget *updateWidget=NULL){
		ui = _ui;
		stack++;
		if(updateWidget!=NULL){
			updateWidget->update();
			qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		setGUIEnable(false);
	};
	~SelectLotForReviewLocker(){
		stack--;
		if(stack==0){
			setGUIEnable(true);
		}
	};
public:
	void setGUIEnable(bool enable){
		if(ui!=NULL){
			ui->cancelButton->setEnabled(enable);
			ui->okButton->setEnabled(enable);
			ui->pbUpdate->setEnabled(enable);
			ui->tabWidget->setEnabled(enable);
		}
	};

private:
	Ui::SelectLotFormClass *ui;

	static int stack;
};

int SelectLotForReview::SelectLotForReviewLocker::stack = 0;

SelectLotForReview::SelectLotForReview(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent),m_FrontMasterCode(-1),m_FrontMachineID(-1),m_BackMasterCode(-1),m_BackMachineID(-1)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	SetName(sName);
	WidthFileName	=100;
	WidthLotName	=150;
	SameWidth		=true;


	SelectLotForReviewLocker locker(&ui, this);

	connect(ui.twFrontLot, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(doubleClicked(int,int)));
	connect(ui.twBackLot, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(doubleClicked(int,int)));
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));

	ui.cancelButton->setVisible(false);

	ui.twFrontLot->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);	// 横ヘッダー部が均等の幅で伸縮表示される
	ui.twBackLot->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);	// 横ヘッダー部が均等の幅で伸縮表示される

	if(GetEditMode()==false){
		ui.twFrontLot->setRowCount(0);
		ui.twBackLot->setRowCount(0);
		connect(ui.pbUpdate, SIGNAL(clicked()), this, SLOT(updateLotList()));
	}

	initProperty();
}

SelectLotForReview::~SelectLotForReview()
{

}
void SelectLotForReview::Prepare()
{
	if(SameWidth==false){
		ui.twFrontLot	->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Fixed);
		ui.twFrontLot	->setColumnWidth(0,WidthFileName);
		ui.twFrontLot	->setColumnWidth(1,WidthLotName);
		ui.twBackLot	->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Fixed);
		ui.twBackLot	->setColumnWidth(0,WidthFileName);
		ui.twBackLot	->setColumnWidth(1,WidthLotName);
	}
}

void SelectLotForReview::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		updateGUI();
		GUICmdReviewUpdateLocalVar->Ret = true;
		return;
	}
	GUICmdReviewLotList *GUICmdReviewLotListVar = dynamic_cast<GUICmdReviewLotList *>(packet);
	if(GUICmdReviewLotListVar!=NULL){
		if(GUICmdReviewLotListVar->side==Review::Front){
			m_FrontMasterCode = GUICmdReviewLotListVar->MasterCode;
			m_FrontMachineID = GUICmdReviewLotListVar->MachineID;

			if(m_FrontMasterCode==-1 || m_FrontMachineID==-1){
				ui.twFrontLot->setRowCount(0);
				GUICmdReviewLotListVar->Ret = true;
				return;
			}
		}else{
			m_BackMasterCode = GUICmdReviewLotListVar->MasterCode;
			m_BackMachineID = GUICmdReviewLotListVar->MachineID;

			if(m_BackMasterCode==-1 || m_BackMachineID==-1){
				ui.twBackLot->setRowCount(0);
				GUICmdReviewLotListVar->Ret = true;
				return;
			}
		}

		ShowLotList(GUICmdReviewLotListVar->side, GUICmdReviewLotListVar->lotList);

		GUICmdReviewLotListVar->Ret = true;
		return;
	}

	GUICmdSetCancelButtonVisible *GUICmdSetCancelButtonVisibleVar = dynamic_cast<GUICmdSetCancelButtonVisible *>(packet);
	if(GUICmdSetCancelButtonVisibleVar!=NULL){
		ui.cancelButton->setVisible(GUICmdSetCancelButtonVisibleVar->visible);
		return;
	}

	GUICmdSetEnable *GUICmdSetEnableVar = dynamic_cast<GUICmdSetEnable *>(packet);
	if(GUICmdSetEnableVar!=NULL){
		setGUIEnable(GUICmdSetEnableVar->enable);
		return;
	}
	
	ReviewCommonPacket::CmdReqSettingPropertyDialog *CmdReqSettingPropertyDialogVar = dynamic_cast<ReviewCommonPacket::CmdReqSettingPropertyDialog *>(packet);
	if(CmdReqSettingPropertyDialogVar!=NULL){
		CmdReqSettingPropertyDialogVar->setDialog(getPropertyDialog());
		CmdReqSettingPropertyDialogVar->setGroupName(ReviewGUI::PropertyGroupName::Global);
		CmdReqSettingPropertyDialogVar->setGUIName(ReviewGUI::Name::SelectLotForReview);
		return;
	}
}

void SelectLotForReview::updateLotList()
{
	SelectLotForReviewLocker locker(&ui, this);

	//QMessageBox mbox;
	//mbox.setStandardButtons(QMessageBox::StandardButton::NoButton);
	//mbox.setText("Updating Lot List");
	//mbox.setModal(true);
	//mbox.show();

	//qApp->processEvents(QEventLoop::ProcessEventsFlag::ExcludeUserInputEvents);

	ReviewPIBase *RBase = GetReviewAlgorithm();
	
	CmdServerUpdateLotList UpdateLotCmd(GetLayersBase());
	RBase->TransmitDirectly( &UpdateLotCmd );

	CmdReqMasterDataInfo LoadedMaster(GetLayersBase());
	RBase->TransmitDirectly(&LoadedMaster);

	if(LoadedMaster.FrontMasterDataInfo.MasterCode!=-1 && LoadedMaster.FrontMasterDataInfo.MachineID!=-1){
		ShowLotList(Review::Front, UpdateLotCmd.FrontLotList);
	}else{
		ShowLotList(Review::Front, LotInfoList());
	}
	if(LoadedMaster.BackMasterDataInfo.MasterCode!=-1 && LoadedMaster.BackMasterDataInfo.MachineID!=-1){
		ShowLotList(Review::Back, UpdateLotCmd.BackLotList);
	}else{
		ShowLotList(Review::Back, LotInfoList());
	}

	CmdUpdateForSaveLotList	UpdateForSaveLotCmd(GetLayersBase());
	RBase->TransmitDirectly( &UpdateForSaveLotCmd );


	//qDebug() << "[Front Lot List]";
	//qDebug() << m_FrontMasterCode << "," << m_FrontMachineID;
	//qDebug() << UpdateLotCmd.FrontLotList;
	//qDebug() << "[Back Lot List]";
	//qDebug() << m_BackMasterCode << "," << m_BackMachineID;
	//qDebug() << UpdateLotCmd.BackLotList;
	BroadcastBuildForShow();
}

void SelectLotForReview::ShowLotList(Review::SideType side, const LotInfoList &lotList)
{
	SelectLotForReviewLocker locker(&ui, this);

	if(lotList.isEmpty()==true){
		if(side==Review::Front){
			ui.twFrontLot->setRowCount(0);
			return;
		}else{
			ui.twBackLot->setRowCount(0);
			return;
		}
	}

	QTableWidget *table;
	if(side==Review::Front){
		table = ui.twFrontLot;
	}else{
		table = ui.twBackLot;
	}
	table->setRowCount(lotList.count());
	for(int y=0; y<table->rowCount(); y++){
		table->setItem(y, 0, new QTableWidgetItem(lotList[y].Filename()));
		table->setItem(y, 1, new QTableWidgetItem(lotList[y].LotName));
		qDebug() << lotList[y].TableName << LangSolver.GetString(SelectLotForReview_LS,LID_0)/*","*/ << lotList[y].LotName;
	}
	table->update();
}

void SelectLotForReview::doubleClicked(int row, int /*column*/)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();

	if(RBase==NULL){// Algorithmエラー
		return;
	}

	CmdSetSequenceEnable setSeqEnable(GetLayersBase());
	setSeqEnable.enable = false;
	RBase->TransmitDirectly( &setSeqEnable );
	setSeqEnable.enable = true;

	SelectLotForReviewLocker locker(&ui, this);

	CmdReqMasterDataInfo reqMInfo(GetLayersBase());
	RBase->TransmitDirectly(&reqMInfo);
	
	// 表側
	int MasterCode = reqMInfo.FrontMasterDataInfo.MasterCode;//m_FrontMasterCode;
	int MachineID = reqMInfo.FrontMasterDataInfo.MachineID;//m_FrontMachineID;

	// 裏側
	int rMasterCode = reqMInfo.BackMasterDataInfo.MasterCode;//m_BackMasterCode;
	int rMachineID = reqMInfo.BackMasterDataInfo.MachineID;//m_BackMachineID;

	// ロット名の検索
	QString tagLot;
	QString rtagLot;
	if(ui.tabWidget->currentIndex()==0){// 表側テーブルのダブルクリック時
		tagLot = ui.twFrontLot->item(row, 0)->text();
		for(int i=0; i<ui.twBackLot->rowCount(); i++){
			if(tagLot==ui.twBackLot->item(i, 0)->text()){
				rtagLot = tagLot;
				break;
			}
		}
	}else{// 裏側テーブルのダブルクリック時
		rtagLot = ui.twBackLot->item(row, 0)->text();
		for(int i=0; i<ui.twFrontLot->rowCount(); i++){
			if(rtagLot==ui.twFrontLot->item(i, 0)->text()){
				tagLot = rtagLot;
				break;
			}
		}
	}

	CmdServerSetLot Send(GetLayersBase());// ロット読み込みコマンドパケット
	CmdClearSideLot ClearCmd(GetLayersBase());// ロット削除コマンドパケット

	if(MasterCode!=-1 && MachineID!=-1 && tagLot.isEmpty()==false){// 正常
		// 表側読み込み
		Send.side = Review::Front;
		Send.LotFileName = tagLot;//Review::makeLotFileName(MasterCode, MachineID, tagLot);
		RBase->TransmitDirectly(&Send);
	}else{// 不正
		ClearCmd.side = Review::Front;
		RBase->TransmitDirectly(&ClearCmd);
	}
	
	if(rMasterCode!=-1 && rMachineID!=-1 && rtagLot.isEmpty()==false){// 正常
		// 裏側読み込み
		Send.side = Review::Back;
		Send.LotFileName = rtagLot;//Review::makeLotFileName(rMasterCode, rMachineID, rtagLot);
		RBase->TransmitDirectly(&Send);
	}else{// 不正
		ClearCmd.side = Review::Back;
		RBase->TransmitDirectly(&ClearCmd);
	}


	SeqControlParam	*Param=NULL;
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
	}
	if(Param!=NULL){
		Param	->LotName	=Send.LotFileName;
	}


	CmdReqCurrentLotInfo reqCurrentLotInfo(GetLayersBase());
	RBase->TransmitDirectly( &reqCurrentLotInfo );

	bool pro = getProperty().autoShowResultLoadLotForm;

	if(getProperty().autoShowResultLoadLotForm==true && reqCurrentLotInfo.getLotInfo(Review::Front).TableName.isEmpty()==false && reqCurrentLotInfo.getLotInfo(Review::Back).TableName.isEmpty()==false){

		CmdReqOrganizedHistoryList reqHistroyList(GetLayersBase());
		RBase->TransmitDirectly( &reqHistroyList );
	
		if(reqHistroyList.listPtr!=NULL){
			quint32 fNGCount=0;
			quint32 fOKCount=0;
			quint32 bNGCount=0;
			quint32 bOKCount=0;

			const OrganizedHistoryListPtr hlist = reqHistroyList.listPtr;

			for(int i=0; i<hlist->count(); i++){
				if(hlist->at(i).hasFront()==true){
					if(hlist->at(i).getFront()->isOK()==true){
						fOKCount++;
					}else{
						fNGCount++;
					}
				}
				if(hlist->at(i).hasBack()==true){
					if(hlist->at(i).getBack()->isOK()==true){
						bOKCount++;
					}else{
						bNGCount++;
					}
				}
			}

			if(getProperty().showOnlyHasError==false || (fNGCount+fOKCount)!=(bNGCount+bOKCount)){
				{
				ResultLotLoadForm resultForm(this);
				resultForm.setValue(fNGCount, fOKCount, bNGCount, bOKCount);
				resultForm.exec();
				}
				qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
			}
		}
	}

	// 初期位置設定
	CmdSetCurrentHistory SetCurrentHistoryCmd(GetLayersBase());
	SetCurrentHistoryCmd.Index = 0;
	RBase->TransmitDirectly(&SetCurrentHistoryCmd);

	CmdReqOrganizedHistoryList ReqOrgHistory(GetLayersBase());
	RBase->TransmitDirectly(&ReqOrgHistory);

	for(int i=0; i<ReqOrgHistory.listPtr->count(); i++){
		QString text;
		if(ReqOrgHistory.listPtr->at(i).isEmergencyResult(text)==true){
			text += LangSolver.GetString(SelectLotForReview_LS,LID_1)/*"\nThe board is regarded as OK"*/;
			QMessageBox::warning(this, LangSolver.GetString(SelectLotForReview_LS,LID_2)/*"HistoryResultError"*/, text);
		}
	}

	CmdReqCurrentHistory ReqCurrentHistoryCmd(GetLayersBase());
	RBase->TransmitDirectly(&ReqCurrentHistoryCmd);

	// NGの検査基盤までスキップ
	if(ReqCurrentHistoryCmd.historyPrt()!=NULL){
		if(ReqCurrentHistoryCmd.historyPrt()->isOK()==true){
			CmdMoveCurrentHistoryToNGBoard MoveCurrentHistoryToNGCmd(GetLayersBase());
			MoveCurrentHistoryToNGCmd.direction = Review::Next;
			RBase->TransmitDirectly(&MoveCurrentHistoryToNGCmd);

			CmdReqCurrentHistory ReqCurrentHistoryCmd(GetLayersBase());
			RBase->TransmitDirectly(&ReqCurrentHistoryCmd);

			if(ReqCurrentHistoryCmd.historyPrt()->isOK()==false){
				CmdSetCurrentNGNail SetCurrentNGCmd(GetLayersBase());
				SetCurrentNGCmd.refType = Review::Ref_Index;
				SetCurrentNGCmd.locate = Review::First;
				RBase->TransmitDirectly(&SetCurrentNGCmd);
			}
		}else{
			CmdSetCurrentNGNail SetCurrentNGCmd(GetLayersBase());
			SetCurrentNGCmd.refType = Review::Ref_Index;
			SetCurrentNGCmd.locate = Review::First;
			RBase->TransmitDirectly(&SetCurrentNGCmd);
		}
	}

	// 最初にチェックを入れる
	//CmdSetCurrentNGChecked SetCurrentNGCheckedCmd(GetLayersBase());
	//SetCurrentNGCheckedCmd.isChecked = true;
	//Base->TransmitDirectly(&SetCurrentNGCheckedCmd);


	//CmdReqAdjacentCurrentNG snd(GetLayersBase());
	//Base->TransmitDirectly(&snd);

	CmdUpdateForSaveLotList	UpdateForSaveLotCmd(GetLayersBase());
	RBase->TransmitDirectly( &UpdateForSaveLotCmd );


	// GUIを更新
	ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ShowHistoryListForReview);
	ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageListForReview);
	ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ListStatisticNG);
	ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ShowThumbnail);

	ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);
	//ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::WholeImageForReview);
	//ReviewGUI::UpdateHistoryGUI(GetLayersBase(), ReviewGUI::Name::WholeImageForReview);
	ReviewGUI::UpdateLotGUI(GetLayersBase(), ReviewGUI::Name::WholeImageForReview);

	// 全確認済みをチェック
	GUICmdUpdateCurrentHistoryChecked CheckHistoryCmd(GetLayersBase());
	ReviewGUI::ReviewGUICmdSend(GetLayersBase(), &CheckHistoryCmd, ReviewGUI::Name::ShowHistoryListForReview);


	//GUIFormBase *FBase = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::WholeImageForReview, "");
	//if(FBase!=NULL){
	//	GUICmdUpdateCurrentNGNail UpdateNGCmd(GetLayersBase());
	//	FBase->TransmitDirectly(&UpdateNGCmd);
	//}
	//GUIFormBase *HistoryGUI = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::ShowHistoryListForReview, "");
	//if(HistoryGUI!=NULL){
	//	GUICmdReviewUpdateLocal HistoryUpdateCmd(GetLayersBase());
	//	HistoryGUI->TransmitDirectly(&HistoryUpdateCmd);
	//}

	//CmdReqMasterDataInfo ReqMInfoCmd(GetLayersBase());
	//Base->TransmitDirectly( &ReqMInfoCmd );

	//Review::OrganizedSideType oside = Review::OrganizedSideType::None;
	//bool frontExist = !ReqMInfoCmd.FrontMasterDataInfo.isEmpty();
	//bool backExist = !ReqMInfoCmd.BackMasterDataInfo.isEmpty();
	//if(frontExist){
	//	if(backExist){
	//		oside = Review::OrganizedSideType::Both;
	//	}else{
	//		oside = Review::OrganizedSideType::FrontOnly;
	//	}
	//}else{
	//	if(backExist){
	//		oside = Review::OrganizedSideType::BackOnly;
	//	}else{
	//		oside = Review::OrganizedSideType::None;
	//	}
	//}

	//CmdReqOrganizedHistoryList ReqOrgCmd(GetLayersBase());
	//Base->TransmitDirectly( &ReqOrgCmd );

	//if(ReqOrgCmd.listPtr!=NULL && ReqOrgCmd.listPtr->isEmpty()==false){
	//	if(oside==Review::OrganizedSideType::Both){// 両面の場合
	//		// エラーチェック
	//		// 検査IDの飛び、重複を検索

	//		//QList<int> InspectIDList;
	//		QHash<int,bool> FrontMultiIDError;
	//		QList<int> FrontNoExistError;// 表側のないID
	//		QHash<int,bool> BackMultiIDError;
	//		QList<int> BackNoExistError;// 裏側のないID
	//		int FrontOKCount=0;
	//		int FrontNGCount=0;
	//		int BackOKCount=0;
	//		int BackNGCount=0;

	//		for(int i=0; i<ReqOrgCmd.listPtr->count(); i++){
	//			//InspectIDList.append(ReqOrgCmd.listPtr->at(i).getInspectID());// IDの保存
	//			if(ReqOrgCmd.listPtr->at(i).hasFront()==false){// 表検査履歴チェック
	//				FrontNoExistError.append(ReqOrgCmd.listPtr->at(i).getInspectID());// 検査履歴なし
	//			}else{
	//				if(FrontMultiIDError.contains(ReqOrgCmd.listPtr->at(i).getInspectID())==true){// 検査IDが複数存在している
	//					FrontMultiIDError[ReqOrgCmd.listPtr->at(i).getInspectID()] = false;
	//				}else{
	//					FrontMultiIDError.insert(ReqOrgCmd.listPtr->at(i).getInspectID(), true);// 通常はIDごとにここに一度だけ入る
	//				}
	//				if(ReqOrgCmd.listPtr->at(i).getFront()->isOK()){// OKかNGかで分岐、加算
	//					FrontOKCount++;
	//				}else{
	//					FrontNGCount++;
	//				}
	//			}
	//			if(ReqOrgCmd.listPtr->at(i).hasBack()==false){// 裏検査履歴チェック
	//				BackNoExistError.append(ReqOrgCmd.listPtr->at(i).getInspectID());// 検査履歴なし
	//			}else{
	//				if(BackMultiIDError.contains(ReqOrgCmd.listPtr->at(i).getInspectID())==true){// 検査IDが複数存在している
	//					BackMultiIDError[ReqOrgCmd.listPtr->at(i).getInspectID()] = BackMultiIDError[ReqOrgCmd.listPtr->at(i).getInspectID()] + 1;
	//				}else{
	//					BackMultiIDError.insert(ReqOrgCmd.listPtr->at(i).getInspectID(), 1);// 通常はIDごとにここに一度だけ入る
	//				}
	//				if(ReqOrgCmd.listPtr->at(i).getBack()->isOK()){// OKかNGかで分岐、加算
	//					BackOKCount++;
	//				}else{
	//					BackNGCount++;
	//				}
	//			}
	//		}

	//		{
	//		// エラーじゃないものを取り除く
	//		QList<int> keys = FrontMultiIDError.keys(true);// エラーじゃない
	//		for(int i=0; i<keys.count(); i++){
	//			FrontMultiIDError.remove(keys[i]);// 取り除き
	//		}
	//		keys = BackMultiIDError.keys(true);// エラーじゃない
	//		for(int i=0; i<keys.count(); i++){
	//			BackMultiIDError.remove(keys[i]);// 取り除き
	//		}
	//		}

	//		//// 検査IDの最大値を計算
	//		//int maxID=INT_MIN;
	//		//for(int i=0; i<InspectIDList.count(); i++){
	//		//	if(maxID<InspectIDList[i]){
	//		//		maxID = InspectIDList[i];
	//		//	}
	//		//}

	//		//// 検査IDの飛び、重複をチェック
	//		//QList<int> MultiErrorInspectIDList;//	IDが重複している場合
	//		//QList<int> NoExistErrorInspectIDList;//	IDがない場合
	//		//for(int i=0; i<maxID; i++){
	//		//	int cnt = InspectIDList.count(i);// i番の検査IDの数(通常１個)
	//		//	if(cnt>1){// 複数エラーの場合
	//		//		MultiErrorInspectIDList.append(i);
	//		//	}else if(cnt==0){// ID無しエラーの場合
	//		//		NoExistErrorInspectIDList.append(i);
	//		//	}
	//		//}
	//		
	//		// 何らかのエラーがあった場合
	//		if(/*MultiErrorInspectIDList.isEmpty()==false	|| NoExistErrorInspectIDList.empty()==false ||*/
	//			FrontMultiIDError.isEmpty()==false		|| FrontNoExistError.isEmpty()==false ||
	//			BackMultiIDError.isEmpty()==false		|| BackNoExistError.isEmpty()==false){
	//			QDialog diag;// エラー表示ダイアログ
	//			if(resultUi!=NULL){
	//				delete resultUi;
	//			}
	//			resultUi = new Ui::SelectLotResultClass;
	//			resultUi->setupUi(&diag);

	//			// 検査ボード計上結果
	//			resultUi->twBoardCount->setItem(0, 0, new QTableWidgetItem(QString::number(FrontOKCount)));
	//			resultUi->twBoardCount->setItem(1, 0, new QTableWidgetItem(QString::number(FrontNGCount)));
	//			resultUi->twBoardCount->setItem(2, 0, new QTableWidgetItem(QString::number(FrontOKCount+FrontNGCount)));
	//			resultUi->twBoardCount->setItem(0, 1, new QTableWidgetItem(QString::number(BackOKCount)));
	//			resultUi->twBoardCount->setItem(1, 1, new QTableWidgetItem(QString::number(BackNGCount)));
	//			resultUi->twBoardCount->setItem(2, 1, new QTableWidgetItem(QString::number(BackOKCount+BackNGCount)));

	//			if(FrontMultiIDError.isEmpty()==false || FrontNoExistError.isEmpty()==false){
	//				resultUi->twFrontError->setRowCount(FrontMultiIDError.count() + FrontNoExistError.count());// 行数の調整
	//				QList<int> keyList = FrontMultiIDError.keys();// キーの取得
	//				qSort(keyList);// IDを昇順に並べ替え
	//				int row;
	//				for(int i=0, row=0; i<keyList.count(); i++,row++){
	//					resultUi->twFrontError->setItem(row, 0, new QTableWidgetItem(QString::number(FrontMultiIDError[keyList[i]])));
	//					resultUi->twFrontError->setItem(row, 1, new QTableWidgetItem("Multi ID"));
	//				}
	//				qSort(FrontNoExistError);// IDを昇順に並べ替え
	//				for(int i=0; i<FrontNoExistError.count(); i++,row++){
	//					resultUi->twFrontError->setItem(row, 0, new QTableWidgetItem(QString::number(FrontNoExistError[i])));
	//					resultUi->twFrontError->setItem(row, 1, new QTableWidgetItem("No ID"));
	//				}
	//			}

	//			if(BackMultiIDError.isEmpty()==false || BackNoExistError.isEmpty()==false){
	//				resultUi->twBackError->setRowCount(BackMultiIDError.count() + BackNoExistError.count());// 行数の調整
	//				QList<int> keyList = BackMultiIDError.keys();// キーの取得
	//				qSort(keyList);// IDを昇順に並べ替え
	//				int row;
	//				for(int i=0, row=0; i<keyList.count(); i++,row++){
	//					resultUi->twBackError->setItem(row, 0, new QTableWidgetItem(QString::number(BackMultiIDError[keyList[i]])));
	//					resultUi->twBackError->setItem(row, 1, new QTableWidgetItem("Multi ID"));
	//				}
	//				qSort(BackNoExistError);// IDを昇順に並べ替え
	//				for(int i=0; i<BackNoExistError.count(); i++,row++){
	//					resultUi->twBackError->setItem(row, 0, new QTableWidgetItem(QString::number(BackNoExistError[i])));
	//					resultUi->twBackError->setItem(row, 1, new QTableWidgetItem("No ID"));
	//				}
	//			}

	//			diag.exec();
	//		}else{
	//			if(resultUi!=NULL){
	//				delete resultUi;
	//				resultUi = NULL;
	//			}
	//		}
	//	}
	//}

	// フォーカスを移動
	GUIFormBase *GBase;
	GUICmdSetFocus Cmd(GetLayersBase());
	GBase = GetReviewGUIForm(ReviewGUI::Name::NGImageListForReview);
	if(GBase!=NULL){
		GBase->TransmitDirectly(&Cmd);
	}
	GBase = GetReviewGUIForm(ReviewGUI::Name::ShowThumbnail);
	if(GBase!=NULL){
		GBase->TransmitDirectly(&Cmd);
	}

	CmdClearVRSCommandBuffer clearMoveVRSBuffer(GetLayersBase());
	CmdMoveVRSToCurrentNG moveCurrentNG(GetLayersBase());
	
	RBase->TransmitDirectly( &clearMoveVRSBuffer );
	RBase->TransmitDirectly( &setSeqEnable );
	RBase->TransmitDirectly( &moveCurrentNG );

	BroadcastBuildForShow();

	emit SignalClose();
}

void SelectLotForReview::okButtonClicked()
{
	QTableWidget *table;
	if(ui.tabWidget->currentIndex()==0){// Front
		table = ui.twFrontLot;
	}else{// Back
		table = ui.twBackLot;
	}
	if(table->currentRow()==-1)return;
	doubleClicked(table->currentRow(), table->currentColumn());
}

void SelectLotForReview::cancelButtonClicked()
{
	emit SignalClose();
}

void SelectLotForReview::updateGUI(bool onlySelf)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	SelectLotForReviewLocker locker(&ui, this);

	CmdReqMasterDataInfo ReqMInfoCmd(GetLayersBase());
	RBase->TransmitDirectly(&ReqMInfoCmd);

	//if(ReqMInfoCmd.FrontMasterDataInfo.MasterCode==m_FrontMasterCode && ReqMInfoCmd.FrontMasterDataInfo.MachineID==m_FrontMachineID &&
	//	ReqMInfoCmd.BackMasterDataInfo.MasterCode==m_FrontMasterCode && ReqMInfoCmd.BackMasterDataInfo.MachineID==m_FrontMachineID){
	//	return;
	//}


	//CmdServerReqCurrentLot Cmd(GetLayersBase());
	//RBase->TransmitDirectly(&Cmd);

	GUICmdReqStaticMachineID	MachineCmd(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"SelectMachine" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&MachineCmd);
	}

	//QStringList list;
	if(ReqMInfoCmd.FrontMasterDataInfo.MasterCode!=m_FrontMasterCode || ReqMInfoCmd.FrontMasterDataInfo.MachineID!=m_FrontMachineID){
		
		CmdServerSelectLotList Cmd(GetLayersBase());
		Cmd.MasterCode = ReqMInfoCmd.FrontMasterDataInfo.MasterCode;
		if(MachineCmd.DefaultTopMachineID<0){
			Cmd.MachineID = ReqMInfoCmd.FrontMasterDataInfo.MachineID;
		}
		else{
			Cmd.MachineID = MachineCmd.DefaultTopMachineID;
		}

		RBase->TransmitDirectly(&Cmd);

		if(Cmd.Ret==false)return;

		//for(QStringList::ConstIterator str=Cmd.LotList.constBegin(); str!=Cmd.LotList.constEnd(); str++){
		//	QString appendStr;
		//	int filenameIndex = str->lastIndexOf(QDir::separator());
		//	if(filenameIndex==-1){
		//		filenameIndex = str->lastIndexOf(/**/'\\');
		//	}
		//	if(filenameIndex==-1){
		//		filenameIndex = str->lastIndexOf(/**/'/');
		//	}

		//	if(filenameIndex==-1){
		//		appendStr = *str;
		//	}else{
		//		appendStr = str->right(str->count() - (filenameIndex+1));
		//	}
		//	list.append(appendStr);
		//}

		ui.twFrontLot->setRowCount(Cmd.list.count());
		for(int i=0; i<Cmd.list.count(); i++){
			ui.twFrontLot->setItem(i, 0, new QTableWidgetItem(Cmd.list[i].Filename()));
			ui.twFrontLot->setItem(i, 1, new QTableWidgetItem(Cmd.list[i].LotName));
		}
	}


	if(ReqMInfoCmd.BackMasterDataInfo.MasterCode!=m_BackMasterCode || ReqMInfoCmd.BackMasterDataInfo.MachineID!=m_BackMachineID){
				
		CmdServerSelectLotList Cmd(GetLayersBase());
		Cmd.MasterCode = ReqMInfoCmd.BackMasterDataInfo.MasterCode;
		if(MachineCmd.DefaultBottomMachineID<0){
			Cmd.MachineID = ReqMInfoCmd.BackMasterDataInfo.MachineID;
		}
		else{
			Cmd.MachineID = MachineCmd.DefaultBottomMachineID;
		}

		RBase->TransmitDirectly(&Cmd);

		if(Cmd.Ret==false)return;
		
		//list.clear();
		//for(QStringList::ConstIterator str=Cmd.LotList.constBegin(); str!=Cmd.LotList.constEnd(); str++){
		//	QString appendStr;
		//	int filenameIndex = str->lastIndexOf(QDir::separator());
		//	if(filenameIndex==-1){
		//		filenameIndex = str->lastIndexOf(/**/'\\');
		//	}
		//	if(filenameIndex==-1){
		//		filenameIndex = str->lastIndexOf(/**/'/');
		//	}

		//	if(filenameIndex==-1){
		//		appendStr = *str;
		//	}else{
		//		appendStr = str->right(str->count() - (filenameIndex+1));
		//	}
		//	list.append(appendStr);
		//}

		ui.twBackLot->setRowCount(Cmd.list.count());
		for(int i=0; i<Cmd.list.count(); i++){
			ui.twBackLot->setItem(i, 0, new QTableWidgetItem(Cmd.list[i].Filename()));
			ui.twBackLot->setItem(i, 1, new QTableWidgetItem(Cmd.list[i].LotName));
		}
	}


	//ui.tblLotList->clear();
	//ReviewPIBase *RBase = GetReviewAlgorithm();
	//if(RBase!=NULL){
	//	CmdServerSelectLotList Send(GetLayersBase());
	//	Send.MasterCode = m_MasterCode;
	//	Send.MachineID = m_MachineID;
	//	RBase->TransmitDirectly(&Send);
	//	if(Send.Ret==true){
	//		ShowLotList(Send.LotList);
	//	}
	//}
}

void SelectLotForReview::setGUIEnable(bool enable)
{
	ui.cancelButton->setEnabled(enable);
	ui.okButton->setEnabled(enable);
	ui.pbUpdate->setEnabled(enable);
	ui.tabWidget->setEnabled(enable);
}
