/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
   fileid : saperaCtrl.cpp
  subject : Sapera SDK control functions
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <QMessageBox>
#include "swap.h"

#include "sapClassBasic.h"
#include "conio.h"
#include "XMainSchemeMemory.h"

#include "saperaCtrl.h"
#include "featureCtrl.h"
#include <omp.h>
#include "XCriticalFunc.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "CameraXtiumCISVienex.h"
#include "XLogOut.h"
#include "XGeneralFunc.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"

#define MAX_CONFIG_FILES   36       // 10 numbers + 26 lowercase letters

BOOL GetOptionsFromQuestions(char *acqServerName, UINT32 *pAcqDeviceIndex,UINT32 *pacqResourceNumber)
{
   //////// Ask questions to user to select acquisition board/device and config file ////////

   // Get total number of boards in the system
   int serverCount = SapManager::GetServerCount();
   if (serverCount == 0)
   {
      return false;
   }
   
   int devicesToSkip = 0;
   for (int serverIndex = 0; serverIndex < serverCount; serverIndex++)
   {
      if (SapManager::GetResourceCount(serverIndex, SapManager::ResourceAcqDevice) != 0)
      {
         char serverName[CORSERVER_MAX_STRLEN];
         SapManager::GetServerName(serverIndex, serverName, sizeof(serverName));
         if (strstr(serverName,"CameraLink_") > 0)
            devicesToSkip++;
      }
   }
   // Scan the boards to find those that support acquisition
   BOOL serverFound = false;
   BOOL cameraFound = false;
   int serverIndex;
   for (serverIndex = 0; serverIndex < serverCount; serverIndex++)
   {
      if (SapManager::GetResourceCount(serverIndex, SapManager::ResourceAcq) != 0)
      {
         char serverName[CORSERVER_MAX_STRLEN];
         SapManager::GetServerName(serverIndex, serverName, sizeof(serverName));
//         printf("%d: %s\n", serverIndex, serverName);
         serverFound = TRUE;
		break;
      }
	  else if (SapManager::GetResourceCount(serverIndex, SapManager::ResourceAcqDevice) != 0)
      {
         char serverName[CORSERVER_MAX_STRLEN];
         SapManager::GetServerName(serverIndex, serverName, sizeof(serverName));
         if (strstr(serverName,"CameraLink_") > 0)
            continue;
         printf("%d: %s\n", serverIndex, serverName);
         cameraFound = TRUE;
      }
   }

   // At least one acquisition server must be available
   if (!serverFound && !cameraFound)
   {
      printf("No acquisition server found!\n");
      return false;
   }

	SapManager::GetServerName(serverIndex, acqServerName, CORSERVER_MAX_STRLEN);


// Scan all the acquisition devices on that server and show menu to user
int deviceCount = SapManager::GetResourceCount(acqServerName, SapManager::ResourceAcq);
int cameraCount = (deviceCount == 0) ? SapManager::GetResourceCount(acqServerName, SapManager::ResourceAcqDevice) : 0;

	printf("\nSelect the acquisition device (or 'q' to quit)");
	printf("\n..............................................\n");

	for (int deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++)
	{
		char deviceName[CORPRM_GETSIZE(CORACQ_PRM_LABEL)];
		SapManager::GetResourceName(acqServerName, SapManager::ResourceAcq, deviceIndex, deviceName, sizeof(deviceName));
		printf("%d: %s\n", deviceIndex+1, deviceName);
	}

	if (deviceCount == 0)
	{
		for (int cameraIndex = 0; cameraIndex < cameraCount; cameraIndex++)
		{
			char cameraName[CORPRM_GETSIZE(CORACQ_PRM_LABEL)];
			SapManager::GetResourceName(acqServerName, SapManager::ResourceAcqDevice, cameraIndex, cameraName, sizeof(cameraName));
			printf("%d: %s\n", cameraIndex+1, cameraName);
		}
	}
	*pAcqDeviceIndex	=1;
	*pacqResourceNumber	=2;
	return true;
}


using namespace std;

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : saperaCtrl(void)
     arg1 : nil
   result : nil
  subject : constructor

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : bool link(void)
     arg1 : nil
   result : true	false
  subject : Sapera initialyze
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
#define	DEF_AcquisitionLineRate	(UINT32)25000	// Hz


