// -----------------------------------------------------------------------------------------
//	sapera setting control functions
//	featureCtrl.c
// -----------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <QStringList>

#include "sapClassBasic.h"
#include "featureCtrl.h"

/* ----------------------------------------------------------------------------
 cost Array init
---------------------------------------------------------------------------- */
const char *featureCtrl::_pFeatureName[EN_FEATURE_TYPE_MAX] = {
	"DeviceModelName"						//0. 
	,"DeviceVendorName"						//1. 
	,"DeviceSerialNumber"					//2. 
	,"DeviceID"								//3. 
	,"DeviceFirmwareVersion"				//4. 
	,"DeviceVersion"						//5. 
	,"DeviceManufacturerInfo"				//6. 
	,"deviceScriptVersion"					//7. 
	,"deviceBISTStatus"						//8. 
	,"deviceBIST"							//9. 
	,"deviceLEDColorControl"				//10.
	,"DeviceTemperature"					//11.
	,"refreshTemperature"					//12.
	,"deviceInputVoltage"					//13.
	,"refreshVoltage"						//14.
	,"UserSetDefaultSelector"				//15.
	,"UserSetSelector"						//16.
	,"UserSetLoad"							//17.
	,"UserSetSave"							//18.
	,"DeviceReset"							//19.
	,"DeviceScanType"						//20.
	,"sensorColorType"						//21.
	,"AcquisitionLineRate"					//22.
	,"measuredLineRate"						//23.
	,"refreshMeasuredLineRate"				//24.
	,"sensorTDIStagesSelection"				//25.
	,"ExposureMode"							//26.
	,"ExposureTime"							//27.
	,"ScanDirectionSource"					//28.
	,"SensorScanDirection"					//29.
	,"currentDirection"						//30.
	,"refreshCurrentDirection"				//31.
	,"BlackLevel"							//32.
	,"GainSelector"							//33.
	,"gainExtended"							//34.
	,"Gain"									//35.
	,"TriggerMode"							//36.
	,"flatfieldCorrectionMode"				//37.
	,"flatfieldCalibrationClearCoefficient"	//38.
	,"flatfieldCorrectionAlgorithm"			//39.
	,"flatfieldCalibrationTarget"			//40.
	,"flatfieldCalibrationSampleSize"		//41.
	,"flatfieldCalibrationROIOffsetX"		//42.
	,"flatfieldCalibrationROIWidth"			//43.
	,"flatfieldCalibrationFPN"				//44.
	,"flatfieldCalibrationPRNU"				//45.
	,"flatfieldRoiPrnu"						//46.
	,"flatfieldSetRoiPrnu"					//47.
	,"flatfieldCorrectionCurrentActiveSet"	//48.
	,"flatfieldCalibrationSave"				//49.
	,"flatfieldCalibrationLoad"				//50.
	,"lutMode"								//51.
	,"gammaCorrection"						//52.
	,"lutSize"								//53.
	,"flatfieldSfrRoiSelector"				//54.
	,"flatfieldSfrRoiOffsetX"				//55.
	,"flatfieldSfrRoiWidth"					//56.
	,"flatfieldSfrRoiValue"					//57.
	,"blackLevelEnable"						//58.
	,"calibrateBlackLevel"					//59.
	,"imageMagnificationMode"				//60.
	,"PixelFormat"							//61.
	,"PixelCoding"							//62.
	,"PixelColorFilter"						//63.
	,"WidthMax"								//64.
	,"OffsetX"								//65.
	,"Width"								//66.
	,"Height"								//67.
	,"BinningHorizontal"					//68.
	,"BinningVertical"						//69.
	,"TestImageSelector"					//70.
	,"portRoiSelector"						//71.
	,"multipleROICount"						//72.
	,"multipleROISelector"					//73.
	,"multipleROIOffsetX"					//74.
	,"multipleROIWidth"						//75.
	,"FileSelector"							//76.
	,"FileOperationExecute"					//77.
	,"FileOpenMode"							//78.
	,"FileAccessOffset"						//79.
	,"FileAccessLength"						//80.
	,"FileAccessBuffer"						//81.
	,"FileSize"								//82.
	,"FileOperationSelector"				//83.
	,"FileOperationStatus"					//84.
	,"FileOperationResult"					//85.
	,"DeviceManifestXMLMajorVersion"		//86.
	,"DeviceManifestXMLMinorVersion"		//87.
	,"clhsDiscovery"						//88.
	,"clhsNextDeviceConfig"					//89.
	,"clhsErrorCountSelector"				//90.
	,"clhsErrorCount"						//91.
	,"clhsErrorCountRefresh"				//92.
	,"clhsErrorCountReset"					//93.
	,"refreshGenCPStatus"					//94.
	,"genCPStatus"							//95.
	,"AcquisitionMode"						//96.
	,"AcquisitionStart"						//97.
	,"AcquisitionStop"						//98.
	,"AcquisitionStatus"					//99.
};

