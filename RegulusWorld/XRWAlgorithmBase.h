#pragma once
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\RegulusWorld\XRWAlgorithmBase.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "NList.h"
#include "XIntClass.h"
#include "XMapBuffer.h"
#include "XMacroFunction.h"


class	ExcludedListPack;
class	ClipboardAlgorithm;
class	RootNameListContainer;
class	QSqlDatabase;
class	VectorLineBase;
class	ErrorCodeList;
class	LanguagePackage;
class	RWAlgorithmDLLList;
class	RW3DBaseRoot;
class	RegulusWorld;
class	RWAlgorithmDLLContainer;

//========================================================================

class	RWLogicDLL	: public NPList<RWLogicDLL>,public DLLMacroFunc
{
	friend	class	AlgorithmBase;

	RegulusWorld		*Base;
	RWAlgorithmDLLList	*DLLPointer;
	RW3DBaseRoot		*InstBase;

	QWidget		*ShowAndSetItemsForm;
	QWidget		*ChangeItemsAttrForm;

	QString			Organization;
	WORD			DLLType;
	WORD			Ver;

	int32			DynamicID;			
	QString			Copyright;

public:
	RWLogicDLL(RegulusWorld *Base);
	~RWLogicDLL(void);

	void		Set(RWAlgorithmDLLList *s);
	RWLogicDLL	&operator=(RWLogicDLL &src);
	bool		IsRWAlgorithm(void);
	bool		SetLanguageCode(int LanguageCode);
	void		InitialName(void);
	bool		InitialAlloc(RegulusWorld *Base);
	void		InitialAfterParamLoaded(void);
	RW3DBaseRoot	*AllocOnly(RegulusWorld *Base);
	void		AssociateComponent	(ComponentListContainer &List);

	QString		GetFileName(void)		const;
	QString		GetDLLRoot(void)		const;
	QString		GetDLLName(void)		const;
	QString		GetExplain(void);
	WORD		GetDLLType(void)		{	return DLLType;		}
	int32		GetDynamicID(void)		{	return DynamicID;	}
	QString		GetOrganization(void)	const	{	return Organization;	}
	WORD		GetVer(void)			const	{	return Ver;		}
	void		SetDynamicID(int32 id)			{	DynamicID=id;	}

	bool		CheckDLL(const QString &root, const QString &name);

	void		ReallocRW3DBaseRoot(RegulusWorld *Base);

	RW3DBaseRoot	*GetInstance(void){		return InstBase;	}
	virtual	int		RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)	override;

private:
	QString		GetDefaultFileName(void);
};


class	RWLogicDLLBaseClass : public NPListPack<RWLogicDLL>
{
	RegulusWorld		*Base;
public:
	RWLogicDLLBaseClass(RegulusWorld *base);
	~RWLogicDLLBaseClass(void);

	RWLogicDLLBaseClass	&operator=(const RWLogicDLLBaseClass &src);

	int		AddDLLs(const RWAlgorithmDLLContainer &AlgoCont ,RegulusWorld *Base);
	bool	LoadOneDLL(RegulusWorld *Base ,const QString &DLLFileNameWithPath);
	void	AssociateComponent	(ComponentListContainer &List);

	bool	CheckDuplicatedAlgorithm(QStringList &Error);
	bool	CheckInstalledAlgorithm(RootNameListContainer &FromGUI ,RootNameListContainer &LackOfAlgorithm);
	void    InitialAfterParamLoaded(void);

	RWLogicDLL	*Search(int dynamicID);
	RWLogicDLL	*Search(const QString &_DLLRoot ,const QString &_DLLName);

	int			GetDLLCounts(void);
	bool		SetLanguageCode(int LanguageCode);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
