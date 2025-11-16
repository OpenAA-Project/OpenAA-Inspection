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
	"DeviceModelName",								// 0. DeviceModelName
	"DeviceVendorName",								// 1. DeviceVendorName
	"DeviceSerialNumber",							// 2. DeviceSerialNumber
	"DeviceID",										// 3. DeviceID
	"DeviceFirmwareVersion",						// 4. DeviceFirmwareVersion
	"DeviceVersion",								// 5. DeviceVersion
	"DeviceManufacturerInfo",						// 6. DeviceManufacturerInfo
	"deviceScriptVersion",							// 7. deviceScriptVersion
	"deviceBISTStatus",								// 8. deviceBISTStatus
	"deviceBIST",									// 9. deviceBIST
	"deviceLEDColorControl",						// 10. deviceLEDColorControl
	"DeviceTemperature",							// 11. DeviceTemperature
	"refreshTemperature",							// 12. refreshTemperature
	"deviceInputVoltage",							// 13. deviceInputVoltage
	"refreshVoltage",								// 14. refreshVoltage
	"UserSetDefaultSelector",						// 15. UserSetDefaultSelector
	"UserSetSelector",								// 16. UserSetSelector
	"UserSetLoad",									// 17. UserSetLoad
	"UserSetSave",									// 18. UserSetSave
	"DeviceReset",									// 19. DeviceReset
	"DeviceScanType",								// 20. DeviceScanType
	"sensorColorType",								// 21. sensorColorType
	"AcquisitionLineRate",							// 22. AcquisitionLineRate
	"measuredLineRate",								// 23. measuredLineRate
	"refreshMeasuredLineRate",						// 24. refreshMeasuredLineRate
	"sensorTDIStagesSelection",						// 25. sensorTDIStagesSelection
	"ExposureMode",									// 26. ExposureMode
	"ExposureTime",									// 27. ExposureTime
	"ScanDirectionSource",							// 28. ScanDirectionSource
	"SensorScanDirection",							// 29. SensorScanDirection
	"currentDirection",								// 30. currentDirection
	"refreshCurrentDirection",						// 31. refreshCurrentDirection
	"GainSelector",									// 32. GainSelector
	"BlackLevel",									// 33. BlackLevel
	"Gain",											// 34. Gain
	"sensorLineSpatialCorrection",					// 35. sensorLineSpatialCorrection
	"imageDistortionCorrectionMode",				// 36. imageDistortionCorrectionMode
	"imageDistortionCorrectionAlgorithm",			// 37. imageDistortionCorrectionAlgorithm
	"imageDistortionCorrectionLineSelector",		// 38. imageDistortionCorrectionLineSelector
	"imageDistortionParallaxCorrectionPixelStretch",// 39. imageDistortionParallaxCorrectionPixelStretch
	"saveLastImageToFlash",							// 40. saveLastImageToFlash
	"TriggerMode",									// 41. TriggerMode
	"flatfieldCorrectionMode",						// 42. flatfieldCorrectionMode
	"flatfieldCalibrationClearCoefficient",			// 43. flatfieldCalibrationClearCoefficient
	"flatfieldCorrectionAlgorithm",					// 44. flatfieldCorrectionAlgorithm
	"flatfieldCalibrationTarget",					// 45. flatfieldCalibrationTarget
	"flatfieldCalibrationSampleSize",				// 46. flatfieldCalibrationSampleSize
	"flatfieldCalibrationROIOffsetX",				// 47. flatfieldCalibrationROIOffsetX
	"flatfieldCalibrationROIWidth",					// 48. flatfieldCalibrationROIWidth
	"flatfieldCalibrationFPN",						// 49. flatfieldCalibrationFPN
	"flatfieldCalibrationPRNU",						// 50. flatfieldCalibrationPRNU
	"flatfieldRoiPrnu",								// 51. flatfieldRoiPrnu
	"flatfieldSetRoiPrnu",							// 52. flatfieldSetRoiPrnu
	"flatfieldCorrectionCurrentActiveSet",			// 53. flatfieldCorrectionCurrentActiveSet
	"flatfieldCalibrationSave",						// 54. flatfieldCalibrationSave
	"flatfieldCalibrationLoad",						// 55. flatfieldCalibrationLoad
	"flatfieldSfrRoiSelector",						// 56. flatfieldSfrRoiSelector
	"flatfieldSfrRoiOffsetX",						// 57. flatfieldSfrRoiOffsetX
	"flatfieldSfrRoiWidth",							// 58. flatfieldSfrRoiWidth
	"flatfieldSfrRoiValue",							// 59. flatfieldSfrRoiValue
	"BalanceWhiteAuto",								// 60. BalanceWhiteAuto
	"lutMode",										// 61. lutMode
	"gammaCorrection",								// 62. gammaCorrection
	"blackLevelEnable",								// 63. blackLevelEnable
	"calibrateBlackLevel",							// 64. calibrateBlackLevel
	"PixelFormat",									// 65. PixelFormat
	"ComponentSelector",							// 66. ComponentSelector
	"ComponentEnable",								// 67. ComponentEnable
	"ComponentID",									// 68. ComponentID
	"PixelColorFilter",								// 69. PixelColorFilter
	"WidthMax",										// 70. WidthMax
	"OffsetX",										// 71. OffsetX
	"Width",										// 72. Width
	"Height",										// 73. Height
	"BinningHorizontal",							// 74. BinningHorizontal
	"BinningVertical",								// 75. BinningVertical
	"TestImageSelector",							// 76. TestImageSelector
	"portRoiSelector",								// 77. portRoiSelector
	"multipleROICount",								// 78. multipleROICount
	"multipleROISelector",							// 79. multipleROISelector
	"multipleROIOffsetX",							// 80. multipleROIOffsetX
	"multipleROIWidth",								// 81. multipleROIWidth
	"FileSelector",									// 82. FileSelector
	"FileOperationExecute",							// 83. FileOperationExecute
	"FileOpenMode",									// 84. FileOpenMode
	"FileAccessOffset",								// 85. FileAccessOffset
	"FileAccessLength",								// 86. FileAccessLength
	"FileAccessBuffer",								// 87. FileAccessBuffer
	"FileSize",										// 88. FileSize
	"FileOperationSelector",						// 89. FileOperationSelector
	"FileOperationStatus",							// 90. FileOperationStatus
	"FileOperationResult",							// 91. FileOperationResult
	"DeviceManifestXMLMajorVersion",				// 92. DeviceManifestXMLMajorVersion
	"DeviceManifestXMLMinorVersion",				// 93. DeviceManifestXMLMinorVersion
	"clhsDiscovery",								// 94. clhsDiscovery
	"clhsNextDeviceConfig",							// 95. clhsNextDeviceConfig
	"clhsErrorCountSelector",						// 96. clhsErrorCountSelector
	"clhsErrorCount",								// 97. clhsErrorCount
	"clhsErrorCountRefresh",						// 98. clhsErrorCountRefresh
	"clhsErrorCountReset",							// 99. clhsErrorCountReset
	"refreshGenCPStatus",							// 100. refreshGenCPStatus
	"genCPStatus",									// 101. genCPStatus
	"AcquisitionMode",								// 102. AcquisitionMode
	"AcquisitionStart",								// 103. AcquisitionStart
	"AcquisitionStop",								// 104. AcquisitionStop
	"AcquisitionStatus",							// 105. AcquisitionStatus
	"SaperaBufferFormat",							// 106. SaperaBufferFormat
	"PixelSize"										// 107. PixelSize
};

