
#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <stdlib.h>
#include <QTimer>
#include <QThread>
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XAlert.h"
#include "XPointer.h"
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
#include "XTransfer.h"
#include "XCriticalFunc.h"
#include "XDatabaseLoader.h"
#include "XPieceArchitect.h"
#include "OnProcessingForm.h"
#include "XCrossObj.h"
#include "XDirectComm.h"
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
#include "XServiceForLayers.h"
#include "XGUI.h"
#include "XSyncGUI.h"
#include "XStatusController.h"
#include "XLearningRegist.h"
#include "XImageProcess.h"
#include "XDateTime.h"
#include "XShareMasterData.h"
#include "XPrinterManager.h"
#include "XPointer.h"
#include "XIntegrationComm.h"
#include "XIntegrationPacketComm.h"


	
void	LayersBase::LockMutexCommErrorList(void)
{
	MutexCommErrorList.lock();
}

void	LayersBase::UnlockMutexCommErrorList(void)
{
	MutexCommErrorList.unlock();
}

void	LayersBase::SetCommErrorNoAck(int globalpage,const QString &ClassNameStr)
{
	CommErrorList	*r=new CommErrorList;
	r->GlobalPage	=globalpage;
	r->ClassNameStr	=ClassNameStr;
	r->TM			=XDateTime::currentDateTime();
	MutexCommErrorList.lock();
	CommErrorListContainer.AppendList(r);
	if(CommErrorListContainer.GetCount()>MaxCommErrorList){
		CommErrorList	*L=CommErrorListContainer.GetFirst();
		CommErrorListContainer.RemoveList(L);
		delete	L;
	}
	MutexCommErrorList.unlock();
}
void	LayersBase::SetCommErrorNoAck(int SlaveNo,int GlobalPage,const QString &ClassNameStr)
{
	CommErrorList	*r=new CommErrorList;
	r->GlobalPage	=GlobalPage;
	r->SlaveNo		=SlaveNo;
	r->ClassNameStr	=ClassNameStr;
	r->TM			=XDateTime::currentDateTime();
	MutexCommErrorList.lock();
	CommErrorListContainer.AppendList(r);
	if(CommErrorListContainer.GetCount()>MaxCommErrorList){
		CommErrorList	*L=CommErrorListContainer.GetFirst();
		CommErrorListContainer.RemoveList(L);
		delete	L;
	}
	MutexCommErrorList.unlock();
}

