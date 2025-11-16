#include "NGImageListForReviewResource.h"
#include "NGImageListForReview.h"
#include "../XGUIReviewCommonPacket.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "XReviewCommonPacket.h"
#include "../XGUIReviewGlobal.h"
#include "../WholeImageForReview/WholeImageForReviewPacket.h"
#include "../ShowHistoryListForReview/ShowHistoryListForReviewPacket.h"

#include "NGImageListForReviewProperty.h"
#include "XAutofocusControl.h"
#include <QMessageBox>
#include "XSequenceRepairLocal.h"
#include "XCriticalFunc.h"
#include <QMenu>
#include <QAction>

static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"NGImageListForReview";


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
	return(/**/"Show NG Image List for Review");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new NGImageListForReview(Base,parent));
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
	if(maxDataDim<11)
		return(-1);

	Data[0].Type = /**/"int32";
	Data[0].VariableNameWithRoute=/**/"NextListDelayMiliSec";
	Data[0].Pointer	=&((NGImageListForReview *)Instance)->reqData.NextListDelay;
	Data[1].Type = /**/"bool";
	Data[1].VariableNameWithRoute=/**/"NextWaitProgressVisible";
	Data[1].Pointer	=&((NGImageListForReview *)Instance)->reqData.WaitProgressVisible;

	Data[2].Type = /**/"bool";
	Data[2].VariableNameWithRoute=/**/"SameWidth";
	Data[2].Pointer	=&((NGImageListForReview *)Instance)->SameWidth;
	Data[3].Type = /**/"int32";
	Data[3].VariableNameWithRoute=/**/"WidthXYMatrix";
	Data[3].Pointer	=&((NGImageListForReview *)Instance)->WidthXYMatrix;
	Data[4].Type = /**/"int32";
	Data[4].VariableNameWithRoute=/**/"WidthLibrary";
	Data[4].Pointer	=&((NGImageListForReview *)Instance)->WidthLibrary;
	Data[5].Type = /**/"int32";
	Data[5].VariableNameWithRoute=/**/"WidthCause";
	Data[5].Pointer	=&((NGImageListForReview *)Instance)->WidthCause;
	Data[6].Type = /**/"int32";
	Data[6].VariableNameWithRoute=/**/"WidthCount";
	Data[6].Pointer	=&((NGImageListForReview *)Instance)->WidthCount;
	Data[7].Type = /**/"int32";
	Data[7].VariableNameWithRoute=/**/"WidthArea";
	Data[7].Pointer	=&((NGImageListForReview *)Instance)->WidthArea;
	Data[8].Type = /**/"bool";
	Data[8].VariableNameWithRoute=/**/"SkipSamePiece";
	Data[8].Pointer	=&((NGImageListForReview *)Instance)->SkipSamePiece;
	Data[9].Type = /**/"int32";
	Data[9].VariableNameWithRoute=/**/"WaitMilisecToChangeSurface";
	Data[9].Pointer	=&((NGImageListForReview *)Instance)->WaitMilisecToChangeSurface;

	return(10);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/NGImageListForReview.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NGImageListForReview
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NGImageListForReview::NGImageListForReview(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent),defPalette(palette()),m_property(NULL),m_propertyDialog(NULL),m_propertyUi(NULL)
{
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	SameWidth		=true;
	WidthXYMatrix	=80;
	WidthLibrary	=60;
	WidthCause		=60;
	WidthCount		=30;
	WidthArea		=60;
	SkipSamePiece	=false;
	WaitMilisecToChangeSurface	=1000;

	initProperty();

	ui.setupUi(this);

	hhlNGPoint = LangSolver.GetString(NGImageListForReview_LS,LID_18)/*"X,Y"*/;
	hhlLibrary = LangSolver.GetString(NGImageListForReview_LS,LID_19)/*"LIBRARY"*/;
	hhlNGCause = LangSolver.GetString(NGImageListForReview_LS,LID_20)/*"NG Cause"*/;
	hhlNGCount = LangSolver.GetString(NGImageListForReview_LS,LID_21)/*"NG Count"*/;
	hhlNGArea  = LangSolver.GetString(NGImageListForReview_LS,LID_22)/*"Area"*/;

	LangSolver.SetUI(this);

	mainHHeader << hhlNGPoint << hhlLibrary << hhlNGCause << hhlNGCount << hhlNGArea;

	ui.tblMain->setColumnCount(mainHHeader.count());
	ui.tblMain->setHorizontalHeaderLabels(mainHHeader);
	ui.tblMain->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);

	NextListDelay = 0;
	reqData.NextListDelay = 0;
	reqData.WaitProgressVisible = true;
	setKeyPressedState(false);
	setAutoFillBackground(true);

	if(GetEditMode()==true){
	
	}else{
		ui.tblMain->setRowCount(0);

		ui.tblMain->installEventFilter(this);
		ui.gridLayout->installEventFilter(this);
		ui.horizontalLayout->installEventFilter(this);
		ui.label->installEventFilter(this);
		ui.leNGCount->installEventFilter(this);
		ui.verticalLayout->installEventFilter(this);

		contextMenu = new QMenu(this);

		//settingDialog = new SettingDialog(this);
		//settingAction = new QAction("Set Sort Order", this);
		//contextMenu->addAction(settingAction);

		controlInfoDialog = new ControlInfoDialog(this);
		controlInfoDialog->append(/**/"Space", LangSolver.GetString(NGImageListForReview_LS,LID_4)/*"Swap Flag for NG sign view."*/);
		controlInfoDialog->append(/**/"F1～F12", LangSolver.GetString(NGImageListForReview_LS,LID_5)/*"Set F key type Flag at current NG."*/);
		controlInfoDialog->append(/**/"Del", LangSolver.GetString(NGImageListForReview_LS,LID_6)/*"Remove F key type Flag at current NG."*/);
		showControlAction = new QAction(LangSolver.GetString(NGImageListForReview_LS,LID_7)/*"Control Infomation"*/, this);
		contextMenu->addAction(showControlAction);

		//connect(settingAction, SIGNAL(triggered()), this, SLOT(SlotSetSortOrder()));
		connect(showControlAction, SIGNAL(triggered()), this, SLOT(SlotShowKeyAssignInfoDialog()));

		connect(ui.tblMain, SIGNAL(currentCellChanged (int, int, int, int)), this, SLOT(cellChanged(int, int, int, int)));

		keyWaitTimeLine = new QTimeLine(1000, this);
		keyWaitTimeLine->setFrameRange(0, 100);

		ui.progKeyWait->setRange(0, 100);

		connect(keyWaitTimeLine, SIGNAL(frameChanged(int)), ui.progKeyWait, SLOT(setValue(int)));
		connect(ui.progKeyWait, SIGNAL(valueChanged(int)), this, SLOT(endKeyWaitTimeLine(int)));

		ui.tblMain->setFocus();
	}

	ui.tblMain->setHorizontalHeaderLabels(mainHHeader);
	ui.tblMain->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
}

