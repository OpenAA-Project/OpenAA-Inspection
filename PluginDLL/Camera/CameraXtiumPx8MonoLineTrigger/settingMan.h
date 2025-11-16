#pragma once

#include <QString>

class CameraCommand;

// 対応コマンドの一覧
enum CLHS_PX8Type{
	TYPE_Gain,
	TYPE_DigitalOffset,
	TYPE_ExposureMode,// 露光モード設定
	TYPE_ExposureTime,// 露光時間設定
	TYPE_UseTestPattern,// テストパターン使用フラグ
	TYPE_ScanDirection,// スキャン方向設定
	TYPE_ENUM_COUNT
};

class CLHS_PX8Setting
{
public:
	CLHS_PX8Setting::CLHS_PX8Setting(){
		clear();
	};

	void clear(){
		Gain = 0;
		DigitalOffset = 0;
		ExposureMode = 0;
		ExposureTime = 56;
		EnableTestPattern = false;
		ScanDirection = true;
	};

	double getData(CLHS_PX8Type type) const {
		switch(type){
		case TYPE_Gain:
			return Gain;
			break;

		case TYPE_DigitalOffset:
			return DigitalOffset;
			break;

		case TYPE_ExposureMode:
			return ExposureMode;// 露光モード設定
			break;
		case TYPE_ExposureTime:
			return ExposureTime;// 露光時間設定
			break;
		case TYPE_UseTestPattern:
			return ((EnableTestPattern==false) ? 0 : 1);// テストパターン使用フラグ
			break;
		case TYPE_ScanDirection:
			return ((ScanDirection==true) ? 0 : 1);// スキャン方向設定
			break;
		default:
			return INT_MIN;
			break;
		}

		return INT_MIN;
	};

public:
	double	Gain;
	int		DigitalOffset;	
	int ExposureMode;/* 0:FreeRun, 1:Edge, 2:virtual expose fix by time on edge, 3:virtual expose fix by time on level */
	int ExposureTime;/* 56 to 32767 */
	bool EnableTestPattern;/* true:setTest, false:defaultOut */
	bool ScanDirection;/* true:forward, false:reverse */
};

// [usage]
// QString commStr;
// commStr += CameraCommand::setRGBGain(350, 350, 350);
// commStr += CameraCommand::setRGBOffset(0, 0, 0);
// CameraCommand::endCommand(commStr);
// comRW << commStr;

class CLHS_PX8CommandCreater
{
public:
	// RGBゲイン
	static QString setGain(double gain/* 280 to 530 */);

	// オフセット
	static QString setDigitalOffset(int offset/* 0 to 12 */);

	// 出力設定
	static QString initialOnFactory(void);
	static QString loadFromMemory(void);
	static QString saveToMemory(void);
	static QString setExposureMode(int type/* 0:FreeRun, 1:Edge, 2:virtual expose fix by time on edge, 3:virtual expose fix by time on level */);
	static QString setExposureTime(int exposure/* 56 to 32767 */);
	static QString setTestPatternOutput(bool useTest/* true:setTest, false:defaultOut */);
	static QString setScanDirection(bool forward/* true:forward, false:reverse */);

	static QString createFixCommandFromStruct(const CLHS_PX8Setting &data);// this command is able to use soon after created.

public:
	// 情報取得
	static QString getCurrentCameraState();

public:
	static QString makeCommand(const QString &CMD, double value, double min, double max);
	static QString makeCommand2(const QString &CMD, double value1, double value2, double min, double max);
	static QString makeCommand(const QString &CMD, double value);
	static QString makeCommand2(const QString &CMD, double value1, double value2);
	static QString makeCommand(const QString &CMD);
};

class CameraCommand : public CLHS_PX8CommandCreater {};