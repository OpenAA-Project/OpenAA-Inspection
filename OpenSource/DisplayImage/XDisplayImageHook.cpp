#include "DisplayImageResource.h"
#include "XGUIFormBase.h"
#include "XTypeDef.h"
#include "XCrossObj.h"
#include "XGeneralFunc.h"
#include <omp.h>
#include <math.h>
#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "XDisplayImage.h"
#include "XDisplayImageHook.h"



FunctionServerClass::~FunctionServerClass(void)
{
	/*
	for(DisplayImagePointerList *p=PointerList.GetFirst();p!=NULL;p=p->GetNext()){
		p->Pointer->ReleaseHook(this);
	}
	*/
	PointerList.RemoveAll();
}

void	FunctionServerClass::SetHookedDisplayImage(GUIFormBase *t)
{
	DisplayImagePointerList *p=new DisplayImagePointerList(t);
	PointerList.AppendList(p);
}

void	FunctionServerClass::DeleteTarget(GUIFormBase *f)
{
	for(DisplayImagePointerList *p=PointerList.GetFirst();p!=NULL;){
		if(p->Pointer==f){
			DisplayImagePointerList *NextP=p->GetNext();
			PointerList.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}
}


DisplayImageHooked::~DisplayImageHooked(void)
{
	HookedFunctionListPaintFirstPack		.RemoveAll();
	HookedFunctionListPaintLastPack			.RemoveAll();
	HookedFunctionListMouseMovePack			.RemoveAll();
	HookedFunctionListLClickPack			.RemoveAll();
	HookedFunctionListLClickPackOnFree		.RemoveAll();
	HookedFunctionListLClickWithShiftPack	.RemoveAll();
	HookedFunctionListLDoubleClickPack		.RemoveAll();
	HookedFunctionListRClickPack			.RemoveAll();
	HookedFunctionListRClickPackOnFree		.RemoveAll();
	HookedFunctionListRClickWithShiftPack	.RemoveAll();
	HookedFunctionListDrawEndPack			.RemoveAll();
}

void	DisplayImageHooked::ReleaseHook(FunctionServerClass *f)
{
	for(HookedFunctionListPaintFirst *p=HookedFunctionListPaintFirstPack.GetFirst();p!=NULL;){
		if(p->Obj==f){
			HookedFunctionListPaintFirst *NextP=p->GetNext();
			HookedFunctionListPaintFirstPack.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListPaintLast *p=HookedFunctionListPaintLastPack.GetFirst();p!=NULL;){
		if(p->Obj==f){
			HookedFunctionListPaintLast *NextP=p->GetNext();
			HookedFunctionListPaintLastPack.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListMouseMove *p=HookedFunctionListMouseMovePack.GetFirst();p!=NULL;){
		if(p->Obj==f){
			HookedFunctionListMouseMove *NextP=p->GetNext();
			HookedFunctionListMouseMovePack.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListLClick *p=HookedFunctionListLClickPack.GetFirst();p!=NULL;){
		if(p->Obj==f){
			HookedFunctionListLClick *NextP=p->GetNext();
			HookedFunctionListLClickPack.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListLClickOnFree *p=HookedFunctionListLClickPackOnFree.GetFirst();p!=NULL;){
		if(p->Obj==f){
			HookedFunctionListLClickOnFree *NextP=p->GetNext();
			HookedFunctionListLClickPackOnFree.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListLClickWithShift *p=HookedFunctionListLClickWithShiftPack.GetFirst();p!=NULL;){
		if(p->Obj==f){
			HookedFunctionListLClickWithShift *NextP=p->GetNext();
			HookedFunctionListLClickWithShiftPack.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListLDoubleClick *p=HookedFunctionListLDoubleClickPack.GetFirst();p!=NULL;){
		if(p->Obj==f){
			HookedFunctionListLDoubleClick *NextP=p->GetNext();
			HookedFunctionListLDoubleClickPack.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListRClick *p=HookedFunctionListRClickPack.GetFirst();p!=NULL;){
		if(p->Obj==f){
			HookedFunctionListRClick *NextP=p->GetNext();
			HookedFunctionListRClickPack.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListRClickOnFree *p=HookedFunctionListRClickPackOnFree.GetFirst();p!=NULL;){
		if(p->Obj==f){
			HookedFunctionListRClickOnFree *NextP=p->GetNext();
			HookedFunctionListRClickPackOnFree.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListRClickWithShift *p=HookedFunctionListRClickWithShiftPack.GetFirst();p!=NULL;){
		if(p->Obj==f){
			HookedFunctionListRClickWithShift *NextP=p->GetNext();
			HookedFunctionListRClickWithShiftPack.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListDrawEnd *p=HookedFunctionListDrawEndPack.GetFirst();p!=NULL;){
		if(p->Obj==f){
			HookedFunctionListDrawEnd *NextP=p->GetNext();
			HookedFunctionListDrawEndPack.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}
}

int	DisplayImageHooked::HookedFunctionBase::CompareBase(DisplayImageHooked::HookedFunctionBase &src)
{	
	GUIFormBase *a=dynamic_cast<GUIFormBase *>(Obj);
	GUIFormBase *b=dynamic_cast<GUIFormBase *>(src.Obj);
	if(a!=NULL && b!=NULL){
		int32	ta=a->GetShowingOrder();
		int32	tb=b->GetShowingOrder();
		return ta-tb;
	}
	return 0;
}



void	DisplayImageHooked::SetHookInPaintFirst(FunctionServerClass *Obj,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,QPainter &pnt ,QImage &PntImage),bool HighestPriority)
{
	for(HookedFunctionListPaintFirst *p=HookedFunctionListPaintFirstPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Obj==Obj && p->Function==Function){
			if(HighestPriority==true){
				HookedFunctionListPaintFirstPack.RemoveList(p);
				HookedFunctionListPaintFirstPack.InsertList(0,p);
			}
			return;
		}
	}
	HookedFunctionListPaintFirst *a=new HookedFunctionListPaintFirst(Obj);
	a->Function=Function;
	if(HighestPriority==true){
		HookedFunctionListPaintFirstPack.InsertList(0,a);
	}
	else{
		HookedFunctionListPaintFirstPack.AppendList(a);
	}
	Obj->SetHookedDisplayImage(DisplayImageInst);
	HookedFunctionListPaintFirstPack.Sort();
}
void	DisplayImageHooked::SetHookInPaintLast(FunctionServerClass *Obj,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,QPainter &pnt ,QImage &PntImage),bool HighestPriority)
{
	for(HookedFunctionListPaintLast *p=HookedFunctionListPaintLastPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Obj==Obj && p->Function==Function){
			if(HighestPriority==true){
				HookedFunctionListPaintLastPack.RemoveList(p);
				HookedFunctionListPaintLastPack.InsertList(0,p);
			}
			return;
		}
	}
	HookedFunctionListPaintLast *a=new HookedFunctionListPaintLast(Obj);
	a->Function=Function;
	if(HighestPriority==true){
		HookedFunctionListPaintLastPack.InsertList(0,a);
	}
	else{
		HookedFunctionListPaintLastPack.AppendList(a);
	}
	Obj->SetHookedDisplayImage(DisplayImageInst);
	HookedFunctionListPaintLastPack.Sort();

	GUIFormBase	*Form;
	for(HookedFunctionListPaintLast *p=HookedFunctionListPaintLastPack.GetFirst();p!=NULL;p=p->GetNext()){
		Form=dynamic_cast<GUIFormBase	*>(p->Obj);
	}
}
void	DisplayImageHooked::SetHookInMouseMove(FunctionServerClass *Obj,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY),bool HighestPriority)
{
	for(HookedFunctionListMouseMove *p=HookedFunctionListMouseMovePack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Obj==Obj && p->Function==Function){
			if(HighestPriority==true){
				HookedFunctionListMouseMovePack.RemoveList(p);
				HookedFunctionListMouseMovePack.InsertList(0,p);
			}
			return;
		}
	}
	HookedFunctionListMouseMove *a=new HookedFunctionListMouseMove(Obj);
	a->Function=Function;
	if(HighestPriority==true){
		HookedFunctionListMouseMovePack.InsertList(0,a);
	}
	else{
		HookedFunctionListMouseMovePack.AppendList(a);
	}
	Obj->SetHookedDisplayImage(DisplayImageInst);
	HookedFunctionListMouseMovePack.Sort();
}
void	DisplayImageHooked::SetHookInMouseLClick(FunctionServerClass *Obj,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY),bool HighestPriority)
{
	for(HookedFunctionListLClick *p=HookedFunctionListLClickPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Obj==Obj && p->Function==Function){
			if(HighestPriority==true){
				HookedFunctionListLClickPack.RemoveList(p);
				HookedFunctionListLClickPack.InsertList(0,p);
			}
			return;
		}
	}
	HookedFunctionListLClick *a=new HookedFunctionListLClick(Obj);
	a->Function=Function;
	if(HighestPriority==true){
		HookedFunctionListLClickPack.InsertList(0,a);
	}
	else{
		HookedFunctionListLClickPack.AppendList(a);
	}
	Obj->SetHookedDisplayImage(DisplayImageInst);
	HookedFunctionListLClickPack.Sort();
}
void	DisplayImageHooked::SetHookInMouseLClickOnFree(FunctionServerClass *Obj,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY),bool HighestPriority)
{
	for(HookedFunctionListLClickOnFree *p=HookedFunctionListLClickPackOnFree.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Obj==Obj && p->Function==Function){
			if(HighestPriority==true){
				HookedFunctionListLClickPackOnFree.RemoveList(p);
				HookedFunctionListLClickPackOnFree.InsertList(0,p);
			}
			return;
		}
	}
	HookedFunctionListLClickOnFree *a=new HookedFunctionListLClickOnFree(Obj);
	a->Function=Function;
	if(HighestPriority==true){
		HookedFunctionListLClickPackOnFree.InsertList(0,a);
	}
	else{
		HookedFunctionListLClickPackOnFree.AppendList(a);
	}
	Obj->SetHookedDisplayImage(DisplayImageInst);
	HookedFunctionListLClickPackOnFree.Sort();
}
void	DisplayImageHooked::SetHookInMouseLClickWithShift(FunctionServerClass *Obj,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY),bool HighestPriority)
{
	for(HookedFunctionListLClickWithShift *p=HookedFunctionListLClickWithShiftPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Obj==Obj && p->Function==Function){
			if(HighestPriority==true){
				HookedFunctionListLClickWithShiftPack.RemoveList(p);
				HookedFunctionListLClickWithShiftPack.InsertList(0,p);
			}
			return;
		}
	}
	HookedFunctionListLClickWithShift *a=new HookedFunctionListLClickWithShift(Obj);
	a->Function=Function;
	if(HighestPriority==true){
		HookedFunctionListLClickWithShiftPack.InsertList(0,a);
	}
	else{
		HookedFunctionListLClickWithShiftPack.AppendList(a);
	}
	Obj->SetHookedDisplayImage(DisplayImageInst);
	HookedFunctionListLClickWithShiftPack.Sort();
}
void	DisplayImageHooked::SetHookInMouseLDoubleClick(FunctionServerClass *Obj,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY),bool HighestPriority)
{
	for(HookedFunctionListLDoubleClick *p=HookedFunctionListLDoubleClickPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Obj==Obj && p->Function==Function){
			if(HighestPriority==true){
				HookedFunctionListLDoubleClickPack.RemoveList(p);
				HookedFunctionListLDoubleClickPack.InsertList(0,p);
			}
			return;
		}
	}
	HookedFunctionListLDoubleClick *a=new HookedFunctionListLDoubleClick(Obj);
	a->Function=Function;
	if(HighestPriority==true){
		HookedFunctionListLDoubleClickPack.InsertList(0,a);
	}
	else{
		HookedFunctionListLDoubleClickPack.AppendList(a);
	}
	Obj->SetHookedDisplayImage(DisplayImageInst);
	HookedFunctionListLDoubleClickPack.Sort();
}
void	DisplayImageHooked::SetHookInMouseRClick(FunctionServerClass *Obj,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY),bool HighestPriority)
{
	for(HookedFunctionListRClick *p=HookedFunctionListRClickPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Obj==Obj && p->Function==Function){
			if(HighestPriority==true){
				HookedFunctionListRClickPack.RemoveList(p);
				HookedFunctionListRClickPack.InsertList(0,p);
			}
			return;
		}
	}
	HookedFunctionListRClick *a=new HookedFunctionListRClick(Obj);
	a->Function=Function;
	if(HighestPriority==true){
		HookedFunctionListRClickPack.InsertList(0,a);
	}
	else{
		HookedFunctionListRClickPack.AppendList(a);
	}
	Obj->SetHookedDisplayImage(DisplayImageInst);
	HookedFunctionListRClickPack.Sort();
}
void	DisplayImageHooked::SetHookInMouseRClickOnFree(FunctionServerClass *Obj,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY),bool HighestPriority)
{
	for(HookedFunctionListRClickOnFree *p=HookedFunctionListRClickPackOnFree.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Obj==Obj && p->Function==Function){
			if(HighestPriority==true){
				HookedFunctionListRClickPackOnFree.RemoveList(p);
				HookedFunctionListRClickPackOnFree.InsertList(0,p);
			}
			return;
		}
	}
	HookedFunctionListRClickOnFree *a=new HookedFunctionListRClickOnFree(Obj);
	a->Function=Function;
	if(HighestPriority==true){
		HookedFunctionListRClickPackOnFree.InsertList(0,a);
	}
	else{
		HookedFunctionListRClickPackOnFree.AppendList(a);
	}
	Obj->SetHookedDisplayImage(DisplayImageInst);
	HookedFunctionListRClickPackOnFree.Sort();
}
void	DisplayImageHooked::SetHookInMouseRClickWithShift(FunctionServerClass *Obj,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY),bool HighestPriority)
{
	for(HookedFunctionListRClickWithShift *p=HookedFunctionListRClickWithShiftPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Obj==Obj && p->Function==Function){
			if(HighestPriority==true){
				HookedFunctionListRClickWithShiftPack.RemoveList(p);
				HookedFunctionListRClickWithShiftPack.InsertList(0,p);
			}
			return;
		}
	}
	HookedFunctionListRClickWithShift *a=new HookedFunctionListRClickWithShift(Obj);
	a->Function=Function;
	if(HighestPriority==true){
		HookedFunctionListRClickWithShiftPack.InsertList(0,a);
	}
	else{
		HookedFunctionListRClickWithShiftPack.AppendList(a);
	}
	Obj->SetHookedDisplayImage(DisplayImageInst);
	HookedFunctionListRClickWithShiftPack.Sort();
}
void	DisplayImageHooked::SetHookInDrawEnd(FunctionServerClass *Obj,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *),bool HighestPriority)
{
	for(HookedFunctionListDrawEnd *p=HookedFunctionListDrawEndPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Obj==Obj && p->Function==Function){
			if(HighestPriority==true){
				HookedFunctionListDrawEndPack.RemoveList(p);
				HookedFunctionListDrawEndPack.InsertList(0,p);
			}
			return;
		}
	}
	HookedFunctionListDrawEnd *a=new HookedFunctionListDrawEnd(Obj);
	a->Function=Function;
	if(HighestPriority==true){
		HookedFunctionListDrawEndPack.InsertList(0,a);
	}
	else{
		HookedFunctionListDrawEndPack.AppendList(a);
	}
	Obj->SetHookedDisplayImage(DisplayImageInst);
	HookedFunctionListDrawEndPack.Sort();
}

