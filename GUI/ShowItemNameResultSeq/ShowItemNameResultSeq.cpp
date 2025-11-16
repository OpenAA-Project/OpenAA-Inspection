/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowItemNameResultSeq\ShowItemNameResultSeq.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowItemNameResultSeq.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XDataAlgorithm.h"
#include "XResult.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"ItemNameResultSeq";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show item name and result, and output sequence");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowItemNameResultSeq(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"ItemDLLRoot";
	Data[0].Pointer				 =&((ShowItemNameResultSeq *)Instance)->ItemDLLRoot;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"ItemDLLName";
	Data[1].Pointer				 =&((ShowItemNameResultSeq *)Instance)->ItemDLLName;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"SeqNo";
	Data[2].Pointer				 =&((ShowItemNameResultSeq *)Instance)->SeqNo;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"ShowItemName";
	Data[3].Pointer				 =&((ShowItemNameResultSeq *)Instance)->ShowItemName;
	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowItemNameResultSeq.png")));
}

//DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
//{
//	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase();
//	A->TableName=/**/"MASTERDATA";
//	A->FieldName=/**/"MACOFFSET";
//	A->DefaultData.setValue((int)0);
//	Data.AppendList(A);
//}

//===================================================================================================

ShowItemNameResultSeq::ShowItemNameResultSeq(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent)
{
	ItemDLLRoot	=/**/"DLLRoot";
	ItemDLLName	=/**/"DLLName";
	ItemName	=/**/"ItemName";
	SeqNo		=-1;
	ShowItemName=true;
	Item		=NULL;
	ioItemValue	=NULL;
	ShowingCount=0;
	LastValue	=-1;
	LastResult	=NULL;
	
	GetParamGUI()->SetParam(&ItemName, /**/"ShowItemNameResultSeq",/**/"ItemName"		,/**/"Item name"		);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowItemNameResultSeq::~ShowItemNameResultSeq()
{
}

void	ShowItemNameResultSeq::ResizeAction()
{
	if(ShowItemName==true){
		LabelItemName.setGeometry(0,0,width()-40-2,height());
	}
	LabelResult.setGeometry(width()-40,0,40,height());
}

void	ShowItemNameResultSeq::Prepare(void)
{
	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioItemValue		=new SignalOperandInt(this,SeqNo	,/**/"ShowItemNameResultSeq:ioItemValue");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioItemValue,&Error)==false){
				ioItemValue->ShowErrorMessage(Error);
			}
			connect(ioItemValue,SIGNAL(loaded()),this,SLOT(SlotSeqLoaded()));
			connect(ioItemValue,SIGNAL(changed(int)),this,SLOT(SlotSeqChanged(int)));
			connect(this,SIGNAL(SignalShowValue(int)),this,SLOT(SlotShowValue(int)),Qt::QueuedConnection);
		}
	}
	if(ShowItemName==true){
		LabelItemName.setParent(this);
	}
	LabelResult.setParent(this);
}

void	ShowItemNameResultSeq::BuildForShow(void)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(ItemDLLRoot,ItemDLLName);
	if(ABase!=NULL){
		Item=ABase->SearchItemByName(ItemName);
		if(Item!=NULL){
			if(ShowItemName==true){
				LabelItemName.setText(Item->GetItemName());
			}
		}
	}
}

void	ShowItemNameResultSeq::SlotSeqLoaded()
{
	if(Item!=NULL){
		ResultInItemRoot	*R=Item->GetCurrentResult();
		if(R!=NULL){
			int	e=R->GetError();
			ioItemValue->Set(e);
			if(ShowingCount==0 && (LastValue!=e || LastResult!=R)){
				LastValue=e;
				LastResult=R;
				ShowingCount++;
				emit	SignalShowValue(e);
			}
		}
	}
}
void	ShowItemNameResultSeq::SlotShowValue(int d)
{
	LabelResult.setText(QString::number(d));
	ShowingCount--;
}

void	ShowItemNameResultSeq::SlotSeqChanged(int)
{
	if(Item!=NULL){
		ResultInItemRoot	*R=Item->GetCurrentResult();
		if(R!=NULL){
			int	e=R->GetError();
			e=ioItemValue->Get();
			if(ShowingCount==0 && LastValue!=e){
				ShowingCount++;
				emit	SignalShowValue(e);
			}
			LastValue=e;
		}
	}
}