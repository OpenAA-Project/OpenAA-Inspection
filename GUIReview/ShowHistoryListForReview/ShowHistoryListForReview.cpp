#include "ShowHistoryListForReviewResource.h"
#include "ShowHistoryListForReview.h"
#include "../XGUIReviewGlobal.h"
#include "ReviewStructureItems.h"
#include "ReviewStructurePacket.h"
#include "../XGUIReviewCommonPacket.h"
#include "XReviewCommonPacket.h"
#include "../XGUIReviewGlobal.h"
#include "../WholeImageForReview/WholeImageForReviewPacket.h"
#include "../NGImageForReview/NGImageForReviewPacket.h"

#include "ShowHistoryListForReviewPacket.h"
#include "XSequenceRepairLocal.h"
#include <QScrollBar>


static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"ShowHistoryListForReview";


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
	return(/**/"Show History");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowHistoryListForReview(Base,parent));
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
	if(maxDataDim<5)
		return(-1);

	Data[0].Type = /**/"bool";
	Data[0].VariableNameWithRoute=/**/"SameWidth";
	Data[0].Pointer	=&((ShowHistoryListForReview *)Instance)->SameWidth;
	Data[1].Type = /**/"int32";
	Data[1].VariableNameWithRoute=/**/"Width1";
	Data[1].Pointer	=&((ShowHistoryListForReview *)Instance)->Width1;
	Data[2].Type = /**/"int32";
	Data[2].VariableNameWithRoute=/**/"Width2";
	Data[2].Pointer	=&((ShowHistoryListForReview *)Instance)->Width2;
	Data[3].Type = /**/"int32";
	Data[3].VariableNameWithRoute=/**/"Width3";
	Data[3].Pointer	=&((ShowHistoryListForReview *)Instance)->Width3;
	Data[4].Type = /**/"int32";
	Data[4].VariableNameWithRoute=/**/"Width4";
	Data[4].Pointer	=&((ShowHistoryListForReview *)Instance)->Width4;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowHistoryListForReview.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ShowHistoryListForReview
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShowHistoryListForReview::ShowHistoryListForReview(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent),OKBoardVisible(false)
{
	Width1	=48;
	Width2	=160;
	Width3	=100;
	Width4	=100;
	SameWidth	=true;

	hhlInspectID	= LangSolver.GetString(ShowHistoryListForReview_LS,LID_14)/*"ID"*/;
	hhlInspectedTime= LangSolver.GetString(ShowHistoryListForReview_LS,LID_15)/*"Time"*/;
	hhlFrontInfo	= LangSolver.GetString(ShowHistoryListForReview_LS,LID_16)/*"F-Img(NG)"*/;
	hhlBackInfo		= LangSolver.GetString(ShowHistoryListForReview_LS,LID_17)/*"B-Img(NG)"*/;

	ui.setupUi(this);
	LangSolver.SetUI(this);

	twHorizontalHeaderLabels << hhlInspectID << hhlInspectedTime << hhlFrontInfo << hhlBackInfo;
	ui.twHistoryList->setHorizontalHeaderLabels(twHorizontalHeaderLabels);
	ui.twHistoryList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	ui.pbShowErrrorDialog->setEnabled(false);

	connect(this, SIGNAL(SignalResize()), SLOT(ResizeAction()));
	//connect(ui.twHistoryList, SIGNAL(cellClicked(int, int)), this, SLOT(relativeCellClicked(int, int)));
	connect(ui.twHistoryList, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(relativeCellClicked(int, int, int, int)));
	connect(ui.cbOKVisible, SIGNAL(stateChanged(int)), this, SLOT(stateOKViewChanged(int)));
	connect(ui.pbReload, SIGNAL(clicked()), this, SLOT(reloadData()));
	connect(ui.pbShowErrrorDialog, SIGNAL(clicked()), this, SLOT(showErrorDialog()));
	connect(ui.twHistoryList->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(sliderChanged(int)));

	ui.twHistoryList->setColumnCount(twHorizontalHeaderLabels.count());
	if(GetEditMode()==false){
		ui.twHistoryList->setRowCount(0);
	}

	//if(GetEditMode()==false){
	//	contextMenu = new QMenu(this);
	//	settingAction = new QAction("Setting", this);

	//	contextMenu->addAction(settingAction);

	//	connect(settingAction, SIGNAL(triggered()), this, SLOT(showSettingDialog()));
	//}

	setMinimumSize(100, 70);
	initProperty();
}
void	ShowHistoryListForReview::Prepare(void)
{
	if(SameWidth==false){
		ui.twHistoryList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Fixed);
		ui.twHistoryList->setColumnWidth(0,Width1);
		ui.twHistoryList->setColumnWidth(0,Width2);
		ui.twHistoryList->setColumnWidth(1,Width3);
		ui.twHistoryList->setColumnWidth(2,Width4);
	}
}
void ShowHistoryListForReview::ResizeAction()
{
}

