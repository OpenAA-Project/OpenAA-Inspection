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
#include "CameraXtiumPx8Repeat.h"
#include "XLogOut.h"
#include "XGeneralFunc.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"

#define MAX_CONFIG_FILES   36       // 10 numbers + 26 lowercase letters

BOOL GetOptionsFromQuestions(char *acqServerName, UINT32 *pAcqDeviceIndex)
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
	*pAcqDeviceIndex = 1;
	return true;
}


using namespace std;

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : saperaCtrl(void)
     arg1 : nil
   result : nil
  subject : constructor
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
saperaCtrl::saperaCtrl(int CamNo ,LayersBase *base,CameraXtiumPx8Repeat *parent)
	:QThread(base->GetMainWidget()), CameraHandle(CamNo,base) ,Parent(parent)
{
	_Acq		= NULL;
	_AcqDevice	= NULL;
	_Buffers	= NULL;
	_Xfer		= NULL;
	_View		= NULL;
	_Bayer		= NULL;
	_FeatureInfo= NULL;
	_Gio		= NULL;
	_bLinked	= false;
	_nStatus	= EN_CTRLSTS_IDLE;		// 制御用
	_nGioDev	= 0;
	_nStartReserve = 0;
	fc			=NULL;
	GCount		=MaxGCount;
	CurrentGPos	=0;
	LineValid	=true;
	Calibrated	=false;

	_gainMax = 0.0;
	_gainMin = 0.0;
	_currentGain = 0.0;
	CONST_MAX_COEF = 1.05;

	Terminated	=false;
	Halted		=false;
	RepeatON	=true;
	Index		=-1;
	FirstCapture=true;
	ResetPoint();
	CurrentWPage=-1;

	setPriority(QThread::HighPriority);
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : ~saperaCtrl(void)
     arg1 : nil
   result : nil
  subject : destructor
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
saperaCtrl::~saperaCtrl(void)
{
	Terminated=true;
	wait(1000);
	delete	fc;
	unlink();
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : bool link(void)
     arg1 : nil
   result : true	false
  subject : Sapera initialyze
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
#define	DEF_AcquisitionLineRate	(UINT32)25000	// Hz

static	int	CallBackCounter;

void	saperaCtrl::CallBackByLine(SapAcqCallbackInfo *pInfo)
{
}

bool saperaCtrl::link(char *pConfigFilename)
{
	BOOL	LineActive;
	bool	Ret;
	UINT32   acqDeviceNumber = 0;
	char    acqServerName[CORSERVER_MAX_STRLEN];
	BOOL	isNotSupported = false,status = false,acquisitionCreated = TRUE,acqDeviceCreated = TRUE;
	SapAcquisition::SignalStatus signalStatus=0;

	unlink();
	strcpy(ConfigFileName,pConfigFilename);
	if (!GetOptionsFromQuestions(acqServerName, &acqDeviceNumber)) {
		GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link", acqDeviceNumber,false);
		return false;
	}

	// Feature setting
	if(fc==NULL)
		fc = new featureCtrl(acqServerName);


	GSleep(100);

	//delete fc;
	//fc = NULL;

//	SapLocation loc(0, _nGioDev);
	SapLocation loc2(acqServerName, acqDeviceNumber);


	if (SapManager::GetResourceCount(acqServerName, SapManager::ResourceAcq) > 0) {
		// SapGio Instanciate
		//_Gio	= new SapGio(loc2);
		_Acq	= new SapAcquisition(loc2, pConfigFilename);

		_Buffers= new SapBuffer(GCount, _Acq);
//		_View	= new SapView(_Buffers, SapHwndAutomatic);
		_Xfer	= new SapAcqToBuf(_Acq, _Buffers, acqCallback, this);
		_Gio    = new SapGio(loc2, gioCallback, this);

		// Create acquisition object
		if (_Acq && !*_Acq && !_Acq->Create()) {
			acquisitionCreated = false;
			GetLayersBase()->GetLogCreater()->PutLogR(__LINE__, "saperaCtrl::link-acquisitionCreated", false);
		}
		
		GetSignalStatus();

		//if(Parent->Setting.ExternalTrigger==true) {
		//	fc->setFeatureValue(featureCtrl::EN_TriggerMode, "External");
		//}
		//else{
		//	fc->setFeatureValue(featureCtrl::EN_TriggerMode, "Internal");
		//}

		GSleep(100);

		int	MaxLines;
		MaxLines=GetMaxLines()/8;	//FixedCamLineCount;	//GetMaxLines();

		Ret=_Acq->SetParameter( CORACQ_PRM_CROP_HEIGHT, MaxLines-OverlapYLen/8 );
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
	Parent->CamDotPerLine=max(Width,GetDotPerLine());
	
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

/*
	// save current gain value
	_gainMax=0, _gainMin=0, _currentGain =0;
	_AcqDevice->GetFeatureInfo("Gain", &feature);
	feature.GetMax(&_gainMax);
	feature.GetMin(&_gainMin);
	_gainMax = floor(_gainMax);     // Round down to previous integer 標準関数のようです。切り捨て。
	_gainMin = ceil(_gainMin);      // Round up to next integer 標準関数のようです。切り上げ。

	// Get current Gain value in camera
	status = _AcqDevice->GetFeatureValue("Gain", &_currentGain);
*/
	//Ret=_Xfer->Freeze();


   // release resource
	_bLinked = true;

	AllocateBuff();

	Terminated	=false;
	Halted		=false;
	start();	//Start thread

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
void	saperaCtrl::ResetPoint(void)
{
	MutexStackedLineCount.lock();
	CurrentWPage=0;
	CurrentRPage=0;

	for(int page=0;page<GetPageNumb();page++){
		StateInPage[page]=-1;
	}
	CurrentWPoint=0;
	CurrentRPoint=0;
	MutexStackedLineCount.unlock();
}

void saperaCtrl::GetSignalStatus(SapAcquisition::SignalStatus signalStatus)
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
void	saperaCtrl::SignalOutCamError()
{
	emit	SignalLinkOut();
}

void saperaCtrl::SignalCallback(SapAcqCallbackInfo *pInfo)
{
	SapAcquisition::SignalStatus status=pInfo->GetSignalStatus();
	if((status & SapAcquisition::SignalPixelLinkLock)==0){
		//QMessageBox::critical(NULL,"Error","No signal");
		saperaCtrl *pDlg = (saperaCtrl *) pInfo->GetContext();
		pDlg->SignalOutCamError();
	}
	//
	//pDlg->GetSignalStatus(pInfo->GetSignalStatus());
}


void saperaCtrl::GetSignalStatus()
{

	if (_Acq && _Acq->IsSignalStatusAvailable())
	{
		if (_Acq->GetSignalStatus(&signalStatus, SignalCallback, this))
			GetSignalStatus(signalStatus);
	}
}
bool saperaCtrl::ChangeLineCount(int YCount)
{
	Terminated=true;
	wait(1000);
	bool	Ret;

	//GSleep(3000);
	//Ret=fc->setFeatureValue("initializeBlackLevel", true);
	GSleep(1000);

	UINT64 BinningHorizontal;
	UINT64 BinningVertical;
	Ret=fc->getFeatureValue("BinningHorizontal", &BinningHorizontal);
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningHorizontal"	,BinningHorizontal,Ret);
	Ret=fc->getFeatureValue("BinningVertical"	 , &BinningVertical);
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningVertical"	,BinningVertical,Ret);

	Ret=fc->setFeatureValue("AcquisitionStop", true);
	GetLayersBase()->GetLogCreater()->PutLogR(__LINE__, "saperaCtrl::link-AcquisitionoStop", Ret);

	bool	StopMode;
	StopMode=true;
	BOOL isAvailable;
	GSleep(2000);

	BinningVertical=Parent->Setting.VerticalBinning;
	if(BinningVertical>2)
		BinningVertical=2;
	Ret=fc->setFeatureValueWithStop("BinningVertical", BinningVertical);
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningVertical", BinningVertical,Ret);

	UINT64	DotPerLine=Parent->GetDotPerLine();
	Ret=fc->setFeatureValueWithStop("multipleROIWidth", DotPerLine);

	UINT64	ImageStart=(Parent->Setting.ImageStart/64)*64;
	Ret=fc->setFeatureValueWithStop("multipleROIOffsetX", ImageStart);

	Ret=fc->setFeatureValue("blackLevelEnable","False" );
	Ret=fc->setFeatureValue("lutMode","Gamma" );
	Ret=fc->setFeatureValue("imageDistortionCorrectionMode","Active" );
	Ret=fc->setFeatureValue("imageDistortionCorrectionLineSelector","Red" );
	Ret=fc->setFeatureValue("imageDistortionParallaxCorrectionPixelStretch",3.0);

	GSleep(300);
	Ret=fc->setFeatureValue("flatfieldCalibrationFPN",true );
	GSleep(300);
	Ret=fc->setFeatureValue("flatfieldCalibrationFPN",true );
	GSleep(300);

	Ret=fc->setFeatureValue("AcquisitionStart", true);
	GetLayersBase()->GetLogCreater()->PutLogR(__LINE__, "saperaCtrl::link-AcquisitionStart", Ret);

	BinningHorizontal=0;
	BinningVertical	=0;
	Ret=fc->getFeatureValue("BinningHorizontal"	, &BinningHorizontal);
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningHorizontal", BinningHorizontal,Ret);
	Ret=fc->getFeatureValue("BinningVertical"	, &BinningVertical);
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningVertical", BinningVertical,Ret);

	ImageStart=0;
	fc->getFeatureValue("multipleROIOffsetX"	, &ImageStart);
	DotPerLine=0;
	fc->getFeatureValue("multipleROIWidth"	, &DotPerLine);

	wait(1000);

	UINT32   acqDeviceNumber = 0;
	char    acqServerName[CORSERVER_MAX_STRLEN];
	BOOL	isNotSupported = false,status = false,acquisitionCreated = TRUE,acqDeviceCreated = TRUE;

	if (!GetOptionsFromQuestions(acqServerName, &acqDeviceNumber)) {
		return false;
	}
	SapLocation loc2(acqServerName, acqDeviceNumber);

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


	int	MaxLines;
	MaxLines=GetMaxLines()/8;	//FixedCamLineCount;	//GetMaxLines();

	Ret=_Acq->SetParameter( CORACQ_PRM_CROP_HEIGHT, MaxLines-OverlapYLen/8 );
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-CORACQ_PRM_CROP_HEIGHT", MaxLines,Ret);

	int	Width;
	Ret=_Acq->GetParameter( CORACQ_PRM_CROP_WIDTH, &Width );
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-CORACQ_PRM_CROP_WIDTH", Width,Ret);
	Parent->CamDotPerLine=max(Width,GetDotPerLine());
	
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

	AllocateBuff();
	ResetPoint();
	FirstCapture=true;
	Index=-1;

	Terminated	=false;
	Halted		=false;
	_nStatus = EN_CTRLSTS_IDLE;

	start();

	return true;

FreeHandles:
	unlink();
	return false;
}
bool	saperaCtrl::SetCalibration(void)
{
	bool	Ret=true;
	Ret=fc->setFeatureValue("flatfieldCalibrationFPN",true );
	GSleep(300);
	Ret=fc->setFeatureValue("flatfieldCalibrationFPN",true );
	GSleep(300);
	Calibrated=true;
	GSleep(1000);

	return Ret;
}

void saperaCtrl::AllocateBuff(void)
{
	LockAccessImage.lock();
	LockGetImage.lock();
	CurrentRPoint=0;
	CurrentWPoint=0;
	LockGetImage.unlock();
	LockAccessImage.unlock();
}
/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : bool startCapture(void)
     arg1 : nil
   result : true	false
  subject : Start capture
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
bool saperaCtrl::startCapture(void)
{
	//Halted=false;
	return true;
}

bool saperaCtrl::startCaptureInside(void)
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
bool saperaCtrl::stopCapture(void)
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
bool saperaCtrl::unlink(void)
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

	wait(200);

	return true;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : void acqCallback(SapXferCallbackInfo *pInfo)
     arg1 : SapXferCallbackInfo *pInfo
   result : nil
  subject : カメラデータ到着でCallbackされます。
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
void saperaCtrl::acqCallback(SapXferCallbackInfo *pInfo)
{
	saperaCtrl *pSapera = (saperaCtrl *)pInfo->GetContext();

	pSapera->_nStatus = EN_CTRLSTS_GRABED;
	pSapera->CaptureImage();
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : void gioCallback(SapGioCallbackInfo *pInfo)
     arg1 : SapGioCallbackInfo *pInfo
   result : nil
  subject : GIO callback funvtion
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
void saperaCtrl::gioCallback(SapGioCallbackInfo *pInfo)
{
	saperaCtrl *pSapera = (saperaCtrl *)pInfo->GetContext();;

	SapGio *pGio = pSapera->_Gio;
	SapGio::PinState *states = NULL;
	bool r;

	states = new SapGio::PinState[pSapera->_Gio->GetNumPins()];
	pSapera->_Gio->SetDisplayStatusMode(SapManager::StatusLog, NULL);
	r = pSapera->_Gio->GetPinState(states);
	pSapera->_Gio->SetDisplayStatusMode(SapManager::StatusNotify, NULL);

	if (r && states[CONST_IO_PIN_NUM] == SapGio::PinHigh) {
		pSapera->_nStatus = EN_CTRLSTS_GRABED;
		// Start continous grab
		//pSapera->_Xfer->Grab();
	}
	delete states;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : bool updateLUT(SapBuffer* Buffers, SapLut* m_pLut, char *chAcqLutName)
     arg1 : SapXferCallbackInfo *pInfo
   result : nil
  subject : LUT update
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
bool saperaCtrl::updateLUT(SapBuffer* Buffers, SapLut* m_pLut, char *chAcqLutName, int unLutMode)
{
#if 0
	//////// Ask questions to user to select LUT mode ////////
	DWORD prmIndex = 1;
	char acqLutFileName[STRING_LENGTH];

//	if (unLutMode>=EN_LTU_MODE_MAX) return false;

	switch (unLutMode) {
	case EN_LUT_MODE_NORMAL:
		m_pLut->Normal();
		CorStrncpy(acqLutFileName, "Normal_Lut_Mode.lut", sizeof("Normal_Lut_Mode.lut"));
		CorStrncpy(chAcqLutName, "Normal Lut", sizeof("Normal Lut"));
		break;

	case EN_LUT_MODE_ARITHMENTIC:
		int operationMode = 0;//Linear plus offset with clip
		/*
			Others operations available
		*/
		//int operation = 1;//Linear minus offset(absolute)
		//int operation = 2;//Linear minus offset(with clip)
		//int operation = 3;//Linear with lower clip
		//int operation = 4;//Linear with upper clip
		//int operation = 5;//Scale to maximum limit

		SapData offSet;
		offSet = SetDataValue(Buffers, &prmIndex);
		m_pLut->Arithmetic((SapLut::ArithmeticOp)operationMode, offSet);
		CorStrncpy(acqLutFileName, "Arithmetic_Lut_Mode.lut", sizeof("Arithmetic_Lut_Mode.lut"));
		CorStrncpy(chAcqLutName, "Arithmetic Lut", sizeof("Arithmetic Lut"));
		break;

	case EN_LUT_MODE_BINARY:
		SapData clipValue;
		clipValue = SetDataValue(Buffers, &prmIndex);
		m_pLut->BinaryPattern(0, clipValue);
		CorStrncpy(acqLutFileName, "Binary_Lut_Mode.lut", sizeof("Binary_Lut_Mode.lut"));
		CorStrncpy(chAcqLutName, "Binary Lut", sizeof("Binary Lut"));
		break;

	case EN_LUT_MODE_BOOLEAN:
		SapData booleanFunction;
		booleanFunction = SetDataValue(Buffers, &prmIndex);
		m_pLut->Boolean((SapLut::BooleanOp)0, booleanFunction);
		/*
			Others operations available
		*/
		// AND
		//m_pLut->Boolean((SapLut::BooleanOp)1, booleanFunction);
		// OR
		//m_pLut->Boolean((SapLut::BooleanOp)2, booleanFunction);
		// XOR
		CorStrncpy(acqLutFileName, "Boolean_Lut_Mode.lut", sizeof("Boolean_Lut_Mode.lut"));
		CorStrncpy(chAcqLutName, "Boolean Lut", sizeof("Boolean Lut"));
		break;

	case EN_LUT_MODE_GAMMA:
		int gammaFactor = (int)(2*GAMMA_FACTOR);
		m_pLut->Gamma((float)gammaFactor/GAMMA_FACTOR);
		CorStrncpy(acqLutFileName, "Gamma_Lut_Mode.lut", sizeof("Gamma_Lut_Mode.lut"));
		CorStrncpy(chAcqLutName, "Gamma Lut", sizeof("Gamma Lut"));
		break;

	case EN_LUT_MODE_REVERS:
		m_pLut->Reverse();
		CorStrncpy(acqLutFileName, "Reverse_Lut_Mode.lut", sizeof("Reverse_Lut_Mode.lut"));
		CorStrncpy(chAcqLutName, "Reverse Lut", sizeof("Reverse Lut"));
		break;

	case EN_LUT_MODE_ROLL:
		int numEntries = 128;
		m_pLut->Roll(numEntries);
		CorStrncpy(acqLutFileName, "Roll_Lut_Mode.lut", sizeof("Roll_Lut_Mode.lut"));
		CorStrncpy(chAcqLutName, "Roll Lut", sizeof("Roll Lut"));
		break;

	case EN_LUT_MODE_SHIFT:
		int bitsToShift = 3;
		m_pLut->Shift(bitsToShift);
		CorStrncpy(acqLutFileName, "Shift_Lut_Mode.lut", sizeof("Shift_Lut_Mode.lut"));
		CorStrncpy(chAcqLutName, "Shift Lut", sizeof("Shift Lut"));
		break;

	case EN_LUT_MODE_SLOPE:
		int startIndex1 = 76;
		int endIndex1 = 179;
		BOOL clipOutSide = false;//TRUE
		SapData minValue;
		SapData maxValue;
		minValue = SetDataValue(Buffers, &prmIndex);
		maxValue = SetDataValue(Buffers, &prmIndex);
		m_pLut->Slope(startIndex1, endIndex1, minValue, maxValue, clipOutSide);
		CorStrncpy(acqLutFileName, "Slope_With_Range_Lut_Mode.lut", sizeof("Slope_With_Range_Lut_Mode.lut"));
		CorStrncpy(chAcqLutName, "Slope With Range Lut", sizeof("Slope With Range Lut"));
		break;

	case EN_LUT_MODE_SINGLE:
		SapData treshValue;
		treshValue = SetDataValue(Buffers, &prmIndex);
		m_pLut->Threshold(treshValue);
		CorStrncpy(acqLutFileName, "Threshold_Single_Mode.lut", sizeof("Threshold_Single_Mode.lut"));
		CorStrncpy(chAcqLutName, "Threshold Single Lut", sizeof("Threshold Single Lut"));
		break;

	case EN_LUT_MODE_DOUBLE:
		SapData treshValue1;
		SapData treshValue2;
		treshValue1 = SetDataValue(Buffers, &prmIndex);
		treshValue2 = SetDataValue(Buffers, &prmIndex);
		m_pLut->Threshold(treshValue1, treshValue2);
		CorStrncpy(acqLutFileName, "Threshold_Double_Mode.lut", sizeof("Threshold_Double_Mode.lut"));
		CorStrncpy(chAcqLutName, "Threshold Double Lut", sizeof("Threshold Double Lut"));
		break;
	}
	m_pLut->Save(acqLutFileName);		// Save LUT to file (can be reloaded in the main demo)
#endif
	return true;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : bool updateGain(double dBlue, double dGreen, double dRed)
     arg1 : int nBlue
     arg2 : int nGreen
     arg3 : int nRed
   result : nil
  subject : Gain update
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
bool saperaCtrl::updateGain(double dBlue, double dGreen, double dRed)
{
	if(Parent->Setting.CameraControl==true){
		// Initialize all Gain colors to 0
		_AcqDevice->SetFeatureValue("GainBlue",  dBlue);
		_AcqDevice->SetFeatureValue("GainGreen", dGreen);
		_AcqDevice->SetFeatureValue("GainRed",   dRed);
	}
	return true;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : int saperaAutoWhiteBalance(void)
     arg1 : nil
   result : true	false
  subject : Sapera initialyze
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
bool saperaCtrl::saperaAutoWhiteBalance(char *pConfigFilename)
{
	char     acqServerName[CORSERVER_MAX_STRLEN];
	UINT32   acqDeviceNumber;
	BOOL status = false;

	int oldPixelFormat       = 0;
	double coefBlueGain      = CONST_MAX_COEF + 1;
	double coefGreenGain     = CONST_MAX_COEF + 1;
	double coefRedGain       = CONST_MAX_COEF + 1;
	int calibrationIteration = 0;
	BOOL isAvailable  = false;

	acqDeviceNumber = 0;	// OR 1 camera number by index ?

	if (!GetOptionsFromQuestions(acqServerName, &acqDeviceNumber)) {
		return false;
	}

	SapAcqDevice acqDevice(acqServerName);
	if (!acqDevice.Create()) return false;

	SapLocation loc(acqServerName);

	// Monochrome models are not supported for White Balance Calibration.
	UINT32 colorType = 0;
	isAvailable = false;
	if (acqDevice.IsFeatureAvailable("ColorType",&isAvailable) && isAvailable) {	// 使用可能か?
		if(acqDevice.GetFeatureValue("ColorType", &colorType)) {
			if (colorType == 0) return false;
		}
	}

	// GAIN調整可能?
	BOOL bRedGain = false;
	BOOL bGreenGain = false;
	BOOL bBlueGain = false;
	acqDevice.IsFeatureAvailable("GainRed", &bRedGain);
	acqDevice.IsFeatureAvailable("GainGreen", &bGreenGain);
	acqDevice.IsFeatureAvailable("GainBlue", &bBlueGain);

	if (!bRedGain && !bGreenGain && !bBlueGain) return false;

	// Start continous grab
	_Xfer->Grab();

   // Stop grab
   _Xfer->Freeze();
   if (!_Xfer->Wait(5000)) return 0;

	isAvailable = false;
	if (acqDevice.IsFeatureAvailable("PixelFormat",&isAvailable) && isAvailable) {
		acqDevice.GetFeatureValue("PixelFormat", &oldPixelFormat);
	}
	else return false;

	if (oldPixelFormat != GVSP_PIX_BAYRG8) {
		// Camera Pixel Format defined is not Raw Bayer.
		// We change the value

		// Disconnect tranfer
		status = _Xfer->Disconnect();

		status = acqDevice.SetFeatureValue("PixelFormat", (UINT32)GVSP_PIX_BAYRG8);

		// Destroy existing view object
		if (_View && *_View && !_View->Destroy()) {
			return false;
		}
		delete _View;
		_View = NULL;

		// Destroy existing transfer object
		if (_Xfer && *_Xfer && !_Xfer->Destroy()) {
			return false;
		}
		delete _Xfer;
		_Xfer = NULL;

		// Destroy existing buffer object
		if (_Buffers && *_Buffers && !_Buffers->Destroy()) {
			return false;
		}
		delete _Buffers;
		_Buffers = NULL;

        // Instantiation of new buffer object
	    _Buffers= new SapBufferWithTrash(2, &acqDevice);
        // Instantiation of new view object
	    _View = new SapView(_Buffers, SapHwndAutomatic);
        // Instantiation of new transfer object
//		void (saperaCtrl::*fpFunc)(SapXferCallbackInfo *pInfo) = &saperaCtrl::acqCallback;
		_Xfer = new SapAcqDeviceToBuf(&acqDevice, _Buffers, acqCallback, this);

        // Recreate buffer object
        if (_Buffers && !*_Buffers && !_Buffers->Create()) return false;

		// ReCreate view object
		if (_View && !*_View && !_View->Create()) return false;

		// Recreate transfer object
		if (_Xfer && !*_Xfer && !_Xfer->Create()) {
			unlink();
			return false;
		}

		// Connect tranfer
		_Xfer->Connect();
	}
	// Initialize all Gain colors to 0
	acqDevice.SetFeatureValue("GainBlue",  0);
	acqDevice.SetFeatureValue("GainGreen", 0);
	acqDevice.SetFeatureValue("GainRed",   0);

	// Create an empty feature object for each gain color (to receive information)
	_FeatureInfo= new SapFeature(acqDevice.GetLocation());
	if (!_FeatureInfo->Create()) return false;

	// Instantiation of new Bayer object
	_Bayer = new SapBayer(_Buffers);

	// Create Bayer object
	if (_Bayer && !*_Bayer && !_Bayer->Create()) {
		unlink();
		return false;
	}

	// Choose alignment used
	_Bayer->SetAlign(SapBayer::AlignRGGB);

	// Definition of ROI used for calibration
	int fixSelectedRoiLeft = 0;
	int fixSelectedRoiTop = 0;
	// Half buffer width
	int fixSelectedRoiWidth = _Buffers->GetWidth() / 2;
	// Half buffer height
	int fixSelectedRoiHeight = _Buffers->GetHeight() / 2;

	// Start loop for calibration until each coefficient is under 1.05
	while (coefBlueGain > CONST_MAX_COEF || coefGreenGain > CONST_MAX_COEF || coefRedGain > CONST_MAX_COEF) {
		// Acquire an image
		if (!_Xfer->Snap()) {
//            MessageBox(NULL, "Unable to acquire an image", "", MB_OK);
            return false;
		}
		Sleep(500);

		// Call WhiteBalance function
		if (_Bayer->WhiteBalance(_Buffers, fixSelectedRoiLeft, fixSelectedRoiTop, fixSelectedRoiWidth, fixSelectedRoiHeight) == false) {
			break;
		}

		// New coefficients values are reused.
		coefBlueGain = _Bayer->GetWBGain().Blue();
		coefGreenGain = _Bayer->GetWBGain().Green();
		coefRedGain = _Bayer->GetWBGain().Red();

		if (coefRedGain > CONST_MAX_COEF) {
			if (!ComputeGain("GainRed", &acqDevice, _FeatureInfo, coefRedGain)) {
				break;
			}
		}
		if (coefGreenGain > CONST_MAX_COEF) {
			if (!ComputeGain("GainGreen", &acqDevice, _FeatureInfo, coefGreenGain)) {
              break;
			}
		}
		if (coefBlueGain > CONST_MAX_COEF) {
			if (!ComputeGain("GainBlue", &acqDevice, _FeatureInfo, coefBlueGain)) {
				break;
			}
		}

		if (calibrationIteration >= MAX_CALIBRATION_ITERATION) {
//         printf("Iterations for calibration are at the maximum.\n");
			break;
		}
		calibrationIteration++;
	}

    // Uncomment this part if you want to get new values after calibration.
    UINT32 gainBlue=0, gainRed=0, gainGreen=0;
    acqDevice.GetFeatureValue("GainBlue", &gainBlue);
    acqDevice.GetFeatureValue("GainRed", &gainRed);
    acqDevice.GetFeatureValue("GainGreen", &gainGreen);

	if (oldPixelFormat != GVSP_PIX_BAYRG8) {
		// Camera Pixel Format was changed for Raw Bayer.
		// We set the original value.

		// Stop transfer
		_Xfer->Disconnect();

		// Set initial value
		acqDevice.SetFeatureValue("PixelFormat", oldPixelFormat);

		// Destroy view object
		if (_View && *_View && !_View->Destroy()) {
			unlink();
			return false;
		}
		delete _View;

		// Destroy transfer object
		if (_Xfer && *_Xfer && !_Xfer->Destroy()) {
			unlink();
			return false;
		}
		delete _Xfer;

		// Destroy bayer object
		if (_Bayer && *_Bayer && !_Bayer->Destroy()) {
			unlink();
			return false;
		}
		delete _Bayer;
		_Bayer = NULL;

		// Destroy buffer object
		if (_Buffers && *_Buffers && !_Buffers->Destroy()) {
			unlink();
			return false;
		}
		delete _Buffers;

		_Buffers= new SapBufferWithTrash(2, &acqDevice);
		_View	= new SapView(_Buffers, SapHwndAutomatic);
		_Xfer = new SapAcqDeviceToBuf(&acqDevice, _Buffers, acqCallback, _View);

		// Create buffer object
		if (_Buffers && !*_Buffers && !_Buffers->Create()) {
			unlink();
			return false;
		}

		// ReCreate view object
		if (_View && !*_View && !_View->Create()) {
			unlink();
			return false;
		}

		// Create transfer object
		if (_Xfer && !*_Xfer && !_Xfer->Create()) {
			unlink();
			return false;
		}
	}
	// Start continous grab

	_Xfer->Grab();

	// Stop grab
	_Xfer->Freeze();
	if (!_Xfer->Wait(5000)) {
//		printf("Grab could not stop properly.\n");
	}
	unlink();
	return true;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : bool :ComputeGain(char* Name, SapAcqDevice* AcqDevice, SapFeature* featureInfo, double coefGain)
     arg1 : char* Name				ゲイン名
     arg2 : SapAcqDevice* AcqDevice	AcqDeviceポインタ
     arg3 : SapFeature* featureInfo	featureInfoポインタ
     arg4 : double coefGain			ゲイン
   result : true	false
  subject : 指定の値を評価し、その結果を戻り値に返します。
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
bool saperaCtrl::ComputeGain(const char* Name, SapAcqDevice* AcqDevice, SapFeature* featureInfo, double coefGain)
{
	int featureExponent, gainCameraValue;
	UINT32 gainRedMin, gainRedMax;
	float powValue;
	double NewGainValuePrecision;
	INT32 NewGainRounded;

	// 指定名称の現在の設定値を得る
	if(!AcqDevice->GetFeatureInfo(Name, featureInfo)) return false;

	// Get Gain Red minimum
	featureInfo->GetMin(&gainRedMin);
	// Get Gain Red maximum
	featureInfo->GetMax(&gainRedMax);
	// Get Gain Value
	AcqDevice->GetFeatureValue(Name, &gainCameraValue);
	// Get Gain exponent
	featureInfo->GetSiToNativeExp10(&featureExponent);

	if (gainCameraValue == 0) {
		powValue = pow((float)10, featureExponent);	// べき乗
		NewGainValuePrecision = (coefGain * powValue);
	}
	else {
		NewGainValuePrecision = (coefGain * gainCameraValue);
	}
	NewGainRounded = (INT32)(NewGainValuePrecision + 0.5);	// 少数以下四捨五入

	if (!ValidateWhiteBalance(NewGainRounded, gainRedMin, gainRedMax)) return false;

	// 算出された値を設定
	AcqDevice->SetFeatureValue(Name, (UINT32)NewGainRounded);

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
bool saperaCtrl::ValidateWhiteBalance(int value, int minValue, int maxValue)
{
	if(value < minValue || value > maxValue) return false;
	return true;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : int prepareCapture(void)
     arg1 : nil
   result : true	false
  subject : キャプチャ開始準備
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
bool saperaCtrl::prepareCapture(void)
{
	if(isRunning()==false){
		Terminated=false;
		start();
	}
	return true;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : int getStatus(void)
     arg1 : nil
   result : _nStatus
  subject : 現在のステータスを戻り値に返します。
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
int saperaCtrl::getStatusInside(void)
{
	BOOL	LineActive;
	_Acq->GetSignalStatus(SapAcquisition::SignalHSyncPresent, &LineActive);
	if(LineActive==false) {
		LineValid=false;
		return 0x100;
	}
	else {
		LineValid=true;
	}

	if (_nStatus == EN_CTRLSTS_GRABED) return 0;

	return 1;
}

int saperaCtrl::getStatus(void)
{
	if(LineValid==false) {
		return 0x100;
	}
	//int	RPage=min(CurrentRPage,Parent->GetReadablePage());
	//if (StateInPage[RPage]==1) return 0;

	if (StateInPage[CurrentRPage]==1) return 0;
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

bool	saperaCtrl::SetQuickProperty(CameraQuickProperty Attr, double RelativeValue)
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

DWORD	*saperaCtrl::ClearCenterLine(int index)
{
	int	YN=_Buffers->GetHeight();
	int	BuffWidth=_Buffers->GetWidth();
	void	*SrcAddress;

	_Buffers->GetAddress(index,&SrcAddress);
	DWORD	*d=((DWORD *)SrcAddress);
	d+=BuffWidth/2;

	DWORD	*dd=d;
	for(int y=0;y<YN;y++){
		*dd=0;
		dd+=BuffWidth;
	}
	return d;
}

//void	saperaCtrl::run()
//{
//	DWORD	PassedTime;
//	startCaptureInside();
//	DWORD	StartTime=::GetComputerMiliSec();
//
//	while(Terminated==false){
//		
//		DWORD	t1=::GetComputerMiliSec();
//		ListedTime1[ListedTimeCounter]=t1-StartTime;
//		StartTime=t1;
//
//		ImageBuffer *Buff[3];
//
//		Buff[0]=&ImageStack[0];
//		Buff[1]=&ImageStack[1];
//		Buff[2]=&ImageStack[2];
//		int	BuffWidth=_Buffers->GetWidth();
//
//		Index=(_Buffers->GetIndex()+1)%GCount;
//		DWORD	*d=ClearCenterLine(Index);
//
//		int	StartLine=0;
//		int	EndLine=0;
//		int	YN=_Buffers->GetHeight();
//
//		int	MaxYShift=max(max(Parent->Setting.OffsetYRed,Parent->Setting.OffsetYGreen),Parent->Setting.OffsetYBlue);
//		int	MinYShift=min(min(Parent->Setting.OffsetYRed,Parent->Setting.OffsetYGreen),Parent->Setting.OffsetYBlue);
//
//		while(getStatusInside()!=0){
//			if(Terminated==true)
//				return;
//			YN=_Buffers->GetHeight();
//			if(FirstCapture==false){
//				while((EndLine+1)<YN && (*d!=0 || *(d+BuffWidth)!=0)){
//					EndLine++;
//					d+=BuffWidth;
//				}
//				if((EndLine-StartLine)>(10+MaxYShift)){
//					
//					void	*SrcAddress;
//					_Buffers->GetAddress(Index,&SrcAddress);
//					LockAccessImage.lock();
//					getPartialImageInside(Index ,Buff
//										,StartLine , EndLine-MaxYShift);
//					LockAccessImage.unlock();
//					StartLine=EndLine-MaxYShift;
//				}
//			}
//			else{
//				StartLine=0;
//				EndLine=0;
//			}
//			msleep(1);
//		}
//		//Index=(_Buffers->GetIndex()+1)%GCount;
//		DWORD	t=::GetComputerMiliSec();
//		void	*SrcAddress;
//		_Buffers->GetAddress(Index,&SrcAddress);
//		_Buffers->GetAddress(&SrcAddress);
//		if(FirstCapture==true){
//			LockAccessImage.lock();
//			getPartialImageInside(-1,Buff
//								,StartLine , YN);
//			LockAccessImage.unlock();
//		}
//		else{
//			LockAccessImage.lock();
//			getPartialImageInside(Index ,Buff
//								,StartLine , YN);
//			LockAccessImage.unlock();
//		}
//		FirstCapture=false;
//		_nStatus = EN_CTRLSTS_IDLE;
//		if(Halted==false){
//			ListedTime2[ListedTimeCounter]=::GetComputerMiliSec()-t;
//			ListedTimeCounter++;
//			if(ListedTimeCounter>=1000)
//				ListedTimeCounter=0;
//		}
//	}
//}


void	saperaCtrl::run()
{
	DWORD	PassedTime;
	startCaptureInside();
	DWORD	StartTime=::GetComputerMiliSec();

	while(Terminated==false){
		GSleep(1000);
	}
}