int NGImageListForReview::getNextListDelay()
{
	if(currentRow()<0){
		return NextListDelay;
	}

	int retWaitTime = NextListDelay;// AnyDataInLibraryによるウェイトタイム設定値の取得]

	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdReqAdjacentCurrentNG ReqAdjacentCurrentNGCmd(GetLayersBase());

		RBase->TransmitDirectly( &ReqAdjacentCurrentNGCmd );

		if(ReqAdjacentCurrentNGCmd.existCurrentNG()==false){
			return NextListDelay;
		}else{
			for(int i=0; i<ReqAdjacentCurrentNGCmd.currentNG()->NGPointList.count(); i++){
				if(retWaitTime<ReqAdjacentCurrentNGCmd.currentNG()->NGPointList[i].Tag.Wait){
					retWaitTime = ReqAdjacentCurrentNGCmd.currentNG()->NGPointList[i].Tag.Wait;// 最大待機時間の設定
				}
			}
		}
	}

	return retWaitTime;
}

int NGImageListForReview::getNextListDelay(const NGNailItem &item) const
{
	int retWaitTime = NextListDelay;// AnyDataInLibraryによるウェイトタイム設定値の取得

	for(int i=0; i<item.NGPointList.count(); i++){
		if(retWaitTime<item.NGPointList[i].Tag.Wait){
			retWaitTime = item.NGPointList[i].Tag.Wait;// 最大待機時間の設定
		}
	}

	return retWaitTime;
}

//void NGImageListForReview::SlotSetSortOrder()
//{
//	ReviewPIBase *RBase = GetReviewAlgorithm();
//	CmdReqSortNGOrder ReqSortOrder(GetLayersBase());
//	RBase->TransmitDirectly(&ReqSortOrder);
//	settingDialog->setSortOrder(ReqSortOrder.order);
//
//	int oldIndex = settingDialog->getSortIndex();
//	if(settingDialog->exec()==QDialog::Accepted){
//		CmdSetSortNGOrder Send(GetLayersBase());
//		Send.order = settingDialog->getSortOrder();
//		RBase->TransmitDirectly(&Send);
//
//		updateGUI();
//
//		ReviewGUI::UpdateHistoryGUI(GetLayersBase(), ReviewGUI::Name::NGImageListForReview);
//		ReviewGUI::UpdateHistoryGUI(GetLayersBase(), ReviewGUI::Name::ShowThumbnail);
//		ReviewGUI::UpdateHistoryGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);
//		ReviewGUI::UpdateHistoryGUI(GetLayersBase(), ReviewGUI::Name::WholeImageForReview);
//	}else{
//		settingDialog->setSortIndex(oldIndex);
//	}
//	settingDialog->setVisible(false);
//}

void NGImageListForReview::SlotShowKeyAssignInfoDialog()
{
	controlInfoDialog->show();
}