ShowHistoryListForReview::~ShowHistoryListForReview()
{

}

void ShowHistoryListForReview::showSettingDialog()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL){
		return;
	}

	CmdReqSortHistoryOrder ReqSortHistCmd(GetLayersBase());
	RBase->TransmitDirectly( &ReqSortHistCmd );

	Ui::SettingDialogClass dui;
	QDialog dialog(this);

	dui.setupUi( &dialog );

	dui.cbSortOrder->setCurrentIndex( (int)ReqSortHistCmd.order );

	if(dialog.exec()==QDialog::Accepted){
		Review::OrderOfSortHistory order = (Review::OrderOfSortHistory)dui.cbSortOrder->currentIndex();
		CmdSetSortHistoryOrder Cmd(GetLayersBase());
		Cmd.order = order;
		RBase->TransmitDirectly( &Cmd );

		updateGUI();

		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageListForReview);
		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);
		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ShowThumbnail);
		ReviewGUI::UpdateHistoryGUI(GetLayersBase(), ReviewGUI::Name::WholeImageForReview);

		GUICmdSetFocus focusCmd(GetLayersBase());

		ReviewGUI::ReviewGUICmdSend(GetLayersBase(), &focusCmd, ReviewGUI::Name::NGImageListForReview);
		ReviewGUI::ReviewGUICmdSend(GetLayersBase(), &focusCmd, ReviewGUI::Name::ShowThumbnail);
	}
}

void ShowHistoryListForReview::showErrorDialog()
{
	//ReviewPIBase *RBase = GetReviewAlgorithm();
	//
	//if(RBase==NULL)return;

	//CmdReqOrganizedHistoryList ReqHistoryListCmd(GetLayersBase());
	//RBase->TransmitDirectly(&ReqHistoryListCmd);

	//CmdReqMasterDataInfo ReqMInfoCmd(GetLayersBase());
	//RBase->TransmitDirectly(&ReqMInfoCmd);

	//errorDialog.setHistory(ReqHistoryListCmd.listPtr, ReqMInfoCmd.sideType());

	if(errorDialog.hasError()){
		errorDialog.show();
	}
}

void ShowHistoryListForReview::contextMenuEvent(QContextMenuEvent *event)
{
	//if(GetEditMode()==false){
	//	QPoint p = event->pos() + geometry().topLeft();
	//	if(parentWidget()!=NULL){
	//		p += parentWidget()->geometry().topLeft();
	//	}
	//	contextMenu->exec(p);
	//}
}

