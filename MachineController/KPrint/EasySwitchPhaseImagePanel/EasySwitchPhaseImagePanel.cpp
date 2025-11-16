/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasySwitchPhaseImagePanel\EasySwitchPhaseImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EasySwitchPhaseImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XSwitchPhase.h"
#include "CartonMenuForm.h"
#include <QColor>

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasySwitchPhaseImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"EasySwitchPhaseImagePanel");
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
	EasySwitchPhaseImagePanel	*B=new EasySwitchPhaseImagePanel(Base,parent);
	//B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((EasySwitchPhaseImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	//Data[N].Type				  =/**/"QString";
	//Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	//Data[N].Pointer			  =&((EasySwitchPhaseImagePanel *)Instance)->ImageControlToolsName;
	//N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasySwitchPhaseImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"SwitchPhase"));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

EasySwitchPhaseImagePanel::EasySwitchPhaseImagePanel(LayersBase *Base ,QWidget *parent)
:IntegrationAlgoSimpleImagePanel(Base,/**/"Basic",/**/"SwitchPhase",parent)
{
	SetMode(mtFrameDraw::fdPoly);
}

void	EasySwitchPhaseImagePanel::Prepare(void)
{
	IntegrationAlgoSimpleImagePanel::Prepare();
}

AlgorithmDrawAttr	*EasySwitchPhaseImagePanel::CreateDrawAttrPointer(void)
{
	SwitchPhaseDrawAttr	*mattr=new SwitchPhaseDrawAttr(
									 Qt::green	,128
									,Qt::red	,128
									,Qt::magenta,128
									,Qt::cyan
									,Qt::gray);

	return mattr;
}

