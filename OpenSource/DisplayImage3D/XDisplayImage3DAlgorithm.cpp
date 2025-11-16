#include "XDisplayImage3D.h"
#include "XGUIDLL.h"
#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "XCriticalFunc.h"
#include "XDisplayImage3DPacket.h"
#include <QMenu>
#include <QMessageBox>


void	DisplayImage3DAlgo::DrawNoneBtnBtnDown()
{
	if(MainCanvas!=NULL){
		SetMode(mtFrameDraw3D::fdNone,MainCanvas->GetFrameColor());
	}
	ButtonExecuteDraw();
	SetAlterSomething();
	GetLayersBase()->SetStatusModes(this,/**/"ItemNone");
}

void	DisplayImage3DAlgo::ItemDrawBtnDown()
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
					if(RCmd.Mode==mtFrameDraw3D::fdNone){
						CmdPanelSetButton	SCmd(GetLayersBase());
						SCmd.Mode=mtFrameDraw3D::fdRectangle;
						s->TransmitDirectly(&SCmd);
					}
				}
			}
		}
	}
	if(ItemDrawBtn->isChecked()==true){
		AllUpImagePanel();
		NoneButtonDown();
	}

	SetDrawingMode(_Normal);
	//ButtonExecuteDraw();
	SetAlterSomething();
	GetLayersBase()->SetStatusModes(this,/**/"ItemDraw");
}

void	DisplayImage3DAlgo::ItemSelectBtnDown()
{
	ButtonExecuteSelectArea();
	if(MainCanvas!=NULL){
		if(MainCanvas->GetMode()==mtFrameDraw3D::fdNone){
			SetMode(mtFrameDraw3D::fdRectangle ,Qt::red);
		}
	}
	SetAlterSomething();
	GetLayersBase()->SetStatusModes(this,/**/"ItemSelect");
}
void	DisplayImage3DAlgo::ItemSelectMenuBtnDown()
{
	QMenu	Menu(this);
	Menu.addAction ("Select All"			, this, SLOT(SlotSelectAll()));
	Menu.addAction ("Select locked items"	, this, SLOT(SlotSelectLocked()));
	Menu.addAction ("Select by Library"		, this, SLOT(SlotSelectLibrary()));
	if(GetPageNumb()>1){
		Menu.addAction ("Select by Page"			, this, SLOT(SlotSelectByPage()));
	}
	Menu.addAction ("Select by Origin"				, this, SLOT(SlotSelectByOrigin()));
	Menu.addAction ("Select manual creature"		, this, SLOT(SlotSelectManualCreature()));
	Menu.addAction ("Select and move by ID/ItemName", this, SLOT(SlotSelectByItemIDName()));
	AddMenuSelectMenuBtn(Menu);

	QPoint	Q=mapToGlobal(ItemSelectMenuBtn->geometry().center());
	Menu.exec(Q);
}

void	DisplayImage3DAlgo::ItemMoveItemBtnDown()
{
	if(ItemMoveItemBtn->isChecked()==true){
		AllUpImagePanel();
		SetDrawingMode(_ItemMoveWait);
		SetMode(mtFrameDraw3D::fdNone ,Qt::red);
		//SetDrawingMode(_ItemMoveWait);
		SetCursor(mtFrameDraw3D::fdMove);
		SetAlterSomething();
		GetLayersBase()->SetStatusModes(this,/**/"ItemMove");
	}
	else{
		if(ItemNoneBtn!=NULL){
			NoneBtn->setChecked(true);
			DrawNoneBtnBtnDown();
		}
	}
}
void	DisplayImage3DAlgo::MoveStart(void)
{
	DisplayImage::MoveStart();
	if(MoveItemBtn!=NULL){
		MoveItemBtn->setChecked(true);
		MoveItemBtnDown();
	}
}
void	DisplayImage3DAlgo::MoveStart(int globalX ,int globalY)
{
	DisplayImage::MoveStart(globalX ,globalY);
}
void	DisplayImage3DAlgo::ItemDeleteBtnDown()
{
	GetLayersBase()->ShowProcessingForm("Delete items");
	ButtonExecuteDeleteSelected();
	SetAlterSomething();
	GetLayersBase()->CloseProcessingForm();
}
void	DisplayImage3DAlgo::ItemLockBtnDown()
{
	QMenu	Menu(this);
	Menu.addAction ("Lock selected items"	, this, SLOT(SlotLockBtnDown()));
	Menu.addAction ("Unlock all"			, this, SLOT(SlotUnlockBtnDown()));
	AddMenuLockBtn(Menu);

	QPoint	Q=mapToGlobal(ItemLockBtn->geometry().center());
	Menu.exec(Q);

}

