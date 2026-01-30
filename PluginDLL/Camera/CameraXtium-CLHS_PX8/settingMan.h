/*
 * Copyright (C) 2018
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

#pragma once

#include <QString>

class CameraCommand;

// �Ή��R�}���h�̈ꗗ
enum CLHS_PX8Type{
	TYPE_AnalogGain,
	TYPE_DigitalGain,
	TYPE_DigitalOffset,
	TYPE_ExposureMode,// �I�����[�h�ݒ�
	TYPE_ExposureTime,// �I�����Ԑݒ�
	TYPE_UseTestPattern,// �e�X�g�p�^�[���g�p�t���O
	TYPE_ScanDirection,// �X�L���������ݒ�
	TYPE_ENUM_COUNT
};

class CLHS_PX8Setting
{
public:
	CLHS_PX8Setting::CLHS_PX8Setting(){
		clear();
	};

	void clear(){
		AnalogGain = 0;
		DigitalGain = 0;
		DigitalOffset = 0;
		ExposureMode = 0;
		ExposureTime = 56;
		EnableTestPattern = false;
		ScanDirection = true;
	};

	double getData(CLHS_PX8Type type) const {
		switch(type){
		case TYPE_AnalogGain:
			return AnalogGain;
			break;
		case TYPE_DigitalGain:
			return DigitalGain;
			break;
		case TYPE_DigitalOffset:
			return DigitalOffset;
			break;

		case TYPE_ExposureMode:
			return ExposureMode;// �I�����[�h�ݒ�
			break;
		case TYPE_ExposureTime:
			return ExposureTime;// �I�����Ԑݒ�
			break;
		case TYPE_UseTestPattern:
			return ((EnableTestPattern==false) ? 0 : 1);// �e�X�g�p�^�[���g�p�t���O
			break;
		case TYPE_ScanDirection:
			return ((ScanDirection==true) ? 0 : 1);// �X�L���������ݒ�
			break;
		default:
			return INT_MIN;
			break;
		}

		return INT_MIN;
	};

public:
	double	AnalogGain;
	int		DigitalGain;	
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
	// RGB�Q�C��
	static QString setAnalogGain(double gain/* 280 to 530 */);
	static QString setDigitalGain(int gain/* 220 to 470 */);

	// �I�t�Z�b�g
	static QString setDigitalOffset(int offset/* 0 to 12 */);

	// �o�͐ݒ�
	static QString initialOnFactory(void);
	static QString loadFromMemory(void);
	static QString saveToMemory(void);
	static QString setExposureMode(int type/* 0:FreeRun, 1:Edge, 2:virtual expose fix by time on edge, 3:virtual expose fix by time on level */);
	static QString setExposureTime(int exposure/* 56 to 32767 */);
	static QString setTestPatternOutput(bool useTest/* true:setTest, false:defaultOut */);
	static QString setScanDirection(bool forward/* true:forward, false:reverse */);

	static QString createFixCommandFromStruct(const CLHS_PX8Setting &data);// this command is able to use soon after created.

public:
	// �����擾
	static QString getCurrentCameraState();

public:
	static QString makeCommand(const QString &CMD, double value, double min, double max);
	static QString makeCommand2(const QString &CMD, double value1, double value2, double min, double max);
	static QString makeCommand(const QString &CMD, double value);
	static QString makeCommand2(const QString &CMD, double value1, double value2);
	static QString makeCommand(const QString &CMD);
};

class CameraCommand : public CLHS_PX8CommandCreater {};