#include "DisplayImageResource.h"
#define	_USE_MATH_DEFINES
#include <QMessageBox>
#include <QMenu>
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XTypeDef.h"
#include "XCrossObj.h"
#include "SelectPasteForm.h"
#include "XGeneralDialog.h"
#include "SelectItemForm.h"
#include "SelectByLibraryDialog.h"
#include "ExpandedPasteForm.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include <math.h>
#include "SelectPages.h"
#include "MoveImageForm.h"
#include "SelectByOrigin.h"
#include "SelectMovePastePage.h"
#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "SaveImageOnPointDialog.h"
#include "RegulateBrightnessForm.h"
#include "XGeneralStocker.h"
#include "mtImageToolButtonWithBalloon.h"
#include "mtImageToolButtonColored.h"
#include "swap.h"
#include "InputRotate.h"
#include "InputMirror.h"
#include "SelectOneItemForm.h"
#include "EditItemNameDialog.h"
#include "SetectSearchItemDialog.h"
#include "SelectPageItemDialog.h"
#include "XDataInLayerToDisplayImage.h"
#include "XGUIPacketGeneral.h"
#include "ShrinkItemDialog.h"
#include "SelectLibraryForm.h"
#include "SelectLibraryInListDialog.h"
#include "XAlgorithmBase.h"
#include "MakeOutlineItemDialog.h"
#include <omp.h>

//========================================================================
DisplayImageWithAlgorithm::DisplayImageWithAlgorithm(LayersBase *LBase
							,const QString &algoRoot ,const QString &algoName
							,const QString &emitterRoot ,const QString &emitterName,DisplayType dtype
							,QWidget *parent)
:DisplayImage(LBase,emitterRoot ,emitterName,dtype,parent)
{
	ItemsBmpCounts				=0;
	ItemsBmpReceiver			=NULL;
	ItemsBmpRequester			=NULL;
	CmdReqTemporaryItems		=NULL;
	CmdAckTemporaryItems		=NULL;
	EnableOutsideItems			=true;

	AlgoRoot		=algoRoot;
	AlgoName		=algoName;
	NoneBtn			=NULL;
	DrawBtn			=NULL;
	SelectBtn		=NULL;
	SelectMenuBtn	=NULL;
	CutItemBtn		=NULL;
	MoveItemBtn		=NULL;
	DeleteBtn		=NULL;
	LockBtn			=NULL;
	GroupBtn		=NULL;
	CopyBtn			=NULL;
	PasteBtn		=NULL;
	RegistAreaBtn	=NULL;
	VisibleMenuBtn	=NULL;
	RotateBtn		=NULL;
	MirrorBtn		=NULL;
	UncoveredBtn	=NULL;
	ItemMenuBtn		=NULL;
	MultiSelectBtn	=NULL;
	SeparateItemBtn	=NULL;

	ActionSelectAll	=NULL;
	ActionCopy		=NULL;
	ActionPaste		=NULL;
	ActionDelete	=NULL;

	AlgoOptions.DrawBtn			=true;
	AlgoOptions.SelectBtn		=true;
	AlgoOptions.SelectMenuBtn	=true;
	AlgoOptions.CutItemBtn		=true;
	AlgoOptions.MoveItemBtn		=true;
	AlgoOptions.DeleteBtn		=true;
	AlgoOptions.LockBtn			=true;
	AlgoOptions.GroupBtn		=true;
	AlgoOptions.CopyBtn			=true;
	AlgoOptions.PasteBtn		=true;
	AlgoOptions.RegistAreaBtn	=true;
	AlgoOptions.VisibleMenuBtn	=true;
	AlgoOptions.RotateBtn		=true;
	AlgoOptions.MirrorBtn		=true;
	AlgoOptions.UncoveredBtn	=true;
	AlgoOptions.ItemMenuBtn		=true;
	AlgoOptions.MultiSelectBtn	=false;
	AlgoOptions.SeparateItemBtn	=false;

	EnableMultiSelection.EnableMultiSelectInDraw	=true;
	EnableMultiSelection.EnableMultiSelectInCut		=true;
	EnableMultiSelection.EnableMultiSelectInMove	=true;
	EnableMultiSelection.EnableMultiSelectInDelete	=true;
	EnableMultiSelection.EnableMultiSelectInLock	=true;
	EnableMultiSelection.EnableMultiSelectInCopy	=true;
	EnableMultiSelection.EnableMultiSelectInRotate	=true;
	EnableMultiSelection.EnableMultiSelectInMirror	=true;

	WBar.setParent(this);
	WBar.move(0,0);

	AllocInnerBuffWithAlgorithm();

	LastMode=Mode_None;
	ItemTunableList.append(/**/"DrawBtn");
	ItemTunableList.append(/**/"SelectBtn");
	ItemTunableList.append(/**/"SelectMenuBtn");
	ItemTunableList.append(/**/"CutItemBtn");
	ItemTunableList.append(/**/"MoveItemBtn");
	ItemTunableList.append(/**/"DeleteBtn");
	ItemTunableList.append(/**/"LockBtn");
	ItemTunableList.append(/**/"GroupBtn");
	ItemTunableList.append(/**/"CopyBtn");
	ItemTunableList.append(/**/"PasteBtn");
	ItemTunableList.append(/**/"RegistAreaBtn");
	ItemTunableList.append(/**/"VisibleMenuBtn");
	ItemTunableList.append(/**/"RotateBtn");
	ItemTunableList.append(/**/"MirrorBtn");
	ItemTunableList.append(/**/"UncoveredBtn");
	ItemTunableList.append(/**/"ItemMenuBtn");
	ItemTunableList.append(/**/"MultiSelectBtn");
	ItemTunableList.append(/**/"SeparateItemBtn");
}

void	DisplayImageWithAlgorithm::AllocInnerBuffWithAlgorithm(void)
{
	if(ItemsBmpCounts==GetLayersBase()->GetPageNumb())
		return;
	if(ItemsBmpCounts>0){
		for(int i=0;i<ItemsBmpCounts;i++){
			delete	ItemsBmpRequester[i];
			delete	ItemsBmpReceiver[i];
			delete	CmdReqTemporaryItems[i];
			delete	CmdAckTemporaryItems[i];
		}
		delete	[]ItemsBmpRequester;
		delete	[]ItemsBmpReceiver;
		delete	[]CmdReqTemporaryItems;
		delete	[]CmdAckTemporaryItems;
	}
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
		ItemsBmpCounts=GetLayersBase()->GetPageNumb();
		ItemsBmpReceiver=new GUICmdSendItemsBmp*[ItemsBmpCounts];
		ItemsBmpRequester=new GUICmdReqItemsBmp*[ItemsBmpCounts];
		CmdReqTemporaryItems		=new GUICmdReqTemporaryItems*[ItemsBmpCounts];
		CmdAckTemporaryItems		=new GUICmdAckTemporaryItems*[ItemsBmpCounts];

		for(int page=0;page<ItemsBmpCounts;page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			ItemsBmpReceiver[page]=new GUICmdSendItemsBmp(Base,EmitterRoot,EmitterName,globalPage);
			ItemsBmpRequester[page]=new GUICmdReqItemsBmp(this,Base,EmitterRoot,EmitterName,globalPage);		
			CmdReqTemporaryItems[page]		=new GUICmdReqTemporaryItems(this,Base,EmitterRoot,EmitterName,globalPage);
			CmdAckTemporaryItems[page]		=new GUICmdAckTemporaryItems(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		}
	}
}

DisplayImageWithAlgorithm::~DisplayImageWithAlgorithm(void)
{
	disconnect(this,SLOT(DrawNoneBtnBtnDown()));
	disconnect(this,SLOT(DrawBtnDown()));
	disconnect(this,SLOT(SelectBtnDown()));
	disconnect(this,SLOT(SelectMenuBtnDown()));
	disconnect(this,SLOT(CutItemBtnDown()));
	disconnect(this,SLOT(MoveItemBtnDown()));
	disconnect(this,SLOT(DeleteBtnDown()));
	disconnect(this,SLOT(LockBtnDown()));
	disconnect(this,SLOT(GroupBtnDown()));
	disconnect(this,SLOT(CopyBtnDown()));
	disconnect(this,SLOT(PasteBtnDown()));
	disconnect(this,SLOT(RegistAreaBtnDown()));
	disconnect(this,SLOT(VisibleMenuBtnDown()));
	disconnect(this,SLOT(RotateBtnDown()));
	disconnect(this,SLOT(MirrorBtnDown()));
	disconnect(this,SLOT(UncoveredBtnDown()));
	disconnect(this,SLOT(ItemMenuBtnDown()));
	disconnect(this,SLOT(MultiSelectBtnDown()));
	disconnect(this,SLOT(SeparateItemBtnDown()));

	disconnect(this, SLOT(SlotSelectAll()));
	disconnect(this, SLOT(CopyBtnDown()));
	disconnect(this, SLOT(PasteBtnDownFromShortcut()));
	disconnect(this, SLOT(DeleteBtnDown()));

	for(int i=0;i<ItemsBmpCounts;i++){
		delete	ItemsBmpRequester[i];
		delete	ItemsBmpReceiver[i];
		delete	CmdReqTemporaryItems[i];
		delete	CmdAckTemporaryItems[i];
	}
	delete	[]ItemsBmpRequester;
	delete	[]ItemsBmpReceiver;
	delete	[]CmdReqTemporaryItems;
	delete	[]CmdAckTemporaryItems;

	ItemsBmpRequester	=NULL;
	ItemsBmpReceiver	=NULL;

	if(NoneBtn!=NULL){
		delete	NoneBtn;
		NoneBtn	=NULL;
	}
	if(DrawBtn!=NULL){
		delete	DrawBtn;
		DrawBtn	=NULL;
	}
	if(SelectBtn!=NULL){
		delete	SelectBtn;
		SelectBtn		=NULL;
	}
	if(SelectMenuBtn!=NULL){
		delete	SelectMenuBtn;
		SelectMenuBtn=NULL;
	}
	if(CutItemBtn!=NULL){
		delete	CutItemBtn;
		CutItemBtn		=NULL;
	}
	if(MoveItemBtn!=NULL){
		delete	MoveItemBtn;
		MoveItemBtn		=NULL;
	}
	if(DeleteBtn!=NULL){
		delete	DeleteBtn;
		DeleteBtn		=NULL;
	}
	if(LockBtn!=NULL){
		delete	LockBtn;
		LockBtn			=NULL;
	}
	if(GroupBtn!=NULL){
		delete	GroupBtn;
		GroupBtn		=NULL;
	}
	if(CopyBtn!=NULL){
		delete	CopyBtn;
		CopyBtn			=NULL;
	}
	if(PasteBtn!=NULL){
		delete	PasteBtn;
		PasteBtn		=NULL;
	}
	if(RegistAreaBtn!=NULL){
		delete	RegistAreaBtn;
		RegistAreaBtn	=NULL;
	}
	if(VisibleMenuBtn!=NULL){
		delete	VisibleMenuBtn;
		VisibleMenuBtn	=NULL;
	}
	if(RotateBtn!=NULL){
		delete	RotateBtn;
		RotateBtn	=NULL;
	}
	if(MirrorBtn!=NULL){
		delete	MirrorBtn;
		MirrorBtn	=NULL;
	}
	if(UncoveredBtn!=NULL){
		delete	UncoveredBtn;
		UncoveredBtn	=NULL;
	}
	if(ItemMenuBtn!=NULL){
		delete	ItemMenuBtn;
		ItemMenuBtn=NULL;
	}
	if(MultiSelectBtn!=NULL){
		delete	MultiSelectBtn;
		MultiSelectBtn	=NULL;
	}
	if(SeparateItemBtn!=NULL){
		delete	SeparateItemBtn;
		SeparateItemBtn	=NULL;
	}

	if(ActionSelectAll!=NULL){
		delete	ActionSelectAll;
		ActionSelectAll	=NULL;
	}
	if(ActionCopy!=NULL){
		delete	ActionCopy;
		ActionCopy		=NULL;
	}
	if(ActionPaste!=NULL){
		delete	ActionPaste;
		ActionPaste		=NULL;
	}
	if(ActionDelete!=NULL){
		delete	ActionDelete;
		ActionDelete	=NULL;
	}
}
bool	DisplayImageWithAlgorithm::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	DisplayImage::Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
	AllocInnerBuffWithAlgorithm();
}
bool	DisplayImageWithAlgorithm::InsertPage(int IndexPage)	//Create page before Indexed page
{
	DisplayImage::InsertPage(IndexPage);
	AllocInnerBuffWithAlgorithm();
}
bool	DisplayImageWithAlgorithm::RemovePage(int IndexPage)
{
	DisplayImage::RemovePage(IndexPage);
	AllocInnerBuffWithAlgorithm();
}

AlgorithmBase	*DisplayImageWithAlgorithm::GetAlgorithmBase(void)	const
{
	AlgorithmBase	*ret=GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	if(ret==NULL){
		QMessageBox::critical ( NULL
								, LangDISolver.GetString(XDisplayImage_LS,LID_24)/*"Error"*/
								, LangDISolver.GetString(XDisplayImage_LS,LID_25)/*"GetAlgorithmBase returns NULL Root("*/
									+AlgoRoot
									+QString(/**/")+Name(")
									+AlgoName
									+QString(/**/")"));
		return NULL;
	}
	return ret;
}

int		DisplayImageWithAlgorithm::GetButtonIndex(const QString &IconStr)	const
{
	for(int i=0;i<ShownButtons.count();i++){
		if(ShownButtons[i]==IconStr){
			return i;
		}
	}
	return -1;
}

void	DisplayImageWithAlgorithm::InsertIconButton(const QString &BeforeIcon,QWidget *b)
{
	int	Index=GetButtonIndex(BeforeIcon);
	if(Index>=0){
		QList<QAction *> L=IBar.actions();
		if(Index<L.count()){
			QAction *a=L[Index];
			IBar.insertWidget(a,b);
		}
		else if(L.count()!=0){
			QAction *a=L[0];
			IBar.insertWidget(a,b);
		}
		else{
			IBar.addWidget(b);
		}
	}
	else{
		QList<QAction *> L=IBar.actions();
		if(L.count()!=0){
			QAction *a=L[0];
			IBar.insertWidget(a,b);
		}
		else{
			IBar.addWidget(b);
		}
	}
}


