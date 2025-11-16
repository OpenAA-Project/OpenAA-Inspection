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
#include "swap.h"

#include "sapClassBasic.h"
#include "conio.h"
#include "XMainSchemeMemory.h"

#include "saperaCtrlColor.h"
#include "featureCtrl.h"
#include <omp.h>
#include "XCriticalFunc.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "CameraXtiumLinearHSColorMonoLineTrigger.h"
#include "XLogOut.h"
#include "XGeneralFunc.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"

#define MAX_CONFIG_FILES   36       // 10 numbers + 26 lowercase letters
#define	CamDeviceName	"CameraLink HS Color RGB"

static	BOOL GetOptionsFromQuestions(char *acqServerName, UINT32 *pAcqDeviceIndex)
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
	*pAcqDeviceIndex = -1;

	for (int deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++)
	{
		char deviceName[CORPRM_GETSIZE(CORACQ_PRM_LABEL)];
		SapManager::GetResourceName(acqServerName, SapManager::ResourceAcq, deviceIndex, deviceName, sizeof(deviceName));
		if(strstr(deviceName,CamDeviceName)!=NULL){
			*pAcqDeviceIndex = deviceIndex;
			break;
		}
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
	return true;
}


using namespace std;

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : saperaCtrl(void)
     arg1 : nil
   result : nil
  subject : constructor
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
saperaCtrlColor::saperaCtrlColor(int CamNo ,LayersBase *base,CameraXtiumLinearHSColor *parent)
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
	GCount		=2;
	CurrentGPos	=0;
	Calibrated	=false;
	LineValid	=true;

	_gainMax = 0.0;
	_gainMin = 0.0;
	_currentGain = 0.0;
	CONST_MAX_COEF = 1.05;

	Terminated	=false;
	Halted		=false;
	RepeatON	=true;
	Index		=-1;
	FirstCapture=true;
	EndLineMergin	=0;
	setPriority(QThread::LowPriority);
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : ~saperaCtrl(void)
     arg1 : nil
   result : nil
  subject : destructor
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
saperaCtrlColor::~saperaCtrlColor(void)
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

