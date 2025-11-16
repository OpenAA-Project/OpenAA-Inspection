/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XFilterInstance.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XFILTERINSTANCE_H)
#define	XFILTERINSTANCE_H

#include <QtGui>
#include <QLibrary>
#include "XTypeDef.h"
#include "XFilterClass.h"
#include "XParamGlobal.h"
#include "XServiceForLayers.h"
#include "NList.h"

class	FilterDLLList;
class	FilterBankInPage;
class	LanguagePackage;
class	FilterInstanceContainer;


class	FilterInstanceList : public NPList<FilterInstanceList>,public ServiceForLayers
{
	friend	class	FilterClassBase;

	FilterDLLList	*DLLPointer;
	FilterClassBase	*Handle;
	bool			Initialised;
	FilterInstanceContainer	*Parent;
	bool			Enabled;
public:

	FilterInstanceList(FilterInstanceContainer *parent ,LayersBase *Base);
	~FilterInstanceList(void);

	bool	CreateInstance(const QString &FilterNameStr,int32 &ErrorCode);
	bool	Initial(const QString &FilterNameStr,int32 &ErrorCode);
	bool	Release(void);
	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	;
	bool	Reallocate(int newLayerNumb)						;

	FilterInstanceList	&operator=(const FilterInstanceList &src);

	int		GetPage(void)		const;
	int		GetPhaseCode(void)	const;
	bool	GetEnabled(void)	const	{	return Enabled;	}
	void	SetEnabled(bool b)			{	Enabled=b;		}

	int		GetDLLVersion(void)	const;
	void	SetLoadedDLLVersion(int d);
	int		GetLoadedDLLVersion(void)	const;
	bool	Load(QIODevice *str);
	bool	Save(QIODevice *str)	const;

	bool	ShowSetting(QWidget *parent);
	void	ExecuteBeforeScan	(void);
	ExeResult	ExecuteInitialAfterEdit	(void);
	ExeResult	ExecuteStartByInspection(void);
	ExeResult	ExecutePreAlignment		(void);
	ExeResult	ExecuteAlignment		(void);
	ExeResult	ExecutePreProcessing	(void);
	ExeResult	ExecuteProcessing		(void);
	ExeResult	ExecuteProcessingRevived(void);
	ExeResult	ExecutePostProcessing	(void);

	bool	ExecuteImage(ImageBuffer *Buff[],int BufferDimCounts);
	void	TransmitDirectly(GUIDirectMessage *packet);

	bool	IsValid(void)		const;
	QString	GetFilterName(void)	const;

	FilterClassBase	*GetFilterHandle(void)	const	{	return Handle;	}
};

class	FilterInstanceListPointerList : public NPList<FilterInstanceListPointerList>
{
	FilterInstanceList	*Point;
public:
	FilterInstanceListPointerList(FilterInstanceList *p):Point(p){}
	FilterInstanceList	*GetPointer(void)	const	{	return Point;	}
};


class	FilterInstanceContainer : public NPListPack<FilterInstanceList>,public ServiceForLayers
{
	friend	class	FilterClassBase;

	int32	ErrorCode;
	int		Page;
	int		PhaseCode;
public:
	FilterInstanceContainer(int phase ,int page ,LayersBase *Base);
	~FilterInstanceContainer(void);

	bool	AppendFilter(const QString &FilterNameStr);
	bool	ReleaseAll(void);
	void	SetEnabled(bool b);
	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	Reallocate(int newLayerNumb);

	FilterInstanceContainer	&operator=(const FilterInstanceContainer &src);

	int		GetPage(void)		const;
	int		GetPhaseCode(void)	;
	void	SetPage(int page)	{	Page=page;		}
	void	SetPhaseCode(int d)	{	PhaseCode=d;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	FilterInstanceList	*Search(const QString &_FilterName)	const;
	void	EnumInstance(NPListPack<FilterInstanceListPointerList> &PointerContainer ,const QString &_FilterName);

	void	ExecuteBeforeScan	(void);
	ExeResult	ExecuteInitialAfterEdit	(void);
	ExeResult	ExecuteStartByInspection(void);
	ExeResult	ExecutePreAlignment		(void);
	ExeResult	ExecuteAlignment		(void);
	ExeResult	ExecutePreProcessing	(void);
	ExeResult	ExecuteProcessing		(void);
	ExeResult	ExecuteProcessingRevived(void);
	ExeResult	ExecutePostProcessing	(void);

	bool	ExecuteImage(ImageBuffer *Buff[],int BufferDimCounts);
};

#endif