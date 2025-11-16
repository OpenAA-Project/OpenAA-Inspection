#include "DisplayImageResource.h"
#define	_USE_MATH_DEFINES
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XTypeDef.h"
#include "XCrossObj.h"
#include "SelectPasteForm.h"
#include "XGeneralDialog.h"
#include "SelectByLibraryDialog.h"
#include "ExpandedPasteForm.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include <omp.h>
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
#include "XJpeg2000.h"
#include "XMacroFunction.h"
#include "XDataInLayerToDisplayImage.h"
#include "XGUIPacketGeneral.h"

void	DisplayImageWithAlgorithm::Initial(const QString &GUIRoot,const QString &GUIName)
{
	LayersBase		*LBase=GetLayersBase();
	if(LBase!=NULL){
		(*LBase)=new GUICmdReleaseSelectImagePanel	(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdOperationMove			(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdOperationMoveFromOutside	(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdReqMovedPage				(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdAckMovedPage				(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdSelectByOrigin			(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdReqAllItemsForSelect		(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdAckAllItemsForSelect		(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdReqSelectItemByID		(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdAckSelectItemByID		(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdReqSelectedItems			(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdAckSelectedItems			(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdSetMultiSelectMode		(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdReqChangeLibItem			(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdReqSelectedItemLibID		(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdAckSelectedItemLibID		(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdReqSelectedItemIDInLibID	(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdAckSelectedItemIDInLibID	(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdMakeOutlineItem			(LBase,GUIRoot,GUIName);
	}
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base!=NULL){
		(*LBase)=new GUICmdSelectItems				(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdSelectAll				(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdSelectByLibs				(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdCutItems					(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdOperationCopy			(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdOperationPaste			(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdOperationDelete			(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdOperationLock			(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdOperationUnlock			(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdOperationGroup			(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdReqItemsBmp				(this,Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdSendItemsBmp				(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdRegistArea				(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdActivateOnItem			(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdSendActivateOnItem		(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdInvisibleSelected		(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdReqTemporaryItems		(this,Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdAckTemporaryItems		(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdActivateOnItemDirect		(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdReqClearTemporaryItems	(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdSelectLocked				(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdSelectManualCreature		(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdVisibleAll				(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdReqRatate				(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdReqMirror				(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdSetActivateItem			(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdClearActivateItem		(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdPasteMatrix				(LBase,GUIRoot,GUIName);
		(*LBase)=new GUICmdReqShrink				(Base,GUIRoot,GUIName);
		(*LBase)=new GUICmdSeparateItems			(Base,GUIRoot,GUIName);

		(*LBase)=new SlaveCommSendTemporaryItems	(Base,GUIRoot,GUIName);
		(*LBase)=new SlaveCommSendFixTemporaryItems	(Base,GUIRoot,GUIName);
		(*LBase)=new SlaveCommReqPasteShape			(LBase,GUIRoot,GUIName);
		(*LBase)=new SlaveCommAckPasteShape			(LBase,GUIRoot,GUIName);
		(*LBase)=new SlaveCommReqPasteFromClipboard	(LBase,GUIRoot,GUIName);
		(*LBase)=new SlaveCommAckPasteFromClipboard	(LBase,GUIRoot,GUIName);
	}
}

void	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(GUICmdPacketBasePointerListContainer &GUICmdContainer
																		 ,LayersBase *Base
																		 ,const QString &sRoot ,const QString &sName 
																		 ,DisplayImage::DisplayType DType)
{
	GUICmdContainer=new GUICmdReqItemIndependentPack		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdSendIndependentPack			(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReqItemIndependentsPack		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReqSelectCopied				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReqCutByPasted				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdSyncDrawingMode				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReqItemCountOnLocalPoint		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdSendItemCountOnLocalPoint		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReqExpandedPaste				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReqSelectedItemListsForPaste	(Base,sRoot,sName);
	GUICmdContainer=new	GUICmdSendSelectedItemListsForPaste	(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReqDrawItemListsForPaste		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdSendDrawItemListsForPaste		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReqSelectByOrigin				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdAckSelectByOrigin				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReqSelectedItemCount			(Base,sRoot,sName);
	GUICmdContainer=new GUICmdSendSelectedItemCount			(Base,sRoot,sName);
	GUICmdContainer=new GUICmdSelectItemByID				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdSetItemNameInSelected			(Base,sRoot,sName);
	GUICmdContainer=new GUICmdSelectItemsByOriginType		(Base,sRoot,sName);
}

int	DisplayImageWithAlgorithm::SetPropertyInDLL(struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	ret=DisplayImage::SetPropertyInDLL(Data ,maxDataDim);
	if(ret<0){
		return -1;
	}
	if(ret+34>maxDataDim){
		return -1;
	}

	Data[ret+0].Type					=/**/"bool";
	Data[ret+0].VariableNameWithRoute=/**/"AlgoOptions.DrawBtn";
	Data[ret+0].Pointer				 =&AlgoOptions.DrawBtn;
	Data[ret+1].Type					=/**/"bool";
	Data[ret+1].VariableNameWithRoute=/**/"AlgoOptions.SelectBtn";
	Data[ret+1].Pointer				 =&AlgoOptions.SelectBtn;
	Data[ret+2].Type					=/**/"bool";
	Data[ret+2].VariableNameWithRoute=/**/"AlgoOptions.SelectMenuBtn";
	Data[ret+2].Pointer				 =&AlgoOptions.SelectMenuBtn;
	Data[ret+3].Type					=/**/"bool";
	Data[ret+3].VariableNameWithRoute=/**/"AlgoOptions.CutItemBtn";
	Data[ret+3].Pointer				 =&AlgoOptions.CutItemBtn;
	Data[ret+4].Type					=/**/"bool";
	Data[ret+4].VariableNameWithRoute=/**/"AlgoOptions.MoveItemBtn";
	Data[ret+4].Pointer				 =&AlgoOptions.MoveItemBtn;
	Data[ret+5].Type					=/**/"bool";
	Data[ret+5].VariableNameWithRoute=/**/"AlgoOptions.DeleteBtn";
	Data[ret+5].Pointer				 =&AlgoOptions.DeleteBtn;
	Data[ret+6].Type					=/**/"bool";
	Data[ret+6].VariableNameWithRoute=/**/"AlgoOptions.LockBtn";
	Data[ret+6].Pointer				 =&AlgoOptions.LockBtn;
	Data[ret+7].Type					=/**/"bool";
	Data[ret+7].VariableNameWithRoute=/**/"AlgoOptions.GroupBtn";
	Data[ret+7].Pointer				 =&AlgoOptions.GroupBtn;
	Data[ret+8].Type					=/**/"bool";
	Data[ret+8].VariableNameWithRoute=/**/"AlgoOptions.CopyBtn";
	Data[ret+8].Pointer				 =&AlgoOptions.CopyBtn;
	Data[ret+9].Type					=/**/"bool";
	Data[ret+9].VariableNameWithRoute=/**/"AlgoOptions.PasteBtn";
	Data[ret+9].Pointer				 =&AlgoOptions.PasteBtn;
	Data[ret+10].Type					=/**/"bool";
	Data[ret+10].VariableNameWithRoute=/**/"AlgoOptions.RegistAreaBtn";
	Data[ret+10].Pointer			 =&AlgoOptions.RegistAreaBtn;
	Data[ret+11].Type					=/**/"bool";
	Data[ret+11].VariableNameWithRoute=/**/"AlgoOptions.VisibleMenuBtn";
	Data[ret+11].Pointer			 =&AlgoOptions.VisibleMenuBtn;
	Data[ret+12].Type					=/**/"bool";
	Data[ret+12].VariableNameWithRoute=/**/"AlgoOptions.RotateBtn";
	Data[ret+12].Pointer			 =&AlgoOptions.RotateBtn;
	Data[ret+13].Type					=/**/"bool";
	Data[ret+13].VariableNameWithRoute=/**/"AlgoOptions.MirrorBtn";
	Data[ret+13].Pointer			 =&AlgoOptions.MirrorBtn;
	Data[ret+14].Type					=/**/"bool";
	Data[ret+14].VariableNameWithRoute=/**/"AlgoOptions.UncoveredBtn";
	Data[ret+14].Pointer			 =&AlgoOptions.UncoveredBtn;
	Data[ret+15].Type					=/**/"bool";
	Data[ret+15].VariableNameWithRoute=/**/"AlgoOptions.ItemMenuBtn";
	Data[ret+15].Pointer			 =&AlgoOptions.ItemMenuBtn;
	Data[ret+16].Type					=/**/"bool";
	Data[ret+16].VariableNameWithRoute=/**/"AlgoOptions.MultiSelectBtn";
	Data[ret+16].Pointer			 =&AlgoOptions.MultiSelectBtn;
	Data[ret+17].Type					=/**/"bool";
	Data[ret+17].VariableNameWithRoute=/**/"AlgoOptions.SeparateItemBtn";
	Data[ret+17].Pointer			 =&AlgoOptions.SeparateItemBtn;
	Data[ret+18].Type				 =/**/"TunableList";
	Data[ret+18].VariableNameWithRoute=/**/"ItemTunableList";
	Data[ret+18].Pointer			 =&ItemTunableList;

	Data[ret+19].Type					=/**/"QImage";
	Data[ret+19].VariableNameWithRoute	=/**/"IconItemImages.NoneIcon";
	Data[ret+19].Pointer				=&IconItemImages.NoneItemIcon;
	Data[ret+20].Type					=/**/"QImage";
	Data[ret+20].VariableNameWithRoute	=/**/"IconItemImages.DrawItemIcon";
	Data[ret+20].Pointer				=&IconItemImages.DrawItemIcon;
	Data[ret+21].Type					=/**/"QImage";
	Data[ret+21].VariableNameWithRoute	=/**/"IconItemImages.SelectItemIcon";
	Data[ret+21].Pointer				=&IconItemImages.SelectItemIcon;
	Data[ret+22].Type					=/**/"QImage";
	Data[ret+22].VariableNameWithRoute	=/**/"IconItemImages.SelectMenuItemIcon";
	Data[ret+22].Pointer				=&IconItemImages.SelectMenuItemIcon;
	Data[ret+23].Type					=/**/"QImage";
	Data[ret+23].VariableNameWithRoute	=/**/"IconItemImages.CutItemItemIcon";
	Data[ret+23].Pointer				=&IconItemImages.CutItemItemIcon;
	Data[ret+24].Type					=/**/"QImage";
	Data[ret+24].VariableNameWithRoute	=/**/"IconItemImages.MoveItemIcon";
	Data[ret+24].Pointer				=&IconItemImages.MoveItemIcon;
	Data[ret+25].Type					=/**/"QImage";
	Data[ret+25].VariableNameWithRoute	=/**/"IconItemImages.DeleteItemIcon";
	Data[ret+25].Pointer				=&IconItemImages.DeleteItemIcon;
	Data[ret+26].Type					=/**/"QImage";
	Data[ret+26].VariableNameWithRoute	=/**/"IconItemImages.LockItemIcon";
	Data[ret+26].Pointer				=&IconItemImages.LockItemIcon;
	Data[ret+27].Type					=/**/"QImage";
	Data[ret+27].VariableNameWithRoute	=/**/"IconItemImages.GroupItemIcon";
	Data[ret+27].Pointer				=&IconItemImages.GroupItemIcon;
	Data[ret+28].Type					=/**/"QImage";
	Data[ret+28].VariableNameWithRoute	=/**/"IconItemImages.CopyItemIcon";
	Data[ret+28].Pointer				=&IconItemImages.CopyItemIcon;
	Data[ret+29].Type					=/**/"QImage";
	Data[ret+29].VariableNameWithRoute	=/**/"IconItemImages.PasteItemIcon";
	Data[ret+29].Pointer				=&IconItemImages.PasteItemIcon;
	Data[ret+30].Type					=/**/"QImage";
	Data[ret+30].VariableNameWithRoute	=/**/"IconItemImages.RegistAreaItemIcon";
	Data[ret+30].Pointer				=&IconItemImages.RegistAreaItemIcon;
	Data[ret+31].Type					=/**/"QImage";
	Data[ret+31].VariableNameWithRoute	=/**/"IconItemImages.VisibleMenuItemIcon";
	Data[ret+31].Pointer				=&IconItemImages.VisibleMenuItemIcon;
	Data[ret+32].Type					=/**/"QImage";
	Data[ret+32].VariableNameWithRoute	=/**/"IconItemImages.RotateItemIcon";
	Data[ret+32].Pointer				=&IconItemImages.RotateItemIcon;
	Data[ret+33].Type					=/**/"QImage";
	Data[ret+33].VariableNameWithRoute	=/**/"IconItemImages.MirrorItemIcon";
	Data[ret+33].Pointer				=&IconItemImages.MirrorItemIcon;
	Data[ret+34].Type					=/**/"QImage";
	Data[ret+34].VariableNameWithRoute	=/**/"IconItemImages.UncoveredItemIcon";
	Data[ret+34].Pointer				=&IconItemImages.UncoveredItemIcon;
	Data[ret+35].Type					=/**/"QImage";
	Data[ret+35].VariableNameWithRoute	=/**/"IconItemImages.ItemMenuIcon";
	Data[ret+35].Pointer				=&IconItemImages.ItemMenuIcon;
	Data[ret+36].Type					=/**/"QImage";
	Data[ret+36].VariableNameWithRoute	=/**/"IconItemImages.MultiSelectIcon";
	Data[ret+36].Pointer				=&IconItemImages.MultiSelectIcon;
	Data[ret+37].Type					=/**/"QImage";
	Data[ret+37].VariableNameWithRoute	=/**/"IconItemImages.SeparateItemIcon";
	Data[ret+37].Pointer				=&IconItemImages.SeparateItemIcon;
	Data[ret+38].Type					=/**/"bool";
	Data[ret+38].VariableNameWithRoute=/**/"IconItemImages.ItemMenuIcon";
	Data[ret+38].Pointer				=&IconItemImages.ItemMenuIcon;

	return ret+39;
}

static	bool	MacroDrawRectItem(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<4){
		return false;
	}
	bool	ok;
	int	x1=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y1=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	x2=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y2=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	FlexArea	Area;
	Area.SetRectangle(x1,y1,x2,y2);
	V->DrawEndAfterOperation(Area);
	return true;
}
static	bool	MacroSelectItemInRect(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<4){
		return false;
	}
	bool	ok;
	int	x1=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y1=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	x2=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y2=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	FlexArea	Area;
	Area.SetRectangle(x1,y1,x2,y2);
	V->ExeSelectItems(Area);
	return true;
}
static	bool	MacroSelectAllItems(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotSelectAll();
	return true;
}
static	bool	MacroSelectAllLock(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotSelectLocked();
	return true;
}
static	bool	MacroReleaseAllSelection(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ExecuteReleaseAllSelection();
	return true;
}
static	bool	MacroCutItemInRect(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<4){
		return false;
	}
	bool	ok;
	int	x1=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y1=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	x2=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y2=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	FlexArea	Area;
	Area.SetRectangle(x1,y1,x2,y2);
	V->ExeCutItems(Area);
	return true;
}
static	bool	MacroMoveItem(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	int	dx=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	dy=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->ExecuteMove(dx,dy);
	return true;
}
static	bool	MacroDeleteItems(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ButtonExecuteDeleteSelected();
	return true;
}
static	bool	MacroLockItems(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ButtonExecuteLockSelected();
	return true;
}
static	bool	MacroUnlockItems(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ButtonExecuteUnlockAll();
	return true;
}
static	bool	MacroGroupItems(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ButtonExecuteGroupSelected();
	return true;
}
static	bool	MacroCopyItems(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ButtonExecuteCopySelected(true);
	return true;
}

static	bool	MacroSaveTopPastedItems(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString	FileName=Args[0];
	QFile	F(FileName);
	if(F.open(QIODevice::WriteOnly)==false){
		return false;
	}

	SelectPasteForm	*PForm=new SelectPasteForm(V,Instance->GetLayersBase());
	IntList	RowList;
	RowList.Add(0);
	if(PForm->SaveLine(&F,RowList)==false){
		return false;
	}
	delete	PForm;
	return true;
}
static	bool	MacroLoadPastedItems(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString	FileName=Args[0];
	QFile	F(FileName);
	if(F.open(QIODevice::ReadOnly)==false){
		return false;
	}

	SelectPasteForm	*PForm=new SelectPasteForm(V,Instance->GetLayersBase());
	if(PForm->LoadLine(&F)==false){
		return false;
	}
	delete	PForm;
	return true;
}

static	bool	MacroRotateItems(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	AngleDegree=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->ExecuteRotate(AngleDegree);

	return true;
}

static	bool	MacroMirrorItems(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	Kind=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}

	if(Kind==0){
		V->ExecuteMirror(AlgorithmItemRoot::_XMirror);
	}
	else{
		V->ExecuteMirror(AlgorithmItemRoot::_YMirror);
	}

	return true;
}

static	bool	MacroChangeItemName(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	V->ExecuteChangeItemName(Args[0]);

	return true;
}

static	bool	MacroSelectItems(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<3){
		return false;
	}
	struct	OriginTypeSelection SelectMode(NULL);
	if(Args.count()>=1 && Args[0].toLower()==/**/"true")
		SelectMode._FromUnknown=true;
	if(Args.count()>=2 && Args[1].toLower()==/**/"true")
		SelectMode._FromManual=true;
	if(Args.count()>=3 && Args[2].toLower()==/**/"true")
		SelectMode._FromCAD=true;
	if(Args.count()>=4 && Args[3].toLower()==/**/"true")
		SelectMode._FromMPA=true;

	V->ExecuteSelectItemsByOriginType(SelectMode);

	return true;
}

static	bool	MacroSelectItemsByLib(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	LibID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}

	V->ExeSelectItemsByLib(LibID);
	return true;
}
int32	DisplayImageWithAlgorithm::RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int	ret=DisplayImage::RegistMacroFunction(Functions,MaxBuffer);
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"DrawRectItem";
		Functions[ret].ArgName.append(/**/"Left");
		Functions[ret].ArgName.append(/**/"Top");
		Functions[ret].ArgName.append(/**/"Right");
		Functions[ret].ArgName.append(/**/"Bottom");
		Functions[ret].Explain.append(/**/"Draw rectangle item");
		Functions[ret].DLL_ExcuteMacro	=MacroDrawRectItem;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SelectItemInRect";
		Functions[ret].ArgName.append(/**/"Left");
		Functions[ret].ArgName.append(/**/"Top");
		Functions[ret].ArgName.append(/**/"Right");
		Functions[ret].ArgName.append(/**/"Bottom");
		Functions[ret].Explain.append(/**/"Select items in rectangle");
		Functions[ret].DLL_ExcuteMacro	=MacroSelectItemInRect;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SelectAllItems";
		Functions[ret].Explain.append(/**/"Select all items");
		Functions[ret].DLL_ExcuteMacro	=MacroSelectAllItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SelectAllLock";
		Functions[ret].Explain.append(/**/"Select all locked items");
		Functions[ret].DLL_ExcuteMacro	=MacroSelectAllLock;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ReleaseAllSelection";
		Functions[ret].Explain.append(/**/"Release all selection");
		Functions[ret].DLL_ExcuteMacro	=MacroReleaseAllSelection;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CutItemInRect";
		Functions[ret].ArgName.append(/**/"Left");
		Functions[ret].ArgName.append(/**/"Top");
		Functions[ret].ArgName.append(/**/"Right");
		Functions[ret].ArgName.append(/**/"Bottom");
		Functions[ret].Explain.append(/**/"Cut items in rectangle");
		Functions[ret].DLL_ExcuteMacro	=MacroCutItemInRect;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MoveItem";
		Functions[ret].ArgName.append(/**/"Dx");
		Functions[ret].ArgName.append(/**/"Dy");
		Functions[ret].Explain.append(/**/"Move selected items");
		Functions[ret].DLL_ExcuteMacro	=MacroMoveItem;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"DeleteItems";
		Functions[ret].Explain.append(/**/"Delete selected items");
		Functions[ret].DLL_ExcuteMacro	=MacroDeleteItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"LockItems";
		Functions[ret].Explain.append(/**/"Lock selected items");
		Functions[ret].DLL_ExcuteMacro	=MacroLockItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"UnlockItems";
		Functions[ret].Explain.append(/**/"Unlock selected items");
		Functions[ret].DLL_ExcuteMacro	=MacroUnlockItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"GroupItems";
		Functions[ret].Explain.append(/**/"Bind selected items into one");
		Functions[ret].DLL_ExcuteMacro	=MacroGroupItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CopyItems";
		Functions[ret].Explain.append(/**/"Copy selected items");
		Functions[ret].DLL_ExcuteMacro	=MacroCopyItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SaveTopPastedItems";
		Functions[ret].ArgName.append(/**/"File name");
		Functions[ret].Explain.append(/**/"Save top pasted items");
		Functions[ret].DLL_ExcuteMacro	=MacroSaveTopPastedItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"LoadPastedItems";
		Functions[ret].ArgName.append(/**/"File name");
		Functions[ret].Explain.append(/**/"Load pasted items");
		Functions[ret].DLL_ExcuteMacro	=MacroLoadPastedItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"RotateItems";
		Functions[ret].ArgName.append(/**/"Angle degree");
		Functions[ret].Explain.append(/**/"Rotate selected items");
		Functions[ret].DLL_ExcuteMacro	=MacroRotateItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MirrorItems";
		Functions[ret].ArgName.append(/**/"X-axis:0 ,Y-axis:1");
		Functions[ret].Explain.append(/**/"Mirror selected items");
		Functions[ret].DLL_ExcuteMacro	=MacroMirrorItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ChangeItemName";
		Functions[ret].ArgName.append(/**/"Item name");
		Functions[ret].Explain.append(/**/"Change item name in selected items");
		Functions[ret].DLL_ExcuteMacro	=MacroChangeItemName;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SelectItems";
		Functions[ret].ArgName.append(/**/"Select AutoGenerated items (true/false)");
		Functions[ret].ArgName.append(/**/"Select manual created items (true/false)");
		Functions[ret].ArgName.append(/**/"Select CAD-created items (true/false)");
		Functions[ret].Explain.append(/**/"Selected items");
		Functions[ret].DLL_ExcuteMacro	=MacroSelectItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SelectItemsByLibID";
		Functions[ret].ArgName.append(/**/"LibID");
		Functions[ret].Explain.append(/**/"Select items by LibraryID");
		Functions[ret].DLL_ExcuteMacro	=MacroSelectItemsByLib;
		ret++;
	}
	return ret;
}