void	DisplayImage3DAlgo::SlotLockBtnDown()
{
	ButtonExecuteLockSelected();
	SetAlterSomething();
}
void	DisplayImage3DAlgo::SlotUnlockBtnDown()
{
	ButtonExecuteUnlockAll();
	SetAlterSomething();
}

void	DisplayImage3DAlgo::ItemGroupBtnDown()
{
	if(QMessageBox::warning(NULL
					,"Make bind to Group"
					, "Do you bind selected items to make group?"
					,QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){							
		ButtonExecuteGroupSelected();
		SetAlterSomething();
	}
}
void	DisplayImage3DAlgo::ItemCopyBtnDown()
{
	GetLayersBase()->ShowProcessingForm("Copy items");
	ButtonExecuteCopySelected(true);
	SetAlterSomething();
	GetLayersBase()->CloseProcessingForm();
}
void	DisplayImage3DAlgo::ItemPasteBtnDown()
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
void	DisplayImage3DAlgo::ItemSlotSelectAll()
{
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
void	DisplayImage3DAlgo::ItemSlotSelectLocked()
{
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
void	DisplayImage3DAlgo::ItemSlotSelectLibrary()
{
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
void	DisplayImage3DAlgo::ItemExeSelectItemsByLib(int LibID)
{
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

void	DisplayImage3DAlgo::ItemSlotSelectByPage()
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
void	DisplayImage3DAlgo::ItemSlotSelectByOrigin()
{
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
void	DisplayImage3DAlgo::ItemSlotSelectManualCreature()
{
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

void	DisplayImage3DAlgo::ButtonExecuteSelectByPage(int globalPage)
{
	GUICmdSelectAll	Cmd(GetAlgorithmBase(),EmitterRoot,EmitterName ,globalPage);
	Cmd.LayerList=LayerList;
	if(Cmd.SendOnly(globalPage,1)==false){
		SetError(Error_Comm , /**/"Send error :ButtonExecuteSelectByPage",ErrorCodeList::_Alart);
	}
}
void	DisplayImage3DAlgo::ItemSlotSelectByItemIDName()
{
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


void	DisplayImage3DAlgo::ItemRotateBtnDown()
{
	InputRotate	D(GetLayersBase(),this);
	if(D.exec()==(int)true){
		ExecuteRotate(D.Angle);
	}
}
void	DisplayImage3DAlgo::ItemMirrorBtnDown()
{
	InputMirror	D(GetLayersBase(),this);
	if(D.exec()==(int)true){
		ExecuteMirror(D.MirrorMode);
	}
}

void	DisplayImage3DAlgo::ItemSlotEditItemName()
{
	EditItemNameDialog	D(GetLayersBase(),/**/"");
	if(D.exec()==(int)true){
		ExecuteChangeItemName(D.ItemName);
	}
}

void	DisplayImage3DAlgo::SlotVisibleAll()
{
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
void	DisplayImage3DAlgo::SlotInvisibleAll()
{
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
void	DisplayImage3DAlgo::SlotInvisibleSelected()
{
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

void	DisplayImage3DAlgo::CanvasSlotDrawEnd(void)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base==NULL){
		return;
	}
	if(MainCanvas!=NULL){
		if(ItemSelectBtn!=NULL && ItemSelectBtn->isChecked()==true){
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
	}
	ExecuteAfterDrawEnd();
	SetAlterSomething();
	Repaint();
}


void	DisplayImage3DAlgo::ButtonExecuteDraw(void)
{
	AllUpImagePanel();
}

void	DisplayImage3DAlgo::ButtonExecuteSelectArea(void)
{
	AllUpImagePanel();
	SetAlterSomething();
}

void	DisplayImage3DAlgo::ButtonExecuteDeleteSelected(void)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
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
void	DisplayImage3DAlgo::ButtonExecuteLockSelected(void)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
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

void	DisplayImage3DAlgo::ButtonExecuteUnlockAll(void)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
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
void	DisplayImage3DAlgo::ButtonExecuteGroupSelected(void)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
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

void	DisplayImage3DAlgo::ButtonExecuteCopySelected(bool EnableDup)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
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

void	DisplayImage3DAlgo::ButtonExecutePasteInSameAlgorithm(void)
{
	//GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Paste in same algorithm");

	if(MainCanvas!=NULL){
		SetMode(mtFrameDraw3D::fdNone,MainCanvas->GetFrameColor());
	}
	DrawingMode=_PasteMovePreStart;
	MoveCurrentGlobalX=MoveStartGlobalX=0;
	MoveCurrentGlobalY=MoveStartGlobalY=0;
	AllUpToolButton();
	AllUpImagePanel();
}

void	DisplayImage3DAlgo::ButtonExecutePasteInSameAlgorithmSamePos(void)
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

void	DisplayImage3DAlgo::ButtonExecutePasteInFixedPos(void)
{
	//GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Paste in fexed position");

	if(MainCanvas!=NULL){
		SetMode(mtFrameDraw3D::fdNone,MainCanvas->GetFrameColor());
	}
	DrawingMode=_PasteCreateShapeStart;
	MoveCurrentGlobalX=MoveStartGlobalX=0;
	MoveCurrentGlobalY=MoveStartGlobalY=0;
	AllUpToolButton();
	AllUpImagePanel();
}

void	DisplayImage3DAlgo::ExecuteReleaseAllSelection(void)
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
void	DisplayImage3DAlgo::ExecuteAfterDrawEnd(void)
{
}

void	DisplayImage3DAlgo::ButtonExecutePaste(void)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
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


void	DisplayImage3DAlgo::PutRectangle(int x1,int y1 ,int x2,int y2)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.RectangleData.x1	=x1;
		GetRawSDataPoint()->UData.RectangleData.y1	=y1;
		GetRawSDataPoint()->UData.RectangleData.x2	=x2;
		GetRawSDataPoint()->UData.RectangleData.y2	=y2;
	}
	CanvasSlotDrawEnd();
}

void	DisplayImage3DAlgo::PutEndlessLine(int x ,int y ,double s)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.LineData.x=x;
		GetRawSDataPoint()->UData.LineData.y=y;
		GetRawSDataPoint()->UData.LineData.s=s;
	}
	CanvasSlotDrawEnd();
}

void	DisplayImage3DAlgo::PutLine(int x1,int y1 ,int x2,int y2)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.ChoppedLineData.x1	=x1;
		GetRawSDataPoint()->UData.ChoppedLineData.y1	=y1;
		GetRawSDataPoint()->UData.ChoppedLineData.x2	=x2;
		GetRawSDataPoint()->UData.ChoppedLineData.y2	=y2;
	}
	CanvasSlotDrawEnd();
}

void	DisplayImage3DAlgo::PutHalfLine(int x ,int y ,double s ,double length)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.HalfLineData.x=x;
		GetRawSDataPoint()->UData.HalfLineData.y=y;
		GetRawSDataPoint()->UData.HalfLineData.s=s;
	}
	CanvasSlotDrawEnd();
}

void	DisplayImage3DAlgo::PutEllipse(int cx, int cy, int rx ,int ry)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.EllipseData.cx	=cx;
		GetRawSDataPoint()->UData.EllipseData.cy	=cy;
		GetRawSDataPoint()->UData.EllipseData.rx	=rx;
		GetRawSDataPoint()->UData.EllipseData.ry	=ry;
	}
	CanvasSlotDrawEnd();
}
void	DisplayImage3DAlgo::PutCircle(int cx, int cy, int r)
{
	if(MainCanvas!=NULL){
		GetRawSDataPoint()->UData.CircleData.cx	=cx;
		GetRawSDataPoint()->UData.CircleData.cy	=cy;
		GetRawSDataPoint()->UData.CircleData.r	=r;
	}
	CanvasSlotDrawEnd();
}
void	DisplayImage3DAlgo::PutLongCircle(int cx1, int cy1, int cx2, int cy2, int r)
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