void ShowHistoryListForReview::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		updateGUI();
		GUICmdReviewUpdateLocalVar->Ret = true;
		return;
	}
	GUICmdUpdateCurrentHistory *GUICmdUpdateCurrentHistoryVar = dynamic_cast<GUICmdUpdateCurrentHistory *>(packet);
	if(GUICmdUpdateCurrentHistoryVar!=NULL){
		if(NGIndexAtTableRow.isEmpty()==true){
			return;
		}
		CmdReqCurrentHistory Cmd(GetLayersBase());
		ReviewPIBase *RBase = GetReviewAlgorithm();
		RBase->TransmitDirectly(&Cmd);
		if(Cmd.Ret==true){
			int tableIndex;
			if(ui.cbOKVisible->isChecked()==false){
				tableIndex = NGIndexAtTableRow.indexOf(Cmd.index());
			}else{
				tableIndex = Cmd.index();
			}
			updateGUI();
			if(Cmd.index()>=0 && tableIndex!=-1){
				ui.twHistoryList->setCurrentCell(tableIndex, 0);
			}else{
				if(Cmd.index()<NGIndexAtTableRow.count() && ui.twHistoryList->rowCount()>=NGIndexAtTableRow[Cmd.index()]){
					ui.twHistoryList->setCurrentCell(Cmd.index(), 0);
				}else{
					ui.twHistoryList->setCurrentCell(-1, -1);
				}
			}
		}else{
			updateGUI();
			if(ui.twHistoryList->rowCount()!=0 && ui.twHistoryList->columnCount()!=0){
				ui.twHistoryList->setCurrentCell(0, 0);
			}
		}
		return;
	}
	GUICmdUpdateCurrentHistoryChecked *GUICmdUpdateCurrentHistoryCheckedVar = dynamic_cast<GUICmdUpdateCurrentHistoryChecked *>(packet);
	if(GUICmdUpdateCurrentHistoryCheckedVar!=NULL){
		CmdReqCurrentHistory Cmd(GetLayersBase());
		ReviewPIBase *RBase = GetReviewAlgorithm();
		RBase->TransmitDirectly(&Cmd);
		if(Cmd.historyPrt()!=NULL){
			if(Cmd.historyPrt()->hasFront()==true){
				for(int i=0; i<Cmd.historyPrt()->getFront()->getNGNails().count(); i++){
					if(Cmd.historyPrt()->getFront()->getNGNails()[i].isChecked==false){
						for(int j=0; j<ui.twHistoryList->columnCount(); j++){
							QTableWidgetItem *item = ui.twHistoryList->item(getTableIndex(Cmd.index()), j);
							if(item!=NULL){
								item->setBackgroundColor(Qt::white);
							}else{
								QMessageBox::critical(this, LangSolver.GetString(ShowHistoryListForReview_LS,LID_8)/*"Error"*/, LangSolver.GetString(ShowHistoryListForReview_LS,LID_9)/*"Error"*/);
							}
						}
						return;
					}
				}
			}
			if(Cmd.historyPrt()->hasBack()==true){
				for(int i=0; i<Cmd.historyPrt()->getBack()->getNGNails().count(); i++){
					if(Cmd.historyPrt()->getBack()->getNGNails()[i].isChecked==false){
						for(int j=0; j<ui.twHistoryList->columnCount(); j++){
							QTableWidgetItem *item = ui.twHistoryList->item(getTableIndex(Cmd.index()), j);
							if(item!=NULL){
								item->setBackgroundColor(Qt::white);
							}else{
								QMessageBox::critical(this, LangSolver.GetString(ShowHistoryListForReview_LS,LID_10)/*"Error"*/, LangSolver.GetString(ShowHistoryListForReview_LS,LID_11)/*"Error"*/);
							}
						}
						return;
					}
				}
			}
			for(int j=0; j<ui.twHistoryList->columnCount(); j++){
				int index = getTableIndex(Cmd.index());
				QTableWidgetItem *item = ui.twHistoryList->item(index, j);
				if(item!=NULL){
					item->setBackgroundColor(QColor(170,255,170));
				}else{
					QMessageBox::critical(this, LangSolver.GetString(ShowHistoryListForReview_LS,LID_12)/*"Error"*/, LangSolver.GetString(ShowHistoryListForReview_LS,LID_13)/*"Error"*/);
				}
			}
		}
		return;
	}
	GUICmdSetEnable *GUICmdSetEnableVar = dynamic_cast<GUICmdSetEnable *>(packet);
	if(GUICmdSetEnableVar!=NULL){
		setGUIEnale(GUICmdSetEnableVar->enable);
		return;
	}
	
	ReviewCommonPacket::CmdReqSettingPropertyDialog *CmdReqSettingPropertyDialogVar = dynamic_cast<ReviewCommonPacket::CmdReqSettingPropertyDialog *>(packet);
	if(CmdReqSettingPropertyDialogVar!=NULL){
		//CmdReqSettingPropertyDialogVar->dialog = getPropertyDialog();
		CmdReqSettingPropertyDialogVar->setDialog(NULL);
		CmdReqSettingPropertyDialogVar->setGroupName(ReviewGUI::PropertyGroupName::Global);
		CmdReqSettingPropertyDialogVar->setGUIName(ReviewGUI::Name::ShowHistoryListForReview);
		return;
	}
}

int ShowHistoryListForReview::getTableIndex(int GlobalIndex)
{
	if(GlobalIndex<0)return -1;
	if(ui.cbOKVisible->isChecked()==true){
		return GlobalIndex;
	}else{
		return NGIndexAtTableRow.indexOf(GlobalIndex);
	}
}

