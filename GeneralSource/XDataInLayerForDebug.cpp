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

#include "XTypeDef.h"
#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <QReadWriteLock>
#include <stdlib.h>
#include <QTimer>
#include <QThread>
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XAlert.h"
#include "XPointer.h"
#include "XDLLType.h"
#include "XAlgorithmInterfaceDLL.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "Regulus64Version.h"
#include "XDataInLayerCommander.h"
#include "XResultDLLManager.h"
#include "XDatabase.h"
#include <omp.h>
#include "SelectPasteForm.h"
#include "XTransferInterface.h"
#include "XTransfer.h"
#include "XCriticalFunc.h"
#include "XDatabaseLoader.h"
#include "XPieceArchitect.h"
#include "OnProcessingForm.h"
#include "XCrossObj.h"
#include "XDirectComm.h"
#include "XLightInterfaceDLL.h"
#include "XLightClass.h"
#include "ServiceLibResource.h"
#include "XGUIFormBase.h"
#include "XFilterManager.h"
#include "XErrorCode.h"
#include "XFileRegistry.h"
#include "XOutlineOffset.h"
#include "XLogo.h"
#include "XAnyData.h"
#include <QMessageBox>
#include "XDirectComm.h"
#include "XGeneralStocker.h"
#include "XLearningRule.h"
#include "XPassword.h"
#include "XDisplayImagePacket.h"
#include "XServiceForLayers.h"
#include "XGUI.h"
#include "XSyncGUI.h"
#include "XStatusController.h"
#include "XLearningRegist.h"
#include "XImageProcess.h"
#include "ShowLoadingDLLForm.h"
#include "XLotInformation.h"
#include "XHistgramByParam.h"
#include "XDateTime.h"
#include "AlertDialog.h"
#include "XShareMasterData.h"
#include "XCSV.h"
#include "XPrinterManager.h"
#include "XImageExpand.h"
#include "XIntegrationComm.h"
#include "XIntegrationBase.h"
#include "XIntegrationPacketComm.h"
#include "XResize.h"
#include "XResultAnalizer.h"
#include "XDirectCommPacket.h"
#include "XDataInLayerToDisplayImage.h"
#include "ThreadSequence.h"
#include "XDataInLayerCmdLocal.h"
#include "XFilterInstance.h"
#include "XCameraClass.h"
#include "XAuthenticationInside.h"
#include "XResult.h"
#include "XWriteResultThread.h"
#include "XLibraryType.h"
#include "XArrangementFromFile.h"
#include "XLogOut.h"
#include "XParamDatabase.h"
#include "XImageStocker.h"
#include "XLanguageStockerLoader.h"
#include "XShadowTree.h"
#include "XFileThread.h"
#include "XLevel.h"
#include "SelectThresholdLevelDialog.h"
#include "XMultiLayerColor.h"


bool	LayersBase::PickupGUILanguage(void)
{
	GUIFormBase *GUIRet[10000]; 
	
	int n=GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->EnumGUIInst(GUIRet,10000);

	for(int i=0;i<n;i++){
		GUIRet[i]->PickupGUILanguage(GUILanguageContainerInst);
	}
	return true;
}
