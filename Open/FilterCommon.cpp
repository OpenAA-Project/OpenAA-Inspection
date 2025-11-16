/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\FilterCommon.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XDataInLayer.h"
#include "Regulus64Version.h"
#include <QtGlobal>
#include "XFilterDLL.h"
#include "XFilterClass.h"
#include "XDLLType.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return NULL;
}
WORD	DLL_GetDLLType(void)
//	return	DLL type for FilterDLL
{
	return(DLLFilterMode);
}

bool		DLL_Close(void *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	FilterClassBase	*hBase=(FilterClassBase *)handle;
	delete	hBase;
	return true;
}
DEFFUNCEX	void	DLL_ExecuteBeforeScan	(FilterClassBase *handle)
//	Execute something image before scanning
{
	handle->ExecuteBeforeScan();
}