void NGImageListForReview::contextMenuEvent(QContextMenuEvent *event)
{
	if(GetEditMode()==false){
		QPoint p = event->pos() + geometry().topLeft();
		if(parentWidget()!=NULL){
			p += parentWidget()->geometry().topLeft();
		}
		contextMenu->exec(p/*event->pos() + geometry().topLeft() + parentWidget()->geometry().topLeft()*/);
	}
}

NGImageListForReview::~NGImageListForReview()
{

}

void NGImageListForReview::Prepare()
{
	if(SameWidth==false){
		ui.tblMain->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Fixed);
		ui.tblMain->setColumnWidth(0,WidthXYMatrix);
		ui.tblMain->setColumnWidth(1,WidthLibrary);
		ui.tblMain->setColumnWidth(2,WidthCause);
		ui.tblMain->setColumnWidth(3,WidthCount);
		ui.tblMain->setColumnWidth(4,WidthArea);
	}

	NextListDelay = reqData.NextListDelay;
	ui.progKeyWait->setVisible(reqData.WaitProgressVisible);
	if(NextListDelay==0){
		ui.progKeyWait->hide();
	}
}

bool NGImageListForReview::eventFilter(QObject *target, QEvent *event)
{
	static	DWORD	LastTimeToKeyPress;	
	static	int		LastRow=-1;

	if(target == ui.tblMain ||
		target == ui.gridLayout ||
		target == ui.horizontalLayout ||
		target == ui.label ||
		target == ui.leNGCount ||
		target == ui.verticalLayout){
			if(event->type() == QEvent::KeyPress){

				int	FrontCount=-1;
				CmdReqCurrentHistory XSend(GetLayersBase());
				ReviewPIBase *RBase = GetReviewAlgorithm();
				RBase->TransmitDirectly(&XSend);
				if(XSend.historyPrt()->hasFront()==true){
					NGNailList NGList = XSend.historyPrt()->getFront()->getNGNails();
					FrontCount=NGList.count();
				}
				DWORD	D=(::GetComputerMiliSec()-LastTimeToKeyPress);
				if(currentRow()==FrontCount && D<WaitMilisecToChangeSurface){
					event->accept();
				}
				else{
					QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
					keyPressEvent(keyEvent);
				}
				if(target == ui.tblMain && LastRow!=currentRow()){
					LastTimeToKeyPress=::GetComputerMiliSec();
				}
				LastRow=currentRow();
				return true;
			}
	}
	return false;
}

void NGImageListForReview::updateGUI()
{
	if(GetEditMode()==true){
		return;
	}

	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdReqCurrentHistory Send(GetLayersBase());
		RBase->TransmitDirectly(&Send);
		if(Send.historyPrt()==NULL){
			setNGList(OrganizedHistoryItem());
			setViewColor(OrganizedHistoryItem());
		}else{
			setNGList(*Send.historyPrt());
			setViewColor(*Send.historyPrt());
		}
		CmdReqAdjacentCurrentNG CurrentAdjacentNG(GetLayersBase());
		RBase->TransmitDirectly(&CurrentAdjacentNG);
		if(CurrentAdjacentNG.Ret==true && CurrentAdjacentNG.existCurrentNG()==true){
			if(CurrentAdjacentNG.currentNGIndex()<0){
				ui.tblMain->setCurrentCell(-1, 0);
			}else{
				ui.tblMain->setCurrentCell(CurrentAdjacentNG.currentNGIndex(), 0);
				setCheckedCurrentNG();
				refleshTableRow(ui.tblMain->currentRow());
			}
		}

		CmdSetCurrentRowNGListForSave SendL(GetLayersBase());
		SendL.CurrentRow=0;
		RBase->TransmitDirectly(&SendL);
	}
}

void NGImageListForReview::refleshTableRow(int row)
{
	if(row==-1)return;
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdReqCurrentHistory ReqHistCmd(GetLayersBase());
		RBase->TransmitDirectly(&ReqHistCmd);
		if(ReqHistCmd.Ret==true){
			CmdReqFKeyColorList ReqFColorCmd(GetLayersBase());
			RBase->TransmitDirectly(&ReqFColorCmd);
			if(ReqHistCmd.historyPrt()->getNGNailItemIterator(row)->isChecked==true){
				fillBackgraundColorOnTableAtRow(row, ReqFColorCmd.list[Review::FKeyToInt(ReqHistCmd.historyPrt()->getNGNailItemIterator(row)->FKey)]);
			}else{
				fillBackgraundColorOnTableAtRow(row, QColor(Qt::white));
			}
		}
	}
}

