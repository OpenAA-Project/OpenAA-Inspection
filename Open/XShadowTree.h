#pragma once

#include <QString>
#include <QIODevice>
#include <QImage>
#include <QPainter>
#include <QFile>
#include "XTypeDef.h"
#include "XServiceForLayers.h"
#include "NList.h"
#include "XParamGlobal.h"
#include "XDataAlgorithmPipe.h"

class	AlgorithmInPageRoot;
class	AlgorithmInLayerRoot;
class	AlgorithmItemRoot;
class	ShadowControlInterface;
class	ShadowControlInterfaceContainer;
class   LayersBase;
class   ListPhasePageLayerPack;
class   LogicDLL;
class   XDateTime;
class   ResultInspectionForStockPointerContainer;
class   ResultInspection;
class   DataInPage;
class	FileThread;
class	ExecuteInitialAfterEditInfo;
class	LibInfoListContainer;
class	LibDataList;
class	ResultDLL;
class	LogicDLL;

class LayersBasePointerList : public NPList<LayersBasePointerList>
{
public:
	LayersBase	*Base;

	explicit	LayersBasePointerList(LayersBase *b):Base(b){}
};


class	ShadowTree : public NPList<ShadowTree> ,public PipeShadowTree
{
	ShadowControlInterface	*ShadowInterface;
	LayersBase				*LayersBasePointer;
	LayersBase				*ParentPointer;

	ShadowControlInterfaceContainer	*Children;

	QString	ShadowDLLFileName;
	QString	ShadowGlobalFileName;
	QString	ShadowGUIFileName;
	ShadowParameter	Param;
	int		ShadowNumber;
public:

	ShadowTree(int ShadowNumber ,LayersBase *ParentBase);
	ShadowTree(const ShadowTree &src);
	virtual	~ShadowTree(void);

	void	SetInterface(ShadowControlInterface *iface);
	ShadowControlInterface	*GetShadowInterface(void);
	bool	LoadShadowChildrenDLL(void);

	virtual	bool	InitialInShadow(void);

	ShadowTree	&operator=(const ShadowTree &src);
	virtual	int		GetIDInClass(void)		const;
	virtual	int		GetLevel(void)			const;
	virtual	int		GetUniqueID(void)		const;
	int				GetShadowNumber(void)	const{	return ShadowNumber;	}

	QString	GetShadowDLLFileName(void)		const;
	QString	GetShadowGlobalFileName(void)	const;
	QString	GetShadowGUIFileName(void)		const;
	QString	GetShadowParamFileName(void)	const;

	void	SetShadowDLLFileName	(const QString &filename);
	void	SetShadowGlobalFileName	(const QString &filename);
	void	SetShadowGUIFileName	(const QString &filename);
	void	SetParam(const ShadowParameter &s);

	virtual	bool	SaveShadowParam(QIODevice *f);
	virtual	bool	LoadShadowParam(QIODevice *f);

	int		GetShadowChildrenCount(void)		const;
	int		GetShadowTotalChildrenCount(void)	const;
	int		GetShadowLevel(void)				const;	//Top:0
	ShadowTree	*GetShadowChildren(int n)		const;
	ShadowTree	*FindShadowTree(int UniqueID)	const;
	LayersBase	*GetShadowTree(int ShadowLevel ,int ShadowNumber)	const;
	LayersBase	*GetTopLayersBase(void)			const;
	LayersBase	*GetParentLayersBase(void)		const	{	return ParentPointer;		}
	LayersBase	*GetTreeLayersBase(void)		const	{	return LayersBasePointer;	}
	void		SetTreeLayersBase(LayersBase *s);
	virtual	void	ShowShadow(void){}

	void	CopyParamGlobalFromParent(void);
	virtual	void	ChildCopyParamGlobalFromParent(ParamGlobal *ParentParam){}
	void	CopyShadowTreeParamResultDLL(ResultDLL *SrcParent);
	virtual	void	ChildCopyShadowTreeParamResultDLL(ResultDLL *Parent);
	void	CopyShadowTreeParamLogicDLL(LogicDLL *SrcParent);

