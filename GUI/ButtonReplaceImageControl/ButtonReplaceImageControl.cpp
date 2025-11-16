/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonReplaceImageControl\ButtonReplaceImageControl.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonReplaceImageControl.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XStatusController.h"
#include "ReplaceImageControlForm.h"
#include "XPropertyReplaceImagePacket.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ReplaceImageControl";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to replace image");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReplaceImageAddMaskArea		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReplaceImageAckMaskArea		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReplaceImageAddMaskImage		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReplaceImageCalcMask			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReplaceImageMouseLDown		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReplaceImageSetCompositeColor	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReplaceImageSetCompositeImage	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReplaceImageSetCompositePage	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReplaceImageReqDraw			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReplaceImageAckDraw			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReplaceImageProcessMode		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReplaceImageMaskMode			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReplaceImageMakeAreaMask		(Base, QString(sRoot), QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonReplaceImageControl(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonReplaceImageControl *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonReplaceImageControl *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonReplaceImageControl *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonReplaceImageControl *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"CurrentPage";
	Data[4].Pointer				 =&((ButtonReplaceImageControl *)Instance)->CurrentPage;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"HookPanelInst";
	Data[5].Pointer				 =&((ButtonReplaceImageControl *)Instance)->HookPanelInst;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonReplaceImageControl.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ReplaceImage"));
}


//==================================================================================================
ButtonReplaceImageControl::ButtonReplaceImageControl(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	//setObjectName(QString::fromUtf8(/**/"ButtonReplaceImageControlObj"));
	Msg=/**/"Replace Image";
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonReplaceImage");
	Button.setCheckable(false);
	Form		=NULL;
	HookPanel	=NULL;
	CurrentPage	=0;

	resize(100,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonReplaceImageControl::~ButtonReplaceImageControl(void)
{
	if(Form!=NULL){
		Form->close();
		Form->deleteLater();
		Form=NULL;
	}
}
void	ButtonReplaceImageControl::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}
static	bool PanelPaintFunction(FunctionServerClass *Obj,GUIFormBase *TartgetForm,QPainter &pnt ,QImage &PntImage);
static	bool PanelDrawEndFunction(FunctionServerClass *Obj,GUIFormBase *TartgetForm);
static	bool PanelMouseLDouble(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY);
static	bool PanelMouseFunction(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY);
	
void	ButtonReplaceImageControl::SetHook(void)
{
	HookPanel	=dynamic_cast<DisplayImage *>(GetLayersBase()->FindByName(HookPanelInst));
	if(HookPanel!=NULL){
		HookPanel->SetHookInPaintLast			(this,PanelPaintFunction	,true);
		HookPanel->SetHookInDrawEnd				(this,PanelDrawEndFunction	,true);
		HookPanel->SetHookInMouseLDoubleClick	(this,PanelMouseLDouble		,true);
		HookPanel->SetHookInMouseMove			(this,PanelMouseFunction	,true);
		HookPanel->SetHookInMouseLClick			(this,PanelMouseFunction	,true);
		HookPanel->SetHookInMouseLClickOnFree	(this,PanelMouseFunction	,true);
		HookPanel->SetHookInMouseRClick			(this,PanelMouseFunction	,true);
		HookPanel->SetHookInMouseRClickOnFree	(this,PanelMouseFunction	,true);
	}
}

void	ButtonReplaceImageControl::DeleteHook(void)
{
	HookPanel	=dynamic_cast<DisplayImage *>(GetLayersBase()->FindByName(HookPanelInst));
	if(HookPanel!=NULL){
		HookPanel->ReleaseHook(this);
	}
}


static	bool PanelPaintFunction(FunctionServerClass *Obj,GUIFormBase *TartgetForm,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TartgetForm);
	if(DImage!=NULL){
		ButtonReplaceImageControl	*Form=dynamic_cast<ButtonReplaceImageControl *>(Obj);
		if(Form!=NULL && Form->IsAvailableShowMask()==true){
			Form->DrawPanel(pnt,DImage->GetMovx(),DImage->GetMovy(),DImage->GetZoomRate()
							,DImage->GetCanvasWidth(),DImage->GetCanvasHeight());
			return false;
		}
	}
	return true;
}
static	bool PanelDrawEndFunction(FunctionServerClass *Obj,GUIFormBase *TartgetForm)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TartgetForm);
	if(DImage!=NULL){
		ButtonReplaceImageControl	*Form=dynamic_cast<ButtonReplaceImageControl *>(Obj);
		if(Form!=NULL && Form->IsAvailableDrawAreaForMask()==true){
            FlexArea    Area;
            DisplayImage::ToFlexArea(*DImage->GetRawSDataPoint(),Area);
			Form->PanelDrawEnd(Area);
			return false;
		}
	}
	return true;
}
static	bool PanelMouseLDouble(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TartgetForm);
	if(DImage!=NULL){
		ButtonReplaceImageControl	*Form=dynamic_cast<ButtonReplaceImageControl *>(Obj);
		if(Form!=NULL && Form->IsAvailableMouseLDouble()==true){
			Form->ExeMouseLDown(GlobalPosX,GlobalPosY);
			return false;
		}
	}
	return true;
}

