#if	!defined(XLEARNINGREGIST_H)
#define	XLEARNINGREGIST_H

#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include <QIODevice>
#include <QString>
#include "XTypeDef.h"
#include "XDateTime.h"
#include "XDataInLayer.h"
#include "XBoolList.h"
#include "XDualIntList.h"
#include "XEntryPoint.h"
#include "XDLLType.h"

class	ImageBuffer;
class	LayersBase;
class	AlignmentPacket2D;
class	FlexArea;
class	LeariningGUIInitializer;
class	AlignmentPacket2D;
class	ExecuteInitialAfterEditInfo;
class	AlgorithmLibraryListContainer;
class	AlgorithmThreshold;

class	LearningMenu
{
public:
	QString	MenuMessage;
	int		MenuID;
	bool	OkMode;		//NG->OK

	LearningMenu	&operator=(const LearningMenu &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	LearningResource
{
public:
    int32	x1,y1,x2,y2;//検査画像上のページ内位置
	QImage	Image;
	int		Cause[2];
	double	DoubleCause;
	int		Hx,Hy;		//Shift by itself

	LearningResource	&operator=(const LearningResource &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	LearningImage : public NPList<LearningImage>,public EntryPointBase
{
	LayersBase	*Base;

	ImageBuffer	*SavedImage;
	ImageBuffer	*SavedMasterImage;
	int			ShowingShiftX,ShowingShiftY;

	XDateTime	CreatedTime;
	int			GlobalPage;

	class	LNLayersBase : public LayersBase
	{
		LearningImage	*Parent;
	public:
		LNLayersBase(LearningImage *parent,LayersBase *ParentLayer);

		bool	Set(LayersBase *Base,LearningImage *parent);
		void	SetIndexedToTargetBuff(ImageBuffer *SrcBuffPointer[]
										,int SrcX1 ,int SrcY1 ,int SrcX2 ,int SrcY2);

		ImageBuffer	&GetMasterBuff(int layer);
	};
	LNLayersBase			*LearningLayersBase;

	int			OrgLocalX1 ,OrgLocalY1 ,OrgLocalX2 ,OrgLocalY2;

	bool		ShowingTarget;
	bool		ShowingMaster;
	AlignmentPacket2D	*AVector;

public:
	BoolList	MarkToProceed;
	BoolList	ResultMark;

	LearningImage(LayersBase *Base);
	~LearningImage(void);

	bool	SetAllocImage(const XDateTime &_CreatedTime ,int GlobalPage
						, int LocalX1 ,int LocalY1 ,int LocalX2 ,int LocalY2
						, AlignmentPacket2D *Align);

	void	SetImageToMasterOrg(void);
	void	RestoreToMasterOrg(void);
	void	SetImageToTargetOrg(AlignmentPacket2D *Align);
	void	RestoreToTargetOrg(void);
	
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
	bool	SaveAlgorithm(QIODevice *f, const QString &AlgoBlobName);
	bool	LoadAlgorithm(QIODevice *f, const QString &AlgoBlobName);

	LayersBase	*GetLearningLayersBase(void)	const	{	return LearningLayersBase;		}
	bool	IsIncludeOrg(int LocalX ,int LocalY);
	bool	GetMarkToProceed(int layer)			const	{	return MarkToProceed[layer];	}
	void	SetMarkToProceed(int layer ,bool b);
	void	SetResultMarkForLearning(int layer ,int x ,int y);

	XDateTime	&GetCreatedTime(void){	return CreatedTime;			}
	int		GetWidth(void)					const	{	return OrgLocalX2-OrgLocalX1;	}
	int		GetHeight(void)					const	{	return OrgLocalY2-OrgLocalY1;	}
	void	GetOrgCenter(int &Cx, int &Cy)	const;
	void	GetOrgLocalArea(int &x1, int &y1 , int &x2 ,int &y2)	const;
	int		GetLayerNumb(void)		const;
	bool	GetShowingTarget(void)	const	{	return ShowingTarget;	}
	bool	GetShowingMaster(void)	const	{	return ShowingMaster;	}
	int		GetGlobalPage(void)		const	{	return GlobalPage;		}

	void	DrawImage(QImage &Img, int movx ,int movy ,double ZoomRate
					,const QColor &LColor
					,int OffsetX ,int OffsetY);

	void	DrawThumnailImage(QImage &Img, int ImageWidth ,int ImageHeight);

	void	ExecuteInitialAfterEdit	(ExecuteInitialAfterEditInfo &EInfo,bool ProgressStep=true);
	void	ExecuteStartByScanOnly	(bool ProgressStep=true);
	void	ExecuteStartByInspection(bool ProgressStep=true);
	void	ExecuteCaptured			(ListPhasePageLayerPack &CapturedList ,bool ProgressStep=true);
	void	ExecutePreAlignment		(bool ProgressStep=true);
	void	ExecuteAlignment		(bool ProgressStep=true);
	void	ExecutePreProcessing	(bool ProgressStep=true);
	void	ExecuteProcessing		(bool ProgressStep=true);
	void	ExecuteProcessingRevived(bool ProgressStep=true);
	void	ExecutePostProcessing	(bool ProgressStep=true);
	void	ExecutePreScanning		(bool ProgressStep=true);
	void	ExecuteScanning			(bool ProgressStep=true);
	void	ExecutePostScanning		(bool ProgressStep=true);

	//---------------------------------------------------------------
	LayersBase			*GetLayersParentBase(void)	const	{	return Base;	}
	virtual	LayersBase			*GetLayersBase(void)		const	override{	return LearningLayersBase;	}
	virtual	ThreadSequence		*GetThreadSequence(void)	const	override{	return NULL;	}
	virtual	ExecuteInspectBase	*GetExecuteInspect(void)	const	override{	return NULL;	}
	virtual	void		SetLanguageCode(int LanguageCode)			override{}
	virtual	PieceClass			*SearchAndLoadPiece(int masterCode,QString &ErrorMessageOfFalse)	override{	return NULL;	}

	virtual	bool	SendData (int32 commID ,int privatePage
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QBuffer *f 
								,ErrorCodeList &ErrorData)	override;
	virtual	bool	SendDataDirectComm(int32 commID ,int privatePage
										,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
										,QBuffer *f 
										,ErrorCodeList &ErrorData)	override;
	virtual	bool	SendIntegrationData (int slaveNo
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QBuffer *f ,ErrorCodeList &ErrorData)	override;

	virtual	bool	SendArray(int32 commID ,int privatePage
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QByteArray *f
								,ErrorCodeList &ErrorData)	override;
	virtual	void	ReadyReadDirectComm(void)	override;

	virtual	QTcpSocket	*GetSocket(int ComNo)											override{	return NULL;	}
	virtual	QTcpSocket	*GetIntegrationSocket(int slaveNo)								override{	return NULL;	}
	virtual	GUIFormBase	*GUIMouseLeftDownInEdit(GUIFormBase *Current ,QMouseEvent * Event)	override{	return NULL;	}
	virtual	void	GUISetProperty(GUIFormBase *Current,GUIFormBase *PutTop)	override{}
	virtual	bool	GUIIsEditMode(void)					override{	return false;	}
	virtual	void	GUIRemoveItem(GUIFormBase *w)		override{}
	virtual	GUIInstancePack		*GetGUIInstancePack(void)override;

	virtual	DirectComm			*CreateDirectComm(QObject * parent)override{	return NULL;	}
	virtual	bool				InitialDirectCommInSlave(DirectComm	*p,QObject * parent ,SystemConnectionInfoContainer &)override{	return true;	}

	virtual	int					GetDirectCommIDFromGlobalPage(int globalPageTo)		override				{	return 0;		}
	virtual	void	WaitReadyReadAll(int milisec)				override{}
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override{}
	virtual	void	LoopOnIdle(void)	override{}
private:

};
inline	void	LearningImage::SetMarkToProceed(int layer ,bool b)
{	
	if(MarkToProceed.GetItem(layer)!=NULL){
		MarkToProceed.GetItem(layer)->SetValue(b);
	}
	else{
		while(MarkToProceed.GetItem(layer)==NULL){
			MarkToProceed.Add(b);
		}
	}
}

class	LearningRegister : public ServiceForLayers
{
public:
	LearningRegister(LayersBase *Base);


	void	InitialInSystem(GUICmdPacketBasePointerListContainer &GUICmdContainer);

	bool	RegistForLearning(int GlobalX1 ,int GlobalY1 ,int GlobalX2 ,int GlobalY2
							, bool OkMode
							,AlgorithmLibraryListContainer &LibList
							,int Priority
							,FlexArea &PointArea);
	bool	RegistForLearning(int GlobalX1 ,int GlobalY1 ,int GlobalX2 ,int GlobalY2
							, bool OkMode
							,AlgorithmItemRoot *Item
							,int Priority);

	bool	GetLearningArea( int GlobalCx ,int GlobalCy
							,int &RetGlobalX1 ,int &RetGlobalY1 ,int &RetGlobalX2 ,int &RetGlobalY2);

	int		GetLearningMenu(int LibType
							,LearningMenu LearningMenuDim[]
							,int MaxMenuDim);
private:
	int		SaveForLearning(int GlobalX1 ,int GlobalY1 ,int GlobalX2 ,int GlobalY2
							, bool OkMode,int Priority);

	bool	RemoveLearning(int LearningID);
};

class LearningParamInDB : public NPListSaveLoad<LearningParamInDB>
{
public:
	int			ParamID	;
	int			LibType	;
	int			LibID	;
	QByteArray	ParamData;
	DetailResultInfoListContainer ResultList;

	LearningParamInDB(void);
	LearningParamInDB(const LearningParamInDB &src);

	LearningParamInDB	&operator=(const LearningParamInDB &src);
	bool	operator==(const LearningParamInDB &src);
	bool	operator!=(const LearningParamInDB &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class LearningInDB : public NPListPackSaveLoad<LearningParamInDB>
					,public NPList<LearningInDB>
{
public:
	int			LearningID	;
	int			MachineID	;
	QDateTime	UpdateTime	;
	int			MasterCode	;
	int			SampleType	;
	int			Priority	;
	int			Version		;
	int			XSize		;
	int			YSize		;
	int			Layer		;
	QByteArray	MasterImage	;
	QByteArray	TargetImage	;
	QByteArray	PointData	;
	QByteArray	Alignment	;

	LayersBase		*LayerForCalc	;
	EntryPointBase	*EPointForCalc	;

	int			Result;

	LearningInDB(void);
	LearningInDB(const LearningInDB &src);
	~LearningInDB(void);

	LearningInDB	&operator=(const LearningInDB &src);
	bool	operator==(const LearningInDB &src);
	bool	operator!=(const LearningInDB &src);

	virtual	LearningParamInDB	*Create(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class LearningInDBAll : public NPListPack<LearningInDB>
{
public:
	LearningInDBAll(void);
	LearningInDBAll(const LearningInDBAll &src);

	LearningInDBAll	&operator=(const LearningInDBAll &src);
	bool	operator==(const LearningInDBAll &src);
	bool	operator!=(const LearningInDBAll &src);

	LearningInDB	*Search(int LearningID);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class LearningInDBThresholdParamBase : public NPList<LearningInDBThresholdParamBase>
{
public:
	LearningInDBThresholdParamBase(void){}

	virtual	void	StepStrict(AlgorithmThreshold *Thr,double Level)	=0;
	virtual	void	StepLoose (AlgorithmThreshold *Thr,double Level)	=0;

	virtual	void	BackupValue(AlgorithmThreshold *Thr)	=0;
	virtual	void	RestoreValue(AlgorithmThreshold *Thr)	=0;
};
template<class T>
class LearningInDBThresholdParam : public LearningInDBThresholdParamBase
{
	int		Offset;

	T	OldValue;
	T	Value;
	T	MinValue;
	T	MaxValue;
	double	StepOffset;
	double	StepMultiply;
public:
	LearningInDBThresholdParam(void)		{	Offset=0;	}
	virtual	~LearningInDBThresholdParam(void);

	void	SetLearningParam(AlgorithmThreshold *Thr ,T *value	,T MinValue,T MaxValue	,double stepoffset,double stepmultiply	);

	virtual	void	StepStrict(AlgorithmThreshold *Thr,double Level)	override;
	virtual	void	StepLoose (AlgorithmThreshold *Thr,double Level)	override;

	virtual	void	BackupValue(AlgorithmThreshold *Thr)	override;
	virtual	void	RestoreValue(AlgorithmThreshold *Thr)	override;
};

class LearningInDBThresholdGroup : public LearningInDBThresholdParamBase
{
	NPListPack<LearningInDBThresholdParamBase>	Container;
public:
	LearningInDBThresholdGroup(void);

	void	AddLearningParam(AlgorithmThreshold *Thr ,char *value	,char MinValue,char MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,BYTE *value	,BYTE MinValue,BYTE MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,short *value	,short MinValue,short MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,WORD *value	,WORD MinValue,WORD MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,int32 *value	,int32 MinValue,int32 MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,DWORD *value	,DWORD MinValue,DWORD MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,int64 *value	,int64 MinValue,int64 MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,float *value	,float MinValue,float MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,double *value	,double MinValue,double MaxValue,double stepoffset,double stepmultiply	);

	virtual	void	StepStrict(AlgorithmThreshold *Thr,double Level)	override;
	virtual	void	StepLoose (AlgorithmThreshold *Thr,double Level)	override;

	virtual	void	BackupValue(AlgorithmThreshold *Thr)	override;
	virtual	void	RestoreValue(AlgorithmThreshold *Thr)	override;
};

class LearningInDBThreshold : public NPListPack<LearningInDBThresholdParamBase>
{
public:
	LearningInDBThreshold(void);

	void	AddLearningParam(AlgorithmThreshold *Thr ,char *value	,char MinValue,char MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,BYTE *value	,BYTE MinValue,BYTE MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,short *value	,short MinValue,short MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,WORD *value	,WORD MinValue,WORD MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,int32 *value	,int32 MinValue,int32 MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,DWORD *value	,DWORD MinValue,DWORD MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,int64 *value	,int64 MinValue,int64 MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,float *value	,float MinValue,float MaxValue	,double stepoffset,double stepmultiply	);
	void	AddLearningParam(AlgorithmThreshold *Thr ,double *value	,double MinValue,double MaxValue,double stepoffset,double stepmultiply	);
};

//===============================================================================

class	LearningImagePointerList : public NPList<LearningImagePointerList>
{
	LearningImage	*Pointer;
	int			GlobalPage;
	XDateTime	CreatedTime;
	int			OrgLocalX1 ,OrgLocalY1 ,OrgLocalX2 ,OrgLocalY2;
public:
	LearningImagePointerList(void)				{	Pointer=NULL;	}
	LearningImagePointerList(LearningImage *p);

	int				GetGlobalPage(void)		{	return GlobalPage;	}
	const XDateTime	&GetCreatedTime(void)	{	return CreatedTime;	}

	bool	Load(QIODevice *f,LayersBase *Base);
	bool	Save(QIODevice *f);

	void	GetOrgLocalArea(int &x1, int &y1 , int &x2 ,int &y2);

	LearningImagePointerList	&operator=(LearningImagePointerList &src);
};

class	LearningImagePointerContainer : public NPListPack<LearningImagePointerList>
{
public:
	LearningImagePointerContainer(void){}

	bool	Load(QIODevice *f,LayersBase *Base);
	bool	Save(QIODevice *f);

	LearningImagePointerContainer	&operator=(LearningImagePointerContainer &src);
	LearningImagePointerContainer	&operator+=(LearningImagePointerContainer &src);
};

class LibInfoList : public NPListSaveLoad<LibInfoList>
{
public:
	int		LibType;
	IntList	LibIDs ;

	LibInfoList(void);
	LibInfoList(const LibInfoList &src);

	LibInfoList	&operator=(const LibInfoList &src);
	bool	operator==(const LibInfoList &src);
	bool	operator!=(const LibInfoList &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};
class LibInfoListContainer : public NPListPackSaveLoad<LibInfoList>
{
public:
	LibInfoListContainer(void);
	LibInfoListContainer(const LibInfoListContainer &src);

	LibInfoListContainer	&operator=(const LibInfoListContainer &src);

	bool	AppendMerge(LibInfoList *t);
	void	AppendMerge(const LibInfoListContainer &src);

	virtual	LibInfoList	*Create(void)	override;
};

class LibDataList : public NPListSaveLoad<LibDataList>
{
public:
	int			LibType;
	int			LibID;
	QByteArray	LibData;

	LibDataList(void);
	LibDataList(const LibDataList &src);

	LibDataList	&operator=(const LibDataList &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class LibDataListContainer : public NPListPackSaveLoad<LibDataList>
{
public:
	LibDataListContainer(void);
	LibDataListContainer(const LibDataListContainer &src);

	LibDataListContainer	&operator=(const LibDataListContainer &src);

	virtual	LibDataList	*Create(void)	override;
};

#endif