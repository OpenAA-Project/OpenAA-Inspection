/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XAlgorithmLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XALGORITHMLIBRARY_H)
#define	XALGORITHMLIBRARY_H

#include <QIODevice>
#include <QVariant>
#include <QDateTime>
#include "XTypeDef.h"
#include "XIntClass.h"
#include "XAlgorithmLibNGType.h"
#include "XReportedTopic.h"
#include "XDateTime.h"
#include "Regulus64Version.h"
#include "NListComp.h"
#include "XServiceForLayers.h"

class	QSqlDatabase;
class	AlgorithmLibraryContainer;
class	LayersBase;
class	AlgorithmLibrary;
class	AlgorithmLibraryLevelContainer;
class	CommonDataInLibTypeListContainer;
class	CommonDataInLibType;
class	AlgorithmBase;

//===============================================================================
class	CommonDataInLibType : public NPList<CommonDataInLibType>
{
public:
	int32		CommonID;
	QString		Name;
	QDateTime	LastUpdated;
	int32		Version;
	QByteArray	Data;

	CommonDataInLibType(void)	{	CommonID=-1;	Version=RegulusVersion;	}	

};

class	CommonDataInLibTypeContainer : public NPListPack<CommonDataInLibType>
{
public:
	CommonDataInLibTypeContainer(void){}

};

class	CommonDataInLibTypeList : public NPList<CommonDataInLibTypeList>
{
public:
	int32		CommonID;
	QString		Name;

	CommonDataInLibTypeList(void){	CommonID=-1;	}
};

class	CommonDataInLibTypeListContainer : public NPListPack<CommonDataInLibTypeList>
{
public:
	CommonDataInLibTypeListContainer(void){}

};

//===============================================================================

class	OriginNames : public NPList<OriginNames>
{
public:
	QString	DLLRoot;
	QString	DLLName;
	int		Numb;

	OriginNames(void) { Numb = 0; }
	OriginNames(const OriginNames& src) {
		DLLRoot = src.DLLRoot;
		DLLName = src.DLLName;
		Numb = src.Numb;
	}
	bool	Load(QIODevice* f);
	bool	Save(QIODevice* f);
	OriginNames& operator=(const OriginNames& src);
};

//===============================================================================

class	AlgorithmLibraryList : public NPList<AlgorithmLibraryList>
{
  #pragma	pack(push,1)
	int32	LibType;
	int32	LibID;
  #pragma	pack(pop)
	QString	LibName;

public:
	AlgorithmLibraryList(void){}
	AlgorithmLibraryList(const AlgorithmLibraryList &src);
	AlgorithmLibraryList(int libType ,int libID ,const QString &libName){	LibType=libType;	LibID=libID;	LibName=libName;	}
	AlgorithmLibraryList(LayersBase *base,int libType ,int libID);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	operator==(const AlgorithmLibraryList &src)	const;
	AlgorithmLibraryList	&operator=(const AlgorithmLibraryList &src);

	int32	GetLibType(void)	const	{	return LibType;		}
	void	SetLibType(int32 b)			{	LibType=b;			}
	int32	GetLibID(void)		const	{	return LibID;		}
	void	SetLibID(int32 b)			{	LibID=b;			}
	QString	GetLibName(void)	const	{	return LibName;		}
	void	SetLibName(const QString &s){	LibName=s;		}

	virtual	int	Compare(AlgorithmLibraryList &src) override;
};

class	AlgorithmLibraryListContainer : public NPListPack<AlgorithmLibraryList>
{
public:
	AlgorithmLibraryListContainer(const AlgorithmLibraryListContainer &src);
	AlgorithmLibraryListContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	AlgorithmLibraryListContainer	&operator=(const AlgorithmLibraryListContainer &src);
	AlgorithmLibraryListContainer	&operator=(const AlgorithmLibraryList &src);
	AlgorithmLibraryListContainer	&operator+=(const AlgorithmLibraryListContainer &src);
	AlgorithmLibraryListContainer	&operator+=(const AlgorithmLibraryList &src);

