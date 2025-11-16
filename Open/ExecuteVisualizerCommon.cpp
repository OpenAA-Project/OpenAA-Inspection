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
#include "XDLLType.h"
//#include <QtGlobal>

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return NULL;
}

WORD	DLL_GetDLLType(void)
//	return	DLL type for FilterDLL
{
	return(DLLExecuteVisualizerMode);
}

bool		_cdecl	DLL_Close(void *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	delete	handle;
	return true;
}