void ShowHistoryListForReview::setTableRowItem(int row, TableData data ,int &TopNGCount ,int &BackNGCount ,XDateTime &InspectionTime)
{
	QTableWidgetItem *item;

	item = new QTableWidgetItem(QString::number(data.EID));
	ui.twHistoryList->setItem(row, twHorizontalHeaderLabels.indexOf(hhlInspectID), item);

	InspectionTime	=data.InspectedTime;
	item = new QTableWidgetItem(data.InspectedTime.toString());
	ui.twHistoryList->setItem(row, twHorizontalHeaderLabels.indexOf(hhlInspectedTime), item);
	
	if(data.hasFront()==true){
		if(data.FrontNGNailCount==0){
			item = new QTableWidgetItem(/**/"OK");
		}else{
			item = new QTableWidgetItem(QString(/**/"%1(%2)").arg(data.FrontNGNailCount).arg(QString::number(data.FrontNGCount)));
			TopNGCount+=data.FrontNGCount;
		}
	}else{
		item = new QTableWidgetItem(/**/"-");
	}
	ui.twHistoryList->setItem(row, twHorizontalHeaderLabels.indexOf(hhlFrontInfo), item);
	
	if(data.hasBack()==true){
		if(data.BackNGNailCount==0){
			item = new QTableWidgetItem(/**/"OK");
		}else{
			item = new QTableWidgetItem(QString(/**/"%1(%2)").arg(data.BackNGNailCount).arg(QString::number(data.BackNGCount)));
			BackNGCount+=data.BackNGCount;
		}
	}else{
		item = new QTableWidgetItem(/**/"-");
	}
	ui.twHistoryList->setItem(row, twHorizontalHeaderLabels.indexOf(hhlBackInfo), item);

	if(data.isAllChecked==true){
		if(row<ui.twHistoryList->rowCount()){
			for(int i=0; i<ui.twHistoryList->columnCount(); i++){
				if(ui.twHistoryList->item(row, i)!=NULL){
					ui.twHistoryList->item(row, i)->setBackgroundColor(QColor(170, 255, 170));
				}
			}
		}
	}else{
		if(row<ui.twHistoryList->rowCount()){
			for(int i=0; i<ui.twHistoryList->columnCount(); i++){
				if(ui.twHistoryList->item(row, i)!=NULL){
					ui.twHistoryList->item(row, i)->setBackgroundColor(Qt::white);
				}
			}
		}
	}
}

void ShowHistoryListForReview::ShowHistoryList(OrganizedHistoryListPtr orgHistoryListPtr)
{
	if(orgHistoryListPtr==NULL){
		return;
	}
	OrgDataList.clear();
	NGIndexAtTableRow.clear();

	int OKBoardCount=0;
	int NGBoardCount=0;
	int	HaltBoardCount=0;

	// 全データのリストを作成
	for(int i=0; i<orgHistoryListPtr->count(); i++){
		TableData data;
		bool isAllChecked = true;
		data.EID = orgHistoryListPtr->at(i).getInspectID();
		data.InspectedTime = orgHistoryListPtr->at(i).getInspectedTime();
		if(orgHistoryListPtr->at(i).hasFront()==true){
			if(orgHistoryListPtr->at(i).getFront()->isHalt()==true)
				data.FrontHalt=true;
			data.FrontNGNailCount = orgHistoryListPtr->at(i).getFront()->getNGNails().count();
			data.FrontNGCount = orgHistoryListPtr->at(i).getFront()->NGCount;
			data.InspectedMachine=orgHistoryListPtr->at(i).getFront()->InspectedMachine;
			for(int j=0; isAllChecked==true && j<orgHistoryListPtr->at(i).getFront()->getNGNails().count(); j++){
				if(orgHistoryListPtr->at(i).getFront()->getNGNails()[j].isChecked==false){
					isAllChecked = false;
					break;
				}
			}
		}
		if(orgHistoryListPtr->at(i).hasBack()==true){
			if(orgHistoryListPtr->at(i).getBack()->isHalt()==true)
				data.BackHalt=true;
			data.BackNGNailCount = orgHistoryListPtr->at(i).getBack()->getNGNails().count();
			data.BackNGCount = orgHistoryListPtr->at(i).getBack()->NGCount;
			if(isAllChecked==true){
				for(int j=0; isAllChecked==true && j<orgHistoryListPtr->at(i).getBack()->getNGNails().count(); j++){
					if(orgHistoryListPtr->at(i).getBack()->getNGNails()[j].isChecked==false){
						isAllChecked = false;
						break;
					}
				}
			}
		}
		data.isAllChecked = isAllChecked;
		OrgDataList.append(data);
		if(data.isOK()==true){
			OKBoardCount++;
		}else{
			NGBoardCount++;
		}
		if(data.FrontHalt==true || data.BackHalt==true){
			HaltBoardCount++;
		}
	}

	// OKNG基盤数を表示
	ui.lbOKBoardCount->setText(QString::number(OKBoardCount));
	ui.lbNGBoardCount->setText(QString::number(NGBoardCount));

	ui.leHistoryCount->setText(QString::number(OKBoardCount+NGBoardCount));

	// 行列数を設定
	ui.twHistoryList->setColumnCount(twHorizontalHeaderLabels.count());
	ui.twHistoryList->setHorizontalHeaderLabels(twHorizontalHeaderLabels);

	// 最初のイテレータ
	OrganizedHistoryList::ConstIterator it=orgHistoryListPtr->constBegin();

	// テーブルの各セルに要素を配置
	//for(int i=0; it!=orgHistoryListPtr->constEnd(); it++,i++){
	
	// NGのインデックスリスト作成
	for(int i=0; i<OrgDataList.count(); i++){
		if(OrgDataList[i].isOK()==false){
			NGIndexAtTableRow.append(i);
		}
	}
	ReviewPIBase *RBase = GetReviewAlgorithm();
	CmdSetCountOkNgForSave	CmdCounter(GetLayersBase());
	CmdCounter.CountOK	=OKBoardCount;
	CmdCounter.CountNG	=NGBoardCount;
	CmdCounter.CountHalt=HaltBoardCount;
	RBase->TransmitDirectly(&CmdCounter);

	updateTable();
}

