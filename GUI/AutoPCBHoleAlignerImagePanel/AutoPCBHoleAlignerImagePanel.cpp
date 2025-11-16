/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AutoPCBHoleAlignerImagePanel\AutoPCBHoleAlignerImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "AutoPCBHoleAlignerImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "XAutoPCBHoleAlignerPacket.h"

static	const	char	*sRoot="Inspection";
static	const	char	*sName="AutoPCBHoleAlignerImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("AutoPCBHoleAligner ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Target);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AutoPCBHoleAlignerImagePanel	*B=new AutoPCBHoleAlignerImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((AutoPCBHoleAlignerImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 	=/**/"QString";
	Data[N].VariableNameWithRoute	=/**/"ImageControlToolsName";
	Data[N].Pointer				 	=&((AutoPCBHoleAlignerImagePanel *)Instance)->ImageControlToolsName;
	Data[N+1].Type					=/**/"int32";
	Data[N+1].VariableNameWithRoute	=/**/"ShowFixedPhase";
	Data[N+1].Pointer				= &((AutoPCBHoleAlignerImagePanel *)Instance)->ShowFixedPhase;
	N+=2;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	char	*s;
	QList<QByteArray> DList=QImageReader::supportedImageFormats ();
	for(int i=0;i<DList.count();i++){
		QByteArray	M=DList.value(i);
		s=M.data();
		if(strcmp(s,"png")==0)
			break;
	}

	QPixmap	D(":Resources/AutoPCBHoleAlignerImagePanel.png");
	return(new QIcon(D));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList("Basic","AutoPCBHoleAligner"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

//==================================================================================================
AutoPCBHoleAlignerImagePanel::AutoPCBHoleAlignerImagePanel(LayersBase *Base,QWidget *parent)
:DisplayImageWithAlgorithm(Base,"Basic" ,"AutoPCBHoleAligner",QString(sRoot),QString(sName),__Master,parent)
{
	ClickAreaSize=5;
}

void	AutoPCBHoleAlignerImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

AlgorithmDrawAttr	*AutoPCBHoleAlignerImagePanel::CreateDrawAttrPointer(void)
{
	if(ShowFixedPhase!=-1)
		GetLayersBase()->TF_SetCurrentScanPhaseNumber(ShowFixedPhase); // phase function
	GUICmdReqAutoPCBHoleAlignerDrawMode	DrawMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAutoPCBHoleAligner" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	AutoPCBHoleAlignerDrawAttr	*A=new AutoPCBHoleAlignerDrawAttr();
	A->DrawHole			=DrawMode.DrawHole;
	A->DrawFringe		=DrawMode.DrawFringe;
	A->SelectedLDList	=DrawMode.SelectedLDList;
	return A;
}
void	AutoPCBHoleAlignerImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}


static	bool AutoPCBHoleAlignerFunctionLater(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		AutoPCBHoleAlignerImagePanel	*Form=dynamic_cast<AutoPCBHoleAlignerImagePanel *>(Obj);
		if(Form!=NULL){
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->DrawItems(DImage,pnt,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				Form->GetLayersBase()->UnlockWeakDraw();
			}
			return false;
		}
	}
	return true;
}

static	bool AutoPCBHoleAlignerFunctionLClicked(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY)
{
	DisplayImageWithAlgorithm	*a=dynamic_cast<DisplayImageWithAlgorithm	*>(TartgetForm);
	if(a!=NULL){
		if(a->GetImageDrawingMode()!=DisplayImage::_Normal){
			return true;
		}
	}
	AutoPCBHoleAlignerImagePanel	*Form=dynamic_cast<AutoPCBHoleAlignerImagePanel *>(Obj);
	if(Form!=NULL){
		FlexArea	RectArea;
		RectArea.SetRectangle(GlobalPosX-Form->ClickAreaSize/2,GlobalPosY-Form->ClickAreaSize/2
							, GlobalPosX+Form->ClickAreaSize/2,GlobalPosY+Form->ClickAreaSize/2);
		Form->ExecuteDrawEnd(RectArea);
		return false;
	}
	return true;
}

static	bool AutoPCBHoleAlignerFunctionDrawEnd(FunctionServerClass *Obj,GUIFormBase *TartgetForm)
{
	DisplayImageWithAlgorithm	*a=dynamic_cast<DisplayImageWithAlgorithm	*>(TartgetForm);
	if(a!=NULL){
		if(a->GetImageDrawingMode()!=DisplayImage::_Normal){
			return true;
		}
	}
	AutoPCBHoleAlignerImagePanel	*Form=dynamic_cast<AutoPCBHoleAlignerImagePanel *>(Obj);
	if(Form!=NULL){
		FlexArea resultarea;
		a->ToFlexArea( *a->GetRawSDataPoint(),resultarea);
		Form->ExecuteDrawEnd(resultarea);
		return false;
	}
	return true;
}

void	AutoPCBHoleAlignerImagePanel::RequireHooks(GUIFormBase *mother)
{
	DisplayImage	*DImg=dynamic_cast<DisplayImage *>(mother);
	if(DImg!=NULL){
		DImg->SetHookInPaintLast(this,AutoPCBHoleAlignerFunctionLater);
///		DImg->SetHookInMouseLClick(this,AutoPCBHoleAlignerFunctionLClicked);
///		DImg->SetHookInDrawEnd(this,AutoPCBHoleAlignerFunctionDrawEnd);
	}
}

void	AutoPCBHoleAlignerImagePanel::ExecuteDrawEnd(FlexArea &Area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAutoPCBHoleAligner" ,/**/"");
	if(GProp!=NULL){
		CmdAutoPCBHoleAlignerExecuteDrawEnd	RCmd(GetLayersBase());
		RCmd.GlobalArea=Area;
		GProp->TransmitDirectly(&RCmd);
	}
}
//=======================================================================

