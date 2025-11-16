/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\RasterReferenceImagePanel\RasterReferenceImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "RasterReferenceImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
//#include "ImageControlTools.h"
#include "XRaster.h"
#include "XGeneralFunc.h"
//#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XGUIRasterPacket.h"
#include "XDataAlgorithm.h"
#include "swap.h"

#include <QIcon>
#include <QPixmap>
#include <QWidget>
#include <QMessageBox>

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"RasterReferenceImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"RasterReferenceImagePanel");
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
	RasterReferenceImagePanel	*B=new RasterReferenceImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((RasterReferenceImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((RasterReferenceImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/RasterReferenceImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Raster"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

RasterReferenceImagePanel::RasterReferenceImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"Raster",QString(sRoot),QString(sName),__Master,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

RasterReferenceImagePanel::~RasterReferenceImagePanel(void)
{
}

void	RasterReferenceImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);

	//connect(this,SIGNAL(SignalJustMouseLPress(int,int)),this,SLOT(SlotJustMouseLPress (int ,int )));
}

AlgorithmDrawAttr	*RasterReferenceImagePanel::CreateDrawAttrPointer(void)
{	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Raster");
	if(Ab!=NULL){
		RasterBase	*M=(RasterBase *)Ab;
		RasterDrawAttr	*mattr=new RasterDrawAttr(
								   M->ColorNormal		,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRasterReference" ,/**/"");
		if(GProp!=NULL){
			CmdRasterGetDrawAttr	Da(GetLayersBase());
			GProp->TransmitDirectly(&Da);
			mattr->ShownFileID		=Da.ShownFileID	;
			for(int i=0;i<MaxRasterLayer;i++){
				mattr->LayerColor[i]=Da.LayerColor[i];
			}
			for(int i=0;i<MaxRasterLayer;i++){
				mattr->DrawMode.FileLayerIDTable[i]=Da.FileLayerIDTable[i];
			}
			mattr->DrawMode.CurrentElementGlobalPage	=Da.CurrentElementGlobalPage;

			mattr->DrawMode.CurrentElementID	=-1;
			mattr->MaskIDLsit				=Da.MaskIDList		;

			mattr->DrawMode.ShowPDF			=Da.ShowPDF			;
			mattr->DrawMode.MoveMode		=Da.MoveMode		;
			mattr->DrawMode.MoveElementMode	=Da.MoveElementMode	;
			mattr->DrawMode.RotateMode		=Da.RotateMode		;
			mattr->DrawMode.ExtendMode		=Da.ExtendMode		;
			mattr->DrawMode.SlopeXMode		=Da.SlopeXMode		;
			mattr->DrawMode.SlopeYMode		=Da.SlopeYMode		;
			mattr->DrawMode.AlignmentMode	=Da.AlignmentMode	;
			mattr->DrawMode.DrawPickUpArea	=Da.DrawPickUpArea	;
			mattr->DrawMode.ShowReferenceItems	=Da.ShowReferenceItems;
			mattr->DrawMode.ReferenceID			=Da.ReferenceID;
		}
		
		return mattr;
	}
	return new RasterDrawAttr();
}

void	RasterReferenceImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRasterReference" ,/**/"");
	if(GProp!=NULL){
		CmdRasterDrawEnd	Da(GetLayersBase());
		Da.Area=area;
		GProp->TransmitDirectly(&Da);
	}
}

void	RasterReferenceImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}
