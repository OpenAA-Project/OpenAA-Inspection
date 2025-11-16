/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAlgorithmBase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QSqlRecord>
#include <QSqlQuery>
#include "XAlgorithmInterfaceDLL.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XDLLType.h"
#include "XDatabase.h"
#include "XAlgorithmDLL.h"
#include "XDatabaseLoader.h"
#include "XErrorCode.h"
#include "XGUIFormBase.h"
#include "XFileRegistry.h"
#include "XMapBuffer.h"
#include "XDataComponent.h"
#include "XGUIComponent.h"

AlgorithmDLLList::AlgorithmDLLList(LayersBase *Base)
:ServiceForLayers(Base)
,Parent(NULL)
{
	DLL_GetDLLType				=NULL;
	DLL_GetOrganization			=NULL;
	DLL_GetName					=NULL;
	DLL_GetVersion				=NULL;

	DLL_InitialAlloc			=NULL;
	DLL_Close					=NULL;
	DLL_ReleaseAlgorithmBase	=NULL;
	DLL_CheckCopyright			=NULL;
	DLL_AssociateComponent		=NULL;

	DLL_NewLibrary				=NULL;
	DLL_GetPriority				=NULL;
	DLL_GetExplain				=NULL;
	DLL_SetLanguage				=NULL;
	DLL_SetLanguageCommon		=NULL;
	DLL_GetBlobName				=NULL;
	DLL_GetAlgorithmType		=NULL;

	DLL_ExecuteMoveItemsToDispatcherForLoadingParts	=NULL;
	DLL_ExecuteCopyItemsFormDispatcherForParts		=NULL;
	DLL_ExecuteRemoveItemFormDispatcher				=NULL;

	DLL_ExecuteInitialAfterEdit	=NULL;
	DLL_ExecuteStartByInspection=NULL;
	DLL_ExecuteCaptured			=NULL;
	DLL_ExecutePreAlignment		=NULL;
	DLL_ExecuteAlignment		=NULL;
	DLL_ExecutePreProcessing	=NULL;
	DLL_ExecuteProcessing		=NULL;
	DLL_ExecuteProcessingRevived=NULL;
	DLL_ExecutePostProcessing	=NULL;
	DLL_ExecutePreScanning		=NULL;
	DLL_ExecuteScanning			=NULL;
	DLL_ExecutePostScanning		=NULL;
	DLL_ExecuteManageResult		=NULL;
	DLL_ExecuteMatch			=NULL;

	DLL_DrawResultBase			=NULL;
	DLL_DrawResultDetail		=NULL;
	DLL_ShowAndSetItems			=NULL;
	DLL_MakeIndependentItems	=NULL;
	DLL_SetIndependentItemData	=NULL;
	DLL_ChangeItemsAttr			=NULL;
	DLL_SaveItem				=NULL;
	DLL_LoadItem				=NULL;
	DLL_CreateResultBaseForAlgorithm=NULL;

	DLL_LoadAddedResultData		=NULL;
	DLL_SaveAddedResultData		=NULL;
	DLL_RemoveAddedResultData	=NULL;
	DLL_GetAlignmentPointer		=NULL;
	DLL_GetAlignmentForProcessing=NULL;

	DLL_ReleaseGeneralAlgorithmData	=NULL;
	DLL_CreateGeneralAlgorithmData	=NULL;
	DLL_LoadGeneralAlgorithmData	=NULL;
	DLL_SaveGeneralAlgorithmData	=NULL;
	DLL_ReplyGeneralAlgorithmData	=NULL;

	DLL_ResultItemToString			=NULL;
	DLL_BindSpecialResult			=NULL;

	DLL_IsEdited					=NULL;
	DLL_IsCalcDone					=NULL;
	DLL_SetEdited					=NULL;
	DLL_SetCalcDone					=NULL;

	DLL_LocalPos2Name				=NULL;

	DLL_SaveCSVMasterReport			=NULL;
	DLL_GetNGTypeContainer			=NULL;

	DLL_ReceivePacketDirectComm		=NULL;
	DLL_RegistMacroFunction			=NULL;

	PriorityInitialAfterEdit	=100;
	PriorityAutoGeneration		=100;
	PriorityStartByInspection	=100;
	PriorityPreAlignment		=100;
	PriorityAlignment			=100;
	PriorityPreProcessing		=100;
	PriorityProcessing			=100;
	PriorityProcessingRevived	=100;
	PriorityPostProcessing		=100;
	PriorityPreScanning			=100;
	PriorityScanning			=100;
	PriorityPostScanning		=100;
	PriorityManageResult		=100;
}

AlgorithmDLLList::AlgorithmDLLList(const AlgorithmDLLList *parent ,LayersBase *Base)
:ServiceForLayers(Base)
,Parent(parent)
{
	FileName										=Parent->FileName										;
	DLLRoot											=Parent->DLLRoot										;
	DLLName											=Parent->DLLName										;

	DLL_GetDLLType									=Parent->DLL_GetDLLType									;
	DLL_GetOrganization								=Parent->DLL_GetOrganization							;
	DLL_GetName										=Parent->DLL_GetName									;
	DLL_GetVersion									=Parent->DLL_GetVersion									;
	DLL_InitialAlloc								=Parent->DLL_InitialAlloc								;
	DLL_Close										=Parent->DLL_Close										;
	DLL_ReleaseAlgorithmBase						=Parent->DLL_ReleaseAlgorithmBase						;
	DLL_AssociateComponent							=Parent->DLL_AssociateComponent							;
	DLL_CheckCopyright								=Parent->DLL_CheckCopyright								;
	DLL_NewLibrary									=Parent->DLL_NewLibrary									;
	DLL_GetPriority									=Parent->DLL_GetPriority								;
	DLL_GetExplain									=Parent->DLL_GetExplain									;
	DLL_SetLanguage									=Parent->DLL_SetLanguage								;
	DLL_SetLanguageCommon							=Parent->DLL_SetLanguageCommon							;
	DLL_GetBlobName									=Parent->DLL_GetBlobName								;
	DLL_GetAlgorithmType							=Parent->DLL_GetAlgorithmType							;
	DLL_ExecuteMoveItemsToDispatcherForLoadingParts	=Parent->DLL_ExecuteMoveItemsToDispatcherForLoadingParts;
	DLL_ExecuteCopyItemsFormDispatcherForParts		=Parent->DLL_ExecuteCopyItemsFormDispatcherForParts		;
	DLL_ExecuteRemoveItemFormDispatcher				=Parent->DLL_ExecuteRemoveItemFormDispatcher			;
	DLL_ExecuteInitialAfterEdit						=Parent->DLL_ExecuteInitialAfterEdit					;
	DLL_ExecuteStartByInspection					=Parent->DLL_ExecuteStartByInspection					;
	DLL_ExecuteCaptured								=Parent->DLL_ExecuteCaptured;
	DLL_ExecutePreAlignment							=Parent->DLL_ExecutePreAlignment						;
	DLL_ExecuteAlignment							=Parent->DLL_ExecuteAlignment							;
	DLL_ExecutePreProcessing						=Parent->DLL_ExecutePreProcessing						;
	DLL_ExecuteProcessing							=Parent->DLL_ExecuteProcessing							;
	DLL_ExecuteProcessingRevived					=Parent->DLL_ExecuteProcessingRevived					;
	DLL_ExecutePostProcessing						=Parent->DLL_ExecutePostProcessing						;
	DLL_ExecutePreScanning							=Parent->DLL_ExecutePreScanning							;
	DLL_ExecuteScanning								=Parent->DLL_ExecuteScanning							;
	DLL_ExecutePostScanning							=Parent->DLL_ExecutePostScanning						;
	DLL_ExecuteManageResult							=Parent->DLL_ExecuteManageResult						;
	DLL_ExecuteMatch								=Parent->DLL_ExecuteMatch								;
	DLL_DrawResultBase								=Parent->DLL_DrawResultBase								;
	DLL_DrawResultDetail							=Parent->DLL_DrawResultDetail							;
	DLL_ShowAndSetItems								=Parent->DLL_ShowAndSetItems							;
	DLL_MakeIndependentItems						=Parent->DLL_MakeIndependentItems						;
	DLL_SetIndependentItemData						=Parent->DLL_SetIndependentItemData						;
	DLL_ChangeItemsAttr								=Parent->DLL_ChangeItemsAttr							;
	DLL_SaveItem									=Parent->DLL_SaveItem									;
	DLL_LoadItem									=Parent->DLL_LoadItem									;
	DLL_CreateResultBaseForAlgorithm				=Parent->DLL_CreateResultBaseForAlgorithm				;
	DLL_LoadAddedResultData							=Parent->DLL_LoadAddedResultData						;
	DLL_SaveAddedResultData							=Parent->DLL_SaveAddedResultData						;
	DLL_RemoveAddedResultData						=Parent->DLL_RemoveAddedResultData						;
	DLL_GetAlignmentPointer							=Parent->DLL_GetAlignmentPointer						;
	DLL_GetAlignmentForProcessing					=Parent->DLL_GetAlignmentForProcessing					;
	DLL_ReleaseGeneralAlgorithmData					=Parent->DLL_ReleaseGeneralAlgorithmData				;
	DLL_CreateGeneralAlgorithmData					=Parent->DLL_CreateGeneralAlgorithmData					;
	DLL_LoadGeneralAlgorithmData					=Parent->DLL_LoadGeneralAlgorithmData					;
	DLL_SaveGeneralAlgorithmData					=Parent->DLL_SaveGeneralAlgorithmData					;
	DLL_ReplyGeneralAlgorithmData					=Parent->DLL_ReplyGeneralAlgorithmData					;
	DLL_ResultItemToString							=Parent->DLL_ResultItemToString							;
	DLL_BindSpecialResult							=Parent->DLL_BindSpecialResult							;
	DLL_IsEdited									=Parent->DLL_IsEdited									;
	DLL_IsCalcDone									=Parent->DLL_IsCalcDone									;
	DLL_SetEdited									=Parent->DLL_SetEdited									;
	DLL_SetCalcDone									=Parent->DLL_SetCalcDone								;
	DLL_LocalPos2Name								=Parent->DLL_LocalPos2Name								;
	DLL_SaveCSVMasterReport							=Parent->DLL_SaveCSVMasterReport						;
	DLL_GetNGTypeContainer							=Parent->DLL_GetNGTypeContainer							;
	DLL_ReceivePacketDirectComm						=Parent->DLL_ReceivePacketDirectComm					;
	DLL_RegistMacroFunction							=Parent->DLL_RegistMacroFunction						;

	PriorityInitialAfterEdit						=Parent->PriorityInitialAfterEdit	;
	PriorityAutoGeneration							=Parent->PriorityAutoGeneration		;
	PriorityStartByInspection						=Parent->PriorityStartByInspection	;
	PriorityPreAlignment							=Parent->PriorityPreAlignment		;
	PriorityAlignment								=Parent->PriorityAlignment			;
	PriorityPreProcessing							=Parent->PriorityPreProcessing		;
	PriorityProcessing								=Parent->PriorityProcessing			;
	PriorityProcessingRevived						=Parent->PriorityProcessingRevived	;
	PriorityPostProcessing							=Parent->PriorityPostProcessing		;
	PriorityPreScanning								=Parent->PriorityPreScanning		;
	PriorityScanning								=Parent->PriorityScanning			;
	PriorityPostScanning							=Parent->PriorityPostScanning		;
	PriorityManageResult							=Parent->PriorityManageResult		;
}

AlgorithmDLLList::~AlgorithmDLLList(void)
{
	if(ReEntrantDLL==true){
		return;
	}
	ReEntrantDLL=true;
	if(DLL_Close!=NULL){
		DLL_Close();
	}
	if(DllLib.isLoaded()==true){
		DllLib.unload();	//Error occurs in final DLL unload
	}
	ReEntrantDLL=false;
}

bool	AlgorithmDLLList::LoadDLL(const QString &filename)
{
	DllLib.setFileName(filename);
	if(DllLib.load()==false)
		return(false);
	DLL_GetDLLType				=(WORD (*)(void))DllLib.resolve("DLL_GetDLLType");
	DLL_GetOrganization			=(bool (*)(QString &))DllLib.resolve("DLL_GetOrganization");
	DLL_GetName					=(bool (*)(QString &Root ,QString &Name))DllLib.resolve("DLL_GetName");
	DLL_GetVersion				=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	if(DLLManager::LoadDLL(DllLib)==false){
		return false;
	}
	DLL_GetExplain				=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");
	DLL_SetLanguage				=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve("DLL_SetLanguage");
	DLL_SetLanguageCommon		=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve("DLL_SetLanguageCommon");
	DLL_CheckCopyright			=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");
	DLL_GetBlobName				=(const char *(*)(void))DllLib.resolve("DLL_GetBlobName");
	DLL_GetAlgorithmType		=(DWORD (*)(void))DllLib.resolve("DLL_GetAlgorithmType");

	DLL_InitialAlloc			=(AlgorithmBase *(*)(LayersBase *Base))DllLib.resolve("DLL_InitialAlloc");
	DLL_Close					=(void (*)(void))DllLib.resolve(/**/"DLL_Close");
	DLL_ReleaseAlgorithmBase	=(void (*)(AlgorithmBase *Point))DllLib.resolve("DLL_ReleaseAlgorithmBase");
	DLL_AssociateComponent		=(void (*)(LayersBase *Base,ComponentListContainer &List))DllLib.resolve(/**/"DLL_AssociateComponent");

	DLL_NewLibrary				=(AlgorithmLibraryContainer	*(*)(LayersBase *))DllLib.resolve("DLL_NewLibrary");
	DLL_GetPriority				=(int (*)(int AlgorithmBit_Type))DllLib.resolve("DLL_GetPriority");

	DLL_ExecuteMoveItemsToDispatcherForLoadingParts	=(bool (*)(AlgorithmBase *base))DllLib.resolve("DLL_ExecuteMoveItemsToDispatcherForLoadingParts");
	DLL_ExecuteCopyItemsFormDispatcherForParts		=(bool (*)(AlgorithmBase *base))DllLib.resolve("DLL_ExecuteCopyItemsFormDispatcherForParts");
	DLL_ExecuteRemoveItemFormDispatcher				=(bool (*)(AlgorithmBase *base))DllLib.resolve("DLL_ExecuteRemoveItemFormDispatcher");

	DLL_ExecuteInitialAfterEdit		=(ExeResult	(*)(int,AlgorithmBase *,ResultBaseForAlgorithmRoot * ,ExecuteInitialAfterEditInfo &EInfo))DllLib.resolve("DLL_ExecuteInitialAfterEdit");
	DLL_ExecuteStartByInspection	=(ExeResult	(*)(int,AlgorithmBase *,ResultBaseForAlgorithmRoot * ))DllLib.resolve("DLL_ExecuteStartByInspection");
	DLL_ExecuteCaptured				=(ExeResult	(*)(int,AlgorithmBase *,ResultBaseForAlgorithmRoot *  ,ListPhasePageLayerPack &))DllLib.resolve("DLL_ExecuteCaptured");
	DLL_ExecutePreAlignment			=(ExeResult	(*)(int,AlgorithmBase *,ResultBaseForAlgorithmRoot * ))DllLib.resolve("DLL_ExecutePreAlignment");
	DLL_ExecuteAlignment			=(ExeResult	(*)(int,AlgorithmBase *,ResultBaseForAlgorithmRoot * ))DllLib.resolve("DLL_ExecuteAlignment");
	DLL_ExecutePreProcessing		=(ExeResult	(*)(int,AlgorithmBase *,ResultBaseForAlgorithmRoot * ))DllLib.resolve("DLL_ExecutePreProcessing");
	DLL_ExecuteProcessing			=(ExeResult	(*)(int,AlgorithmBase *,ResultBaseForAlgorithmRoot * ))DllLib.resolve("DLL_ExecuteProcessing");
	DLL_ExecuteProcessingRevived	=(ExeResult	(*)(int,AlgorithmBase *,ResultBaseForAlgorithmRoot * ))DllLib.resolve("DLL_ExecuteProcessingRevived");
	DLL_ExecutePostProcessing		=(ExeResult	(*)(int,AlgorithmBase *,ResultBaseForAlgorithmRoot * ))DllLib.resolve("DLL_ExecutePostProcessing");
	DLL_ExecutePreScanning			=(ExeResult	(*)(int,AlgorithmBase *,ResultBaseForAlgorithmRoot * ))DllLib.resolve("DLL_ExecutePreScanning");
	DLL_ExecuteScanning				=(ExeResult	(*)(int,AlgorithmBase *,ResultBaseForAlgorithmRoot * ))DllLib.resolve("DLL_ExecuteScanning");
	DLL_ExecutePostScanning			=(ExeResult	(*)(int,AlgorithmBase *,ResultBaseForAlgorithmRoot * ))DllLib.resolve("DLL_ExecutePostScanning");
	DLL_ExecuteManageResult			=(ExeResult	(*)(int,AlgorithmBase *,ResultInspection *Res))DllLib.resolve("DLL_ExecuteManageResult");
	DLL_ExecuteMatch				=(ExeResult	(*)(int,AlgorithmBase *InstBase,ImagePointerContainer &TargetImages,int cx, int cy ,double &Result))DllLib.resolve("DLL_ExecuteMatch");

	DLL_DrawResultBase				=(bool	(*)(int32 ShowFixedPhase,AlgorithmBase *,ResultBaseForAlgorithmRoot * ,QPainter &,QImage *,int ,int ,double,int))DllLib.resolve("DLL_DrawResultBase");
	DLL_ShowAndSetItems				=(QWidget *(*)(QWidget *, int32 ,AlgorithmBase *,AlgorithmItemIndependentPack &,ShowAndSetItemsBaseClass *Something))DllLib.resolve("DLL_ShowAndSetItems");
	DLL_MakeIndependentItems		=(void	(*)(int32 ,int32 ,bool,int ,int ,AlgorithmBase *,AlgorithmItemIndependentPack &))DllLib.resolve("DLL_MakeIndependentItems");
	DLL_SetIndependentItemData		=(void	(*)(int32 
												,AlgorithmBase *,int32 ,int32 ,int32 ,int32
												,AlgorithmItemRoot *
												,IntList &
												,QByteArray &
												,QByteArray &))DllLib.resolve("DLL_SetIndependentItemData");
	DLL_DrawResultDetail			=(bool	(*)(AlgorithmItemRoot *Item ,ResultPosList *Pos
												,DetailResultInfoListContainer &RetList))DllLib.resolve("DLL_DrawResultDetail");

	DLL_ChangeItemsAttr				=(QWidget *(*)(QWidget *, int32 ,AlgorithmBase *,AlgorithmItemIndependentPack &))DllLib.resolve("DLL_ChangeItemsAttr");
	DLL_SaveItem					=(bool	(*)(QIODevice *f,AlgorithmItemRoot *item))DllLib.resolve("DLL_SaveItem");
	DLL_LoadItem					=(bool	(*)(QIODevice *f,AlgorithmItemRoot *item ,LayersBase *LBase))DllLib.resolve("DLL_LoadItem");
	DLL_CreateResultBaseForAlgorithm=(ResultBaseForAlgorithmRoot *(*)(LogicDLL *parent))DllLib.resolve("DLL_CreateResultBaseForAlgorithm");

	DLL_LoadAddedResultData		=(AddedDataClass *(*)(QIODevice *f ,int32 AddedDataType))DllLib.resolve("DLL_LoadAddedResultData");
	DLL_SaveAddedResultData		=(bool (*)(QIODevice *f ,AddedDataClass *d ,int32 AddedDataType))DllLib.resolve("DLL_SaveAddedResultData");
	DLL_RemoveAddedResultData	=(void (*)(AddedDataClass *d))DllLib.resolve("DLL_RemoveAddedResultData");

	DLL_GetAlignmentPointer			=(AlignmentPacketBase *(*)(AlgorithmBase *base ,int localPage, int localX ,int localY,AlgorithmItemRoot *Item ,bool FromGlobal))DllLib.resolve("DLL_GetAlignmentPointer");
	DLL_GetAlignmentForProcessing			=(void (*)(AlgorithmBase *base ,int localPage, AlignmentPacketBase &Packet))DllLib.resolve("DLL_GetAlignmentForProcessing");

	DLL_ReleaseGeneralAlgorithmData	=(bool	(*)(AlgorithmBase *InstBase ,int32 Command,void *data))DllLib.resolve("DLL_ReleaseGeneralAlgorithmData");
	DLL_CreateGeneralAlgorithmData	=(void *(*)(AlgorithmBase *InstBase ,int32 Command,void *reqData))DllLib.resolve("DLL_CreateGeneralAlgorithmData");
	DLL_LoadGeneralAlgorithmData	=(bool	(*)(AlgorithmBase *InstBase ,QIODevice *f,int32 Command ,void *data))DllLib.resolve("DLL_LoadGeneralAlgorithmData");
	DLL_SaveGeneralAlgorithmData	=(bool	(*)(AlgorithmBase *InstBase ,QIODevice *f,int32 Command ,void *data))DllLib.resolve("DLL_SaveGeneralAlgorithmData");
	DLL_ReplyGeneralAlgorithmData	=(bool	(*)(AlgorithmBase *InstBase ,int32 Command ,void *data))DllLib.resolve("DLL_ReplyGeneralAlgorithmData");

	DLL_ResultItemToString			=(bool (*)(ResultInItemRoot *ItemRes ,QString &RetStrBuf))DllLib.resolve("DLL_ResultItemToString");
	DLL_BindSpecialResult			=(bool (*)(ResultInItemRoot *ItemRes ,ErrorGroupPack &Dest))DllLib.resolve("DLL_BindSpecialResult");

	DLL_IsEdited					=(bool (*)(AlgorithmBase *InstBase))DllLib.resolve("DLL_IsEdited");
	DLL_IsCalcDone					=(bool (*)(AlgorithmBase *InstBase))DllLib.resolve("DLL_IsCalcDone");
	DLL_SetEdited					=(void (*)(AlgorithmBase *InstBase,bool edited))DllLib.resolve("DLL_SetEdited");
	DLL_SetCalcDone					=(void (*)(AlgorithmBase *InstBase,bool calcdone))DllLib.resolve("DLL_SetCalcDone");

	DLL_LocalPos2Name				=(bool (*)(AlgorithmBase *Base ,int Page ,int XLocalPos, int YLocalPos ,QString &Name))DllLib.resolve("DLL_LocalPos2Name");

	DLL_SaveCSVMasterReport			=(bool (*)(AlgorithmBase *InstBase, QStringListListCSV &CSVData))DllLib.resolve("DLL_SaveCSVMasterReport");
	DLL_GetNGTypeContainer			=(bool (*)(AlgorithmBase *ABase 
										 , int LibID
										 , LibNGTypeInAlgorithm &NGTypeContainer))DllLib.resolve("DLL_GetNGTypeContainer");
	DLL_ReceivePacketDirectComm		=(bool (*)(AlgorithmBase *ABase 
												,LayersBase *Base
												,int32 cmd 
												,int32 globalPage 
												,const char *EmitterRoot 
												,const char *EmitterName 
												,const char *ClassName
												,QBuffer &buff
												,int32 IDForUndo
												,ErrorCodeList &ErrorData))DllLib.resolve("DLL_ReceivePacketDirectCommAlgo");

	DLL_RegistMacroFunction		=(int32	(*)(ExportFuncForMacro Functions[],int MaxBuffer))DllLib.resolve("DLL_RegistMacroFunction");

	return(true);
}

