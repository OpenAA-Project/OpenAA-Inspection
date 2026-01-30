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

#include "MultiFileMapImagePanelResource.h"

#include "MultiFileMapImagePanel.h"
#include "XCrossObj.h"
#include "XGeneralFunc.h"
#include "XMultiFileMap.h"
//#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XGUIMultiFileMapPacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"MultiFileMapImagePanel";
//LayersBase *_Base;


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"MultiFileMap ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Target);

	(*Base)=new GUICmdAckMultiFileMapInfo	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqMultiFileMapInfo(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	//_Base=Base;
	MultiFileMapImagePanel	*B=new MultiFileMapImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((MultiFileMapImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((MultiFileMapImagePanel *)Instance)->ImageControlToolsName;
	N++;

	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	QPixmap	D(/**/":Resources/MultiFileMapImagePanel.png");
	return(new QIcon(D));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"MultiFileMap"));
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
MultiFileMapImagePanel::MultiFileMapImagePanel(LayersBase *Base,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"MultiFileMap",QString(sRoot),QString(sName),__Master,parent)
{
}

void	MultiFileMapImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

AlgorithmDrawAttr	*MultiFileMapImagePanel::CreateDrawAttrPointer(void)
{
//	GUICmdReqLineEnhancerDrawMode	DrawMode(GetLayersBase());
//	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMultiFileMap" ,/**/"");
//	if(GProp!=NULL){
//		GProp->TransmitDirectly(&DrawMode);
//	}
	MultiFileMapBase	*Algo=(MultiFileMapBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MultiFileMap");
	MultiFileMapDrawAttr	*A=new MultiFileMapDrawAttr (Algo->ColorArea	,Algo->TransparentLevel
														,Algo->ColorSelected,Algo->TransparentLevel
														,Algo->ColorActive	,Algo->TransparentLevel
														,Algo->NegColorArea
														,Algo->NegColorSelected);

	return A;
}
void	MultiFileMapImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}
void	MultiFileMapImagePanel::MouseMoveEvent(int globalX ,int globalY)
{
	DisplayImageWithAlgorithm::MouseMoveEvent(globalX ,globalY);
	IntList PageList;
	GetLayersBase()->GetGlobalPage(globalX ,globalY,PageList);
	for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
		int	GlobalPage=c->GetValue();
		GUICmdReqMultiFileMapInfo	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckMultiFileMapInfo	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.GlobalX=globalX;
		RCmd.GlobalY=globalY;
		GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMultiFileMap" ,/**/"");
		RCmd.Send(GlobalPage,0,ACmd);
		if(DProp!=NULL && ACmd.PosX>=0 && ACmd.PosY>=0){
			DProp->TransmitDirectly(&ACmd);
		}	
	}
}
//=======================================================================