bool saperaCtrlColor::link(char *pConfigFilename)
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

	//bool	ResetMode=true;
	//fc->setFeatureValue(/**/"DeviceReset", ResetMode);
	//GSleep(25000);

	GSleep(1000);

	//delete fc;
	//fc = NULL;

	if (SapManager::GetResourceCount(acqServerName, SapManager::ResourceAcq) > 0) {

		SapLocation loc2(acqServerName, acqDeviceNumber);
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

		GSleep(1000);

		int	MaxLines;
		if(Parent->DupLineMode==false){
			MaxLines=GetMaxLines()*Parent->Shrink2;
		}
		else{
			MaxLines=GetMaxLines()*Parent->Shrink2/2;
		}
		Ret=_Acq->SetParameter( CORACQ_PRM_CROP_HEIGHT, MaxLines );
		GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-CORACQ_PRM_CROP_HEIGHT", MaxLines,Ret);

		//Ret=_Acq->RegisterCallback(SapAcquisition::EventEndOfLine | 100,CallBackByLine,NULL);
	}
	if (!acquisitionCreated) {
		goto FreeHandles;
	}


	int	Width;
	Ret=_Acq->GetParameter( CORACQ_PRM_CROP_WIDTH, &Width );
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-CORACQ_PRM_CROP_WIDTH", Width,Ret);
	Parent->CamDotPerLine=max(Width,GetDotPerLine());
	
	GSleep(1000);
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

	// Feature setting
	if(fc==NULL){
		int	ResourceNo=0;
		fc = new featureCtrl(acqServerName,ResourceNo);
		char	ManufacturersPartNumber[256];
		fc->getFeatureValue("deviceManufacturersPartNumber", ManufacturersPartNumber, sizeof(ManufacturersPartNumber));
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

bool saperaCtrlColor::ControlCamera(void)
{
	bool	Ret;

	//if(Parent->Setting.CameraControl==true){
	//	Ret=fc->setFeatureValue(featureCtrl::EN_AcquisitionLineRate, (double)DEF_AcquisitionLineRate);
	//	GetLayersBase()->GetLogCreater()->PutLogR(__LINE__, "saperaCtrl::link-EN_AcquisitionLineRate", Ret);
	//}
	// 
	//if(Parent->Setting.ExternalTrigger==true){
	//	fc->setFeatureValue(featureCtrl::EN_TriggerMode, "External");
	//}
	//else{
	//	fc->setFeatureValue(featureCtrl::EN_TriggerMode, "Internal");
	//}

	if(Parent->Setting.CameraControl==true){
		UINT64 SensorMaxWidth;
		Ret=fc->getFeatureValue("WidthMax", &SensorMaxWidth);
		GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-WidthMax", SensorMaxWidth,Ret);

		if(Parent->Setting.ROIOffset!=0){
			int64	ROIOffsetX=(Parent->Setting.ROIOffset/32)*32;
			Ret=fc->setFeatureValueWithStop("multipleROIOffsetX", ROIOffsetX);
			int64	ROIWidth=(GetDotPerLine()/32)*32;
			Ret=fc->setFeatureValueWithStop("multipleROIWidth", ROIWidth);
			ROIOffsetX=0;
			ROIWidth=0;
			Ret=fc->getFeatureValue("multipleROIOffsetX", &ROIOffsetX);
			Ret=fc->getFeatureValue("multipleROIOffsetX", &ROIWidth);
		}

		int	HDiv=SensorMaxWidth/(GetDotPerLine()*Parent->Shrink2);
		if(HDiv>=2){
			UINT64 BinningHorizontal;
			Ret=fc->getFeatureValue("BinningHorizontal", &BinningHorizontal);
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningHorizontal"	,BinningHorizontal,Ret);

			bool	StopMode;
			StopMode=true;
			BOOL isAvailable;
			GSleep(3000);

			//SapFeature feature;
			//Ret=fc->GetFeatureInfo("AcquisitionStop", &feature);

			//Ret=fc->setFeatureValue("AcquisitionStop", StopMode);
			BinningHorizontal=2;
			Ret=fc->setFeatureValueWithStop("BinningHorizontal", BinningHorizontal);
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningHorizontal", BinningHorizontal,Ret);

			GSleep(1000);

			Ret=fc->setFeatureValue("AcquisitionStart", true);
			GetLayersBase()->GetLogCreater()->PutLogR(__LINE__, "saperaCtrl::link-AcquisitionStart", Ret);

			BinningHorizontal=0;
			Ret=fc->getFeatureValue("BinningHorizontal"	, &BinningHorizontal);
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningHorizontal", BinningHorizontal,Ret);
		}
		else{
			UINT64 BinningHorizontal;
			Ret=fc->getFeatureValue("BinningHorizontal", &BinningHorizontal);
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningHorizontal", BinningHorizontal,Ret);

			bool	StopMode;
			StopMode=true;
			BOOL isAvailable;

			GSleep(3000);

			//SapFeature feature;
			//Ret=fc->GetFeatureInfo("AcquisitionStop", &feature);

			//Ret=fc->setFeatureValue("AcquisitionStop", StopMode);
			BinningHorizontal=1;
			Ret=fc->setFeatureValueWithStop("BinningHorizontal", BinningHorizontal);
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningHorizontal", BinningHorizontal,Ret);

			if(GetLayersBase()->GetFastBoot()==false){
				SetCalibration();
			}
			GSleep(1000);

			Ret=fc->setFeatureValue("AcquisitionStart", true);
			GetLayersBase()->GetLogCreater()->PutLogR(__LINE__, "saperaCtrl::link-AcquisitionStart", Ret);

			BinningHorizontal=0;
			Ret=fc->getFeatureValue("BinningHorizontal", &BinningHorizontal);
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningHorizontal",BinningHorizontal,Ret);

		}
		int	VDiv=Parent->Setting.VerticalBinning;
		if(VDiv>=2){
			UINT64 BinningVertical;
			Ret=fc->getFeatureValue("BinningVertical"	 , &BinningVertical);
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningVertical"	,BinningVertical,Ret);

			bool	StopMode;
			StopMode=true;
			BOOL isAvailable;
			GSleep(3000);

			//SapFeature feature;
			//Ret=fc->GetFeatureInfo("AcquisitionStop", &feature);

			//Ret=fc->setFeatureValue("AcquisitionStop", StopMode);
			BinningVertical=2;
			Ret=fc->setFeatureValueWithStop("BinningVertical", BinningVertical);
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningVertical", BinningVertical,Ret);

			if(GetLayersBase()->GetFastBoot()==false){
				SetCalibration();
			}
			GSleep(1000);

			Ret=fc->setFeatureValue("AcquisitionStart", true);
			GetLayersBase()->GetLogCreater()->PutLogR(__LINE__, "saperaCtrl::link-AcquisitionStart", Ret);

			BinningVertical=0;
			Ret=fc->getFeatureValue("BinningVertical"	, &BinningVertical);
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningVertical", BinningVertical,Ret);
		}
		else{
			UINT64 BinningVertical;
			Ret=fc->getFeatureValue("BinningVertical"	 , &BinningVertical);
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningVertical", BinningVertical,Ret);

			bool	StopMode;
			StopMode=true;
			BOOL isAvailable;

			if(GetLayersBase()->GetFastBoot()==false){
				SetCalibration();
			}
			GSleep(3000);

			//SapFeature feature;
			//Ret=fc->GetFeatureInfo("AcquisitionStop", &feature);

			//Ret=fc->setFeatureValue("AcquisitionStop", StopMode);
			BinningVertical=1;
			Ret=fc->setFeatureValueWithStop("BinningVertical", BinningVertical);
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningHorizontal", BinningVertical,Ret);

			GSleep(1000);

			Ret=fc->setFeatureValue("AcquisitionStart", true);
			GetLayersBase()->GetLogCreater()->PutLogR(__LINE__, "saperaCtrl::link-AcquisitionStart", Ret);

			BinningVertical=0;
			Ret=fc->getFeatureValue("BinningVertical"	 , &BinningVertical);
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-BinningVertical",BinningVertical,Ret);
		}
	}
	return true;
}

bool	saperaCtrlColor::SetCalibration(void)
{
	bool	Ret=true;
//	if(Parent->Setting.AutoBlackLevel==true)
//		Ret=fc->setFeatureValue("blackLevelEnable","True" );
//	else
//		Ret=fc->setFeatureValue("blackLevelEnable","False" );
//
//	if(Calibrated==false){
//		if(Parent->Setting.CalibrateFPN==true){
//			if(Parent->ioLightControlOFF!=NULL){
//				Parent->ioLightControlOFF->Set(true);
//			}
//			GSleep(Parent->Setting.LightOffMilisec);
//
//			Ret=fc->setFeatureValue("flatfieldCalibrationClearCoefficient",true );
//			GSleep(Parent->Setting.LightOnMilisec);
//			Ret=fc->setFeatureValue("flatfieldCalibrationFPN",true );
//			GSleep(Parent->Setting.LightOnMilisec);
//			Ret=fc->setFeatureValue("flatfieldCalibrationFPN",true );
//			GSleep(Parent->Setting.LightOnMilisec);
//			Calibrated=true;
//			GSleep(1000);
//			Ret=fc->setFeatureValue("AcquisitionStart", true);
//			GetLayersBase()->GetLogCreater()->PutLogR(__LINE__, "saperaCtrl::link-AcquisitionStart", Ret);
//			
//			if(Parent->ioLightControlOFF!=NULL){
//				Parent->ioLightControlOFF->Set(false);
//			}
//		}
//	}
	return Ret;
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

void saperaCtrlColor::GetSignalStatus(SapAcquisition::SignalStatus signalStatus)
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

void saperaCtrlColor::SignalCallback(SapAcqCallbackInfo *pInfo)
{
	saperaCtrlColor *pDlg = (saperaCtrlColor *) pInfo->GetContext();
	pDlg->GetSignalStatus(pInfo->GetSignalStatus());
}


void saperaCtrlColor::GetSignalStatus()
{

	if (_Acq && _Acq->IsSignalStatusAvailable())
	{
		if (_Acq->GetSignalStatus(&signalStatus, SignalCallback, this))
			GetSignalStatus(signalStatus);
	}
}
bool saperaCtrlColor::ChangeLineCount(int YCount)
{
	UINT32   acqDeviceNumber = 0;
	char    acqServerName[CORSERVER_MAX_STRLEN];
	BOOL	isNotSupported = false,status = false,acquisitionCreated = TRUE,acqDeviceCreated = TRUE;

	int	MaxLines;
	_Acq->GetParameter( CORACQ_PRM_CROP_HEIGHT, &MaxLines );
	if(Parent->DupLineMode==true){
		MaxLines*=2;
	}
	if(MaxLines==YCount)
		return true;

	if (!GetOptionsFromQuestions(acqServerName, &acqDeviceNumber)) {
		return false;
	}
	Terminated=true;
	wait(1000);

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

	GSleep(1000);

	_Acq	= new SapAcquisition(loc2, ConfigFileName);
	_Buffers= new SapBuffer(GCount, _Acq);
	_Xfer	= new SapAcqToBuf(_Acq, _Buffers, acqCallback, this);
	_Gio    = new SapGio(loc2, gioCallback, this);

	if (_Acq && !*_Acq && !_Acq->Create()) {
		acquisitionCreated = false;
	}
	
	//_Acq->GetSignalStatus(SapAcquisition::SignalHSyncPresent, &LineActive);
	GetSignalStatus();

	GSleep(1000);

	bool	Ret;
	int		Height;
	if(Parent->DupLineMode==false)
		Height=GetMaxLines()*Parent->Shrink2;
	else{
		Height=GetMaxLines()*Parent->Shrink2/2;
	}
	Ret=_Acq->SetParameter(CORACQ_PRM_CROP_HEIGHT, Height);
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__, "saperaCtrl::link-CORACQ_PRM_CROP_HEIGHT", Height,Ret);
//	Ret=_Buffers->SetHeight(Height);
//	Ret=_Xfer->UpdateFrameRateStatistics();

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
	GSleep(1000);

	AllocateBuff();
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

void saperaCtrlColor::AllocateBuff(void)
{
	for(int i=0;i<CamStackNumb;i++){
		ImageStack[i][0].Set(0,0,GetDotPerLine(),GetMaxLines());
		ImageStack[i][1].Set(0,0,GetDotPerLine(),GetMaxLines());
		ImageStack[i][2].Set(0,0,GetDotPerLine(),GetMaxLines());
		if(GetParamGlobal()->AllocateTargetTRBuff==true){
			TRImageStack[i][0].Set(0,0,GetMaxLines(),GetDotPerLine());
			TRImageStack[i][1].Set(0,0,GetMaxLines(),GetDotPerLine());
			TRImageStack[i][2].Set(0,0,GetMaxLines(),GetDotPerLine());
		}
	}
	StackedNumb=0;
	CurrentWTop=0;
	CurrentRTop=0;
}
/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : bool startCapture(void)
     arg1 : nil
   result : true	false
  subject : Start capture
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
bool saperaCtrlColor::startCapture(void)
{
	Halted=false;
	return true;
}

bool saperaCtrlColor::startCaptureInside(void)
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
bool saperaCtrlColor::stopCapture(void)
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
bool saperaCtrlColor::unlink(void)
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
void saperaCtrlColor::acqCallback(SapXferCallbackInfo *pInfo)
{
	saperaCtrlColor *pSapera = (saperaCtrlColor *)pInfo->GetContext();

	// Resfresh view
//	pSapera->_View->Show();		// いるのかな???
	pSapera->_nStatus = EN_CTRLSTS_GRABED;
}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : void gioCallback(SapGioCallbackInfo *pInfo)
     arg1 : SapGioCallbackInfo *pInfo
   result : nil
  subject : GIO callback funvtion
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
void saperaCtrlColor::gioCallback(SapGioCallbackInfo *pInfo)
{
	saperaCtrlColor *pSapera = (saperaCtrlColor *)pInfo->GetContext();;

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
bool saperaCtrlColor::updateLUT(SapBuffer* Buffers, SapLut* m_pLut, char *chAcqLutName, int unLutMode)
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
bool saperaCtrlColor::updateGain(double dBlue, double dGreen, double dRed)
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
bool saperaCtrlColor::saperaAutoWhiteBalance(char *pConfigFilename)
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
bool saperaCtrlColor::ComputeGain(const char* Name, SapAcqDevice* AcqDevice, SapFeature* featureInfo, double coefGain)
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
bool saperaCtrlColor::ValidateWhiteBalance(int value, int minValue, int maxValue)
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
bool saperaCtrlColor::prepareCapture(void)
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
int saperaCtrlColor::getStatusInside(void)
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

int saperaCtrlColor::getStatus(void)
{
	//if(LineValid==false) {
	////	return 0x100;
	//}
	int	Ret;
	MutexStackImage.lock();
	if (StackedNumb>0)
		Ret=0;
	else
		Ret=1;
	MutexStackImage.unlock();
	return Ret;
}


/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
 function : bool ValidateWhiteBalance(int value, int minValue, int maxValue)
     arg1 : int value		評価する値
     arg2 : int minValue	最小値
     arg3 : int maxValue	最大値
   result : true	false
  subject : 指定の値を評価し、その結果を戻り値に返します。
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
bool saperaCtrlColor::getImage(ImageBuffer *Buff[],ImageBuffer *TRBuff[])
{
	MutexSwapImage.lock();
	Buff[0]->Swap(ImageStack[CurrentRTop][0]);
	Buff[1]->Swap(ImageStack[CurrentRTop][1]);
	Buff[2]->Swap(ImageStack[CurrentRTop][2]);
	//*Buff[0]=ImageStack[CurrentRTop][0];
	//*Buff[1]=ImageStack[CurrentRTop][1];
	//*Buff[2]=ImageStack[CurrentRTop][2];

	if(GetParamGlobal()->AllocateTargetTRBuff==true){
		TRBuff[0]->Swap(TRImageStack[CurrentRTop][0]);
		TRBuff[1]->Swap(TRImageStack[CurrentRTop][1]);
		TRBuff[2]->Swap(TRImageStack[CurrentRTop][2]);
	}
	MutexSwapImage.unlock();
	CurrentRTop++;
	if(CurrentRTop>=CamStackNumb){
		CurrentRTop=0;
	}
	MutexStackImage.lock();
	StackedNumb--;
	MutexStackImage.unlock();

	return true;
}

bool	saperaCtrlColor::SetQuickProperty(CameraQuickProperty Attr, double RelativeValue)
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

static	DWORD	ListedTime1[1000];
static	DWORD	ListedTime2[1000];
static	int		ListedTimeCounter=0;

DWORD	*saperaCtrlColor::ClearCenterLine(int index)
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

struct SaperaScanInfo
{
	int	StartLine;
	int	EndLine;
	DWORD	MSec;
};

void	saperaCtrlColor::CopyParam(void)
{
	MatrixRX	=Parent->MatrixRX;
	MatrixGX	=Parent->MatrixGX;
	MatrixBX	=Parent->MatrixBX;
	MatrixRXTR	=Parent->MatrixRXTR;
	MatrixGXTR	=Parent->MatrixGXTR;
	MatrixBXTR	=Parent->MatrixBXTR;
	dyR			=Parent->Setting.OffsetYRed;
	dyG			=Parent->Setting.OffsetYGreen;
	dyB			=Parent->Setting.OffsetYBlue;
	dxR			=Parent->Setting.OffsetXRed;
	dxG			=Parent->Setting.OffsetXGreen;
	dxB			=Parent->Setting.OffsetXBlue;

	GainRedL	=Parent->Setting.GainRedL	+Parent->Setting.AddedGainR;
	GainGreenL	=Parent->Setting.GainGreenL	+Parent->Setting.AddedGainG;
	GainBlueL	=Parent->Setting.GainBlueL	+Parent->Setting.AddedGainB;
	OffsetRedL	=Parent->Setting.OffsetRedL	;
	OffsetGreenL=Parent->Setting.OffsetGreenL;
	OffsetBlueL	=Parent->Setting.OffsetBlueL	;			 			
	GainRedR	=Parent->Setting.GainRedR	+Parent->Setting.AddedGainR;
	GainGreenR	=Parent->Setting.GainGreenR	+Parent->Setting.AddedGainG;
	GainBlueR	=Parent->Setting.GainBlueR	+Parent->Setting.AddedGainB;
	OffsetRedR	=Parent->Setting.OffsetRedR	;
	OffsetGreenR=Parent->Setting.OffsetGreenR;
	OffsetBlueR	=Parent->Setting.OffsetBlueR	;
	
	GainOffsetTableRL	=Parent->GainOffsetTableRL;
	GainOffsetTableGL	=Parent->GainOffsetTableGL;
	GainOffsetTableBL	=Parent->GainOffsetTableBL;
	GainOffsetTableRR	=Parent->GainOffsetTableRR;
	GainOffsetTableGR	=Parent->GainOffsetTableGR;
	GainOffsetTableBR	=Parent->GainOffsetTableBR;
	LeftRight	=Parent->Setting.LeftRight;
}

void	saperaCtrlColor::run()
{
	DWORD	PassedTime;
	startCaptureInside();
	DWORD	StartTime=::GetComputerMiliSec();
	GSleep(2000);
	struct SaperaScanInfo	CamDim[1000];

	while(Terminated==false){
		
		DWORD	t1=::GetComputerMiliSec();
		ListedTime1[ListedTimeCounter]=t1-StartTime;
		StartTime=t1;

		bool	BasicMode=false;
		if((Parent->Setting.GainRedL	+Parent->Setting.AddedGainR)==1.0
		&& (Parent->Setting.GainGreenL	+Parent->Setting.AddedGainG)==1.0
		&& (Parent->Setting.GainBlueL	+Parent->Setting.AddedGainB)==1.0
		&& Parent->Setting.OffsetRedL==0
		&& Parent->Setting.OffsetGreenL==0
		&& Parent->Setting.OffsetBlueL==0
		&& (Parent->Setting.GainRedR	+Parent->Setting.AddedGainR)==1.0
		&& (Parent->Setting.GainGreenR	+Parent->Setting.AddedGainG)==1.0
		&& (Parent->Setting.GainBlueR	+Parent->Setting.AddedGainB)==1.0
		&& Parent->Setting.OffsetRedR==0
		&& Parent->Setting.OffsetGreenR==0
		&& Parent->Setting.OffsetBlueR==0){
			BasicMode=true;
		}
		LoopCounter=0;

		ImageBuffer *Buff[3];
		ImageBuffer *TRBuff[3];
		Buff[0]=&ImageStack[CurrentWTop][0];
		Buff[1]=&ImageStack[CurrentWTop][1];
		Buff[2]=&ImageStack[CurrentWTop][2];
		TRBuff[0]=&TRImageStack[CurrentWTop][0];
		TRBuff[1]=&TRImageStack[CurrentWTop][1];
		TRBuff[2]=&TRImageStack[CurrentWTop][2];

		msleep(10);
		CopyParam();
		Index=(_Buffers->GetIndex()+1)%GCount;
		DWORD	*d=ClearCenterLine(Index);

		int	StartLine=0;
		int	EndLine=0;
		int	YN=_Buffers->GetHeight();

		int	MaxYShift=max(max(Parent->Setting.OffsetYRed,Parent->Setting.OffsetYGreen),Parent->Setting.OffsetYBlue);
		int	MinYShift=min(min(Parent->Setting.OffsetYRed,Parent->Setting.OffsetYGreen),Parent->Setting.OffsetYBlue);

		int	MerginY = 0;
		int	MaxOpenMP = 18 * 2;



		int	BuffWidth=_Buffers->GetWidth();
		int width	= min(Buff[0]->GetWidth() ,BuffWidth);	//CONST_MAX_WIDTH;
		int height	= min(Buff[0]->GetHeight(),(Parent->DupLineMode==false)?_Buffers->GetHeight():_Buffers->GetHeight()*2);	//CONST_MAX_HEIGHT;

		void	*SrcAddress;
		if(Index>=0){
			_Buffers->GetAddress(Index,&SrcAddress);
		}
		else{
			_Buffers->GetAddress(&SrcAddress);
		}
		YN=_Buffers->GetHeight();
		DWORD	CamStartTime=0;
		while(getStatusInside()!=0){
			if(Terminated==true)
				return;

			if(FirstCapture==false){
				while((EndLine+1)<YN && (*d!=0 || *(d+BuffWidth)!=0)){
					EndLine++;
					d+=BuffWidth;
				}
				if(((EndLine-MerginY)-StartLine)>(MaxOpenMP+MaxYShift)){
					if(StartLine==0){
						CamStartTime=::GetComputerMiliSec();
					}
			
					if(Parent->Shrink2==1){
						if(BasicMode==true){
							CopyParam();
							getPartialImageInsideBasic(Index ,Buff,TRBuff
												,StartLine , (EndLine-MerginY)-MaxYShift
												,SrcAddress
												,BuffWidth
												,width
												,height);
						}
						else{
							CopyParam();
							getPartialImageInside(Index ,Buff,TRBuff
												,StartLine , (EndLine-MerginY)-MaxYShift
												,SrcAddress
												,BuffWidth
												,width
												,height);
						}
					}
					else
					if(Parent->Shrink2==2){
						CopyParam();
						getPartialImageInsideShrink2(Index ,Buff,TRBuff
											,StartLine , (EndLine-MerginY)-MaxYShift);
					}
					if(LoopCounter<sizeof(CamDim)/sizeof(CamDim[0])){
						CamDim[LoopCounter].StartLine=StartLine;
						CamDim[LoopCounter].EndLine	 =EndLine;
						CamDim[LoopCounter].MSec	 =::GetComputerMiliSec()-CamStartTime;
						LoopCounter++;
					}
					StartLine=(EndLine-MerginY)-MaxYShift;
				}
			}
			else{
				StartLine=0;
				EndLine=0;
			}
			msleep(15);
		}

		//QThread::usleep(10000);
		//_Buffers->GetAddress(&SrcAddress);
		if(FirstCapture==true){
			if(Parent->Shrink2==1){
				if(BasicMode==true){
					CopyParam();
					getPartialImageInsideBasic(-1,Buff,TRBuff
												,StartLine , YN
												,SrcAddress
												,BuffWidth
												,width
												,height);
				}
				else{
					CopyParam();
					getPartialImageInside(-1,Buff,TRBuff
										,StartLine , YN
												,SrcAddress
												,BuffWidth
												,width
												,height);
				}
			}
			else
			if(Parent->Shrink2==2){
				CopyParam();
				getPartialImageInsideShrink2(-1,Buff,TRBuff
									,StartLine , YN);
			}
		}
		else{
			//Buff[0]->Memset(0);
			//Buff[1]->Memset(0);
			//Buff[2]->Memset(0);

			if(Parent->Shrink2==1){
				if(BasicMode==true){
					CopyParam();
					getPartialImageInsideBasic(Index ,Buff,TRBuff
									,StartLine , YN
												,SrcAddress
												,BuffWidth
												,width
												,height);
				}
				else{
					CopyParam();
					getPartialImageInside(Index ,Buff,TRBuff
									,StartLine , YN
												,SrcAddress
												,BuffWidth
												,width
												,height);
				}
				//memset(SrcAddress,0,BuffWidth*height*4);
			}
			else
			if(Parent->Shrink2==2){
				CopyParam();
				getPartialImageInsideShrink2(Index ,Buff,TRBuff
											,StartLine , YN);
			}
		}
		RemoveCenterBlack(Buff);

		FirstCapture=false;
		_nStatus = EN_CTRLSTS_IDLE;
		if(Halted==false){
			ListedTime2[ListedTimeCounter]=::GetComputerMiliSec()-CamStartTime;
			ListedTimeCounter++;
			if(ListedTimeCounter>=1000)
				ListedTimeCounter=0;

			if(RepeatON==true){
				CurrentWTop++;
				if(CurrentWTop>=CamStackNumb){
					CurrentWTop=0;
				}
				MutexStackImage.lock();
				StackedNumb++;
				MutexStackImage.unlock();
			}
		}
	}
}