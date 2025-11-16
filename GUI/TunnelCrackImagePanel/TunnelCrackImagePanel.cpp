#include "TunnelCrackImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\TunnelCrackImagePanel\TunnelCrackImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "TunnelCrackImagePanel.h"
#include "TargetImageControlTools.h"
#include "XCrossObj.h"
//#include "XGUI.h"
#include "XTunnelCrack.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XDisplayImagePacket.h"

static	char	*sRoot=/**/"Customized";
static	char	*sName=/**/"TunnelCrackImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"TunnelCrackImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Target);

	(*Base)=new GUICmdReqItemIndependentPack		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendIndependentPack			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSelectCopied				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSyncDrawingMode				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqTunnelCrackImageItemsBmp	(Base, NULL,sRoot,sName);
	(*Base)=new GUICmdSendTunnelCrackImageItemsBmp(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	TunnelCrackImagePanel	*B=new TunnelCrackImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((TunnelCrackImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((TunnelCrackImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/TunnelCrackImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Customized",/**/"TunnelCrack"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

//==================================================================================================
TunnelCrackImagePanel::TunnelCrackImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Customized" ,/**/"TunnelCrack",QString(sRoot),QString(sName),__Target,parent)
{
	QString	emitterRoot=sRoot;
	QString	emitterName=sName;
	ItemsBmpCounts=GetPageNumb();
	ItemsBmpReceiver	=new GUICmdSendTunnelCrackImageItemsBmp*[ItemsBmpCounts];
	ItemsBmpRequester	=new GUICmdReqTunnelCrackImageItemsBmp*[ItemsBmpCounts];
	for(int page=0;page<ItemsBmpCounts;page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		ItemsBmpReceiver[page]=new GUICmdSendTunnelCrackImageItemsBmp(GetLayersBase(),emitterRoot,emitterName,globalPage);
		ItemsBmpRequester[page]=new GUICmdReqTunnelCrackImageItemsBmp(GetLayersBase(),this,emitterRoot,emitterName,globalPage);		
		ItemsBmpRequester[page]->AlgoRoot=AlgoRoot;
		ItemsBmpRequester[page]->AlgoName=AlgoName;
	}
}
TunnelCrackImagePanel::~TunnelCrackImagePanel(void)
{
	for(int i=0;i<ItemsBmpCounts;i++){
		delete	ItemsBmpRequester[i];
		delete	ItemsBmpReceiver[i];
	}
	delete	[]ItemsBmpRequester;
	delete	[]ItemsBmpReceiver;

	ItemsBmpRequester	=NULL;
	ItemsBmpReceiver	=NULL;
	#ifdef _MSC_VER
	_CrtCheckMemory();
	#endif
}

void	TunnelCrackImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	TunnelCrackImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

void	TunnelCrackImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Customized" ,/**/"PropertyTunnelCrack" ,/**/"");
	if(GProp!=NULL){
		CmdCreateTunnelCrackDrawEnd	Da;
		GetActiveLayerList(Da.LayerList);
		Da.Area			=area;
		GProp->TransmitDirectly(&Da);
	}
}

void	TunnelCrackImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

void	TunnelCrackImagePanel::GetActiveLayerList(IntList &LayerList)
{
	CmdReqTargetImageLayer	DrawMode(GetLayerNumb());
	GUIFormBase	*TProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"TargetImageControlTools" ,ImageControlToolsName);
	if(TProp!=NULL){
		TProp->TransmitDirectly(&DrawMode);
		LayerList=DrawMode.LayerList;
	}
	else{
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			LayerList.AppendList(new IntClass(Layer));
		}
	}
}

void	TunnelCrackImagePanel::CanvasSlotOnPaint(QPainter &pnt)
{
	CmdReqTargetImageLayer	DrawMode(GetLayerNumb());
	GUIFormBase	*TProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"TargetImageControlTools" ,ImageControlToolsName);
	if(TProp!=NULL){
		TProp->TransmitDirectly(&DrawMode);
		RedCircleMode=DrawMode.RedCircleMode;
	}
	DisplayImage::CanvasSlotOnPaint(pnt);
}

void	TunnelCrackImagePanel::DrawAfterImage(QPainter &pnt ,QImage &PntImage)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	IntList	LayerList;
	CmdReqTargetImageLayer	DrawMode(GetLayerNumb());
	GUIFormBase	*TProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"TargetImageControlTools" ,ImageControlToolsName);
	if(TProp!=NULL){
		TProp->TransmitDirectly(&DrawMode);
		LayerList=DrawMode.LayerList;
	}
	//if(DrawMode.ShowNGItemButton==true || DrawMode.ShowAllItemsButton==true){
		int	globalX1;
		int	globalY1;
		int	globalX2;
		int	globalY2;
		GetLayersBase()->GetArea(globalX1,globalY1 ,globalX2,globalY2);
		int	N=0;
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

			ItemsBmpRequester[N]->LayerList	=LayerList;
			DataInPage *P=GetLayersBase()->GetPageData(page);
			int	Dx1	=P->GetOutlineOffset()->x;
			int	Dy1	=P->GetOutlineOffset()->y;
			int	Dx2	=P->GetOutlineOffset()->x+GetDotPerLine();
			int	Dy2	=P->GetOutlineOffset()->x+GetMaxLines();
			int	Gx1,Gy1,Gx2,Gy2;
			ChangeDxy2Gxy(Dx1,Dy1 ,Gx1 ,Gy1);
			ChangeDxy2Gxy(Dx2,Dy2 ,Gx2 ,Gy2);
			if(CheckOverlapRectRectFast(0, 0, GetCanvasWidth(), GetCanvasHeight()
										,Gx1, Gy1, Gx2, Gy2)==false)
				continue;
			ItemsBmpRequester[N]->Data.ZoomRate	=GetZoomRate();
			ItemsBmpRequester[N]->Data.MovX			=GetMovx()+P->GetOutlineOffset()->x;
			ItemsBmpRequester[N]->Data.MovY			=GetMovy()+P->GetOutlineOffset()->y;
			//if(ItemsBmpRequester[N]->Data.MovX>0)
			//	ItemsBmpRequester[N]->Data.MovX=0;
			//if(ItemsBmpRequester[N]->Data.MovY>0)
			//	ItemsBmpRequester[N]->Data.MovY=0;

			ItemsBmpRequester[N]->Data.GlobalPage	=globalPage;
			if(Gx1<0)
				Gx1=0;
			if(Gy1<0)
				Gy1=0;
			if(Gx2>GetCanvasWidth())
				Gx2=GetCanvasWidth();
			if(Gy2>GetCanvasHeight())
				Gy2=GetCanvasHeight();
			ItemsBmpRequester[N]->Data.Gx1		=Gx1;
			ItemsBmpRequester[N]->Data.Gy1		=Gy1;
			ItemsBmpRequester[N]->Data.Gx2		=Gx2;
			ItemsBmpRequester[N]->Data.Gy2		=Gy2;
			ChangeGxy2Dxy(Gx1,Gy1 ,Dx1 ,Dy1);
			ChangeGxy2Dxy(Gx2,Gy2 ,Dx2 ,Dy2);
			ItemsBmpRequester[N]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
			ItemsBmpRequester[N]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
			ItemsBmpRequester[N]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
			ItemsBmpRequester[N]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
			ItemsBmpRequester[N]->Data.MoveGlobalDx	=MoveCurrentGlobalX - MoveStartGlobalX;
			ItemsBmpRequester[N]->Data.MoveGlobalDy	=MoveCurrentGlobalY - MoveStartGlobalY;
			ItemsBmpRequester[N]->InstName	=GetName();
			ItemsBmpRequester[N]->ShowNGItemButton	=DrawMode.ShowNGItemButton;
			ItemsBmpRequester[N]->ShowAllItemsButton=DrawMode.ShowAllItemsButton;
			ItemsBmpRequester[N]->SelectedAlgorithm	=GetAlgorithmBase();
			ItemsBmpRequester[N]->ResultMode=true;

			N++;
		}
		for(int n=0;n<N;n++){
			ItemsBmpRequester[n]->Send(ItemsBmpRequester[n]->Data.GlobalPage,0,*ItemsBmpReceiver[n]);
		}
		for(int n=0;n<N;n++){
			if(ItemsBmpReceiver[n]->IsReceived()==true && ItemsBmpReceiver[n]->IData!=NULL){
				pnt.drawImage(ItemsBmpRequester[n]->Data.Gx1 ,ItemsBmpRequester[n]->Data.Gy1
					 ,*(const QImage *)ItemsBmpReceiver[n]->IData);
			}
		}
	//}
	ReEntrant=false;
}