void	AlgorithmDLLList::GetExportFunctions(QStringList &Str)
{
	if(DLL_GetOrganization!=NULL){
		Str.append("DLL_GetOrganization");
	}
	if(DLL_GetDLLType!=NULL){
		Str.append("DLL_GetDLLType");
	}
	if(DLL_GetName!=NULL){
		Str.append("DLL_GetName");
	}
	if(DLL_GetVersion!=NULL){
		Str.append("DLL_GetVersion");
	}
	if(DLL_GetExplain!=NULL){
		Str.append("DLL_GetExplain");
	}
	if(DLL_SetLanguage!=NULL){
		Str.append("DLL_SetLanguage");
	}
	if(DLL_SetLanguageCommon!=NULL){
		Str.append("DLL_SetLanguageCommon");
	}
	if(DLL_CheckCopyright!=NULL){
		Str.append("DLL_CheckCopyright");
	}
	if(DLL_GetBlobName!=NULL){
		Str.append("DLL_GetBlobName");
	}
	if(DLL_GetAlgorithmType!=NULL){
		Str.append("DLL_GetAlgorithmType");
	}
	if(DLL_InitialAlloc!=NULL){
		Str.append("DLL_InitialAlloc");
	}
	if(DLL_Close!=NULL){
		Str.append("DLL_Close");
	}
	if(DLL_ReleaseAlgorithmBase!=NULL){
		Str.append("DLL_ReleaseAlgorithmBase");
	}
	if(DLL_AssociateComponent!=NULL){
		Str.append("DLL_AssociateComponent");
	}

	if(DLL_NewLibrary!=NULL){
		Str.append("DLL_NewLibrary");
	}
	if(DLL_GetPriority!=NULL){
		Str.append("DLL_GetPriority");
	}

	if(DLL_ExecuteMoveItemsToDispatcherForLoadingParts!=NULL){
		Str.append("DLL_ExecuteMoveItemsToDispatcherForLoadingParts");
	}
	if(DLL_ExecuteCopyItemsFormDispatcherForParts!=NULL){
		Str.append("DLL_ExecuteCopyItemsFormDispatcherForParts");
	}
	if(DLL_ExecuteRemoveItemFormDispatcher!=NULL){
		Str.append("DLL_ExecuteRemoveItemFormDispatcher");
	}

	if(DLL_ExecuteInitialAfterEdit	!=NULL){
		Str.append("DLL_ExecuteInitialAfterEdit");
	}
	if(DLL_ExecuteStartByInspection!=NULL){
		Str.append("DLL_ExecuteStartByInspection");
	}
	if(DLL_ExecuteCaptured!=NULL){
		Str.append("DLL_ExecuteCaptured");
	}
	if(DLL_ExecutePreAlignment!=NULL){
		Str.append("DLL_ExecutePreAlignment");
	}
	if(DLL_ExecuteAlignment!=NULL){
		Str.append("DLL_ExecuteAlignment");
	}
	if(DLL_ExecutePreProcessing!=NULL){
		Str.append("DLL_ExecutePreProcessing");
	}
	if(DLL_ExecuteProcessing!=NULL){
		Str.append("DLL_ExecuteProcessing");
	}
	if(DLL_ExecuteProcessingRevived!=NULL){
		Str.append("DLL_ExecuteProcessingRevived");
	}
	if(DLL_ExecutePostProcessing!=NULL){
		Str.append("DLL_ExecutePostProcessing");
	}
	if(DLL_ExecutePreScanning!=NULL){
		Str.append("DLL_ExecutePreScanning");
	}
	if(DLL_ExecuteScanning!=NULL){
		Str.append("DLL_ExecuteScanning");
	}
	if(DLL_ExecutePostScanning!=NULL){
		Str.append("DLL_ExecutePostScanning");
	}
	if(DLL_ExecuteManageResult!=NULL){
		Str.append("DLL_ExecuteManageResult");
	}

	if(DLL_DrawResultBase!=NULL){
		Str.append("DLL_DrawResultBase");
	}
	if(DLL_ShowAndSetItems!=NULL){
		Str.append("DLL_ShowAndSetItems");
	}
	if(DLL_MakeIndependentItems!=NULL){
		Str.append("DLL_MakeIndependentItems");
	}
	if(DLL_SetIndependentItemData!=NULL){
		Str.append("DLL_SetIndependentItemData");
	}
	if(DLL_DrawResultDetail!=NULL){
		Str.append("DLL_DrawResultDetail");
	}
	if(DLL_ChangeItemsAttr!=NULL){
		Str.append("DLL_ChangeItemsAttr");
	}

	if(DLL_SaveItem!=NULL){
		Str.append("DLL_SaveItem");
	}
	if(DLL_LoadItem!=NULL){
		Str.append("DLL_LoadItem");
	}
	if(DLL_CreateResultBaseForAlgorithm!=NULL){
		Str.append("DLL_CreateResultBaseForAlgorithm");
	}

	if(DLL_LoadAddedResultData!=NULL){
		Str.append("DLL_LoadAddedResultData");
	}
	if(DLL_SaveAddedResultData!=NULL){
		Str.append("DLL_SaveAddedResultData");
	}
	if(DLL_RemoveAddedResultData!=NULL){
		Str.append("DLL_RemoveAddedResultData");
	}

	if(DLL_ReleaseGeneralAlgorithmData!=NULL){
		Str.append("DLL_ReleaseGeneralAlgorithmData");
	}
	if(DLL_CreateGeneralAlgorithmData!=NULL){
		Str.append("DLL_CreateGeneralAlgorithmData");
	}
	if(DLL_LoadGeneralAlgorithmData!=NULL){
		Str.append("DLL_LoadGeneralAlgorithmData");
	}
	if(DLL_SaveGeneralAlgorithmData!=NULL){
		Str.append("DLL_SaveGeneralAlgorithmData");
	}
	if(DLL_ReplyGeneralAlgorithmData!=NULL){
		Str.append("DLL_ReplyGeneralAlgorithmData");
	}

	if(DLL_ResultItemToString!=NULL){
		Str.append("DLL_ResultItemToString");
	}
	if(DLL_BindSpecialResult!=NULL){
		Str.append("DLL_BindSpecialResult");
	}

	if(DLL_GetAlignmentPointer!=NULL){
		Str.append("DLL_GetAlignmentPointer");
	}
	if(DLL_GetAlignmentForProcessing!=NULL){
		Str.append("DLL_GetAlignmentForProcessing");
	}

	if(DLL_IsEdited!=NULL){
		Str.append("DLL_IsEdited");
	}
	if(DLL_IsCalcDone!=NULL){
		Str.append("DLL_IsCalcDone");
	}
	if(DLL_SetEdited!=NULL){
		Str.append("DLL_SetEdited");
	}
	if(DLL_SetCalcDone!=NULL){
		Str.append("DLL_SetCalcDone");
	}

	if(DLL_LocalPos2Name!=NULL){
		Str.append("DLL_LocalPos2Name");
	}
	if(DLL_SaveCSVMasterReport!=NULL){
		Str.append("DLL_SaveCSVMasterReport");
	}
	if(DLL_GetNGTypeContainer!=NULL){
		Str.append("DLL_GetNGTypeContainer");
	}
	if(DLL_ReceivePacketDirectComm!=NULL){
		Str.append("DLL_ReceivePacketDirectComm");
	}
	if(DLL_RegistMacroFunction!=NULL){
		Str.append("DLL_RegistMacroFunction");
	}
	DLLManager::GetExportFunctions(Str);
}

bool			AlgorithmDLLList::GetOrganization(QString &str)
{
	if(DLL_GetOrganization!=NULL){
		InFunc=true;
		bool	ret=DLL_GetOrganization(str);
		InFunc=false;
		return ret;
	}
	return false;
}

bool	AlgorithmDLLList::IsAlgorithm(void)
{
	int	d=GetDLLType();
	if((d&DLLModeMask)==DLLAlgorithmMode){
		return(true);
	}
	return(false);
}

WORD			AlgorithmDLLList::GetDLLType(void)
{
	if(DLL_GetDLLType!=NULL){
		InFunc=true;
		WORD	ret=DLL_GetDLLType();
		InFunc=false;
		return ret;
	}
	return 0;
}
bool			AlgorithmDLLList::GetName(QString &Root ,QString &Name)
{
	if(DLL_GetName!=NULL){
		InFunc=true;
		bool	ret=DLL_GetName(Root ,Name);
		InFunc=false;
		return ret;
	}
	return false;
}
bool			AlgorithmDLLList::GetName(void)
{
	return GetName(DLLRoot,DLLName);
}

WORD			AlgorithmDLLList::GetVersion(void)
{
	if(DLL_GetVersion!=NULL){
		InFunc=true;
		WORD	ret=DLL_GetVersion();
		InFunc=false;
		return ret;
	}
	return 0;
}

const QString	AlgorithmDLLList::GetExplain(void)
{
	if(DLL_GetExplain!=NULL){
		InFunc=true;
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			const QString	ret=QString(c);	
			InFunc=false;
			return ret;
		}
		InFunc=false;
	}
	return /**/"";
}
bool			AlgorithmDLLList::SetLanguage(int LanguageCode)
{
	if(DLL_SetLanguage!=NULL){
		InFunc=true;
		DLL_SetLanguageCommon(GetLayersBase()->GetLanguagePackageData(),LanguageCode);
		DLL_SetLanguage(GetLayersBase()->GetLanguagePackageData(),LanguageCode);
		InFunc=false;
		return true;
	}
	return false;
}
bool			AlgorithmDLLList::CheckCopyright(QString &CopyrightString)
{
	if(DLL_CheckCopyright!=NULL){
		InFunc=true;
		bool	ret=DLL_CheckCopyright(CopyrightString);
		InFunc=false;
		return ret;
	}
	return false;
}
const char		*AlgorithmDLLList::GetBlobName(void)
{
	if(DLL_GetBlobName!=NULL){
		InFunc=true;
		const char	*ret=DLL_GetBlobName();
		InFunc=false;
		return ret;
	}
	return NULL;
}
DWORD			AlgorithmDLLList::GetAlgorithmType(void)
{
	if(DLL_GetAlgorithmType!=NULL){
		InFunc=true;
		DWORD	ret=DLL_GetAlgorithmType();
		InFunc=false;
		return ret;
	}
	return 0xFFFFFFFFU;
}
AlgorithmBase	*AlgorithmDLLList::InitialAlloc(LayersBase *Base)
{
	if(DLL_InitialAlloc!=NULL){
		InFunc=true;
		AlgorithmBase	*ret=DLL_InitialAlloc(Base);
		InFunc=false;
		return ret;
	}
	return NULL;
}
void	AlgorithmDLLList::ReleaseAlgorithmBase(AlgorithmBase *Point)
{
	if(DLL_ReleaseAlgorithmBase!=NULL){
		InFunc=true;
		DLL_ReleaseAlgorithmBase(Point);
		InFunc=false;
	}
}
void	AlgorithmDLLList::AssociateComponent(ComponentListContainer &List)
{
	if(DLL_AssociateComponent!=NULL){
		DLL_AssociateComponent(GetLayersBase(),List);
	}
}
AlgorithmLibraryContainer	*AlgorithmDLLList::NewLibrary(LayersBase *Base)
{
	if(DLL_NewLibrary!=NULL){
		InFunc=true;
		AlgorithmLibraryContainer	*ret=DLL_NewLibrary(Base);
		InFunc=false;
		return ret;
	}
	return NULL;
}
int				AlgorithmDLLList::GetPriority(int PriorityTypeBit_Type)
{
	if(DLL_GetPriority!=NULL){
		InFunc=true;
		int	ret=DLL_GetPriority(PriorityTypeBit_Type);
		InFunc=false;
		return ret;
	}
	return -1;
}

