/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyBCodeImagePanel\EasyBCodeImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EasyBCodeImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XBCRInspection.h"
#include <QColor>
#include "EasyPropertyBCodeForm.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyBCodeImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"EasyBCodeImagePanel");
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
	EasyBCodeImagePanel	*B=new EasyBCodeImagePanel(Base,parent);
	//B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((EasyBCodeImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	//Data[N].Type				  =/**/"QString";
	//Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	//Data[N].Pointer			  =&((EasyBCodeImagePanel *)Instance)->ImageControlToolsName;
	//N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyBCodeImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"BCRInspection"));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

EasyBCodeImagePanel::EasyBCodeImagePanel(LayersBase *Base ,QWidget *parent)
:IntegrationAlgoSimpleImagePanel(Base,/**/"Basic",/**/"BCRInspection",parent)
{
	SetMode(mtFrameDraw::fdPoly);
	UseSelectionDialog=true;
}

void	EasyBCodeImagePanel::Prepare(void)
{
	IntegrationAlgoSimpleImagePanel::Prepare();
}

AlgorithmDrawAttr	*EasyBCodeImagePanel::CreateDrawAttrPointer(void)
{	
	//GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"EasyPropertyBCode" ,/**/"");
	//CmdColorDifferenceDrawInfo	Da(GetLayersBase());
	//if(GProp!=NULL){
	//	GProp->TransmitDirectly(&Da);
	//}

	BCRInspectionDrawAttr	*mattr=new BCRInspectionDrawAttr(
									 Qt::green	,128
									,Qt::red	,128
									,Qt::magenta,128
									,Qt::darkGreen
									,Qt::darkRed);

	mattr->DType					=DisplayImage::__Master;
	
	//BCRInspectionBase	*ABase=(BCRInspectionBase *)GetAlgorithmBase();

	return mattr;
}

void	EasyBCodeImagePanel::DrawEndAfterOperationAddItem(FlexArea &ResultArea,QByteArray &SomethingData)
{
	IntegrationAlgoSimpleImagePanel::DrawEndAfterOperationAddItem(ResultArea,SomethingData);
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyBCode",GUIRet ,100);
	for(int i=0;i<n;i++){
		EasyPropertyBCodeForm	*GUI=dynamic_cast<EasyPropertyBCodeForm *>(GUIRet[i]);
		if(GUI!=NULL){
			if(GUI->SlaveNo==GetSlaveNo()){
				CmdShowBCodeGrid	Da(GetLayersBase());
				GUI->TransmitDirectly(&Da);
			}
		}
	}
}

void	EasyBCodeImagePanel::MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)
{
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyBCode",GUIRet ,100);
	for(int i=0;i<n;i++){
		EasyPropertyBCodeForm	*GUI=dynamic_cast<EasyPropertyBCodeForm *>(GUIRet[i]);
		if(GUI!=NULL){
			if(GUI->SlaveNo==GetSlaveNo()){
				CmdReqBCodeInfo	Da(GetLayersBase());
				GUI->TransmitDirectly(&Da);

				QBuffer	Buff;
				Buff.open(QIODevice::WriteOnly);
				::Save(&Buff,(int)Da.BCodeType);
				::Save(&Buff,(int)Da.QuilityGrade);
				Da.GradeList.Save(&Buff);
				Data=Buff.buffer();
			}
		}
	}
}

void	EasyBCodeImagePanel::AddItemInAlgorithm(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &Area ,QByteArray &Data,QByteArray &SomethingData)
{
	QBuffer	Buff(&Data);
	Buff.open(QIODevice::ReadOnly);
	int	iBCodeType;
	::Load(&Buff,iBCodeType);
	CmdReqBCodeInfo::_BCodeType		BCodeType=(CmdReqBCodeInfo::_BCodeType)iBCodeType;

	double	QuilityGrade;
	::Load(&Buff,QuilityGrade);
	BCRGradeListContainer	GradeList;
	GradeList.Load(&Buff);

	AddBCRInspectionAreaPacket	Cmd(GetLayersBase());
	Cmd.Area		=Area;
	Cmd.CheckType	=(BCodeType==CmdReqBCodeInfo::_ReadBCode)?0:1;
	Cmd.QuilityGrade	=QuilityGrade;
	Cmd.GradeList		=GradeList;

	if(APage!=NULL)
		APage->TransmitDirectly(&Cmd);
}

//=======================================================================