void ShowHistoryListForReview::updateTable()
{
	CmdSetCurrentNGInfo	GCmd(GetLayersBase());

	XDateTime	InspectionTime;
	ui.twHistoryList->setRowCount(0);
	ui.twHistoryList->setUpdatesEnabled(false);
	if(ui.cbOKVisible->isChecked()==true){
		ui.twHistoryList->setRowCount(OrgDataList.count());
		for(int i=0; i<OrgDataList.count(); i++){
			setTableRowItem(i, OrgDataList[i],GCmd.NGCountTop,GCmd.NGCountBack,InspectionTime);
			if(GCmd.InspectionTimeFirst.IsAvailable()==false || GCmd.InspectionTimeFirst>InspectionTime){
				GCmd.InspectionTimeFirst=InspectionTime;
			}
			if(GCmd.InspectionTimeLast.IsAvailable()==false || GCmd.InspectionTimeLast<InspectionTime){
				GCmd.InspectionTimeLast=InspectionTime;
			}
			GCmd.InspectedMachine=OrgDataList[i].InspectedMachine;
		}
	}else{
		ui.twHistoryList->setRowCount(NGIndexAtTableRow.count());
		for(int i=0; i<NGIndexAtTableRow.count(); i++){
			setTableRowItem(i, OrgDataList[NGIndexAtTableRow[i]],GCmd.NGCountTop,GCmd.NGCountBack,InspectionTime);
			if(GCmd.InspectionTimeFirst.IsAvailable()==false || GCmd.InspectionTimeFirst>InspectionTime){
				GCmd.InspectionTimeFirst=InspectionTime;
			}
			if(GCmd.InspectionTimeLast.IsAvailable()==false || GCmd.InspectionTimeLast<InspectionTime){
				GCmd.InspectionTimeLast=InspectionTime;
			}
			GCmd.InspectedMachine=OrgDataList[NGIndexAtTableRow[i]].InspectedMachine;
		}
	}
	ui.twHistoryList->setUpdatesEnabled(true);
	ui.twHistoryList->horizontalHeader()->resizeSections(QHeaderView::ResizeMode::ResizeToContents);

	ReviewPIBase *RBase = GetReviewAlgorithm();
	RBase->TransmitDirectly(&GCmd);
}

void ShowHistoryListForReview::sliderChanged(int value)
{
	ui.twHistoryList->horizontalHeader()->resizeSections(QHeaderView::ResizeMode::ResizeToContents);
	ui.twHistoryList->horizontalHeader()->setStretchLastSection(true);
}