bool	AlgorithmDLLList::ExecuteMoveItemsToDispatcherForLoadingParts(AlgorithmBase *base)
{
	if(DLL_ExecuteMoveItemsToDispatcherForLoadingParts!=NULL){
		InFunc=true;
		bool	ret=DLL_ExecuteMoveItemsToDispatcherForLoadingParts(base);
		InFunc=false;
		return ret;
	}
	return false;
}
bool	AlgorithmDLLList::ExecuteCopyItemsFormDispatcherForParts(AlgorithmBase *base)
{
	if(DLL_ExecuteCopyItemsFormDispatcherForParts!=NULL){
		InFunc=true;
		bool	ret=DLL_ExecuteCopyItemsFormDispatcherForParts(base);
		InFunc=false;
		return ret;
	}
	return NULL;
}
bool	AlgorithmDLLList::ExecuteRemoveItemFormDispatcher(AlgorithmBase *base)
{
	if(DLL_ExecuteRemoveItemFormDispatcher!=NULL){
		InFunc=true;
		bool	ret=DLL_ExecuteRemoveItemFormDispatcher(base);
		InFunc=false;
		return ret;
	}
	return false;
}
bool	AlgorithmDLLList::MakeExecuteInitialAfterEditInfo	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	if(base!=NULL){
		return base->MakeExecuteInitialAfterEditInfo(ExeID ,Res,EInfo);
	}
	return false;
}
ExeResult	AlgorithmDLLList::ExecuteInitialAfterEditPrev(int ExeID 
														,AlgorithmBase *base
														,ResultBaseForAlgorithmRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	return base->ExecuteInitialAfterEditPrev(ExeID,Res,EInfo);
}
ExeResult	AlgorithmDLLList::ExecuteInitialAfterEdit	(int ExeID 
														,AlgorithmBase *base
														,ResultBaseForAlgorithmRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	if(DLL_ExecuteInitialAfterEdit!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecuteInitialAfterEdit	(ExeID,base,Res,EInfo);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}
ExeResult	AlgorithmDLLList::ExecuteInitialAfterEditPost(int ExeID 
														,AlgorithmBase *base
														,ResultBaseForAlgorithmRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	return base->ExecuteInitialAfterEditPost(ExeID,Res,EInfo);
}

ExeResult	AlgorithmDLLList::ExecuteStartByInspection	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res)
{
	if(DLL_ExecuteStartByInspection!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecuteStartByInspection	(ExeID,base,Res);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}
ExeResult	AlgorithmDLLList::ExecuteCaptured		(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res ,ListPhasePageLayerPack &CapturedList)
{
	if(DLL_ExecuteCaptured!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecuteCaptured	(ExeID,base,Res,CapturedList);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}ExeResult	AlgorithmDLLList::ExecutePreAlignment	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res)
{
	if(DLL_ExecutePreAlignment!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecutePreAlignment	(ExeID,base,Res);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}
ExeResult	AlgorithmDLLList::ExecuteAlignment	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res)
{
	if(DLL_ExecuteAlignment!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecuteAlignment(ExeID,base,Res);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}
ExeResult	AlgorithmDLLList::ExecutePreProcessing	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res)
{
	if(DLL_ExecutePreProcessing!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecutePreProcessing(ExeID,base,Res);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}
ExeResult	AlgorithmDLLList::ExecuteProcessing	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res)
{
	if(DLL_ExecuteProcessing!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecuteProcessing(ExeID,base,Res);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}
ExeResult	AlgorithmDLLList::ExecuteProcessingRevived(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res)
{
	if(DLL_ExecuteProcessingRevived!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecuteProcessingRevived(ExeID,base,Res);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}
ExeResult	AlgorithmDLLList::ExecutePostProcessing	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res)
{
	if(DLL_ExecutePostProcessing!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecutePostProcessing	(ExeID,base,Res);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}
ExeResult	AlgorithmDLLList::ExecutePreScanning(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res)
{
	if(DLL_ExecutePreScanning!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecutePreScanning	(ExeID,base,Res);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}
ExeResult	AlgorithmDLLList::ExecuteScanning(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res)
{
	if(DLL_ExecuteScanning!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecuteScanning	(ExeID,base,Res);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}
ExeResult	AlgorithmDLLList::ExecutePostScanning(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res)
{
	if(DLL_ExecutePostScanning!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecutePostScanning	(ExeID,base,Res);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}
ExeResult	AlgorithmDLLList::ExecuteManageResult	(int ExeID ,AlgorithmBase *base,ResultInspection *Res)
{
	if(DLL_ExecuteManageResult!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecuteManageResult	(ExeID,base,Res);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}

ExeResult	AlgorithmDLLList::ExecuteMatch	(int ExeID ,AlgorithmBase *InstBase,ImagePointerContainer &TargetImages,int cx, int cy ,double &Result)
{
	if(DLL_ExecuteMatch!=NULL){
		InFunc=true;
		ExeResult	ret=DLL_ExecuteMatch(ExeID,InstBase,TargetImages,cx, cy ,Result);
		InFunc=false;
		return ret;
	}
	return _ER_NoFunc;
}

bool	AlgorithmDLLList::DrawResultBase(int32 ShowFixedPhase,AlgorithmBase *InstBase ,ResultBaseForAlgorithmRoot *Res,QPainter &Pnt ,QImage *IData ,int MovX ,int MovY ,double ZoomRate,int localPage)
{
	if(DLL_DrawResultBase!=NULL){
		InFunc=true;
		bool	ret=DLL_DrawResultBase(ShowFixedPhase,InstBase ,Res,Pnt ,IData ,MovX ,MovY ,ZoomRate,localPage);
		InFunc=false;
		return ret;
	}
	return false;
}
QWidget	*AlgorithmDLLList::ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	QWidget	*RetForm=NULL;
	if(DLL_ShowAndSetItems!=NULL){
		for(AlgorithmItemIndependent *p=Data.Items.GetFirst();p!=NULL;){
			if(p->AlgorithmRoot!=DLLRoot || p->AlgorithmName!=DLLName){
				AlgorithmItemIndependent *NextP=p->GetNext();
				Data.Items.RemoveList(p);
				delete	p;
				p=NextP;
			}
			else{
				p=p->GetNext();
			}
		}
		if(Data.Items.GetNumber()!=0){
			InFunc=true;
			RetForm=DLL_ShowAndSetItems(parent, Command ,InstBase ,Data,Something);
			InFunc=false;
		}
	}
	return RetForm;
}
void	AlgorithmDLLList::MakeIndependentItems(int32 TargetPhase,int32 localPage ,bool SubResultMoving, int localX ,int localY,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	if(DLL_MakeIndependentItems!=NULL){
		InFunc=true;
		DLL_MakeIndependentItems(TargetPhase,localPage ,SubResultMoving, localX ,localY,InstBase ,Data);
		InFunc=false;
	}
}
void	AlgorithmDLLList::SetIndependentItemData(int32 Command
												,AlgorithmBase *InstBase ,int32 TargetPhase,int32 LocalPage,int32 Layer,int32 ItemID
												,AlgorithmItemRoot *Data
												,IntList &EdittedMemberID
												,QByteArray &Something
												,QByteArray &AckData)
{
	if(DLL_SetIndependentItemData!=NULL){
		InFunc=true;
		DLL_SetIndependentItemData(Command,InstBase ,TargetPhase,LocalPage,Layer,ItemID,Data,EdittedMemberID,Something,AckData);
		InFunc=false;
	}
}
bool	AlgorithmDLLList::DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos
										   ,DetailResultInfoListContainer &RetList)
{
	if(DLL_DrawResultDetail!=NULL){
		InFunc=true;
		bool	ret=DLL_DrawResultDetail(Item ,Pos ,RetList);
		InFunc=false;
		return ret;
	}
	return false;
}

QWidget	*AlgorithmDLLList::ChangeItemsAttr(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	QWidget	*RetForm=NULL;
	if(DLL_ChangeItemsAttr!=NULL){
		InFunc=true;
		RetForm=DLL_ChangeItemsAttr(parent, Command ,InstBase ,Data);
		InFunc=false;
	}
	return RetForm;
}

bool	AlgorithmDLLList::SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	if(DLL_SaveItem!=NULL){
		InFunc=true;
		bool	ret=DLL_SaveItem(f,item);
		InFunc=false;
		return ret;
	}
	return true;
}
bool	AlgorithmDLLList::LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	if(DLL_LoadItem!=NULL){
		InFunc=true;
		bool	ret=DLL_LoadItem(f,item,LBase);
		InFunc=false;
		return ret;
	}
	return false;
}
ResultBaseForAlgorithmRoot	*AlgorithmDLLList::CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	if(DLL_CreateResultBaseForAlgorithm!=NULL){
		InFunc=true;
		ResultBaseForAlgorithmRoot	*ret=DLL_CreateResultBaseForAlgorithm(parent);
		InFunc=false;
		return ret;
	}
	return NULL;
}

AddedDataClass	*AlgorithmDLLList::LoadAddedResultData (QIODevice *f ,int32 AddedDataType)
{
	if(DLL_LoadAddedResultData!=NULL){
		InFunc=true;
		AddedDataClass	*ret=DLL_LoadAddedResultData (f ,AddedDataType);
		InFunc=false;
		return ret;
	}
	return NULL;
}
bool			AlgorithmDLLList::SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType)
{
	if(DLL_SaveAddedResultData!=NULL){
		InFunc=true;
		bool	ret=DLL_SaveAddedResultData(f ,d ,AddedDataType);
		InFunc=false;
		return ret;
	}
	return false;
}
void			AlgorithmDLLList::RemoveAddedResultData(AddedDataClass *d)
{
	if(DLL_RemoveAddedResultData!=NULL){
		InFunc=true;
		DLL_RemoveAddedResultData(d);
		InFunc=false;
	}
}

bool	AlgorithmDLLList::ReleaseGeneralAlgorithmData(AlgorithmBase *InstBase ,int32 Command,void *data)
{
	if(DLL_ReleaseGeneralAlgorithmData!=NULL){
		InFunc=true;
		bool	ret=DLL_ReleaseGeneralAlgorithmData(InstBase ,Command,data);
		InFunc=false;
		return ret;
	}
	return false;
}
void	*AlgorithmDLLList::CreateGeneralAlgorithmData(AlgorithmBase *InstBase ,int32 Command,void *reqData)
{
	if(DLL_CreateGeneralAlgorithmData!=NULL){
		InFunc=true;
		void	*ret=DLL_CreateGeneralAlgorithmData(InstBase ,Command,reqData);
		InFunc=false;
		return ret;
	}
	return NULL;
}
bool	AlgorithmDLLList::LoadGeneralAlgorithmData(AlgorithmBase *InstBase ,QIODevice *f,int32 Command ,void *data)
{
	if(DLL_LoadGeneralAlgorithmData!=NULL){
		InFunc=true;
		bool	ret=DLL_LoadGeneralAlgorithmData(InstBase ,f,Command ,data);
		InFunc=false;
		return ret;
	}
	return false;
}
bool	AlgorithmDLLList::SaveGeneralAlgorithmData(AlgorithmBase *InstBase ,QIODevice *f,int32 Command ,void *data)
{
	if(DLL_SaveGeneralAlgorithmData!=NULL){
		InFunc=true;
		bool	ret=DLL_SaveGeneralAlgorithmData(InstBase ,f,Command ,data);
		InFunc=false;
		return ret;
	}
	return false;
}
bool	AlgorithmDLLList::ReplyGeneralAlgorithmData(AlgorithmBase *InstBase ,int32 Command ,void *data)
{
	if(DLL_ReplyGeneralAlgorithmData!=NULL){
		InFunc=true;
		bool	ret=DLL_ReplyGeneralAlgorithmData(InstBase ,Command ,data);
		InFunc=false;
		return ret;
	}
	return false;
}

bool	AlgorithmDLLList::ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuf)
{
	if(DLL_ResultItemToString!=NULL){
		InFunc=true;
		bool	ret=DLL_ResultItemToString(ItemRes ,RetStrBuf);
		InFunc=false;
		return ret;
	}
	return false;
}
bool	AlgorithmDLLList::BindSpecialResult(ResultInItemRoot *ItemRes ,ErrorGroupPack &Dest)
{
	if(DLL_BindSpecialResult!=NULL){
		InFunc=true;
		bool	ret=DLL_BindSpecialResult(ItemRes ,Dest);
		InFunc=false;
		return ret;
	}
	return false;
}

bool	AlgorithmDLLList::SaveCSVMasterReport(AlgorithmBase *InstBase, QStringListListCSV &CSVData)
{
	if(DLL_SaveCSVMasterReport!=NULL){
		InFunc=true;
		bool	ret=DLL_SaveCSVMasterReport(InstBase, CSVData);
		InFunc=false;
		return ret;
	}
	return false;
}


AlignmentPacketBase	*AlgorithmDLLList::GetAlignmentPointer(AlgorithmBase *base ,int localPage, int localX ,int localY,AlgorithmItemRoot *Item ,bool FromGlobal)
{
	if(DLL_GetAlignmentPointer!=NULL){
		InFunc=true;
		AlignmentPacketBase	*ret=DLL_GetAlignmentPointer(base ,localPage, localX ,localY,Item ,FromGlobal);
		InFunc=false;
		return ret;
	}
	return NULL;
}
void		AlgorithmDLLList::GetAlignmentForProcessing(AlgorithmBase *base ,int localPage, AlignmentPacketBase &Packet)
{
	if(DLL_GetAlignmentForProcessing!=NULL){
		InFunc=true;
		DLL_GetAlignmentForProcessing(base ,localPage, Packet);
		InFunc=false;
	}
}

bool	AlgorithmDLLList::IsEdited(AlgorithmBase *InstBase)
{
	if(DLL_IsEdited!=NULL){
		InFunc=true;
		bool	ret=DLL_IsEdited(InstBase);
		InFunc=false;
		return ret;
	}
	return false;
}
bool	AlgorithmDLLList::IsCalcDone(AlgorithmBase *InstBase)
{
	if(DLL_IsCalcDone!=NULL){
		InFunc=true;
		bool	ret=DLL_IsCalcDone(InstBase);
		InFunc=false;
		return ret;
	}
	return false;
}
void	AlgorithmDLLList::SetEdited(AlgorithmBase *InstBase,bool edited)
{
	if(DLL_SetEdited!=NULL){
		InFunc=true;
		DLL_SetEdited(InstBase,edited);
		InFunc=false;
	}
}
void	AlgorithmDLLList::SetCalcDone(AlgorithmBase *InstBase,bool calcdone)
{
	if(DLL_SetCalcDone!=NULL){
		InFunc=true;
		DLL_SetCalcDone(InstBase,calcdone);
		InFunc=false;
	}
}
bool	AlgorithmDLLList::LocalPos2Name(AlgorithmBase *Base ,int Page ,int XLocalPos, int YLocalPos ,QString &Name)
{
	if(DLL_LocalPos2Name!=NULL){
		InFunc=true;
		bool	ret=DLL_LocalPos2Name(Base ,Page ,XLocalPos, YLocalPos ,Name);
		InFunc=false;
		return ret;
	}
	return false;
}

bool	AlgorithmDLLList::GetNGTypeContainer(AlgorithmBase *ABase ,int LibID
							,  LibNGTypeInAlgorithm &NGTypeContainer)
{
	if(DLL_GetNGTypeContainer!=NULL){
		InFunc=true;
		bool	ret=DLL_GetNGTypeContainer(ABase,LibID,  NGTypeContainer);
		InFunc=false;
		return ret;
	}
	return false;
}

bool	AlgorithmDLLList::ReceivePacketDirectComm(AlgorithmBase *ABase ,int32 cmd ,int32 globalPage ,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName,QBuffer &buff,int32 IDForUndo,ErrorCodeList &ErrorData)
{
	if(DLL_ReceivePacketDirectComm!=NULL){
		return DLL_ReceivePacketDirectComm(ABase,GetLayersBase(),cmd ,globalPage ,EmitterRoot ,EmitterName ,ClassName,buff,IDForUndo,ErrorData);
	}
	return false;
}


bool	AlgorithmDLLList::CheckSystemVersion(QStringList &Str)
{
	return CheckSystemVersionFunc(Str ,"AlgorithmDLL",DLLRoot ,DLLName);
}

void		AlgorithmDLLList::SetPriority(const AlgorithmDefList &Def)
{
	if(Def.PriorityInitialAfterEdit>=0){
		PriorityInitialAfterEdit=Def.PriorityInitialAfterEdit;
	}
	if(Def.PriorityAutoGeneration>=0){
		PriorityAutoGeneration=Def.PriorityAutoGeneration;
	}
	if(Def.PriorityStartByInspection>=0){
		PriorityStartByInspection=Def.PriorityStartByInspection;
	}
	if(Def.PriorityPreAlignment>=0){
		PriorityPreAlignment=Def.PriorityPreAlignment;
	}
	if(Def.PriorityAlignment>=0){
		PriorityAlignment=Def.PriorityAlignment;
	}
	if(Def.PriorityPreProcessing>=0){
		PriorityPreProcessing=Def.PriorityPreProcessing;
	}
	if(Def.PriorityProcessing>=0){
		PriorityProcessing=Def.PriorityProcessing;
	}
	if(Def.PriorityProcessingRevived>=0){
		PriorityProcessingRevived=Def.PriorityProcessingRevived;
	}
	if(Def.PriorityPostProcessing>=0){
		PriorityPostProcessing=Def.PriorityPostProcessing;
	}
	if(Def.PriorityPreScanning>=0){
		PriorityPreScanning=Def.PriorityPreScanning;
	}
	if(Def.PriorityScanning>=0){
		PriorityScanning=Def.PriorityScanning;
	}
	if(Def.PriorityPostScanning>=0){
		PriorityPostScanning=Def.PriorityPostScanning;
	}
	if(Def.PriorityManageResult>=0){
		PriorityManageResult=Def.PriorityManageResult;
	}
}

int		AlgorithmDLLList::GetPriorityDetail(OperationMode mode)
{
	switch(mode){
		case ModeInitialAfterEdit:
			return PriorityInitialAfterEdit;
		case ModeAutoGeneration:
			return PriorityAutoGeneration;
		case ModeStartByInspection:
			return PriorityStartByInspection;
		case ModePreAlignment:
			return PriorityPreAlignment;
		case ModeAlignment:
			return PriorityAlignment;
		case ModePreProcessing:
			return PriorityPreProcessing;
		case ModeProcessing:
			return PriorityProcessing;
		case ModeProcessingRevived:
			return PriorityProcessingRevived;
		case ModePostProcessing:
			return PriorityPostProcessing;
		case ModePreScanning:
			return PriorityPreScanning;
		case ModeScanning:
			return PriorityScanning;
		case ModePostScanning:
			return PriorityPostScanning;
		case ModeManageResult:
			return PriorityManageResult;
	}
	return 0;
}
void	AlgorithmDLLList::SetPriorityDetail(OperationMode mode,int priority)
{
	switch(mode){
		case ModeInitialAfterEdit:
			PriorityInitialAfterEdit	=priority;
			break;
		case ModeAutoGeneration:
			PriorityAutoGeneration		=priority;
			break;
		case ModeStartByInspection:
			PriorityStartByInspection	=priority;
			break;
		case ModePreAlignment:
			PriorityPreAlignment		=priority;
			break;
		case ModeAlignment:
			PriorityAlignment			=priority;
			break;
		case ModePreProcessing:
			PriorityPreProcessing		=priority;
			break;
		case ModeProcessing:
			PriorityProcessing			=priority;
			break;
		case ModeProcessingRevived:
			PriorityProcessingRevived	=priority;
			break;
		case ModePostProcessing:
			PriorityPostProcessing		=priority;
			break;
		case ModePreScanning:
			PriorityPreScanning			=priority;
			break;
		case ModeScanning:
			PriorityScanning			=priority;
			break;
		case ModePostScanning:
			PriorityPostScanning		=priority;
			break;
		case ModeManageResult:
			PriorityManageResult		=priority;
			break;
	}
}


