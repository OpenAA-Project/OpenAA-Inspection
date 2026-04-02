/*
 * Copyright (C) 2025
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
{
	DLLVersion		=-1;
	LoadedVersion	=-1;
}

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