//=======================================================================


GUICmdReqTunnelCrackImageItemsBmp::GUICmdReqTunnelCrackImageItemsBmp(LayersBase *Base ,TunnelCrackImagePanel *form  
									,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Form=form;
}
GUICmdReqTunnelCrackImageItemsBmp::~GUICmdReqTunnelCrackImageItemsBmp(void)
{
}

bool	GUICmdReqTunnelCrackImageItemsBmp::Load(QIODevice *f)
{
	if(::Load(f,InstName)==false)
		return false;
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;

	if(LayerList.Load(f)==false)
		return false;
	if(::Load(f,ShowNGItemButton)==false)
		return false;
	if(::Load(f,ShowAllItemsButton)==false)
		return false;
	QString	DLLRoot;
	QString	DLLName;

	if(::Load(f,DLLRoot)==false)
		return false;
	if(::Load(f,DLLName)==false)
		return false;
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(::Load(f,ResultMode)==false)
		return false;
	SelectedAlgorithm=GetLayersBase()->GetAlgorithmBase(DLLRoot,DLLName);

	return(true);
}
bool	GUICmdReqTunnelCrackImageItemsBmp::Save(QIODevice *f)
{
	if(::Save(f,InstName)==false)
		return false;
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	if(LayerList.Save(f)==false)
		return false;

	if(::Save(f,ShowNGItemButton)==false)
		return false;
	if(::Save(f,ShowAllItemsButton)==false)
		return false;
	QString	DLLRoot;
	QString	DLLName;
	if(SelectedAlgorithm!=NULL){
		SelectedAlgorithm->GetDLLName(DLLRoot,DLLName);
	}
	if(::Save(f,DLLRoot)==false)
		return false;
	if(::Save(f,DLLName)==false)
		return false;
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(::Save(f,ResultMode)==false)
		return false;
	return(true);
}

