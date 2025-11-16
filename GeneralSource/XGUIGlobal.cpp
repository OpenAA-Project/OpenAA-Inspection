/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGUIGlobal.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include<QSqlQuery>
#include "XGUI.h"
#include "XErrorCode.h"
#include <string.h>
#include "XGeneralFunc.h"
#include <QBuffer>
#include "XParamGlobal.h"

#if defined(ModeEditGUI)
#include "itemlistwindow.h"
#include "propertylist.h"
extern	ItemListWindow* MainItem;
extern	PropertyList* MainProperty;

#endif // defined(ModeEditGUI)

#include "XDataInLayer.h"
#include "XDataInExe.h"
#include "XDatabase.h"
#include "XGUIFormBase.h"
#include "XGUIInterfaceDLL.h"

int		GUIItemInstance::GetUnitPos(int x)
{
	int	u=GetGridUnitForEditMode();
	return (x/u)*u;
}
void	GUIItemInstance::SlotRelease()
{
	if(Handle!=NULL){
		GUIPositionX1=GetUnitPos(Handle->geometry().left());
		GUIPositionY1=GetUnitPos(Handle->geometry().top());
		Handle->move(GUIPositionX1,GUIPositionY1);

		GUIPositionX2=Handle->geometry().right();
		GUIPositionY2=Handle->geometry().bottom();
#if defined(ModeEditGUI)
		if(MainProperty!=NULL){
			MainProperty->Repaint();
		}
#endif
	}
}
void	GUIItemInstance::SlotMove()
{
	if(Handle!=NULL){
		int	dx=Handle->geometry().left() -GUIPositionX1;
		int	dy=Handle->geometry().top()  -GUIPositionY1;
		GUIPositionX1=Handle->geometry().left();
		GUIPositionY1=Handle->geometry().top();
		GUIPositionX2=Handle->geometry().right();
		GUIPositionY2=Handle->geometry().bottom();

		if(Handle->GetSelectedInEditMode()==true){
			for(GUIInstancePack *p=GetLayersBase()->GetGuiInitializer()->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
				for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
					if(g==this)
						continue;
					if(g->Handle->GetSelectedInEditMode()==true){
						g->Handle->move(dx+g->Handle->geometry().left(),dy+g->Handle->geometry().top());
					}
				}
			}
		}

#if defined(ModeEditGUI)
		if(MainProperty!=NULL){
			MainProperty->Repaint();
		}
#endif
	}
}
void	GUIItemInstance::SlotResize()
{
	if(Handle!=NULL){
		GUIPositionX1=Handle->geometry().left();
		GUIPositionY1=Handle->geometry().top();
		GUIPositionX2=Handle->geometry().right();
		GUIPositionY2=Handle->geometry().bottom();
#if defined(ModeEditGUI)
		if(MainProperty!=NULL){
			MainProperty->Repaint();
		}
#endif
	}
}

GUIFormBase *SearchName(QObject *Parent,const QString &FormName)
{
	GUIFormBase	*f=dynamic_cast<GUIFormBase	*>(Parent);
	if(f!=NULL){
		if(f->GetName()==FormName)
			return f;
	}
	QObjectList List=Parent->children ();
	for(int i=0;i<List.count();i++){
		GUIFormBase	*h=SearchName(List[i],FormName);
		if(h!=NULL){
			return h;
		}
	}
	return NULL;
}