void NGImageListForReview::setNGList(const OrganizedHistoryItem &history)
{
	ui.tblMain->setRowCount(0);
	if(history.hasFront()==false && history.hasBack()==false){// NGなどない
		ui.tblMain->setCurrentCell(-1, -1);
		ui.leNGCount->setText(/**/"0");
		return;
	}

	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL){
		QMessageBox::critical(this
							, LangSolver.GetString(NGImageListForReview_LS,LID_8)/*"Algorithm Access Error"*/
							, LangSolver.GetString(NGImageListForReview_LS,LID_9)/*"ReviewStructure is not exits or not able to access."*/);
		return;
	}

	// ライブラリハッシュテーブルを取得
	CmdReqInsLib Send(GetLayersBase());
	RBase->TransmitDirectly(&Send);

	// 検査ライブラリ取得失敗時は表示しない
	bool noInsLib = !Send.Ret;
	int NGSum=0;
	int NGNailSum=0;
	if(history.hasFront()){
		NGSum += history.getFront()->NGCount;
		NGNailSum += history.getFront()->getNGNails().count();
	}
	if(history.hasBack()){
		NGSum += history.getBack()->NGCount;
		NGNailSum += history.getBack()->getNGNails().count();
	}

	// 全NG数を表示できるように行を調整
	ui.tblMain->setRowCount(NGNailSum);

	// NG数を記述
	ui.leNGCount->setText(QString::number(NGSum));

	int currentRow=0;
	FrontCount=0;
	BackCount=0;
	if(history.hasFront()==true){// 表側の履歴あり
		// 記述するNGリスト
		addNGList(*history.getFront(), Send.FrontInsLibHash, currentRow);
		currentRow += history.getFront()->getNGNails().count();
		FrontCount = history.getFront()->getNGNails().count();
	}
	if(history.hasBack()==true){
		addNGList(*history.getBack(), Send.BackInsLibHash, currentRow);
		BackCount = history.getBack()->getNGNails().count();
	}

	updateVerticalHeader(FrontCount, BackCount);

	// 現在NGを選択する
	if(ui.tblMain->rowCount()!=0){
		CmdReqAdjacentCurrentNG CurrentNGState(GetLayersBase());
		RBase->TransmitDirectly(&CurrentNGState);
		ui.tblMain->setCurrentCell(CurrentNGState.currentNGIndex(), 0);

		CmdSetCurrentNGChecked CheckCurrentNGCmd(GetLayersBase());
		RBase->TransmitDirectly(&CheckCurrentNGCmd);
	}

	ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);
}

void NGImageListForReview::setViewColor(const OrganizedHistoryItem &history)
{
	QPalette pale = defPalette;
	QColor backColor = defPalette.window().color();
	int FrontCount = 0;
	int BackCount = 0;

	if(history.getSideType()==Review::OrganizedSideType::FrontOnly){
		backColor = getResultColor(history.getFront()->Result, defPalette.window().color());
		FrontCount = history.getFront()->getNGNails().count();
	}else if(history.getSideType()==Review::OrganizedSideType::BackOnly){
		backColor = getResultColor(history.getBack()->Result, defPalette.window().color());
		BackCount = history.getBack()->getNGNails().count();
	}else if(history.getSideType()==Review::OrganizedSideType::Both){
		QColor fColor = getResultColor(history.getFront()->Result, defPalette.window().color());
		FrontCount = history.getFront()->getNGNails().count();
		BackCount = history.getBack()->getNGNails().count();
		if(fColor==defPalette.window().color()){
			backColor = getResultColor(history.getBack()->Result, defPalette.window().color());
		}else{
			backColor = fColor;
		}
	}else{
		backColor = defPalette.window().color();
	}

	pale.setColor(QPalette::Window, backColor);

	setAutoFillBackground(true);
	setPalette(pale);

	GUIFormBase *HistoryListPtr = GetReviewGUIForm(ReviewGUI::Name::ShowHistoryListForReview);
	if(HistoryListPtr!=NULL){
		HistoryListPtr->setAutoFillBackground(true);
		HistoryListPtr->setPalette(pale);
	}

	//QList<GUIFormBase *> list = ReviewGUI::ReviewGUIExistList(GetLayersBase());
	//for(int i=0; i<list.count(); i++){
	//	list[i]->setAutoFillBackground(true);
	//	list[i]->setPalette(pale);
	//}

	update();
	updateVerticalHeader(FrontCount, BackCount);
}

QColor NGImageListForReview::getResultColor(const QStringList &resultList, const QColor &defaultColor)
{
	if(resultList.contains(/**/"OK")){
		return defaultColor;;// 通常色
	}else if(resultList.contains(/**/"TimeOver")){
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase!=NULL){
			CmdSetHaltForSave	SendL(GetLayersBase());
			SendL.Halt=2;
			RBase->TransmitDirectly(&SendL);
		}
		return QColor(Qt::yellow);// タイムオーバー
	}else if(resultList.contains(/**/"MaxOver")){
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase!=NULL){
			CmdSetHaltForSave	SendL(GetLayersBase());
			SendL.Halt=3;
			RBase->TransmitDirectly(&SendL);
		}
		return QColor(Qt::yellow);// NG個数過多
	}else if(resultList.contains(/**/"NG")){
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase!=NULL){
			CmdSetHaltForSave	SendL(GetLayersBase());
			SendL.Halt=1;
			RBase->TransmitDirectly(&SendL);
		}
		return defaultColor;// 通常色
	}else{
		return defaultColor;
	}
}

