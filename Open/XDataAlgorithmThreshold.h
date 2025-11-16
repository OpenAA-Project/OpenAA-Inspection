/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDataAlgorithmThreshold.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XDataAlgorithmThresholdH
#define XDataAlgorithmThresholdH

#include <QIODevice>
#include <QMouseEvent>
#include <QColor>
#include "XTypeDef.h"
#include "NList.h"
#include "NListComp.h"
#include "XFlexArea.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XVector.h"
#include "XParamBase.h"
#include "XLearningRule.h"
#include "XCSV.h"
#include "XDot.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XMapBuffer.h"
#include "XAlgorithmLibNGType.h"
#include "XUndoBase.h"
#include "XReportedTopic.h"
#include "XHistgramByParam.h"
#include "XManualExecuter.h"
#include "XAlgorithmCommon.h"

class	AlgorithmThreshold;
class	AlgorithmItemRoot;
class   AlgorithmInLayerRoot;
class   AlgorithmInPageRoot;
class	AlgorithmInPageInOnePhase;
class   AlgorithmBase;
class	AlgorithmParentFromItem;
class	DataInPage;
class	DataInLayer;
class	LayersBase;
class	ParamGlobal;
class	ParamComm;
class	ResultInItemRoot;
class	ResultInLayerRoot;
class	ResultInPageRoot;
class	ResultBasePhase;
class	ResultBaseForAlgorithmRoot;
class	GUIDirectMessage;
class	ClipboardAlgorithmItem;
class	ClipboardAlgorithm;
class	AlgorithmItemIndependentPack;
class	AlgorithmLibraryListContainer;
class	AlgorithmLibrary;
class	AlgorithmLibraryLevelContainer;
class	AlgorithmLibraryList;
class	SelectLibListContainer;
class	OriginNames;
class	ItemPointerListInPage;
class	ItemPointerListInLayer;
class	ItemPointerList;
class	ExpandedSelectedItemListContainer;
class	VectorLineBase;
class	ReportedTopic;
class	LotInformation;
class	ListPageLayerIDPack;
class	AlgorithmLibraryStocker;
class	AlgorithmItemIndependent;
class	LearningMenu;
class	LearningResource;
class	ChangedMap;
class	LearningInDBThreshold;


class ThresholdMemberModifierBase : public NPList<ThresholdMemberModifierBase>
{
public:
	int32	MemberID;

	ThresholdMemberModifierBase(int32 memberid)	:MemberID(memberid){}

	virtual	int32	GetClassID(void)	=0;
	virtual	bool	CopyFrom(const ThresholdMemberModifierBase &src)	=0;
	virtual	void	SetModifierAdded(int addedvalue)					=0;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};


class ThresholdMemberModifierChar : public ThresholdMemberModifierBase
{
public:
	char	*Point;
	short	Added;

	ThresholdMemberModifierChar(int32 memberid ,char *p)
		:ThresholdMemberModifierBase(memberid),Point(p),Added(0)	{}

	virtual	int32	GetClassID(void)	override	{	return 7;	}

	virtual	bool	CopyFrom(const ThresholdMemberModifierBase &src)	override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	SetModifierAdded(int addedvalue)	override;
};


class ThresholdMemberModifierBYTE: public ThresholdMemberModifierBase
{
public:
	BYTE	*Point;
	short	Added;

	ThresholdMemberModifierBYTE(int32 memberid ,BYTE *p)
		:ThresholdMemberModifierBase(memberid),Point(p),Added(0)	{}

	virtual	int32	GetClassID(void)	override	{	return 8;	}

	virtual	bool	CopyFrom(const ThresholdMemberModifierBase &src)	override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	SetModifierAdded(int addedvalue)	override;
};


class ThresholdMemberModifierShort : public ThresholdMemberModifierBase
{
public:
	short	*Point;
	short	Added;

	ThresholdMemberModifierShort(int32 memberid ,short *p)
		:ThresholdMemberModifierBase(memberid),Point(p),Added(0)	{}

	virtual	int32	GetClassID(void)	override	{	return 1;	}

	virtual	bool	CopyFrom(const ThresholdMemberModifierBase &src)	override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	SetModifierAdded(int addedvalue)	override;
};


class ThresholdMemberModifierInt : public ThresholdMemberModifierBase
{
public:
	int		*Point;
	int		Added;

	ThresholdMemberModifierInt(int32 memberid ,int *p)
		:ThresholdMemberModifierBase(memberid),Point(p),Added(0)	{}

	virtual	int32	GetClassID(void)	override	{	return 2;	}

	virtual	bool	CopyFrom(const ThresholdMemberModifierBase &src)	override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	SetModifierAdded(int addedvalue)	override;
};


class ThresholdMemberModifierWord : public ThresholdMemberModifierBase
{
public:
	WORD	*Point;
	int		Added;

	ThresholdMemberModifierWord(int32 memberid ,WORD *p)
		:ThresholdMemberModifierBase(memberid),Point(p),Added(0)	{}

	virtual	int32	GetClassID(void)	override	{	return 3;	}

