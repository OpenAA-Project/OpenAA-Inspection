/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XEntryPointWithSequence.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <stdlib.h>
#include <QTimer>
#include <QThread>
#include "XDataInLayer.h"
//#include "AlertDialog.h"
#include "XShareMasterData.h"
#include "XCameraClass.h"
#include "XGUI.h"
#include "XDataInExe.h"
#include "XGeneralFunc.h"
#include "XExecuteInspectBase.h"
#include "ThreadSequence.h"

void	EntryPointForGlobal::LoopOnIdle(void)
{
	if(GetExecuteInspect()!=NULL){
		if(GetExecuteInspect()->IsLocalCamera()==true){
			for(int cam=0;cam<GetLayersBase()->GetParamGlobal()->TotalCameraNumb;cam++){
				CameraClass	*c=GetExecuteInspect()->GetCamera(cam);
				if(c!=NULL){
					c->LoopOnIdle();
				}
			}
		}
	}
	if(GetThreadSequence()!=NULL){
		GetThreadSequence()->LoopOnIdle();
	}
}