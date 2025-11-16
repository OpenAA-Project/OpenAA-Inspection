/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AlignmentBlockImagePanel\AlignmentBlockImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define _USE_MATH_DEFINES
#include <math.h>
#include "AlignmentBlockImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
//#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include <QBitmap>
#include "XAlignmentBlock.h"
#include "SelectPages.h"
#include "XGUI.h"
//#include "ImagePanelTools.h"
//#include "PropertyAlignmentBlockForm.h"
//#include "XPropertyAlignmentBlockPacket.h"
#include "XDisplayImagePacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"AlignmentBlockImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"AlignmentBlock ImagePanel");
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
	AlignmentBlockImagePanel	*B=new AlignmentBlockImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	AlignmentBlockImagePanel *InstancePtr=dynamic_cast<AlignmentBlockImagePanel *>((AlignmentBlockImagePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				  =/**/"QString";
		Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
		Data[N].Pointer				=&((AlignmentBlockImagePanel *)Instance)->ImageControlToolsName;

		return(N+1);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/AlignmentBlockImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AlignmentBlock"));
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

AlignmentBlockImagePanel::AlignmentBlockImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"AlignmentBlock",QString(sRoot),QString(sName),__Target,parent)
{
}

void	AlignmentBlockImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

void	AlignmentBlockImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);
}

void	AlignmentBlockImagePanel::DrawBtnDown()
{
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

AlgorithmDrawAttr	*AlignmentBlockImagePanel::CreateDrawAttrPointer(void)
{	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentBlock");
	if(Ab!=NULL){
		AlignmentBlockBase	*M=(AlignmentBlockBase *)Ab;
		AlignmentBlockDrawAttr	*mattr=new AlignmentBlockDrawAttr(GetLayersBase()
								  ,M->ColorArea			,128
								  ,M->ColorSelected		,128
								  ,M->ColorActive		,128);
		
		return mattr;
	}
	return new AlignmentBlockDrawAttr(GetLayersBase());
}

void	AlignmentBlockImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=LBase->GetAlgorithmBase(/**/"Basic",/**/"AlignmentBlock");
	if(Ab==NULL)
		return;
	AlignmentBlockBase	*MBase=dynamic_cast<AlignmentBlockBase *>(Ab);
	if(MBase==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentBlock" ,/**/"");
	//CmdAlignmentBlockDrawEnd	Da(GetLayersBase());
	//if(GProp!=NULL){
	//	GetActiveLayerList(Da.LayerList);
	//	Da.Area=area;
	//	GProp->TransmitDirectly(&Da);
	//}
}

void	AlignmentBlockImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

