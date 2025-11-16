#include "HookAlgorithmImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\HookAlgorithmImagePanel\HookAlgorithmImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "HookAlgorithmImagePanel.h"
#include "XDLLOnly.h"
#include "XForWindows.h"
#include <QMessageBox>
#include "XGeneralFunc.h"

static	const	char	*sRoot=/**/"Other";
static	const	char	*sName=/**/"HookAlgorithmImagePanel";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Hook another AlgorithmImagePanel");
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

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new HookAlgorithmImagePanel(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"SrcAlgoImagePanelRoot";
	Data[0].Pointer				 =&((HookAlgorithmImagePanel *)Instance)->SrcAlgoImagePanelRoot;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"SrcAlgoImagePanelName";
	Data[1].Pointer				 =&((HookAlgorithmImagePanel *)Instance)->SrcAlgoImagePanelName;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"SrcAlgoImagePanelInst";
	Data[2].Pointer				 =&((HookAlgorithmImagePanel *)Instance)->SrcAlgoImagePanelInst;

	Data[3].Type				 =/**/"QString";
	Data[3].VariableNameWithRoute=/**/"TargetImagePanelRoot";
	Data[3].Pointer				 =&((HookAlgorithmImagePanel *)Instance)->TargetImagePanelRoot;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"TargetImagePanelName";
	Data[4].Pointer				 =&((HookAlgorithmImagePanel *)Instance)->TargetImagePanelName;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"TargetImagePanelInst";
	Data[5].Pointer				 =&((HookAlgorithmImagePanel *)Instance)->TargetImagePanelInst;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/HookAlgorithmImagePanel.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
HookAlgorithmImagePanel::HookAlgorithmImagePanel(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SrcImg=NULL;
	TargetImg=NULL;
	IData	=NULL;
	LastZoomRate	=1.0;
	LastMovX		=0;
	LastMovY		=0;
	LastWidth		=0;
	LastHeight		=0;
}

HookAlgorithmImagePanel::~HookAlgorithmImagePanel(void)
{
	SrcImg=NULL;
	TargetImg=NULL;
	if(IData!=NULL){
		delete	IData;
		IData=NULL;
	}
}


static	bool TargetFunctionLater(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		HookAlgorithmImagePanel	*Form=dynamic_cast<HookAlgorithmImagePanel *>(Obj);
		if(Form!=NULL){
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->Draw(pnt,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				Form->GetLayersBase()->UnlockWeakDraw();
			}
		}
	}
	return true;
}


void	HookAlgorithmImagePanel::ReadyParam(void)
{
	GUIFormBase	*SrcPanel=GetLayersBase()->FindByName(SrcAlgoImagePanelRoot,SrcAlgoImagePanelName,SrcAlgoImagePanelInst);
	GUIFormBase	*TargetPanel=GetLayersBase()->FindByName(TargetImagePanelRoot,TargetImagePanelName,TargetImagePanelInst);

	if(SrcPanel==NULL || TargetPanel==NULL)
		return;

	SrcImg		=dynamic_cast<DisplayImage *>(SrcPanel);
	TargetImg	=dynamic_cast<DisplayImage *>(TargetPanel);
	if(SrcImg!=NULL && TargetPanel!=NULL){
		TargetImg->SetHookInPaintLast(this,TargetFunctionLater);
		bool ret=(connect(this,SIGNAL(SignalOnPaint(QPainter &)),SrcImg,SLOT(CanvasSlotOnPaint(QPainter &))))?true:false;
	}
}

void	HookAlgorithmImagePanel::Draw(QPainter &pnt ,double ZoomRate ,int movx ,int movy)
{
	if(SrcImg!=NULL){
		if(IData==NULL || ZoomRate!=LastZoomRate || movx!=LastMovX || movy!=LastMovY 
		|| LastWidth!=TargetImg->GetCanvasWidth() || LastHeight!=TargetImg->GetCanvasHeight()){
			double	Z=SrcImg->GetZoomRate();
			int		Mx=SrcImg->GetMovx();
			int		My=SrcImg->GetMovy();
			LastZoomRate=ZoomRate;
			LastMovX	=movx;
			LastMovY	=movy;
			SrcImg->SetMovXY(movx,movy);
			SrcImg->SetZoomRate(ZoomRate);
			if(IData!=NULL && (LastWidth!=TargetImg->GetCanvasWidth() || LastHeight!=TargetImg->GetCanvasHeight())){
				delete	IData;
				IData=NULL;
			}
			if(IData==NULL){
				IData=new QImage(TargetImg->GetCanvasWidth(),TargetImg->GetCanvasHeight(),QImage::Format_ARGB32);
			}
			LastWidth	=TargetImg->GetCanvasWidth();
			LastHeight	=TargetImg->GetCanvasHeight();

			IData->fill(0);
			QPainter	XPnt(IData);
			emit	SignalOnPaint(XPnt);

			AddAlphaChannel(*IData,70);

			SrcImg->SetMovXY(Mx,My);
			SrcImg->SetZoomRate(Z);
		}
		pnt.drawImage(0,0,*IData);

	}
}

//=================================================================