void	DisplayImageWithAlgorithm::AllUpToolButton(void)
{
	if(NoneBtn!=NULL){
		NoneBtn->setChecked(true);
	}
}

void	DisplayImageWithAlgorithm::PushDrawItemButton(void)
{
	if(DrawBtn!=NULL){
		DrawBtn->setChecked(true);
	}
}

void	DisplayImageWithAlgorithm::SelectArea(IntList &LayerList, FlexArea &Area)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectItems	hCmd(GetAlgorithmBase(),EmitterRoot ,EmitterName,globalPage);
		hCmd.Area	=Area;
		hCmd.Phase	=ShowFixedPhase;
		hCmd.MultiSelect	=GetMultiSelect();
		if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(hCmd.Area)==true){
			hCmd.LayerList=LayerList;
			if(hCmd.SendOnly(globalPage ,0)==false){
				SetError(Error_Comm , /**/"Send error :SelectArea",ErrorCodeList::_Alart);
			}
		}
	}
}

void	DisplayImageWithAlgorithm::ExeSelectItems(FlexArea &Area)
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);
                
	ExecuteReleaseAllSelection();
	SelectArea(LayerList, Area);
}

void	DisplayImageWithAlgorithm::ExeCutItems(FlexArea &Area)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base==NULL){
		return;
	}
	IntList	LayerList;
	GetActiveLayerList(LayerList);
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Cut items");
                             
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdCutItems	Cmd(Base,EmitterRoot ,EmitterName,globalPage);
		Cmd.Area	=Area;
		Cmd.Phase	=ShowFixedPhase;
		Cmd.MultiSelect	=GetMultiSelect();
		if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(Cmd.Area)==true){
			Cmd.LayerList=LayerList;
			if(Cmd.SendOnly(globalPage ,0)==false){
				SetError(Error_Comm , /**/"Send error :ExeCutItems",ErrorCodeList::_Alart);
			}
		}
	}
}

void	DisplayImageWithAlgorithm::SeparateItems(FlexArea &Area)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base==NULL){
		return;
	}
	IntList	LayerList;
	GetActiveLayerList(LayerList);
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Separate items");
                             
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSeparateItems	Cmd(Base,EmitterRoot ,EmitterName,globalPage);
		Cmd.Area	=Area;
		Cmd.Phase	=ShowFixedPhase;
		if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(Cmd.Area)==true){
			Cmd.LayerList=LayerList;
			if(Cmd.SendOnly(globalPage ,0)==false){
				SetError(Error_Comm , /**/"Send error :ExeCutItems",ErrorCodeList::_Alart);
			}
		}
	}
}

void	DisplayImageWithAlgorithm::CanvasSlotDrawEnd(void)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base==NULL){
		return;
	}
	if(MainCanvas!=NULL){
		if(SelectBtn!=NULL && SelectBtn->isChecked()==true){
			FlexArea resultarea;
			ToFlexArea( *GetRawSDataPoint(),resultarea);
			ExeSelectItems(resultarea);
			MainCanvas->Clear();
			if(LastMode==Mode_None){
				ExecuteClickButton(/**/"NoneBtn");
				//DrawNoneBtnBtnDown();
			}
			else if(LastMode==Mode_DrawBtn){
				ExecuteClickButton(/**/"DrawBtn");
				//DrawBtnDown();
			}
			else if(LastMode==Mode_CutItemBtn){
				ExecuteClickButton(/**/"CutItemBtn");
				//CutItemBtnDown();
			}
			else if(LastMode==Mode_MoveItemBtn){
				ExecuteClickButton(/**/"MoveItemBtn");
				//MoveItemBtnDown();
			}
			else if(LastMode==Mode_RegistAreaBtn){
				ExecuteClickButton(/**/"RegistAreaBtn");
				//RegistAreaBtnDown();
			}
		}
		else if(CutItemBtn!=NULL && CutItemBtn->isChecked()==true){
			FlexArea resultarea;
			ToFlexArea( *GetRawSDataPoint(),resultarea);
			if(0<=GetShowOnePage() && GetShowOnePage()<GetPageNumb()){
				DataInPage *P=GetLayersBase()->GetPageData(GetShowOnePage());
				resultarea.MoveToNoClip(P->GetOutlineOffset()->x,P->GetOutlineOffset()->y);
			}
			ExeCutItems(resultarea);
			MainCanvas->Clear();
		}
		else if(RegistAreaBtn!=NULL && RegistAreaBtn->isChecked()==true){
			FlexArea resultarea;
			ToFlexArea(*GetRawSDataPoint(),resultarea);
			if(0<=GetShowOnePage() && GetShowOnePage()<GetPageNumb()){
				DataInPage *P=GetLayersBase()->GetPageData(GetShowOnePage());
				resultarea.MoveToNoClip(P->GetOutlineOffset()->x,P->GetOutlineOffset()->y);
			}
			IntList	LayerList;
			GetActiveLayerList(LayerList);
		                         
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdRegistArea	Cmd(Base,EmitterRoot ,EmitterName,globalPage);
				Cmd.Area=resultarea;
				if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(Cmd.Area)==true){
					Cmd.LayerList=LayerList;
					if(Cmd.SendOnly(globalPage ,0)==false){
						SetError(Error_Comm , /**/"Send error :CanvasSlotDrawEnd",ErrorCodeList::_Alart);
					}
				}
			}
			MainCanvas->Clear();
		}
		else if(SeparateItemBtn!=NULL && SeparateItemBtn->isChecked()==true){
			FlexArea resultarea;
			ToFlexArea( *GetRawSDataPoint(),resultarea);
			if(0<=GetShowOnePage() && GetShowOnePage()<GetPageNumb()){
				DataInPage *P=GetLayersBase()->GetPageData(GetShowOnePage());
				resultarea.MoveToNoClip(P->GetOutlineOffset()->x,P->GetOutlineOffset()->y);
			}
			SeparateItems(resultarea);
			MainCanvas->Clear();
		}
		else{
			DisplayImage::CanvasSlotDrawEnd();
		}
	}
	ExecuteAfterDrawEnd();
	SetAlterSomething();
	Repaint();
}
//void	DisplayImageWithAlgorithm::CanvasSlotOnPaint(QPainter &pnt)
//{
//	DisplayImage::CanvasSlotOnPaint(pnt);
//}
void	DisplayImageWithAlgorithm::MouseMoveEvent(int globalX ,int globalY)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		if(GetLayersBase()->GetSendingData(globalPage)==true){
			return;
		}
	}
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base==NULL){
		return;
	}
	if(DrawingMode==_PasteMovePreStart){
	}
	else if(DrawingMode==_ItemMoveWait){
	}
	else if(DrawingMode==_CutByShapePreStart){
	}
	else
	if(DrawingMode==_PasteMove 
	|| DrawingMode==_ItemMove
	|| DrawingMode==_RotateMoveAngling 
	|| DrawingMode==_SlopeXMoveAngling 
	|| DrawingMode==_SlopeYMoveAngling 
	|| DrawingMode==_ExtendMoving 
	|| DrawingMode==_CutByShape){
		MoveCurrentGlobalX=globalX;
		MoveCurrentGlobalY=globalY;
		if(DrawingMode==_ItemMove){
			MovingNow(MoveCurrentGlobalX,MoveCurrentGlobalY);
		}
		else if(DrawingMode==_RotateMoveAngling){
			RotateAngling(MoveCurrentGlobalX,MoveCurrentGlobalY);
		}
		else if(DrawingMode==_SlopeXMoveAngling){
			SlopeXAngling(MoveCurrentGlobalX,MoveCurrentGlobalY);
		}
		else if(DrawingMode==_SlopeYMoveAngling){
			SlopeYAngling(MoveCurrentGlobalX,MoveCurrentGlobalY);
		}
		else if(DrawingMode==_ExtendMoving){
			ExtendingNow(MoveCurrentGlobalX,MoveCurrentGlobalY);
		}
	}
	else{
		ExecuteActiveOnItemXY(globalX ,globalY);
	}
	if(DrawingMode!=_Normal){
		MainCanvas->Repaint();
	}
}
void	DisplayImageWithAlgorithm::ExecuteActiveOnItemXY(int globalX ,int globalY)
{
	int	ActiveCount=0;
	if(ShowOnePage<0 || GetPageNumb()<=ShowOnePage){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int localX ,localY;
			GetLayersBase()->GetPageData(page)->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,localX ,localY);
			if(GetLayersBase()->GetPageData(page)->IsInclude(localX,localY)==true){
				ActiveCount++;
			}
		}
		if(ActiveCount!=0){
			IntList	LayerList;
			GetActiveLayerList(LayerList);
			ListPageLayerIDPack	ItemList;
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				int localX ,localY;
				GetLayersBase()->GetPageData(page)->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,localX ,localY);
				int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				AlgorithmBase	*Base=GetAlgorithmBase();
				GUICmdActivateOnItem		Cmd(Base,EmitterRoot ,EmitterName,globalPage);
				GUICmdSendActivateOnItem	AckCmd(Base,EmitterRoot ,EmitterName,globalPage);
				Cmd.LayerList=LayerList;
				Cmd.PosX=localX;
				Cmd.PosY=localY;
				if(GetLayersBase()->GetPageData(page)->IsInclude(localX,localY)==true){
					if(Cmd.Send(globalPage ,0,AckCmd)==false){
						SetError(Error_Comm , /**/"Send error :ExecuteActiveOnItemXY",ErrorCodeList::_Alart);
					}
				}
				else{
					if(Cmd.Send(globalPage ,1,AckCmd)==false){
						SetError(Error_Comm , /**/"Send error :ExecuteActiveOnItemXY",ErrorCodeList::_Alart);
					}
				}
				for(ListLayerAndID *a=AckCmd.ItemList.GetFirst();a!=NULL;a=a->GetNext()){
					ItemList.AppendList(new ListPageLayerID(page,a->Layer,a->ID));
				}
			}
			if(ItemList.GetNumber()!=0){
				emit	TouchItems(&ItemList);
			}
		}
	}
	else{
		int localX ,localY;
		GetLayersBase()->GetPageData(ShowOnePage)->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,localX ,localY);
		if(GetLayersBase()->GetPageData(ShowOnePage)->IsInclude(localX,localY)==true){
			ActiveCount++;
		}
		if(ActiveCount!=0){
			IntList	LayerList;
			GetActiveLayerList(LayerList);
			ListPageLayerIDPack	ItemList;

			int localX ,localY;
			GetLayersBase()->GetPageData(ShowOnePage)->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,localX ,localY);
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(ShowOnePage);
			AlgorithmBase	*Base=GetAlgorithmBase();
			GUICmdActivateOnItem		Cmd(Base,EmitterRoot ,EmitterName,globalPage);
			GUICmdSendActivateOnItem	AckCmd(Base,EmitterRoot ,EmitterName,globalPage);
			Cmd.LayerList=LayerList;
			Cmd.PosX=localX;
			Cmd.PosY=localY;
			if(GetLayersBase()->GetPageData(ShowOnePage)->IsInclude(localX,localY)==true){
				if(Cmd.Send(globalPage ,0,AckCmd)==false){
					SetError(Error_Comm , /**/"Send error :ExecuteActiveOnItemXY",ErrorCodeList::_Alart);
				}
			}
			else{
				if(Cmd.Send(globalPage ,1,AckCmd)==false){
					SetError(Error_Comm , /**/"Send error :ExecuteActiveOnItemXY",ErrorCodeList::_Alart);
				}
			}
			for(ListLayerAndID *a=AckCmd.ItemList.GetFirst();a!=NULL;a=a->GetNext()){
				ItemList.AppendList(new ListPageLayerID(ShowOnePage,a->Layer,a->ID));
			}
			if(ItemList.GetNumber()!=0){
				emit	TouchItems(&ItemList);
			}
		}
	}
}
void	DisplayImageWithAlgorithm::ExecuteActiveOnItem(int globalPage ,int layer ,int itemID)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	GUICmdActivateOnItemDirect	Cmd(Base,EmitterRoot ,EmitterName,globalPage);
	Cmd.Layer=layer;
	Cmd.ItemID=itemID;
	if(Cmd.SendOnly(globalPage ,0)==false){
		SetError(Error_Comm , /**/"Send error :ExecuteActiveOnItem",ErrorCodeList::_Alart);
	}
}

DisplayImage::__DrawingMode	DisplayImageWithAlgorithm::GetImageDrawingMode(void)	const
{
	DisplayImage::__DrawingMode	Ret=DisplayImage::GetImageDrawingMode();
	if(MoveItemBtn!=NULL && MoveItemBtn->isChecked()==true){
		return DisplayImage::_ItemMoveWait;
	}
	if(MoveItemBtn!=NULL && MoveItemBtn->isChecked()==false && Ret==DisplayImage::_ItemMoveWait){
		return DisplayImage::_Normal;
	}

	return Ret;
}
DisplayImageWithAlgorithm::ButtonPushedButton		DisplayImageWithAlgorithm::GetButtonPushedButton(void)	const
{
	if(MoveItemBtn!=NULL && MoveItemBtn->isChecked()==true){
		return Mode_MoveItemBtn;
	}
	if(DrawBtn!=NULL && DrawBtn->isChecked()==true){
		return Mode_DrawBtn;
	}
	if(CutItemBtn!=NULL && CutItemBtn->isChecked()==true){
		return Mode_CutItemBtn;
	}
	if(RegistAreaBtn!=NULL && RegistAreaBtn->isChecked()==true){
		return Mode_RegistAreaBtn;
	}
	return Mode_None;
}
void	DisplayImageWithAlgorithm::ButtonExecuteDraw(void)
{
	AllUpImagePanel();
}

