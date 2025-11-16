/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SavePartialImagePanel\SavePartialImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#define _USE_MATH_DEFINES
#include <math.h>
#include "SavePartialImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include <QBitmap>
#include "XSavePartialImage.h"
#include "XGUI.h"
//#include "ImagePanelTools.h"
#include "XPropertySavePartialImagePacket.h"


static	const	char	*sRoot="Inspection";
static	const	char	*sName="SavePartialImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("SavePartialImagePanel");
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
	SavePartialImagePanel	*B=new SavePartialImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	SavePartialImagePanel *InstancePtr=dynamic_cast<SavePartialImagePanel *>((SavePartialImagePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				  ="QString";
		Data[N].VariableNameWithRoute="ImageControlToolsName";
		Data[N].Pointer				=&((SavePartialImagePanel *)Instance)->ImageControlToolsName;

		return(N+1);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/SavePartialImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList("Basic","SavePartialImage"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

//====================================================================================

SavePartialImagePanel::SavePartialImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,"Basic" ,"SavePartialImage",QString(sRoot),QString(sName),__Master,parent)
{
}

void	SavePartialImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

void	SavePartialImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);
}

void	SavePartialImagePanel::DrawBtnDown()
{
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

AlgorithmDrawAttr	*SavePartialImagePanel::CreateDrawAttrPointer(void)
{	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SavePartialImage");
	if(Ab!=NULL){
		SavePartialImageBase	*M=(SavePartialImageBase *)Ab;
		SavePartialImageDrawAttr	*mattr=new SavePartialImageDrawAttr();

		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertySavePartialImage" ,/**/"");
		CmdGetDrawAttr	Da(GetLayersBase());
		if(GProp!=NULL){
			GProp->TransmitDirectly(&Da);
		}
		
		return mattr;
	}
	return new SavePartialImageDrawAttr();
}

void	SavePartialImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=LBase->GetAlgorithmBase(/**/"Basic",/**/"SavePartialImage");
	if(Ab==NULL)
		return;
	SavePartialImageBase	*MBase=dynamic_cast<SavePartialImageBase *>(Ab);
	if(MBase==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertySavePartialImage" ,/**/"");
	CmdCreateSavePartialImageManualPacket	Da(GetLayersBase());
	if(GProp!=NULL){
		Da.Area=area;
		GProp->TransmitDirectly(&Da);
	}
}

void	SavePartialImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