void NGImageListForReview::updateVerticalHeader(int FrontCount, int BackCount)
{
	QStringList vHeader;
	for(int i=0; i<FrontCount; i++){
		vHeader << QString(/**/"F-%1").arg(i+1);
	}
	for(int i=0; i<BackCount; i++){
		vHeader << QString(/**/"B-%1").arg(i+1);
	}
	ui.tblMain->setVerticalHeaderLabels(vHeader);
	
	for(int i=0; i<FrontCount; i++){
		ui.tblMain->verticalHeaderItem(i)->setBackgroundColor(palette().window().color());
	}
	for(int i=FrontCount; i<FrontCount+BackCount; i++){
		ui.tblMain->verticalHeaderItem(i)->setBackgroundColor(Qt::darkGray);
	}
}

QColor NGImageListForReview::setFKey(Review::FKey key)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdSetFKeyToNGNail Send(GetLayersBase());
		Send.key = key;
		RBase->TransmitDirectly(&Send);
		if(Send.Ret==false){
			QMessageBox::warning(this
								, LangSolver.GetString(NGImageListForReview_LS,LID_10)/*"XMLWrite Error"*/
								, LangSolver.GetString(NGImageListForReview_LS,LID_11)/*"F-Key to XML File writted whold be fault."*/);
		}
	
		CmdSetFKeyForSave SetSend(GetLayersBase());
		SetSend.Key=key;
		RBase->TransmitDirectly(&SetSend);

		return Send.FKeyColor;
	}

	return Review::getDefaultFKeyColor(Review::NoFKey);
}