featureCtrl::featureCtrl(char* acqServerName)
	: _acqServerName(NULL)
{
	_acqServerName = new char[strlen(acqServerName) + 1];
	strcpy(_acqServerName, acqServerName);
	acqDevice=new SapAcqDevice(_acqServerName);
	SuccessOfCreate=acqDevice->Create();
}

featureCtrl::~featureCtrl(void)
{
	delete [] _acqServerName;
	_acqServerName = NULL;

	if(acqDevice!=NULL){
		acqDevice->Destroy();
		delete	acqDevice;
		acqDevice=NULL;
	}
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
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureIndex, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->SetFeatureValue(featureIndex, featureValue);
	return r;
}

bool featureCtrl::setFeatureValue(int featureIndex, UINT32 featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureIndex, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);

	r = acqDevice->SetFeatureValue(featureIndex, featureValue);
	return r;
}

bool featureCtrl::setFeatureValue(int featureIndex, INT64 featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureIndex, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);

	r = acqDevice->SetFeatureValue(featureIndex, featureValue);
	return r;
}

bool featureCtrl::setFeatureValue(int featureIndex, UINT64 featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureIndex, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);

	r = acqDevice->SetFeatureValue(featureIndex, featureValue);
	return r;
}

bool featureCtrl::setFeatureValue(int featureIndex, float featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureIndex, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);

	r = acqDevice->SetFeatureValue(featureIndex, featureValue);
	return r;
}

