/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyMeasureImagePanel\EasyMeasureImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QIcon>
#include <QPixmap>
#include <QToolBar>
#include <QBuffer>

#include "EasyMeasureImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "EasyPropertyMeasureForm.h"
#include "XIntegrationBase.h"
#include "CartonMenuForm.h"
#include "XMasking.h"
#include "XMeasureLineMove.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyMeasureImagePanel";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"EasyMeasureImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);
	Q_INIT_RESOURCE(IntegrationLib);

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
	EasyMeasureImagePanel	*B=new EasyMeasureImagePanel(Base,parent);
	//B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((EasyMeasureImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	//Data[N].Type				  =/**/"QString";
	//Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	//Data[N].Pointer			  =&((EasyMaskingImagePanel *)Instance)->ImageControlToolsName;
	//N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyMeasureImagePanel.png")));
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

EasyMeasureImagePanel::EasyMeasureImagePanel(LayersBase *Base ,QWidget *parent)
:IntegrationAlgoSimpleImagePanel(Base,/**/"Measure",/**/"MeasureLineMove",parent)
{
	ShowingItemID=-1;
	CurrentPointNo=0;
	SetMode(mtFrameDraw::fdPoly);
}
void	EasyMeasureImagePanel::Prepare(void)
{
	IntegrationAlgoSimpleImagePanel::Prepare();
}

AlgorithmDrawAttr	*EasyMeasureImagePanel::CreateDrawAttrPointer(void)
{
	MeasureLineMoveDrawAttr	*p=new MeasureLineMoveDrawAttr(
							 Qt::green		,128
							,Qt::magenta	,128
							,Qt::red		,128
							,Qt::cyan		
							,Qt::green);
	p->ShowingItemID	=ShowingItemID;
	return p;
}
	
void	EasyMeasureImagePanel::DrawImage(QImage &Image
							,double ZoomRate ,int MovX ,int MovY 
							,int Phase ,IntList &LayerList
							,QByteArray	&DrawAtterData
							,QString &AlgoDLLRoot ,QString &AlgoDLLName
							,bool tOnSelection
							,bool tOnMoving
							,int tSelectionDx,int tSelectionDy)
{
	IntegrationAlgoSimpleImagePanel::DrawImage(Image 
							,ZoomRate ,MovX ,MovY 
							,Phase ,LayerList
							,DrawAtterData
							,AlgoDLLRoot ,AlgoDLLName
							,tOnSelection
							,tOnMoving
							,tSelectionDx,tSelectionDy);

	MeasureLineMoveDrawAttr	*Attr=(MeasureLineMoveDrawAttr *)CreateDrawAttrPointer();
	if(Attr!=NULL){
		QBuffer	Buff(&DrawAtterData);
		Buff.open(QIODevice::ReadOnly);
		Attr->LoadAttr(&Buff);
	}
}

void	EasyMeasureImagePanel::SlotJustMouseLPress  (int UniversalDx,int UniversalDy)
{
}
void	EasyMeasureImagePanel::SlotJustMouseLRelease(int UniversalDx,int UniversalDy)
{
	CartonMenuForm	*CartonMenuProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(CartonMenuProp!=NULL){
		EasyPropertyMeasureForm	*EasyPropertyForm=GetPropertyForm();
		if(EasyPropertyForm!=NULL){
			if(CurrentPointNo==0 && EasyPropertyForm->DrawMode==0){
				GlobalX1=UniversalDx;
				GlobalY1=UniversalDy;
				CurrentPointNo=1;
			}
			else
			if(CurrentPointNo==1 && EasyPropertyForm->DrawMode==0){
				GlobalX2=UniversalDx;
				GlobalY2=UniversalDy;
				CurrentPointNo=0;

				CmdAddDistance	Cmd(GetLayersBase());
				Cmd.X1			=GlobalX1;
				Cmd.Y1			=GlobalY1;
				Cmd.X2			=GlobalX2;
				Cmd.Y2			=GlobalY2;
				Cmd.LineLength	=30;
				Cmd.LineLibID1	=CartonMenuProp->Param.BladeLineLib;
				Cmd.LineLibID2	=CartonMenuProp->Param.BladeLineLib;
				Cmd.DistanceLibID=CartonMenuProp->Param.BladeDistanceLib;
				EasyPropertyForm->TransmitDirectly(&Cmd);
				ResetDraw();
				SetCancelDraw();
			}
			else if(EasyPropertyForm->DrawMode==1 || EasyPropertyForm->DrawMode==2){
				CmdSetEndPointDistance	Cmd(GetLayersBase());
				Cmd.GlobalX		=UniversalDx;
				Cmd.GlobalY		=UniversalDy;
				EasyPropertyForm->TransmitDirectly(&Cmd);
				ResetDraw();
				SetCancelDraw();
			}
		}
	}
}

EasyPropertyMeasureForm	*EasyMeasureImagePanel::GetPropertyForm(void)
{
	GUIFormBase *GUIFormRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyMeasure" ,GUIFormRet,100);
	EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(ThisM==NULL)
		return NULL;
	int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
	EasyPropertyMeasureForm	*AccessForm=NULL;
	for(int i=0;i<n;i++){
		if(((EasyPropertyMeasureForm *)GUIFormRet[i])->SlaveNo==SlaveNo){
			AccessForm=((EasyPropertyMeasureForm *)GUIFormRet[i]);
			break;
		}
	}
	return AccessForm;
}

void	EasyMeasureImagePanel::MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)
{
	//CartonMenuForm	*GMenu=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	//if(GMenu!=NULL){
	//	EasyPropertyMeasureForm	*GProp=GetPropertyForm();
	//	CmdReqDentMeasureData	Da(GetLayersBase());
	//	if(GProp!=NULL){
	//		GProp->TransmitDirectly(&Da);
	//
	//		QBuffer	Buff;
	//		Buff.open(QIODevice::WriteOnly);
	//		::Save(&Buff,Da.ManualCreateBlade);
	//		int	SlaveNo=GetSlaveNo();
	//
	//		Data=Buff.buffer();
	//	}
	//}
}