	virtual	bool	CopyFrom(const ThresholdMemberModifierBase &src)	override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	SetModifierAdded(int addedvalue)	override;
};


class ThresholdMemberModifierDWord : public ThresholdMemberModifierBase
{
public:
	DWORD	*Point;
	int		Added;

	ThresholdMemberModifierDWord(int32 memberid ,DWORD *p)
		:ThresholdMemberModifierBase(memberid),Point(p),Added(0)	{}

	virtual	int32	GetClassID(void)	override	{	return 4;	}

	virtual	bool	CopyFrom(const ThresholdMemberModifierBase &src)	override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	SetModifierAdded(int addedvalue)	override;
};


class ThresholdMemberModifierFloat : public ThresholdMemberModifierBase
{
public:
	float	*Point;
	float	Added;

	ThresholdMemberModifierFloat(int32 memberid ,float *p)
		:ThresholdMemberModifierBase(memberid),Point(p),Added(0)	{}

	virtual	int32	GetClassID(void)	override	{	return 5;	}

	virtual	bool	CopyFrom(const ThresholdMemberModifierBase &src)	override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	SetModifierAdded(int addedvalue)	override;
};


class ThresholdMemberModifierDouble : public ThresholdMemberModifierBase
{
public:
	double	*Point;
	double	Added;

	ThresholdMemberModifierDouble(int32 memberid ,double *p)
		:ThresholdMemberModifierBase(memberid),Point(p),Added(0)	{}

	virtual	int32	GetClassID(void)	override	{	return 6;	}

	virtual	bool	CopyFrom(const ThresholdMemberModifierBase &src)	override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	SetModifierAdded(int addedvalue)	override;
};

class ThresholdMemberModifierContainer : public NPListPack<ThresholdMemberModifierBase>
{
	AlgorithmThreshold	*Parent;
public:
	ThresholdMemberModifierContainer(AlgorithmThreshold *p);

	ThresholdMemberModifierBase	*Create(int32 ClassID);

	ThresholdMemberModifierContainer	&operator=(const ThresholdMemberModifierContainer &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	GetModifierAdded(int MemberID ,char &RetValueInt)	const;
	bool	GetModifierAdded(int MemberID ,BYTE &RetValueInt)	const;
	bool	GetModifierAdded(int MemberID ,short &RetValueInt)	const;
	bool	GetModifierAdded(int MemberID ,int &RetValueInt)	const;
	bool	GetModifierAdded(int MemberID ,WORD &RetValueInt)	const;
	bool	GetModifierAdded(int MemberID ,DWORD &RetValueInt)	const;
	bool	GetModifierAdded(int MemberID ,float &RetValueInt)	const;
	bool	GetModifierAdded(int MemberID ,double &RetValueInt)	const;


	void	SetModifierAdded(int MemberID ,int addedvalue);
};


//=========================================================================================
//èÍèäÇ…ÇÊÇ¡ÇƒïsïœÇ»ÇµÇ´Ç¢íl
class	AlgorithmThreshold :public NPList<AlgorithmThreshold> 
							,public HistgramInThreshold
							,public LearningValueInThreshold
{
	AlgorithmItemRoot	*Parent;
	int		ThresholdLevelID;

	ThresholdMemberModifierContainer	MemberModifierContainer;
public:
	AlgorithmThreshold(AlgorithmItemRoot *parent);
	//AlgorithmThreshold(const AlgorithmThreshold &src);
	~AlgorithmThreshold(void){}

	AlgorithmThreshold	&operator=(const AlgorithmThreshold &src);
	virtual	void	CopyFrom(const AlgorithmThreshold &src);
	virtual	void	CopyFrom(const AlgorithmThreshold &src,IntList &EdittedMemberID);
	virtual	bool	Save(QIODevice *f)					=0;
    virtual	bool	Load(QIODevice *f)					=0;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const	=0;
	virtual	int		GetSize(void)							const	=0;
	virtual	void	Reflect(AlgorithmThreshold *Src ,ChangedMap &Map){}	

	virtual	void	FromLibrary(AlgorithmLibrary *src){}
	virtual	void	ToLibrary(AlgorithmLibrary *Dest){}
	virtual	void	RegistHist(void){}
	virtual	WORD	GetDLLVersion(void);	
	virtual	int		GetLoadedVersion(void);
	virtual	LayersBase		*GetLayersBase(void)	const;
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const{};

	virtual	AlgorithmItemRoot	*GetParentItem(void)	const	{	return Parent;	}

	int		GetThresholdLevelID(void)	const	{	return ThresholdLevelID;	}
	void	SetThresholdLevelID(int d)			{	ThresholdLevelID=d;			}

	//For learning
	void	SetLearningParam(LearningInDBThreshold &L,char *value	,char MinValue,char MaxValue	,double stepoffset,double stepmultiply);
	void	SetLearningParam(LearningInDBThreshold &L,BYTE *value	,BYTE MinValue,BYTE MaxValue	,double stepoffset,double stepmultiply);
	void	SetLearningParam(LearningInDBThreshold &L,short *value	,short MinValue,short MaxValue	,double stepoffset,double stepmultiply);
	void	SetLearningParam(LearningInDBThreshold &L,WORD *value	,WORD MinValue,WORD MaxValue	,double stepoffset,double stepmultiply);
	void	SetLearningParam(LearningInDBThreshold &L,int32 *value	,int32 MinValue,int32 MaxValue	,double stepoffset,double stepmultiply);
	void	SetLearningParam(LearningInDBThreshold &L,DWORD *value	,DWORD MinValue,DWORD MaxValue	,double stepoffset,double stepmultiply);
	void	SetLearningParam(LearningInDBThreshold &L,int64 *value	,int64 MinValue,int64 MaxValue	,double stepoffset,double stepmultiply);
	void	SetLearningParam(LearningInDBThreshold &L,float *value	,float MinValue,float MaxValue	,double stepoffset,double stepmultiply);
	void	SetLearningParam(LearningInDBThreshold &L,double *value	,double MinValue,double MaxValue,double stepoffset,double stepmultiply);

	virtual	void	SetLearningParam(LearningInDBThreshold &L){}


	void	SetModifierMember(int MemberID, char *member);
	void	SetModifierMember(int MemberID, BYTE *member);
	void	SetModifierMember(int MemberID, short *member);
	void	SetModifierMember(int MemberID, int *member);
	void	SetModifierMember(int MemberID, WORD *member);
	void	SetModifierMember(int MemberID, DWORD *member);
	void	SetModifierMember(int MemberID, float *member);
	void	SetModifierMember(int MemberID, double *member);

	bool	GetModifierAdded(int MemberID ,char &RetAddedValue)	const;
	bool	GetModifierAdded(int MemberID ,BYTE &RetAddedValue)	const;
	bool	GetModifierAdded(int MemberID ,short &RetAddedValue)	const;
	bool	GetModifierAdded(int MemberID ,int &RetAddedValue)	const;
	bool	GetModifierAdded(int MemberID ,WORD &RetAddedValue)	const;
	bool	GetModifierAdded(int MemberID ,DWORD &RetAddedValue)	const;
	bool	GetModifierAdded(int MemberID ,float &RetAddedValue)	const;
	bool	GetModifierAdded(int MemberID ,double &RetAddedValue)	const;

	void	SetModifierAdded(int MemberID ,int addedvalue);

	virtual	bool	SaveMember(QIODevice *f);
    virtual	bool	LoadMember(QIODevice *f);

};

class AlgorithmThresholdContainer : public NPListPack<AlgorithmThreshold>
{
	AlgorithmItemRoot *Parent;
public:
	explicit	AlgorithmThresholdContainer(AlgorithmItemRoot *ParentItem=NULL);
	~AlgorithmThresholdContainer(void);

