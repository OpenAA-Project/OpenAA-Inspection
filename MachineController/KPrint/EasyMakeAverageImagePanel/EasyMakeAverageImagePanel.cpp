/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyMakeAverageImagePanel\EasyMakeAverageImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EasyMakeAverageImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include <QColor>
#include <QByteArray>
#include <QIcon>
#include <QPixmap>
#include "XMakeAverageImage.h"
#include "EasyMakeAverageImageForm.h"

const	char *sRoot=/**/"KidaPrint";
const	char *sName=/**/"EasyMakeAverageImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root, QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"EasyMakeAverageImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);
	Q_INIT_RESOURCE(IntegrationLib);

	//DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
	Q_CLEANUP_RESOURCE(IntegrationLib);
}

DEFFUNCEX	GUIFormBase *DLL_CreateInstance(LayersBase *Base, QWidget *parent)
{
	EasyMakeAverageImagePanel *B=new EasyMakeAverageImagePanel(Base, parent);
	//B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void *Instance, struct	PropertyClass Data[], WORD	maxDataDim)
{
	int	N=((EasyMakeAverageImagePanel *)Instance)->SetPropertyInDLL(Data, maxDataDim);
	if(N < 0)
		return -1;
	//Data[N].Type				  =/**/"QString";
	//Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	//Data[N].Pointer			  =&((EasyMakeAverageImagePanel *)Instance)->ImageControlToolsName;
	//N++;
	return(N);
}

DEFFUNCEX	QIcon *DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyMakeAverageImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"MakeAverageImage"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg, int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

EasyMakeAverageImagePanel::EasyMakeAverageImagePanel(LayersBase *Base, QWidget *parent)
	:IntegrationAlgoSimpleImagePanel(Base,/**/"Basic",/**/"MakeAverageImage", parent)
{
	SetMode(mtFrameDraw::fdPoly);
	UseSelectionDialog=true;
}

void	EasyMakeAverageImagePanel::Prepare(void)
{
	IntegrationAlgoSimpleImagePanel::Prepare();
}

AlgorithmDrawAttr *EasyMakeAverageImagePanel::CreateDrawAttrPointer(void)
{
	//GUIFormBase *GProp=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"EasyMakeAverageImage",/**/"");
	//CmdMaskingDrawInfo	Da(GetLayersBase());
	//if(GProp != NULL) {
	//	GProp->TransmitDirectly(&Da);
	//}

	CmdReqAverageDrawMode	RCmd(GetLayersBase());
	RCmd.DrawAttr=MakeAverageImageDrawAttr::_Average;
	GUIFormBase *GUIRet[100];
	int	n;
	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyMakeAverageImage", GUIRet, 100);
	for(int i=0;i < n;i++) {
		EasyMakeAverageImageForm *GUI=dynamic_cast<EasyMakeAverageImageForm *>(GUIRet[i]);
		if(GUI!=NULL) {
			if(GUI->TargetSlaveNo==GetSlaveNo()){
				GUI->TransmitDirectly(&RCmd);
				break;
			}
		}
	}

	MakeAverageImageDrawAttr *mattr=new MakeAverageImageDrawAttr(GetLayersBase()
																,Qt::green		,128
																,Qt::magenta	,128
																,Qt::red		,128);
	mattr->DType=DisplayImage::__Master;

	mattr->DrawMode=RCmd.DrawAttr;
	mattr->ModeShowItems=true;

	return mattr;
}

void	EasyMakeAverageImagePanel::MakeDataToAddItem(FlexArea &GlobalArea, QByteArray &Data)
{
	//GUIFormBase *GUIRet[100];
	//int	n;
	//n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyMakeAverageImage", GUIRet, 100);
	//for(int i=0;i < n;i++) {
	//	EasyPropertyMaskingForm *GUI=dynamic_cast<EasyPropertyMaskingForm *>(GUIRet[i]);
	//	if(GUI != NULL) {
	//		if(GUI->SlaveNo == GetSlaveNo()) {
	//			CmdMaskingDrawInfo	Da(GetLayersBase());
	//			GUI->TransmitDirectly(&Da);
	//
	//			QBuffer	Buff;
	//			Buff.open(QIODevice::WriteOnly);
	//			::Save(&Buff, Da.Effective);
	//			Da.LimitedLib.Save(&Buff);
	//			Data=Buff.buffer();
	//		}
	//	}
	//}
}
void	EasyMakeAverageImagePanel::AddItemInAlgorithm(int SlaveNo, AlgorithmInPageRoot *APage, IntList &LayerList, FlexArea &Area, QByteArray &Data,QByteArray &SomethingData)
{
	CmdAddAverageArea	Cmd(GetLayersBase());
	Cmd.Area=Area;
	if(APage != NULL)
		APage->TransmitDirectly(&Cmd);
}


//=======================================================================