void	DisplayImage3DAlgo::PutRotRectangle(int cx, int cy ,int width ,int height ,double s)
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

void	DisplayImage3DAlgo::PutRotEllipse(int cx, int cy, int rx ,int ry ,double s)
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

void	DisplayImage3DAlgo::PutArc(int cx, int cy, int rx ,int ry ,double StartS ,double EndS)
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

void	DisplayImage3DAlgo::PutRing(int cx, int cy, int rx1 ,int ry1 , int rx2 ,int ry2)
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

void	DisplayImage3DAlgo::ExecuteSelectItemsByOriginType	(struct	OriginTypeSelection &SelectMode)
{
	QString emitterRoot;
	QString emitterName;
	QString AlgoRoot;
	QString AlgoName;

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


void	DisplayImage3DAlgo::ExecuteActiveOnItemXY(int globalX ,int globalY)
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
void	DisplayImage3DAlgo::ExecuteActiveOnItem(int globalPage ,int layer ,int itemID)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	GUICmdActivateOnItemDirect	Cmd(Base,EmitterRoot ,EmitterName,globalPage);
	Cmd.Layer=layer;
	Cmd.ItemID=itemID;
	if(Cmd.SendOnly(globalPage ,0)==false){
		SetError(Error_Comm , /**/"Send error :ExecuteActiveOnItem",ErrorCodeList::_Alart);
	}
}