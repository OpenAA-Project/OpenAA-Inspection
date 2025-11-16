/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XAlgorithmDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XALGORITHMDLLH
#define XALGORITHMDLLH

#include <QtGui>
#include <QColor>
#include <QString>
#include "XTypeDef.h"
#include "XDLLOnly.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XCSV.h"
#include "XDataComponent.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	AddedDataClass;
class	ResultBaseForAlgorithm;
class	ResultByAlgorithm;
class	ErrorGroupPack;
class	ShowAndSetItemsBaseClass;
class	LanguagePackage;
class	ListPhasePageLayerPack;

extern	"C"{

struct	DllToAppFuncs
{
	void		(*APP_MouseMove)(int gx ,int gy);
};

//------------------------------------------------------------

#define		AlgorithmBit_TypeCaptured			0x02000000
#define		AlgorithmBit_TypePreAlignment		0x00000001
#define		AlgorithmBit_TypeAlignment			0x00000002
#define		AlgorithmBit_TypePreProcessing		0x00000004
#define		AlgorithmBit_TypeProcessing			0x00000008
#define		AlgorithmBit_TypeProcessingRevived	0x00000010
#define		AlgorithmBit_TypePostProcessing		0x00000020
#define		AlgorithmBit_TypeNoProcessing		0x00000040
#define		AlgorithmBit_TypePieceProcessing	0x00000100
#define		AlgorithmBit_TypePreScanning		0x00000200
#define		AlgorithmBit_TypeScanning			0x00000400
#define		AlgorithmBit_TypePostScanning		0x00000800
#define		AlgorithmBit_TypeMatchAlignment		0x00001000
#define		AlgorithmBit_TypeManageResult		0x00008000
#define		AlgorithmBit_TypeMasking			0x00800000
#define		AlgorithmBit_TypeDynamicMasking		0x01000000

#define		AlgorithmBit_TypeMask				0xFFFFFF

//------------------------------------------------------------
//	Priority type bit

#define	PriorityType_ExecuteInitialAfterEdit	0x0001
#define	PriorityType_ExecuteAutoGeneration		0x0800
#define	PriorityType_ExecuteStartByInspection	0x0002
#define	PriorityType_ExecuteCaptured			0x1000
#define	PriorityType_ExecutePreAlignment		0x0004
#define	PriorityType_ExecuteAlignment			0x0008
#define	PriorityType_ExecutePreProcessing		0x0010
#define	PriorityType_ExecuteProcessing			0x0020
#define	PriorityType_ExecuteProcessingRevived	0x0400
#define	PriorityType_ExecutePostProcessing		0x0040
#define	PriorityType_ExecutePreScanning			0x0080
#define	PriorityType_ExecuteScanning			0x0100
#define	PriorityType_ExecutePostScanning		0x0200
#define	PriorityType_ExecuteManageResult		0x8000

#define	PriorityType_All						0xffff

//------------------------------------------------------------

#ifdef _MSC_VER
DEFFUNCEX	bool		DLL_GetOrganization(QString &str);
DEFFUNCEX	WORD		DLL_GetDLLType(void);
DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name);
DEFFUNCEX	WORD		DLL_GetVersion(void);
DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	void		DLL_GetUsageFiles(QStringList &RelativeFilePath);
DEFFUNCEX	bool		DLL_CheckCopyright(QString &CopyrightString);
DEFFUNCEX	const char	*DLL_GetExplain(void);
DEFFUNCEX	void		DLL_Close(void);
DEFFUNCEX	void		DLL_SetLanguageCommon(LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	void		DLL_SetLanguage		 (LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	const char	*DLL_GetBlobName(void);
DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void);
DEFFUNCEX	AlgorithmBase				*DLL_InitialAlloc(LayersBase *Base);
DEFFUNCEX	void						DLL_ReleaseAlgorithmBase(AlgorithmBase *Point);
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base);
DEFFUNCEX	int			DLL_GetPriority(int AlgorithmBit_Type);	//0:Strongest 100:Default

DEFFUNCEX	bool	DLL_GetNGTypeContainer(AlgorithmBase *ABAse 
										 , int LibID
										 , LibNGTypeInAlgorithm &NGTypeContainer);

DEFFUNCEX	bool	DLL_ExecuteMoveItemsToDispatcherForLoadingParts(AlgorithmBase *base);
DEFFUNCEX	bool	DLL_ExecuteCopyItemsFormDispatcherForParts(AlgorithmBase *base);
DEFFUNCEX	bool	DLL_ExecuteRemoveItemFormDispatcher(AlgorithmBase *base);

DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEdit	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
DEFFUNCEX	ExeResult	DLL_ExecuteStartByInspection(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteCaptured			(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res ,ListPhasePageLayerPack &CapturedList);
DEFFUNCEX	ExeResult	DLL_ExecutePreAlignment		(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteAlignment		(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePreProcessing	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessing		(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingRevived(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePostProcessing	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePreScanning		(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteScanning			(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePostScanning		(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteManageResult		(int ExeID ,AlgorithmBase *base,ResultInspection *Res);

DEFFUNCEX	ExeResult	DLL_ExecuteMatch			(int ExeID ,AlgorithmBase *InstBase,ImagePointerContainer &TargetImages,int cx, int cy ,double &Result);

DEFFUNCEX	bool	DLL_DrawResultBase(int32 ShowFixedPhase,AlgorithmBase *InstBase ,ResultBaseForAlgorithmRoot *Res,QPainter &PntFromIData ,QImage *IData ,int MovX ,int MovY ,double ZoomRate ,int localPage);
DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data ,ShowAndSetItemsBaseClass *Something);
DEFFUNCEX	void	DLL_MakeIndependentItems(int32 TargetPhase,int32 localPage ,bool SubResultMoving, int localX ,int localY,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
DEFFUNCEX	void	DLL_SetIndependentItemData(int32 Command
									,AlgorithmBase *InstBase ,int32 TargetPhase,int32 LocalPage,int32 Layer,int32 ItemID
									,AlgorithmItemRoot *Data
									,IntList &EdittedMemberID
									,QByteArray &Something
									,QByteArray &AckData);
DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos 
										 ,DetailResultInfoListContainer &RetList);

DEFFUNCEX	QWidget	*DLL_ChangeItemsAttr(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item);
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase);
DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent);

DEFFUNCEX	bool	DLL_ReleaseGeneralAlgorithmData(AlgorithmBase *InstBase ,int32 Command,void *data);
DEFFUNCEX	void	*DLL_CreateGeneralAlgorithmData(AlgorithmBase *InstBase ,int32 Command,void *reqdata);
DEFFUNCEX	bool	DLL_LoadGeneralAlgorithmData(AlgorithmBase *InstBase ,QIODevice *f,int32 Command ,void *data);
DEFFUNCEX	bool	DLL_SaveGeneralAlgorithmData(AlgorithmBase *InstBase ,QIODevice *f,int32 Command ,void *data);
DEFFUNCEX	bool	DLL_ReplyGeneralAlgorithmData(AlgorithmBase *InstBase ,int32 Command ,void *data);

DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuf);
DEFFUNCEX	bool	DLL_BindSpecialResult(ResultInItemRoot *ItemRes ,ErrorGroupPack &Dest);

DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

DEFFUNCEX	AlignmentPacketBase	*DLL_GetAlignmentPointer(AlgorithmBase *base ,int localPage, int localX ,int localY ,AlgorithmItemRoot *Item ,bool FromGlobal);
DEFFUNCEX	void		DLL_GetAlignmentForProcessing		 (AlgorithmBase *base ,int localPage, AlignmentPacketBase &Packet);

DEFFUNCEX	bool	DLL_IsEdited(AlgorithmBase *InstBase);
DEFFUNCEX	bool	DLL_IsCalcDone(AlgorithmBase *InstBase);
DEFFUNCEX	void	DLL_SetEdited(AlgorithmBase *InstBase,bool edited);
DEFFUNCEX	void	DLL_SetCalcDone(AlgorithmBase *InstBase,bool calcdone);

DEFFUNCEX	bool	DLL_SaveCSVMasterReport(AlgorithmBase *InstBase, QStringListListCSV &CSVData);
DEFFUNCEX	bool	DLL_ReceivePacketDirectCommAlgo(AlgorithmBase *ABase 
													,LayersBase *Base
													,int32 cmd 
													,int32 globalPage 
													,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName
													,QBuffer &buff
													,int32 IDForUndo
													,ErrorCodeList &ErrorData);

DEFFUNCEX	bool	DLL_Name2GloalPos(AlgorithmBase *Base ,QString Name ,int &XGlobalPos, int &YGlobalPos);
DEFFUNCEX	bool	DLL_Name2LocalPos(AlgorithmBase *Base ,QString Name ,int &Page ,int &XLocalPos, int &YLocalPos);
DEFFUNCEX	bool	DLL_LocalPos2Name(AlgorithmBase *Base ,int Page ,int XLocalPos, int YLocalPos ,QString &Name);
DEFFUNCEX	bool	DLL_GlobalPos2Name(AlgorithmBase *Base ,int XGlobalPos, int YGlobalPos ,QString &Name);
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer);

DEFFUNCEX	void	DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);
#endif

};

#endif