void NGImageListForReview::addNGList(const HistoryItem &history, const InsLibraryHash &InsLibHash, int InsertRow)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();

	CmdReqWholeImageInfo CmdReqWInfo(GetLayersBase());
	RBase->TransmitDirectly(&CmdReqWInfo);

	CmdReqForSaveNGList	hCmdReqForSaveNGList(GetLayersBase());

	QList<QList<QPoint> > outlineOffset;
	switch(history.Side){
	case Review::Front:
		outlineOffset = CmdReqWInfo.FrontOutlineOffset;
		hCmdReqForSaveNGList.Top=true;
		break;
	case Review::Back:
		outlineOffset = CmdReqWInfo.BackOutlineOffset;
		hCmdReqForSaveNGList.Top=false;
		break;
	default:
		return;
		break;
	}

	CmdReqCSVOffset	ViewOffset(GetLayersBase());
	RBase->TransmitDirectly(&ViewOffset);


	NGNailList NGList = history.getNGNails();
	hCmdReqForSaveNGList.NGPoints=NGList.count();

	for(int i=0; i<NGList.count(); i++){// NG画像個数の全部追加
		NGNailItem NGItem = NGList.at(i);// NG画像単位情報
		QTableWidgetItem *item;// 挿入するテーブルセルのバッファ

		ForSaveNGPoint	*ForSaveNGPointer=new ForSaveNGPoint(InsertRow+i);
		ForSaveNGPointer->Top=hCmdReqForSaveNGList.Top;
		hCmdReqForSaveNGList.Data.NGList.AppendList(ForSaveNGPointer);
	
		ForSaveNGPointer->Side	=(history.Side==Review::Front)?1:2;

		// XY情報
		if(mainHHeader.contains(hhlNGPoint)==true){
			//int		XPos=NGItem.TargetPosX + outlineOffset[NGItem.phase][NGItem.page].x();
			//int		YPos=NGItem.TargetPosY + outlineOffset[NGItem.phase][NGItem.page].y();
			int		XPos;
			int		YPos;
			if(NGItem.NGPointList.count()>0){
				XPos=NGItem.NGPointList[0].x+ outlineOffset[NGItem.phase][NGItem.page].x();
				YPos=NGItem.NGPointList[0].y+ outlineOffset[NGItem.phase][NGItem.page].y();
			}
			else{
				XPos=NGItem.TargetPosX + outlineOffset[NGItem.phase][NGItem.page].x();
				YPos=NGItem.TargetPosY + outlineOffset[NGItem.phase][NGItem.page].y();
			}
			ForSaveNGPointer->Position=QPoint(XPos,YPos);
			if(ViewOffset.CSVUnitMM==false){
				QString xyStr = QString(/**/"%1,%2").arg(XPos).arg(YPos);
				item = new QTableWidgetItem(xyStr);
			}
			else{
				XPos=(XPos+ViewOffset.CSVOffsetX)*ViewOffset.CSVMagnificationX;
				YPos=(YPos+ViewOffset.CSVOffsetY)*ViewOffset.CSVMagnificationY;
				if(ViewOffset.CSVReverseX==true){
					XPos=-XPos;
				}
				if(ViewOffset.CSVReverseY==true){
					YPos=-YPos;
				}
				QString xyStr = QString::number(GetParamGlobal()->TransformPixelToUnit(XPos),'f',GetParamGlobal()->SmallNumberFigure)
							   +QString(/**/",")
							   +QString::number(GetParamGlobal()->TransformPixelToUnit(YPos),'f',GetParamGlobal()->SmallNumberFigure);
				item = new QTableWidgetItem(xyStr);
			}
			ui.tblMain->setItem(InsertRow+i, mainHHeader.indexOf(hhlNGPoint), item);
		}
		
		// INSLIB情報
		if(mainHHeader.contains(hhlNGCause)==true){
			if(InsLibHash.isEmpty()==false){
				QString LibName = /**/"";
				QList<InsLibraryItem> list = InsLibHash.values(NGItem.getLibraryRal());

				for(QList<InsLibraryItem>::Iterator LibItem=list.begin(); LibItem!=list.end(); LibItem++){
					if(LibItem->LibCode==NGItem.getLibraryCode()){
						LibName = LibItem->LibName;
						break;
					}
				}
				item = new QTableWidgetItem(LibName);
				ForSaveNGPointer->Cause=LibName;
			}else{
				item = new QTableWidgetItem();
			}
			ui.tblMain->setItem(InsertRow+i, mainHHeader.indexOf(hhlNGCause), item);
		}

		// NG数
		if(mainHHeader.contains(hhlNGCount)==true){
			item = new QTableWidgetItem(QString::number(NGItem.NGPointList.count()));
			ui.tblMain->setItem(InsertRow+i, mainHHeader.indexOf(hhlNGCount), item);
		}

		// NG原因
		if(mainHHeader.contains(hhlLibrary)==true){
			item = new QTableWidgetItem(NGItem.getLibraryRal());
			ui.tblMain->setItem(InsertRow+i, mainHHeader.indexOf(hhlLibrary), item);
		}

		// PCE情報
		if(mainHHeader.contains(hhlNGArea)==true){
			QStringList NGIPCE;
			for(int ng=0; ng<NGItem.NGPointList.count(); ng++){
				for(int pci=0; pci<NGItem.NGPointList[ng].PCEItems.count(); pci++){
					if(NGIPCE.contains(NGItem.NGPointList[ng].PCEItems[pci].pieceName())==false){
						NGIPCE.append(NGItem.NGPointList[ng].PCEItems[pci].pieceName());
					}
				}
			}

			QString RowPCEStr;
			if(NGIPCE.isEmpty()==false){
				RowPCEStr.append(NGIPCE.first());
				for(int pci=1; pci<NGIPCE.count(); pci++){
					RowPCEStr.append(NGIPCE[pci]);
				}
			}

			item = new QTableWidgetItem(RowPCEStr);
			ui.tblMain->setItem(InsertRow+i, mainHHeader.indexOf(hhlNGArea), item);
		}
	}

	// 色付け
	if(RBase!=NULL){
		CmdReqFKeyColorList Send(GetLayersBase());
		RBase->TransmitDirectly(&Send);
		for(int i=0; i<NGList.count(); i++){
			NGNailItem NGItem = NGList.at(i);// NG画像単位情報
			if(NGItem.isChecked){
				fillBackgraundColorOnTableAtRow(InsertRow+i, Send.list[Review::FKeyToInt(NGItem.FKey)]);
			}else{
				fillBackgraundColorOnTableAtRow(InsertRow+i, QColor(Qt::white));
			}
		}
	}else{
		for(int i=0; i<NGList.count(); i++){
			fillBackgraundColorOnTableAtRow(InsertRow+i, QColor(Qt::white));
		}
	}
	RBase->TransmitDirectly(&hCmdReqForSaveNGList);
}

void NGImageListForReview::TransmitDirectly(GUIDirectMessage *packet)
{
	// 更新
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase!=NULL){
			updateGUI();
			GUICmdReviewUpdateLocalVar->Ret = true;
		}else{
			GUICmdReviewUpdateLocalVar->Ret = false;
		}
		return;
	}

	GUICmdUpdateCurrentHistory *GUICmdUpdateCurrentHistoryVar = dynamic_cast<GUICmdUpdateCurrentHistory *>(packet);
	if(GUICmdUpdateCurrentHistoryVar!=NULL){
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase!=NULL){
			updateGUI();
		}
		return;
	}

	GUICmdSetFocus *GUICmdSetFocusVar = dynamic_cast<GUICmdSetFocus *>(packet);
	if(GUICmdSetFocusVar!=NULL){
		ui.tblMain->setFocus();
		return;
	}
	
	ReviewCommonPacket::CmdReqSettingPropertyDialog *CmdReqSettingPropertyDialogVar = dynamic_cast<ReviewCommonPacket::CmdReqSettingPropertyDialog *>(packet);
	if(CmdReqSettingPropertyDialogVar!=NULL){
		CmdReqSettingPropertyDialogVar->setDialog(getPropertyDialog());
		CmdReqSettingPropertyDialogVar->setGroupName(ReviewGUI::PropertyGroupName::Standard);
		CmdReqSettingPropertyDialogVar->setGUIName(ReviewGUI::Name::NGImageListForReview);
		return;
	}
}
void	NGImageListForReview::Terminated(void)
{
	CmdUpdateForSaveLotList	UpdateForSaveLotCmd(GetLayersBase());
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		RBase->TransmitDirectly( &UpdateForSaveLotCmd );
	}
}

