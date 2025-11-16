/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-Desktop\CategorizedShaderImagePanel\CategorizedShaderImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "CategorizedShaderImagePanel.h"
#include "XCrossObj.h"
#include "XCategorizedShader.h"
#include "XPropertyCategorizedShaderPacket.h"
#include "XGeneralDialog.h"
#include "XDisplayImagePacket.h"



static	char	*sRoot="Inspection";
static	char	*sName="CategorizedShaderImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("CategorizedShader ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
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
	CategorizedShaderImagePanel	*B=new CategorizedShaderImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((CategorizedShaderImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 ="QString";
	Data[N].VariableNameWithRoute="ImageControlToolsName";
	Data[N].Pointer				 =&((CategorizedShaderImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/CategorizedShaderImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList("Basic","CategorizedShader"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

//==================================================================================================
CategorizedShaderImagePanel::CategorizedShaderImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"CategorizedShader",QString(sRoot),QString(sName),__Master,parent)
{
}

void	CategorizedShaderImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	CategorizedShaderImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

void	CategorizedShaderImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyCategorizedShader" ,/**/"");
	CmdCategorizedShaderDrawEnd	Da(GetLayersBase());
	Da.Area			=area;
	GProp->TransmitDirectly(&Da);
}


AlgorithmDrawAttr	*CategorizedShaderImagePanel::CreateDrawAttrPointer(void)
{	
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyCategorizedShader" ,/**/"");
	//CmdMaskingDrawOnOffPacket	Da;
	//if(GProp!=NULL){
	//	GProp->TransmitDirectly(&Da);
	//}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CategorizedShader");
	if(Ab!=NULL){
		CategorizedShaderBase	*M=(CategorizedShaderBase *)Ab;
		CategorizedShaderDrawAttr	*mattr=new CategorizedShaderDrawAttr(
									GetLayersBase()
								  ,M->ColorItem		,M->TransparentLevel
								  ,M->ColorSelected	,M->TransparentLevel
								  ,M->ColorActive	,M->TransparentLevel
								  );
		//mattr->EffectiveMode	=Da.Effective;
		//mattr->IneffectiveMode	=Da.Ineffective;
		return mattr;
	}
	return new CategorizedShaderDrawAttr();
}


//=======================================================================