void	DisplayImageWithAlgorithm::ButtonExecuteSelectArea(void)
{
	AllUpImagePanel();
	SetAlterSomething();
}
void	DisplayImageWithAlgorithm::ButtonExecuteCutItem(void)
{
	AllUpImagePanel();
	SetAlterSomething();
}
void	DisplayImageWithAlgorithm::ButtonExecuteDeleteSelected(void)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
		IntList	LayerList;
		GetActiveLayerList(LayerList);
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Delete selected items");

		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdOperationDelete	Cmd(Base ,EmitterRoot ,EmitterName,globalPage);
			Cmd.LayerList=LayerList;
			Cmd.Phase	 =ShowFixedPhase;
			if(Cmd.SendOnly(globalPage ,0)==false){
				SetError(Error_Comm , /**/"Send error :ButtonExecuteDeleteSelected",ErrorCodeList::_Alart);
			}
		}
		BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
		SetAlterSomething();
	}
}
void	DisplayImageWithAlgorithm::ButtonExecuteLockSelected(void)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
		IntList	LayerList;
		GetActiveLayerList(LayerList);
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Lock selected items");

		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdOperationLock	Cmd(Base ,EmitterRoot ,EmitterName,globalPage);
			Cmd.LayerList=LayerList;
			if(Cmd.SendOnly(globalPage ,0)==false){
				SetError(Error_Comm , /**/"Send error :ButtonExecuteLockSelected",ErrorCodeList::_Alart);
			}
		}
		SetAlterSomething();
	}
}

void	DisplayImageWithAlgorithm::ButtonExecuteUnlockAll(void)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
		IntList	LayerList;
		GetActiveLayerList(LayerList);
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Unlock all");

		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdOperationUnlock	Cmd(Base ,EmitterRoot ,EmitterName,globalPage);
			Cmd.LayerList=LayerList;
			if(Cmd.SendOnly(globalPage ,0)==false){
				SetError(Error_Comm , /**/"Send error :ButtonExecuteUnlockAll",ErrorCodeList::_Alart);
			}
		}
		SetAlterSomething();
	}
}
void	DisplayImageWithAlgorithm::ButtonExecuteGroupSelected(void)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
		IntList	LayerList;
		GetActiveLayerList(LayerList);
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Group selected");

		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdOperationGroup	Cmd(Base ,EmitterRoot ,EmitterName,globalPage);
			Cmd.LayerList=LayerList;
			if(Cmd.SendOnly(globalPage ,0)==false){
				SetError(Error_Comm , /**/"Send error :ButtonExecuteGroupSelected",ErrorCodeList::_Alart);
			}
		}
		BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
		SetAlterSomething();
	}
}
void	DisplayImageWithAlgorithm::ButtonExecuteCopySelected(bool EnableDup)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
		IntList	LayerList;
		GetActiveLayerList(LayerList);
		XDateTime createdTime=XDateTime::currentDateTime();
		GetLayersBase()->ClearAllAckFlag();

		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdOperationCopy	Cmd(Base ,EmitterRoot ,EmitterName,globalPage);
			Cmd.CreatedTime=createdTime;
			Cmd.LayerList=LayerList;
			Cmd.EnableDup=EnableDup;
			if(Cmd.Send(NULL,globalPage,0)==false){
				SetError(Error_Comm , /**/"Send error :ButtonExecuteCopySelected",ErrorCodeList::_Alart);
			}
		}
		SetAlterSomething();
		GetLayersBase()->WaitAllAcknowledged(10*60*100);
	}
}

void	DisplayImageWithAlgorithm::ButtonExecutePasteInSameAlgorithm(void)
{
	//GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Paste in same algorithm");

	if(MainCanvas!=NULL){
		SetModeByOthers(mtFrameDraw::fdNone,MainCanvas->GetFrameColor());
	}
	DrawingMode=_PasteMovePreStart;
	MoveCurrentGlobalX=MoveStartGlobalX=0;
	MoveCurrentGlobalY=MoveStartGlobalY=0;
	AllUpToolButton();
	AllUpImagePanel();
}

void	DisplayImageWithAlgorithm::ButtonExecutePasteInSameAlgorithmSamePos(void)
{
	ExecuteReleaseAllSelection();
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Paste in same algorithm");
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdExecutePaste	Cmd(GetLayersBase(),GUICmdExecutePaste::_PurePaste,EmitterRoot,EmitterName ,GlobalPage);
		Cmd.InstName=GetName();
		Cmd.Dx=0;
		Cmd.Dy=0;
		Cmd.SamePage=true;
		if(Cmd.SendOnly(GlobalPage,0)==false){
			SetError(Error_Comm , /**/"Send error :_PasteMove",ErrorCodeList::_Alart);
		}
	}
	//DrawingMode=_Normal;
	DrawingMode=SavedDrawingMode;
	if(MainCanvas!=NULL){
		MainCanvas->Clear();
	}
	BroadcastDirectly(_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	if(MainCanvas!=NULL){
		StartMovx=MainCanvas->GetMovx();
		StartMovy=MainCanvas->GetMovy();
	}
}

void	DisplayImageWithAlgorithm::ButtonExecutePasteInFixedPos(void)
{
	//GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Paste in fexed position");

	if(MainCanvas!=NULL){
		SetModeByOthers(mtFrameDraw::fdNone,MainCanvas->GetFrameColor());
	}
	DrawingMode=_PasteCreateShapeStart;
	MoveCurrentGlobalX=MoveStartGlobalX=0;
	MoveCurrentGlobalY=MoveStartGlobalY=0;
	AllUpToolButton();
	AllUpImagePanel();
}

void	DisplayImageWithAlgorithm::ButtonExecuteCutByShape(void)
{
	//GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Cut by shape");

	if(MainCanvas!=NULL){
		SetModeByOthers(mtFrameDraw::fdNone,MainCanvas->GetFrameColor());
	}
	DrawingMode=_CutByShapePreStart;
	MoveCurrentGlobalX=MoveStartGlobalX=0;
	MoveCurrentGlobalY=MoveStartGlobalY=0;
	AllUpToolButton();
	AllUpImagePanel();
}

void	DisplayImageWithAlgorithm::ButtonExecutePaste(void)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
		IntList	LayerList;
		GetActiveLayerList(LayerList);
		SelectPasteForm	*PForm=new SelectPasteForm(this,Base->GetLayersBase());
		GeneralDialog	D(GetLayersBase(),PForm,this);
		D.exec();
		if(PForm->RetMode>0){
			if(PForm->RetMode==1){
				ButtonExecutePasteInSameAlgorithm();
			}
			else if(PForm->RetMode==2){
				ButtonExecutePasteInFixedPos();
			}
			else if(PForm->RetMode==3){
				DrawingMode=_Normal;
			}
			else if(PForm->RetMode==5){
				ButtonExecuteCutByShape();
			}
			else if(PForm->RetMode==6){
				SavedDrawingMode=DrawingMode;
				ButtonExecutePasteInSameAlgorithmSamePos();
			}
			else if(PForm->RetMode==16){
				SavedDrawingMode=DrawingMode;
				ButtonExecutePasteInSameAlgorithmSamePos();
			}
			BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
		}
		SetMaskPaint(0);
		Repaint();
		SetAlterSomething();
		delete	PForm;
	}
}

void	DisplayImageWithAlgorithm::ExpandedPasteExecuteInSameAlgorithm(ExpandedItemPosContainer &ExpandedItems)
{
	int	MinX=99999999;
	int	MaxX=-99999999;
	int	MinY=99999999;
	int	MaxY=-99999999;
	//for(ExpandedSelectedItemList *p=ExpandedPasteCurrent.SelectedItemLists.GetFirst();p!=NULL;p=p->GetNext()){
	for(int i=0;i<ExpandedPasteCurrent.SelectedItemLists.GetCount();i++){
		ExpandedSelectedItemList *p=ExpandedPasteCurrent.SelectedItemLists.Get(i);
		if(MinX>p->X1){
			MinX=p->X1;
		}
		if(MinY>p->Y1){
			MinY=p->Y1;
		}
		if(MaxX<p->X2){
			MaxX=p->X2;
		}
		if(MaxY<p->Y2){
			MaxY=p->Y2;
		}
	}

	QString emitterRoot;
	QString emitterName;
	QString AlgoRoot;
	QString AlgoName;
	IntList	LayerList;

	GetActiveLayerList(LayerList);
	GetIdentity(emitterRoot ,emitterName);
	GetAlgorithm(AlgoRoot,AlgoName);

	IntList PhaseList;
	if(GetParamGlobal()->CommonOperationInAllPhases==false){
		PhaseList.Add(GetLayersBase()->GetCurrentPhase());
	}
	else{
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PhaseList.Add(phase);
		}
	}

	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		IntList	*PageList	=new IntList[GetPageNumb()];
		ListPageLayerIDPack	*Items=new ListPageLayerIDPack[GetPageNumb()];
		int		DifferentPageCount=0;
		int	Row=0;
		for(ExpandedItemPos *p=ExpandedItems.GetFirst();p!=NULL;p=p->GetNext(),Row++){
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

				GUICmdReqMovedPage	RCmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
				int	cx=(p->Pos[0].X+p->Pos[1].X+p->Pos[2].X+p->Pos[3].X)/4;
				int	cy=(p->Pos[0].Y+p->Pos[1].Y+p->Pos[2].Y+p->Pos[3].Y)/4;
				RCmd.GlobalDx	=cx-(MinX+MaxX)/2;
				RCmd.GlobalDy	=cy-(MinY+MaxY)/2;
				RCmd.AlgoRoot	=AlgoRoot;
				RCmd.AlgoName	=AlgoName;
				RCmd.Phase		=phase;
				GUICmdAckMovedPage	ACmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
				if(RCmd.Send(GlobalPage,0,ACmd)==true){
					PageList[page].Merge(ACmd.PageList);
					if(Row==0){
						Items[page]		=ACmd.Items;
					}
				}
				else{
					SetError(Error_Comm , /**/"Send error :ExpandedPasteExecuteInSameAlgorithm-GUICmdReqMovedPage",ErrorCodeList::_Alart);
				}
			}
		}
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			DifferentPageCount=max(DifferentPageCount,(int)PageList[page].GetCount());
		}
		if(phase==0){
			if(DifferentPageCount>=2){
				SelectMovePastePage	PageDialog(GetLayersBase(),PageList,GetLayersBase()->GetPageNumb(),this);
				if(PageDialog.exec()==(int)false){
					delete	[]PageList;
					delete	[]Items;
					return;
				}
			}
		}
		else{
		}

		for(ExpandedItemPos *p=ExpandedItems.GetFirst();p!=NULL;p=p->GetNext()){
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdOperationMoveFromOutside	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
				int	cx=(p->Pos[0].X+p->Pos[1].X+p->Pos[2].X+p->Pos[3].X)/4;
				int	cy=(p->Pos[0].Y+p->Pos[1].Y+p->Pos[2].Y+p->Pos[3].Y)/4;
				Cmd.GlobalDx	=cx-(MinX+MaxX)/2;
				Cmd.GlobalDy	=cy-(MinY+MaxY)/2;
				Cmd.AlgoRoot	=AlgoRoot;
				Cmd.AlgoName	=AlgoName;
				Cmd.PageListForOutside	=PageList[page];
				Cmd.Phase		=phase;
				if(Cmd.SendOnly(GlobalPage,1)==false){
					SetError(Error_Comm , /**/"Send error :ExpandedPasteExecuteInSameAlgorithm-GUICmdOperationMoveFromOutside",ErrorCodeList::_Alart);
				}
			}
		}
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			if(PageList[page].GetCount()==0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReleaseSelectImagePanel	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
				Cmd.AlgoRoot=AlgoRoot;
				Cmd.AlgoName=AlgoName;
				if(Cmd.SendOnly(GlobalPage,0)==false){
					SetError(Error_Comm , /**/"Send error :ExpandedPasteExecuteInSameAlgorithm-ExecuteReleaseAllSelection",ErrorCodeList::_Alart);
				}
			}
		}

		for(ExpandedItemPos *p=ExpandedItems.GetFirst();p!=NULL;p=p->GetNext()){
			for(int page=0;page<GetPageNumb();page++){
				GUICmdReqExpandedPaste	Cmd(GetLayersBase(),emitterRoot ,emitterName,GetLayersBase()->GetGlobalPageFromLocal(page));
				Cmd.Mode=GUICmdReqExpandedPaste::_SameAlgorithmPaste;
				Cmd.AlgoRoot=AlgoRoot;
				Cmd.AlgoName=AlgoName;
				Cmd.Px1=p->Pos[0].X;
				Cmd.Py1=p->Pos[0].Y;
				Cmd.Px2=p->Pos[1].X;
				Cmd.Py2=p->Pos[1].Y;
				Cmd.Px3=p->Pos[2].X;
				Cmd.Py3=p->Pos[2].Y;
				Cmd.Px4=p->Pos[3].X;
				Cmd.Py4=p->Pos[3].Y;
				int	cx=(p->Pos[0].X+p->Pos[1].X+p->Pos[2].X+p->Pos[3].X)/4;
				int	cy=(p->Pos[0].Y+p->Pos[1].Y+p->Pos[2].Y+p->Pos[3].Y)/4;
				Cmd.Dx=cx-(MinX+MaxX)/2;
				Cmd.Dy=cy-(MinY+MaxY)/2;
				if(abs(Cmd.Dx)>2 || abs(Cmd.Dy)>2){
					Cmd.PastedLayer=LayerList;
					if(Cmd.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0)==false){
						SetError(Error_Comm , /**/"Send error :ExpandedPasteExecuteInSameAlgorithm",ErrorCodeList::_Alart);
					}
				}
			}
		}
		delete	[]PageList;
		delete	[]Items;
	}
	Repaint();
}
void	DisplayImageWithAlgorithm::GetSelectedLists(void)
{
	ExpandedPasteStart.SelectedItemLists.RemoveAll();
	ExpandedPasteCurrent.SelectedItemLists.RemoveAll();

	QString emitterRoot;
	QString emitterName;
	QString AlgoRoot;
	QString AlgoName;
	IntList	LayerList;

	GetActiveLayerList(LayerList);
	GetIdentity(emitterRoot ,emitterName);
	GetAlgorithm(AlgoRoot,AlgoName);
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqSelectedItemListsForPaste	RCmd(GetLayersBase(),emitterRoot ,emitterName,GetLayersBase()->GetGlobalPageFromLocal(page));
		GUICmdSendSelectedItemListsForPaste	SCmd(GetLayersBase(),emitterRoot ,emitterName,GetLayersBase()->GetGlobalPageFromLocal(page));
		RCmd.AlgoRoot=AlgoRoot;
		RCmd.AlgoName=AlgoName;
		RCmd.LayerList=LayerList;
		if(RCmd.Send(GetLayersBase()->GetGlobalPageFromLocal(page),0,SCmd)==true){
			for(int i=0;i<SCmd.Lists.GetCount();i++){
				ExpandedSelectedItemList *c=SCmd.Lists.Get(i);
				c->X1+=GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x;
				c->Y1+=GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y;
				c->X2+=GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x;
				c->Y2+=GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y;
				//ExpandedPasteStart.SelectedItemLists.AppendList(c);
				ExpandedPasteStart.SelectedItemLists.AppendList(*c);
			}
		}
		else{
			SetError(Error_Comm , /**/"Send error :GetSelectedLists",ErrorCodeList::_Alart);
		}
	}
}

