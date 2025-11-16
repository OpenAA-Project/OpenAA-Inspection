/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignment\PropertyAlignmentForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyAlignmentFormResource.h"
#include "PropertyAlignmentForm.h"
#include "XGeneralFunc.h"
#include "AlignmentImagePropertyPacket.h"
#include "InputAlignmentAreaForm.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "InputAlignmentPointForm.h"
#include "InputAlignmentGroupForm.h"
#include "XDisplayImagePacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//==============================================================================

PropertyAlignmentForm::PropertyAlignmentForm(LayersBase *Base,QWidget *parent)
    : GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	ui.tableWidgetArea->setColumnWidth (0,40);
	ui.tableWidgetArea->setColumnWidth (1,40);
	ui.tableWidgetArea->setColumnWidth (2,40);
	ui.tableWidgetArea->setColumnWidth (3,110);
	ui.tableWidgetArea->setColumnWidth (4,90);

	ui.tableWidgetPoint->setColumnWidth (0,80);
	ui.tableWidgetPoint->setColumnWidth (1,80);
	ui.tableWidgetPoint->setColumnWidth (2,40);
	ui.tableWidgetPoint->setColumnWidth (3,40);
	ui.tableWidgetPoint->setColumnWidth (4,40);

	ShowAreaGrid();
	InstallIgnoreKeyForChild();
}

void	PropertyAlignmentForm::BuildForShow(void)
{
	ShowAreaGrid();
}

PropertyAlignmentForm::~PropertyAlignmentForm()
{

}

void	PropertyAlignmentForm::StartPage(void)
{
	ui.toolButtonArea->setChecked(true);
	ShowAreaGrid();
}

void	PropertyAlignmentForm::ShowAreaGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendAlignmentAreaList	**BmpReceiver=new GUICmdSendAlignmentAreaList*[GetLayersBase()->GetPageNumb()];
	GUICmdReqAlignmentAreaList	**BmpRequester=new GUICmdReqAlignmentAreaList*[GetLayersBase()->GetPageNumb()];
	int	N=0;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		BmpReceiver[N]=new GUICmdSendAlignmentAreaList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[N]=new GUICmdReqAlignmentAreaList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		N++;
	}
	AreaList.RemoveAll();
	for(int n=0;n<N;n++){
		if(BmpRequester[n]->Send(BmpRequester[n]->GetGlobalPage(),0,*BmpReceiver[n])==true){
			AreaList+=BmpReceiver[n]->Area;
		}
	}

	for(int i=0;i<N;i++){
		delete	BmpRequester[i];
		delete	BmpReceiver[i];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	ui.tableWidgetArea->setRowCount(AreaList.GetNumber());
	N=0;
	for(AlignmentAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext(),N++){
		QTableWidgetItem *w;
		w=ui.tableWidgetArea->item (N, 0);
		if(w==NULL)
			ui.tableWidgetArea->setItem(N,0,(w=new QTableWidgetItem()));
		w->setText(QString::number(a->GlobalPage));
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		w=ui.tableWidgetArea->item (N, 1);
		if(w==NULL)
			ui.tableWidgetArea->setItem(N,1,(w=new QTableWidgetItem()));
		w->setText(QString::number(a->Layer));
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		w=ui.tableWidgetArea->item (N, 2);
		if(w==NULL)
			ui.tableWidgetArea->setItem(N,2,(w=new QTableWidgetItem()));
		w->setText(QString::number(a->AreaID));
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		w=ui.tableWidgetArea->item (N, 3);
		if(w==NULL)
			ui.tableWidgetArea->setItem(N,3,(w=new QTableWidgetItem()));
		w->setText(a->AreaName);
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		w=ui.tableWidgetArea->item (N, 4);
		if(w==NULL)
			ui.tableWidgetArea->setItem(N,4,(w=new QTableWidgetItem()));
		w->setText(QString::number(a->XSize)
						+ QString(/**/",")
						+ QString::number(a->YSize));
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}

	ReEntrant=false;
}

