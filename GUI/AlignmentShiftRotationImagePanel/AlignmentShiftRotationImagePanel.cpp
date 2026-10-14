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

#include "AlignmentShiftRotationImagePanel.h"
#include "XCrossObj.h"
#include "XGUIDLL.h"
#include "XGUI.h"
//#include "ImageControlTools.h"
#include "XAlignmentShiftRotation.h"
#include "XGeneralFunc.h"
//#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XPacketAlignmentShiftRotation.h"
#include "XPropertyAlignmentShiftRotationPacket.h"


const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"AlignmentShiftRotationImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"AlignmentShiftRotationImagePanel");
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
	AlignmentShiftRotationImagePanel	*B=new AlignmentShiftRotationImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((AlignmentShiftRotationImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((AlignmentShiftRotationImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/AlignmentShiftRotationImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AlignmentShiftRotation"));
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

AlignmentShiftRotationImagePanel::AlignmentShiftRotationImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"AlignmentShiftRotation",QString(sRoot),QString(sName),__Master,parent)
{
}

AlignmentShiftRotationImagePanel::~AlignmentShiftRotationImagePanel(void)
{}

void	AlignmentShiftRotationImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

AlgorithmDrawAttr	*AlignmentShiftRotationImagePanel::CreateDrawAttrPointer(void)
{
	AlignmentShiftRotationDrawAttr	*A=new AlignmentShiftRotationDrawAttr();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentShiftRotation" 
												,/**/"");
	if(GProp!=NULL){
		CmdAlignmentShiftRotationDrawModePacket	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
		A->DrawModeArea		= Da.DrawModeArea;
		A->DrawModeHVLines	= Da.DrawModeHVLines;
		A->HVLinesPage			=Da.HVLinesPage			;
		A->HVLinesPhase			=Da.HVLinesPhase		;
		A->HVLinesItemID		=Da.HVLinesItemID		;
		A->HVLinesAngleIndex	=Da.HVLinesAngleIndex	;
	}

	return A;
}

void	AlignmentShiftRotationImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentShiftRotation" 
												,/**/"");
	if(GProp!=NULL){
		CmdAlignmentShiftRotationDrawEnd	Da(GetLayersBase());
		Da.Area=area;
		GProp->TransmitDirectly(&Da);
	}
}

void	AlignmentShiftRotationImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

void	AlignmentShiftRotationImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
}