void	DisplayImageWithAlgorithm::DrawInsideExpandedPaste( QPainter &pnt ,double movx,double movy,double ZoomRate
											,ExpandedSelectedItemListContainer &SelectedItemLists
											,ExpandedItemPosContainer &ExpandedItems
											,int ImageWidth ,int ImageHeight
											,int SourceCenterX ,int SourceCenterY)
{
	QString emitterRoot;
	QString emitterName;
	QString AlgoRoot;
	QString AlgoName;
	GetIdentity(emitterRoot ,emitterName);
	GetAlgorithm(AlgoRoot,AlgoName);

	IntList	PageList;
	//for(ExpandedSelectedItemList *p=SelectedItemLists.GetFirst();p!=NULL;p=p->GetNext()){
	for(int i=0;i<SelectedItemLists.GetCount();i++){
		ExpandedSelectedItemList *p=SelectedItemLists.Get(i);
		if(PageList.IsInclude(p->Page)==false){
			PageList.Add(p->Page);
		}
	}
	int	N=SelectedItemLists.GetCount();
	for(IntClass *C=PageList.GetFirst();C!=NULL;C=C->GetNext()){
		int	Page=C->GetValue();

		GUICmdReqDrawItemListsForPaste	RCmd(GetLayersBase(),emitterRoot ,emitterName,GetLayersBase()->GetGlobalPageFromLocal(Page));
		GUICmdSendDrawItemListsForPaste	SCmd(GetLayersBase(),emitterRoot ,emitterName,GetLayersBase()->GetGlobalPageFromLocal(Page));
		RCmd.AlgoRoot			=AlgoRoot;
		RCmd.AlgoName			=AlgoName;
		RCmd.ZoomRate			=ZoomRate;
		RCmd.movx				=movx;
		RCmd.movy				=movy;
		RCmd.Width				=ImageWidth;
		RCmd.SourceCenterX		=SourceCenterX;
		RCmd.SourceCenterY		=SourceCenterY;
		RCmd.Height				=ImageHeight;
		if(N<300){
			RCmd.SelectedItemLists	=SelectedItemLists;
		}
		else{
			int	Sep=N/300;
			for(int	n=0;n<SelectedItemLists.GetCount();n+=Sep){
				RCmd.SelectedItemLists.AppendList(*SelectedItemLists.Get(n));
			}
		}
		RCmd.ExpandedItems		=ExpandedItems;
		if(RCmd.Send(GetLayersBase()->GetGlobalPageFromLocal(Page),0,SCmd)==false){
			SetError(Error_Comm , /**/"Send error :DrawInsideExpandedPaste",ErrorCodeList::_Alart);
		}
		pnt.drawImage(0,0, *SCmd.Image);
		}
}



void	DisplayImageWithAlgorithm::DrawNoneBtnBtnDown()
{
	if(MainCanvas!=NULL){
		SetModeByOthers(mtFrameDraw::fdNone,MainCanvas->GetFrameColor());
	}
	ButtonExecuteDraw();
	SetAlterSomething();
	LastMode=Mode_None;
	GetLayersBase()->SetStatusModes(this,/**/"ItemNone");
}
void	DisplayImageWithAlgorithm::DrawBtnDown()
{
	GUIFormBase *Ret[100];
	int N=GetLayersBase()->EnumGUIInst(/**/"Button" ,/**/"ImagePanelTools" ,Ret,100);
	for(int i=0;i<N;i++){
		GUIFormBase	*s=dynamic_cast<GUIFormBase *>(Ret[i]);
		if(s!=NULL){
			for(int k=0;k<s->GetRelatedForm().count();k++){
				QString	v=s->GetRelatedForm().value(k);
				if(v==GetName()){
					CmdPanelGetButton	RCmd(GetLayersBase());
					s->TransmitDirectly(&RCmd);
					if(RCmd.Mode==mtFrameDraw::fdNone){
						CmdPanelSetButton	SCmd(GetLayersBase());
						SCmd.Mode=mtFrameDraw::fdRectangle;
						s->TransmitDirectly(&SCmd);
					}
				}
			}
		}
	}
	if(DrawBtn->isChecked()==true){
		AllUpImagePanel();
		NoneButtonDown();
	}
	if(MainCanvas!=NULL){
		MainCanvas->SetMode(ModeFromOther);
	}
	SetDrawingMode(_Normal);
	//ButtonExecuteDraw();
	SetAlterSomething();
	LastMode=Mode_DrawBtn;
	GetLayersBase()->SetStatusModes(this,/**/"ItemDraw");
}

void	DisplayImageWithAlgorithm::SelectBtnDown()
{
	if(MainCanvas!=NULL){
		MainCanvas->SetMode(ModeFromOther);
	}
	ButtonExecuteSelectArea();
	if(MainCanvas!=NULL){
		if(MainCanvas->GetMode()==mtFrameDraw::fdNone){
			SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
		}
	}
	SetAlterSomething();
	GetLayersBase()->SetStatusModes(this,/**/"ItemSelect");
}
void	DisplayImageWithAlgorithm::SelectMenuBtnDown()
{
	QMenu	Menu(this);
	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_139)/*"Select All"*/			, this, SLOT(SlotSelectAll()));
	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_140)/*"Select locked items"*/	, this, SLOT(SlotSelectLocked()));
	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_141)/*"Select by Library"*/		, this, SLOT(SlotSelectLibrary()));
	if(GetPageNumb()>1){
		Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_30)/*"Select by Page"*/		, this, SLOT(SlotSelectByPage()));
	}
	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_31)/*"Select by Origin"*/		, this, SLOT(SlotSelectByOrigin()));
	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_32)/*"Select manual creature"*/	, this, SLOT(SlotSelectManualCreature()));
	Menu.addAction (LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_215)/*"Select and move by ID/ItemName"*/		, this, SLOT(SlotSelectByItemIDName()));
	AddMenuSelectMenuBtn(Menu);

	StartMenu(SelectMenuBtn ,&Menu);

	QPoint	Q=mapToGlobal(SelectMenuBtn->geometry().center());
	Menu.exec(Q);
}
void	DisplayImageWithAlgorithm::ItemMenuBtnDown()
{
	AlgorithmBase	*ABase=GetAlgorithmBase();
	if(ABase==NULL){
		return;
	}
	QMenu	Menu(this);
	Menu.addAction (LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_216)/*"Edit item name"*/	, this, SLOT(SlotEditItemName()));
	if(ABase->AvailableShrinkItem()==true){
		Menu.addAction (LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_217)/*"Shrink/Expand item"*/, this, SLOT(SlotShrinkItem()));
	}
	if(ABase->AvailableChangeLibrary()==true){
		Menu.addAction (LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_218)/*"Change item library"*/, this, SLOT(SlotChangeLibItem()));
	}
	if(ABase->AvailableAlgorithmComponentWindow()==true){
		Menu.addAction ("Show AlgorithmWindow", this, SLOT(SlotAlgorithmComponentWindow()));
	}
	if(ABase->AvailableGenerateBlock()==true){
		Menu.addAction ("Make outline item in Selected items", this, SLOT(SlotMakeOutlineItem()));
	}
	AddMenuItemMenuBtn(Menu);

	StartMenu(ItemMenuBtn ,&Menu);

	QPoint	Q=mapToGlobal(ItemMenuBtn->geometry().center());
	Menu.exec(Q);
}
void	DisplayImageWithAlgorithm::CutItemBtnDown()
{
	ButtonExecuteCutItem();
	if(MainCanvas!=NULL){
		MainCanvas->SetMode(ModeFromOther);
	}
	SetAlterSomething();
	LastMode=Mode_CutItemBtn;
	GetLayersBase()->SetStatusModes(this,/**/"ItemCut");
}
void	DisplayImageWithAlgorithm::RegistAreaBtnDown()
{
	if(MainCanvas!=NULL){
		MainCanvas->SetMode(ModeFromOther);
	}
	//ButtonExecuteCutItem();
	SetAlterSomething();
	LastMode=Mode_RegistAreaBtn;
	GetLayersBase()->SetStatusModes(this,/**/"ItemRegistArea");
}
void	DisplayImageWithAlgorithm::MoveItemBtnDown()
{
	if(MoveItemBtn->isChecked()==true){
		if(MainCanvas!=NULL){
			MainCanvas->SetMode(ModeFromOther);
		}
		AllUpImagePanel();
		SetDrawingMode(_ItemMoveWait);
		SetModeByOthers(mtFrameDraw::fdNone ,Qt::red);
		//SetDrawingMode(_ItemMoveWait);
		SetCursor(mtFrameDraw::fdMove);
		SetAlterSomething();
		LastMode=Mode_MoveItemBtn;
		GetLayersBase()->SetStatusModes(this,/**/"ItemMove");
	}
	else{
		if(NoneBtn!=NULL){
			NoneBtn->setChecked(true);
			DrawNoneBtnBtnDown();
		}
	}
}
void	DisplayImageWithAlgorithm::MoveStart(void)
{
	DisplayImage::MoveStart();
	if(MoveItemBtn!=NULL){
		MoveItemBtn->setChecked(true);
		MoveItemBtnDown();
	}
}
void	DisplayImageWithAlgorithm::MoveStart(int globalX ,int globalY)
{
	DisplayImage::MoveStart(globalX ,globalY);
}
void	DisplayImageWithAlgorithm::DeleteBtnDown()
{
	GetLayersBase()->ShowProcessingForm(LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_219)/*"Delete items"*/);
	ButtonExecuteDeleteSelected();
	SetAlterSomething();
	GetLayersBase()->CloseProcessingForm();
}
void	DisplayImageWithAlgorithm::LockBtnDown()
{
	QMenu	Menu(this);
	Menu.addAction (LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_80)/*"Lock selected items"*/	, this, SLOT(SlotLockBtnDown()));
	Menu.addAction (LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_81)/*"Unlock all"*/			, this, SLOT(SlotUnlockBtnDown()));
	AddMenuLockBtn(Menu);
	StartMenu(LockBtn ,&Menu);

	QPoint	Q=mapToGlobal(LockBtn->geometry().center());
	Menu.exec(Q);

}

void	DisplayImageWithAlgorithm::SlotLockBtnDown()
{
	ButtonExecuteLockSelected();
	SetAlterSomething();
}
void	DisplayImageWithAlgorithm::SlotUnlockBtnDown()
{
	ButtonExecuteUnlockAll();
	SetAlterSomething();
}
void	DisplayImageWithAlgorithm::SlotShrinkItem()
{
	ShrinkItemDialog	D(GetLayersBase());
	if(D.exec()==(int)true){
		AlgorithmBase	*Base=GetAlgorithmBase();
		if(Base!=NULL){
			IntList	LayerList;
			GetActiveLayerList(LayerList);
			GetLayersBase()->ClearAllAckFlag();

			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReqShrink	Cmd(Base ,EmitterRoot ,EmitterName,globalPage);
				Cmd.ExpandPixels	=D.ExpandPixels;
				Cmd.LayerList		=LayerList;
				Cmd.MaskForSameLib	=D.MaskForSameLib;
				if(Cmd.Send(NULL,globalPage,0)==false){
					SetError(Error_Comm , /**/"Send error :GUICmdReqShrink",ErrorCodeList::_Alart);
				}
			}
			SetAlterSomething();
			GetLayersBase()->WaitAllAcknowledged(10*60*100);
		}

	}
}
int	DisplayImageWithAlgorithm::GetLibType(void)	const
{
	AlgorithmBase	*ABase=GetAlgorithmBase();
	if(ABase!=NULL){
		return ABase->GetLibType();
	}
	return -1;
}
void	DisplayImageWithAlgorithm::SlotChangeLibItem()
{
	if(GetLibType()<0)
		return;

	SelectLibraryForm	*PForm=new SelectLibraryForm(GetLibType(),GetLayersBase());
	GeneralDialog	D(GetLayersBase(),PForm,this);
	D.exec();
	if(PForm->SelectedLibID>=0){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqChangeLibItem	Cmd(GetLayersBase() ,EmitterRoot ,EmitterName,globalPage);
			Cmd.Phase=GetLayersBase()->GetCurrentPhase();
			Cmd.LibType	=GetLibType();
			Cmd.LibID	=PForm->SelectedLibID;
			if(Cmd.Send(NULL,globalPage,0)==false){
				SetError(Error_Comm , /**/"Send error :GUICmdReqChangeLibItem",ErrorCodeList::_Alart);
			}
		}
	}
}
void	DisplayImageWithAlgorithm::SlotAlgorithmComponentWindow()
{
	IntList	LibList;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqSelectedItemLibID	RCmd(GetLayersBase() ,EmitterRoot ,EmitterName,globalPage);
		GUICmdAckSelectedItemLibID	SCmd(GetLayersBase() ,EmitterRoot ,EmitterName,globalPage);
		RCmd.Phase=GetLayersBase()->GetCurrentPhase();
		RCmd.LibType	=GetLibType();
		if(RCmd.Send(globalPage,0,SCmd)==true){
			LibList.Merge(SCmd.LibList);
		}
	}
	int	LibID=-1;
	if(LibList.GetCount()>1){
		SelectLibraryInListDialog	D(GetLibType() ,LibList,GetLayersBase());
		if(D.exec()==true){
			LibID=D.SelectedLibID;
		}
		else{
			return;
		}
	}
	else{
		LibID=LibList[0];
	}
	AlgorithmItemIndependentPack	IData(GetLayersBase());
	if(ShowFixedPhase>=0){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

			for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
				GUICmdReqSelectedItemIDInLibID	RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),GlobalPage);
				GUICmdAckSelectedItemIDInLibID	SCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),GlobalPage);
				RCmd.Phase	=ShowFixedPhase;
				RCmd.LibType=GetLibType();
				RCmd.LibID	=LibID;
				RCmd.Layer	=Layer;
				if(RCmd.Send(GlobalPage,0,SCmd)==true && SCmd.ItemIDs.GetCount()>0){
					GUICmdReqItemIndependentsPack	CmdPacket(GetLayersBase(),GetDLLRoot(),GetDLLName(),GlobalPage);
					CmdPacket.TargetPhase=ShowFixedPhase;
					CmdPacket.Items		=SCmd.ItemIDs;
					CmdPacket.LibType	=GetLibType();
					CmdPacket.LibID		=LibID;
					CmdPacket.Layer		=Layer;
					GUICmdSendIndependentPack	RecPacket(GetLayersBase(),GetDLLRoot(),GetDLLName(),GlobalPage);
					CmdPacket.Send(GlobalPage,0,RecPacket);
					if(RecPacket.IsReceived()==true){
						IData.Items+=RecPacket.IData.Items;
					}
				}
			}
		}
	}
	else{
		for(int phase=0;phase<GetPhaseNumb();phase++){
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
					GUICmdReqSelectedItemIDInLibID	RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),GlobalPage);
					GUICmdAckSelectedItemIDInLibID	SCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),GlobalPage);
					RCmd.Phase	=phase;
					RCmd.LibType=GetLibType();
					RCmd.LibID	=LibID;
					RCmd.Layer	=Layer;
					if(RCmd.Send(GlobalPage,0,SCmd)==true && SCmd.ItemIDs.GetCount()>0){
						GUICmdReqItemIndependentsPack	CmdPacket(GetLayersBase(),GetDLLRoot(),GetDLLName(),GlobalPage);
						CmdPacket.TargetPhase=phase;
						CmdPacket.Items		=SCmd.ItemIDs;
						CmdPacket.LibType	=GetLibType();
						CmdPacket.LibID		=LibID;
						CmdPacket.Layer		=Layer;
						GUICmdSendIndependentPack	RecPacket(GetLayersBase(),GetDLLRoot(),GetDLLName(),GlobalPage);
						CmdPacket.Send(GlobalPage,0,RecPacket);
						if(RecPacket.IsReceived()==true){
							IData.Items+=RecPacket.IData.Items;
						}
					}
				}
			}
		}
	}
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
	if(ABase!=NULL){
		LogicDLL	*L=ABase->GetLogicDLL();
		L->ShowAndSetItems(this,0,L->GetInstance(),IData,NULL);
	}
}