static	bool PanelMouseFunction(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TartgetForm);
	if(DImage!=NULL){
		ButtonReplaceImageControl	*Form=dynamic_cast<ButtonReplaceImageControl *>(Obj);
		if(Form!=NULL && Form->IsAvailableDrawAreaForMask()==true){
			return false;
		}
	}
	return true;
}

void	ButtonReplaceImageControl::closeEvent(QCloseEvent *event)
{
	if(Form!=NULL){
		Form->close();
		Form->deleteLater();
		Form=NULL;
	}
}

void	ButtonReplaceImageControl::TransmitDirectly(GUIDirectMessage *packet)
{
	//CmdReplaceImageControl	*CmdReplaceImageControlVar=dynamic_cast<CmdReplaceImageControl *>(packet);
	//if(CmdReplaceImageControlVar!=NULL){
	//	Label.setText(CmdReplaceImageControlVar->FileName);
	//	return;
	//}
	GUICmdReplaceImageDrawEnd	*GUICmdReplaceImageDrawEndVar=dynamic_cast<GUICmdReplaceImageDrawEnd *>(packet);
	if(GUICmdReplaceImageDrawEndVar!=NULL){
		if(Form!=NULL){
			Form->SetDrawEnd(GUICmdReplaceImageDrawEndVar->Area);
		}
		return;
	}
    CmdReplaceImageMouseLDown   *CmdReplaceImageMouseLDownVar=dynamic_cast<CmdReplaceImageMouseLDown *>(packet);
    if(CmdReplaceImageMouseLDownVar!=NULL){
		if(Form!=NULL){
			Form->ExeMouseLDown(CmdReplaceImageMouseLDownVar->X,CmdReplaceImageMouseLDownVar->Y);
		}
        return;
    }
	CmdReplaceImagePopupWindow	*CmdReplaceImagePopupWindowVar=dynamic_cast<CmdReplaceImagePopupWindow *>(packet);
	if(CmdReplaceImagePopupWindowVar!=NULL){
		SlotClicked(true);
		return;
	}
}

void    ButtonReplaceImageControl::CloseForm(void)
{
	if(Form!=NULL){
		Form->close();
		Form->deleteLater();
		Form=NULL;
	}
}

void	ButtonReplaceImageControl::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonReplaceImageControl::SlotClicked (bool checked)
{
	if(Form==NULL){
		Form=new ReplaceImageControlForm(GetLayersBase(),this);
	}
	Form->show();
}

void	ButtonReplaceImageControl::DrawPanel(QPainter &pnt,int movx ,int movy,double ZoomRate,int CanvasWidth ,int CanvasHeight)
{
	if(Form!=NULL){
		Form->DrawPanel(pnt,movx ,movy,ZoomRate,CanvasWidth ,CanvasHeight);
	}
}
void	ButtonReplaceImageControl::PanelDrawEnd(FlexArea &Area)
{
	if(Form!=NULL){
		Form->SetDrawEnd(Area);
	}
}

bool	ButtonReplaceImageControl::IsAvailableShowMask(void)
{
	if(Form!=NULL){
		return Form->IsAvailableShowMask();
	}
	return false;
}
bool	ButtonReplaceImageControl::IsAvailableDrawAreaForMask(void)
{
	if(Form!=NULL){
		return Form->IsAvailableDrawAreaForMask();
	}
	return false;
}
bool    ButtonReplaceImageControl::IsAvailableMouseLDouble(void)
{
	if(Form!=NULL){
		return Form->IsAvailableMouseLDouble();
	}
	return false;
}
void    ButtonReplaceImageControl::ExeMouseLDown(int X, int Y)
{
	if(Form!=NULL){
		Form->ExeMouseLDown(X,Y);
	}
}