bool CameraXtiumCISVienex::link(char *pConfigFilename)
{
	BOOL	LineActive;
	bool	Ret;
	UINT32   acqDeviceNumber = 0;
	UINT32   acqResourceNumber = 0;
	char    acqServerName[CORSERVER_MAX_STRLEN];
	BOOL	isNotSupported = false,status = false,acquisitionCreated = TRUE,acqDeviceCreated = TRUE;
	SapAcquisition::SignalStatus signalStatus=0;

	unlink();
	strcpy(ConfigFileName,pConfigFilename);
	if (!GetOptionsFromQuestions(acqServerName, &acqDeviceNumber,&acqResourceNumber)) {
		GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link", acqDeviceNumber,false);
		return false;
	}

	// Feature setting
	//if(fc==NULL)
	//	fc = new featureCtrl(acqServerName,acqDeviceNumber,acqResourceNumber);


	GSleep(100);

	//delete fc;
	//fc = NULL;

//	SapLocation loc(0, _nGioDev);
	SapLocation loc2(acqServerName, acqResourceNumber);


	if (SapManager::GetResourceCount(acqServerName, SapManager::ResourceAcq) > 0) {

		_Acq	= new SapAcquisition(loc2, pConfigFilename);

		_Buffers= new SapBuffer(GCount, _Acq);
//		_View	= new SapView(_Buffers, SapHwndAutomatic);
		_Xfer	= new SapAcqToBuf(_Acq, _Buffers, acqCallback, this);
		_Gio    = new SapGio(loc2, gioCallback, this);

		// Create acquisition object
		if (_Acq->Create()==false) {
			acquisitionCreated = false;
			GetLayersBase()->GetLogCreater()->PutLogR(__LINE__, "saperaCtrl::link-acquisitionCreated", false);
		}
		
		if(_Acq->GetSerialPortName(SerialPortName)==false){
			return false;
		}

		//GetSignalStatus();

		//if(Parent->Setting.ExternalTrigger==true) {
		//	fc->setFeatureValue(featureCtrl::EN_TriggerMode, "External");
		//}
		//else{
		//	fc->setFeatureValue(featureCtrl::EN_TriggerMode, "Internal");
		//}

		GSleep(100);

		int	MaxLines;
		MaxLines=GetMaxLines()/8;	//FixedCamLineCount;	//GetMaxLines();

		Ret=_Acq->SetParameter( CORACQ_PRM_CROP_HEIGHT, MaxLines);
		GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-CORACQ_PRM_CROP_HEIGHT", MaxLines,Ret);

		//Ret=_Acq->RegisterCallback(  SapAcquisition::EventLinkUnlock
		//							| SapAcquisition::EventHsyncUnlock
		//							| SapAcquisition::EventNoHSync
		//							| SapAcquisition::EventNoVSync
		//							,CallBackByLine,NULL);
		_Acq->GetSignalStatus(&signalStatus, SignalCallback, this);
	}
	if (!acquisitionCreated) {
		goto FreeHandles;
	}
	int	Width;
	Ret=_Acq->GetParameter( CORACQ_PRM_CROP_WIDTH, &Width );
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-CORACQ_PRM_CROP_WIDTH", Width,Ret);
	CamDotPerLine=max(Width,GetDotPerLine());
	
	GSleep(100);
	// Create buffer object
	if (_Buffers && !*_Buffers && !_Buffers->Create()) {
		goto FreeHandles;
	}

	// Create transfer object
	if (_Xfer && !*_Xfer && !_Xfer->Create()) {
		goto FreeHandles;
	}

	// Create view object
	if (_View && !*_View && !_View->Create()) {
		goto FreeHandles;
	}

	// SapGio Create
	if (_Gio && !*_Gio && !_Gio->Create()) {
		goto FreeHandles;
	}


   // release resource
	_bLinked = true;

	Terminated	=false;
	Halted		=false;

	startCaptureInside();
	//start();	//Start thread

	return true;

// error end program
FreeHandles:
	unlink();

	// release resource
	_bLinked = false;

	return false;
}

typedef struct
{
	const	char   *name;
	INT32  signalID;
	BOOL   bSignalAvailable;
}ACQ_SIGNAL_STATUS;