GUIFormBase		*EntryPointForGlobal::GUIMouseLeftDownInEdit(GUIFormBase *Current ,QMouseEvent * Event)
{

#if defined(ModeEditGUI)
	GUIInitializer	*GD=Current->GetLayersBase()->GetGuiInitializer();
	ItemButtonList	*p=MainItem->GetActiveButton();
	if(p!=NULL){
		GuiDLLItem	*G=p->DLLPoint;
		if(G!=NULL){
			//GUIFormBase	*f=G->CreateInstance();
			//if(f!=NULL){
			GUIItemInstance	*Inst=new GUIItemInstance(GD->GetGUIInstanceRoot(),G);
			//Inst->Handle=f;
			int	GridUnitForEditMode=GD->GetGridUnitForEditMode();
			Inst->Parent	=GD->GetGUIInstanceRoot();
			Inst->InstanceID=GD->GetGUIInstanceRoot()->GetMaxInstanceID()+1;
			GUIItemInstance *parentOfCurrent=GD->GetGUIInstanceRoot()->Search(Current);
			if(parentOfCurrent!=NULL){
				Inst->ParentInstanceID=parentOfCurrent->InstanceID;
			}
			else{
				for(QWidget	*PCurrent=Current;PCurrent!=NULL;PCurrent=PCurrent->parentWidget()){
					GUIFormBase	*NowCurrent=dynamic_cast<GUIFormBase *>(PCurrent);
					if(NowCurrent!=NULL){
						parentOfCurrent=GD->GetGUIInstanceRoot()->Search(NowCurrent);
						if(parentOfCurrent!=NULL){
							Inst->ParentInstanceID=parentOfCurrent->InstanceID;
							break;
						}
					}
				}
			}
			DWORD ErrorCode;
			if(Inst->Initial(Current->GetLayersBase(),Current,ErrorCode ,G)==false){
				return(NULL);
			}
			GUIFormBase	*f=Inst->Handle;
			GD->GetGUIInstanceRoot()->AppendList(Inst);
	
			int	x=Event->x();
			int	y=Event->y();

			//x=(x/Current->GetGridUnitForEditMode())*Current->GetGridUnitForEditMode();
			//y=(y/Current->GetGridUnitForEditMode())*Current->GetGridUnitForEditMode();

			GUIFormBase	*PutTop=Current->GetTopSurfaceWidget(x,y);
			f->setParent(PutTop);
			int	tx=PutTop->mapFromGlobal(Event->globalPos()).x();
			int	ty=PutTop->mapFromGlobal(Event->globalPos()).y();
			tx=(tx/Current->GetGridUnitForEditMode())*Current->GetGridUnitForEditMode();
			ty=(ty/Current->GetGridUnitForEditMode())*Current->GetGridUnitForEditMode();
			f->move(tx,ty);
			f->ReflectAlignment();
			f->InitialPrepare();
			f->Prepare();
			if(GetLayersBase()->GetEntryPoint()->GUIIsEditMode()==true){
				f->SetEditMode();
				f->CreateSelectedWindow();
				Inst->connect(Inst->Handle,SIGNAL(SignalMove()),Inst,SLOT(SlotMove()));
				Inst->connect(Inst->Handle,SIGNAL(SignalResize()),Inst,SLOT(SlotResize()));
				Inst->connect(Inst->Handle,SIGNAL(SignalRelease()),Inst,SLOT(SlotRelease()));
			}
			f->SetGridUnitForEditMode(GridUnitForEditMode);

			for(int t=1;t<1000;t++){
				QString	FormName=Inst->DLLAccess->GetDLLName()+QString::number(t);
				GUIFormBase	*TopClass=f->GetTopClass();
				if(TopClass!=NULL){
					if(SearchName(TopClass,FormName)==NULL){
						f->SetName(FormName);
						break;
					}
				}
			}
			f->CreatedInEditMode(PutTop);

			f->show();
			
			p->setUnchecked();
			Current->GetLayersBase()->GetEntryPoint()->GUISetProperty(f,PutTop);
			if(MainProperty!=NULL){
				MainProperty->Repaint();
			}
			Inst->GUIPositionX1=f->geometry().left();
			Inst->GUIPositionY1=f->geometry().top();
			Inst->GUIPositionX2=f->geometry().right();
			Inst->GUIPositionY2=f->geometry().bottom();
			return(f);			
		}
	}
#endif
	return(NULL);
}