	bool	operator==(const AlgorithmLibraryListContainer &src)	const;
	bool	operator!=(const AlgorithmLibraryListContainer &src)	const	{	return !operator==(src);	}
	bool	IsPartialInclude(const AlgorithmLibraryListContainer &src);
	IntList	GetIDList(void);
	AlgorithmLibraryList	*SearchLibrary(int LibType, int LibID)			const;
	AlgorithmLibraryList	*SearchLibrary(const AlgorithmLibraryList &src)	const;
	void	Add(int LibType ,AlgorithmLibraryLevelContainer &Lib);
	void	Merge(LayersBase *Base,int LibType ,int LibID);
	void	Merge(const AlgorithmLibraryListContainer &src);
	bool	IsInclude(int LibID)						const;
	bool	IsInclude(int LibType,int LibID)			const;
	bool	IsInclude(const AlgorithmLibraryList &src)	const;
};

//-----------------------------------------
class	AlgorithmLibrary : public NPList<AlgorithmLibrary>
{
	friend	class	AlgorithmLibraryContainer;
	friend	class	AlgorithmLibraryLevelContainer;

	AlgorithmLibraryLevelContainer	*Parent;
	WORD		ThresholdLevelID;

public:
	explicit	AlgorithmLibrary(AlgorithmLibraryLevelContainer *p);
	AlgorithmLibrary(const AlgorithmLibrary &src);
	AlgorithmLibrary(void);
	virtual	~AlgorithmLibrary(void);

	void	SetParent(AlgorithmLibraryLevelContainer *p)				{	Parent=p;		}
	AlgorithmLibraryLevelContainer	*GetParentLevelContainer(void)		{	return Parent;	}
	int32		GetLibID(void)				const;
	int32		GetLibFolderID(void)		const;
	int32		GetLastWorker(void)			const;
	int32		GetDataVersion(void)		const;
	const XDateTime	&GetLastUpdated(void)	const;

	QString		GetLibName(void)	const;
	int32		GetLibType(void)	const;
	int32		GetSourceID(void)	const;
	QColor		GetLibColor(void)	const;

	QString		GetLibComment(void)	const;
	bool		SetLibComment(const QString &text);

	IntList		&GetAdaptedPickLayers(void);
	bool		HasPickLayer(int Layer);

	IntList		&GetAdaptedGenLayers(void);
	bool		HasGenLayer(int Layer);

	int		GetThresholdLevelID(void)	{	return ThresholdLevelID;	}
	void	SetThresholdLevelID(int ID)	{	ThresholdLevelID=ID;		}

	virtual	AlgorithmLibrary &operator=(const AlgorithmLibrary &src);
	virtual	bool	SaveBlob(QIODevice *f);
	virtual	bool	LoadBlob(QIODevice *f);
	bool	Save(QIODevice *f);		//Call SaveBlob inside
	bool	Load(QIODevice *f);		//Call LoadBlob inside
	bool	LoadOld (AlgorithmLibraryLevelContainer *Parent ,QIODevice *f);	//Call LoadBlob inside
	bool	LoadOld2(AlgorithmLibraryLevelContainer *Parent ,QIODevice *f);	//Call LoadBlob inside

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const{}
};

class AlgorithmLibraryLevelContainer : public NPListPack<AlgorithmLibrary>
{
	friend	class	AlgorithmLibrary;

