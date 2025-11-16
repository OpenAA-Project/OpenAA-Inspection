#pragma once

class featureCtrl {
public:
	/* ----------------------------------------------------------------------------
	 CONST
	---------------------------------------------------------------------------- */
	// FEATURE ITEM INDEX
	enum EN_FEATURE_TYPE {
		EN_DeviceModelName						//0. 
		,EN_DeviceVendorName					//1. 
		,EN_DeviceSerialNumber					//2. 
		,EN_DeviceID							//3. 
		,EN_DeviceFirmwareVersion				//4. 
		,EN_DeviceVersion						//5. 
		,EN_DeviceManufacturerInfo				//6. 
		,EN_deviceScriptVersion					//7. 
		,EN_deviceBISTStatus					//8. 
		,EN_deviceBIST							//9. 
		,EN_deviceLEDColorControl				//10.
		,EN_DeviceTemperature					//11.
		,EN_refreshTemperature					//12.
		,EN_deviceInputVoltage					//13.
		,EN_refreshVoltage						//14.
		,EN_UserSetDefaultSelector				//15.
		,EN_UserSetSelector						//16.
		,EN_UserSetLoad							//17.
		,EN_UserSetSave							//18.
		,EN_DeviceReset							//19.
		,EN_DeviceScanType						//20.
		,EN_sensorColorType						//21.
		,EN_AcquisitionLineRate					//22.
		,EN_measuredLineRate					//23.
		,EN_refreshMeasuredLineRate				//24.
		,EN_sensorTDIStagesSelection			//25.
		,EN_ExposureMode						//26.
		,EN_ExposureTime						//27.
		,EN_ScanDirectionSource					//28.
		,EN_SensorScanDirection					//29.
		,EN_currentDirection					//30.
		,EN_refreshCurrentDirection				//31.
		,EN_BlackLevel							//32.
		,EN_GainSelector						//33.
		,EN_gainExtended						//34.
		,EN_Gain								//35.
		,EN_TriggerMode							//36.
		,EN_flatfieldCorrectionMode				//37.
		,EN_flatfieldCalibrationClearCoefficient//38.
		,EN_flatfieldCorrectionAlgorithm		//39.
		,EN_flatfieldCalibrationTarget			//40.
		,EN_flatfieldCalibrationSampleSize		//41.
		,EN_flatfieldCalibrationROIOffsetX		//42.
		,EN_flatfieldCalibrationROIWidth		//43.
		,EN_flatfieldCalibrationFPN				//44.
		,EN_flatfieldCalibrationPRNU			//45.
		,EN_flatfieldRoiPrnu					//46.
		,EN_flatfieldSetRoiPrnu					//47.
		,EN_flatfieldCorrectionCurrentActiveSet	//48.
		,EN_flatfieldCalibrationSave			//49.
		,EN_flatfieldCalibrationLoad			//50.
		,EN_lutMode								//51.
		,EN_gammaCorrection						//52.
		,EN_lutSize								//53.
		,EN_flatfieldSfrRoiSelector				//54.
		,EN_flatfieldSfrRoiOffsetX				//55.
		,EN_flatfieldSfrRoiWidth				//56.
		,EN_flatfieldSfrRoiValue				//57.
		,EN_blackLevelEnable					//58.
		,EN_calibrateBlackLevel					//59.
		,EN_imageMagnificationMode				//60.
		,EN_PixelFormat							//61.
		,EN_PixelCoding							//62.
		,EN_PixelColorFilter					//63.
		,EN_WidthMax							//64.
		,EN_OffsetX								//65.
		,EN_Width								//66.
		,EN_Height								//67.
		,EN_BinningHorizontal					//68.
		,EN_BinningVertical						//69.
		,EN_TestImageSelector					//70.
		,EN_portRoiSelector						//71.
		,EN_multipleROICount					//72.
		,EN_multipleROISelector					//73.
		,EN_multipleROIOffsetX					//74.
		,EN_multipleROIWidth					//75.
		,EN_FileSelector						//76.
		,EN_FileOperationExecute				//77.
		,EN_FileOpenMode						//78.
		,EN_FileAccessOffset					//79.
		,EN_FileAccessLength					//80.
		,EN_FileAccessBuffer					//81.
		,EN_FileSize							//82.
		,EN_FileOperationSelector				//83.
		,EN_FileOperationStatus					//84.
		,EN_FileOperationResult					//85.
		,EN_DeviceManifestXMLMajorVersion		//86.
		,EN_DeviceManifestXMLMinorVersion		//87.
		,EN_clhsDiscovery						//88.
		,EN_clhsNextDeviceConfig				//89.
		,EN_clhsErrorCountSelector				//90.
		,EN_clhsErrorCount						//91.
		,EN_clhsErrorCountRefresh				//92.
		,EN_clhsErrorCountReset					//93.
		,EN_refreshGenCPStatus					//94.
		,EN_genCPStatus							//95.
		,EN_AcquisitionMode						//96.
		,EN_AcquisitionStart					//97.
		,EN_AcquisitionStop						//98.
		,EN_AcquisitionStatus					//99.

