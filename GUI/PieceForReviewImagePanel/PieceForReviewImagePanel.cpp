#include "PieceForReviewImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PieceForReviewImagePanel\PieceForReviewImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PieceForReviewImagePanel.h"
#include "XCrossObj.h"
//#include "XGUI.h"
#include "XPieceForReview.h"
#include "XPieceForReviewPacket.h"
#include "XGeneralDialog.h"
#include "XGUIPieceForReview.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"PieceForReviewImagePanel";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"PieceForReviewImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	//new GUICmdReqAlignmentBmp(QString(sRoot),QString(sName));
	//new GUICmdSendAlignmentBmp(QString(sRoot),QString(sName));
	//new GUICmdReqAddAlignment(QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}


DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	PieceForReviewImagePanel	*B=new PieceForReviewImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((PieceForReviewImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((PieceForReviewImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PieceForReviewImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"PieceForReview"));
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

//==================================================================================================
PieceForReviewImagePanel::PieceForReviewImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"PieceForReview",QString(sRoot),QString(sName),__Master,parent)
{
}

void	PieceForReviewImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}


void	PieceForReviewImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyPieceForReview" ,/**/"");
	if(GProp!=NULL){
		CmdPieceForReviewDrawEnd	Da(GetLayersBase());
		Da.GlobalArea		=area;
		GProp->TransmitDirectly(&Da);
	}
}


AlgorithmDrawAttr	*PieceForReviewImagePanel::CreateDrawAttrPointer(void)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceForReview");
	if(Ab!=NULL){
		PieceForReviewBase	*M=(PieceForReviewBase *)Ab;
		PieceForReviewDrawAttr	*mattr=new PieceForReviewDrawAttr(
									   M->ColorPieceForReview	,M->TransparentLevel
									  ,M->ColorSelected			,M->TransparentLevel
									  ,M->ColorActive			,M->TransparentLevel
									  ,M->NegColorPieceForReview
									  ,M->NegColorSelected);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyPieceForReview" ,/**/"");
		if(GProp!=NULL){
			CmdPieceForReviewDrawAttr	Da(GetLayersBase());
			Da.Attr		=mattr;
			GProp->TransmitDirectly(&Da);
		}
		return mattr;
	}
	return new PieceForReviewDrawAttr();
}


void	PieceForReviewImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}
//=======================================================================

