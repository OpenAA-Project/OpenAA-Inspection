/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XCameraHandle.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include <QtGui>
#include <QIODevice>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QApplication>
#include <QProgressBar>
#include <QSqlDatabase>
#include "XIntClass.h"
#include "XCameraClass.h"
#include "XCameraHandle.h"
#include "XCameraInterfaceDLL.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "XErrorMessage.h"
#include "swap.h"
#include "XLogOut.h"
#include "Regulus64System.h"

//=========================================================================================
CameraHandle::CameraHandle(int _CamNo ,LayersBase *base)
	:ServiceForLayers(base),CamNo(_CamNo)
{}

int		CameraHandle::GetDotPerLine(void)
{
	return GetParamGlobal()->GetDotPerLineInCamera(CamNo);
}
int		CameraHandle::GetMaxLines(void)
{
	return GetParamGlobal()->GetMaxLinesInCamera(CamNo);
}


void	CameraHandle::EmitSignalCaptured(void)
{
	emit	CameraHandleSignalCaptured();
}