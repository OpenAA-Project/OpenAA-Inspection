/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

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