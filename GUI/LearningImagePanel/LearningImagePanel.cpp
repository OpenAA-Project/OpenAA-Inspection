#include "LearningImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LearningImagePanel\LearningImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "LearningImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "XLearning.h"
#include "ImageControlTools.h"
#include "XGeneralDialog.h"
#include "ImagePanelTools.h"
#include "XLearningPacket.h"


static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"LearningImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"LearningImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Target);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

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
	LearningImagePanel	*B=new LearningImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((LearningImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((LearningImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/LearningImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Learning"));
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
LearningImagePanel::LearningImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"Learning",QString(sRoot),QString(sName),__Target,parent)
{
}

void	LearningImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	LearningImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

void	LearningImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyLearningForm" ,/**/"");

	if(GProp!=NULL){
		AddLearningArea	Da(GetLayersBase());
		Da.Area			=area;
		GProp->TransmitDirectly(&Da);
	}
}


AlgorithmDrawAttr	*LearningImagePanel::CreateDrawAttrPointer(void)
{	
	/*
	GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertyLearning" ,"");
	CmdMaskingPIDrawOnOffPacket	Da;
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
	}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase("Basic","Learning");
	if(Ab!=NULL){
		MaskingPIBase	*M=(MaskingPIBase *)Ab;
		MaskingPIDrawAttr	*mattr=new MaskingPIDrawAttr(
								   M->ColorMask			,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel
								  ,M->NegColorMask		
								  ,M->NegColorSelected);
		mattr->EffectiveMode	=Da.Effective;
		mattr->IneffectiveMode	=Da.Ineffective;
		return mattr;
	}
	*/
	QColor	ColorRuleNG;
	QColor	ColorRuleOK;

	LearningRuleBase	*ABase=(LearningRuleBase *)GetAlgorithmBase();
	LearningRuleDrawAttr	*L=new LearningRuleDrawAttr(ABase->ColorRuleNG,ABase->ColorRuleOK,ABase->TransparentLevel
														,ABase->ColorSelected	,ABase->TransparentLevel
														,ABase->ColorActive		,ABase->TransparentLevel);
	return L;
}

void LearningImagePanel::ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName)
{
	DisplayImageWithAlgorithm::ExecutePasteShape(OriginRoot ,OriginName);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyLearningForm" ,/**/"");
	if(GProp!=NULL)
		GProp->BuildForShow();
}

void	LearningImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================