void	AlgorithmDLLList::SaveAlgorithmDefFile(QTextStream &FStr,QStringList &EffectiveAlgoFileNames)
{
	QFileInfo	fileInfo(FileName);
	if(EffectiveAlgoFileNames.contains(fileInfo.fileName())==true){
		FStr<<fileInfo.fileName()<<QString(",");
	}
	else{
		FStr<<QString("//")<<fileInfo.fileName()<<QString(",");
	}
	FStr<<QString::number(PriorityInitialAfterEdit)<<QString(",");
	FStr<<QString::number(PriorityStartByInspection)<<QString(",");
	FStr<<QString::number(PriorityPreAlignment)<<QString(",");
	FStr<<QString::number(PriorityAlignment)<<QString(",");
	FStr<<QString::number(PriorityPreProcessing)<<QString(",");
	FStr<<QString::number(PriorityProcessing)<<QString(",");
	FStr<<QString::number(PriorityPostProcessing)<<QString(",");
	FStr<<QString::number(PriorityPreScanning)<<QString(",");
	FStr<<QString::number(PriorityScanning)<<QString(",");
	FStr<<QString::number(PriorityPostScanning)<<QString(",");
	FStr<<QString::number(PriorityManageResult)<<QString(",");
	FStr<<QString::number(PriorityAutoGeneration)<<QString(",");
	FStr<<QString::number(PriorityProcessingRevived)<<QString("\n");
}
int		AlgorithmDLLList::RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	if(DLL_RegistMacroFunction!=NULL){
		return DLL_RegistMacroFunction(Functions,MaxBuffer);
	}
	return 0;
}

int	AlgorithmDLLContainer::SearchAddDLL(RootNameListContainer &AlgoList
										,LayersBase *Base 
										,const QStringList &AlgorithmPathList
										,bool LoadAll)
{
	int	N=0;
	AlgorithmDLLList	*DLL;
	QString	AlgoFileName;

	if(LoadAll==true){
		char	buff[200];
		LoadAlgorithmDefFile();

		for(int k=0;k<AlgorithmPathList.count();k++){
			QString	path=AlgorithmPathList[k];

			QString2Char(path,buff,sizeof(buff));
			printf("%s\n",buff);
			QDir::setCurrent(Base->GetSystemPath());
			QString	kstr=QDir::currentPath();
			QDir	Dir;
			if(Dir.cd(path)==true){
				QString	SearchFile=QString("*.")+GetDynamicFileExt();
				QStringList nameFilters(SearchFile);
				QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );

				for(int i=0;i<List.size();i++){
					QString	FileName=path+GetSeparator()+List[i];
					Base->TestLoadDLL(FileName);
					if(QLibrary::isLibrary(FileName)==true){
						DLL=new AlgorithmDLLList(Base);
						DLL->SetFileName(FileName);
						printf("LoadDLL\n");
						if(DLL->LoadDLL(FileName)==true){
							printf("LoadDLL OK\n");
							if(DLL->IsAlgorithm()==true && DLL->GetName()==true){
								AlgoFileName=List.at(i);
								for(AlgorithmDefList *a=AlgorithmDef.GetFirst();a!=NULL;a=a->GetNext()){
									if(AlgoFileName.toLower()==a->Str){
										DLL->SetPriority(*a);
										break;
									}
								}

								printf("AppendList\n");
								AppendList(DLL);
								if(GetLayersBase()!=NULL){
									GetLayersBase()->InformToLoadDLL(FileName);
								}
								N++;
							}
							else{
								delete	DLL;
							}
						}
						else{
							delete	DLL;
						}
					}
				}
			}
		}
	}
	else{
		if(AlgoList.GetNumber()==0){
			LoadAlgorithmDefFile();
			for(int k=0;k<AlgorithmPathList.count();k++){
				QString	path=AlgorithmPathList[k];
				char	buff[200];
				QString2Char(path,buff,sizeof(buff));
				printf("%s\n",buff);
				QDir	Dir;
				QDir::setCurrent(Base->GetSystemPath());
				if(Dir.cd(path)==true){
					QString	SearchFile=QString("*.")+GetDynamicFileExt();
					QStringList nameFilters(SearchFile);
					QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );

					for(int i=0;i<List.size();i++){
						AlgoFileName=List.at(i);
						bool	FoundJ=false;
						AlgorithmDefList	*PriorityList;
						for(AlgorithmDefList *a=AlgorithmDef.GetFirst();a!=NULL;a=a->GetNext()){
							if(AlgoFileName.toLower()==a->Str){
								FoundJ=true;
								PriorityList=a;
							}
						}
						if(FoundJ==true){
							QString	FileName=path+GetSeparator()+AlgoFileName;
							Base->TestLoadDLL(FileName);
							if(QLibrary::isLibrary(FileName)==true){
								DLL=new AlgorithmDLLList(Base);
								DLL->SetFileName(FileName);
								printf("LoadDLL\n");
								if(DLL->LoadDLL(FileName)==true){
									printf("LoadDLL OK\n");
									if(DLL->IsAlgorithm()==true && DLL->GetName()==true){
										DLL->SetPriority(*PriorityList);

										printf("AppendList\n");
										AppendList(DLL);
										if(GetLayersBase()!=NULL){
											GetLayersBase()->InformToLoadDLL(FileName);
										}
										N++;
									}
									else{
										delete	DLL;
									}
								}
								else{
									delete	DLL;
								}
							}
						}
					}
				}
			}
		}
		else{
			LoadAlgorithmDefFile();
			char	buff[200];
			for(int k=0;k<AlgorithmPathList.count();k++){
				QString	path=AlgorithmPathList[k];
				QString2Char(path,buff,sizeof(buff));
				printf("%s\n",buff);
				QDir	Dir;
				QDir::setCurrent(Base->GetSystemPath());
				if(Dir.cd(path)==true){
					QString	SearchFile=QString("*.")+GetDynamicFileExt();
					QStringList nameFilters(SearchFile);
					QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );					

					for(int i=0;i<List.size();i++){
						AlgoFileName=List.at(i);
						QString	FileName=path+GetSeparator()+AlgoFileName;
						Base->TestLoadDLL(FileName);
						if(QLibrary::isLibrary(FileName)==true){
							DLL=new AlgorithmDLLList(Base);
							DLL->SetFileName(FileName);
							printf("LoadDLL\n");
							if(DLL->LoadDLL(FileName)==true){
								printf("LoadDLL OK\n");
								if(DLL->IsAlgorithm()==true && DLL->GetName()==true){
									bool	FoundA=false;
									for(RootNameList *a=AlgoList.GetFirst();a!=NULL;a=a->GetNext()){
										if(DLL->CheckDLL(a->DLLRoot,a->DLLName)==true){
											FoundA=true;
										}
									}
									AlgorithmDefList	*PriorityList=NULL;
									for(AlgorithmDefList *a=AlgorithmDef.GetFirst();a!=NULL;a=a->GetNext()){
										if(AlgoFileName.toLower()==a->Str){
											FoundA=true;
											PriorityList=a;
										}
									}
									if(FoundA==true){
										if(PriorityList!=NULL){
											DLL->SetPriority(*PriorityList);
										}

										printf("AppendList\n");
										AppendList(DLL);
										if(GetLayersBase()!=NULL){
											GetLayersBase()->InformToLoadDLL(FileName);
										}
										N++;
									}
									else{
										delete	DLL;
									}
								}
								else{
									delete	DLL;
								}
							}
						}
					}
				}
			}
		}
	}
	return(N);
}

int		AlgorithmDLLContainer::CopyAddDLL(const AlgorithmDLLContainer *Parent)
{
	RemoveAll();
	for(AlgorithmDLLList *p=Parent->GetFirst();p!=NULL;p=p->GetNext()){
		AlgorithmDLLList	*a=new AlgorithmDLLList(p,GetLayersBase());
		AppendList(a);
	}
	return GetCount();
}

bool	AlgorithmDLLContainer::LoadOneDLL(LayersBase *Base ,const QString &DLLFileNameWithPath)
{
	Base->TestLoadDLL(DLLFileNameWithPath);
	if(QLibrary::isLibrary(DLLFileNameWithPath)==true){
		AlgorithmDLLList	*DLL=new AlgorithmDLLList(Base);
		DLL->SetFileName(DLLFileNameWithPath);
		if(DLL->LoadDLL(DLLFileNameWithPath)==true){
			if(DLL->IsAlgorithm()==true){
				bool	FoundA=false;
				for(AlgorithmDLLList *a=GetFirst();a!=NULL;a=a->GetNext()){
					if(a->CheckDLL(DLL->GetDLLRoot(),DLL->GetDLLName())==true){
						FoundA=true;
					}
				}
				if(FoundA==false){
					AppendList(DLL);
					if(GetLayersBase()!=NULL){
						GetLayersBase()->InformToLoadDLL(DLLFileNameWithPath);
					}
					return true;
				}
			}
		}
		delete	DLL;
	}
	return false;
}

bool	AlgorithmDLLContainer::LoadAlgorithmDefFile(void)
{
	QFile	F(GetParamGlobal()->AlgorithmDefFile);
	if(F.open(QIODevice::ReadOnly)==false){
		return false;
	}
	AlgorithmDef.RemoveAll();
	QTextStream	Str(&F);
	while(Str.atEnd()==false){
		QString	L=Str.readLine();
		L=L.trimmed ();
		if(L.left(2)=="//"){
			continue;
		}
		AlgorithmDefList	*a=new AlgorithmDefList();
		a->SetLine(L.toLower());

		AlgorithmDef.AppendList(a);
	}
	return true;
}

bool	AlgorithmDLLContainer::SaveAlgorithmDefFile(QStringList &EffectiveAlgoFileNames)
{
	QFile	F(GetParamGlobal()->AlgorithmDefFile);
	if(F.open(QIODevice::WriteOnly | QIODevice::Text)==false){
		return false;
	}
	for(AlgorithmDLLList *L=GetFirst();L!=NULL;L=L->GetNext()){
		QTextStream	FStr(&F);
		L->SaveAlgorithmDefFile(FStr,EffectiveAlgoFileNames);
	}
	return true;
}

AlgorithmDefList	*AlgorithmDLLContainer::SearchDef(const QString &AlgoFileName)
{
	QString iAlgoFileName=AlgoFileName.toLower();
	for(AlgorithmDefList *a=AlgorithmDef.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Str==iAlgoFileName){
			return a;
		}
	}
	return NULL;
}

bool	AlgorithmDLLContainer::CheckSystemVersion(QStringList &Str)
{
	bool	Ret=true;
	for(AlgorithmDLLList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	return Ret;
}

//=======================================================================================================================================

LogicDLL::LogicDLL(LayersBase *Base)
:ServiceForLayers(Base)
{
	DLLPointer			=NULL;
	Ver					=0;
	InstBase			=NULL;
	LibContainer		=NULL;
	EnabledExpandable	=true;
	PriorityInitialAfterEdit	=100;
	PriorityAutoGeneration		=100;
	PriorityStartByInspection	=100;
	PriorityPreAlignment		=100;
	PriorityAlignment			=100;
	PriorityPreProcessing		=100;
	PriorityProcessing			=100;
	PriorityProcessingRevived	=100;
	PriorityPostProcessing		=100;
	PriorityPreScanning			=100;
	PriorityScanning			=100;
	PriorityPostScanning		=100;
	PriorityManageResult		=100;

	ShowAndSetItemsForm			=NULL;
	ChangeItemsAttrForm			=NULL;
}

LogicDLL::~LogicDLL(void)
{
	if(ShowAndSetItemsForm!=NULL){
		delete	ShowAndSetItemsForm;
		ShowAndSetItemsForm=NULL;
	}
	if(ChangeItemsAttrForm!=NULL){
		delete	ChangeItemsAttrForm;
		ChangeItemsAttrForm=NULL;
	}

	if(InstBase!=NULL)
		DLLPointer->ReleaseAlgorithmBase(InstBase);
	InstBase=NULL;
	if(LibContainer!=NULL)
		delete	LibContainer;
	LibContainer=NULL;
}

void		LogicDLL::Set(AlgorithmDLLList *s)
{
	DLLPointer=s;

}

LogicDLL	&LogicDLL::operator=(LogicDLL &src)
{
	DLLPointer=src.DLLPointer;
	InitialAlloc(GetLayersBase());
	InitialLibrary(GetLayersBase());

	AlgorithmBase	*Dest=GetInstance();
	AlgorithmBase	*Src =src.GetInstance();
	if(Dest!=NULL && Src!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		Src->SaveParam(&Buff);
		Buff.seek(0);
		Dest->LoadParam(&Buff);
	}
	return *this;
}

bool	LogicDLL::IsAlgorithm(void)
{
	int	d=DLLPointer->GetDLLType();
	if((d&DLLModeMask)==DLLAlgorithmMode){
		return(true);
	}
	return(false);
}

bool	LogicDLL::IsAlignment(void)
{
	int	d=DLLPointer->GetDLLType();
	if((d&DLL_ID_RA_ALIGNMENT)!=0){
		return(true);
	}
	return(false);
}

bool	LogicDLL::IsAvailableGetShowAndSetItemsForm(void)	const
{
	if(DLLPointer->DLL_ShowAndSetItems!=NULL)
		return true;
	return false;
}
bool	LogicDLL::IsAvailableGetChangeItemsAttrForm(void)	const
{
	if(DLLPointer->DLL_ChangeItemsAttr!=NULL)
		return true;
	return false;
}
bool	LogicDLL::SetLanguageCode(int LanguageCode)
{
	if(DLLPointer->SetLanguage(LanguageCode)==true){
		return true;
	}
	return false;
}

QString		LogicDLL::GetDefaultFileName(void)
{
	if(InstBase!=NULL){
		return InstBase->GetDefaultFileName();
	}
	return BlobName + QString(".dat");
}
void	LogicDLL::InitialName(void)
{
	DLLPointer->GetName();
}
bool	LogicDLL::InitialAlloc(LayersBase *Base)
{
	DLLPointer->CheckCopyright(Copyright);
	DLLType=DLLPointer->GetDLLType();

	Ver=DLLPointer->GetVersion();
	AlgorithmType=DLLPointer->GetAlgorithmType();
	if(AlgorithmType==0xFFFFFFFFU){
		return false;
	}

	InitialName();
	DLLPointer->GetOrganization(Organization);

	PriorityInitialAfterEdit	=DLLPointer->GetPriority(PriorityType_ExecuteInitialAfterEdit);
	PriorityAutoGeneration		=DLLPointer->GetPriority(PriorityType_ExecuteAutoGeneration	);
	PriorityStartByInspection	=DLLPointer->GetPriority(PriorityType_ExecuteStartByInspection);
	PriorityCaptured			=DLLPointer->GetPriority(PriorityType_ExecuteCaptured);
	PriorityPreAlignment		=DLLPointer->GetPriority(PriorityType_ExecutePreAlignment);
	PriorityAlignment			=DLLPointer->GetPriority(PriorityType_ExecuteAlignment);
	PriorityPreProcessing		=DLLPointer->GetPriority(PriorityType_ExecutePreProcessing);
	PriorityProcessing			=DLLPointer->GetPriority(PriorityType_ExecuteProcessing);
	PriorityProcessingRevived	=DLLPointer->GetPriority(PriorityType_ExecuteProcessingRevived);
	PriorityPostProcessing		=DLLPointer->GetPriority(PriorityType_ExecutePostProcessing);
	PriorityPreScanning			=DLLPointer->GetPriority(PriorityType_ExecutePreScanning);
	PriorityScanning			=DLLPointer->GetPriority(PriorityType_ExecuteScanning);
	PriorityPostScanning		=DLLPointer->GetPriority(PriorityType_ExecutePostScanning);
	PriorityManageResult		=DLLPointer->GetPriority(PriorityType_ExecuteManageResult);

	if(PriorityInitialAfterEdit==-1){
		PriorityInitialAfterEdit	=DLLPointer->GetPriorityDetail(AlgorithmDLLList::ModeInitialAfterEdit);
	}
	if(PriorityAutoGeneration==-1){
		PriorityAutoGeneration		=DLLPointer->GetPriorityDetail(AlgorithmDLLList::ModeAutoGeneration);
	}
	if(PriorityStartByInspection==-1){
		PriorityStartByInspection	=DLLPointer->GetPriorityDetail(AlgorithmDLLList::ModeStartByInspection);
	}
	if(PriorityPreAlignment==-1){
		PriorityPreAlignment		=DLLPointer->GetPriorityDetail(AlgorithmDLLList::ModePreAlignment);
	}
	if(PriorityAlignment==-1){
		PriorityAlignment			=DLLPointer->GetPriorityDetail(AlgorithmDLLList::ModeAlignment);
	}
	if(PriorityPreProcessing==-1){
		PriorityPreProcessing		=DLLPointer->GetPriorityDetail(AlgorithmDLLList::ModePreProcessing);
	}
	if(PriorityProcessing==-1){
		PriorityProcessing			=DLLPointer->GetPriorityDetail(AlgorithmDLLList::ModeProcessing);
	}
	if(PriorityProcessingRevived==-1){
		PriorityProcessingRevived	=DLLPointer->GetPriorityDetail(AlgorithmDLLList::ModeProcessingRevived);
	}
	if(PriorityPostProcessing==-1){
		PriorityPostProcessing		=DLLPointer->GetPriorityDetail(AlgorithmDLLList::ModePostProcessing	);
	}
	if(PriorityPreScanning==-1){
		PriorityPreScanning			=DLLPointer->GetPriorityDetail(AlgorithmDLLList::ModePreScanning);
	}
	if(PriorityScanning==-1){
		PriorityScanning			=DLLPointer->GetPriorityDetail(AlgorithmDLLList::ModeScanning);
	}
	if(PriorityPostScanning==-1){
		PriorityPostScanning		=DLLPointer->GetPriorityDetail(AlgorithmDLLList::ModePostScanning);
	}
	if(PriorityManageResult==-1){
		PriorityManageResult		=DLLPointer->GetPriorityDetail(AlgorithmDLLList::ModeManageResult);
	}

	const char	*p=DLLPointer->GetBlobName();
	if(p!=NULL){
		BlobName=QString(p);
	}

	int	LanguageCode=0;
	if(Base!=NULL && Base->GetFRegistry()!=NULL){
		LanguageCode=Base->GetFRegistry()->LoadRegInt("Language",0);
	}
	SetLanguageCode(LanguageCode);
	InstBase=AllocOnly(Base);
	
	QString	ParamFileName=GetDefaultFileName();
	if(ParamFileName.isEmpty()==false){
		QFile	PFile(ParamFileName);
		if(PFile.open(QIODevice::ReadOnly)==true){
			if(InstBase!=NULL){
				InstBase->LoadParam(&PFile);
			}
		}
	}
	if(GetInstance()!=NULL){
		GetInstance()->LoadedVersion=Ver;
	}

	return(true);
}
void	LogicDLL::AssociateComponent	(ComponentListContainer &List)
{
	if(DLLPointer!=NULL){
		DLLPointer->AssociateComponent(List);
	}
}
bool	LogicDLL::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	return GetInstance()->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
}
void	LogicDLL::ChangeAlgorithmType(DWORD algorithmtype)
{
	AlgorithmType	=algorithmtype;
}
AlgorithmBase	*LogicDLL::AllocOnly(LayersBase *Base)
{
	AlgorithmBase	*p=DLLPointer->InitialAlloc(Base);
	if(p!=NULL){
		p->LogicDLLPoint=this;
		return p;
	}

	return NULL;
}
void	LogicDLL::InitialAfterParamLoaded(void)
{
	if(InstBase!=NULL){
		InstBase->InitialAfterParamLoaded();
	}
}
void	LogicDLL::ReallocAlgorithmBase(LayersBase *Base)
{
	if(InstBase!=NULL){
		InstBase->Initial(Base);
		QFile	FAlgprithm(GetLayersBase()->GetUserPath()
						 +GetSeparator()
						 +InstBase->GetSavedFileName());
		if(FAlgprithm.open(QIODevice::ReadOnly)==true){
			InstBase->LoadParam(&FAlgprithm);
		}	
		InstBase->InitialAfterParamLoaded();
		InstBase->LogicDLLPoint=this;
	}
}
bool	LogicDLL::InitialLibrary(LayersBase *Base)
{
	if(LibContainer==NULL){
		LibContainer=DLLPointer->NewLibrary(Base);
		if(LibContainer!=NULL && LibContainer->CheckAndCreateLibTypeInDatabase()==false){
			return false;
		}
	}
	return true;
}

