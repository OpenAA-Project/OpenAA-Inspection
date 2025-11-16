/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XFilterManager.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XFILTERMANAGER_H)
#define	XFILTERMANAGER_H

#include <QtGui>
#include <QLibrary>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "XFilterClass.h"
#include "XParamGlobal.h"
#include "XServiceForLayers.h"
#include "NList.h"
#include "XDLLManager.h"

class	FilterBankInPage;
class	LanguagePackage;
class	FilterInstanceContainer;
class	RootNameListContainer;

class	FilterDLLList : public NPList<FilterDLLList>, public DLLManager ,public ServiceForLayers
{
	WORD	(*DLL_GetDLLType)(void);
	bool	(*DLL_GetName)(QString &str);
	WORD	(*DLL_GetVersion)(void);
	const char	*(*DLL_GetExplain)(void);
	void	(*DLL_SetLanguage)(LanguagePackage &Pkg ,int LanguageCode);
	bool	(*DLL_CheckCopyright)(QString &CopyrightString);
	void	(*DLL_AssociateComponent)(LayersBase *Base,ComponentListContainer &List);

	FilterClassBase	*(*DLL_Initial)(LayersBase *base);
	bool	(*DLL_Close)(void *handle);
	bool	(*DLL_Load)(FilterClassBase *handle ,QIODevice &str);
	bool	(*DLL_Save)(FilterClassBase *handle ,QIODevice &str);
	bool	(*DLL_ShowSetting)(FilterClassBase *handle, QWidget *parent);
	void	(*DLL_ExecuteBeforeScan)(FilterClassBase *handle);
	bool	(*DLL_ExecuteImage)(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts);

	QLibrary 	DllLib;
	QString		DllFileName;

	QString		Copyright;
	QString		FilterName;

	bool		IsFilterDLL(void);
	bool		LoadDLL(QString &dllfilename,int32 &ErrorCode);

public:
	explicit	FilterDLLList(LayersBase *base ,const QString &dllfilename);
	virtual	~FilterDLLList(void);

	bool	InitialDLL(int32 &ErrorCode);
	bool	SetLanguageCode(int LanguageCode);
	bool	CheckSystemVersion(QStringList &Str);
	void	AssociateComponent	(ComponentListContainer &List);

	WORD	GetDLLType(void)	const;
	WORD	GetVersion(void)	const;
	QString	GetCopyright(void)	const	{	return Copyright;		}
	QString	GetFilterName(void)	const	{	return FilterName;		}
	QString	GetFileName(void)	const	{	return DllFileName;		}
	const QString	GetExplain(void);

	//------------- for instance ------------------------
	FilterClassBase	*CreateInstance(LayersBase *Base);
	bool	Release(FilterClassBase	*Handle);
	bool	Save(QIODevice *str,FilterClassBase	*Handle);
	bool	Load(QIODevice *str,FilterClassBase	*Handle);
	bool	ShowSetting(QWidget *parent,FilterClassBase	*Handle);
	ExeResult	ExecuteInitialAfterEdit	(FilterClassBase *Handle);
	ExeResult	ExecuteStartByInspection(FilterClassBase *Handle);
	ExeResult	ExecutePreAlignment		(FilterClassBase *Handle);
	ExeResult	ExecuteAlignment		(FilterClassBase *Handle);
	ExeResult	ExecutePreProcessing	(FilterClassBase *Handle);
	ExeResult	ExecuteProcessing		(FilterClassBase *Handle);
	ExeResult	ExecuteProcessingRevived(FilterClassBase *Handle);
	ExeResult	ExecutePostProcessing	(FilterClassBase *Handle);
	void	ExecuteBeforeScan	(FilterClassBase	*Handle);
	bool	ExecuteImage(FilterClassBase *Handle,ImageBuffer *Buff[],int BufferDimCounts);

	virtual	void	GetExportFunctions(QStringList &Str)	override;
};

class	FilterBankBase : public NPListPack<FilterDLLList>,public ServiceForLayers
{
public:
	explicit	FilterBankBase(LayersBase *base);
	virtual	~FilterBankBase(void);

	int	SearchAddDLL(int32 &ErrorCode);
	
	FilterDLLList	*Search(const QString &_FilterName);
	int			GetDLLCounts(void);
	bool		CheckSystemVersion	(QStringList &Str);
	void		AssociateComponent	(ComponentListContainer &List);
};


#endif