bool NGImageListForReview::removeFKey(QColor &afterColor)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdClearFKeyToNGNail Send(GetLayersBase());
		RBase->TransmitDirectly(&Send);
		afterColor = Send.CheckedColor;

		CmdRemoveFKeyForSave RemoveSend(GetLayersBase());
		RBase->TransmitDirectly(&RemoveSend);

		return Send.Ret;
	}
	return false;
}

void NGImageListForReview::fillBackgraundColorOnTableAtRow(int row, QColor color)
{
	if(row>=0 && ui.tblMain->rowCount()>row && ui.tblMain->columnCount()>0){
		for(int i=0; i<ui.tblMain->columnCount(); i++){
			if(ui.tblMain->item(row, i)!=NULL){
				ui.tblMain->item(row, i)->setBackgroundColor(color);
			}
		}
	}
}

void NGImageListForReview::startKeyWaitTimeLine(int interval){
	keyWaitTimeLine->stop();
	if(interval>0){
		ui.progKeyWait->setValue(0);

		keyWaitTimeLine->setCurrentTime(0);
		keyWaitTimeLine->setDuration(interval);
		keyWaitTimeLine->start();
	}else{
		ui.progKeyWait->setValue( ui.progKeyWait->maximum() );
	}
}

void NGImageListForReview::endKeyWaitTimeLine(int value)
{
	if(value==ui.progKeyWait->maximum()){
		//setGUIEnable(true);
		setKeyPressedState(false);
		
		GUICmdSetEnable SetEnableCmd(GetLayersBase());
		SetEnableCmd.enable = true;

//		GUIFormBase *Base;
//		Base = GetReviewGUIForm(ReviewGUI::Name::ListMasterDataAndLoad);
//		if(Base!=NULL)Base->TransmitDirectly(&SetEnableCmd);
//		Base = GetReviewGUIForm(ReviewGUI::Name::SelectLotForReview);
//		if(Base!=NULL)Base->TransmitDirectly(&SetEnableCmd);
//		Base = GetReviewGUIForm(ReviewGUI::Name::ShowHistoryListForReview);
//		if(Base!=NULL)Base->TransmitDirectly(&SetEnableCmd);

		ui.tblMain->setFocus();
	}else if(ui.tblMain->isEnabled()==true){
		//setGUIEnable(false);

		GUICmdSetEnable SetEnableCmd(GetLayersBase());
		SetEnableCmd.enable = false;

//		GUIFormBase *Base;
//		Base = GetReviewGUIForm(ReviewGUI::Name::ListMasterDataAndLoad);
//		if(Base!=NULL)Base->TransmitDirectly(&SetEnableCmd);
//		Base = GetReviewGUIForm(ReviewGUI::Name::SelectLotForReview);
//		if(Base!=NULL)Base->TransmitDirectly(&SetEnableCmd);
//		Base = GetReviewGUIForm(ReviewGUI::Name::ShowHistoryListForReview);
//		if(Base!=NULL)Base->TransmitDirectly(&SetEnableCmd);

		ui.tblMain->setFocus();
	}else{
		// 特に何も
	}
}

void NGImageListForReview::setGUIEnable(bool enable)
{
	ui.tblMain->setEnabled(enable);
}

void NGImageListForReview::setCurrentRow(int row)
{
	ui.tblMain->setCurrentCell(row, 0);

	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdSetCurrentRowNGListForSave Send(GetLayersBase());
		Send.CurrentRow=row;
		RBase->TransmitDirectly(&Send);
	}
}

int NGImageListForReview::currentRow()
{
	return ui.tblMain->currentRow();
}