int		LogicDLL::GetPriority(int PriorityTypeBit_Type)	const
{
	switch(PriorityTypeBit_Type){
		case PriorityType_ExecuteInitialAfterEdit:
			return PriorityInitialAfterEdit;
		case PriorityType_ExecuteAutoGeneration:
			return PriorityAutoGeneration;
		case PriorityType_ExecuteStartByInspection:
			return PriorityStartByInspection;
		case PriorityType_ExecuteCaptured:
			return PriorityCaptured;
		case PriorityType_ExecutePreAlignment:
			return PriorityPreAlignment;
		case PriorityType_ExecuteAlignment	:
			return PriorityAlignment;
		case PriorityType_ExecutePreProcessing:
			return PriorityPreProcessing;
		case PriorityType_ExecuteProcessing	:
			return PriorityProcessing;
		case PriorityType_ExecuteProcessingRevived:
			return PriorityProcessingRevived;
		case PriorityType_ExecutePostProcessing:
			return PriorityPostProcessing;
		case PriorityType_ExecutePreScanning:
			return PriorityPreScanning;
		case PriorityType_ExecuteScanning	:
			return PriorityScanning;
		case PriorityType_ExecutePostScanning:
			return PriorityPostScanning;
		case PriorityType_ExecuteManageResult:
			return PriorityManageResult;
		default:
			return 100;
	}
}

QString		LogicDLL::GetExplain(void)
{	
	if(DLLPointer->GetExplain().isEmpty()==true){
		return /**/"";
	}
	return DLLPointer->GetExplain();
}

AddedDataClass	*LogicDLL::LoadAddedResultData (QIODevice *f ,int32 AddedDataType)
{
	AddedDataClass	*ret=DLLPointer->LoadAddedResultData (f ,AddedDataType);
	return(ret);
}
bool			LogicDLL::SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType)
{
	bool	ret=DLLPointer->SaveAddedResultData (f ,d ,AddedDataType);
	return(ret);
}
void			LogicDLL::RemoveAddedResultData(AddedDataClass *d)
{
	DLLPointer->RemoveAddedResultData(d);
}

bool	LogicDLL::CheckAndCreateBlobInMasterPageTable(const QSqlDatabase &db)
{
	if(BlobName.isEmpty()==false && GetLayersBase()->GetDatabaseLoader()){
		if(GetLayersBase()->GetDatabaseLoader()->S_CheckAndCreateBlobInMasterPageTable(db,BlobName)==false){
			return false;
		}
	}
	return true;
}

AlignmentPacketBase	*LogicDLL::GetAlignmentPointer(int localPage, int localX ,int localY,AlgorithmItemRoot *Item ,bool FromGlobal)
{
	AlignmentPacketBase	*ret=DLLPointer->GetAlignmentPointer(InstBase,localPage, localX,localY,Item ,FromGlobal);
	return ret;
}
void		LogicDLL::GetAlignmentForProcessing(int localPage, AlignmentPacketBase &Packet)
{
	DLLPointer->GetAlignmentForProcessing(InstBase,localPage, Packet);
}

bool	LogicDLL::ExecuteMoveItemsToDispatcherForLoadingParts(void)
{
	bool	ret=DLLPointer->ExecuteMoveItemsToDispatcherForLoadingParts(InstBase);
	return ret;
}

bool	LogicDLL::ExecuteCopyItemsFormDispatcherForParts(void)
{
	bool	ret=DLLPointer->ExecuteCopyItemsFormDispatcherForParts(InstBase);
	return ret;
}

bool	LogicDLL::ExecuteRemoveItemFormDispatcher(void)
{
	bool	ret=DLLPointer->ExecuteRemoveItemFormDispatcher(InstBase);
	return ret;
}

bool	LogicDLL::IsMaskAlgorithm(void)
{
	if((AlgorithmType&AlgorithmBit_TypeMasking)!=0){
		return true;
	}
	return false;
}
bool	LogicDLL::IsProcessAlgorithm(void)
{
	if((AlgorithmType&(AlgorithmBit_TypePreProcessing | AlgorithmBit_TypeProcessing | AlgorithmBit_TypePostProcessing))!=0){
		return true;
	}
	return false;
}
	
bool	LogicDLL::MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	if(DLLPointer!=NULL && InstBase!=NULL){
		return DLLPointer->MakeExecuteInitialAfterEditInfo	(ExeID ,InstBase,Res,EInfo);
	}
	return false;
}

ExeResult	LogicDLL::ExecuteInitialAfterEditPrev(int ExeID 
												,ResultBaseForAlgorithmRoot	*pResult
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	ret=DLLPointer->ExecuteInitialAfterEditPrev(ExeID ,InstBase,pResult,EInfo);
	if((GetParamGlobal()->DebugLevel & 0x02)!=0){
		#ifdef _MSC_VER
		if(_CrtCheckMemory()==false){
			ErrorOccurs();
		}
		#endif
	}
	return ret;
}

ExeResult	LogicDLL::ExecuteInitialAfterEdit	(int ExeID 
												,ResultBaseForAlgorithmRoot	*pResult
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	ret=DLLPointer->ExecuteInitialAfterEdit(ExeID ,InstBase,pResult,EInfo);
	if((GetParamGlobal()->DebugLevel & 0x02)!=0){
		#ifdef _MSC_VER
		if(_CrtCheckMemory()==false){
			ErrorOccurs();
		}
		#endif
	}
	return ret;
}

ExeResult	LogicDLL::ExecuteInitialAfterEditPost(int ExeID 
												,ResultBaseForAlgorithmRoot	*pResult
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	ret=DLLPointer->ExecuteInitialAfterEditPost(ExeID ,InstBase,pResult,EInfo);
	if((GetParamGlobal()->DebugLevel & 0x02)!=0){
		#ifdef _MSC_VER
		if(_CrtCheckMemory()==false){
			ErrorOccurs();
		}
		#endif
	}
	return ret;
}
ExeResult	LogicDLL::ExecuteStartByInspection(int ExeID ,ResultBaseForAlgorithmRoot *pResult)
{
	AlgorithmBase	*A=GetInstance();
	if(A!=NULL){
		A->SetProcessDone(false);
	}
	ExeResult	ret=DLLPointer->ExecuteStartByInspection(ExeID ,InstBase,pResult);
	if((GetParamGlobal()->DebugLevel & 0x02)!=0){
		#ifdef _MSC_VER
		if(_CrtCheckMemory()==false){
			ErrorOccurs();
		}
		#endif
	}
	return ret;
}
ExeResult	LogicDLL::ExecuteCaptured	(int ExeID ,ResultBaseForAlgorithmRoot *pResult,ListPhasePageLayerPack &CapturedList)
{
	if((AlgorithmType&AlgorithmBit_TypeCaptured)!=0){
		ExeResult	ret=DLLPointer->ExecuteCaptured(ExeID ,InstBase,pResult,CapturedList);
		if((GetParamGlobal()->DebugLevel & 0x02)!=0){
			#ifdef _MSC_VER
			if(_CrtCheckMemory()==false){
				ErrorOccurs();
			}
			#endif
		}
		return ret;
	}
	return _ER_true;
}
ExeResult	LogicDLL::ExecutePreAlignment		(int ExeID ,ResultBaseForAlgorithmRoot *pResult)
{
	if((AlgorithmType&AlgorithmBit_TypePreAlignment)!=0){
		ExeResult	ret=DLLPointer->ExecutePreAlignment(ExeID ,InstBase,pResult);
		if((GetParamGlobal()->DebugLevel & 0x02)!=0){
			#ifdef _MSC_VER
			if(_CrtCheckMemory()==false){
				ErrorOccurs();
			}
			#endif
		}
		return ret;
	}
	return _ER_true;
}
ExeResult	LogicDLL::ExecuteAlignment		(int ExeID ,ResultBaseForAlgorithmRoot *pResult)
{
	if((AlgorithmType&AlgorithmBit_TypeAlignment)!=0){
		ExeResult	ret=DLLPointer->ExecuteAlignment(ExeID ,InstBase,pResult);
		if((GetParamGlobal()->DebugLevel & 0x02)!=0){
			#ifdef _MSC_VER
			if(_CrtCheckMemory()==false){
				ErrorOccurs();
			}
			#endif
		}
		return ret;
	}
	return _ER_true;
}
ExeResult	LogicDLL::ExecutePreProcessing	(int ExeID ,ResultBaseForAlgorithmRoot *pResult)
{
	if((AlgorithmType&AlgorithmBit_TypePreProcessing)!=0 || (AlgorithmType&AlgorithmBit_TypeProcessing)!=0){
		ExeResult	ret=DLLPointer->ExecutePreProcessing(ExeID ,InstBase,pResult);
		if((GetParamGlobal()->DebugLevel & 0x02)!=0){
			#ifdef _MSC_VER
			if(_CrtCheckMemory()==false){
				ErrorOccurs();
			}
			#endif
		}
		return ret;
	}
	return _ER_true;
}
void	LogicDLL::MakeUncoveredMap(int Page ,BYTE **BMap, int XByte ,int YLen)
{
	if((AlgorithmType&AlgorithmBit_TypeProcessing)!=0){
		if(InstBase!=NULL){
			InstBase->GetPageData(Page)->MakeUncoveredMap(BMap, XByte ,YLen);
		}
	}
	else if((AlgorithmType&AlgorithmBit_TypeMasking)!=0){
		if(InstBase!=NULL){
			InstBase->GetPageData(Page)->MakeUncoveredMap(BMap, XByte ,YLen);
		}
	}
}

ExeResult	LogicDLL::ExecuteProcessing		(int ExeID ,ResultBaseForAlgorithmRoot *pResult)
{
	if((AlgorithmType&AlgorithmBit_TypeProcessing)!=0){
		ExeResult	ret=DLLPointer->ExecuteProcessing(ExeID ,InstBase,pResult);
		if((GetParamGlobal()->DebugLevel & 0x02)!=0){
			#ifdef _MSC_VER
			if(_CrtCheckMemory()==false){
				ErrorOccurs();
			}
			#endif
		}
		return ret;
	}
	return _ER_true;
}
ExeResult	LogicDLL::ExecuteProcessingRevived(int ExeID ,ResultBaseForAlgorithmRoot *pResult)
{
	if((AlgorithmType&AlgorithmBit_TypeProcessing)!=0){
		ExeResult	ret=DLLPointer->ExecuteProcessingRevived(ExeID ,InstBase,pResult);
		if((GetParamGlobal()->DebugLevel & 0x02)!=0){
			#ifdef _MSC_VER
			if(_CrtCheckMemory()==false){
				ErrorOccurs();
			}
			#endif
		}
		return ret;
	}
	return _ER_true;
}
ExeResult	LogicDLL::ExecutePostProcessing	(int ExeID ,ResultBaseForAlgorithmRoot *pResult)
{
	if((AlgorithmType&AlgorithmBit_TypePostProcessing)!=0){
		ExeResult	ret=DLLPointer->ExecutePostProcessing(ExeID ,InstBase,pResult);
		if((GetParamGlobal()->DebugLevel & 0x02)!=0){
			#ifdef _MSC_VER
			if(_CrtCheckMemory()==false){
				ErrorOccurs();
			}
			#endif
		}
		return ret;
	}
	return _ER_true;
}
ExeResult	LogicDLL::ExecutePreScanning	(int ExeID ,ResultBaseForAlgorithmRoot *pResult)
{
	if((AlgorithmType&AlgorithmBit_TypePreScanning)!=0){
		ExeResult	ret=DLLPointer->ExecutePreScanning(ExeID ,InstBase,pResult);
		if((GetParamGlobal()->DebugLevel & 0x02)!=0){
			#ifdef _MSC_VER
			if(_CrtCheckMemory()==false){
				ErrorOccurs();
			}
			#endif
		}
		return ret;
	}
	return _ER_true;
}
ExeResult	LogicDLL::ExecuteScanning	(int ExeID ,ResultBaseForAlgorithmRoot *pResult)
{
	if((AlgorithmType&AlgorithmBit_TypeScanning)!=0){
		ExeResult	ret=DLLPointer->ExecuteScanning(ExeID ,InstBase,pResult);
		if((GetParamGlobal()->DebugLevel & 0x02)!=0){
			#ifdef _MSC_VER
			if(_CrtCheckMemory()==false){
				ErrorOccurs();
			}
			#endif
		}
		return ret;
	}
	return _ER_true;
}
ExeResult	LogicDLL::ExecutePostScanning	(int ExeID ,ResultBaseForAlgorithmRoot *pResult)
{
	if((AlgorithmType&AlgorithmBit_TypePostScanning)!=0){
		ExeResult	ret=DLLPointer->ExecutePostScanning(ExeID ,InstBase,pResult);
		if((GetParamGlobal()->DebugLevel & 0x02)!=0){
			#ifdef _MSC_VER
			if(_CrtCheckMemory()==false){
				ErrorOccurs();
			}
			#endif
		}
		return ret;
	}
	return _ER_true;
}
ExeResult	LogicDLL::ExecuteManageResult		(int ExeID ,ResultInspection *Res)
{
	if((AlgorithmType&AlgorithmBit_TypeManageResult)!=0){
		ExeResult	ret=DLLPointer->ExecuteManageResult(ExeID ,InstBase,Res);
		if((GetParamGlobal()->DebugLevel & 0x02)!=0){
			#ifdef _MSC_VER
			if(_CrtCheckMemory()==false){
				ErrorOccurs();
			}
			#endif
		}
		return ret;
	}
	return _ER_true;
}
	
ExeResult	LogicDLL::ExecuteMatch	(int ExeID ,ImagePointerContainer &TargetImages,int cx, int cy ,double &Result)
{
	if((AlgorithmType&AlgorithmBit_TypeMatchAlignment)!=0){
		ExeResult	ret=DLLPointer->ExecuteMatch(ExeID ,InstBase,TargetImages,cx, cy ,Result);
		if((GetParamGlobal()->DebugLevel & 0x02)!=0){
			#ifdef _MSC_VER
			if(_CrtCheckMemory()==false){
				ErrorOccurs();
			}
			#endif
		}
		return ret;
	}
	return _ER_true;
}


bool	LogicDLL::DrawResultBase(int32 ShowFixedPhase,ResultBaseForAlgorithmRoot *Res ,QPainter &PntFromIData ,QImage *IData ,int MovX ,int MovY ,double ZoomRate,int localPage)
{
	if(Res!=NULL){
		bool	ret=DLLPointer->DrawResultBase(ShowFixedPhase,InstBase,Res ,PntFromIData ,IData ,MovX ,MovY ,ZoomRate,localPage);
		if((GetParamGlobal()->DebugLevel & 0x08)!=0){
			#ifdef _MSC_VER
			if(_CrtCheckMemory()==false){
				ErrorOccurs();
			}
			#endif
		}
		return ret;
	}
	return true;
}


bool	LogicDLL::DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos
								   ,DetailResultInfoListContainer &RetList)
{
	bool	ret=DLLPointer->DrawResultDetail(Item ,Pos ,RetList);
	if((GetParamGlobal()->DebugLevel & 0x08)!=0){
		#ifdef _MSC_VER
		if(_CrtCheckMemory()==false){
			ErrorOccurs();
		}
		#endif
	}
	return ret;
}

void	LogicDLL::ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	if(ShowAndSetItemsForm!=NULL){
		ShowAndSetItemsForm->close();
		if(ShowAndSetItemsForm!=NULL){
			ShowAndSetItemsForm->deleteLater();
		}
		ShowAndSetItemsForm=NULL;
	}
	QApplication::processEvents();
	ShowAndSetItemsForm=DLLPointer->ShowAndSetItems(parent, Command ,InstBase ,Data,Something);
	AlgorithmComponentWindow	*AWindow=dynamic_cast<AlgorithmComponentWindow *>(ShowAndSetItemsForm);
	//bool	Ret;
	if(AWindow!=NULL){
		AWindow->SetLogicDLL(this);
		//Ret=connect(AWindow,SIGNAL(SignalClosed()),this,SLOT(SlotShowAndSetItemsFormClosed()));
		//It doesn't work well in close
	}
	
}
void	LogicDLL::SlotShowAndSetItemsFormClosed()
{
	if(ShowAndSetItemsForm!=NULL){
		ShowAndSetItemsForm->deleteLater();
		ShowAndSetItemsForm=NULL;
	}
}