  #pragma	pack(push,1)
	int32		LibID;
	int32		LibFolderID;
	int32		LastWorker;
	int32		DataVersion;
	int32		LibType;
  #pragma	pack(pop)
	XDateTime	LastUpdated;
	QString		LibName;
	int32		SourceID;
	IntList		AdaptedPickLayers;
	IntList		AdaptedGenLayers;
	QColor		LibColor;
	QString		LibComment;
	AlgorithmLibraryContainer	*Parent;

public:
	explicit	AlgorithmLibraryLevelContainer(AlgorithmLibraryContainer *p);
	explicit	AlgorithmLibraryLevelContainer(AlgorithmBase *base);
	AlgorithmLibraryLevelContainer(const AlgorithmLibraryLevelContainer &src);
	~AlgorithmLibraryLevelContainer(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	SaveBlob(QIODevice *f);
	bool	LoadBlob(QIODevice *f);

	AlgorithmLibraryLevelContainer	&operator=(const AlgorithmLibraryLevelContainer &src);

	AlgorithmLibrary	*GetLibrary(int ThresholdLevelID=-1);	//Don't delete pointer
	void	Set(AlgorithmLibrary *lib ,int ThresholdLevelID=-1);
	void	Set(AlgorithmLibrary &lib ,int ThresholdLevelID=-1);
	void	AppendList(AlgorithmLibrary *additem);

	virtual		void	Reset(void)					{	LibID=-1;			}
	int32		GetLibID(void)				const	{	return LibID;		}
	void		SetLibID(int32 id)					{	LibID=id;			}
	int32		GetLibFolderID(void)		const	{	return LibFolderID;	}
	void		SetLibFolderID(int32 d)				{	LibFolderID=d;		}
	int32		GetLastWorker(void)			const	{	return LastWorker;	}
	void		SetLastWorker(int32 d)				{	LastWorker=d;		}
	int32		GetDataVersion(void)		const	{	return DataVersion;	}
	void		SetDataVersion(int32 d)				{	DataVersion=d;		}
	void		SetLastUpdated(const XDateTime &d)	{	LastUpdated=d;	}
	XDateTime	&GetLastUpdated(void)				{	return LastUpdated;	}

	QString		GetLibName(void)			const	{	return LibName;		}
	void		SetLibName(const QString &s)		{	LibName=s;			}
	int32		GetLibType(void)			const	{	return LibType;		}
	int32		GetSourceID(void)			const	{	return SourceID;	}
	void		SetSourceID(int32 id)				{	SourceID=id;		}

	void		SetLibColor(const QColor &col)		{	LibColor=col;		}
	QColor		GetLibColor(void)				const{	return LibColor;	}
	QString		GetLibComment(void)				const{	return LibComment;	}
	void		SetLibComment(const QString &s)		{	LibComment=s;		}

	IntList		&GetAdaptedPickLayers(void)							{	return AdaptedPickLayers;			}
	void		SetAdaptedPickLayers(const IntList &_AdaptedLayers)	{	AdaptedPickLayers=_AdaptedLayers;	}
	bool		HasPickLayer(int Layer);

	IntList		&GetAdaptedGenLayers(void)							{	return AdaptedGenLayers;			}
	void		SetAdaptedGenLayers(const IntList &_AdaptedLayers)	{	AdaptedGenLayers=_AdaptedLayers;	}
	bool		HasGenLayer(int Layer);

	AlgorithmLibraryContainer	*GetParent(void)	{	return Parent;	}
	void		Clear(void);
	bool		SwitchThresholdLevel(int OldLevel ,int NewLevel);
	void		CopyThresholdLevel	(int SourceLevelID ,int DestLevelID);
	bool		IsInclude(int LibID);
private:

};

class ColorWithID : public NPList<ColorWithID>
{
public:
	QColor	Color;
	int		ID;

	ColorWithID(void){	ID=-1;	}
	explicit	ColorWithID(const QColor &col ,int id)	{	Color=col;	ID=id;				}
	ColorWithID(const ColorWithID &src)		{	Color=src.Color;	ID=src.ID;	}
};

class ColorWithIDContainer : public NPListPack<ColorWithID>
{
public:
	ColorWithIDContainer(void){}

	ColorWithID	*Find(int id);
	void	Merge(const QColor &col ,int id);
	void	Remove(int id);
};


class	AlgorithmLibraryContainer : public ServiceForLayers
{
	ColorWithIDContainer	StackColor;
public:
	explicit	AlgorithmLibraryContainer(LayersBase *base);
	virtual	~AlgorithmLibraryContainer(void);

	virtual	int		GetLibType(void)=0;
	virtual	const char	*GetLibTypeName(void)=0;
	virtual	AlgorithmLibrary	*CreateNew()=0;

	virtual	LibNGTypeItem	*CreateLibNGTypeItem(LayersBase *base){	return NULL;	}

	bool	GetNGTypeContainer(int LibID
							,  LibNGTypeInAlgorithm &NGTypeContainer);
	LibNGTypeItem	*GetNGTypeItem		(int LibID,int NGTypeID);
	bool			SaveNewNGTypeItem	(int LibID,LibNGTypeItem *Item);
	bool			UpdateNGTypeItem	(int LibID,LibNGTypeItem *Item);
	bool			DeleteNGTypeItem	(int LibID,LibNGTypeItem *Item);

	bool	CheckAndCreateLibTypeInDatabase(void);

	bool	EnumLibrary(int LibType,int LibFolderID ,AlgorithmLibraryListContainer &LibIDList);
	int		EnumLibrary(int LibType,AlgorithmLibraryListContainer &LibIDList);
	int		EnumLibrary(AlgorithmLibraryListContainer &LibIDList){	return EnumLibrary(GetLibType(),LibIDList);	}
	void	GetLibraryNames(AlgorithmLibraryListContainer &LibIDList);
	bool	GetLibrary(int LibID ,AlgorithmLibraryLevelContainer &Dest);
	bool	GetLibraryList(int LibID ,AlgorithmLibraryList &Dest);
	QString	GetLibraryName(int LibID);
	bool	GetLayers(int LibID ,IntList &AdaptedPickLayers ,IntList &AdaptedGenLayers);
	QColor	GetLibColor(int LibID);