bool featureCtrl::setFeatureValue(int featureIndex, double featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureIndex, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);

	r = acqDevice->SetFeatureValue(featureIndex, featureValue);
	return r;
}

bool featureCtrl::setFeatureValue(int featureIndex, bool featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureIndex, (BOOL)featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->SetFeatureValue(featureIndex, featureValue);
	return r;
}

bool featureCtrl::setFeatureValue(int featureIndex, const char *featureString)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureIndex, featureString);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->SetFeatureValue(featureIndex, featureString);
	return r;
}

bool featureCtrl::setFeatureValue(int featureIndex, SapBuffer* featureBuffer)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureIndex, featureBuffer);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->SetFeatureValue(featureIndex, featureBuffer);
	return r;
}

bool featureCtrl::setFeatureValue(int featureIndex, SapLut* featureLut)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureIndex, featureLut);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->SetFeatureValue(featureIndex, featureLut);
	return r;
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
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureName, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);

	r = acqDevice->SetFeatureValue(featureName, featureValue);
	return r;
}

bool featureCtrl::setFeatureValue(const char *featureName, INT64 featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureName, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);

	r = acqDevice->SetFeatureValue(featureName, featureValue);
	return r;
}

bool featureCtrl::setFeatureValue(const char *featureName, UINT64 featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureName, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->SetFeatureValue(featureName, featureValue);
	return r;
}
bool featureCtrl::setFeatureValueWithStop(const char *featureName, INT64 featureValue)
{
	bool r,r1,r2;
	//bool rs2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	BOOL	StopMode=TRUE;
	//	r1 = acqDevice.SetFeatureValue(/**/"AcquisitionStop", StopMode);
	//	r2 = acqDevice.SetFeatureValue(featureName, featureValue);
	//	rs2= acqDevice.Destroy();
	//}
	//return (r & rs2);

	BOOL	StopMode=TRUE;
	r1 = acqDevice->SetFeatureValue(/**/"AcquisitionStop", StopMode);
	r2 = acqDevice->SetFeatureValue(featureName, featureValue);
	return r1 & r2;
}

bool featureCtrl::setFeatureValue(const char *featureName, float featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureName, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);

	r = acqDevice->SetFeatureValue(featureName, featureValue);
	return r;
}

bool featureCtrl::setFeatureValue(const char *featureName, double featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureName, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->SetFeatureValue(featureName, featureValue);
	return r;
}

bool featureCtrl::setFeatureValue(const char *featureName, bool featureValue)
{
	bool r;
	//bool r2 = false;
	//BOOL	bfeatureValue=featureValue;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureName, bfeatureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	BOOL	B;
	if(featureValue==true)
		B=TRUE;
	else
		B=false;
	r = acqDevice->SetFeatureValue(featureName, B);
	return r;
}

bool featureCtrl::setFeatureValue(const char *featureName, const char *featureString)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureName, featureString);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->SetFeatureValue(featureName, featureString);
	return r;
}

bool featureCtrl::setFeatureValue(const char *featureName, SapBuffer* featureBuffer)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureName, featureBuffer);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->SetFeatureValue(featureName, featureBuffer);
	return r;
}

bool featureCtrl::setFeatureValue(const char *featureName, SapLut* featureLut)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.SetFeatureValue(featureName, featureLut);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->SetFeatureValue(featureName, featureLut);
	return r;
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
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureIndex, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureIndex, featureValue);
	return r;
}


bool featureCtrl::getFeatureValue(int featureIndex, UINT32* featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureIndex, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureIndex, featureValue);
	return r;
}

