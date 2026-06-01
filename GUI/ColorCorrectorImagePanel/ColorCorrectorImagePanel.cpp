/*
 * Copyright (C) 2025
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

#include "ColorCorrectorImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XColorCorrector.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XPropertyColorCorrectorPacket.h"
#include "XDataInLayer.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"ColorCorrectorImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"ColorCorrectorImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,__Master);

	(*Base)=new GUICmdReqItemIndependentPack	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendIndependentPack		(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	ColorCorrectorImagePanel	*B=new ColorCorrectorImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((ColorCorrectorImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((ColorCorrectorImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ColorCorrectorImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ColorCorrector"));
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

ColorCorrectorImagePanel::ColorCorrectorImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"ColorCorrector",QString(sRoot),QString(sName),__Master,parent)
{
}

void	ColorCorrectorImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

AlgorithmDrawAttr	*ColorCorrectorImagePanel::CreateDrawAttrPointer(void)
{	
	CmdColorCorrectorDrawModePacket	MCmd(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyColorCorrector" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&MCmd);
	}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorCorrector");
	if(Ab!=NULL){
		ColorCorrectorBase	*M=(ColorCorrectorBase *)Ab;
		ColorCorrectorDrawAttr	*mattr=new ColorCorrectorDrawAttr(GetLayersBase()
								  ,M->ColorNormal		,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel);
		mattr->VType=MCmd.VType;
		return mattr;
	}
	return new ColorCorrectorDrawAttr(GetLayersBase());
}

void	ColorCorrectorImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=LBase->GetAlgorithmBase(/**/"Basic",/**/"ColorCorrector");
	if(Ab==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyColorCorrector" ,/**/"");
	CmdColorCorrectorDrawEnd	Da(GetLayersBase());
	if(GProp!=NULL){
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		GProp->TransmitDirectly(&Da);
	}
}

void	ColorCorrectorImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}