// COR_TEST_SIGNAL_STATUS
ACQ_SIGNAL_STATUS  g_AcqSignalStatus[] = {
	{ "Pixel Clock Present           ", SapAcquisition::SignalPixelClkPresent, false },
	{ "Pixel Clock1 Present          ", SapAcquisition::SignalPixelClk1Present, false },
	{ "Pixel Clock2 Present          ", SapAcquisition::SignalPixelClk2Present, false },
	{ "Pixel Clock3 Present          ", SapAcquisition::SignalPixelClk3Present, false },
	{ "Pixel ClockAll Present        ", SapAcquisition::SignalPixelClkAllPresent, false },
	{ "Line Valid Present            ", SapAcquisition::SignalHSyncPresent, false },
	{ "Frame Valid Present           ", SapAcquisition::SignalVSyncPresent, false },
	{ "Camera Power Present          ", SapAcquisition::SignalPowerPresent, false },
	{ "HSLink CLHS Lane lock signal  ", SapAcquisition::SignalPixelLinkLock, false }
};


void CameraXtiumCISVienex::GetSignalStatus(SapAcquisition::SignalStatus signalStatus)
{
	BOOL	m_IsSignalDetected = (signalStatus != SapAcquisition::SignalNone);

	char signalName[128];

	int  nSignal = sizeof(g_AcqSignalStatus) / sizeof(g_AcqSignalStatus[0]);
	BOOL signalAvailable = false;
	QString str;

	for (int i = 0; i < nSignal; i++)
	{
		strcpy_s(signalName, sizeof(signalName), g_AcqSignalStatus[i].name);

		signalAvailable = _Acq->IsSignalStatusAvailable(g_AcqSignalStatus[i].signalID);
		if (signalAvailable)
		{
			if ((signalStatus & g_AcqSignalStatus[i].signalID) == g_AcqSignalStatus[i].signalID)
			{
				str=QString("Yes ")+signalName;
			}
			else
			{
				str=QString("No ")+signalName;
			}
		}
		else
		{
			str=QString("No ")+signalName;
		}
	}
}


void CameraXtiumCISVienex::SignalCallback(SapAcqCallbackInfo *pInfo)
{
	SapAcquisition::SignalStatus status=pInfo->GetSignalStatus();
	if((status & SapAcquisition::SignalPixelLinkLock)==0){
		CameraXtiumCISVienex *pDlg = (CameraXtiumCISVienex *) pInfo->GetContext();
		//pDlg->SignalOutCamError();
	}
}