featureCtrl::featureCtrl(char* acqServerName)
	: _acqServerName(NULL)
{
	_acqServerName = new char[strlen(acqServerName) + 1];
	strcpy(_acqServerName, acqServerName);
}

featureCtrl::~featureCtrl(void)
{
	delete [] _acqServerName;
	_acqServerName = NULL;
}

/* -----------------------------------------------------------------------------------------
   function : const char *getFeatureName(enum EN_FEATURE_TYPE enFeature)
	   arg1 : enum EN_FEATURE_TYPE enType	種別
	 result : Feature Name へのポインタ
	subject : 指定番号のFeatureNameへのポインタを戻り値に返します。
----------------------------------------------------------------------------------------- */
const char *featureCtrl::getFeatureName(enum EN_FEATURE_TYPE enFeature)
{
	if (enFeature < EN_FEATURE_TYPE_MAX) {
		return _pFeatureName[enFeature];
	}
	return NULL;
}

/* -----------------------------------------------------------------------------------------
   function : BOOL setFeature(enum EN_FEATURE_TYPE enType, int value)
	   arg1 : enum EN_FEATURE_TYPE enType	種別
	   arg2 : int value						値
	 result : true	false
	subject : 設定書き込み
----------------------------------------------------------------------------------------- */
/*
マニュアルには載っているが、ヘッダーファイルに未定義
*/
bool featureCtrl::setFeatureValue(int featureIndex, INT32 featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureIndex, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(int featureIndex, UINT32 featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureIndex, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(int featureIndex, INT64 featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureIndex, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(int featureIndex, UINT64 featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureIndex, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(int featureIndex, float featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureIndex, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(int featureIndex, double featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureIndex, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(int featureIndex, bool featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureIndex, (BOOL)featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(int featureIndex, const char *featureString)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureIndex, featureString);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(int featureIndex, SapBuffer* featureBuffer)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureIndex, featureBuffer);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(int featureIndex, SapLut* featureLut)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureIndex, featureLut);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

/*
マニュアルには載っているが、ヘッダーファイルに未定義
bool featureCtrl::setFeatureValue(const char *featureName, INT32 featureValue)
{
	if (!_acqDevice) return false;
	return _acqDevice->SetFeatureValue(*featureName, featureValue);
}
*/

bool featureCtrl::setFeatureValue(const char *featureName, UINT32 featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureName, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(const char *featureName, INT64 featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureName, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(const char *featureName, UINT64 featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureName, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}
bool featureCtrl::setFeatureValueWithStop(const char *featureName, INT64 featureValue)
{
	bool r,r1,r2;
	bool rs2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		BOOL	StopMode=TRUE;
		r1 = acqDevice.SetFeatureValue(/**/"AcquisitionStop", StopMode);
		r2 = acqDevice.SetFeatureValue(featureName, featureValue);
		rs2= acqDevice.Destroy();
	}
	return (r & rs2);
}

bool featureCtrl::setFeatureValue(const char *featureName, float featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureName, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(const char *featureName, double featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureName, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(const char *featureName, bool featureValue)
{
	bool r;
	bool r2 = false;
	BOOL	bfeatureValue=featureValue;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureName, bfeatureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(const char *featureName, const char *featureString)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureName, featureString);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(const char *featureName, SapBuffer* featureBuffer)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureName, featureBuffer);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::setFeatureValue(const char *featureName, SapLut* featureLut)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.SetFeatureValue(featureName, featureLut);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

/* -----------------------------------------------------------------------------------------
   function : bool getFeature(enum EN_FEATURE_TYPE enType, int value)
	   arg1 : enum EN_FEATURE_TYPE enType	種別
	   arg2 : int value						値
     result : true	false
	subject : 設定読み出し
----------------------------------------------------------------------------------------- */
/*
マニュアルには載っているが、ヘッダーファイルに未定義
*/
bool featureCtrl::getFeatureValue(int featureIndex, INT32* featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureIndex, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}


bool featureCtrl::getFeatureValue(int featureIndex, UINT32* featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureIndex, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(int featureIndex, INT64* featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureIndex, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(int featureIndex, UINT64* featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureIndex, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(int featureIndex, float* featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureIndex, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(int featureIndex, double* featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureIndex, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(int featureIndex, bool* featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureIndex, (BOOL*)featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(int featureIndex, char* featureString, int featureStringSize)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureIndex, featureString, featureStringSize);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(int featureIndex, SapBuffer* featureBuffer)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureIndex, featureBuffer);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(int featureIndex, SapLut* featureLut)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureIndex, featureLut);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

/*
マニュアルには載っているが、ヘッダーファイルに未定義

bool featureCtrl::getFeatureValue(const char* featureName, INT32* featureValue)
{
	if (!_acqDevice) return false;
	return _acqDevice->GetFeatureValue(featureName, featureValue);
}
*/

bool featureCtrl::getFeatureValue(const char* featureName, UINT32* featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureName, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(const char* featureName, INT64* featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureName, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(const char* featureName, UINT64* featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureName, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(const char* featureName, float* featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureName, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(const char* featureName, double* featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureName, featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(const char* featureName, bool* featureValue)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureName, (BOOL*)featureValue);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(const char* featureName, char* featureString, int featureStringSize)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureName, featureString, featureStringSize);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(const char* featureName, SapBuffer* featureBuffer)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureName, featureBuffer);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::getFeatureValue(const char* featureName, SapLut* featureLut)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		r = acqDevice.GetFeatureValue(featureName, featureLut);
		r2= acqDevice.Destroy();
	}
	return (r & r2);
}

bool featureCtrl::GetFeatureInfo(const char *featureName, SapFeature *feature)
{
	bool r;
	bool r2 = false;

	SapAcqDevice acqDevice(_acqServerName);
	if ((r = acqDevice.Create())) {
		/*
		int	featureCount=0;
		acqDevice.GetFeatureCount( &featureCount);
		QStringList	FeatureNameList;
		for(int i = 0; i < featureCount; i++ ){
			char	cfeatureName[256];
			acqDevice.GetFeatureNameByIndex( i, cfeatureName, sizeof( featureName ));
			FeatureNameList.append(cfeatureName);
			//printf( "featureIndex = %04d, featureName = %s\n", i, cfeatureName );
		}
		*/
		feature->SetLocation(acqDevice.GetLocation());
		feature->Create();
		int featureIndex=106;
		r = acqDevice.GetFeatureInfo(featureName, feature);
		BOOL	BRet;
		SapFeature::Type type;
		BRet=feature->GetType(&type);
		SapFeature::AccessMode accessMode;
		BRet=feature->GetAccessMode(&accessMode);
		SapFeature::WriteMode writeMode;
		BRet=feature->GetWriteMode(&writeMode);
		SapFeature::Visibility visibility;
		BRet=feature->GetVisibility(&visibility);

		r2= acqDevice.Destroy();
	}
	return (r & r2);

}