void	DisplayImageHooked::RemoveHook(FunctionServerClass *Obj)
{
	for(HookedFunctionListPaintFirst *p=HookedFunctionListPaintFirstPack.GetFirst();p!=NULL;){
		if(p->Obj==Obj){
			HookedFunctionListPaintFirst	*PNext=p->GetNext();
			HookedFunctionListPaintFirstPack.RemoveList(p);
			delete	p;
			p=PNext;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListPaintLast *p=HookedFunctionListPaintLastPack.GetFirst();p!=NULL;){
		if(p->Obj==Obj){
			HookedFunctionListPaintLast	*PNext=p->GetNext();
			HookedFunctionListPaintLastPack.RemoveList(p);
			delete	p;
			p=PNext;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListMouseMove *p=HookedFunctionListMouseMovePack.GetFirst();p!=NULL;){
		if(p->Obj==Obj){
			HookedFunctionListMouseMove	*PNext=p->GetNext();
			HookedFunctionListMouseMovePack.RemoveList(p);
			delete	p;
			p=PNext;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListLClick *p=HookedFunctionListLClickPack.GetFirst();p!=NULL;){
		if(p->Obj==Obj){
			HookedFunctionListLClick	*PNext=p->GetNext();
			HookedFunctionListLClickPack.RemoveList(p);
			delete	p;
			p=PNext;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListLClickOnFree *p=HookedFunctionListLClickPackOnFree.GetFirst();p!=NULL;){
		if(p->Obj==Obj){
			HookedFunctionListLClickOnFree	*PNext=p->GetNext();
			HookedFunctionListLClickPackOnFree.RemoveList(p);
			delete	p;
			p=PNext;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListLClickWithShift *p=HookedFunctionListLClickWithShiftPack.GetFirst();p!=NULL;){
		if(p->Obj==Obj){
			HookedFunctionListLClickWithShift	*PNext=p->GetNext();
			HookedFunctionListLClickWithShiftPack.RemoveList(p);
			delete	p;
			p=PNext;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListLDoubleClick *p=HookedFunctionListLDoubleClickPack.GetFirst();p!=NULL;){
		if(p->Obj==Obj){
			HookedFunctionListLDoubleClick	*PNext=p->GetNext();
			HookedFunctionListLDoubleClickPack.RemoveList(p);
			delete	p;
			p=PNext;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListRClick *p=HookedFunctionListRClickPack.GetFirst();p!=NULL;){
		if(p->Obj==Obj){
			HookedFunctionListRClick	*PNext=p->GetNext();
			HookedFunctionListRClickPack.RemoveList(p);
			delete	p;
			p=PNext;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListRClickOnFree *p=HookedFunctionListRClickPackOnFree.GetFirst();p!=NULL;){
		if(p->Obj==Obj){
			HookedFunctionListRClickOnFree	*PNext=p->GetNext();
			HookedFunctionListRClickPackOnFree.RemoveList(p);
			delete	p;
			p=PNext;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListRClickWithShift *p=HookedFunctionListRClickWithShiftPack.GetFirst();p!=NULL;){
		if(p->Obj==Obj){
			HookedFunctionListRClickWithShift	*PNext=p->GetNext();
			HookedFunctionListRClickWithShiftPack.RemoveList(p);
			delete	p;
			p=PNext;
		}
		else{
			p=p->GetNext();
		}
	}
	for(HookedFunctionListDrawEnd *p=HookedFunctionListDrawEndPack.GetFirst();p!=NULL;){
		if(p->Obj==Obj){
			HookedFunctionListDrawEnd	*PNext=p->GetNext();
			HookedFunctionListDrawEndPack.RemoveList(p);
			delete	p;
			p=PNext;
		}
		else{
			p=p->GetNext();
		}
	}
}

void	DisplayImageHooked::SetDisplayImageInst(DisplayImage *p)
{	
	DisplayImageInst=p;
}

DisplayImage *DisplayImageHooked::GetDisplayImageInst(void)
{	
	return (DisplayImage *)DisplayImageInst;
}


bool	DisplayImageHooked::HookedExecutePaintFirst(QPainter &pnt ,QImage &PntImage)
{
	HookResult=true;
	for(HookedFunctionListPaintFirst *p=HookedFunctionListPaintFirstPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Function(p->Obj,DisplayImageInst,pnt ,PntImage)==false){
			HookResult=false;
			break;
		}
	}
	return HookResult;
}
bool	DisplayImageHooked::HookedExecutePaintLast(QPainter &pnt ,QImage &PntImage)
{
	HookResult=true;
	GUIFormBase	*Form;
	for(HookedFunctionListPaintLast *p=HookedFunctionListPaintLastPack.GetFirst();p!=NULL;p=p->GetNext()){
		//Form=dynamic_cast<GUIFormBase	*>(p->Obj);
		if(p->Function(p->Obj,DisplayImageInst,pnt ,PntImage)==false){
			HookResult=false;
			break;
		}
	}
	return HookResult;
}
bool	DisplayImageHooked::HookedExecuteMouseMove(int GlobalPosX,int GlobalPosY)
{
	HookResult=true;
	for(HookedFunctionListMouseMove *p=HookedFunctionListMouseMovePack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Function(p->Obj,DisplayImageInst,GlobalPosX,GlobalPosY)==false){
			HookResult=false;
			break;
		}
	}
	return HookResult;
}
bool	DisplayImageHooked::HookedExecuteLClick(int GlobalPosX,int GlobalPosY)
{
	HookResult=true;
	for(HookedFunctionListLClick *p=HookedFunctionListLClickPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Function(p->Obj,DisplayImageInst,GlobalPosX,GlobalPosY)==false){
			HookResult=false;
			break;
		}
	}
	return HookResult;
}
bool	DisplayImageHooked::HookedExecuteLClickOnFree(int GlobalPosX,int GlobalPosY)
{
	HookResult=true;
	for(HookedFunctionListLClickOnFree *p=HookedFunctionListLClickPackOnFree.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Function(p->Obj,DisplayImageInst,GlobalPosX,GlobalPosY)==false){
			HookResult=false;
			break;
		}
	}
	return HookResult;
}
bool	DisplayImageHooked::HookedExecuteLClickWithShift(int GlobalPosX,int GlobalPosY)
{
	HookResult=true;
	for(HookedFunctionListLClickWithShift *p=HookedFunctionListLClickWithShiftPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Function(p->Obj,DisplayImageInst,GlobalPosX,GlobalPosY)==false){
			HookResult=false;
			break;
		}
	}
	return HookResult;
}
bool	DisplayImageHooked::HookedExecuteLDoubleClick(int GlobalPosX,int GlobalPosY)
{
	HookResult=true;
	for(HookedFunctionListLDoubleClick *p=HookedFunctionListLDoubleClickPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Function(p->Obj,DisplayImageInst,GlobalPosX,GlobalPosY)==false){
			HookResult=false;
			break;
		}
	}
	return HookResult;
}
bool	DisplayImageHooked::HookedExecuteRClick(int GlobalPosX,int GlobalPosY)
{
	bool	Ret=true;
	for(HookedFunctionListRClick *p=HookedFunctionListRClickPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Function(p->Obj,DisplayImageInst,GlobalPosX,GlobalPosY)==false){
			Ret=false;
			break;
		}
	}
	return Ret;
}
bool	DisplayImageHooked::HookedExecuteRClickOnFree(int GlobalPosX,int GlobalPosY)
{
	bool	Ret=true;
	for(HookedFunctionListRClickOnFree *p=HookedFunctionListRClickPackOnFree.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Function(p->Obj,DisplayImageInst,GlobalPosX,GlobalPosY)==false){
			Ret=false;
			break;
		}
	}
	return Ret;
}
bool	DisplayImageHooked::HookedExecuteRClickWithShift(int GlobalPosX,int GlobalPosY)
{
	bool	Ret=true;
	for(HookedFunctionListRClickWithShift *p=HookedFunctionListRClickWithShiftPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Function(p->Obj,DisplayImageInst,GlobalPosX,GlobalPosY)==false){
			Ret=false;
			break;
		}
	}
	return Ret;
}
bool	DisplayImageHooked::HookedExecuteDrawEnd(void)
{
	HookResult=true;
	for(HookedFunctionListDrawEnd *p=HookedFunctionListDrawEndPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Function(p->Obj,DisplayImageInst)==false){
			HookResult=false;
			break;
		}
	}
	return HookResult;
}