void ShowHistoryListForReview::reloadData()
{
	int currentRow = ui.twHistoryList->currentRow();
	int currentColumn = ui.twHistoryList->currentColumn();
	int currentEID = -1;

	ReviewPIBase *RBase = GetReviewAlgorithm();

	CmdReqCurrentHistory RCH(GetLayersBase());

	RBase->TransmitDirectly( &RCH );

	if(RCH.Ret==true && RCH.historyPrt()!=NULL){
		currentEID = RCH.historyPrt()->getInspectID();
	}

	// ロットの再読み込み
	CmdUpdateCurrentLotData UCLD(GetLayersBase());
	
	RBase->TransmitDirectly(&UCLD);

	// 過去の行を設定
	int eidIndex = twHorizontalHeaderLabels.indexOf(hhlInspectID);

	for(int row=0; row<ui.twHistoryList->rowCount(); row++){
		if(ui.twHistoryList->item(row, eidIndex)->text().toInt()==currentEID){
			CmdSetCurrentHistory SCH(GetLayersBase());

			SCH.Index = row;

			RBase->TransmitDirectly(&SCH);
		}
	}

	ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());

	GUICmdSetFocus SF(GetLayersBase());
	GUIFormBase *NBase = GetReviewGUIForm(ReviewGUI::Name::NGImageListForReview);
	GUIFormBase *TBase = GetReviewGUIForm(ReviewGUI::Name::ShowThumbnail);

	if(TBase!=NULL){
		TBase->TransmitDirectly(&SF);
	}else{
		if(NBase!=NULL){
			NBase->TransmitDirectly(&SF);
		}
	}

	ui.twHistoryList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	ui.twHistoryList->updateGeometry();
}

void ShowHistoryListForReview::relativeCellClicked(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	if(currentRow==-1){
		//GUIFormBase *p = GetReviewGUIForm(ReviewGUI::Name::NGImageForReview);
		//if(p!=NULL){
		//	GUICmdReqSetNGImage ClearNGImageCmd(GetLayersBase());
		//	ClearNGImageCmd.NGNailPtr = NULL;
		//	p->TransmitDirectly(&ClearNGImageCmd);
		//}
		return;
	}
	if(ui.cbOKVisible->isChecked()==true && NGIndexAtTableRow.contains(currentRow)==false){// NGのインデックスに含まれない（OKボードの場合）
		repaint();
		ui.twHistoryList->setCurrentCell(previousRow, previousColumn, QItemSelectionModel::SelectionFlag::ClearAndSelect | QItemSelectionModel::SelectionFlag::Rows);// 前のインデックスを指定
		update();
		return;
	}
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		SeqControlParam	*Param=NULL;
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		}
		CmdSetCurrentHistory SetCurrentHistoryCmd(GetLayersBase());
		//SetCurrentHistoryCmd.Index = currentRow;
		if(ui.cbOKVisible->isChecked()==false){
			if(currentRow<NGIndexAtTableRow.count()){
				SetCurrentHistoryCmd.Index = NGIndexAtTableRow[currentRow];
			}else{
				if(NGIndexAtTableRow.isEmpty()==true){
					SetCurrentHistoryCmd.Index = -1;
				}else{
					SetCurrentHistoryCmd.Index = NGIndexAtTableRow.count()-1;
				}
			}
		}else{
			SetCurrentHistoryCmd.Index = currentRow;
		}
		RBase->TransmitDirectly(&SetCurrentHistoryCmd);

		//CmdSetCurrentNGChecked checkCmd(GetLayersBase());
		//checkCmd.isChecked = true;
		//RBase->TransmitDirectly(&checkCmd);

		CmdReqForSaveBundle BCmd(GetLayersBase());
		BCmd.CurerntRow	=currentRow;
		if(ui.cbOKVisible->isChecked()==true){
			BCmd.InspectionID	=OrgDataList[currentRow].EID;
			BCmd.InspectionTime	=OrgDataList[currentRow].InspectedTime;
			if(Param!=NULL){
				Param->InspectionID	=BCmd.InspectionID;
			}
			//BCmd.Halt			=OrgDataList[currentRow].
		}else{
			if(NGIndexAtTableRow.count()>currentRow){
				BCmd.InspectionID	=OrgDataList[NGIndexAtTableRow[currentRow]].EID;
				BCmd.InspectionTime	=OrgDataList[NGIndexAtTableRow[currentRow]].InspectedTime;
				//BCmd.Halt			=OrgDataList[NGIndexAtTableRow[currentRow]].
				if(Param!=NULL){
					Param->InspectionID	=BCmd.InspectionID;
				}
			}
		}
		RBase->TransmitDirectly(&BCmd);

		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ListPiece);
		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);
		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageListForReview);
		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ShowThumbnail);
		
		GUIFormBase *Base = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::ShowThumbnail, /**/"");
		if(Base!=NULL){
			GUICmdSetFocus FocusCmd(GetLayersBase());
			Base->TransmitDirectly(&FocusCmd);
		}
		Base = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::NGImageListForReview, /**/"");
		if(Base!=NULL){
			GUICmdSetFocus FocusCmd(GetLayersBase());
			Base->TransmitDirectly(&FocusCmd);
		}
		Base = GetReviewGUIForm(ReviewGUI::Name::WholeImageForReview);
		if(Base!=NULL){
			GUICmdUpdateCurrentHistory Cmd(GetLayersBase());
			Base->TransmitDirectly(&Cmd);
		}


		return;
	}
}