bool featureCtrl::getFeatureValue(int featureIndex, INT64* featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureIndex, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureIndex, featureValue);
	return r;
}

bool featureCtrl::getFeatureValue(int featureIndex, UINT64* featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureIndex, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureIndex, featureValue);
	return r;
}

bool featureCtrl::getFeatureValue(int featureIndex, float* featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureIndex, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureIndex, featureValue);
	return r;
}

bool featureCtrl::getFeatureValue(int featureIndex, double* featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureIndex, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureIndex, featureValue);
	return r;
}

bool featureCtrl::getFeatureValue(int featureIndex, bool* featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureIndex, (BOOL*)featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureIndex, (BOOL*)featureValue);
	return r;
}

bool featureCtrl::getFeatureValue(int featureIndex, char* featureString, int featureStringSize)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureIndex, featureString, featureStringSize);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureIndex, featureString, featureStringSize);
	return r;
}

bool featureCtrl::getFeatureValue(int featureIndex, SapBuffer* featureBuffer)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureIndex, featureBuffer);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureIndex, featureBuffer);
	return r;
}

bool featureCtrl::getFeatureValue(int featureIndex, SapLut* featureLut)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureIndex, featureLut);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureIndex, featureLut);
	return r;
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
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureName, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureName, featureValue);
	return r;
}

bool featureCtrl::getFeatureValue(const char* featureName, INT64* featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureName, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureName, featureValue);
	return r;
}

bool featureCtrl::getFeatureValue(const char* featureName, UINT64* featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureName, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureName, featureValue);
	return r;
}

bool featureCtrl::getFeatureValue(const char* featureName, float* featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureName, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureName, featureValue);
	return r;
}

bool featureCtrl::getFeatureValue(const char* featureName, double* featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureName, featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureName, featureValue);
	return r;
}

bool featureCtrl::getFeatureValue(const char* featureName, bool* featureValue)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureName, (BOOL*)featureValue);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureName, (BOOL*)featureValue);
	return r;
}

bool featureCtrl::getFeatureValue(const char* featureName, char* featureString, int featureStringSize)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureName, featureString, featureStringSize);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureName,  featureString, featureStringSize);
	return r;
}

bool featureCtrl::getFeatureValue(const char* featureName, SapBuffer* featureBuffer)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureName, featureBuffer);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureName, featureBuffer);
	return r;
}

bool featureCtrl::getFeatureValue(const char* featureName, SapLut* featureLut)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	r = acqDevice.GetFeatureValue(featureName, featureLut);
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);
	r = acqDevice->GetFeatureValue(featureName, featureLut);
	return r;
}

bool featureCtrl::GetFeatureInfo(const char *featureName, SapFeature *feature)
{
	bool r;
	//bool r2 = false;
	//
	//SapAcqDevice acqDevice(_acqServerName);
	//if ((r = acqDevice.Create())) {
	//	feature->SetLocation(acqDevice.GetLocation());
	//	feature->Create();
	//	int featureIndex=106;
	//	r = acqDevice.GetFeatureInfo(featureName, feature);
	//	BOOL	BRet;
	//	SapFeature::Type type;
	//	BRet=feature->GetType(&type);
	//	SapFeature::AccessMode accessMode;
	//	BRet=feature->GetAccessMode(&accessMode);
	//	SapFeature::WriteMode writeMode;
	//	BRet=feature->GetWriteMode(&writeMode);
	//	SapFeature::Visibility visibility;
	//	BRet=feature->GetVisibility(&visibility);
	//
	//	r2= acqDevice.Destroy();
	//}
	//return (r & r2);

	feature->SetLocation(acqDevice->GetLocation());
	feature->Create();
	int featureIndex=106;
	r = acqDevice->GetFeatureInfo(featureName, feature);
	BOOL	BRet;
	SapFeature::Type type;
	BRet=feature->GetType(&type);
	SapFeature::AccessMode accessMode;
	BRet=feature->GetAccessMode(&accessMode);
	SapFeature::WriteMode writeMode;
	BRet=feature->GetWriteMode(&writeMode);
	SapFeature::Visibility visibility;
	BRet=feature->GetVisibility(&visibility);
	return r;
}