void	LogicDLL::MakeIndependentItems(int32 TargetPhase,int32 localPage ,bool SubResultMoving, int localX ,int localY,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	DLLPointer->MakeIndependentItems(TargetPhase,localPage ,SubResultMoving, localX,localY,InstBase ,Data);
}
void	LogicDLL::SetIndependentItemData(int32 Command
										,int32 TargetPhase,int32 LocalPage,int32 Layer,int32 ItemID
										,AlgorithmItemRoot *Data
										,IntList &EdittedMemberID
										,QByteArray &Something
										,QByteArray &AckData)
{
	DLLPointer->SetIndependentItemData(Command
										,GetInstance() ,TargetPhase,LocalPage,Layer,ItemID
										,Data
										,EdittedMemberID
										,Something
										,AckData);
}

void	LogicDLL::ChangeItemsAttr(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	if(ChangeItemsAttrForm!=NULL)
		delete	ChangeItemsAttrForm;
	ChangeItemsAttrForm	=DLLPointer->ChangeItemsAttr(parent, Command ,InstBase ,Data);
}

bool	LogicDLL::SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	bool	ret=DLLPointer->SaveItem(f,item);
	return ret;
}
bool	LogicDLL::LoadItem(QIODevice *f,AlgorithmItemRoot *item)
{
	bool	ret=DLLPointer->LoadItem(f,item,GetLayersBase());
	return ret;
}

bool	LogicDLL::ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	return DLLPointer->ResultItemToString(ItemRes ,RetStrBuff);
}

bool	LogicDLL::BindSpecialResult(ResultInItemRoot *ItemRes ,ErrorGroupPack &Dest)
{
	return DLLPointer->BindSpecialResult(ItemRes ,Dest);
}

AlgorithmItemRoot *LogicDLL::CreateItem(AlgorithmBase *InstBase,int ItemClassType)
{
	if(InstBase->GetPageData(0)!=NULL){
		return InstBase->GetPageData(0)->CreateItem(ItemClassType);
	}
	return NULL;
}
ResultBaseForAlgorithmRoot	*LogicDLL::CreateResultBaseForAlgorithm(ResultInspection *ResultInspectionPointer)
{
	ResultBaseForAlgorithmRoot	*ret=DLLPointer->CreateResultBaseForAlgorithm(this);
	if(ret!=NULL){
		ret->SetParent(ResultInspectionPointer);
	}
	return ret;
}


bool	LogicDLL::ReleaseGeneralAlgorithmData(int32 Command,void *data)
{
	bool	ret=DLLPointer->ReleaseGeneralAlgorithmData(GetInstance(),Command,data);
	return ret;
}
void	*LogicDLL::CreateGeneralAlgorithmData(int32 Command,void *reqData)
{
	void	*ret=DLLPointer->CreateGeneralAlgorithmData(GetInstance(),Command,reqData);
	return ret;
}
bool	LogicDLL::LoadGeneralAlgorithmData(QIODevice *f,int32 Command ,void *data)
{
	bool	ret=DLLPointer->LoadGeneralAlgorithmData(GetInstance(),f,Command ,data);
	return ret;
}
bool	LogicDLL::SaveGeneralAlgorithmData(QIODevice *f,int32 Command ,void *data)
{
	bool	ret=DLLPointer->SaveGeneralAlgorithmData(GetInstance(),f,Command ,data);
	return ret;
}
bool	LogicDLL::ReplyGeneralAlgorithmData(int32 Command ,void *data)
{
	bool	ret=DLLPointer->ReplyGeneralAlgorithmData(GetInstance(),Command ,data);
	return ret;
}

ClipboardAlgorithm	*LogicDLL::ExecuteCopy(int localPage ,const XDateTime &createdTime,IntList &LayerList)
{
	ClipboardAlgorithm	*C=new ClipboardAlgorithm(createdTime,InstBase->GetLayersBase());
	C->Base=InstBase;
	InstBase->ExecuteCopy(localPage ,*C,LayerList);
	if(C->Items.GetFirst()!=NULL){
		return C;
	}
	delete	C;
	return NULL;
}

QString		LogicDLL::GetFileName(void)	const	{	return DLLPointer->GetFileName();		}
QString		LogicDLL::GetDLLRoot(void)	const	{	return DLLPointer->GetDLLRoot();		}
QString		LogicDLL::GetDLLName(void)	const	{	return DLLPointer->GetDLLName();		}
bool		LogicDLL::CheckDLL(const QString &root, const QString &name)
{	
	return DLLPointer->CheckDLL(root, name);
}

bool	LogicDLL::IsEdited(void)
{
	return DLLPointer->IsEdited(GetInstance());
}
bool	LogicDLL::IsCalcDone(void)
{
	return DLLPointer->IsCalcDone(GetInstance());
}
void	LogicDLL::SetEdited(bool edited)
{
	DLLPointer->SetEdited(GetInstance(),edited);
}
void	LogicDLL::SetCalcDone(bool calcdone)
{
	DLLPointer->SetCalcDone(GetInstance(),calcdone);
}
bool	LogicDLL::LocalPos2Name(int LocalPage ,int XLocalPos, int YLocalPos ,QString &Name)
{
	return DLLPointer->LocalPos2Name(InstBase,LocalPage ,XLocalPos, YLocalPos ,Name);
}

bool	LogicDLL::SaveCSVMasterReport(AlgorithmBase *InstBase, QStringListListCSV &CSVData)
{
	return DLLPointer->SaveCSVMasterReport(InstBase, CSVData);
}

bool	LogicDLL::ReceivePacketDirectComm(int32 cmd ,int32 globalPage ,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName,QBuffer &buff,int32 IDForUndo,ErrorCodeList &ErrorData)
{
	return DLLPointer->ReceivePacketDirectComm(InstBase,cmd ,globalPage ,EmitterRoot ,EmitterName ,ClassName,buff,IDForUndo,ErrorData);
}

bool	LogicDLL::GetReflectionMap(ReflectionMode Mode ,ConstMapBuffer &Map ,int phase ,int page, int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	AlgorithmInPageRoot	*Ap=GetInstance()->GetPageDataPhase(phase)->GetPageData(page);
	ConstMapBuffer	*B=Ap->CreateReflectionMapForGenerator(Mode,layer ,LibData ,Anything);
	if(B==NULL){
		return false;
	}
	//Map.SetXY(B,Ap->GetDotPerLine(),Ap->GetMaxLines(),Map.GetFormat());
	Map.MoveFrom(*B);
	return true;
}
bool	LogicDLL::GetReflectionMap(ReflectionMode Mode ,ConstMapBuffer &Map ,int phase ,int page, int layer ,void *Anything)
{
	AlgorithmInPageRoot	*Ap=GetInstance()->GetPageDataPhase(phase)->GetPageData(page);
	ConstMapBuffer	*B=Ap->CreateReflectionMapForGenerator(Mode,layer ,Anything);
	if(B==NULL){
		return false;
	}
	//Map.SetXY(B,Ap->GetDotPerLine(),Ap->GetMaxLines(),Map.GetFormat());
	Map.MoveFrom(*B);
	return true;
}
bool	LogicDLL::GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,int phase ,int page, int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	bool	ret=GetInstance()->GetPageDataPhase(phase)->GetPageData(page)->CreateReflectionVectorForGenerator(Mode,Vector ,layer ,LibData ,Anything);
	return ret;
}

bool	LogicDLL::GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,int phase ,int page, int layer ,void *Anything)
{
	bool	ret=GetInstance()->GetPageDataPhase(phase)->GetPageData(page)->CreateReflectionVectorForGenerator(Mode,Vector ,layer ,Anything);
	return ret;
}
bool	LogicDLL::IncludeLibInReflection(ReflectionMode Mode ,int page, int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	bool	ret=GetInstance()->GetPageData(page)->IncludeLibInReflectionForGenerator(Mode,layer,LibData,Anything);
	return ret;
}
bool	LogicDLL::GetUsageLibInReflection(ReflectionMode Mode ,int page, int layer,AlgorithmLibraryListContainer &Ret)
{
	bool	ret=GetInstance()->GetPageData(page)->GetUsageLibInReflectionForGenerator(Mode,layer,Ret);
	return ret;
}

bool	LogicDLL::GetNGTypeContainer(int LibID
							,  LibNGTypeInAlgorithm &NGTypeContainer)
{
	return DLLPointer->GetNGTypeContainer(GetInstance()
										, LibID
										, NGTypeContainer);
}
int		LogicDLL::RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	return DLLPointer->RegistMacroFunction(Functions,MaxBuffer);
}

//===============================================================================

AlgorithmDefList::AlgorithmDefList(void)
{
	PriorityInitialAfterEdit	=100;
	PriorityAutoGeneration		=100;
	PriorityStartByInspection	=100;
	PriorityPreAlignment		=100;
	PriorityAlignment			=100;
	PriorityPreProcessing		=100;
	PriorityProcessing			=100;
	PriorityProcessingRevived	=100;
	PriorityPostProcessing		=100;
	PriorityPreScanning			=100;
	PriorityScanning			=100;
	PriorityPostScanning		=100;
	PriorityManageResult		=100;
}

void	AlgorithmDefList::SetLine(const QString &DefStr)
{
	Str=DefStr.section(',',0,0);

	QString	L=DefStr.section(',',1);

	bool	Ok;
	int		Priority;
	QString	H=L.section(',',0,0);
	if(H.isEmpty()==false){
		Priority=H.toInt(&Ok);
		if(Ok==true){
			PriorityInitialAfterEdit=Priority;
		}
	}
	H=L.section(',',1,1);
	if(H.isEmpty()==false){
		Priority=H.toInt(&Ok);
		if(Ok==true){
			PriorityStartByInspection=Priority;
		}
	}
	H=L.section(',',2,2);
	if(H.isEmpty()==false){
		Priority=H.toInt(&Ok);
		if(Ok==true){
			PriorityPreAlignment=Priority;
		}
	}
	H=L.section(',',3,3);
	if(H.isEmpty()==false){
		Priority=H.toInt(&Ok);
		if(Ok==true){
			PriorityAlignment=Priority;
		}
	}
	H=L.section(',',4,4);
	if(H.isEmpty()==false){
		Priority=H.toInt(&Ok);
		if(Ok==true){
			PriorityPreProcessing=Priority;
		}
	}
	H=L.section(',',5,5);
	if(H.isEmpty()==false){
		Priority=H.toInt(&Ok);
		if(Ok==true){
			PriorityProcessing=Priority;
		}
	}
	H=L.section(',',6,6);
	if(H.isEmpty()==false){
		Priority=H.toInt(&Ok);
		if(Ok==true){
			PriorityPostProcessing=Priority;
		}
	}
	H=L.section(',',7,7);
	if(H.isEmpty()==false){
		Priority=H.toInt(&Ok);
		if(Ok==true){
			PriorityPreScanning=Priority;
		}
	}
	H=L.section(',',8,8);
	if(H.isEmpty()==false){
		Priority=H.toInt(&Ok);
		if(Ok==true){
			PriorityScanning=Priority;
		}
	}
	H=L.section(',',9,9);
	if(H.isEmpty()==false){
		Priority=H.toInt(&Ok);
		if(Ok==true){
			PriorityPostScanning=Priority;
		}
	}
	H=L.section(',',10,10);
	if(H.isEmpty()==false){
		Priority=H.toInt(&Ok);
		if(Ok==true){
			PriorityManageResult=Priority;
		}
	}
	H=L.section(',',11,11);
	if(H.isEmpty()==false){
		Priority=H.toInt(&Ok);
		if(Ok==true){
			PriorityAutoGeneration=Priority;
		}
	}
	H=L.section(',',12,12);
	if(H.isEmpty()==false){
		Priority=H.toInt(&Ok);
		if(Ok==true){
			PriorityProcessingRevived=Priority;
		}
	}
}

LogicDLLBaseClass::LogicDLLBaseClass(LayersBase *base):ServiceForLayers(base)
{
}
LogicDLLBaseClass::~LogicDLLBaseClass(void)
{
	//ResultData.Release();
	LogicDLL *c=NULL;
	while((c=GetFirst())!=NULL){
		RemoveList(c);
		delete	c;
	}
}

LogicDLLBaseClass	&LogicDLLBaseClass::operator=(const LogicDLLBaseClass &src)
{
	RemoveAll();
	for(LogicDLL *L=src.GetFirst();L!=NULL;L=L->GetNext()){
		LogicDLL *M=new LogicDLL(GetLayersBase());
		*M= *L;
		AppendList(M);
	}
	return *this;
}

void	LogicDLLBaseClass::CopyFrom(LayersBase *ToBase,const LogicDLLBaseClass &src)
{
	RemoveAll();
	for(LogicDLL *L=src.GetFirst();L!=NULL;L=L->GetNext()){
		LogicDLL *M=new LogicDLL(ToBase);
		*M= *L;
		AppendList(M);
	}
}

int	LogicDLLBaseClass::AddDLLs(const AlgorithmDLLContainer &AlgoCont ,LayersBase *Base)
{
	int	N=0;

	RemoveAll();
	for(AlgorithmDLLList *L=AlgoCont.GetFirst();L!=NULL;L=L->GetNext()){
		LogicDLL	*DLLInst=new LogicDLL(Base);
		DLLInst->Set(L);
		DLLInst->InitialName();

		printf("InitialAlloc\n");
		DLLInst->InitialAlloc(Base);
		AppendList(DLLInst);
		N++;
	}
	return N;
}
bool	LogicDLLBaseClass::LoadOneDLL(LayersBase *Base ,const QString &DLLFileNameWithPath)
{
	for(AlgorithmDLLList *L=Base->GetAlgoDLLContPointer()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetFileName()==DLLFileNameWithPath){
			LogicDLL	*DLLInst=new LogicDLL(Base);
			DLLInst->Set(L);
			DLLInst->InitialName();

			printf("InitialAlloc\n");
			DLLInst->InitialAlloc(Base);
			AppendList(DLLInst);
			return true;
		}
	}
	return false;
}

LogicDLL	*LogicDLLBaseClass::Search(int dynamicID)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetDynamicID()==dynamicID){
			return(L);
		}
	}
	return(NULL);
}
void    LogicDLLBaseClass::InitialAfterParamLoaded(void)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->InitialAfterParamLoaded();
	}
}
LogicDLL	*LogicDLLBaseClass::Search(const QString &_DLLRoot ,const QString &_DLLName)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckDLL(_DLLRoot ,_DLLName)==true){
			return(L);
		}
	}
	return(NULL);
}
LogicDLL	*LogicDLLBaseClass::SearchByAlgorithmType(int algoType)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(algoType)==true){
			return L;
		}
	}
	return NULL;
}
LogicDLL	*LogicDLLBaseClass::NextByAlgorithmType(LogicDLL *Before,int algoType)
{
	for(LogicDLL *L=Before->GetNext();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(algoType)==true){
			return L;
		}
	}
	return NULL;
}

LogicDLL	*LogicDLLBaseClass::SearchByLibType(int LibType)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetLibContainer()!=NULL){
			if(L->GetLibContainer()->GetLibType()==LibType){
				return L;
			}
		}
	}
	return NULL;
}


int		LogicDLLBaseClass::GetDLLCounts(void)
{
	return GetNumber();
}

bool	LogicDLLBaseClass::Save(QIODevice *f)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	LogicDLLBaseClass::Load(QIODevice *f)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()->Load(f)==false){
			return false;
		}
	}
	return true;
}


void	LogicDLLBaseClass::AssociateComponent	 (ComponentListContainer &List)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ComponentListContainer TmpList;
		L->AssociateComponent(TmpList);
		for(ComponentList *L=TmpList.GetFirst();L!=NULL;L=L->GetNext()){
			ComponentList	*Boss;
			for(Boss=List.GetFirst();Boss!=NULL;Boss=Boss->GetNext()){
				if(*Boss==*L){
					break;
				}
			}
			if(Boss==NULL){
				ComponentList	*d=new ComponentList(*L);
				List.AppendList(d);
			}
		}
	}
}

bool	LogicDLLBaseClass::CheckAndCreateBlobInMasterPageTable(const QSqlDatabase &db)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAndCreateBlobInMasterPageTable(db)==false){
			return false;
		}
	}
	return true;
}

int	LogicDLLBaseClass::MakeFieldList(ExcludedListPack &List)
{
	int	N=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetBlobName().isEmpty()==false){
			QString	Str("MASTERPAGE");
			List.AppendList(new ExcludedListForCheck(Str,L->GetBlobName()));
			N++;
		}
	}
	return N;
}

bool	LogicDLLBaseClass::InitialLibrary(LayersBase *Base)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->InitialLibrary(Base)==false){
			return false;
		}
	}
	return true;
}

bool	LogicDLLBaseClass::SetLanguageCode(int LanguageCode)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->SetLanguageCode(LanguageCode);
	}
	return true;
}

struct	LogicDLLPointer
{
	LogicDLL	*Point;
	uint 		Priority;
};

int	LDimFunc(const void *a ,const void *b)
{
	if(((struct LogicDLLPointer *)a)->Priority<((struct LogicDLLPointer *)b)->Priority){
		return -1;
	}
	if(((struct LogicDLLPointer *)a)->Priority>((struct LogicDLLPointer *)b)->Priority){
		return 1;
	}
	return 0;
}

bool	LogicDLLBaseClass::MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	bool	Ret=true;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(L->GetInstance());
		if(L->MakeExecuteInitialAfterEditInfo(ExeID,r,EInfo)==false){
			Ret=false;
		}
	}
	return Ret;
}