void ShowHistoryListForReview::updateGUI()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		// リストを表示
		CmdReqOrganizedHistoryList ReqListCmd(GetLayersBase());
		RBase->TransmitDirectly(&ReqListCmd);

		if(ReqListCmd.Ret==true){
			ShowHistoryList(ReqListCmd.listPtr);
		}else{
			ShowHistoryList(NULL);
		}

		// 現在のカレント履歴を設定
		CmdReqCurrentHistory ReqCurrentHistoryCmd(GetLayersBase());
		RBase->TransmitDirectly(&ReqCurrentHistoryCmd);

		if(ReqCurrentHistoryCmd.index()>=0 && NGIndexAtTableRow.contains(ReqCurrentHistoryCmd.index())){
			ui.twHistoryList->setCurrentCell(NGIndexAtTableRow.indexOf(ReqCurrentHistoryCmd.index()), 0, QItemSelectionModel::SelectionFlag::ClearAndSelect | QItemSelectionModel::SelectionFlag::Rows);
		}

		//int row = ui.twHistoryList->currentRow();

		//int row;
		//for(OrganizedHistoryList::ConstIterator it=Send.listPtr->constBegin(); it!=Send.listPtr->constEnd(); it++,row++){
		//	if(it->getInspectID() == ReqCurrentHistoryCmd.OrgHistoryPtr->getInspectID()){
		//		ui.twHistoryList->setCurrentCell(row, 0);
		//		return;
		//	}
		//}
		//ui.twHistoryList->setCurrentCell(-1, -1);
		ui.twHistoryList->updateGeometry();
		ui.twHistoryList->horizontalHeader()->updateGeometry();

		CmdReqMasterDataInfo ReqMInfoCmd(GetLayersBase());
		RBase->TransmitDirectly(&ReqMInfoCmd);

		errorDialog.setHistory(ReqListCmd.listPtr, ReqMInfoCmd.sideType());

		bool errorDlgVisible = errorDialog.hasError();
		ui.pbShowErrrorDialog->setEnabled(errorDlgVisible);
		QPalette pal = palette();
		if(errorDlgVisible==true){
			pal.setColor(QPalette::ColorRole::Button, QColor(230, 150, 150));
		}
		ui.pbShowErrrorDialog->setPalette(pal);
		//errorDialog.setVisible(errorDlgVisible);

		ui.twHistoryList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
		ui.twHistoryList->updateGeometry();
	}
}

void ShowHistoryListForReview::setGUIEnale(bool enable)
{
	ui.cbOKVisible->setEnabled(enable);
	ui.pbReload->setEnabled(enable);
	ui.pbShowErrrorDialog->setEnabled(enable);
	ui.twHistoryList->setEnabled(enable);
}

void ShowHistoryListForReview::stateOKViewChanged(int state)
{
	if(OrgDataList.isEmpty()==true){
		return;
	}

	int prevIndex = ui.twHistoryList->currentRow();

	updateTable();

	int currIndex;
	if(state==Qt::CheckState::Checked){
		currIndex = NGIndexAtTableRow[prevIndex];
	}else{
		currIndex = NGIndexAtTableRow.indexOf(prevIndex);
	}
	ui.twHistoryList->setCurrentCell(currIndex, 0, QItemSelectionModel::SelectionFlag::ClearAndSelect | QItemSelectionModel::SelectionFlag::Rows);
}

