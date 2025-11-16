/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ExecuteVisualizer\EVObjCamera\EVObjCamera.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EVObjCamera.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "XEVObjCamera.h"
#include "EVObjDLL.h"

static	const	char	*sRoot="Environment";
static	const	char	*sName="EVObjCamera";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Normal camera");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	RunnerObject	*DLL_CreateInstance(LayersBase *Base,RunnerMap *rmap)
{
	return(new RunnerCamera(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}