	bool	Save(QIODevice *f);
    bool	Load(QIODevice *f);

	bool	SaveWithThreshold(QIODevice *f);
    bool	LoadWithThreshold(QIODevice *f,LayersBase *Base);

	bool	SaveMember(QIODevice *f);
    bool	LoadMember(QIODevice *f);

	AlgorithmThreshold	*GetAlgorithmThreshold(int LevelID);

	AlgorithmThresholdContainer	&operator=(const AlgorithmThresholdContainer &src);
};

//=================================================================================
class AlgorithmThresholdPointer : public NPList<AlgorithmThresholdPointer>
{
	AlgorithmThreshold	*Pointer;
	int		LibType;
	int		LibID;
public:
	AlgorithmThresholdPointer(AlgorithmThreshold *AThr ,int LibType ,int LibID);

	int		GetLibType(void)	const	{	return LibType;	}
	int		GetLibID(void)		const	{	return LibID;	}
	AlgorithmThreshold	*GetThreshold(void);
};

class AlgorithmThresholdPointerContainer : public NPListPack<AlgorithmThresholdPointer>
{
public:
	AlgorithmThresholdPointerContainer(void){}

	AlgorithmThreshold			*Search(int LibType ,int LibID);
	AlgorithmThresholdPointer	*SearchPointer(int LibType ,int LibID);
};

//=================================================================================
class AlgorithmThresholdPointerPointer : public NPList<AlgorithmThresholdPointerPointer>
{
	AlgorithmThresholdPointer	*Pointer;
public:
	AlgorithmThresholdPointerPointer(AlgorithmThresholdPointer *p);

	int		GetLibType(void)	const	{	return Pointer->GetLibType();		}
	int		GetLibID(void)		const	{	return Pointer->GetLibID();			}
	AlgorithmThreshold	*GetThreshold(void)	{	return Pointer->GetThreshold();	}
	AlgorithmThresholdPointer	*GetPointer(void)	{	return Pointer;			}
};

class AlgorithmThresholdPointerPointerContainer : public NPListPack<AlgorithmThresholdPointerPointer>
{
public:
	AlgorithmThresholdPointerPointerContainer(void){}

	void	Merge(AlgorithmThresholdPointer *p);
	AlgorithmThreshold	*FindAlgorithmThreshold(int LibType,int LibID);
};

#endif