void	DisplayImageWithAlgorithm::SlotMakeOutlineItem()
{
	MakeOutlineItemDialog	*D=new MakeOutlineItemDialog(GetLayersBase());
	if(D->exec()==true){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdMakeOutlineItem	Cmd(GetLayersBase() ,EmitterRoot ,EmitterName,GlobalPage);
			Cmd.LibType=GetLibType();
			Cmd.Phase=GetLayersBase()->GetCurrentPhase();
			Cmd.OutlineWidth	=D->OutlineWidth;
			if(Cmd.Send(NULL,GlobalPage,0)==false){
				SetError(Error_Comm , /**/"Send error :GUICmdMakeOutlineItem",ErrorCodeList::_Alart);
			}
		}
	}
	delete	D;
}

void	DisplayImageWithAlgorithm::GroupBtnDown()
{
	if(QMessageBox::warning(NULL
					,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_220)/*"Make bind to Group"*/
					, LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_221)/*"Do you bind selected items to make group?"*/
					,QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){							
		ButtonExecuteGroupSelected();
		SetAlterSomething();
	}
}
void	DisplayImageWithAlgorithm::CopyBtnDown()
{
	GetLayersBase()->ShowProcessingForm(LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_222)/*"Copy items"*/);
	ButtonExecuteCopySelected(true);
	SetAlterSomething();
	GetLayersBase()->CloseProcessingForm();
}
void	DisplayImageWithAlgorithm::PasteBtnDown()
{
	ButtonExecutePaste();
	SetAlterSomething();
}
void	DisplayImageWithAlgorithm::PasteBtnDownFromShortcut()
{
	QString _AlgoRoot ,_AlgoName;
	XDateTime	D=SelectPasteForm::GetTopCopiedData(GetLayersBase(),_AlgoRoot ,_AlgoName);
	if(_AlgoRoot==AlgoRoot && _AlgoName==AlgoName){
		SavedDrawingMode=DrawingMode;
		SelectPasteForm::LoadPasteSameAlgorithm(GetLayersBase(),this,D);
		SetAlterSomething();
		ButtonExecutePasteInSameAlgorithmSamePos();
		Repaint();
	}
}
void	DisplayImageWithAlgorithm::SlotSelectAll()
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectAll	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,GlobalPage);
		Cmd.LayerList=LayerList;
		if(Cmd.SendOnly(GlobalPage,1)==false){
			SetError(Error_Comm , /**/"Send error :SlotSelectAll",ErrorCodeList::_Alart);
		}
	}
	SetAlterSomething();
	Repaint();
}
void	DisplayImageWithAlgorithm::SlotSelectLocked()
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectLocked	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,GlobalPage);
		Cmd.LayerList=LayerList;
		if(Cmd.SendOnly(GlobalPage,1)==false){
			SetError(Error_Comm , /**/"Send error :SlotSelectLocked",ErrorCodeList::_Alart);
		}
	}
	SetAlterSomething();
	Repaint();
}
void	DisplayImageWithAlgorithm::SlotSelectLibrary()
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);
	SelectByLibraryDialog	Q(GetAlgorithmBase()->GetLibType() ,GetLayersBase(),this);
	if(Q.exec()==(int)true){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSelectByLibs	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,GlobalPage);
			for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
				for(AlgorithmLibraryList *a=Q.Libs.SelectedList.GetFirst();a!=NULL;a=a->GetNext()){
					SelectLibList	*v=new SelectLibList();
					v->LibType	=a->GetLibType();
					v->LibID	=a->GetLibID();
					v->Layer	=c->GetValue();
					Cmd.SelectedList.AppendList(v);
				}
			}
			if(Cmd.SendOnly(GlobalPage,1)==false){
				SetError(Error_Comm , /**/"Send error :SlotSelectLibrary",ErrorCodeList::_Alart);
			}
		}
	}
	SetAlterSomething();
	Repaint();
}
void	DisplayImageWithAlgorithm::ExeSelectItemsByLib(int LibID)
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);
	if(GetAlgorithmBase()!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSelectByLibs	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,GlobalPage);
			for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
				SelectLibList	*v=new SelectLibList();
				v->LibType	=GetAlgorithmBase()->GetLibType();
				v->LibID	=LibID;
				v->Layer	=c->GetValue();
				Cmd.SelectedList.AppendList(v);
			}
			if(Cmd.SendOnly(GlobalPage,1)==false){
				SetError(Error_Comm , /**/"Send error :ExeSelectItemsByLib",ErrorCodeList::_Alart);
			}
		}
	}
	SetAlterSomething();
	Repaint();
}

void	DisplayImageWithAlgorithm::SlotSelectByPage()
{
	SelectPages	Q(GetLayersBase(),NULL);
	if(Q.exec()==(int)true){
		ExecuteReleaseAllSelection();
		for(IntClass *d=Q.SelectedPages.GetFirst();d!=NULL;d=d->GetNext()){
			int	globalPage=d->GetValue();
			ButtonExecuteSelectByPage(globalPage);
		}
		SetAlterSomething();
	}
}
void	DisplayImageWithAlgorithm::SlotSelectByOrigin()
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);
	NPListPack<OriginNames>	OriginNameList;

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

		GUICmdReqSelectByOrigin	ReqCmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
		ReqCmd.LayerList=LayerList;
		ReqCmd.AlgoRoot=AlgoRoot;
		ReqCmd.AlgoName=AlgoName;
		GUICmdAckSelectByOrigin	AckCmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
		if(ReqCmd.Send(GlobalPage,0,AckCmd)==true){
			for(OriginNames *v=AckCmd.OriginNameList.GetFirst();v!=NULL;v=v->GetNext()){
				OriginNames *s;
				for(s=OriginNameList.GetFirst();s!=NULL;s=s->GetNext()){
					if(v->DLLRoot==s->DLLRoot && v->DLLName==s->DLLName){
						v->Numb+=s->Numb;
						break;
					}
				}
				if(s==NULL){
					s=new OriginNames();
					*s=*v;
					OriginNameList.AppendList(s);
				}
			}
		}
		else{
			SetError(Error_Comm , /**/"Send error :SlotSelectByOrigin",ErrorCodeList::_Alart);
		}
	}
	if(OriginNameList.GetNumber()!=0){
		SelectByOrigin	D(GetLayersBase(),OriginNameList,this);
		if(D.exec()==(int)true){
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdSelectByOrigin	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
				Cmd.LayerList=LayerList;
				Cmd.AlgoRoot=AlgoRoot;
				Cmd.AlgoName=AlgoName;
				Cmd.Names=*D.Selected;
				if(Cmd.SendOnly(GlobalPage,0)==false){
					SetError(Error_Comm , /**/"Send error :SlotSelectByOrigin",ErrorCodeList::_Alart);
				}
			}
		}
	}
}
void	DisplayImageWithAlgorithm::SlotSelectManualCreature()
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectManualCreature	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,GlobalPage);
		Cmd.LayerList=LayerList;
		if(Cmd.SendOnly(GlobalPage,1)==false){
			SetError(Error_Comm , /**/"Send error :SlotSelectManualCreature",ErrorCodeList::_Alart);
		}
	}
	SetAlterSomething();
	Repaint();
}

void	DisplayImageWithAlgorithm::SlotSelectByItemIDName()
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);

	ListPageLayerIDLibNamePack	ItemInfo;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAllItemsForSelect	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
		Cmd.AlgoRoot	=AlgoRoot;
		Cmd.AlgoName	=AlgoName;
		Cmd.LayerList	=LayerList;
		GUICmdAckAllItemsForSelect	Receiver(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
		if(Cmd.Send(GlobalPage,0,Receiver)==true){
			ItemInfo.AddMove(Receiver.ItemInfo);
		}
	}
	SetectSearchItemDialog	Q(GetAlgorithmBase(),ItemInfo,this);
	int	Ret=Q.exec();
	if(Ret==1 || Ret==2 || Ret==3){
		int	MinX=99999999;
		int	MinY=99999999;
		int	MaxX=-99999999;
		int	MaxY=-99999999;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqSelectItemByID	RCmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
			GUICmdAckSelectItemByID	ACmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
			RCmd.AlgoRoot	=AlgoRoot;
			RCmd.AlgoName	=AlgoName;
			for(ListPageLayerID *k=Q.SelectedItems.GetFirst();k!=NULL;k=k->GetNext()){
				if(k->Page==GlobalPage){
					RCmd.SelectedItem.AppendList(new ListLayerAndID(k->Layer,k->ID));
				}
			}
			if(Ret==1)
				RCmd.SelectMode=true;
			else
				RCmd.SelectMode=false;
			if(RCmd.SelectedItem.GetCount()>0){
				if(RCmd.Send(GlobalPage,0,ACmd)==true){
					XYData	*XY=GetLayersBase()->GetGlobalOutlineOffset(GlobalPage);
					MinX=min(MinX,ACmd.MinX+XY->x);
					MinY=min(MinY,ACmd.MinY+XY->y);
					MaxX=max(MaxX,ACmd.MaxX+XY->x);
					MaxY=max(MaxY,ACmd.MaxY+XY->y);
				}
			}
		}
		if(MinX<MaxX && MinY<MaxY){
			CmdDrawImageRectPacket	Cmd( GetLayersBase()
										,MinX,MinY ,MaxX,MaxY);
			TransmitDirectly(&Cmd);
		}
	}
}


void	DisplayImageWithAlgorithm::ExecuteMatrix(void)
{
	ClipboardAlgorithm	*L=GetLayersBase()->GetClipboardDatas()->GetLast();
	if(L!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdPasteMatrix	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
			Cmd.CreatedTime	=L->GetCreatedTime();
			GetAlgorithm(Cmd.AlgoRoot,Cmd.AlgoName);
			Cmd.MatrixData	=*GetLayersBase()->GetPasteListMatrixContainerBase();
			if(Cmd.SendOnly(GlobalPage,0)==false){
				SetError(Error_Comm , /**/"Send error :ExecuteMatrix",ErrorCodeList::_Alart);
			}
		}

	}
}

void	DisplayImageWithAlgorithm::VisibleMenuBtnDown()
{
	QMenu	Menu(this);
	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_33)/*"Visible all"*/					, this, SLOT(SlotVisibleAll()));
	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_34)/*"Invisible all"*/					, this, SLOT(SlotInvisibleAll()));
	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_35)/*"Invisible on selected items"*/	, this, SLOT(SlotInvisibleSelected()));
	AddMenuVisibleMenuBtn(Menu);
	StartMenu(VisibleMenuBtn ,&Menu);

	QPoint	Q=mapToGlobal(VisibleMenuBtn->geometry().center());
	Menu.exec(Q);
}