		,EN_FEATURE_TYPE_MAX
	};

	/* ----------------------------------------------------------------------------
	 FUNCTIONS
	---------------------------------------------------------------------------- */
public:
	featureCtrl(char* acqServerName);
	~featureCtrl(void);

	const char *getFeatureName(enum EN_FEATURE_TYPE enFeature);

	bool setFeatureValue(int featureIndex, INT32 featureValue);
	bool setFeatureValue(int featureIndex, UINT32 featureValue);
	bool setFeatureValue(int featureIndex, INT64 featureValue);
	bool setFeatureValue(int featureIndex, UINT64 featureValue);
	bool setFeatureValue(int featureIndex, float featureValue);
	bool setFeatureValue(int featureIndex, double featureValue);
	bool setFeatureValue(int featureIndex, bool featureValue);
	bool setFeatureValue(int featureIndex, const char *featureString);
	bool setFeatureValue(int featureIndex, SapBuffer* featureBuffer);
	bool setFeatureValue(int featureIndex, SapLut* featureLut);
	bool setFeatureValue(const char *featureName, INT32 featureValue);
	bool setFeatureValue(const char *featureName, UINT32 featureValue);
	bool setFeatureValue(const char *featureName, INT64 featureValue);
	bool setFeatureValueWithStop(const char *featureName, INT64 featureValue);
	bool setFeatureValue(const char *featureName, UINT64 featureValue);
	bool setFeatureValue(const char *featureName, float featureValue);
	bool setFeatureValue(const char *featureName, double featureValue);
	bool setFeatureValue(const char *featureName, bool featureValue);
	bool setFeatureValue(const char *featureName, const char *featureString);
	bool setFeatureValue(const char *featureName, SapBuffer* featureBuffer);
	bool setFeatureValue(const char *featureName, SapLut* featureLut);
	bool getFeatureValue(int featureIndex, INT32* featureValue);
	bool getFeatureValue(int featureIndex, UINT32* featureValue);
	bool getFeatureValue(int featureIndex, INT64* featureValue);
	bool getFeatureValue(int featureIndex, UINT64* featureValue);
	bool getFeatureValue(int featureIndex, float* featureValue);
	bool getFeatureValue(int featureIndex, double* featureValue);
	bool getFeatureValue(int featureIndex, bool* featureValue);
	bool getFeatureValue(int featureIndex, char* featureString, int featureStringSize);
	bool getFeatureValue(int featureIndex, SapBuffer* featureBuffer);
	bool getFeatureValue(int featureIndex, SapLut* featureLut);
	bool getFeatureValue(const char* featureName, INT32* featureValue);
	bool getFeatureValue(const char* featureName, UINT32* featureValue);
	bool getFeatureValue(const char* featureName, INT64* featureValue);
	bool getFeatureValue(const char* featureName, UINT64* featureValue);
	bool getFeatureValue(const char* featureName, float* featureValue);
	bool getFeatureValue(const char* featureName, double* featureValue);
	bool getFeatureValue(const char* featureName, bool* featureValue);
	bool getFeatureValue(const char* featureName, char* featureString, int featureStringSize);
	bool getFeatureValue(const char* featureName, SapBuffer* featureBuffer);
	bool getFeatureValue(const char* featureName, SapLut* featureLut);
   
	bool	GetFeatureInfo(const char *featureName, SapFeature *feature);
   /* ----------------------------------------------------------------------------
	 PUBLIC VALUES
	---------------------------------------------------------------------------- */
public:
	static const char *_pFeatureName[EN_FEATURE_TYPE_MAX];
	char *_acqServerName;

	/* ----------------------------------------------------------------------------
	 PRIVATE VALUES
	---------------------------------------------------------------------------- */
private:
};
