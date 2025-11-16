#include "ThinMetalImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ThinMetalImagePanel\ThinMetalImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#define _USE_MATH_DEFINES
#include <math.h>
#include "ThinMetalImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include <QBitmap>
#include "XThinMetal.h"
#include "XGUI.h"
//#include "ImagePanelTools.h"
#include "XPropertyThinMetalPacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"ThinMetalImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"ThinMetalImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	ThinMetalImagePanel	*B=new ThinMetalImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	ThinMetalImagePanel *InstancePtr=dynamic_cast<ThinMetalImagePanel *>((ThinMetalImagePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				  =/**/"QString";
		Data[N].VariableNameWithRoute =/**/"ImageControlToolsName";
		Data[N].Pointer				=&((ThinMetalImagePanel *)Instance)->ImageControlToolsName;

		Data[N+1].Type				  =/**/"int32";
		Data[N+1].VariableNameWithRoute =/**/"DefaultLibID";
		Data[N+1].Pointer				=&((ThinMetalImagePanel *)Instance)->DefaultLibID;
		return(N+2);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ThinMetalImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ThinMetal"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

ThinMetalImagePanel::ThinMetalImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"ThinMetal",QString(sRoot),QString(sName),__Master,parent)
{
	DefaultLibID=-1;
}

void	ThinMetalImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

void	ThinMetalImagePanel::ReadyParam(void)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(ImageControlToolsName);
	if(f!=NULL){
		CmdSetImageControlTools	RCmd(GetLayersBase());
		RCmd.ModeImageMaster	=false;
		RCmd.ModeImageTarget	=true;
		RCmd.ModeImageTargetTR	=false;
		f->TransmitDirectly(&RCmd);
	}

	//GUIFormBase	*Prop=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyThinMetal",/**/"");
}

void	ThinMetalImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);
}

void	ThinMetalImagePanel::DrawBtnDown()
{
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

AlgorithmDrawAttr	*ThinMetalImagePanel::CreateDrawAttrPointer(void)
{	
	ThinMetalBase	*Base=(ThinMetalBase *)GetAlgorithmBase();
	if(Base!=NULL){
		return new ThinMetalDrawAttr(GetLayersBase()
								,Base->ColorArea	,100
								,Base->ColorSelected	,100
								,Base->ColorActive	,100);
	}
	return NULL;
}

void	ThinMetalImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=LBase->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(Ab==NULL)
		return;
	ThinMetalBase	*MBase=dynamic_cast<ThinMetalBase *>(Ab);
	if(MBase==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyThinMetal" ,/**/"");
	if(GProp!=NULL){
		CmdThinMetalDrawEnd	Da(GetLayersBase());
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
	else{
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual ThinMetal");

		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			int	page=P->GetValue();
			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
			FlexArea	A=area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

				CmdCreateTempThinMetalItemPacket	ItemPacket(GetLayersBase());
				MBase->TransmitDirectly(&ItemPacket);

				CmdCreateTempThinMetalLibraryPacket	LibPacket(GetLayersBase());
				Ab->TransmitDirectly(&LibPacket);
				AlgorithmLibraryLevelContainer	*TempLib=LibPacket.Point;
	
				TempLib->SetLibID(DefaultLibID);
				CmdLoadThinMetalLibraryPacket	Packet(GetLayersBase());
				Packet.Point=TempLib;
				AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
				MBase->TransmitDirectly(&Packet);
				
				CmdCreateByteArrayFromThinMetalItemPacket	BCmd(GetLayersBase());
				BCmd.Point=(ThinMetalItem *)ItemPacket.Point;

				ThinMetalLibrary	*ALib=dynamic_cast<ThinMetalLibrary *>(TempLib->GetLibrary());
				BCmd.Point	->SetLibID(TempLib->GetLibID());
				BCmd.Point	->GetThresholdW()->BrightWidthL	=ALib->BrightWidthL	;
				BCmd.Point	->GetThresholdW()->BrightWidthH	=ALib->BrightWidthH	;
				BCmd.Point	->GetThresholdW()->OKDotL		=ALib->OKDotL		;
				BCmd.Point	->GetThresholdW()->OKDotH		=ALib->OKDotH		;
				BCmd.Point	->GetThresholdW()->OKLengthL	=ALib->OKLengthL		;
				BCmd.Point	->GetThresholdW()->OKLengthH	=ALib->OKLengthH		;
				
				BCmd.Point	->GetThresholdW()->MaxNGDotL	=ALib->MaxNGDotL		;
				BCmd.Point	->GetThresholdW()->MaxNGDotH	=ALib->MaxNGDotH		;
				BCmd.Point	->GetThresholdW()->ShrinkDot	=ALib->ShrinkDot		;
				BCmd.Point	->GetThresholdW()->EnlargeDot	=ALib->EnlargeDot	;

				MBase->TransmitDirectly(&BCmd);

				GUICmdSendAddManualThinMetal	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
				Cmd.Area=A;
				Cmd.BItem=BCmd.Buff;
				Cmd.LayerList.Add(0);
				Cmd.SendOnly(GlobalPage,0);
			}
		}
	}
}

void	ThinMetalImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