void	DisplayImageWithAlgorithm::RotateBtnDown()
{
	InputRotate	D(GetLayersBase(),this);
	if(D.exec()==(int)true){
		ExecuteRotate(D.Angle);
	}
}
void	DisplayImageWithAlgorithm::MirrorBtnDown()
{
	InputMirror	D(GetLayersBase(),this);
	if(D.exec()==(int)true){
		ExecuteMirror(D.MirrorMode);
	}
}
void	DisplayImageWithAlgorithm::UncoveredBtnDown()
{
	if(UncoveredBtn!=NULL && UncoveredBtn->isChecked()==true){
		if(GetLayersBase()->DeliverMakeUncoveredArea()==false){
			SetError(Error_Comm , /**/"Send error :UncoveredBtnDown",ErrorCodeList::_Alart);
		}
		DrawingMode=_DrawUncoveredArea;
		Repaint();
	}
	else{
		DrawingMode=_Normal;
		Repaint();
	}
}
void	DisplayImageWithAlgorithm::MultiSelectBtnDown()
{
	if(MultiSelectBtn!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetMultiSelectMode	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
			Cmd.ItemName	=GetName();
			Cmd.ModeMultiSelect=MultiSelectBtn->isChecked();
			if(Cmd.SendOnly(GlobalPage,0)==false){
				SetError(Error_Comm , /**/"Send error :MultiSelectBtnDown",ErrorCodeList::_Alart);
			}
		}
		Repaint();
	}
}
void	DisplayImageWithAlgorithm::SetMultiSelect(bool b)
{
	if(MultiSelectBtn!=NULL){
		MultiSelectBtn->setChecked(b);
	}
}
bool	DisplayImageWithAlgorithm::GetMultiSelect(void)
{
	return (MultiSelectBtn!=NULL)?MultiSelectBtn->isChecked():false;
}
void	DisplayImageWithAlgorithm::ExecuteRotate(int AngleDegree)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqRatate	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,GlobalPage);
		Cmd.Angle=AngleDegree;
		if(Cmd.SendOnly(GlobalPage,0)==false){
			SetError(Error_Comm , /**/"Send error :RotateBtnDown",ErrorCodeList::_Alart);
		}
	}
	BroadcastStartPage();
	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
}
void	DisplayImageWithAlgorithm::ExecuteMirror(AlgorithmItemRoot::_MirrorMode MirrorMode)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Mirror items");

	QByteArray	*SData=new QByteArray[GetPageNumb()];
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqSelectedItems	RCmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
		GUICmdAckSelectedItems	ACmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
		GetAlgorithmBase()->GetDLLName(RCmd.AlgoRoot,RCmd.AlgoName);
		if(RCmd.Send(GlobalPage,0,ACmd)==false){
			SetError(Error_Comm , /**/"Send error :MirrorBtnDown",ErrorCodeList::_Alart);
		}
		SData[GlobalPage]=ACmd.BuffData;
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqMirror	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,GlobalPage);
		Cmd.PageNumb=GetPageNumb();
		Cmd.BuffData=new QByteArray[Cmd.PageNumb];
		for(int n=0;n<Cmd.PageNumb;n++){
			Cmd.BuffData[n]=SData[n];
		}
		Cmd.MirrorMode=MirrorMode;
		if(Cmd.SendOnly(GlobalPage,0)==false){
			SetError(Error_Comm , /**/"Send error :MirrorBtnDown",ErrorCodeList::_Alart);
		}
	}
	delete	[]SData;
	BroadcastStartPage();
	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
}

void	DisplayImageWithAlgorithm::SlotVisibleAll()
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdVisibleAll	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,GlobalPage);
		Cmd.Visible=true;
		Cmd.LayerList=LayerList;
		if(Cmd.SendOnly(GlobalPage,1)==false){
			SetError(Error_Comm , /**/"Send error :SlotVisibleAll",ErrorCodeList::_Alart);
		}
	}
	SetAlterSomething();
	Repaint();
}
void	DisplayImageWithAlgorithm::SlotInvisibleAll()
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdVisibleAll	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,GlobalPage);
		Cmd.Visible=false;
		Cmd.LayerList=LayerList;
		if(Cmd.SendOnly(GlobalPage,1)==false){
			SetError(Error_Comm , /**/"Send error :SlotInvisibleAll",ErrorCodeList::_Alart);
		}
	}
	SetAlterSomething();
	Repaint();
}
void	DisplayImageWithAlgorithm::SlotInvisibleSelected()
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdInvisibleSelected	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,GlobalPage);
		Cmd.LayerList=LayerList;
		if(Cmd.SendOnly(GlobalPage,1)==false){
			SetError(Error_Comm , /**/"Send error :SlotInvisibleSelected",ErrorCodeList::_Alart);
		}
	}
	SetAlterSomething();
	Repaint();
}

void	DisplayImageWithAlgorithm::ButtonExecuteSelectByPage(int globalPage)
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);

	GUICmdSelectAll	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,globalPage);
	Cmd.LayerList=LayerList;
	if(Cmd.SendOnly(globalPage,1)==false){
		SetError(Error_Comm , /**/"Send error :ButtonExecuteSelectByPage",ErrorCodeList::_Alart);
	}
}
void	DisplayImageWithAlgorithm::ExecuteAfterDrawEnd(void)
{
}


void	DisplayImageWithAlgorithm::SetPasteMode(int _PastedLayer ,const XDateTime &CopiedID,DisplayImage::__DrawingMode DMode)
{
	ClipboardAlgorithm	*C=GetLayersBase()->SearchClipboard(CopiedID);
	if(C!=NULL){
		PastedItems=C;
		DrawingMode=DMode;
		PastedLayer=_PastedLayer;
	}
	else{
		PastedItems=NULL;
	}
}
void	DisplayImageWithAlgorithm::SetPasteForImage(const QColor &Color,const XDateTime &SelectTimeIndex)
{
	ClipboardAlgorithm	*C=GetLayersBase()->SearchClipboard(SelectTimeIndex);
	if(C!=NULL){
		for(ClipboardAlgorithmItem *a=C->Items.GetFirst();a!=NULL;a=a->GetNext()){
			if(GetLayerNumb(a->Page)==3){
				ImageBuffer *Mr;
				ImageBuffer *Mg;
				ImageBuffer *Mb;
				if((DType&__Master)!=0){
					Mr=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(0)->GetMasterBuff();
					Mg=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(1)->GetMasterBuff();
					Mb=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(2)->GetMasterBuff();
				}
				else if((DType&__Target)!=0){
					Mr=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(0)->GetTargetBuff();
					Mg=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(1)->GetTargetBuff();
					Mb=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(2)->GetTargetBuff();
				}
				else if((DType&__DelayedView)!=0){
					Mr=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(0)->GetDelayedViewBuff();
					Mg=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(1)->GetDelayedViewBuff();
					Mb=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(2)->GetDelayedViewBuff();
				}
				else if((DType&__RawTarget)!=0){
					Mr=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(0)->GetRawTargetBuff();
					Mg=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(1)->GetRawTargetBuff();
					Mb=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(2)->GetRawTargetBuff();
				}
				else if((DType&__CamTarget)!=0){
					Mr=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(0)->GetCamTargetBuff();
					Mg=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(1)->GetCamTargetBuff();
					Mb=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(2)->GetCamTargetBuff();
				}
				else{
					Mr=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(0)->GetTargetBuff();
					Mg=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(1)->GetTargetBuff();
					Mb=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(2)->GetTargetBuff();
				}
				BYTE	Cr=Color.red();
				BYTE	Cg=Color.green();
				BYTE	Cb=Color.blue();
				a->Area.FillData(Cr ,*Mr);
				a->Area.FillData(Cg ,*Mg);
				a->Area.FillData(Cb ,*Mb);
			}
			else{
				for(int Ly=0;Ly<GetLayerNumb(a->Page);Ly++){
					ImageBuffer *M;
					if((DType&__Master)!=0){
						M=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(Ly)->GetMasterBuff();
					}
					else if((DType&__Target)!=0){
						M=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(Ly)->GetTargetBuff();
					}
					else if((DType&__DelayedView)!=0){
						M=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(Ly)->GetDelayedViewBuff();
					}
					else if((DType&__RawTarget)!=0){
						M=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(Ly)->GetRawTargetBuff();
					}
					else if((DType&__CamTarget)!=0){
						M=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(Ly)->GetCamTargetBuff();
					}
					else{
						M=&GetLayersBase()->GetPageData(a->Page)->GetLayerData(Ly)->GetTargetBuff();
					}
					BYTE	Col=Color.red();
					a->Area.FillData(Col ,*M);
				}
			}
		}
	}
}

void DisplayImageWithAlgorithm::ExecutePaste(int localPage ,int Dx ,int Dy ,bool SamePage,int _PastedLayer)
{
	AlgorithmBase	*a=GetAlgorithmBase();
	if(PastedItems!=NULL && PastedItems->Base==a){
		int	Numb=PastedItems->Items.GetNumber();
		ClipboardAlgorithmItem	**LTable=new ClipboardAlgorithmItem*[Numb];
		int	N=0;
		for(ClipboardAlgorithmItem	*c=PastedItems->Items.GetFirst();c!=NULL;c=c->GetNext(),N++){
			LTable[N]=c;
		}
		//#pragma omp parallel                             
		//{                                                
		//	#pragma omp for
			for(int i=0;i<N;i++){
				ClipboardAlgorithmItem	*c=LTable[i];
				if(c->Page==localPage){
					if(SamePage==true){
						a->ExecutePaste(PastedLayer,c ,Dx,Dy,true);
					}
					else{
						a->ExecutePaste(PastedLayer,c ,Dx,Dy,false);
					}
				}
			}
		//}
		delete	[]LTable;
	}

	if(SamePage==false){
		int	CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
		for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
			if(CurrentGlobalPage==globalpage){
				continue;
			}

			SlaveCommReqPasteFromClipboard	RCmd(GetLayersBase(),EmitterRoot,EmitterName,CurrentGlobalPage);
			SlaveCommAckPasteFromClipboard	ACmd(GetLayersBase(),EmitterRoot,EmitterName,CurrentGlobalPage);
			RCmd.CreatedTime=PastedItems->GetCreatedTime();
			RCmd.MoveGlobalDx	=Dx;
			RCmd.MoveGlobalDy	=Dy;
			RCmd.InstName		=GetName();
			if(RCmd.Send(globalpage,0,ACmd)==true){
				XYData	*DrawnXY=GetLayersBase()->GetGlobalOutlineOffset(globalpage);
				XYData	*ThisXY =GetLayersBase()->GetGlobalOutlineOffset(CurrentGlobalPage);
				for(ClipboardAlgorithmItem *c=ACmd.ClipboardDatas.Items.GetFirst();c!=NULL;c=c->GetNext()){
					c->Page=CurrentGlobalPage;
					a->ExecutePaste(PastedLayer,c 
												,DrawnXY->x-ThisXY->x+Dx
												,DrawnXY->y-ThisXY->y+Dy);
				}
			}
		}
	}

	SetAlterSomething();
}
void DisplayImageWithAlgorithm::ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName)
{
	AlgorithmBase	*a=GetAlgorithmBase();
	//if(PastedItems==NULL || PastedItems->Base!=a)
	//	return;
	int32	ItemClass=ReturnItemClassForShapePaste();
	QByteArray	Buff;
	if(a->ShowPasteCreateWithShape(Buff,PastedLayer)==true){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Paste in fixed position");

		GetLayersBase()->ShowProcessingForm(LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_231)/*"Paste in fixed position"*/);
		//GetLayersBase()->AddMaxProcessing(GetLayersBase()->GetPageNumb());
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdExecutePaste	Cmd(GetLayersBase(),GUICmdExecutePaste::_ShapedPaste,EmitterRoot,EmitterName ,GlobalPage);
			Cmd.InstName=GetName();
			Cmd.Buff=Buff;
			Cmd.OriginRoot=OriginRoot;
			Cmd.OriginName=OriginName;
			Cmd.ItemClass =ItemClass;
			if(Cmd.SendOnly(GlobalPage,1)==false){
				SetError(Error_Comm , /**/"Send error :ExecutePasteShape",ErrorCodeList::_Alart);
			}
			GetLayersBase()->StepProcessing(page);
		}
		GetLayersBase()->CloseProcessingForm();
	}
	SetAlterSomething();
}

void DisplayImageWithAlgorithm::ExecutePasteForImage(const QString &OriginRoot ,const QString &OriginName)
{
	AlgorithmBase	*a=GetAlgorithmBase();
	QByteArray	Buff;
	if(a->ShowPasteCreateWithShape(Buff,PastedLayer)==true){
		GetLayersBase()->ShowProcessingForm(LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_232)/*"Paste for image"*/);
		GetLayersBase()->SetMaxProcessing(GetLayersBase()->GetPageNumb());
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdExecutePaste	Cmd(GetLayersBase(),GUICmdExecutePaste::_ShapedPaste,EmitterRoot,EmitterName ,GlobalPage);
			Cmd.InstName=GetName();
			Cmd.Buff=Buff;
			Cmd.OriginRoot=OriginRoot;
			Cmd.OriginName=OriginName;
			if(Cmd.SendOnly(GlobalPage,1)==false){
				SetError(Error_Comm , /**/"Send error :ExecutePasteShape",ErrorCodeList::_Alart);
			}
			GetLayersBase()->StepProcessing(page);
		}
		GetLayersBase()->CloseProcessingForm();
	}
	SetAlterSomething();
}

void DisplayImageWithAlgorithm::ExecutePasteCreateWithShape(int localPage ,QByteArray &Buff 
															,const QString &OriginRoot ,const QString &OriginName
															,int ItemClass)
{
	AlgorithmBase	*a=GetAlgorithmBase();
	if(PastedItems==NULL)
		return;
	QBuffer	MemBuff(&Buff);
	for(ClipboardAlgorithmItem	*c=PastedItems->Items.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Page==localPage){
			//a->ExecutePasteCreateWithShape(PastedLayer,c ,MemBuff,MoveCurrentGlobalX-MoveStartGlobalX,MoveCurrentGlobalY-MoveStartGlobalY);
			a->ExecutePasteCreateWithShape(PastedLayer,c ,MemBuff,0,0 ,OriginRoot ,OriginName ,ItemClass);
		}
	}
}

void	DisplayImageWithAlgorithm::ExecuteCutItemsByPasted(int dx,int dy)
{
	bool	MultiSelectMode=(MultiSelectBtn!=NULL)?MultiSelectBtn->isChecked():false;

	AlgorithmBase	*ABase=GetAlgorithmBase();
	if(ABase!=NULL && PastedItems!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot	*APage=ABase->GetPageData(page);
			for(int layer=0;layer<GetLayerNumb(page);layer++){
				FlexArea	Area;
				for(ClipboardAlgorithmItem *a=PastedItems->Items.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->Page==page && a->Layer==layer){
						Area+=a->Area;
					}
				}
				IntList	LayerList;
				LayerList.Add(layer);
				Area.MoveToNoClip(dx,dy);
				APage->CutArea(Area,LayerList,MultiSelectMode);
			}
		}
	}
}