ExeResult	LogicDLLBaseClass::ExecuteInitialAfterEditPrev	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	bool	ReTryMode;

	do{
		ReTryMode=false;
		for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
			if(L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
				if(L->ExecuteMoveItemsToDispatcherForLoadingParts()==false){
					ReTryMode=true;
				}
			}
		}
	}while(ReTryMode==true);

	int	LDimNumb=GetNumber();
	struct LogicDLLPointer LDimInStackP[100];
	struct LogicDLLPointer *LDimP=LDimInStackP;
	if(LDimNumb>sizeof(LDimInStackP)/sizeof(LDimInStackP[0])){
		LDimP=new struct LogicDLLPointer[LDimNumb];
	}
	struct LogicDLLPointer LDimInStackA[100];
	struct LogicDLLPointer *LDimA=LDimInStackA;
	if(LDimNumb>sizeof(LDimInStackA)/sizeof(LDimInStackA[0])){
		LDimA=new struct LogicDLLPointer[LDimNumb];
	}
	struct LogicDLLPointer LDimInStackS[100];
	struct LogicDLLPointer *LDimS=LDimInStackS;
	if(LDimNumb>sizeof(LDimInStackS)/sizeof(LDimInStackS[0])){
		LDimS=new struct LogicDLLPointer[LDimNumb];
	}

	DWORD	ModeChanged=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeAlignment)==true){
			if(L->GetInstance()->IsEdited()==true){
				ModeChanged |=ExecuteInitialAfterEdit_ChangedAlignment;
			}
		}
	}
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeMasking)==true
		|| L->CheckAlgorithmType(AlgorithmBit_TypeDynamicMasking)==true){
			if(L->GetInstance()->IsEdited()==true){
				ModeChanged |=ExecuteInitialAfterEdit_ChangedMask;
			}
		}
	}

	int	PNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==true){
			LDimP[PNumb].Point=L;
			LDimP[PNumb].Priority=L->GetPriority(PriorityType_ExecuteInitialAfterEdit);
			PNumb++;
		}
	}
	int	ANumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeAlignment)==true
		&& L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
			LDimA[ANumb].Point=L;
			LDimA[ANumb].Priority=L->GetPriority(PriorityType_ExecuteInitialAfterEdit);
			ANumb++;
		}
	}
	int	SNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeAlignment)==false
		&& L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
			LDimS[SNumb].Point=L;
			LDimS[SNumb].Priority=L->GetPriority(PriorityType_ExecuteInitialAfterEdit);
			SNumb++;
		}
	}

	GetLayersBase()->AddMaxProcessing(-1,PNumb+ANumb+SNumb);
	if(Res!=NULL){
		QSort(LDimP,PNumb,sizeof(LDimP[0]),LDimFunc);
		do{
			ReTryMode=false;
			for(int i=0;i<PNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDimP[i].Point->GetInstance());
				DWORD	tModeChanged=ModeChanged;
				if(LDimP[i].Point->IsEdited()==true){
					tModeChanged |= ExecuteInitialAfterEdit_ChangedAlgorithm;
				}
				EInfo.ExecuteInitialAfterEdit_Changed=tModeChanged;
				ExeResult	RR=LDimP[i].Point->ExecuteInitialAfterEditPrev(ExeID,r,EInfo);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
				else{
					AlgorithmBase	*ab=LDimP[i].Point->GetInstance();
					if(ab!=NULL){
						ab->SetEdited(false);
					}
				}
				
				GetLayersBase()->StepProcessing(-1);
			}
		}while(ReTryMode==true);

		do{
			ReTryMode=false;
			for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
				if(L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
					if(L->ExecuteCopyItemsFormDispatcherForParts()==false){
						ReTryMode=true;
					}
				}
			}
		}while(ReTryMode==true);

		do{
			ReTryMode=false;
			for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
				if(L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
					if(L->ExecuteRemoveItemFormDispatcher()==false){
						ReTryMode=true;
					}
				}
			}
		}while(ReTryMode==true);

		QSort(LDimA,ANumb,sizeof(LDimA[0]),LDimFunc);
		do{
			ReTryMode=false;
			for(int i=0;i<ANumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDimA[i].Point->GetInstance());
				DWORD	tModeChanged=ModeChanged;
				if(LDimA[i].Point->IsEdited()==true){
					tModeChanged |= ExecuteInitialAfterEdit_ChangedAlgorithm;
				}
				EInfo.ExecuteInitialAfterEdit_Changed=tModeChanged;
				ExeResult	RR=LDimA[i].Point->ExecuteInitialAfterEditPrev(ExeID,r,EInfo);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
				else{
					AlgorithmBase	*ab=LDimA[i].Point->GetInstance();
					if(ab!=NULL){
						ab->SetEdited(false);
					}
				}

				GetLayersBase()->StepProcessing(-1);
			}
		}while(ReTryMode==true);

		QSort(LDimS,SNumb,sizeof(LDimS[0]),LDimFunc);
		do{
			ReTryMode=false;
			for(int i=0;i<SNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDimS[i].Point->GetInstance());
				DWORD	tModeChanged=ModeChanged;
				if(LDimS[i].Point->IsEdited()==true){
					tModeChanged |= ExecuteInitialAfterEdit_ChangedAlgorithm;
				}
				EInfo.ExecuteInitialAfterEdit_Changed=tModeChanged;
				ExeResult	RR=LDimS[i].Point->ExecuteInitialAfterEditPrev(ExeID,r,EInfo);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
				else{
					AlgorithmBase	*ab=LDimS[i].Point->GetInstance();
					if(ab!=NULL){
						ab->SetEdited(false);
					}
				}
				GetLayersBase()->StepProcessing(-1);
			}
		}while(ReTryMode==true);
	}
	if(LDimP!=LDimInStackP){
		delete	[]LDimP;
	}
	if(LDimA!=LDimInStackA){
		delete	[]LDimA;
	}
	if(LDimS!=LDimInStackS){
		delete	[]LDimS;
	}

	return _ER_true;
}


ExeResult	LogicDLLBaseClass::ExecuteInitialAfterEdit	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	bool	ReTryMode;

	do{
		ReTryMode=false;
		for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
			if(L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
				if(L->ExecuteMoveItemsToDispatcherForLoadingParts()==false){
					ReTryMode=true;
				}
			}
		}
	}while(ReTryMode==true);

	int	LDimNumb=GetNumber();
	struct LogicDLLPointer LDimInStackP[100];
	struct LogicDLLPointer *LDimP=LDimInStackP;
	if(LDimNumb>sizeof(LDimInStackP)/sizeof(LDimInStackP[0])){
		LDimP=new struct LogicDLLPointer[LDimNumb];
	}
	struct LogicDLLPointer LDimInStackA[100];
	struct LogicDLLPointer *LDimA=LDimInStackA;
	if(LDimNumb>sizeof(LDimInStackA)/sizeof(LDimInStackA[0])){
		LDimA=new struct LogicDLLPointer[LDimNumb];
	}
	struct LogicDLLPointer LDimInStackS[100];
	struct LogicDLLPointer *LDimS=LDimInStackS;
	if(LDimNumb>sizeof(LDimInStackS)/sizeof(LDimInStackS[0])){
		LDimS=new struct LogicDLLPointer[LDimNumb];
	}

	DWORD	ModeChanged=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeAlignment)==true){
			if(L->GetInstance()->IsEdited()==true){
				ModeChanged |=ExecuteInitialAfterEdit_ChangedAlignment;
			}
		}
	}
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeMasking)==true
		|| L->CheckAlgorithmType(AlgorithmBit_TypeDynamicMasking)==true){
			if(L->GetInstance()->IsEdited()==true){
				ModeChanged |=ExecuteInitialAfterEdit_ChangedMask;
			}
		}
	}

	int	PNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==true){
			LDimP[PNumb].Point=L;
			LDimP[PNumb].Priority=L->GetPriority(PriorityType_ExecuteInitialAfterEdit);
			PNumb++;
		}
	}
	int	ANumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeAlignment)==true
		&& L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
			LDimA[ANumb].Point=L;
			LDimA[ANumb].Priority=L->GetPriority(PriorityType_ExecuteInitialAfterEdit);
			ANumb++;
		}
	}
	int	SNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeAlignment)==false
		&& L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
			LDimS[SNumb].Point=L;
			LDimS[SNumb].Priority=L->GetPriority(PriorityType_ExecuteInitialAfterEdit);
			SNumb++;
		}
	}

	GetLayersBase()->AddMaxProcessing(-1,PNumb+ANumb+SNumb);
	if(Res!=NULL){
		QSort(LDimP,PNumb,sizeof(LDimP[0]),LDimFunc);
		do{
			ReTryMode=false;
			for(int i=0;i<PNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDimP[i].Point->GetInstance());
				DWORD	tModeChanged=ModeChanged;
				if(LDimP[i].Point->IsEdited()==true){
					tModeChanged |= ExecuteInitialAfterEdit_ChangedAlgorithm;
				}
				EInfo.ExecuteInitialAfterEdit_Changed=tModeChanged;
				ExeResult	RR=LDimP[i].Point->ExecuteInitialAfterEdit(ExeID,r,EInfo);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
				else{
					AlgorithmBase	*ab=LDimP[i].Point->GetInstance();
					if(ab!=NULL){
						ab->SetEdited(false);
					}
				}
				
				GetLayersBase()->StepProcessing(-1);
			}
		}while(ReTryMode==true);

		do{
			ReTryMode=false;
			for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
				if(L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
					if(L->ExecuteCopyItemsFormDispatcherForParts()==false){
						ReTryMode=true;
					}
				}
			}
		}while(ReTryMode==true);

		do{
			ReTryMode=false;
			for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
				if(L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
					if(L->ExecuteRemoveItemFormDispatcher()==false){
						ReTryMode=true;
					}
				}
			}
		}while(ReTryMode==true);

		QSort(LDimA,ANumb,sizeof(LDimA[0]),LDimFunc);
		do{
			ReTryMode=false;
			for(int i=0;i<ANumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDimA[i].Point->GetInstance());
				DWORD	tModeChanged=ModeChanged;
				if(LDimA[i].Point->IsEdited()==true){
					tModeChanged |= ExecuteInitialAfterEdit_ChangedAlgorithm;
				}
				EInfo.ExecuteInitialAfterEdit_Changed=tModeChanged;
				ExeResult	RR=LDimA[i].Point->ExecuteInitialAfterEdit	(ExeID,r,EInfo);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
				else{
					AlgorithmBase	*ab=LDimA[i].Point->GetInstance();
					if(ab!=NULL){
						ab->SetEdited(false);
					}
				}

				GetLayersBase()->StepProcessing(-1);
			}
		}while(ReTryMode==true);

		QSort(LDimS,SNumb,sizeof(LDimS[0]),LDimFunc);
		do{
			ReTryMode=false;
			for(int i=0;i<SNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDimS[i].Point->GetInstance());
				DWORD	tModeChanged=ModeChanged;
				if(LDimS[i].Point->IsEdited()==true){
					tModeChanged |= ExecuteInitialAfterEdit_ChangedAlgorithm;
				}
				EInfo.ExecuteInitialAfterEdit_Changed=tModeChanged;
				ExeResult	RR=LDimS[i].Point->ExecuteInitialAfterEdit	(ExeID,r,EInfo);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
				else{
					AlgorithmBase	*ab=LDimS[i].Point->GetInstance();
					if(ab!=NULL){
						ab->SetEdited(false);
					}
				}
				GetLayersBase()->StepProcessing(-1);
			}
		}while(ReTryMode==true);
	}
	if(LDimP!=LDimInStackP){
		delete	[]LDimP;
	}
	if(LDimA!=LDimInStackA){
		delete	[]LDimA;
	}
	if(LDimS!=LDimInStackS){
		delete	[]LDimS;
	}

	return _ER_true;
}


ExeResult	LogicDLLBaseClass::ExecuteInitialAfterEditPost(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	bool	ReTryMode;

	do{
		ReTryMode=false;
		for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
			if(L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
				if(L->ExecuteMoveItemsToDispatcherForLoadingParts()==false){
					ReTryMode=true;
				}
			}
		}
	}while(ReTryMode==true);

	int	LDimNumb=GetNumber();
	struct LogicDLLPointer LDimInStackP[100];
	struct LogicDLLPointer *LDimP=LDimInStackP;
	if(LDimNumb>sizeof(LDimInStackP)/sizeof(LDimInStackP[0])){
		LDimP=new struct LogicDLLPointer[LDimNumb];
	}
	struct LogicDLLPointer LDimInStackA[100];
	struct LogicDLLPointer *LDimA=LDimInStackA;
	if(LDimNumb>sizeof(LDimInStackA)/sizeof(LDimInStackA[0])){
		LDimA=new struct LogicDLLPointer[LDimNumb];
	}
	struct LogicDLLPointer LDimInStackS[100];
	struct LogicDLLPointer *LDimS=LDimInStackS;
	if(LDimNumb>sizeof(LDimInStackS)/sizeof(LDimInStackS[0])){
		LDimS=new struct LogicDLLPointer[LDimNumb];
	}

	DWORD	ModeChanged=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeAlignment)==true){
			if(L->GetInstance()->IsEdited()==true){
				ModeChanged |=ExecuteInitialAfterEdit_ChangedAlignment;
			}
		}
	}
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeMasking)==true
		|| L->CheckAlgorithmType(AlgorithmBit_TypeDynamicMasking)==true){
			if(L->GetInstance()->IsEdited()==true){
				ModeChanged |=ExecuteInitialAfterEdit_ChangedMask;
			}
		}
	}

	int	PNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==true){
			LDimP[PNumb].Point=L;
			LDimP[PNumb].Priority=L->GetPriority(PriorityType_ExecuteInitialAfterEdit);
			PNumb++;
		}
	}
	int	ANumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeAlignment)==true
		&& L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
			LDimA[ANumb].Point=L;
			LDimA[ANumb].Priority=L->GetPriority(PriorityType_ExecuteInitialAfterEdit);
			ANumb++;
		}
	}
	int	SNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeAlignment)==false
		&& L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
			LDimS[SNumb].Point=L;
			LDimS[SNumb].Priority=L->GetPriority(PriorityType_ExecuteInitialAfterEdit);
			SNumb++;
		}
	}

	GetLayersBase()->AddMaxProcessing(-1,PNumb+ANumb+SNumb);
	if(Res!=NULL){
		QSort(LDimP,PNumb,sizeof(LDimP[0]),LDimFunc);
		do{
			ReTryMode=false;
			for(int i=0;i<PNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDimP[i].Point->GetInstance());
				DWORD	tModeChanged=ModeChanged;
				if(LDimP[i].Point->IsEdited()==true){
					tModeChanged |= ExecuteInitialAfterEdit_ChangedAlgorithm;
				}
				EInfo.ExecuteInitialAfterEdit_Changed=tModeChanged;
				ExeResult	RR=LDimP[i].Point->ExecuteInitialAfterEditPost(ExeID,r,EInfo);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
				else{
					AlgorithmBase	*ab=LDimP[i].Point->GetInstance();
					if(ab!=NULL){
						ab->SetEdited(false);
					}
				}
				
				GetLayersBase()->StepProcessing(-1);
			}
		}while(ReTryMode==true);

		do{
			ReTryMode=false;
			for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
				if(L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
					if(L->ExecuteCopyItemsFormDispatcherForParts()==false){
						ReTryMode=true;
					}
				}
			}
		}while(ReTryMode==true);

		do{
			ReTryMode=false;
			for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
				if(L->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==false){
					if(L->ExecuteRemoveItemFormDispatcher()==false){
						ReTryMode=true;
					}
				}
			}
		}while(ReTryMode==true);

		QSort(LDimA,ANumb,sizeof(LDimA[0]),LDimFunc);
		do{
			ReTryMode=false;
			for(int i=0;i<ANumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDimA[i].Point->GetInstance());
				DWORD	tModeChanged=ModeChanged;
				if(LDimA[i].Point->IsEdited()==true){
					tModeChanged |= ExecuteInitialAfterEdit_ChangedAlgorithm;
				}
				EInfo.ExecuteInitialAfterEdit_Changed=tModeChanged;
				ExeResult	RR=LDimA[i].Point->ExecuteInitialAfterEditPost(ExeID,r,EInfo);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
				else{
					AlgorithmBase	*ab=LDimA[i].Point->GetInstance();
					if(ab!=NULL){
						ab->SetEdited(false);
					}
				}

				GetLayersBase()->StepProcessing(-1);
			}
		}while(ReTryMode==true);

		QSort(LDimS,SNumb,sizeof(LDimS[0]),LDimFunc);
		do{
			ReTryMode=false;
			for(int i=0;i<SNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDimS[i].Point->GetInstance());
				DWORD	tModeChanged=ModeChanged;
				if(LDimS[i].Point->IsEdited()==true){
					tModeChanged |= ExecuteInitialAfterEdit_ChangedAlgorithm;
				}
				EInfo.ExecuteInitialAfterEdit_Changed=tModeChanged;
				ExeResult	RR=LDimS[i].Point->ExecuteInitialAfterEditPost(ExeID,r,EInfo);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
				else{
					AlgorithmBase	*ab=LDimS[i].Point->GetInstance();
					if(ab!=NULL){
						ab->SetEdited(false);
					}
				}
				GetLayersBase()->StepProcessing(-1);
			}
		}while(ReTryMode==true);
	}
	if(LDimP!=LDimInStackP){
		delete	[]LDimP;
	}
	if(LDimA!=LDimInStackA){
		delete	[]LDimA;
	}
	if(LDimS!=LDimInStackS){
		delete	[]LDimS;
	}

	return _ER_true;
}


