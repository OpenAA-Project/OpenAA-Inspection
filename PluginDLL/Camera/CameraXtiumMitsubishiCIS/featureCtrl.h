#pragma once

class featureCtrl {
public:
	/* ----------------------------------------------------------------------------
	 CONST
	---------------------------------------------------------------------------- */
	// FEATURE ITEM INDEX
	enum EN_FEATURE_TYPE {
		EN_DeviceModelName,								// 0. DeviceModelName
		EN_DeviceVendorName,							// 1. DeviceVendorName
		EN_DeviceSerialNumber,							// 2. DeviceSerialNumber
		EN_DeviceID,									// 3. DeviceID
		EN_DeviceFirmwareVersion,						// 4. DeviceFirmwareVersion
		EN_DeviceVersion,								// 5. DeviceVersion
		EN_DeviceManufacturerInfo,						// 6. DeviceManufacturerInfo
		EN_deviceScriptVersion,							// 7. deviceScriptVersion
		EN_deviceBISTStatus,							// 8. deviceBISTStatus
		EN_deviceBIST,									// 9. deviceBIST
		EN_deviceLEDColorControl,						// 10. deviceLEDColorControl
		EN_DeviceTemperature,							// 11. DeviceTemperature
		EN_refreshTemperature,							// 12. refreshTemperature
		EN_deviceInputVoltage,							// 13. deviceInputVoltage
		EN_refreshVoltage,								// 14. refreshVoltage
		EN_UserSetDefaultSelector,						// 15. UserSetDefaultSelector
		EN_UserSetSelector,								// 16. UserSetSelector
		EN_UserSetLoad,									// 17. UserSetLoad
		EN_UserSetSave,									// 18. UserSetSave
		EN_DeviceReset,									// 19. DeviceReset
		EN_DeviceScanType,								// 20. DeviceScanType
		EN_sensorColorType,								// 21. sensorColorType
		EN_AcquisitionLineRate,							// 22. AcquisitionLineRate
		EN_measuredLineRate,							// 23. measuredLineRate
		EN_refreshMeasuredLineRate,						// 24. refreshMeasuredLineRate
		EN_sensorTDIStagesSelection,					// 25. sensorTDIStagesSelection
		EN_ExposureMode,								// 26. ExposureMode
		EN_ExposureTime,								// 27. ExposureTim
		EN_ScanDirectionSource,							// 28. ScanDirectionSource
		EN_SensorScanDirection,							// 29. SensorScanDirection
		EN_currentDirection,							// 30. currentDirection
		EN_refreshCurrentDirection,						// 31. refreshCurrentDirection
		EN_GainSelector,								// 32. GainSelector
		EN_BlackLevel,									// 33. BlackLevel
		EN_Gain,										// 34. Gain
		EN_sensorLineSpatialCorrection,					// 35. sensorLineSpatialCorrection
		EN_imageDistortionCorrectionMode,				// 36. imageDistortionCorrectionMode
		EN_imageDistortionCorrectionAlgorithm,			// 37. imageDistortionCorrectionAlgorithm
		EN_imageDistortionCorrectionLineSelector,		// 38. imageDistortionCorrectionLineSelector
		EN_imageDistortionParallaxCorrectionPixelStretch,// 39. imageDistortionParallaxCorrectionPixelStretch
		EN_saveLastImageToFlash,						// 40. saveLastImageToFlash
		EN_TriggerMode,									// 41. TriggerMode
		EN_flatfieldCorrectionMode,						// 42. flatfieldCorrectionMode
		EN_flatfieldCalibrationClearCoefficient,		// 43. flatfieldCalibrationClearCoefficient
		EN_flatfieldCorrectionAlgorithm,				// 44. flatfieldCorrectionAlgorithm
		EN_flatfieldCalibrationTarget,					// 45. flatfieldCalibrationTarget
		EN_flatfieldCalibrationSampleSize,				// 46. flatfieldCalibrationSampleSize
		EN_flatfieldCalibrationROIOffsetX,				// 47. flatfieldCalibrationROIOffsetX
		EN_flatfieldCalibrationROIWidth,				// 48. flatfieldCalibrationROIWidth
		EN_flatfieldCalibrationFPN,						// 49. flatfieldCalibrationFPN
		EN_flatfieldCalibrationPRNU,					// 50. flatfieldCalibrationPRNU
		EN_flatfieldRoiPrnu,							// 51. flatfieldRoiPrnu
		EN_flatfieldSetRoiPrnu,							// 52. flatfieldSetRoiPrnu
		EN_flatfieldCorrectionCurrentActiveSet,			// 53. flatfieldCorrectionCurrentActiveSet
		EN_flatfieldCalibrationSave,					// 54. flatfieldCalibrationSave
		EN_flatfieldCalibrationLoad,					// 55. flatfieldCalibrationLoad
		EN_flatfieldSfrRoiSelector,						// 56. flatfieldSfrRoiSelector
		EN_flatfieldSfrRoiOffsetX,						// 57. flatfieldSfrRoiOffsetX
		EN_flatfieldSfrRoiWidth,						// 58. flatfieldSfrRoiWidth
		EN_flatfieldSfrRoiValue,						// 59. flatfieldSfrRoiValue
		EN_BalanceWhiteAuto,							// 60. BalanceWhiteAuto
		EN_lutMode,										// 61. lutMode
		EN_gammaCorrection,								// 62. gammaCorrection
		EN_blackLevelEnable,							// 63. blackLevelEnable
		EN_calibrateBlackLevel,							// 64. calibrateBlackLevel
		EN_PixelFormat,									// 65. PixelFormat
		EN_ComponentSelector,							// 66. ComponentSelector
		EN_ComponentEnable,								// 67. ComponentEnable
		EN_ComponentID,									// 68. ComponentID
		EN_PixelColorFilter,							// 69. PixelColorFilter
		EN_WidthMax,									// 70. WidthMax
		EN_OffsetX,										// 71. OffsetX
		EN_Width,										// 72. Width
		EN_Height,										// 73. Height
		EN_BinningHorizontal,							// 74. BinningHorizontal
		EN_BinningVertical,								// 75. BinningVertical
		EN_TestImageSelector,							// 76. TestImageSelector
		EN_portRoiSelector,								// 77. portRoiSelector
		EN_multipleROICount,							// 78. multipleROICount
		EN_multipleROISelector,							// 79. multipleROISelector
		EN_multipleROIOffsetX,							// 80. multipleROIOffsetX
		EN_multipleROIWidth,							// 81. multipleROIWidth
		EN_FileSelector,								// 82. FileSelector
		EN_FileOperationExecute,						// 83. FileOperationExecute
		EN_FileOpenMode,								// 84. FileOpenMode
		EN_FileAccessOffset,							// 85. FileAccessOffset
		EN_FileAccessLength,							// 86. FileAccessLength
		EN_FileAccessBuffer,							// 87. FileAccessBuffer
		EN_FileSize,									// 88. FileSize
		EN_FileOperationSelector,						// 89. FileOperationSelector
		EN_FileOperationStatus,							// 90. FileOperationStatus
		EN_FileOperationResult,							// 91. FileOperationResult
		EN_DeviceManifestXMLMajorVersion,				// 92. DeviceManifestXMLMajorVersion
		EN_DeviceManifestXMLMinorVersion,				// 93. DeviceManifestXMLMinorVersion
		EN_clhsDiscovery,								// 94. clhsDiscovery
		EN_clhsNextDeviceConfig,						// 95. clhsNextDeviceConfig
		EN_clhsErrorCountSelector,						// 96. clhsErrorCountSelector
		EN_clhsErrorCount,								// 97. clhsErrorCount
		EN_clhsErrorCountRefresh,						// 98. clhsErrorCountRefresh
		EN_clhsErrorCountReset,							// 99. clhsErrorCountReset
		EN_refreshGenCPStatus,							// 100. refreshGenCPStatus
		EN_genCPStatus,									// 101. genCPStatus
		EN_AcquisitionMode,								// 102. AcquisitionMode
		EN_AcquisitionStart,							// 103. AcquisitionStart
		EN_AcquisitionStop,								// 104. AcquisitionStop
		EN_AcquisitionStatus,							// 105. AcquisitionStatus
		EN_SaperaBufferFormat,							// 106. SaperaBufferFormat
		EN_PixelSize,									// 107. PixelSize
		EN_FEATURE_TYPE_MAX
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