void	DisplayImageWithAlgorithm::ExecuteMove(void)
{
	ExecuteMove(MoveCurrentGlobalX-MoveStartGlobalX,MoveCurrentGlobalY-MoveStartGlobalY);
}
void	DisplayImageWithAlgorithm::ExecuteMove(int dx ,int dy)
{
	AlgorithmBase	*A=GetAlgorithmBase();
	if(A==NULL){
		return;
	}
	UndoStocker	&U=GetLayersBase()->GetUndoStocker();
	U.SetNewTopic(/**/"Move items");

	QString DLLRoot ,DLLName;
	A->GetDLLName(DLLRoot ,DLLName);

	IntList PhaseList;
	if(GetParamGlobal()->CommonOperationInAllPhases==false){
		PhaseList.Add(GetLayersBase()->GetCurrentPhase());
	}
	else{
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PhaseList.Add(phase);
		}
	}

	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();

		IntList	*PageList	=new IntList[GetPageNumb()];
		ListPageLayerIDPack	*Items=new ListPageLayerIDPack[GetPageNumb()];
		int		DifferentPageCount=0;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

			GUICmdReqMovedPage	RCmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
			RCmd.GlobalDx	=dx;
			RCmd.GlobalDy	=dy;
			RCmd.AlgoRoot	=DLLRoot;
			RCmd.AlgoName	=DLLName;
			RCmd.Phase		=phase;
			GUICmdAckMovedPage	ACmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
				PageList[page]	=ACmd.PageList;
				Items[page].Move(ACmd.Items);
			}
			else{
				SetError(Error_Comm , /**/"Send error :ExecuteMove",ErrorCodeList::_Alart);
			}
		}
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			DifferentPageCount=max(DifferentPageCount,(int)PageList[page].GetCount());
		}
		if(phase==0){
			if(DifferentPageCount>=2){
				SelectMovePastePage	PageDialog(GetLayersBase(),PageList,GetLayersBase()->GetPageNumb(),this);
				if(PageDialog.exec()==(int)false){
					delete	[]PageList;
					delete	[]Items;
					return;
				}
			}
		}

		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdOperationMoveFromOutside	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
			Cmd.GlobalDx			=dx;
			Cmd.GlobalDy			=dy;
			Cmd.AlgoRoot			=DLLRoot;
			Cmd.AlgoName			=DLLName;
			Cmd.PageListForOutside	=PageList[page];
			Cmd.Phase				=phase;
			if(Cmd.SendOnly(GlobalPage,1)==false){
				SetError(Error_Comm , /**/"Send error :ExecuteMove",ErrorCodeList::_Alart);
			}
		}
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			bool Alive=false;
			for(int t=0;t<GetLayersBase()->GetPageNumb();t++){
				if(PageList[t].IsInclude(page)==true){
					Alive=true;
					break;
				}
			}
			if(Alive==true){
				GUICmdOperationMove	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
				Cmd.GlobalDx			=dx;
				Cmd.GlobalDy			=dy;
				Cmd.AlgoRoot			=DLLRoot;
				Cmd.AlgoName			=DLLName;
				Cmd.Items.Move(Items[page]);
				Cmd.Phase				=phase;
				if(Cmd.SendOnly(GlobalPage,1)==false){
					SetError(Error_Comm , /**/"Send error :ExecuteMove",ErrorCodeList::_Alart);
				}
			}
			else{
				GUICmdOperationDelete	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,GlobalPage);
				GetActiveLayerList(Cmd.LayerList);
				Cmd.Phase	 =ShowFixedPhase;
				if(Cmd.SendOnly(GlobalPage,1)==false){
					SetError(Error_Comm , /**/"Send error :ExecuteMove-Delete",ErrorCodeList::_Alart);
				}
			}
		}
		DrawingMode=_Normal;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSyncDrawingMode	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
			Cmd.DMode=DrawingMode;
			Cmd.InstName=GetName();
			if(Cmd.SendOnly(GlobalPage,0)==false){
				SetError(Error_Comm , /**/"Send error :ExecuteMove",ErrorCodeList::_Alart);
			}
		}
		delete	[]PageList;
		delete	[]Items;
	}
	SetAlterSomething();
}

void	DisplayImageWithAlgorithm::ExecuteMouseLDown(int globalX ,int globalY)
{
	AlgorithmBase	*A=GetAlgorithmBase();
	if(A==NULL){
		return;
	}
	QString DLLRoot ,DLLName;
	A->GetDLLName(DLLRoot ,DLLName);
	int	Count=0;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

		GUICmdReqSelectedItemCount	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
		Cmd.AlgoRoot=DLLRoot;
		Cmd.AlgoName=DLLName;
		GUICmdSendSelectedItemCount	Receiver(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
		if(Cmd.Send(GlobalPage,0,Receiver)==true){
			Count+=Receiver.SelectedItemCount;
		}
		else{
			SetError(Error_Comm , /**/"Send error :ExecuteMouseLDown",ErrorCodeList::_Alart);
		}
	}
	if(Count!=0){
		if(IsMoveModeButtonDown()==true
		&& (SelectBtn==NULL || SelectBtn->isChecked()==false) && (CutItemBtn==NULL || CutItemBtn->isChecked()==false) && (DrawBtn==NULL || DrawBtn->isChecked()==false)){
			DrawingMode=_ItemMove;		
			MoveStartGlobalX=globalX;
			MoveStartGlobalY=globalY;
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdSyncDrawingMode	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,page);
				Cmd.DMode=DrawingMode;
				Cmd.InstName=GetName();
				if(Cmd.SendOnly(GlobalPage,0)==false){
					SetError(Error_Comm , /**/"Send error :ExecuteMouseLDown",ErrorCodeList::_Alart);
				}
			}		
			MoveStart(MoveStartGlobalX,MoveStartGlobalY);
			SetAlterSomething();
		}
	}
}

void	DisplayImageWithAlgorithm::ExecuteMouseRDown(int globalX ,int globalY)
{
	ExecuteReleaseAllSelection();
}

void	DisplayImageWithAlgorithm::ExecuteReleaseAllSelection(void)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReleaseSelectImagePanel	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
		Cmd.AlgoRoot=AlgoRoot;
		Cmd.AlgoName=AlgoName;
		if(Cmd.SendOnly(GlobalPage,0)==false){
			SetError(Error_Comm , /**/"Send error :ExecuteReleaseAllSelection",ErrorCodeList::_Alart);
		}
	}
	SetAlterSomething();
	emit	SignalReleaseAllSelection();
}
void	DisplayImageWithAlgorithm::MoveFinish(void)
{
	BroadcastBuildForShow();
}

void	DisplayImageWithAlgorithm::SlotEditItemName()
{
	EditItemNameDialog	D(GetLayersBase(),/**/"");
	if(D.exec()==(int)true){
		ExecuteChangeItemName(D.ItemName);
	}
}

void	DisplayImageWithAlgorithm::ExecuteChangeItemName(const QString &itemname)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetItemNameInSelected	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
		Cmd.AlgoRoot=AlgoRoot;
		Cmd.AlgoName=AlgoName;
		Cmd.ItemName=itemname;
		if(Cmd.SendOnly(GlobalPage,0)==false){
			SetError(Error_Comm , /**/"Send error :SlotEditItemName",ErrorCodeList::_Alart);
		}
	}
}

void	DisplayImageWithAlgorithm::ExecuteMouseLDownWithShift(int globalX ,int globalY)
{
//	if(MainCanvas->GetMode()==mtFrameDraw::fdNone){
	AlgorithmBase	*A=GetAlgorithmBase();
	if(A==NULL){
		return;
	}
	IntList PageList;
	IntList	PickedPageList;
	ListLayerIDLibNamePack		PickedItems;
	ListPageLayerIDLibNamePack	PickedItemsWithPage;
	GetLayersBase()->GetGlobalPage(globalX ,globalY,globalX ,globalY ,PageList);
	for(IntClass *d=PageList.GetFirst();d!=NULL;d=d->GetNext()){
		int	globalPage=d->GetValue();
		if(globalPage<0){
			return;
		}
		IntList	LayerList;
		GetActiveLayerList(LayerList);

		int	localX ,localY;
		GetLayersBase()->GetPageData(globalPage)->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,localX ,localY);
		GUICmdReqItemCountOnLocalPoint	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,globalPage);
		Cmd.AlgoRoot	=AlgoRoot;
		Cmd.AlgoName	=AlgoName;
		Cmd.LocalX		=localX;
		Cmd.LocalY		=localY;
		Cmd.LayerList	=LayerList;
		GUICmdSendItemCountOnLocalPoint	Receiver(GetLayersBase(),EmitterRoot,EmitterName ,globalPage);
		if(Cmd.Send(globalPage,0,Receiver)==true){
			if(Receiver.ItemList.GetCount()>0){
				PickedPageList.Merge(globalPage);
				for(ListLayerIDLibName *s=Receiver.ItemList.GetFirst();s!=NULL;s=s->GetNext()){
					ListPageLayerIDLibName	*d=new ListPageLayerIDLibName();
					d->Page	=globalPage;
					d->Layer	=s->Layer;
					d->LibID	=s->LibID;
					d->ID		=s->ID;
					d->ItemName	=s->ItemName;
					PickedItemsWithPage.AppendList(d);
				}
				PickedItems+=Receiver.ItemList;
			}
		}
		else{
			SetError(Error_Comm , /**/"Send error :ExecuteMouseLDownWithShift",ErrorCodeList::_Alart);
		}
	}
	if(PickedPageList.GetCount()==1){
		int	globalPage=PickedPageList.GetFirst()->GetValue();
		ListLayerAndIDPack	SelectedItems;
		if(PickedItems.GetCount()>1){
			SelectItemForm	Q(A,PickedItems,this ,globalPage);
			if(Q.exec()==(int)true){
				SelectedItems=Q.SelectedItems;
			}
		}
		else{
			SelectedItems=PickedItems;
		}
		if(SelectedItems.GetFirst()!=NULL){
			GUICmdSelectItemByID	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,globalPage);
			Cmd.AlgoRoot=AlgoRoot;
			Cmd.AlgoName=AlgoName;
			Cmd.SelectedItem=SelectedItems;
			if(Cmd.SendOnly(globalPage,0)==false){
				SetError(Error_Comm , /**/"Send error :ExecuteMouseLDownWithShift",ErrorCodeList::_Alart);
			}
		}
	}
	else if(PickedPageList.GetCount()>1){
		ListPageLayerIDPack	SelectedItems;
		SelectPageItemDialog	Q(A,PickedItemsWithPage);
		if(Q.exec()==(int)true){
			SelectedItems=Q.SelectedItems;
		}
		if(SelectedItems.GetFirst()!=NULL){
			ListPageLayerID	*s;
			while((s=SelectedItems.GetFirst())!=NULL){
				int	globalPage=s->Page;
				GUICmdSelectItemByID	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,globalPage);
				Cmd.AlgoRoot=AlgoRoot;
				Cmd.AlgoName=AlgoName;
				do{
					ListLayerAndID	*d=new ListLayerAndID();
					d->Layer=s->Layer;
					d->ID	=s->ID;
					Cmd.SelectedItem.AppendList(d);
					SelectedItems.RemoveList(s);
					delete	s;
					for(s=SelectedItems.GetFirst();s!=NULL;s=s->GetNext()){
						if(s->Page==globalPage){
							break;
						}
					}
				}while(s!=NULL);
			
				if(Cmd.SendOnly(globalPage,0)==false){
					SetError(Error_Comm , /**/"Send error :ExecuteMouseLDownWithShift",ErrorCodeList::_Alart);
				}
			}
		}
	}
}

bool	DisplayImageWithAlgorithm::SelectOneItem(int globalX ,int globalY
												 ,ListLayerAndID &SelectedItem)
{
	IntList PageList;
	GetLayersBase()->GetGlobalPage(globalX ,globalY,globalX ,globalY ,PageList);
	for(IntClass *d=PageList.GetFirst();d!=NULL;d=d->GetNext()){
		int	globalPage=d->GetValue();
		if(globalPage<0){
			return false;
		}
		IntList	LayerList;
		GetActiveLayerList(LayerList);

		int	localX ,localY;
		GetLayersBase()->GetPageData(globalPage)->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,localX ,localY);
		GUICmdReqItemCountOnLocalPoint	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,globalPage);
		Cmd.AlgoRoot	=AlgoRoot;
		Cmd.AlgoName	=AlgoName;
		Cmd.LocalX		=localX;
		Cmd.LocalY		=localY;
		Cmd.LayerList	=LayerList;
		GUICmdSendItemCountOnLocalPoint	Receiver(GetLayersBase(),EmitterRoot,EmitterName ,globalPage);
		if(Cmd.Send(globalPage,0,Receiver)==true){
			if(Receiver.ItemList.GetNumber()>1){
				SelectOneItemForm	Q(GetAlgorithmBase(),Receiver.ItemList,this ,globalPage);
				if(Q.exec()==(int)true){
					SelectedItem=Q.SelectedItem;
				}
			}
			else if(Receiver.ItemList.GetNumber()==1){
				SelectedItem=*Receiver.ItemList.GetFirst();
			}
			return true;
		}
	}
	return false;
}

void	DisplayImageWithAlgorithm::SetActivateItem(int globalpage ,int layer, int itemID)
{
	GUICmdSetActivateItem	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,globalpage);
	Cmd.Layer	=layer;
	Cmd.ItemID	=itemID;
	Cmd.Send(NULL,globalpage,0);
}

void	DisplayImageWithAlgorithm::ClearActivattionItems(void)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdClearActivateItem	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,GlobalPage);
		Cmd.Send(NULL,GlobalPage,0);
	}
}

void	DisplayImageWithAlgorithm::PutRectangle(int x1,int y1 ,int x2,int y2)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.RectangleData.x1	=x1;
		GetRawSDataPoint()->UData.RectangleData.y1	=y1;
		GetRawSDataPoint()->UData.RectangleData.x2	=x2;
		GetRawSDataPoint()->UData.RectangleData.y2	=y2;
	}
	CanvasSlotDrawEnd();
}

