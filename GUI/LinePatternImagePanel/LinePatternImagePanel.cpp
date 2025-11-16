/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LinePatternImagePanel\LinePatternImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "LinePatternImagePanel.h"
#include "XAlgorithmDLL.h"

#include "XCrossObj.h"
#include "XLinePatternInspection.h"
#include "XGeneralDialog.h"
#include "XLinePatternPacket.h"



static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"LinePatternImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Image panel for LinePattern inspection");
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
	LinePatternImagePanel	*B=new LinePatternImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((LinePatternImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((LinePatternImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/LinePatternImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"LinePattern"));
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

//==================================================================================================
LinePatternImagePanel::LinePatternImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"LinePattern",QString(sRoot),QString(sName),__Master,parent)
{
}

void	LinePatternImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	LinePatternImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

AlgorithmDrawAttr	*LinePatternImagePanel::CreateDrawAttrPointer(void)
{
	LinePatternBase	*a=dynamic_cast<LinePatternBase *>(GetAlgorithmBase());
	if(a!=NULL){
		LinePatternDrawAttr	*c=new LinePatternDrawAttr(a->ColorMask		,a->TransparentLevel
											,  a->ColorSelected	,a->TransparentLevel
											,  a->ColorActive	,a->TransparentLevel
											,a->NegColorMask
											,a->NegColorSelected);

		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyLinePattern" ,/**/"");
		if(GProp!=NULL){
			CmdLinePatternDrawPacket	Da(GetLayersBase());
			GProp->TransmitDirectly(&Da);
			c->ModeDrawArea		=Da.ModeDrawArea		;
			c->ModeDrawInside	=Da.ModeDrawInside;
			c->ModeDrawOutside	=Da.ModeDrawOutside;
			c->ResultAngleNumber=Da.ResultAngleNumber;
		}
		return c;
	}
	else{
		LinePatternDrawAttr	*c=new LinePatternDrawAttr();
		return c;
	}
}

void	LinePatternImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyLinePattern" ,/**/"");
	VectorLineBase	*V=GetVectorLineBase();
	if(V!=NULL && GProp!=NULL){
		AddLinePacket	Da(GetLayersBase());
		Da.Vector		=V;
		GetActiveLayerList(Da.LayerList);
		GProp->TransmitDirectly(&Da);
	}
	//if(GProp!=NULL){
	//	CmdLinePatternDrawEnd	Da(GetLayersBase());
	//	Da.Area			=area;
	//	GetActiveLayerList(Da.LayerList);
	//	GProp->TransmitDirectly(&Da);
	//}
}

void	LinePatternImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================


