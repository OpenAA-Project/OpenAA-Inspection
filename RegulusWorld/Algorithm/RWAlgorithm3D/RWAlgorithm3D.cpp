/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\RWAlgorithm3D\RWAlgorithm3D.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "RWAlgorithm3D.h"
#include "XRWAlgorithmDLL.h"
#include "XRWAlgorithm3D.h"
#include "XDirectCommPacket.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"RWAlgorithm3D";

DEFFUNCEX	bool		DLL_GetOrganization(QString &str)
{
	str=/**/"MEGATRADE";
	return true;
}
DEFFUNCEX	WORD		DLL_GetDLLType(void)
{
	return DLLRWAlgorithmMode;
}
DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return true;
}
DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return RWAlgorithm3DVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Edit3D for RegulusWorld";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}


DEFFUNCEX	RW3DBaseRoot	*DLL_InitialAlloc(RegulusWorld *Base)
{
	RWAlgorithm3DBase	*base=new RWAlgorithm3DBase(Base);

	//(*Base)=new GUICmdReqPanelImage	(Base,sRoot,sName);
	//(*Base)=new GUICmdAckPanelImage	(Base,sRoot,sName);

	return base;
}

DEFFUNCEX	void		DLL_Close(void)
{
}
DEFFUNCEX	void		ReleaseAlgorithmBase(RW3DBaseRoot *handle)
{
	delete	handle;
}