	bool	SaveNew			(AlgorithmLibraryLevelContainer &Data);	//LibID is generated to Max+1
	bool	SaveNewWithLibID(AlgorithmLibraryLevelContainer &Data);
	bool	Update			(AlgorithmLibraryLevelContainer &Data);
	bool	Load			(AlgorithmLibraryLevelContainer &Data);
	bool	Delete (int32 LibID);

	int		EnumCommonDataInLibType		(CommonDataInLibTypeListContainer &RetContainer);
	bool	SaveNewCommonDataInLibType	(CommonDataInLibType &Data);
	bool	UpdateCommonDataInLibType	(CommonDataInLibType &Data);
	bool	LoadCommonDataInLibType		(CommonDataInLibType &Data);
	bool	DeleteCommonDataInLibType	(int32 CommonID);
};

class	AlgorithmLibraryStockerList : public NPList<AlgorithmLibraryStockerList>
{
	AlgorithmLibraryLevelContainer	*Point;
public:
	explicit	AlgorithmLibraryStockerList(AlgorithmLibraryLevelContainer *src);
	~AlgorithmLibraryStockerList(void);

	AlgorithmLibraryStockerList	&operator=(const AlgorithmLibraryStockerList &src);
	AlgorithmLibraryLevelContainer	&GetLib(void);
	void	SwitchThresholdLevel(int OldLevel ,int NewLevel);
	void	CopyThresholdLevel	(int SourceLevelID ,int DestLevelID);
};

class	AlgorithmLibraryStocker : public NPListPack<AlgorithmLibraryStockerList>
{
public:
	AlgorithmLibraryStocker(void){}

	AlgorithmLibraryLevelContainer	*FindLib(int libtype, int libid);
	void	SwitchThresholdLevel(int OldLevel ,int NewLevel);
	void	CopyThresholdLevel	(int SourceLevelID ,int DestLevelID);
};

class	AlgorithmLibraryContainerForEnum : public AlgorithmLibraryContainer
{
public:
	explicit	AlgorithmLibraryContainerForEnum(LayersBase *Base);

	virtual	int		GetLibType(void)			override	{	return -1;	}
	virtual	const char	*GetLibTypeName(void)	override	{	return /**/"";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override	{	return NULL;	}
	int		EnumLibrary(QSqlDatabase &DB ,int LibType,int LibFolderID ,AlgorithmLibraryListContainer &LibIDList);
	int		EnumLibrary(QSqlDatabase &DB ,int LibType,int LibFolderID ,int LibIDList[] ,int MaxCountDim);
	int		EnumAllLibraries(QSqlDatabase &DB ,int LibType,AlgorithmLibraryListContainer &LibIDList);
};

//===============================================================================

class	ExpandedSelectedItemList	// : public NPList<ExpandedSelectedItemList>
{
public:
	int32	X1,Y1;	
	int32	X2,Y2;
	int32	Page;
	int32	Layer;
	int32	ItemID;

	ExpandedSelectedItemList(void)	{	X1=Y1=X2=Y2=0;	Page=0;	Layer=0;	ItemID=-1;	}

	ExpandedSelectedItemList	&operator=(const ExpandedSelectedItemList &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ExpandedSelectedItemListContainer// : public NPListPack<ExpandedSelectedItemList>
{
	ExpandedSelectedItemList	*Dim;
	int32						AllocatedNumb;
	int32						CurrentNumb;
public:
	ExpandedSelectedItemListContainer(void);
	~ExpandedSelectedItemListContainer(void);

	int	GetCount(void){	return CurrentNumb;	}

	ExpandedSelectedItemList *Get(int n){	return &Dim[n];	}

	void	AppendList(ExpandedSelectedItemList *a);
	void	AppendList(const ExpandedSelectedItemList &a);
	void	RemoveAll(void);
	
	ExpandedSelectedItemListContainer	&operator=(const ExpandedSelectedItemListContainer &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//===============================================================================

class	SelectLibList : public NPList<SelectLibList>
{
public:
	int	LibType;
	int	LibID;
	int	Layer;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	SelectLibListContainer : public NPListPack<SelectLibList>	//ライブラリ選択リストコンテナ
{
public:
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	SelectLibList	*Find(int LibType ,int LibID ,int Layer=-1);
};
#endif
