/*
 * Copyright (C) 2021
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

#ifndef CAMERAXTIUMCLHS_PX8_H
#define CAMERAXTIUMCLHS_PX8_H

#include <qglobal.h>
#include <QList>
#include <QRgb>
#include <QDialog>
#include "CLHS_PX8CommandCreater.h"
#include "CameraXtium_global.h"
#include "XCameraHandle.h"

class	saperaCtrl;

class AbstructOriginateClass
{
public:
	AbstructOriginateClass(bool original):m_isOriginal(original){};

public:
	void setOriginal(bool original){ m_isOriginal = original; };
	bool isOriginal() const { return m_isOriginal; };

public:
	AbstructOriginateClass &operator=(const AbstructOriginateClass &other)
	{
		setOriginal(false);
		return *this;
	};

private:
	bool m_isOriginal;
};

// GlobalGrabberState::stG_Grabber -> all LocalGrabbrState::stL_Grabber
// all LocalGrabbrState::stL_GrabEnd -> GlobalGrabberState::stG_GrabEnd
enum LocalGrabberState{
	stL_Idle=0,		// �ҋ@
	stL_Grabber=1,	// �B���ҋ@��
	stL_GrabEnd=2	// �B���I��
};

enum GlobalGrabberState{
	stG_Idle=0,		// �ҋ@
	stG_Grabber=1	// �B����
};

class CameraXtiumCLHS_PX8 : public AbstructOriginateClass,public CameraHandle
{
public:
	CameraXtiumCLHS_PX8(int CamNo ,LayersBase *base ,bool original);
	~CameraXtiumCLHS_PX8();

public:
	int					DeviceID;
	CLHS_PX8Setting		Setting;
	saperaCtrl			*_sapera;
};

#endif // CAMERAXTIUMCLHS_PX8_H