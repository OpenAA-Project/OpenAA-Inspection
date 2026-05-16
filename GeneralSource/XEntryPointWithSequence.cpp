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
#include "XHistgramByParam.h"
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