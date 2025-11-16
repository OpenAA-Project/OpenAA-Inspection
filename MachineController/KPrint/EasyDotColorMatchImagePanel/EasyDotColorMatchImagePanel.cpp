/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyDotColorMatchImagePanel\EasyDotColorMatchImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EasyDotColorMatchImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XPropertyDotColorMatchingPacket.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyDotColorMatchImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"EasyDotColorMatchImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);
	Q_INIT_RESOURCE(IntegrationLib);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
	Q_CLEANUP_RESOURCE(IntegrationLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	EasyDotColorMatchImagePanel	*B=new EasyDotColorMatchImagePanel(Base,parent);
	//B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((EasyDotColorMatchImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	//Data[N].Type				  =/**/"QString";
	//Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	//Data[N].Pointer			  =&((EasyMaskingImagePanel *)Instance)->ImageControlToolsName;
	//N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyDotColorMatchImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DotColorMatching"));
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

EasyDotColorMatchImagePanel::EasyDotColorMatchImagePanel(LayersBase *Base ,QWidget *parent)
:IntegrationAlgoSimpleImagePanel(Base,/**/"Basic",/**/"DotColorMatching",parent)
{
	SetMode(mtFrameDraw::fdPoly);
	UseSelectionDialog=true;
}
void	EasyDotColorMatchImagePanel::Prepare(void)
{
	IntegrationAlgoSimpleImagePanel::Prepare();
}

AlgorithmDrawAttr	*EasyDotColorMatchImagePanel::CreateDrawAttrPointer(void)
{
	return new DotColorMatchingDrawAttr(GetLayersBase()
							,Qt::green		,128
							,Qt::magenta	,128
							,Qt::red		,128
							,Qt::cyan		,80
							,Qt::green
							,QColor(128,255,0)
							,QColor(192,255,0)
							,QColor(128,255,64)
							,QColor(192,255,64)
							,QColor(64,255,64)
							,QColor(128,255,128)
							,QColor(168,255,0)		);
}
