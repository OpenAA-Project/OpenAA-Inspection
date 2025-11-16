/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\AlgorithmCommon.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XAlgorithmDLL.h"
#include "XDataInLayer.h"
#include "XLanguageClass.h"
#include <QWidget>
#include "XResult.h"

extern	LangSolverNew	LangLibSolver;

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return NULL;
}

DEFFUNCEX	void	DLL_SetLanguageCommon(LanguagePackage &Pkg ,int LanguageCode)
{
	LangLibSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_ReleaseAlgorithmBase(AlgorithmBase *Point)
{
	delete	Point;
}
DEFFUNCEX	bool	DLL_ExecuteMoveItemsToDispatcherForLoadingParts(AlgorithmBase *base)
{
	base->MoveItemsToDispatcherForLoadingParts();
	return true;
}
DEFFUNCEX	bool	DLL_ExecuteCopyItemsFormDispatcherForParts(AlgorithmBase *base)
{
	base->CopyItemsFormDispatcherForParts();
	return true;
}
DEFFUNCEX	bool	DLL_ExecuteRemoveItemFormDispatcher(AlgorithmBase *base)
{
	base->RemoveItemFormDispatcher();
	return true;
}

DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEdit	(int ExeID ,AlgorithmBase *base ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	Res->Initial();
	const ExeResult	ret=base->ExecuteInitialAfterEdit	(ExeID,Res,EInfo);
	//Res->Release();
	return ret;
}
DEFFUNCEX	ExeResult	DLL_ExecuteStartByInspection(int ExeID ,AlgorithmBase *base ,ResultBaseForAlgorithmRoot *Res)
{
	return base->ExecuteStartByInspection	(ExeID,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecuteCaptured(int ExeID ,AlgorithmBase *base ,ResultBaseForAlgorithmRoot *Res,ListPhasePageLayerPack &CapturedList)
{
	return base->ExecuteCaptured(ExeID,Res,CapturedList);
}
DEFFUNCEX	ExeResult	DLL_ExecutePreAlignment		(int ExeID ,AlgorithmBase *base ,ResultBaseForAlgorithmRoot *Res)
{
	return base->ExecutePreAlignment	(ExeID,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecuteAlignment		(int ExeID ,AlgorithmBase *base ,ResultBaseForAlgorithmRoot *Res)
{
	return base->ExecuteAlignment	(ExeID,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecutePreProcessing	(int ExeID ,AlgorithmBase *base ,ResultBaseForAlgorithmRoot *Res)
{
	return base->ExecutePreProcessing	(ExeID,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecuteProcessing		(int ExeID ,AlgorithmBase *base ,ResultBaseForAlgorithmRoot *Res)
{
	return base->ExecuteProcessing	(ExeID,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingRevived(int ExeID ,AlgorithmBase *base ,ResultBaseForAlgorithmRoot *Res)
{
	return base->ExecuteProcessingRevived(ExeID,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecutePostProcessing	(int ExeID ,AlgorithmBase *base ,ResultBaseForAlgorithmRoot *Res)
{
	return base->ExecutePostProcessing	(ExeID,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecutePreScanning		(int ExeID ,AlgorithmBase *base ,ResultBaseForAlgorithmRoot *Res)
{
	return base->ExecutePreScanning	(ExeID,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecuteScanning			(int ExeID ,AlgorithmBase *base ,ResultBaseForAlgorithmRoot *Res)
{
	return base->ExecuteScanning	(ExeID,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecutePostScanning		(int ExeID ,AlgorithmBase *base ,ResultBaseForAlgorithmRoot *Res)
{
	return base->ExecutePostScanning	(ExeID,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecuteManageResult		(int ExeID ,AlgorithmBase *base ,ResultInspection *Res)
{
	return base->ExecuteManageResult	(ExeID,Res);
}

DEFFUNCEX	bool	DLL_DrawResultBase(int32 ShowFixedPhase,AlgorithmBase *InstBase ,ResultBaseForAlgorithmRoot *Res,QPainter &PntFromIData ,QImage *IData ,int MovX ,int MovY ,double ZoomRate,int localPage)
{
	return InstBase->DrawResultBase(ShowFixedPhase,Res,PntFromIData ,*IData ,MovX ,MovY ,ZoomRate,localPage);
}

DEFFUNCEX	void	DLL_MakeIndependentItems(int32 TargetPhase,int32 localPage ,bool SubResultMoving, int localX ,int localY,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	InstBase->MakeIndependentItems(TargetPhase,localPage ,SubResultMoving, localX ,localY,Data);
}

DEFFUNCEX	void	DLL_SetIndependentItemData(int32 Command
										,AlgorithmBase *InstBase ,int32 TargetPhase,int32 LocalPage,int32 Layer,int32 ItemID
										,AlgorithmItemRoot *Data
										,IntList &EdittedMemberID
										,QByteArray &Something
										,QByteArray &AckData)
{
	InstBase->SetIndependentItemData(Command
									,TargetPhase,LocalPage,Layer,ItemID
									,Data
									,EdittedMemberID
									,Something
									,AckData);
}

DEFFUNCEX	bool	DLL_ReleaseGeneralAlgorithmData(AlgorithmBase *InstBase ,int32 Command,void *data)
{
	return InstBase->GeneralDataRelease(Command,data);
}
DEFFUNCEX	void	*DLL_CreateGeneralAlgorithmData(AlgorithmBase *InstBase ,int32 Command,void *reqdata)
{
	return InstBase->GeneralDataCreate(Command,reqdata);
}
DEFFUNCEX	bool	DLL_LoadGeneralAlgorithmData(AlgorithmBase *InstBase ,QIODevice *f,int32 Command ,void *data)
{
	return InstBase->GeneralDataLoad(f,Command,data);
}
DEFFUNCEX	bool	DLL_SaveGeneralAlgorithmData(AlgorithmBase *InstBase ,QIODevice *f,int32 Command ,void *data)
{
	return InstBase->GeneralDataSave(f,Command,data);
}
DEFFUNCEX	bool	DLL_ReplyGeneralAlgorithmData(AlgorithmBase *InstBase ,int32 Command ,void *data)
{
	return InstBase->GeneralDataReply(Command,data);
}

DEFFUNCEX	bool	DLL_IsEdited(AlgorithmBase *InstBase)
{
	return InstBase->IsEdited();
}
DEFFUNCEX	bool	DLL_IsCalcDone(AlgorithmBase *InstBase)
{
	return InstBase->IsCalcDone();
}
DEFFUNCEX	void	DLL_SetEdited(AlgorithmBase *InstBase,bool edited)
{
	InstBase->SetEdited(edited);
}
DEFFUNCEX	void	DLL_SetCalcDone(AlgorithmBase *InstBase,bool calcdone)
{
	InstBase->SetCalcDone(calcdone);
}

DEFFUNCEX	bool	DLL_SaveCSVMasterReport(AlgorithmBase *InstBase, QStringListListCSV &CSVData)
{
	return InstBase->SaveCSVMasterReport(CSVData);
}

DEFFUNCEX	bool	DLL_GetNGTypeContainer(	 AlgorithmBase *ABase 
											,int LibID
											,LibNGTypeInAlgorithm &NGTypeContainer)
{
	ABase->GetNGTypeContainer(LibID	,NGTypeContainer);
	return true;
}