void	EasySwitchPhaseImagePanel::MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)
{
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		::Save(&Buff,GProp->Param.SearchDotForPhase);
		Data=Buff.buffer();
	}
}
void	EasySwitchPhaseImagePanel::AddItemInAlgorithm(int SlaveNo
													,AlgorithmInPageRoot *APage 
													,IntList &LayerList 
													,FlexArea &Area 
													,QByteArray &Data
													,QByteArray &SomethingData)
{
	QBuffer	Buff(&Data);
	Buff.open(QIODevice::ReadOnly);
	int32	SearchDotForPhase;
	::Load(&Buff,SearchDotForPhase);

	SwitchPhaseBase	*ABase=(SwitchPhaseBase *)APage->GetParentBase();
	int	Page=APage->GetPage();
	int	SourcePhase=APage->GetPhaseCode();

	if(SourcePhase==0 && ABase->SamePositionAfter2ndPhase==true){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*APhase=ABase->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=APhase->GetPageData(Page);
			
			AddSwitchPhaseAreaPacket	Cmd(GetLayersBase());
			Cmd.Area=Area;
			Cmd.SearchDot=SearchDotForPhase		;

			PageDataInOnePhase	*Src=GetLayersBase()->GetPageDataPhase(phase);
			PageDataInOnePhase	*Dst=GetLayersBase()->GetPageDataPhase(SourcePhase);
			DataInPage	*Sp=Src->GetPageData(Page);
			DataInPage	*Dp=Dst->GetPageData(Page);
			for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
				DataInLayer	*SL=Sp->GetLayerData(Layer);
				DataInLayer	*DL=Dp->GetLayerData(Layer);
				DL->GetTargetBuff()=SL->GetMasterBuff();
			}
			GetLayersBase()->SetCurrentPhase(SourcePhase);
			int	LastCurrentCalcPoint=GetLayersBase()->GetCurrentCalcPoint();
			GetLayersBase()->SetProcessDone(false);
			GetLayersBase()->SetCurrentCalcPoint(LastCurrentCalcPoint);
			GetLayersBase()->ExecuteStartByInspection	(false);

			int	Index=GetLayersBase()->GetIndexInCurrentStateExecuter(DataInExecuter::FinExecuteStartByInspection);
			GetLayersBase()->SetProcessDone(false);
			GetLayersBase()->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecuteStartByInspection);
			GetLayersBase()->ExecutePreAlignment		(false);

			GetLayersBase()->SetProcessDone(false);
			GetLayersBase()->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecutePreAlignment);
			GetLayersBase()->ExecuteAlignment			(false);

			int	Cx,Cy;
			Area.GetCenter(Cx,Cy);

			AlignmentPacket2D	V;
			V.PosXOnTarget=Cx;
			V.PosYOnTarget=Cy;
			V.ShiftX=0;
			V.ShiftY=0;

			if(Ap!=NULL){
				Ap->GetAlignmentForProcessing(V);
				Cmd.Area.MoveToNoClip(V.ShiftX,V.ShiftY);
				Ap->TransmitDirectly(&Cmd);
			}
		}
	}
	else{
		AlgorithmInPageInOnePhase	*APhase=ABase->GetPageDataPhase(SourcePhase);
		AlgorithmInPageRoot	*Ap=APhase->GetPageData(Page);
		
		AddSwitchPhaseAreaPacket	Cmd(GetLayersBase());
		Cmd.Area=Area;
		Cmd.SearchDot=SearchDotForPhase		;

		PageDataInOnePhase	*Src=GetLayersBase()->GetPageDataPhase(0);
		PageDataInOnePhase	*Dst=GetLayersBase()->GetPageDataPhase(SourcePhase);
		DataInPage	*Sp=Src->GetPageData(Page);
		DataInPage	*Dp=Dst->GetPageData(Page);
		for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
			DataInLayer	*SL=Sp->GetLayerData(Layer);
			DataInLayer	*DL=Dp->GetLayerData(Layer);
			DL->GetTargetBuff()=SL->GetMasterBuff();
		}
		GetLayersBase()->SetCurrentPhase(SourcePhase);
		int	LastCurrentCalcPoint=GetLayersBase()->GetCurrentCalcPoint();
		GetLayersBase()->SetProcessDone(false);
		GetLayersBase()->SetCurrentCalcPoint(LastCurrentCalcPoint);
		GetLayersBase()->ExecuteStartByInspection	(false);

		int	Index=GetLayersBase()->GetIndexInCurrentStateExecuter(DataInExecuter::FinExecuteStartByInspection);
		GetLayersBase()->SetProcessDone(false);
		GetLayersBase()->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecuteStartByInspection);
		GetLayersBase()->ExecutePreAlignment		(false);

		GetLayersBase()->SetProcessDone(false);
		GetLayersBase()->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecutePreAlignment);
		GetLayersBase()->ExecuteAlignment			(false);

		int	Cx,Cy;
		Area.GetCenter(Cx,Cy);

		AlignmentPacket2D	V;
		V.PosXOnTarget=Cx;
		V.PosYOnTarget=Cy;
		V.ShiftX=0;
		V.ShiftY=0;

		if(Ap!=NULL){
			Ap->GetAlignmentForProcessing(V);
			Cmd.Area.MoveToNoClip(V.ShiftX,V.ShiftY);
			Ap->TransmitDirectly(&Cmd);
		}
	}
}
void	EasySwitchPhaseImagePanel::DelSelectedItemsInAlgorithm	(int SlaveNo
																,AlgorithmInPageRoot *APage 
																,IntList &LayerList
																,QByteArray &SomethingData)
{
	int	Page=APage->GetPage();
	AlgorithmBase	*ABase=APage->GetParentBase();
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*APhase=ABase->GetPageDataPhase(phase);
		AlgorithmInPageRoot	*Ap=APhase->GetPageData(Page);		
		Ap->DeleteSelectedItems(LayerList);
	}
}
void	EasySwitchPhaseImagePanel::SelectItem(int Phase
											,IntList &LayerList
											,FlexArea &Area
											,SelectedItemsInfoContainer &RetSelectedContainer
											,QByteArray &SomethingData)
{
	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoDLLRoot ,AlgoDLLName);
		if(Ab!=NULL){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
				if(Ah!=NULL){
					IntList	PageList;
					GetLayersBase()->GetLocalPageFromArea(Area,PageList);
					for(IntClass *v=PageList.GetFirst();v!=NULL;v=v->GetNext()){
						int	Page=v->GetValue();
						DataInPage	*pdata=GetLayersBase()->GetPageData(Page);
						AlgorithmInPageRoot	*Ap=Ah->GetPageData(Page);
						if(Ap!=NULL && pdata!=NULL){
							FlexArea	A=Area;
							pdata->ClipMoveAreaFromGlobal(A);
							if(A.GetPatternByte()>0){
								Ap->SelectItems(A ,LayerList,false);
							}
						}
					}
				}
			}
		}
	}
}

//=======================================================================