void	DisplayImageWithAlgorithm::PutEndlessLine(int x ,int y ,double s)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.LineData.x=x;
		GetRawSDataPoint()->UData.LineData.y=y;
		GetRawSDataPoint()->UData.LineData.s=s;
	}
	CanvasSlotDrawEnd();
}

void	DisplayImageWithAlgorithm::PutLine(int x1,int y1 ,int x2,int y2)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.ChoppedLineData.x1	=x1;
		GetRawSDataPoint()->UData.ChoppedLineData.y1	=y1;
		GetRawSDataPoint()->UData.ChoppedLineData.x2	=x2;
		GetRawSDataPoint()->UData.ChoppedLineData.y2	=y2;
	}
	CanvasSlotDrawEnd();
}

void	DisplayImageWithAlgorithm::PutHalfLine(int x ,int y ,double s ,double length)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.HalfLineData.x=x;
		GetRawSDataPoint()->UData.HalfLineData.y=y;
		GetRawSDataPoint()->UData.HalfLineData.s=s;
	}
	CanvasSlotDrawEnd();
}

void	DisplayImageWithAlgorithm::PutEllipse(int cx, int cy, int rx ,int ry)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.EllipseData.cx	=cx;
		GetRawSDataPoint()->UData.EllipseData.cy	=cy;
		GetRawSDataPoint()->UData.EllipseData.rx	=rx;
		GetRawSDataPoint()->UData.EllipseData.ry	=ry;
	}
	CanvasSlotDrawEnd();
}
void	DisplayImageWithAlgorithm::PutCircle(int cx, int cy, int r)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.CircleData.cx	=cx;
		GetRawSDataPoint()->UData.CircleData.cy	=cy;
		GetRawSDataPoint()->UData.CircleData.r	=r;
	}
	CanvasSlotDrawEnd();
}
void	DisplayImageWithAlgorithm::PutLongCircle(int cx1, int cy1, int cx2, int cy2, int r)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.LongCircleData.cx1	=cx1;
		GetRawSDataPoint()->UData.LongCircleData.cy1	=cy1;
		GetRawSDataPoint()->UData.LongCircleData.cx2	=cx2;
		GetRawSDataPoint()->UData.LongCircleData.cy2	=cy2;
		GetRawSDataPoint()->UData.LongCircleData.r	=r;
	}
	CanvasSlotDrawEnd();
}

void	DisplayImageWithAlgorithm::PutRotRectangle(int cx, int cy ,int width ,int height ,double s)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.RotRectangleData.cx	=cx;
		GetRawSDataPoint()->UData.RotRectangleData.cy	=cy;
		GetRawSDataPoint()->UData.RotRectangleData.rx	=width/2.0;
		GetRawSDataPoint()->UData.RotRectangleData.ry	=height/2.0;
		GetRawSDataPoint()->UData.RotRectangleData.s	=s;
	}
	CanvasSlotDrawEnd();
}

void	DisplayImageWithAlgorithm::PutRotEllipse(int cx, int cy, int rx ,int ry ,double s)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.RotEllipseData.cx	=cx;
		GetRawSDataPoint()->UData.RotEllipseData.cy	=cy;	
		GetRawSDataPoint()->UData.RotEllipseData.rx	=rx;
		GetRawSDataPoint()->UData.RotEllipseData.ry	=ry;
		GetRawSDataPoint()->UData.RotEllipseData.s	=s;
	}
	CanvasSlotDrawEnd();
}

void	DisplayImageWithAlgorithm::PutArc(int cx, int cy, int rx ,int ry ,double StartS ,double EndS)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.ArcData.cx	=cx;
		GetRawSDataPoint()->UData.ArcData.cy	=cy;
		GetRawSDataPoint()->UData.ArcData.r	=(rx+ry)/2.0;
		GetRawSDataPoint()->UData.ArcData.s1	=StartS;
		GetRawSDataPoint()->UData.ArcData.s2	=EndS;
	}
	CanvasSlotDrawEnd();
}

void	DisplayImageWithAlgorithm::PutRing(int cx, int cy, int rx1 ,int ry1 , int rx2 ,int ry2)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.ERingData.cx	=cx;
		GetRawSDataPoint()->UData.ERingData.cy	=cy;
		GetRawSDataPoint()->UData.ERingData.rx1	=rx1;
		GetRawSDataPoint()->UData.ERingData.ry1	=ry1;
		GetRawSDataPoint()->UData.ERingData.rx2	=rx2;
		GetRawSDataPoint()->UData.ERingData.ry2	=ry2;
	}
	CanvasSlotDrawEnd();
}

void	DisplayImageWithAlgorithm::RotateStart(void)
{
	AllUpToolButton();
	DisplayImage::RotateStart();
}

void	DisplayImageWithAlgorithm::SlopeXStart(void)
{
	AllUpToolButton();
	DisplayImage::SlopeXStart();
}

void	DisplayImageWithAlgorithm::SlopeYStart(void)
{
	AllUpToolButton();
	DisplayImage::SlopeYStart();
}

void	DisplayImageWithAlgorithm::ExtendStart(void)
{
	AllUpToolButton();
	DisplayImage::ExtendStart();
}
void	DisplayImageWithAlgorithm::ExecuteSelectItemsByOriginType	(struct	OriginTypeSelection &SelectMode)
{
	QString emitterRoot;
	QString emitterName;
	QString AlgoRoot;
	QString AlgoName;
	IntList	LayerList;

	GetActiveLayerList(LayerList);
	GetIdentity(emitterRoot ,emitterName);
	GetAlgorithm(AlgoRoot,AlgoName);
	for(int page=0;page<GetPageNumb();page++){
		GUICmdSelectItemsByOriginType	RCmd(GetLayersBase(),emitterRoot ,emitterName,GetLayersBase()->GetGlobalPageFromLocal(page));
		RCmd.AlgoRoot=AlgoRoot;
		RCmd.AlgoName=AlgoName;
		RCmd.LayerList=LayerList;
		RCmd.SelectMode=SelectMode;
		RCmd.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0);
	}
}
void	DisplayImageWithAlgorithm::SeparateItemBtnDown()
{
	if(SeparateItemBtn->isChecked()==true){
		if(MainCanvas!=NULL){
			MainCanvas->SetMode(ModeFromOther);
		}
		AllUpImagePanel();
		SetDrawingMode(_ReparateItemByShape);
		SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
		//SetDrawingMode(_ItemMoveWait);
		SetCursor(mtFrameDraw::fdRectangle);
		SetAlterSomething();
		LastMode=Mode_SeparateItemBtn;
		GetLayersBase()->SetStatusModes(this,/**/"SeparateItem");
	}
	else{
		if(SeparateItemBtn!=NULL){
			SeparateItemBtn->setChecked(true);
			DrawNoneBtnBtnDown();
		}
	}
}
void	DisplayImageWithAlgorithm::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);
	CmdDrawImageActivate	*CmdDrawImageActivateVar=dynamic_cast<CmdDrawImageActivate *>(packet);
	if(CmdDrawImageActivateVar!=NULL){
		ExecuteActiveOnItem(CmdDrawImageActivateVar->GlobalPage ,CmdDrawImageActivateVar->Layer ,CmdDrawImageActivateVar->ItemID);
	}
}
bool	DisplayImageWithAlgorithm::ExecuteClickButton(const QString &ButtonName)
{
	if(DisplayImage::ExecuteClickButton(ButtonName)==true){
		return true;
	}
	if(ButtonName==/**/"NoneBtn" && NoneBtn!=NULL){
		NoneBtn->click();
		return true;
	}
	if(ButtonName==/**/"DrawBtn" && DrawBtn!=NULL){
		DrawBtn->click();
		return true;
	}
	if(ButtonName==/**/"SelectBtn" && SelectBtn!=NULL){
		SelectBtn->click();
		return true;
	}
	if(ButtonName==/**/"SelectMenuBtn" && SelectMenuBtn!=NULL){
		SelectMenuBtn->click();
		return true;
	}
	if(ButtonName==/**/"CutItemBtn" && CutItemBtn!=NULL){
		CutItemBtn->click();
		return true;
	}
	if(ButtonName==/**/"MoveItemBtn" && MoveItemBtn!=NULL){
		MoveItemBtn->click();
		return true;
	}
	if(ButtonName==/**/"DeleteBtn" && DeleteBtn!=NULL){
		DeleteBtn->click();
		return true;
	}
	if(ButtonName==/**/"LockBtn" && LockBtn!=NULL){
		LockBtn->click();
		return true;
	}
	if(ButtonName==/**/"GroupBtn" && GroupBtn!=NULL){
		GroupBtn->click();
		return true;
	}
	if(ButtonName==/**/"CopyBtn" && CopyBtn!=NULL){
		CopyBtn->click();
		return true;
	}
	if(ButtonName==/**/"PasteBtn" && PasteBtn!=NULL){
		PasteBtn->click();
		return true;
	}
	if(ButtonName==/**/"RegistAreaBtn" && RegistAreaBtn!=NULL){
		RegistAreaBtn->click();
		return true;
	}
	if(ButtonName==/**/"RotateBtn" && RotateBtn!=NULL){
		RotateBtn->click();
		return true;
	}
	if(ButtonName==/**/"MirrorBtn" && MirrorBtn!=NULL){
		MirrorBtn->click();
		return true;
	}
	if(ButtonName==/**/"UncoveredBtn" && UncoveredBtn!=NULL){
		UncoveredBtn->click();
		return true;
	}
	if(ButtonName==/**/"ItemMenuBtn" && ItemMenuBtn!=NULL){
		ItemMenuBtn->click();
		return true;
	}
	if(ButtonName==/**/"SeparateItemBtn" && SeparateItemBtn!=NULL){
		SeparateItemBtn->click();
		return true;
	}
	return false;
}

void	DisplayImageWithAlgorithm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	SpecifiedBroadcasterDeletePasted	*SpecifiedBroadcasterDeletePastedVar=dynamic_cast<SpecifiedBroadcasterDeletePasted *>(v);
	if(SpecifiedBroadcasterDeletePastedVar!=NULL){
		if(PastedItems==SpecifiedBroadcasterDeletePastedVar->DeletedPointer){
			PastedItems=NULL;
		}
		return;
	}
}

void	DisplayImageWithAlgorithm::GetMenuInfo(MenuInfoContainer &Info)
{
	DisplayImage::GetMenuInfo(Info);

	if(SelectMenuBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(1,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_142)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_143)/*"Select all"*/,this);
		p->SetMenuNumber(200);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(SelectMenuBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(2,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_144)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_145)/*"Select locked items"*/,this);
		p->SetMenuNumber(201);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(SelectMenuBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(3,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_146)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_147)/*"Select by library"*/,this);
		p->SetMenuNumber(202);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(SelectMenuBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(4,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_148)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_149)/*"Select by page"*/,this);
		p->SetMenuNumber(203);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(SelectMenuBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(5,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_150)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_151)/*"Select by origin"*/,this);
		p->SetMenuNumber(204);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(SelectMenuBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(6,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_152)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_153)/*"Select manual creature"*/,this);
		p->SetMenuNumber(205);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(SelectMenuBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(0,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_154)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_155)/*"Separator"*/,this);
		p->SetMenuNumber(206);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(DeleteBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(7,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_156)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_157)/*"Delete items"*/,this);
		p->SetMenuNumber(207);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(LockBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(8,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_158)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_159)/*"Lock items"*/,this);
		p->SetMenuNumber(208);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(GroupBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(9,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_160)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_161)/*"Make Grouo"*/,this);
		p->SetMenuNumber(209);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(CopyBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(10,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_162)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_163)/*"Copy Items"*/,this);
		p->SetMenuNumber(210);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(PasteBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(11,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_164)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_165)/*"Paste items"*/,this);
		p->SetMenuNumber(211);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(VisibleMenuBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(12,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_166)/*"Display"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_167)/*"Visible all items"*/,this);
		p->SetMenuNumber(212);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(VisibleMenuBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(13,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_168)/*"Display"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_169)/*"Invisible all items"*/,this);
		p->SetMenuNumber(213);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(VisibleMenuBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(14,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_170)/*"Display"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_171)/*"Invisible on selected items"*/,this);
		p->SetMenuNumber(214);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(RotateBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(15,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_172)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_173)/*"Rotate on selected items"*/,this);
		p->SetMenuNumber(215);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(MirrorBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(16,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_174)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_175)/*"Mirror on selected items"*/,this);
		p->SetMenuNumber(216);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(UncoveredBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(17,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_181)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_182)/*"Show uncovered area"*/,this);
		p->SetMenuNumber(217);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ItemMenuBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(18,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_142)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_234)/*"Edit item name"*/,this);
		p->SetMenuNumber(218);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(VisibleMenuBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(0,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_176)/*"Display"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_177)/*"Separator"*/,this);
		p->SetMenuNumber(219);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(MultiSelectBtn!=NULL){
		MenuInfoList	*p=new MenuInfoList(19,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_181)/*"Edit"*/,LangDISolver.GetString(XDisplayImageWithAlgorithm_LS,LID_235)/*"Mode for multi selection"*/,this);
		p->SetMenuNumber(220);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
}
void	DisplayImageWithAlgorithm::ExecuteMenu(int ID)
{
	switch(ID){
		case 1:
			SlotSelectAll();
			break;
		case 2:
			SlotSelectLocked();
			break;
		case 3:
			SlotSelectLibrary();
			break;
		case 4:
			SlotSelectByPage();
			break;
		case 5:
			SlotSelectByOrigin();
			break;
		case 6:
			SlotSelectManualCreature();
			break;
		case 7:
			DeleteBtnDown();
			break;
		case 8:
			LockBtnDown();
			break;
		case 9:
			GroupBtnDown();
			break;
		case 10:
			GroupBtnDown();
			break;
		case 11:
			PasteBtnDown();
			break;
		case 12:
			SlotVisibleAll();
			break;
		case 13:
			SlotInvisibleAll();
			break;
		case 14:
			SlotInvisibleSelected();
			break;
		case 15:
			RotateBtnDown();
			break;
		case 16:
			MirrorBtnDown();
			break;
		case 17:
			UncoveredBtnDown();
			break;
		case 19:
			MultiSelectBtnDown();
			break;
		case 20:
			SeparateItemBtnDown();
			break;
	}
}

