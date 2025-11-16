#include "HalconNGListResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\HalconNGList\HalconNGList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "HalconNGList.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDisplayImage.h"
#include "XGeneralFunc.h"

static	char	*sRoot=/**/"Inspection";
static	char	*sName=/**/"HalconInsNGList";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"NG List for Halcon Inspection");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new HalconNGList(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqNGList	(Base,sRoot,sName);
	(*Base)=new GUICmdSendNGList(Base,sRoot,sName);
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
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"WidthLineNumber";
	Data[0].Pointer				 =&((HalconNGList *)Instance)->WidthLineNumber;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"WidthPageNumber";
	Data[1].Pointer				 =&((HalconNGList *)Instance)->WidthPageNumber;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"WidthPosition";
	Data[2].Pointer				 =&((HalconNGList *)Instance)->WidthPosition;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"Attribute";
	Data[3].Pointer				 =&((HalconNGList *)Instance)->WidthAttribute;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"TargetImagePanelName";
	Data[4].Pointer				 =&((HalconNGList *)Instance)->TargetImagePanelName;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/HalconNGList.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"HalconInspection"));
}


//==================================================================================================
HalconNGList::HalconNGList(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	WidthLineNumber		=24;
	WidthPageNumber		=24;
	WidthPosition		=64;
	WidthAttribute		=0;
	NGList.move(0,0);
	resize(250,250);
	NGList.setParent(this);
	//connect(&NGList,SIGNAL(itemEntered (QTableWidgetItem *)),this,SLOT(ListItemClicked (QTableWidgetItem *)));
	connect(&NGList,SIGNAL(itemSelectionChanged ()),this,SLOT(ListItemSelectionChanged()),Qt::QueuedConnection);
	NGList.setSelectionMode(QAbstractItemView::SingleSelection);
	NGList.setSelectionBehavior(QAbstractItemView::SelectRows);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	HalconNGList::Prepare(void)
{
	int	ColCount=((WidthPageNumber>0)?1:0)
				+((WidthPosition>0)?1:0)
				+((WidthAttribute>0)?1:0);
	NGList.setColumnCount(ColCount);
	NGList.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	NGList.setHorizontalHeaderItem ( 0, new QTableWidgetItem(LangSolver.GetString(HalconNGList_LS,LID_0)/*"Pg"*/));
	NGList.setHorizontalHeaderItem ( 1, new QTableWidgetItem(LangSolver.GetString(HalconNGList_LS,LID_1)/*"Position"*/));
	ShowInPlayer(GetLayersBase()->GetCurrentInspectIDForDisplay());
}
void	HalconNGList::ResizeAction()
{
	NGList.resize(width(),height());
}
void	HalconNGList::ShowInPlayer(int64 shownInspectionID)
{
	NGData.RemoveAll();
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HalconInspection");
	if(ABase!=NULL){
		AlgorithmLibraryContainer	*LContainer=ABase->GetLibraryContainer();
		if(LContainer!=NULL){
			LContainer->EnumLibrary(HalconInspectionLibType,LibList);
		}
	}

	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqNGList		CmdReq(GetLayersBase(),sRoot,sName,page);
		CmdReq.ShownInspectionID=shownInspectionID;
		GUICmdSendNGList	CmdAck(GetLayersBase(),sRoot,sName,page);
		if(CmdReq.Send(page ,0,CmdAck)==true){
			for(HalconNGDataList *e=CmdAck.NGData.GetFirst();e!=NULL;e=e->GetNext()){
				e->Page=page;
			}
			NGData+=CmdAck.NGData;
		}
	}
	int	LNumb=NGData.GetNumber();
	NGList.setRowCount(LNumb);
	//NGList.setCurrentCell(0,0);
	NGList.clearSelection();
	//WidthLineNumber;
	int	N=0;
	if(WidthPageNumber>0){
		NGList.setColumnWidth (N, WidthPageNumber);
		N++;
	}
	if(WidthPosition>0){
		NGList.setColumnWidth (N, WidthPosition);
		N++;
	}
	if(WidthAttribute>0){
		NGList.setColumnWidth (N, WidthAttribute);
		N++;
	}

	int	row=0;
	for(HalconNGDataList *e=NGData.GetFirst();e!=NULL;e=e->GetNext(),row++){
		QTableWidgetItem *W;
		int	N=0;
		if(WidthPageNumber>0){
			W=NGList.item ( row, N);
			if(W==NULL){
				W=new QTableWidgetItem();
				NGList.setItem ( row, N,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(QString::number(e->Page));
			N++;
		}
		if(WidthPosition>0){
			W=NGList.item ( row, N);
			if(W==NULL){
				W=new QTableWidgetItem();
				NGList.setItem ( row, N,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(QString::number(e->CenterX) + QString(/**/",") +QString::number(e->CenterY));
			N++;
		}
		if(WidthAttribute>0){
			W=NGList.item ( row, N);
			if(W==NULL){
				W=new QTableWidgetItem();
				NGList.setItem ( row, N,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			AlgorithmLibraryList	*L=LibList.SearchLibrary(HalconInspectionLibType, e->LibID);
			if(L!=NULL)
				W->setText(L->GetLibName());
			else
				W->setText(/**/"");
			N++;
		}
	}
	
	//ListItemSelectionChanged();
}

void	HalconNGList::ListItemSelectionChanged ()
{
	int row	=NGList.currentRow();
	HalconNGDataList *e=NGData.GetItem(row);
	if(e!=NULL){
		GUIFormBase	*F=GetLayersBase()->FindByName(TargetImagePanelName);
		if(F!=NULL){
			DisplayImage	*d=dynamic_cast<DisplayImage *>(F);
			if(d!=NULL){
				DataInPage *pdata=GetLayersBase()->GetPageData(e->Page);
				if(pdata!=NULL){
					d->ShowCenter(e->CenterX +pdata->GetOutlineOffset()->x
								, e->CenterY +pdata->GetOutlineOffset()->y);
				}
			}
		}
	}
}

void	HalconNGList::ListItemClicked ( QTableWidgetItem *)
{
	int row	=NGList.currentRow();
	HalconNGDataList *e=NGData.GetItem(row);
	if(e!=NULL){
		GUIFormBase	*F=GetLayersBase()->FindByName(TargetImagePanelName);
		if(F!=NULL){
			DisplayImage	*d=dynamic_cast<DisplayImage *>(F);
			if(d!=NULL){
				DataInPage *pdata=GetLayersBase()->GetPageData(e->Page);
				if(pdata!=NULL){
					d->ShowCenter(e->CenterX +pdata->GetOutlineOffset()->x
								, e->CenterY +pdata->GetOutlineOffset()->y);
				}
			}
		}
	}
}


//=======================================================================
bool	HalconNGDataList::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,Area)==false)
		return false;
	return true;
}
bool	HalconNGDataList::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,Area)==false)
		return false;
	return true;
}

bool	HalconNGDataListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(HalconNGDataList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	HalconNGDataListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		HalconNGDataList *a=new HalconNGDataList();
		if(a->Load(f)==false)
			return false;
	}
	return true;
}


GUICmdReqNGList::GUICmdReqNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqNGList::Save(QIODevice *f)
{
	::Save(f,ShownInspectionID);
	return(true);
}
bool	GUICmdReqNGList::Load(QIODevice *f)
{
	::Load(f,ShownInspectionID);
	return(true);
}

void	GUICmdReqNGList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNGList	*SendBack=GetSendBack(GUICmdSendNGList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HalconInspection");
	if(ABase!=NULL){
		CmdCreateNGListPacket	Cmd;
		Cmd.Point=&SendBack->NGData;
		Cmd.Res	 =GetLayersBase()->GetBufferedResult(ShownInspectionID);
		if(Cmd.Res==NULL)
			Cmd.Res=GetLayersBase()->GetCurrentResultForCalc();
		ABase->TransmitDirectly(&Cmd);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendNGList::GUICmdSendNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendNGList::Load(QIODevice *f)
{
	if(NGData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendNGList::Save(QIODevice *f)
{
	if(NGData.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendNGList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