void	PropertyAlignmentForm::ShowPointGrid(AlignmentAreaList *A)
{
	PointList.RemoveAll();
	CreatePointList(A);
	ShowPointGridRaw();
}

void	PropertyAlignmentForm::CreatePointList(AlignmentAreaList *A)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	int	globalPage=A->GlobalPage;
	GUICmdSendAlignmentPointList BmpReceiver (GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	GUICmdReqAlignmentPointList	 BmpRequester(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	BmpRequester.Layer =A->Layer;
	BmpRequester.Number=A->Number;

	if(BmpRequester.Send(BmpRequester.GetGlobalPage(),0,BmpReceiver)==true){
		PointList+=BmpReceiver.Points;
	}
	ReEntrant=false;
}
void	PropertyAlignmentForm::ShowPointGridRaw(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;
	ui.tableWidgetPoint->setRowCount(PointList.GetNumber());
	int	N=0;
	for(AlignmentPointList *a=PointList.GetFirst();a!=NULL;a=a->GetNext(),N++){
		QTableWidgetItem *w;
		w=ui.tableWidgetPoint->item (N, 0);
		if(w==NULL)
			ui.tableWidgetPoint->setItem(N,0,(w=new QTableWidgetItem()));
		w->setText(QString::number(a->Cx)
						+ QString(/**/",")
						+ QString::number(a->Cy));
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		w=ui.tableWidgetPoint->item (N, 1);
		if(w==NULL)
			ui.tableWidgetPoint->setItem(N,1,(w=new QTableWidgetItem()));
		w->setText(QString::number(a->XSize)
						+ QString(/**/",")
						+ QString::number(a->YSize));
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		w=ui.tableWidgetPoint->item (N, 2);
		if(w==NULL)
			ui.tableWidgetPoint->setItem(N,2,(w=new QTableWidgetItem()));
		w->setText(QString::number(a->GroupNumber));
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		w=ui.tableWidgetPoint->item (N, 3);
		if(w==NULL)
			ui.tableWidgetPoint->setItem(N,3,(w=new QTableWidgetItem()));
		if(a->AlignmentOnOutline==true)
			w->setText(LangSolver.GetString(PropertyAlignmentForm_LS,LID_3)/*"Outline"*/);
		else
			w->setText(LangSolver.GetString(PropertyAlignmentForm_LS,LID_4)/*"Pattern"*/);
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		w=ui.tableWidgetPoint->item (N, 4);
		if(w==NULL)
			ui.tableWidgetPoint->setItem(N,4,(w=new QTableWidgetItem()));
		w->setText(QString::number(a->SearchDot));
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}
	ReEntrant=false;
}

//==============================================================================


void PropertyAlignmentForm::on_tableWidgetArea_clicked(const QModelIndex &)
{
	CreateAndShowPointGrid();
	for(int page=0;page<GetPageNumb();page++){
		GUICmdSetActiveAreas	RCmd(GetLayersBase(),sRoot,sName,page);

		QList<QTableWidgetItem *> Q=ui.tableWidgetArea->selectedItems ();
		for(int i=0;i<Q.count();i++){
			QTableWidgetItem *qi=Q.value(i);
			if(qi->column()!=0)
				continue;
			AlignmentAreaList *a=AreaList.GetItem(qi->row());
			if(a==NULL)
				continue;
			ReqAlignmentAreaList	*qa=new ReqAlignmentAreaList();
			qa->AreaID		=a->AreaID;
			qa->GlobalPage	=a->GlobalPage;
			qa->Layer		=a->Layer;

			RCmd.ActiveAreas.AppendList(qa);
		}
		RCmd.SendOnly(page,0);
	}
	BroadcastShowInEdit();
}
void PropertyAlignmentForm::CreateAndShowPointGrid(void)
{
	QList<QTableWidgetItem *> Q=ui.tableWidgetArea->selectedItems ();
	PointList.RemoveAll();
	for(int i=0;i<Q.count();i++){
		QTableWidgetItem *qi=Q.value(i);
		if(qi->column()!=0)
			continue;
		AlignmentAreaList *a=AreaList.GetItem(qi->row());
		if(a==NULL)
			continue;
		CreatePointList(a);
	}
	ShowPointGridRaw();
}

void	PropertyAlignmentForm::TransmitDirectly(GUIDirectMessage *packet)
{
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdAlignmentDrawEnd	*Da=dynamic_cast<GUICmdAlignmentDrawEnd *>(packet);
	if(Da!=NULL){
		IntList	PageList;
		int	PageN=GetLayersBase()->GetLocalPageFromArea(Da->Area ,PageList);
		if(PageN<=0)
			return;
		CmdReqImageLayer	RLayer(GetLayersBase(),GetLayerNumb(0));
		GUIFormBase	*GProp=GetImageControlToolsPointer();
		if(GProp!=NULL)
			GProp->TransmitDirectly(&RLayer);

		if(ui.toolButtonArea->isChecked()==true){
			InputAlignmentAreaForm	D(false,GetLayersBase(),/**/"",this);
			if(D.exec()==QDialog::Accepted){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create Alignment area");

				for(IntClass *PList=PageList.GetFirst();PList!=NULL;PList=PList->GetNext()){
					int	LocalPage=PList->GetValue();
					int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);

					FlexArea	A=Da->Area;
					GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(A);				
					for(IntClass *dLayer=RLayer.LayerList.GetFirst();dLayer!=NULL;dLayer=dLayer->GetNext()){
						GUICmdReqAlignmentPutArea	DNewMsg(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
						DNewMsg.Area		=A;
						DNewMsg.AreaName	=D.AreaName;
						DNewMsg.LimitedLib	=D.GetSelectedList();
						DNewMsg.GlobalPage	=globalPage;
						DNewMsg.Layer		=dLayer->GetValue();
						DNewMsg.Priority	=D.Priority;
						DNewMsg.Send(NULL,globalPage ,0);
					}
				}
			}
			ShowAreaGrid();
			for(int r=0;r<ui.tableWidgetArea->rowCount();r++){
				for(int c=0;c<ui.tableWidgetArea->columnCount();c++){
					QTableWidgetItem	*p=ui.tableWidgetArea->item(r,c);
					p->setSelected(false);
				}
			}
			AreaListFromMaster.RemoveAll();
		}
		else if(ui.toolButtonPoint->isChecked()==true){
			QList<QTableWidgetItem *> Q=ui.tableWidgetArea->selectedItems ();
			if(Q.count()==0)
				return;
			InputAlignmentPointForm	D(GetLayersBase(),NULL);
			if(D.exec()==QDialog::Accepted){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create Alignment point");

				for(int i=0;i<Q.count();i++){
					QTableWidgetItem *qi=Q.value(i);
					if(qi->column()!=0)
						continue;
					AlignmentAreaList *a=AreaList.GetItem(qi->row());
					if(a==NULL)
						continue;
					int	globalPage	=a->GlobalPage;
					int	LocalPage	=GetLayersBase()->GetLocalPageFromGlobal(globalPage);

					GUICmdReqAlignmentPutPoint	DNewMsg(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
					DNewMsg.PointArea=Da->Area;
					DNewMsg.MoveDot				=D.MoveDot;		
					DNewMsg.Threshold			=D.Threshold;
					DNewMsg.AlignmentOnOutline	=D.AlignmentOnOutline;	//?O?s?A?E?u???i?1??E?e?A??atrue
					GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(DNewMsg.PointArea);
					if(DNewMsg.PointArea.GetPatternByte()>9){
						DNewMsg.GlobalPage=globalPage;
						DNewMsg.Layer	  =a->Layer;
						DNewMsg.AreaID	  =a->AreaID;
						DNewMsg.Send(NULL,globalPage ,0);					
					}
				}
			}
			PointList.RemoveAll();
			for(int i=0;i<Q.count();i++){
				QTableWidgetItem *qi=Q.value(i);
				if(qi->column()!=0)
					continue;
				AlignmentAreaList *a=AreaList.GetItem(qi->row());
				if(a==NULL)
					continue;
				CreatePointList(a);
			}
			ShowPointGridRaw();
		}
		else if(ui.toolButtonGroup->isChecked()==true){
			QList<QTableWidgetItem *> Q=ui.tableWidgetArea->selectedItems ();
			if(Q.count()==0)
				return;
			InputAlignmentGroupForm	D(GetLayersBase(),NULL);
			if(D.exec()==QDialog::Accepted){
				for(int i=0;i<Q.count();i++){
					QTableWidgetItem *qi=Q.value(i);
					if(qi->column()!=0)
						continue;
					AlignmentAreaList *a=AreaList.GetItem(qi->row());
					if(a==NULL)
						continue;
					int	globalPage	=a->GlobalPage;
					int	LocalPage	=GetLayersBase()->GetLocalPageFromGlobal(globalPage);
					FlexArea	A=Da->Area;
					GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(A);
					for(IntClass *dLayer=RLayer.LayerList.GetFirst();dLayer!=NULL;dLayer=dLayer->GetNext()){
						GUICmdReqAlignmentPutGroup	DNewMsg(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
						DNewMsg.GroupArea=A;
						DNewMsg.GroupNumber	=D.Group;
						DNewMsg.GlobalPage=globalPage;
						DNewMsg.Layer	  =dLayer->GetValue();
						DNewMsg.AreaID	  =a->AreaID;
						DNewMsg.Send(NULL,globalPage ,0);
					}
				}
			}
			PointList.RemoveAll();
			for(int i=0;i<Q.count();i++){
				QTableWidgetItem *qi=Q.value(i);
				if(qi->column()!=0)
					continue;
				AlignmentAreaList *a=AreaList.GetItem(qi->row());
				if(a==NULL)
					continue;
				CreatePointList(a);
			}
			ShowPointGridRaw();
		}
		return;
	}
	GUICmdReqAlignmentDrawMode	*DMode=dynamic_cast<GUICmdReqAlignmentDrawMode *>(packet);
	if(DMode!=NULL){
		if(ui.toolButtonArea->isChecked()==true)
			DMode->Mode=AlignmentDrawAttr::_Area;
		if(ui.toolButtonGroup->isChecked()==true)
			DMode->Mode=AlignmentDrawAttr::_Group;
		if(ui.toolButtonPoint->isChecked()==true)
			DMode->Mode=AlignmentDrawAttr::_Point;
		QList<QTableWidgetItem *> Q=ui.tableWidgetArea->selectedItems ();
		for(int i=0;i<Q.count();i++){
			QTableWidgetItem *qi=Q.value(i);
			if(qi->column()!=0)
				continue;
			AlignmentAreaList *a=AreaList.GetItem(qi->row());
			if(a==NULL)
				continue;
			ReqAlignmentAreaList	*qa=new ReqAlignmentAreaList();
			qa->AreaID		=a->AreaID;
			qa->GlobalPage	=a->GlobalPage;
			qa->Layer		=a->Layer;

			DMode->AList.AppendList(qa);
		}
		DMode->AList+=AreaListFromMaster;
		return;
	}
	GUICmdAlignmentReflectChangeItems	*ReDrawMode=dynamic_cast<GUICmdAlignmentReflectChangeItems *>(packet);
	if(ReDrawMode!=NULL){
		ShowAreaGrid();
		CreateAndShowPointGrid();
		return;
	}
	GetSelectedAlignmentAreaPacket	*SAArea=dynamic_cast<GetSelectedAlignmentAreaPacket *>(packet);
	if(SAArea!=NULL){
		QList<QTableWidgetItem *> Q=ui.tableWidgetArea->selectedItems ();
		for(int i=0;i<Q.count();i++){
			QTableWidgetItem *qi=Q.value(i);
			if(qi->column()!=0)
				continue;
			AlignmentAreaList *a=AreaList.GetItem(qi->row());
			SAArea->SelectedArea.AppendList(new ListLayerAndID(a->Layer,a->AreaID));
		}
		return;
	}
	CmdIsModeItemEditingPacket	*CmdIsModeItemEditingPacketVar=dynamic_cast<CmdIsModeItemEditingPacket *>(packet);
	if(CmdIsModeItemEditingPacketVar!=NULL){
		if(ui.toolButtonArea->isChecked()==true)
			CmdIsModeItemEditingPacketVar->ItemMode=CmdIsModeItemEditingPacket::_AreaMode;
		else if(ui.toolButtonPoint->isChecked()==true)
			CmdIsModeItemEditingPacketVar->ItemMode=CmdIsModeItemEditingPacket::_ItemMode;
		else if(ui.toolButtonGroup->isChecked()==true)
			CmdIsModeItemEditingPacketVar->ItemMode=CmdIsModeItemEditingPacket::_GroupMode;
		return;
	}
	CmdSetActiveAreas	*CmdSetActiveAreasVar=dynamic_cast<CmdSetActiveAreas *>(packet);
	if(CmdSetActiveAreasVar!=NULL){
		ShowAreaGrid();
		for(int r=0;r<ui.tableWidgetArea->rowCount();r++){
			for(int c=0;c<ui.tableWidgetArea->columnCount();c++){
				QTableWidgetItem	*p=ui.tableWidgetArea->item(r,c);
				p->setSelected(false);
			}
		}
		for(ReqAlignmentAreaList *L=CmdSetActiveAreasVar->ActiveAreas.GetFirst();L!=NULL;L=L->GetNext()){
			int	Row=0;
			for(AlignmentAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
				if(L->GlobalPage==a->GlobalPage
				&& L->Layer		==a->Layer
				&& L->AreaID	==a->AreaID){
					for(int c=0;c<ui.tableWidgetArea->columnCount();c++){
						QTableWidgetItem	*p=ui.tableWidgetArea->item(Row,c);
						p->setSelected(true);
					}
				}
			}
		}
		AreaListFromMaster=CmdSetActiveAreasVar->ActiveAreas;
		return;
	}
	CmdAddArea	*CmdAddAreaVar=dynamic_cast<CmdAddArea *>(packet);
	if(CmdAddAreaVar!=NULL){
		for(int r=0;r<ui.tableWidgetArea->rowCount();r++){
			for(int c=0;c<ui.tableWidgetArea->columnCount();c++){
				QTableWidgetItem	*p=ui.tableWidgetArea->item(r,c);
				p->setSelected(false);
			}
		}
		return;
	}
	GUICmdClickAreaButton *GUICmdClickAreaButtonVar=dynamic_cast<GUICmdClickAreaButton *>(packet);
	if(GUICmdClickAreaButtonVar!=NULL){
		ui.toolButtonArea->setChecked(true);
	}
	GUICmdClickPointButton *GUICmdClickPointButtonVar=dynamic_cast<GUICmdClickPointButton *>(packet);
	if(GUICmdClickPointButtonVar!=NULL){
		ui.toolButtonPoint->setChecked(true);
	}
	GUICmdClickGroupButton *GUICmdClickGroupButtonVar=dynamic_cast<GUICmdClickGroupButton *>(packet);
	if(GUICmdClickGroupButtonVar!=NULL){
		ui.toolButtonGroup->setChecked(true);
	}
}

void	PropertyAlignmentForm::CreateAlignmentArea(FlexArea &area)
{
	IntList	PageList;
	int	PageN=GetLayersBase()->GetLocalPageFromArea(area ,PageList);
	if(PageN<=0)
		return;
	CmdReqImageLayer	RLayer(GetLayersBase(),GetLayerNumb(0));
	GUIFormBase	*GProp=GetImageControlToolsPointer();
	if(GProp!=NULL)
		GProp->TransmitDirectly(&RLayer);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create Alignment area");

	for(IntClass *PList=PageList.GetFirst();PList!=NULL;PList=PList->GetNext()){
		int	LocalPage=PList->GetValue();
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);

		FlexArea	A=area;
		GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(A);				
		for(IntClass *dLayer=RLayer.LayerList.GetFirst();dLayer!=NULL;dLayer=dLayer->GetNext()){
			GUICmdReqAlignmentPutArea	DNewMsg(GetLayersBase(),sRoot,sName,globalPage);
			DNewMsg.Area		=A;
			DNewMsg.AreaName	=/**/"";
			DNewMsg.GlobalPage	=globalPage;
			DNewMsg.Layer		=dLayer->GetValue();
			DNewMsg.Priority	=XAlignmentArea::_PriorityMiddle;
			DNewMsg.Send(NULL,globalPage ,0);
		}
	}
	ShowAreaGrid();
	for(int r=0;r<ui.tableWidgetArea->rowCount();r++){
		for(int c=0;c<ui.tableWidgetArea->columnCount();c++){
			QTableWidgetItem	*p=ui.tableWidgetArea->item(r,c);
			p->setSelected(false);
		}
	}
	AreaListFromMaster.RemoveAll();
}
GUIFormBase	*PropertyAlignmentForm::GetImageControlToolsPointer(void)
{
	GUIFormBase *RetGUI[1000];
	int	N=GetLayersBase()->EnumGUIInst(/**/"Button" ,/**/"ImageControlTools" ,RetGUI ,sizeof(RetGUI)/sizeof(RetGUI[0]));

	GUIFormBase	*ImagePanel=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AlignmentImagePanel" ,/**/"");
	if(ImagePanel==NULL)
		return NULL;
	QString	ImageName=ImagePanel->GetName();

	for(int i=0;i<N;i++){
		ImageControlTools	*ImageControlToolsPointer=dynamic_cast<ImageControlTools *>(RetGUI[i]);
		if(ImageControlToolsPointer!=NULL){
			if(ImageControlToolsPointer->RelatedPanels.contains(ImageName)==true){
				return ImageControlToolsPointer;
			}
		}
	}
	return NULL;
}

void	PropertyAlignmentForm::CreateAlignmentPoint(FlexArea &area ,int MoveDot ,int Threshold ,bool AlignmentOnOutline)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create Alignment point");

	for(AlignmentAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext()){
		int	globalPage	=a->GlobalPage;
		int	LocalPage	=GetLayersBase()->GetLocalPageFromGlobal(globalPage);

		GUICmdReqAlignmentPutPoint	DNewMsg(GetLayersBase(),sRoot,sName,globalPage);
		DNewMsg.PointArea			=area;
		DNewMsg.MoveDot				=MoveDot;
		DNewMsg.Threshold			=Threshold;
		DNewMsg.AlignmentOnOutline	=AlignmentOnOutline;	//?O?s?A?E?u???i?1??E?e?A??atrue
		GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(DNewMsg.PointArea);
		if(DNewMsg.PointArea.GetPatternByte()>9){
			DNewMsg.GlobalPage=globalPage;
			DNewMsg.Layer	  =a->Layer;
			DNewMsg.AreaID	  =a->AreaID;
			DNewMsg.Send(NULL,globalPage ,0);					
		}
	}
	PointList.RemoveAll();

	for(AlignmentAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext()){
		CreatePointList(a);
	}
	ShowPointGridRaw();
}

void PropertyAlignmentForm::on_tableWidgetArea_doubleClicked(QModelIndex Index)
{
	int	R=Index.row();
	AlignmentAreaList *a=AreaList.GetItem(R);
	if(a==NULL)
		return;
	GUICmdReqAlignmentAreaInfo	CmdReq(GetLayersBase(),sRoot,sName,a->GlobalPage);
	GUICmdSendAlignmentAreaInfo	CmdAck(GetLayersBase(),sRoot,sName,a->GlobalPage);
	CmdReq.Layer=a->Layer;
	CmdReq.AreaID=a->AreaID;
	if(CmdReq.Send(CmdReq.GetGlobalPage(),0,CmdAck)==true){
		InputAlignmentAreaForm	D(true,GetLayersBase(),/**/"",this);
		D.AreaName			=CmdAck.AreaName;
		D.SetSelectedList(CmdAck.LimitedLib);
		D.Priority			=CmdAck.Priority;
		D.Reflect();
		if(D.exec()==QDialog::Accepted){
			GUICmdReqModifyAlignmentAreaInfo	CmdMod(GetLayersBase(),sRoot,sName,a->GlobalPage);
			CmdMod.DeleteMode=D.DeleteMode;
			CmdMod.Layer		=a->Layer;
			CmdMod.AreaName		=D.AreaName;
			CmdMod.LimitedLib	=D.GetSelectedList();
			CmdMod.Area			=CmdAck.Area;
			CmdMod.AreaID		=CmdAck.AreaID;
			CmdMod.Priority		=D.Priority;
			CmdMod.Send(NULL,a->GlobalPage ,0);
			ShowAreaGrid();
		}
	}
}

void PropertyAlignmentForm::on_tableWidgetPoint_itemDoubleClicked(QTableWidgetItem* Index)
{
	int	R=Index->row();
	AlignmentPointList *a=PointList.GetItem(R);
	if(a==NULL)
		return;
	InputAlignmentPointForm	D(GetLayersBase(),NULL);
	D.MoveDot=a->SearchDot;
	D.Threshold=a->Threshold;
	D.AlignmentOnOutline=a->AlignmentOnOutline;
	D.UpdateData();
	if(D.exec()==QDialog::Accepted){
		QList<QTableWidgetItem *> Q=ui.tableWidgetPoint->selectedItems ();
		if(Q.count()==0)
			return;
		for(int i=0;i<Q.count();i++){
			QTableWidgetItem *qi=Q.value(i);
			if(qi->column()!=0)
				continue;
			AlignmentPointList *a=PointList.GetItem(qi->row());
			if(a==NULL)
				continue;
			int	globalPage	=a->Page;
			//int	LocalPage	=GetLayersBase()->GetLocalPageFromGlobal(globalPage);

			QString	EmitterRoot=sRoot;
			QString	EmitterName=sName;
			GUICmdReqAlignmentModifyPoint	DModMsg(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
			DModMsg.MoveDot				=D.MoveDot;		
			DModMsg.Threshold			=D.Threshold;
			DModMsg.AlignmentOnOutline	=D.AlignmentOnOutline;	//?O?s?A?E?u???i?1??E?e?A??atrue
			DModMsg.GlobalPage=globalPage;
			DModMsg.Layer	  =a->Layer;
			DModMsg.AreaID	  =a->AreaID;
			DModMsg.ItemID	  =a->ItemID;
			DModMsg.Send(NULL,globalPage ,0);					
		}
	CreateAndShowPointGrid();
	}
}


void PropertyAlignmentForm::on_toolButtonArea_clicked()
{
	GUICmdClickAreaButton	RCmd(GetLayersBase(),sRoot,sName,-1);
	RCmd.InstName=GetName();
	RCmd.SendAllPages(NULL,0);
}

void PropertyAlignmentForm::on_toolButtonPoint_clicked()
{
	GUICmdClickPointButton	RCmd(GetLayersBase(),sRoot,sName,-1);
	RCmd.InstName=GetName();
	RCmd.SendAllPages(NULL,0);
}

void PropertyAlignmentForm::on_toolButtonGroup_clicked()
{
	GUICmdClickGroupButton	RCmd(GetLayersBase(),sRoot,sName,-1);
	RCmd.InstName=GetName();
	RCmd.SendAllPages(NULL,0);
}