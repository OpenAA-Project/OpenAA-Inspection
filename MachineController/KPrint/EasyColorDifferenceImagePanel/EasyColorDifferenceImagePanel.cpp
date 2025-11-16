/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyColorDifferenceImagePanel\EasyColorDifferenceImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EasyColorDifferenceImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XColorDifference.h"
#include <QColor>
#include "XGUIDLL.h"
#include "EasyPropertyColorDifferenceForm.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyColorDifferenceImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"EasyColorDifferenceImagePanel");
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

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	EasyColorDifferenceImagePanel	*B=new EasyColorDifferenceImagePanel(Base,parent);
	//B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((EasyColorDifferenceImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	//Data[N].Type				  =/**/"QString";
	//Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	//Data[N].Pointer			  =&((EasyColorDifferenceImagePanel *)Instance)->ImageControlToolsName;
	//N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyColorDifferenceImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ColorDifference"));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

EasyColorDifferenceImagePanel::EasyColorDifferenceImagePanel(LayersBase *Base ,QWidget *parent)
:IntegrationAlgoSimpleImagePanel(Base,/**/"Basic",/**/"ColorDifference",parent)
{
	SetMode(mtFrameDraw::fdPoly);
	UseSelectionDialog=true;
}

void	EasyColorDifferenceImagePanel::Prepare(void)
{
	IntegrationAlgoSimpleImagePanel::Prepare();
}

AlgorithmDrawAttr	*EasyColorDifferenceImagePanel::CreateDrawAttrPointer(void)
{	
	CmdColorDifferenceDrawInfo	Da(GetLayersBase());
	GUIFormBase	*GUIDim[1000];
	int N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint","EasyPropertyColorDifference",GUIDim,1000);
	for(int i=0;i<N;i++){
		EasyPropertyColorDifferenceForm	*f=dynamic_cast<EasyPropertyColorDifferenceForm *>(GUIDim[i]);
		if(N==1){
			f->TransmitDirectly(&Da);
		}
		else
		if(f!=NULL && f->SlaveNo==GetSlaveNo()){
			f->TransmitDirectly(&Da);
		}
	}

	ColorDifferenceDrawAttr	*mattr=new ColorDifferenceDrawAttr(GetLayersBase()
									,Qt::green	,128
									,Qt::red	,128
									,Qt::magenta,128);
	mattr->DType=DisplayImage::__Master;
	
	return mattr;
}

void	EasyColorDifferenceImagePanel::MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"EasyPropertyColorDifference" ,/**/"");
	CmdColorDifferenceDrawInfo	Da(GetLayersBase());
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
	}
	if(Da.LibID>=0){
		GUIFormBase *GUIRet[100];
		int	n;
		n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyColorDifference",GUIRet ,100);
		for(int i=0;i<n;i++){
			EasyPropertyColorDifferenceForm	*GUI=dynamic_cast<EasyPropertyColorDifferenceForm *>(GUIRet[i]);
			if(GUI!=NULL){
				if(GUI->SlaveNo==GetSlaveNo()){
					CmdColorDifferenceDrawInfo	Da(GetLayersBase());
					GUI->TransmitDirectly(&Da);

					QBuffer	Buff;
					Buff.open(QIODevice::WriteOnly);
					::Save(&Buff,Da.LibID);
					Data=Buff.buffer();
				}
			}
		}
	}
}
void	EasyColorDifferenceImagePanel::AddItemInAlgorithm(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &Area ,QByteArray &Data,QByteArray &SomethingData)
{
	QBuffer	Buff(&Data);
	Buff.open(QIODevice::ReadOnly);
	int		LibID;
	::Load(&Buff,LibID);

	CmdAddByteColorDifferenceItemPacket	Cmd(GetLayersBase());
	Cmd.Area		=Area;
	Cmd.LayerList	=LayerList;
	Cmd.LibID		=LibID;
	if(APage!=NULL)
		APage->TransmitDirectly(&Cmd);
}


//=======================================================================