void CameraXtiumCISVienex::GetSignalStatus()
{

	if (_Acq && _Acq->IsSignalStatusAvailable())
	{
		if (_Acq->GetSignalStatus(&signalStatus, SignalCallback, this))
			GetSignalStatus(signalStatus);
	}
}
bool CameraXtiumCISVienex::ChangeLineCount(int XLen ,int YLen ,int LayerCount)
{
	//Terminated=true;
	//wait(1000);
	bool	Ret;


	UINT32   acqDeviceNumber = 0;
	UINT32   acqResourceNumber = 0;
	char    acqServerName[CORSERVER_MAX_STRLEN];
	BOOL	isNotSupported = false,status = false,acquisitionCreated = TRUE,acqDeviceCreated = TRUE;

	if (!GetOptionsFromQuestions(acqServerName, &acqDeviceNumber,&acqResourceNumber)) {
		return false;
	}
	SapLocation loc2(acqServerName, acqResourceNumber);

	if (_Gio && *_Gio) _Gio->Destroy();

	// Destroy view object
	if (_View && *_View) _View->Destroy();

	// Destroy transfer object
	if (_Xfer && *_Xfer) _Xfer->Destroy();

	// Destroy buffer object
	if (_Buffers && *_Buffers) _Buffers->Destroy();

	if (_Acq && *_Acq) _Acq->Destroy();

	// Delete all objects
	if (_Gio)		delete _Gio;
	if (_View)		delete _View;
	if (_Xfer)		delete _Xfer;
	if (_Buffers)	delete _Buffers;
	if (_Acq)		delete _Acq;

	GSleep(100);

	_Acq	= new SapAcquisition(loc2, ConfigFileName);
	_Buffers= new SapBuffer(GCount, _Acq);
	_Xfer	= new SapAcqToBuf(_Acq, _Buffers, acqCallback, this);
	_Gio    = new SapGio(loc2, gioCallback, this);

	if (_Acq && !*_Acq && !_Acq->Create()) {
		acquisitionCreated = false;
	}
	
	//_Acq->GetSignalStatus(SapAcquisition::SignalHSyncPresent, &LineActive);
	GetSignalStatus();

	GSleep(100);

	for(int layer=0;layer<LayerCount;layer++){
		ImageStack[layer].Set(0,0,XLen,YLen);
	}
	int	MaxLines;
	MaxLines=(GetMaxLines()/8)*8;	//FixedCamLineCount;	//GetMaxLines();

	Ret=_Acq->SetParameter( CORACQ_PRM_CROP_HEIGHT, MaxLines);
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-CORACQ_PRM_CROP_HEIGHT", MaxLines,Ret);

	int	Width;
	Ret=_Acq->GetParameter( CORACQ_PRM_CROP_WIDTH, &Width );
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-CORACQ_PRM_CROP_WIDTH", Width,Ret);
	CamDotPerLine=max(Width,GetDotPerLine());
	
	GSleep(100);
	// Create buffer object
	if (_Buffers && !*_Buffers && !_Buffers->Create()) {
		goto FreeHandles;
	}

	// Create transfer object
	if (_Xfer && !*_Xfer && !_Xfer->Create()) {
		goto FreeHandles;
	}

	// Create view object
	if (_View && !*_View && !_View->Create()) {
		goto FreeHandles;
	}

	// SapGio Create
	if (_Gio && !*_Gio && !_Gio->Create()) {
		goto FreeHandles;
	}
	GSleep(100);


	Terminated	=false;
	Halted		=false;
	_nStatus = EN_CTRLSTS_IDLE;

	startCaptureInside();
	//start();

	return true;

FreeHandles:
	unlink();
	return false;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : bool startCapture(void)
     arg1 : nil
   result : true	false
  subject : Start capture
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
bool CameraXtiumCISVienex::startCapture(void)
{
	//Halted=false;
	return true;
}

bool CameraXtiumCISVienex::startCaptureInside(void)
{
	if (_bLinked) {
		// start reserve.
		if (_nStatus != EN_CTRLSTS_IDLE) {
			_nStartReserve++;
			return true;
		}
		_nStatus = EN_CTRLSTS_CAPTURE;
		// Start continous grab
		_Xfer->Grab();
//		_Xfer->Snap();
//		_Xfer->Wait(DEF_FRAME_WAIT);
		return true;
	}
	return false;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : bool startCapture(void)
     arg1 : nil
   result : true	false
  subject : Start capture
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
bool CameraXtiumCISVienex::stopCapture(void)
{
	Halted=true;
	return true;
	/*
	if (_bLinked) {
		// Stop grab
		_Xfer->Freeze();
		if (!_Xfer->Wait(1000)) {
			_Xfer->Abort();
			unlink();
			return true;
		}
	}
	unlink();
	return false;
	*/
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : bool unlink(void)
     arg1 : nil
   result : true	false
  subject : Sapera 初期化を行います。
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
bool CameraXtiumCISVienex::unlink(void)
{
	Terminated=true;

	_bLinked = false;
	_nStatus = EN_CTRLSTS_IDLE;
	_nStartReserve = 0;

	// Destroy FeatureInfo object
	if (_Gio && *_Gio) _Gio->Destroy();

	// Destroy FeatureInfo object
	if (_FeatureInfo && *_FeatureInfo) _FeatureInfo->Destroy();

	// Destroy buffer object
	if (_Bayer && *_Bayer) _Bayer->Destroy();

	// Destroy view object
	if (_View && *_View) _View->Destroy();

	// Destroy transfer object
	if (_Xfer && *_Xfer) _Xfer->Destroy();

	// Destroy buffer object
	if (_Buffers && *_Buffers) _Buffers->Destroy();

	// Destroy acquisition object
	if (_Acq && *_Acq) _Acq->Destroy();

	// Destroy acquisition object
	if (_AcqDevice && *_AcqDevice) _AcqDevice->Destroy();

	// Delete all objects
	if (_Gio)		delete _Gio;
	if (_FeatureInfo) delete _FeatureInfo;
	if (_Bayer)		delete _Bayer;
	if (_View)		delete _View;
	if (_Xfer)		delete _Xfer;
	if (_Buffers)	delete _Buffers;
	if (_Acq)		delete _Acq;
	if (_AcqDevice)	delete _AcqDevice;

	_Gio		 = NULL;
	_FeatureInfo = NULL;
	_Bayer		 = NULL;
	_View		 = NULL;
	_Xfer		 = NULL;
	_Buffers	 = NULL;
	_Acq		 = NULL;
	_AcqDevice	 = NULL;

	//wait(200);

	return true;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : void acqCallback(SapXferCallbackInfo *pInfo)
     arg1 : SapXferCallbackInfo *pInfo
   result : nil
  subject : カメラデータ到着でCallbackされます。
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
void CameraXtiumCISVienex::acqCallback(SapXferCallbackInfo *pInfo)
{
	CameraXtiumCISVienex *pSapera = (CameraXtiumCISVienex *)pInfo->GetContext();

	pSapera->CaptureImage();
	pSapera->_nStatus = EN_CTRLSTS_GRABED;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : void gioCallback(SapGioCallbackInfo *pInfo)
     arg1 : SapGioCallbackInfo *pInfo
   result : nil
  subject : GIO callback funvtion
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
void CameraXtiumCISVienex::gioCallback(SapGioCallbackInfo *pInfo)
{
	CameraXtiumCISVienex *pSapera = (CameraXtiumCISVienex *)pInfo->GetContext();;

	SapGio *pGio = pSapera->_Gio;
	SapGio::PinState *states = NULL;
	bool r;

	states = new SapGio::PinState[pSapera->_Gio->GetNumPins()];
	pSapera->_Gio->SetDisplayStatusMode(SapManager::StatusLog, NULL);
	r = pSapera->_Gio->GetPinState(states);
	pSapera->_Gio->SetDisplayStatusMode(SapManager::StatusNotify, NULL);

	//if (r && states[CONST_IO_PIN_NUM] == SapGio::PinHigh) {
	//	pSapera->_nStatus = EN_CTRLSTS_GRABED;
	//}
	delete states;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : int prepareCapture(void)
     arg1 : nil
   result : true	false
  subject : キャプチャ開始準備
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
bool CameraXtiumCISVienex::prepareCapture(void)
{
	//if(isRunning()==false){
	//	Terminated=false;
	//	start();
	//}
	return true;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : int getStatus(void)
     arg1 : nil
   result : _nStatus
  subject : 現在のステータスを戻り値に返します。
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
int CameraXtiumCISVienex::getStatusInside(void)
{
	//BOOL	LineActive;
	//_Acq->GetSignalStatus(SapAcquisition::SignalHSyncPresent, &LineActive);
	//if(LineActive==false) {
	//	LineValid=false;
	//	return 0x100;
	//}
	//else {
	//	LineValid=true;
	//}

	if (_nStatus == EN_CTRLSTS_GRABED) return 0;

	return 1;
}


/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : bool ValidateWhiteBalance(int value, int minValue, int maxValue)
     arg1 : int value		評価する値
     arg2 : int minValue	最小値
     arg3 : int maxValue	最大値
   result : true	false
  subject : 指定の値を評価し、その結果を戻り値に返します。
////////////////////////////////////////////////////////////////////////////////////////////////////////// */

bool	CameraXtiumCISVienex::SetQuickProperty(CameraQuickProperty Attr, double RelativeValue)
{
	return true;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : bool ValidateWhiteBalance(int value, int minValue, int maxValue)
     arg1 : int value		評価する値
     arg2 : int minValue	最小値
     arg3 : int maxValue	最大値
   result : true	false
  subject : 指定の値を評価し、その結果を戻り値に返します。
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
//void saperaCtrl::setFeature()
//{
//}

DWORD	ListedTime1[1000];
DWORD	ListedTime2[1000];
int		ListedTimeCounter=0;


//void	CameraXtiumCISVienex::run()
//{
//	DWORD	PassedTime;
//	startCaptureInside();
//	DWORD	StartTime=::GetComputerMiliSec();
//
//	while(Terminated==false){
//		GSleep(1000);
//	}
//}