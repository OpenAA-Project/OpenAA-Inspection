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

#include "XRay3DImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XXRay3D.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XPropertyXRay3DPacket.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"XRay3DImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"XRay3DImagePanel");
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
	XRay3DImagePanel	*B=new XRay3DImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((XRay3DImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((XRay3DImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/XRay3DImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"XRay3D"));
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

XRay3DImagePanel::XRay3DImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"XRay3D",QString(sRoot),QString(sName),__Master,parent)
{
}

void	XRay3DImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

AlgorithmDrawAttr	*XRay3DImagePanel::CreateDrawAttrPointer(void)
{
	XRay3DDrawAttr	*A=new XRay3DDrawAttr();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyXRay3D" 											,/**/"");
	if(GProp!=NULL){
		//CmdXRay3DDrawAttr	Da(GetLayersBase());
		//GProp->TransmitDirectly(&Da);
		//A->BlockColor0=Da.BlockColor0;
		//A->BlockColor1=Da.BlockColor1;
		//A->BlockColor2=Da.BlockColor2;
		//A->BlockColor3=Da.BlockColor3;
		//A->BlockColor4=Da.BlockColor4;
		//A->BlockColor5=Da.BlockColor5;
		//A->BlockColor6=Da.BlockColor6;
		//A->BlockColor7=Da.BlockColor7;
	}
	return A;
}

void	XRay3DImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyXRay3D" 											,/**/"");
	if(GProp!=NULL){
		//GUICmdXRay3DDrawEnd	Da(GetLayersBase());
		//Da.Area=area;
		//GProp->TransmitDirectly(&Da);
	}
}

void	XRay3DImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}