ExeResult	LogicDLLBaseClass::ExecuteStartByInspection(int ExeID ,ResultInspection *Res)
{
	bool	ReTryMode;

	int	LDimNumb=GetNumber();
	struct LogicDLLPointer LDimInStack[100];
	struct LogicDLLPointer *LDim=LDimInStack;
	if(LDimNumb>sizeof(LDimInStack)/sizeof(LDimInStack[0])){
		LDim=new struct LogicDLLPointer[LDimNumb];
	}

	int	LNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		LDim[LNumb].Point=L;
		LDim[LNumb].Priority=L->GetPriority(PriorityType_ExecuteStartByInspection);
		LNumb++;
	}
	QSort(LDim,LNumb,sizeof(LDim[0]),LDimFunc);
	if(Res!=NULL){
		do{
			ReTryMode=false;
			for(int i=0;i<LNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDim[i].Point->GetInstance());
				ExeResult	RR=LDim[i].Point->ExecuteStartByInspection(ExeID,r);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
			}
		}while(ReTryMode==true);
	}
	if(LDim!=LDimInStack){
		delete	[]LDim;
	}

	return _ER_true;
}
ExeResult	LogicDLLBaseClass::ExecuteCaptured	(int ExeID ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList)
{
	bool	ReTryMode;

	if(Res!=NULL){
		Res->InitialForInspection();
		Res->ClearRemarkData();

		int	LDimNumb=GetNumber();
		struct LogicDLLPointer LDimInStack[100];
		struct LogicDLLPointer *LDim=LDimInStack;
		if(LDimNumb>sizeof(LDimInStack)/sizeof(LDimInStack[0])){
			LDim=new struct LogicDLLPointer[LDimNumb];
		}

		int	LNumb=0;
		for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
			LDim[LNumb].Point=L;
			LDim[LNumb].Priority=L->GetPriority(PriorityType_ExecuteCaptured);
			LNumb++;
		}
		QSort(LDim,LNumb,sizeof(LDim[0]),LDimFunc);

		do{
			ReTryMode=false;
			for(int i=0;i<LNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDim[i].Point->GetInstance());
				ExeResult	RR=LDim[i].Point->ExecuteCaptured(ExeID,r,CapturedList);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
			}
		}while(ReTryMode==true);
		
		if(LDim!=LDimInStack){
			delete	[]LDim;
		}
	}
	return _ER_true;
}
ExeResult	LogicDLLBaseClass::ExecutePreAlignment		(int ExeID ,ResultInspection *Res)
{
	bool	ReTryMode;

	if(Res!=NULL){
		Res->InitialForInspection();
		Res->ClearRemarkData();

		int	LDimNumb=GetNumber();
		struct LogicDLLPointer LDimInStack[100];
		struct LogicDLLPointer *LDim=LDimInStack;
		if(LDimNumb>sizeof(LDimInStack)/sizeof(LDimInStack[0])){
			LDim=new struct LogicDLLPointer[LDimNumb];
		}

		int	LNumb=0;
		for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
			LDim[LNumb].Point=L;
			LDim[LNumb].Priority=L->GetPriority(PriorityType_ExecutePreAlignment);
			LNumb++;
		}
		QSort(LDim,LNumb,sizeof(LDim[0]),LDimFunc);

		do{
			ReTryMode=false;
			for(int i=0;i<LNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDim[i].Point->GetInstance());
				ExeResult	RR=LDim[i].Point->ExecutePreAlignment(ExeID,r);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
			}
		}while(ReTryMode==true);
		
		if(LDim!=LDimInStack){
			delete	[]LDim;
		}
	}
	return _ER_true;
}
ExeResult	LogicDLLBaseClass::ExecuteAlignment		(int ExeID ,ResultInspection *Res)
{
	bool	ReTryMode;

	int	LDimNumb=GetNumber();
	struct LogicDLLPointer LDimInStack[100];
	struct LogicDLLPointer *LDim=LDimInStack;
	if(LDimNumb>sizeof(LDimInStack)/sizeof(LDimInStack[0])){
		LDim=new struct LogicDLLPointer[LDimNumb];
	}

	int	LNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		LDim[LNumb].Point=L;
		LDim[LNumb].Priority=L->GetPriority(PriorityType_ExecuteAlignment);
		LNumb++;
	}
	QSort(LDim,LNumb,sizeof(LDim[0]),LDimFunc);
	if(Res!=NULL){
		do{
			ReTryMode=false;
			for(int i=0;i<LNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDim[i].Point->GetInstance());
				ExeResult	RR=LDim[i].Point->ExecuteAlignment(ExeID,r);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
			}
		}while(ReTryMode==true);
	}
	if(LDim!=LDimInStack){
		delete	[]LDim;
	}

	return _ER_true;
}
ExeResult	LogicDLLBaseClass::ExecutePreProcessing	(int ExeID ,ResultInspection *Res)
{
	bool	ReTryMode;

	int	LDimNumb=GetNumber();
	struct LogicDLLPointer LDimInStack[100];
	struct LogicDLLPointer *LDim=LDimInStack;
	if(LDimNumb>sizeof(LDimInStack)/sizeof(LDimInStack[0])){
		LDim=new struct LogicDLLPointer[LDimNumb];
	}

	int	LNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		LDim[LNumb].Point=L;
		LDim[LNumb].Priority=L->GetPriority(PriorityType_ExecutePreProcessing);
		LNumb++;
	}
	QSort(LDim,LNumb,sizeof(LDim[0]),LDimFunc);
	if(Res!=NULL){
		do{
			ReTryMode=false;
			for(int i=0;i<LNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDim[i].Point->GetInstance());
				ExeResult	RR=LDim[i].Point->ExecutePreProcessing(ExeID,r);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
			}
		}while(ReTryMode==true);
	}
	if(LDim!=LDimInStack){
		delete	[]LDim;
	}

	return _ER_true;
}
ExeResult	LogicDLLBaseClass::ExecuteProcessing		(int ExeID ,ResultInspection *Res)
{
	bool	ReTryMode;

	int	LDimNumb=GetNumber();
	struct LogicDLLPointer LDimInStack[100];
	struct LogicDLLPointer *LDim=LDimInStack;
	if(LDimNumb>sizeof(LDimInStack)/sizeof(LDimInStack[0])){
		LDim=new struct LogicDLLPointer[LDimNumb];
	}

	int	LNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		LDim[LNumb].Point=L;
		LDim[LNumb].Priority=L->GetPriority(PriorityType_ExecuteProcessing);
		LNumb++;
	}
	QSort(LDim,LNumb,sizeof(LDim[0]),LDimFunc);
	if(Res!=NULL){
		do{
			ReTryMode=false;
			for(int i=0;i<LNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDim[i].Point->GetInstance());
				ExeResult	RR=LDim[i].Point->ExecuteProcessing(ExeID,r);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
			}
		}while(ReTryMode==true);
	}
	if(LDim!=LDimInStack){
		delete	[]LDim;
	}

	return _ER_true;
}
ExeResult	LogicDLLBaseClass::ExecuteProcessingRevived(int ExeID ,ResultInspection *Res)
{
	bool	ReTryMode;

	int	LDimNumb=GetNumber();
	struct LogicDLLPointer LDimInStack[100];
	struct LogicDLLPointer *LDim=LDimInStack;
	if(LDimNumb>sizeof(LDimInStack)/sizeof(LDimInStack[0])){
		LDim=new struct LogicDLLPointer[LDimNumb];
	}

	int	LNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		LDim[LNumb].Point=L;
		LDim[LNumb].Priority=L->GetPriority(PriorityType_ExecuteProcessingRevived);
		LNumb++;
	}
	QSort(LDim,LNumb,sizeof(LDim[0]),LDimFunc);
	if(Res!=NULL){
		do{
			ReTryMode=false;
			for(int i=0;i<LNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDim[i].Point->GetInstance());
				ExeResult	RR=LDim[i].Point->ExecuteProcessingRevived(ExeID,r);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
			}
		}while(ReTryMode==true);
	}
	if(LDim!=LDimInStack){
		delete	[]LDim;
	}

	return _ER_true;
}
ExeResult	LogicDLLBaseClass::ExecutePostProcessing	(int ExeID ,ResultInspection *Res)
{
	bool	ReTryMode;

	int	LDimNumb=GetNumber();
	struct LogicDLLPointer LDimInStack[100];
	struct LogicDLLPointer *LDim=LDimInStack;
	if(LDimNumb>sizeof(LDimInStack)/sizeof(LDimInStack[0])){
		LDim=new struct LogicDLLPointer[LDimNumb];
	}

	int	LNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext(),LNumb++){
		LDim[LNumb].Point=L;
		LDim[LNumb].Priority=L->GetPriority(PriorityType_ExecutePostProcessing);
	}
	QSort(LDim,LNumb,sizeof(LDim[0]),LDimFunc);
	if(Res!=NULL){
		do{
			ReTryMode=false;
			for(int i=0;i<LNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDim[i].Point->GetInstance());
				ExeResult	RR=LDim[i].Point->ExecutePostProcessing(ExeID,r);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
			}
		}while(ReTryMode==true);
	}
	if(LDim!=LDimInStack){
		delete	[]LDim;
	}

	return _ER_true;
}
ExeResult	LogicDLLBaseClass::ExecutePreScanning		(int ExeID ,ResultInspection *Res)
{
	bool	ReTryMode;

	int	LDimNumb=GetNumber();
	struct LogicDLLPointer LDimInStack[100];
	struct LogicDLLPointer *LDim=LDimInStack;
	if(LDimNumb>sizeof(LDimInStack)/sizeof(LDimInStack[0])){
		LDim=new struct LogicDLLPointer[LDimNumb];
	}

	int	LNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		LDim[LNumb].Point=L;
		LDim[LNumb].Priority=L->GetPriority(PriorityType_ExecutePreScanning);
		LNumb++;
	}
	QSort(LDim,LNumb,sizeof(LDim[0]),LDimFunc);
	if(Res!=NULL){
		do{
			ReTryMode=false;
			for(int i=0;i<LNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDim[i].Point->GetInstance());
				ExeResult	RR=LDim[i].Point->ExecutePreScanning(ExeID,r);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
			}
		}while(ReTryMode==true);
	}
	if(LDim!=LDimInStack){
		delete	[]LDim;
	}

	return _ER_true;
}
ExeResult	LogicDLLBaseClass::ExecuteScanning		(int ExeID ,ResultInspection *Res)
{
	bool	ReTryMode;

	int	LDimNumb=GetNumber();
	struct LogicDLLPointer LDimInStack[100];
	struct LogicDLLPointer *LDim=LDimInStack;
	if(LDimNumb>sizeof(LDimInStack)/sizeof(LDimInStack[0])){
		LDim=new struct LogicDLLPointer[LDimNumb];
	}

	int	LNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		LDim[LNumb].Point=L;
		LDim[LNumb].Priority=L->GetPriority(PriorityType_ExecuteScanning);
		LNumb++;
	}
	QSort(LDim,LNumb,sizeof(LDim[0]),LDimFunc);
	if(Res!=NULL){
		do{
			ReTryMode=false;
			for(int i=0;i<LNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDim[i].Point->GetInstance());
				ExeResult	RR=LDim[i].Point->ExecuteScanning(ExeID,r);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
			}
		}while(ReTryMode==true);
	}
	if(LDim!=LDimInStack){
		delete	[]LDim;
	}

	return _ER_true;
}
ExeResult	LogicDLLBaseClass::ExecutePostScanning		(int ExeID ,ResultInspection *Res)
{
	bool	ReTryMode;

	int	LDimNumb=GetNumber();
	struct LogicDLLPointer LDimInStack[100];
	struct LogicDLLPointer *LDim=LDimInStack;
	if(LDimNumb>sizeof(LDimInStack)/sizeof(LDimInStack[0])){
		LDim=new struct LogicDLLPointer[LDimNumb];
	}

	int	LNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		LDim[LNumb].Point=L;
		LDim[LNumb].Priority=L->GetPriority(PriorityType_ExecutePostScanning);
		LNumb++;
	}
	QSort(LDim,LNumb,sizeof(LDim[0]),LDimFunc);
	if(Res!=NULL){
		do{
			ReTryMode=false;
			for(int i=0;i<LNumb;i++){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(LDim[i].Point->GetInstance());
				ExeResult	RR=LDim[i].Point->ExecutePostScanning(ExeID,r);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
			}
		}while(ReTryMode==true);
	}
	if(LDim!=LDimInStack){
		delete	[]LDim;
	}

	return _ER_true;
}

ExeResult	LogicDLLBaseClass::ExecuteManageResult	(int ExeID ,ResultInspection *Res)
{
	bool	ReTryMode;

	int	LDimNumb=GetNumber();
	struct LogicDLLPointer LDimInStack[100];
	struct LogicDLLPointer *LDim=LDimInStack;
	if(LDimNumb>sizeof(LDimInStack)/sizeof(LDimInStack[0])){
		LDim=new struct LogicDLLPointer[LDimNumb];
	}

	int	LNumb=0;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmBit_TypeManageResult)==true){
			LDim[LNumb].Point=L;
			LDim[LNumb].Priority=L->GetPriority(PriorityType_ExecuteManageResult);
			LNumb++;
		}
	}

	if(LNumb!=0){
		QSort(LDim,LNumb,sizeof(LDim[0]),LDimFunc);
		do{
			ReTryMode=false;
			for(int i=0;i<LNumb;i++){
				ExeResult	RR=LDim[i].Point->ExecuteManageResult(ExeID,Res);
				if(RR==_ER_ReqRetryLater){
					ReTryMode=true;
				}
				else if(RR!=_ER_true){
					return RR;
				}
			}
		}while(ReTryMode==true);
	}
	else{
		GetLayersBase()->StandardManageResult(Res);
	}

	if(LDim!=LDimInStack){
		delete	[]LDim;
	}

	return _ER_true;
}

ExeResult	LogicDLLBaseClass::ExecuteRemoveResult(int32 MasterCode , LotBase *Lot, int64 InspectionID ,ResultInspection *Ref)
{
	bool	ReTryMode;

	do{
		ReTryMode=false;
		for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
			ResultBaseForAlgorithmRoot	*R=Ref->GetResultBaseForAlgorithm(L->GetInstance());
			ExeResult	RR=L->GetInstance()->ExecuteRemoveResult(MasterCode , Lot , InspectionID ,R);
			if(RR==_ER_ReqRetryLater){
				ReTryMode=true;
			}
			else if(RR!=_ER_true){
				return RR;
			}
		}
	}while(ReTryMode==true);

	return _ER_true;
}

bool	LogicDLLBaseClass::LocalPos2Name(int LocalPage ,int XLocalPos, int YLocalPos ,QString &Name)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LocalPos2Name(LocalPage ,XLocalPos, YLocalPos ,Name)==true){
			return true;
		}
	}
	return false;
}


ExcludedListForCheck::ExcludedListForCheck(const QString &tableName ,const QString &fieldName)
{
	TableName=tableName;
	FieldName=fieldName;
}

bool	ExcludedListPack::IsExist(QString &tableName ,QString &fieldName)
{
	for(ExcludedListForCheck *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->FieldName.toUpper()==fieldName.toUpper() && L->TableName.toUpper()==tableName.toUpper()){
			return true;
		}
	}
	return false;
}

bool	LogicDLLBaseClass::CheckInstalledAlgorithm(RootNameListContainer &FromGUI,RootNameListContainer &LackOfAlgorithm)
{
	LackOfAlgorithm.RemoveAll();
	for(RootNameList *a=FromGUI.GetFirst();a!=NULL;a=a->GetNext()){
		if(Search(a->DLLRoot ,a->DLLName)==NULL){
			RootNameList	*b=new RootNameList();
			*b= *a;
			LackOfAlgorithm.AppendList(b);
		}
	}
	if(LackOfAlgorithm.GetNumber()!=0){
		return false;
	}
	return true;
}

bool	LogicDLLBaseClass::CheckDuplicatedAlgorithm(QStringList &Error)
{
	bool	Dup=false;
	for(LogicDLL *a=GetFirst();a!=NULL;a=a->GetNext()){
		for(LogicDLL *b=a->GetNext();b!=NULL;b=b->GetNext()){
			if(a->GetDLLRoot()==b->GetDLLRoot() && a->GetDLLName()==b->GetDLLName()){
				QString	Msg=QString("Installed duplicated algorithm (")
							+a->GetDLLRoot()
							+QString(",")
							+a->GetDLLName()
							+QString(")");
				Error.append(Msg);
				Dup=true;
			}
		}
	}
	return Dup;
}


bool	LogicDLLBaseClass::GetReflectionMap(ReflectionMode Mode ,ConstMapBuffer &Map ,int phase ,int page, int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	bool	ret=false;
	DataInPage *Dp=GetLayersBase()->GetPageDataPhase(phase)->GetPageData(page);
	if(Dp==NULL){
		return false;
	}
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()->HasReflection(Mode)==true){
			ConstMapBuffer tMap(Dp->GetDotPerLine(),Dp->GetMaxLines(),Map.GetFormat());
			if(L->GetReflectionMap(Mode,tMap ,phase,page, layer ,LibData ,Anything)==true){
				if(tMap.GetFormat()==MapBufferBase::_BitMap){
					Map|=tMap;
					ret=true;
				}
				else{
					Map.MoveFrom(tMap);
					ret=true;
				}
			}
		}
	}
	return ret;
}
bool	LogicDLLBaseClass::GetReflectionMap(ReflectionMode Mode ,ConstMapBuffer &Map ,int phase ,int page, int layer ,void *Anything)
{
	bool	ret=false;
	DataInPage *Dp=GetLayersBase()->GetPageDataPhase(phase)->GetPageData(page);
	if(Dp==NULL){
		return false;
	}
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()->HasReflection(Mode)==true){
			ConstMapBuffer tMap(Dp->GetDotPerLine(),Dp->GetMaxLines(),Map.GetFormat());
			if(L->GetReflectionMap(Mode,tMap ,phase,page, layer ,Anything)==true){
				if(tMap.GetFormat()==MapBufferBase::_BitMap){
					Map|=tMap;
					ret=true;
				}
				else{
					Map.MoveFrom(tMap);
					ret=true;
				}
			}
		}
	}
	return ret;
}

bool	LogicDLLBaseClass::GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,int phase ,int page, int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	bool	ret=false;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()->HasReflection(Mode)==true){
			VectorLineBase *tVector=Vector.CreateEmpty();
			if(L->GetReflectionVector(Mode,*tVector ,phase ,page, layer ,LibData,Anything)==true){
				Vector.AppendMoveBase(tVector);
				ret=true;
			}
			delete	tVector;
		}
	}
	return ret;
}
	
bool	LogicDLLBaseClass::GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,int phase, int page, int layer ,void *Anything)
{
	bool	ret=false;
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()->HasReflection(Mode)==true){
			VectorLineBase *tVector=Vector.CreateEmpty();
			if(L->GetReflectionVector(Mode,*tVector ,phase ,page, layer ,Anything)==true){
				Vector.AppendMoveBase(tVector);
				ret=true;
			}
			delete	tVector;
		}
	}
	return ret;
}

bool	LogicDLLBaseClass::IncludeLibInReflection(ReflectionMode Mode ,int page, int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()->HasReflection(Mode)==true){
			if(L->IncludeLibInReflection(Mode,page, layer ,LibData ,Anything)==true){
				return true;
			}
		}
	}
	return false;
}

bool	LogicDLLBaseClass::GetUsageLibInReflection(ReflectionMode Mode ,int page, int layer,AlgorithmLibraryListContainer &Ret)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()->HasReflection(Mode)==true){
			if(L->GetUsageLibInReflection(Mode,page, layer ,Ret)==true){
				return true;
			}
		}
	}
	return false;
}

void	LogicDLLBaseClass::ExecuteMove(int localPage ,int GlobalDx,int GlobalDy,bool AllItems)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()!=NULL){
			L->GetInstance()->ExecuteMove(localPage ,GlobalDx,GlobalDy,AllItems);
		}
	}
}
void	LogicDLLBaseClass::ClearResultInPhase(int phase)
{
	for(LogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()!=NULL){
			AlgorithmInPageInOnePhase	*ph=L->GetInstance()->GetPageDataPhase(phase);
			if(ph!=NULL){
				ph->ClearResult();
			}
		}
	}
}