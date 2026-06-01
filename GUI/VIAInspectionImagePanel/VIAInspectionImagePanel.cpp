/*
 * Copyright (C) 2024
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "VIAInspectionImagePanelResource.h"


#define _USE_MATH_DEFINES
#include <math.h>
#include "VIAInspectionImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include <QBitmap>
#include "XViaInspection.h"
#include "XGUI.h"
//#include "ImagePanelTools.h"
#include "XPropertyVIAPacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"VIAInspectionImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"VIAInspectionImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,__Master);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	VIAInspectionImagePanel	*B=new VIAInspectionImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	VIAInspectionImagePanel *InstancePtr=dynamic_cast<VIAInspectionImagePanel *>((VIAInspectionImagePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				  =/**/"QString";
		Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
		Data[N].Pointer				=&((VIAInspectionImagePanel *)Instance)->ImageControlToolsName;

		return(N+1);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/VIAInspectionImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"VIAInspection"));
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

VIAInspectionImagePanel::VIAInspectionImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"VIAInspection",QString(sRoot),QString(sName),__Master,parent)
{
}

void	VIAInspectionImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(fdRectangle ,Qt::red);
}

void	VIAInspectionImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);
}

void	VIAInspectionImagePanel::DrawBtnDown()
{
	SetModeByOthers(fdRectangle ,Qt::red);
}

AlgorithmDrawAttr	*VIAInspectionImagePanel::CreateDrawAttrPointer(void)
{	
	VIABase	*Base=(VIABase *)GetAlgorithmBase();
	if(Base!=NULL){
		return new VIADrawAttr(GetLayersBase()
								,Base->ColorVIANormal	,100
								,Base->ColorVIASelected	,100
								,Base->ColorVIAActive	,100
								,Base->ColorPickup		,80
								,Base->VIAColor0
								,Base->VIAColor1
								,Base->VIAColor2
								,Base->VIAColor3
								,Base->VIAColor4
								,Base->VIAColor5
								,Base->VIAColor6
								,Base->VIAColor7);
	}
	return NULL;
}

void	VIAInspectionImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=LBase->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
	if(Ab==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyVIAInspection" ,/**/"");
	if(GProp!=NULL){
		CmdVIADrawEnd	Da(GetLayersBase());
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}

void	VIAInspectionImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}
