#include "TreeMasterImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\TreeMasterImagePanel\TreeMasterImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "TreeMasterImagePanel.h"
#include "XCrossObj.h"
//#include "XGUI.h"
#include "XTreeMaster.h"
//#include "ImageControlTools.h"
#include "XGeneralDialog.h"
//#include "ImagePanelTools.h"
#include "XTreeMasterPacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"TreeMasterImagePanel";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"TreeMasterImagePanel");
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
	TreeMasterImagePanel	*B=new TreeMasterImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((TreeMasterImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((TreeMasterImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/TreeMasterImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Classify",/**/"TreeMaster"));
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
TreeMasterImagePanel::TreeMasterImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Classify" ,/**/"TreeMaster",QString(sRoot),QString(sName),__Master,parent)
{
}

void	TreeMasterImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}


void	TreeMasterImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyTreeMaster" ,/**/"");
	if(GProp!=NULL){
		CmdTreeMasterDrawEnd	Da(GetLayersBase());
		Da.GlobalArea		=area;
		GProp->TransmitDirectly(&Da);
	}
}

AlgorithmDrawAttr* TreeMasterImagePanel::CreateDrawAttrPointer(void){
	TreeMasterBase *TBase = (TreeMasterBase*)GetLayersBase()->GetAlgorithmBase(/**/"Classify",/**/"TreeMaster");
	if(TBase==NULL)
		return new TreeMasterDrawAttr();
	TreeMasterDrawAttr	*d=new TreeMasterDrawAttr
		(	TBase->ColorArea		,TBase->TransparentLevel,
			TBase->ColorSelected	,TBase->TransparentLevel,
			TBase->ColorActive		,TBase->TransparentLevel	); 
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyTreeMaster" ,/**/"");
	if(GProp!=NULL){
		CmdTreeReqSelectedMasterCode	Cmd(GetLayersBase());
		GProp->TransmitDirectly(&Cmd);
		d->ShowingMasterCode=Cmd.SelectedMasterCode;
	}
	return d;
}

void	TreeMasterImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

void TreeMasterImagePanel::SelectArea(IntList &LayerList,FlexArea &area){
	DisplayImageWithAlgorithm::SelectArea(LayerList,area);
}
//=======================================================================