void NGImageListForReview::moveHistory(Review::Direction direction)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	CmdReqAdjacentCurrentNG	ExistNGCmd(GetLayersBase());		// カレントNGの周囲に関する情報取得コマンド
	CmdMoveCurrentHistoryToNGBoard	HistoryMoveCmd(GetLayersBase());	// 履歴移動用コマンド

	RBase->TransmitDirectly(&ExistNGCmd);// カレントNGの周辺情報を取得

	bool isExistHistory;
	if(direction==Review::Direction::Next){
		isExistHistory = ExistNGCmd.existNextHistory();
	}else{
		isExistHistory = ExistNGCmd.existPreviousHistory();
	}

	if(ExistNGCmd.Ret==true && isExistHistory==true){

		// will recommand
		//if(ExistNGCmd.currentHistory->isErrorBoard()==false &&// 通常の結果限定
		//	ExistNGCmd.currentHistory->isCheckedAll()==false)return;// すべてチェック済みでないので次にはいけない
		
		HistoryMoveCmd.direction = direction;// 履歴移動を次の方向に設定
		RBase->TransmitDirectly(&HistoryMoveCmd);// 履歴を次へ移動

		if(HistoryMoveCmd.Ret==false)return;
		if(ExistNGCmd.currentHistory()==HistoryMoveCmd.CurrentHistoryPtr)return;

		// NGNail位置を先頭へ移動
		CmdSetCurrentNGNail SetNGPosCmd(GetLayersBase());
		SetNGPosCmd.locate = Review::First;
		RBase->TransmitDirectly(&SetNGPosCmd);
		
		if(SetNGPosCmd.Ret==true){
			setCheckedCurrentNG();// カレントNGをチェック済みにする
		}

		//updateGUI();

		GUICmdUpdateCurrentHistory Cmd(GetLayersBase());
		GUIFormBase *Base = GetReviewGUIForm(ReviewGUI::Name::ShowHistoryListForReview);
		if(Base!=NULL){
			Base->TransmitDirectly(&Cmd);
		}

		ReviewGUI::UpdateHistoryGUI(GetLayersBase(), ReviewGUI::Name::WholeImageForReview);

		updateGUI();
		return;
	}
}

void NGImageListForReview::cellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	//if(currentRow==-1 || currentColumn==-1 || previousRow==-1 || previousColumn==-1)return;
	if(currentRow==-1 || currentColumn==-1)	return;

	ReviewPIBase *RBase = GetReviewAlgorithm();

	SeqControlParam	*Param=NULL;
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
	}
	if(currentRow<FrontCount){
		if(Param!=NULL){
			Param->Side	=1;
		}
	}
	else if(currentRow<(FrontCount+BackCount)){
		if(Param!=NULL){
			Param->Side	=2;
		}
	}
	else{
		if(Param!=NULL){
			Param->Side	=0;
		}
	}
	if(RBase!=NULL){
		CmdSetCurrentNGNail Send(GetLayersBase());
		Send.refType = Review::Ref_Index;
		Send.locate = Review::Manual;
		Send.Index = currentRow;
		
		RBase->TransmitDirectly(&Send);
		if(Send.Ret==true){
			if(setCheckedCurrentNG()==true){
				fillBackgraundColorOnTableAtRow(currentRow, getCurrentNGColor());
			}
			
			GUIFormBase *FBase = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::WholeImageForReview, /**/"");
			if(FBase!=NULL){
				GUICmdUpdateCurrentNGNail UpdateNGCmd(GetLayersBase());
				FBase->TransmitDirectly(&UpdateNGCmd);
			}

			ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ShowThumbnail);
			ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);
		}else{
			ui.tblMain->setCurrentCell(previousRow, previousColumn);
		}

		CmdResetDiffVRS DiffSend(GetLayersBase());
		RBase->TransmitDirectly(&DiffSend);

		CmdMovePosition	RCmd(GetLayersBase());
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"AutofocusChuo" ,/**/"");
		if(GProp!=NULL){
			GProp->TransmitDirectly(&RCmd);
		}
		setCurrentRow(currentRow);
	}
}

bool NGImageListForReview::setCheckedCurrentNG()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return false;

	CmdReqAdjacentCurrentNG ngCheckCmd(GetLayersBase());
	RBase->TransmitDirectly(&ngCheckCmd);

	if(ngCheckCmd.existCurrentNG()==true){
		if(ngCheckCmd.currentNG()->isChecked==false){
			startKeyWaitTimeLine(getNextListDelay());
		}
	}

	CmdSetCurrentNGChecked SetNGIsChecked(GetLayersBase());
	RBase->TransmitDirectly(&SetNGIsChecked);

	GUIFormBase *Base = GetReviewGUIForm(ReviewGUI::Name::ShowHistoryListForReview);
	if(Base!=NULL){
		GUICmdUpdateCurrentHistoryChecked Send(GetLayersBase());
		Base->TransmitDirectly(&Send);
	}

	return SetNGIsChecked.Ret;
}

QColor NGImageListForReview::getCurrentNGColor()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return QColor(Qt::white);

	CmdReqAdjacentCurrentNG AdjacentCurrentNGCmd(GetLayersBase());
	RBase->TransmitDirectly(&AdjacentCurrentNGCmd);

	QColor ret = QColor(Qt::white);// デフォルトは白

	if(AdjacentCurrentNGCmd.currentNG()->isChecked==true){
		CmdReqFKeyColorList ReqFColorListCmd(GetLayersBase());
		RBase->TransmitDirectly(&ReqFColorListCmd);

		if(ReqFColorListCmd.Ret==true){
			ret = ReqFColorListCmd.list[Review::FKeyToInt(AdjacentCurrentNGCmd.currentNG()->FKey)];// Fキーに応じた色(Fキー無しも含む)
		}
	}

	return ret;
	
}