	virtual	void	ConvertToTop(int32 &x ,int32 &y){}
	virtual	void	ConvertToLocal(int32 &TopX ,int32 &TopY){}

	virtual	ExeResult	ChildrenExecuteInitialAfterEdit	(ExecuteInitialAfterEditInfo &EInfo,bool ProgressStep=true);
	virtual	ExeResult	ChildrenExecuteStartByScanOnly	(bool ProgressStep=true);
	virtual	ExeResult	ChildrenExecuteStartByInspection(bool ProgressStep=true);
	virtual	ExeResult	ChildrenExecuteCaptured			(ListPhasePageLayerPack &CapturedList ,bool ProgressStep=true);
	virtual	ExeResult	ChildrenExecutePreAlignment		(bool ProgressStep=true);
	virtual	ExeResult	ChildrenExecuteAlignment		(bool ProgressStep=true);
	virtual	ExeResult	ChildrenExecutePreProcessing	(bool ProgressStep=true);
	virtual	ExeResult	ChildrenExecuteProcessing		(bool ProgressStep=true);
	virtual	ExeResult	ChildrenExecuteProcessingRevived(bool ProgressStep=true);
	virtual	ExeResult	ChildrenExecutePostProcessing	(bool ProgressStep=true);
	virtual	ExeResult	ChildrenExecutePreScanning		(bool ProgressStep=true);
	virtual	ExeResult	ChildrenExecuteScanning			(bool ProgressStep=true);
	virtual	ExeResult	ChildrenExecutePostScanning		(bool ProgressStep=true);
	virtual	ExeResult	ChildrenPretendFinishProcessing	(bool ProgressStep=true);

