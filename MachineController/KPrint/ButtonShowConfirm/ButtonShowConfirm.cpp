#include "ButtonShowConfirmResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonShowConfirm\ButtonShowConfirm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonShowConfirm.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "ConfirmForm.h"
#include "XConfirmPacket.h"

#include "XPropPacketAlignment.h"
#include "XPropPacketBCRInspection.h"
#include "XPropPacketColorDifference.h"
#include "XPropPacketDotColorMatching.h"
#include "XPropPacketMeasureLineMove.h"

//extern	LangSolverNew	LangCGSolver;

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"ButtonShowConfirm";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to show confirm debug");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)	=new IntegrationReqConfirmPanelImage		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckConfirmPanelImage		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationSetSelectedArea				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationSetActivateItem				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqThresholdLibID			(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckThresholdLibID			(Base,sRoot,sName,-1);
	(*Base)	=new GUICmdReqThresholdLibID				(Base,sRoot,sName,-1);
	(*Base)	=new GUICmdAckThresholdLibID				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqSelectItems				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqSelectItems				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqSelectItemsByGroupID		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckSelectItemsByGroupID		(Base,sRoot,sName,-1);
	(*Base)	=new GUICmdReqSelectItems					(Base,sRoot,sName,-1);
	(*Base)	=new GUICmdAckSelectItems					(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqItemThresholdData		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckItemThresholdData		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationSetItemThresholdData		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationSetSelectItems				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationClearSelectItems			(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqCurrentResult			(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckCurrentResult			(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqCurrentProcessTime		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckCurrentProcessTime		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqConfirmItemInfo			(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckConfirmItemInfo			(Base,sRoot,sName,-1);

	(*Base)	=new IntegrationReqAlignmentAreaInfo		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckAlignmentAreaInfo		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqAlignmentMarkInfo		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckAlignmentMarkInfo		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqAlignmentPointResult		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckAlignmentPointResult		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqAlignmentItem			(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckAlignmentItem			(Base,sRoot,sName,-1);

	(*Base)	=new IntegrationReqDotColorMatchingTryResult(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckDotColorMatchingTryResult(Base,sRoot,sName,-1);

	(*Base)	=new IntegrationReqMeasureLineMoveSelectItems		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckMeasureLineMoveSelectItems		(Base,sRoot,sName,-1);
	(*Base)	=new GUICmdReqMeasureLineMoveSelectItems			(Base,sRoot,sName,-1);
	(*Base)	=new GUICmdAckMeasureLineMoveSelectItems			(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqMeasureLineMoveItemThresholdData	(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckMeasureLineMoveItemThresholdData	(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationSetMeasureLineMoveItemThresholdData	(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqMeasureLineMoveTryResult			(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckMeasureLineMoveTryResult			(Base,sRoot,sName,-1);

	(*Base)	=new IntegrationReqColorDifferenceItemThresholdData	(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckColorDifferenceItemThresholdData	(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationSetColorDifferenceItemThresholdData	(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqColorDifferenceTryResult			(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckColorDifferenceTryResult			(Base,sRoot,sName,-1);

	(*Base)	=new IntegrationReqBCodeItemListInfo		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckBCodeItemListInfo		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqBCRInspectionTryResult	(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckBCRInspectionTryResult	(Base,sRoot,sName,-1);

	(*Base)	=new IntegrationCmdReqConfirmItemList		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationCmdAckConfirmItemList		(Base,sRoot,sName,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonShowConfirm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				  =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"SlaveNo";
	Data[0].Pointer			  =&((ButtonShowConfirm *)Instance)->SlaveNo;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"Msg";
	Data[1].Pointer				 =&((ButtonShowConfirm *)Instance)->Msg;
	Data[1].Translatable		=true;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"CharColor";
	Data[2].Pointer				 =&((ButtonShowConfirm *)Instance)->CharColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"BackColor";
	Data[3].Pointer				 =&((ButtonShowConfirm *)Instance)->BackColor;
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"CFont";
	Data[4].Pointer				 =&((ButtonShowConfirm *)Instance)->CFont;
	Data[5].Type				  =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"ImageBankListCount";
	Data[5].Pointer				 =&((ButtonShowConfirm *)Instance)->ImageBankListCount;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonShowConfirm.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic"	,/**/"DotColorMatching"));
	List.AppendList(new RootNameList(/**/"Basic"	,/**/"AlignmentLarge"));
	List.AppendList(new RootNameList(/**/"Measure"	,/**/"MeasureLineMove"));
	List.AppendList(new RootNameList(/**/"Basic"	,/**/"ColorDifference"));
	List.AppendList(new RootNameList(/**/"Basic"	,/**/"BCRInspection"));
}

DEFFUNCEX	void	DLL_AssociateGUI(RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Integration",/**/"ImageBank"));
}

//=======================================================================

ButtonShowConfirm::ButtonShowConfirm(LayersBase *Base ,QWidget *parent) :
	GUIFormBase(Base,parent)
{
	SlaveNo=0;
	TargetImageWithNGBuff	=NULL;
	TargetImageWithNGXLen	=0;
	TargetImageWithNGYLen	=0;
	ImageBankListCount		=20;
	Window					=NULL;

	Button.setParent(this);
	Button.setObjectName(/**/"ButtonShowConfirmBtn");
	Button.move(0,0);

	Msg=/**/"Confirm";
	resize(80,25);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
}

ButtonShowConfirm::~ButtonShowConfirm()
{
	Window->deleteLater();

	if(TargetImageWithNGBuff!=NULL){
		delete	[]TargetImageWithNGBuff;
	}
	TargetImageWithNGBuff	=NULL;
	TargetImageWithNGXLen	=0;
	TargetImageWithNGYLen	=0;
}

void	ButtonShowConfirm::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonShowConfirm::ReadyParam(void)
{
}

void	ButtonShowConfirm::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonShowConfirm::SlotClicked (bool checked)
{
	if(Window==NULL){
		Window=new ConfirmForm(GetLayersBase(),this);
	}
	Window->ClearRegisterComponent();
	Window->ShowItemList();
	Window->show();
	Window->on_toolButtonImageBankUpdate_clicked();
	Window->raise();
}

void	ButtonShowConfirm::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	ButtonShowConfirm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	LoadMasterSpecifiedBroadcaster	*LVar=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
	if(LVar!=NULL){
		if(Window!=NULL){
			Window->UpdateAgain();
			return;
		}
	}
}