void	GUICmdReqTunnelCrackImageItemsBmp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*q=GetLayersBase()->FindByName(EmitterRoot ,EmitterName ,InstName);
	if(q==NULL)
		return;
	TunnelCrackImagePanel	*A=dynamic_cast<TunnelCrackImagePanel *>(q);
	if(A==NULL)
		return;
	GUICmdSendTunnelCrackImageItemsBmp	*SendBack=(GUICmdSendTunnelCrackImageItemsBmp *)((GetSendBackPacket()==NULL)?new GUICmdSendTunnelCrackImageItemsBmp(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);
	if(ShowNGItemButton==true){
		SendBack->MakeImage(LayerList
							,Data.Gx1,Data.Gy1 ,Data.Gx2,Data.Gy2
							,Data.Dx1,Data.Dy1 ,Data.Dx2,Data.Dy2
							,Data.MovX,Data.MovY,Data.ZoomRate
							,localPage
							,Data.MoveGlobalDx ,Data.MoveGlobalDy
							,A ,SelectedAlgorithm
							,*GetLayersBase()
							,ResultMode);
	}
	else if(ShowAllItemsButton==true){
		SendBack->MakeImageAll(LayerList
							,Data.Gx1,Data.Gy1 ,Data.Gx2,Data.Gy2
							,Data.Dx1,Data.Dy1 ,Data.Dx2,Data.Dy2
							,Data.MovX,Data.MovY,Data.ZoomRate
							,localPage
							,Data.MoveGlobalDx ,Data.MoveGlobalDy
							,A ,SelectedAlgorithm
							,*GetLayersBase()
							,ResultMode);
	}
	else{
		SendBack->MakeImage(LayerList
							,Data.Gx1,Data.Gy1 ,Data.Gx2,Data.Gy2
							,Data.Dx1,Data.Dy1 ,Data.Dx2,Data.Dy2
							,Data.MovX,Data.MovY,Data.ZoomRate
							,localPage
							,Data.MoveGlobalDx ,Data.MoveGlobalDy
							,A ,SelectedAlgorithm
							,*GetLayersBase()
							,false);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendTunnelCrackImageItemsBmp::GUICmdSendTunnelCrackImageItemsBmp(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	IData=NULL;
	PntFromIData=NULL;
}

GUICmdSendTunnelCrackImageItemsBmp::~GUICmdSendTunnelCrackImageItemsBmp(void)
{
	if(PntFromIData!=NULL)
		delete	PntFromIData;
	PntFromIData=NULL;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

bool	GUICmdSendTunnelCrackImageItemsBmp::Load(QIODevice *f)
{
	if(IData==NULL)
		IData=new QImage();
	IData->load(f,/**/"PNG");
	return(true);
}
bool	GUICmdSendTunnelCrackImageItemsBmp::Save(QIODevice *f)
{
	IData->save(f,/**/"PNG");
	return(true);
}

void	GUICmdSendTunnelCrackImageItemsBmp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendTunnelCrackImageItemsBmp::MakeImage(
								  IntList &LayerList
								 ,int Gx1,int Gy1 ,int Gx2,int Gy2
								 ,int Dx1,int Dy1 ,int Dx2,int Dy2
								 ,int MovX,int MovY, double ZoomRate
								 ,int localPage
								 ,int MoveGlobalDx ,int MoveGlobalDy
								 ,TunnelCrackImagePanel	*A
								 ,AlgorithmBase	*L
								 ,LayersBase &LocalLBase
								 ,bool ResultMode)
{
	DataInPage *P=LocalLBase.GetPageData(localPage);
	int	LGx=Gx2-Gx1;
	int	LGy=Gy2-Gy1;

	if(L==NULL)
		return;
	if(IData!=NULL && (IData->width()!=LGx || IData->height()!=LGy)){
		if(PntFromIData!=NULL)
			delete	PntFromIData;
		delete	IData;
		IData=NULL;
		PntFromIData=NULL;
	}
	if(IData==NULL){
		IData=new QImage(LGx,LGy,QImage::Format_ARGB32);
		if(PntFromIData!=NULL)
			delete	PntFromIData;
		PntFromIData=NULL;
	}
	if(PntFromIData==NULL)
		PntFromIData=new QPainter(IData);
	IData->fill(0);
	ResultInspection	*DRes=LocalLBase.GetCurrentResultForDraw();
	if(DRes!=NULL){
		ResultBaseForAlgorithmRoot *Res=DRes->GetResultBaseForAlgorithm(L);
		if(Res!=NULL && ResultMode==true){
			L->GetPageData(localPage)->DrawResultItem(Res->GetPageData(localPage),LayerList,*IData ,*PntFromIData,MovX-Gx1/ZoomRate ,MovY-Gy1/ZoomRate ,ZoomRate,true);
		}
		else{
			TunnelCrackDrawAttr	Attr;
			L->GetPageData(localPage)->Draw(*IData, LayerList,MovX-Gx1/ZoomRate ,MovY-Gy1/ZoomRate ,ZoomRate ,&Attr);
		}
	}
}
void	GUICmdSendTunnelCrackImageItemsBmp::MakeImageAll(
								  IntList &LayerList
								 ,int Gx1,int Gy1 ,int Gx2,int Gy2
								 ,int Dx1,int Dy1 ,int Dx2,int Dy2
								 ,int MovX,int MovY, double ZoomRate
								 ,int localPage
								 ,int MoveGlobalDx ,int MoveGlobalDy
								 ,TunnelCrackImagePanel	*A
								 ,AlgorithmBase	*L
								 ,LayersBase &LocalLBase
								 ,bool ResultMode)
{
	DataInPage *P=LocalLBase.GetPageData(localPage);
	int	LGx=Gx2-Gx1;
	int	LGy=Gy2-Gy1;

	if(L==NULL)
		return;
	if(IData!=NULL && (IData->width()!=LGx || IData->height()!=LGy)){
		if(PntFromIData!=NULL)
			delete	PntFromIData;
		delete	IData;
		IData=NULL;
		PntFromIData=NULL;
	}
	if(IData==NULL){
		IData=new QImage(LGx,LGy,QImage::Format_ARGB32);
		if(PntFromIData!=NULL)
			delete	PntFromIData;
		PntFromIData=NULL;
	}
	if(PntFromIData==NULL)
		PntFromIData=new QPainter(IData);
	IData->fill(0);
	ResultInspection	*DRes=LocalLBase.GetCurrentResultForDraw();
	if(DRes!=NULL){
		ResultBaseForAlgorithmRoot *Res=DRes->GetResultBaseForAlgorithm(L);
		if(Res!=NULL && ResultMode==true){
			L->GetPageData(localPage)->DrawResultItem(Res->GetPageData(localPage),LayerList,*IData ,*PntFromIData,MovX-Gx1/ZoomRate ,MovY-Gy1/ZoomRate ,ZoomRate,false);
		}
		else{
			TunnelCrackDrawAttr	Attr;
			L->GetPageData(localPage)->Draw(*IData, LayerList,MovX-Gx1/ZoomRate ,MovY-Gy1/ZoomRate ,ZoomRate ,&Attr);
		}
	}
}
//=======================================================================