	virtual	void	SetMasterCodeInTree(int MasterCode);
	virtual	bool	ReallocateShadow(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	virtual	bool	ReallocateShadow(int newPhaseNumb);
	virtual	bool	ReallocXYPixelsShadow(int NewDotPerLine ,int NewMaxLines);
	virtual	bool	ReallocateMasterCountShadow(int CountMaster);
	virtual	bool	InsertPageShadow(int IndexPage);	//Create page before Indexed page
	virtual	bool	RemovePageShadow(int IndexPage);

	void		ShadowSetResultReceivedFlag(int Page);

	void	GatherUsedLibInfoList(LibInfoListContainer &Ret);
	void	SetLibDataList(LibDataList &src);	

	void	CopyShadowMasterToChildren(void);
	void	MakeShadowLayersBasePointer(NPListPack<LayersBasePointerList> &ShadowLayersBasePointer);
	void	CopyShadowImageFromParent(bool Mastered ,int MasterNo
									 ,int Phase ,int Page);
	virtual	void	CopyShadowImageFromParentInChild(bool Mastered 
													,int MasterNo
													,DataInPage *SrcPg
													,int Phase ,int Page){}
	void	ShadowCopyPageData(int DstPage ,int SrcPage ,bool ModeCopyAllAlgorithm=true ,bool ModeCopyAllFilter=true);

	bool	CopyShadowAlgorithmToChildren(void);
	virtual	bool	CopyShadowAlgorithmBase (ShadowTree *Child,const AlgorithmBase &ParentABase, AlgorithmBase *ChildBase);
	virtual	bool	CopyShadowAlgorithmPage	(const AlgorithmInPageRoot &ParentAPage	, AlgorithmInPageRoot *ChildPage);
	virtual	bool	CopyShadowAlgorithmLayer(const AlgorithmInLayerRoot &ParentALayer	, AlgorithmInLayerRoot *ChildLayer);
	virtual	bool	CopyShadowAlgorithmItem	(AlgorithmParentFromItem *ParentG	, const AlgorithmItemRoot &ParentItem);

	bool	SaveShadowChildrenGUIContent(int _MachineID,const QString &ImagePath);
	bool	LoadShadowChildrenGUIContent(int _MachineID);

	bool	SaveShadowParamInChildren(QIODevice *f);
	bool	LoadShadowParamInChildren(QIODevice *f);
	bool	SaveShadowMasterImageFileInChildren(int32 masterCode, int32 machineID
											,const QString &ImagePath,bool ForceSave
											,int LocalPhase,int LocalPage);
	bool	LoadShadowMasterImageFileInChildren(int32 masterCode, int32 machineID
											,const QString &ImagePath
											,int LocalPhase,int LocalPage);
	bool	SaveShadowLogicFileInChildren(int32 masterCode,int32 machineID
											,const QString &ImagePath
											,int LocalPhase,int LocalPage);
	bool	LoadShadowLogicFileInChildren(int32 masterCode,int32 machineID, int DataVersion
											,const QString &ImagePath
											,int LocalPhase,int LocalPage);

	void	ShadowSetMasterImageChanged(bool b,int LocalPhase,int LocalPage);

	bool	ShadowOutputResult(ResultInspection *ParentResultInspection
								,const QString &LotID,int LocalPhase,int LocalPage
								,QIODevice &File);
	bool	ShadowOutputResult(ResultInspection *ParentResultInspection
								,const QString &LotID,int LocalPhase,int LocalPage
								,FileThread &File);
	int		ShadowGetNGImageCount(ResultInspection *ParentResultInspection
								,const QString &LotID,int LocalPhase,int LocalPage);
	bool	ShadowWriteNGImage(ResultInspection *ParentResultInspection
								,const QString &LotID,int LocalPhase,int LocalPage
								,QIODevice &File);
	bool	ShadowSaveNGImage(ResultInspection *ParentResultInspection
								,const QString &LotID,int LocalPhase,int LocalPage
								,QFile &File);

	bool	ShadowWriteNGImage(ResultInspection *ParentResultInspection
								,const QString &LotID,int LocalPhase,int LocalPage
								,FileThread &File);
	bool	ShadowSaveNGImage(ResultInspection *ParentResultInspection
								,const QString &LotID,int LocalPhase,int LocalPage
								,FileThread &File);

	void	ShadeMakeImageNGCircle(QImage *tNGData ,QPainter *tPntFromNGData
									,int dtype		//DisplayImage::DisplayType
									,int Gx1,int Gy1 ,int Gx2,int Gy2
									,int MovX,int MovY, double ZoomRate
									,int localPage
									,bool RedCircleMode
									,bool ShowNGMarkInTarget
									,bool &RetNGData);
	void	SetThresholdLevelShadowTree(int LevelParentID ,int LevelID);
	bool	GetShadowResult(ResultInspection *ParentResultInspection
							,bool3 &Ok ,bool &TimeOver, bool &MaxError
							,bool DependOnPhaseMode,bool DependOnPageMode);
	void	ShowShadowHistory(int ResultCode
							, bool DependOnPhaseMode,bool DependOnPageMode
							, DWORD InspectionTimeMilisec);

	void	WriteResultShadowForceWriteCommon(ResultInspectionForStockPointerContainer &ShadowResStocks);
	void	WriteResultShadowStockedWriteCommon(ResultInspectionForStockPointerContainer &ShadowResStocks);
	void	WriteResultShadowPickupForWriteInSlave(ResultInspectionForStockPointerContainer &ShadowResStocks
													,const XDateTime &InspectedTime);
	void	WriteResultShadowCastAll(void);
	int		GetWriteResultShadowStockedCount(void);
	void	WriteResultSlaveWriteThreadLoop(void);

	void	ShadowBroadcastRefreshCache(void);
	void	ShadowBroadcastRepaintAll(void);
	void	ShadowBroadcastShowInPlayer(int64 shownInspectionID);
	void	ShadowBroadcastOnTheWayInPlayer(int64 shownInspectionID);
	void	ShadowBroadcastRunByEveryInspection(int64 shownInspectionID);
	void	ShadowBroadcastShowInEdit(void);
	void	ShadowSetStartInspectionTimeMilisec(DWORD	s);
private:
	ShadowTree	*GetShadowTreeInner(int ShadowLevel ,int ShadowNumber)	const;
	ShadowTree	*FindShadowTreeInner(int UniqueID)	const;

	void	CopyMasterFromParant(void);
	bool	SaveShadowChildrenGUIContent(int _MachineID,const QString &ImagePath ,int _ShadowNumber);
	bool	LoadShadowChildrenGUIContent(int _MachineID,int _ShadowNumber);

	bool	SaveShadowMasterImageFileInChildren(int32 masterCode, int32 machineID
											,const QString &ImagePath,bool ForceSave
											,int LocalPhase,int LocalPage,int _ShadowNumber);
	bool	LoadShadowMasterImageFileInChildren(int32 masterCode, int32 machineID
											,const QString &ImagePath
											,int LocalPhase,int LocalPage,int _ShadowNumber);
	bool	SaveShadowLogicFileInChildren(int32 masterCode, int32 machineID
											,const QString &ImagePath
											,int LocalPhase,int LocalPage,int _ShadowNumber);
	bool	LoadShadowLogicFileInChildren(int32 masterCode, int32 machineID, int DataVersion
											,const QString &ImagePath
											,int LocalPhase,int LocalPage,int _ShadowNumber);
	void	ShadowSetMasterImageChangedInChildren(bool b,int LocalPhase,int LocalPage);

	bool	GetShadowResultInChildren(ResultInspection *Res
									,bool3 &Ok ,bool &TimeOver, bool &MaxError
									,bool DependOnPhaseMode,bool DependOnPageMode);
	void	ShowShadowHistoryInChildren(int ResultCode
										,bool DependOnPhaseMode,bool DependOnPageMode
										,DWORD InspectionTimeMilisec);
	void	WriteResultShadowForceWriteCommonInChildren(ResultInspectionForStockPointerContainer &ShadowResStocks);
	void	WriteResultShadowStockedWriteCommonInChildren(ResultInspectionForStockPointerContainer &ShadowResStocks);
	void	WriteResultShadowPickupForWriteInSlaveInChildren(ResultInspectionForStockPointerContainer &ShadowResStocks
															,const XDateTime &InspectedTime);
	void	WriteResultShadowCastAllInChildren(void);
	int		GetWriteResultShadowStockedCountInChildren(void);
	void	WriteResultSlaveWriteThreadLoopInChildren(void);

	bool	ShadowOutputResultInChildren(ResultInspection *Res
								,const QString &LotID,int LocalPhase,int LocalPage
								,QIODevice &File);
	bool	ShadowOutputResultInChildren(ResultInspection *Res
								,const QString &LotID,int LocalPhase,int LocalPage
								,FileThread &File);
	int		ShadowGetNGImageCountInChildren(ResultInspection *Res
								,const QString &LotID,int LocalPhase,int LocalPage);
	bool	ShadowWriteNGImageInChildren(ResultInspection *Res
								,const QString &LotID,int LocalPhase,int LocalPage
								,QIODevice &File);
	bool	ShadowSaveNGImageInChildren(ResultInspection *Res
								,const QString &LotID,int LocalPhase,int LocalPage
								,QFile &File);
	bool	ShadowWriteNGImageInChildren(ResultInspection *Res
								,const QString &LotID,int LocalPhase,int LocalPage
								,FileThread &File);
	bool	ShadowSaveNGImageInChildren(ResultInspection *Res
								,const QString &LotID,int LocalPhase,int LocalPage
								,FileThread &File);

protected:
	virtual	void	ShadeMakeImageNGCircleInChild(QImage *tNGData ,QPainter *tPntFromNGData
									,int dtype		//DisplayImage::DisplayType
									,int Gx1,int Gy1 ,int Gx2,int Gy2
									,int MovX,int MovY, double ZoomRate
									,int localPage
									,bool RedCircleMode
									,bool ShowNGMarkInTarget
									,bool &RetNGData
									,int ShadowNumber){}
	virtual	bool	ReallocateShadowInChild(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	virtual	bool	ReallocateShadowInChild(int newPhaseNumb);
	virtual	bool	ReallocXYPixelsShadowInChild(int NewDotPerLine ,int NewMaxLines);
	virtual	void	InsertPageShadowInChild(int IndexPage);	//Create page before Indexed page
	virtual	void	RemovePageShadowInChild(int IndexPage);
};
