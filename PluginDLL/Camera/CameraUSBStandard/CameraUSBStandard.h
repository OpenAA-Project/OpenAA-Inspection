/*
 * Copyright (C) 2025
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

#ifndef CAMERAUSBSTANDARD_H
#define CAMERAUSBSTANDARD_H

#include "camerausbstandard_global.h"
#include "XTypeDef.h"
#include <QIODevice>
#include <QStringList>
#include "XGUIPacketForDLL.h"
//#include "jpeglib.h"
//#include "turbojpeg.h"
#include "XMainSchemeMemory.h"
#include "XServiceForLayers.h"
#include "XCamUSBCommon.h"
#include "XCameraCommon.h"

class	LayersBase;
class	PropertyItem;
class	PropertyItemPowerlineFrequency;

class CameraUSBStandardAnyData : public CameraReqInfoAnyData
{
public:
	bool	ReallocFirst;

	CameraUSBStandardAnyData(void){	ReallocFirst=false;	}
};

class	CmdReqResolutionList : public GUIDirectMessage
{
public:
	int		ProductID;
	int		CurrentIndex;
	QStringList	List;
	int		CurrentXLen,CurrentYLen;

	CmdReqResolutionList(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdSetResolutionList : public GUIDirectMessage
{
public:
	int		CurrentIndex;

	CmdSetResolutionList(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetImageAttr : public GUIDirectMessage
{
public:
	bool	MirrorX;
	bool	MirrorY;
	int		RotationAngle;
	bool	MonoChrome;

	CmdSetImageAttr(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdReqImageAttr : public GUIDirectMessage
{
public:
	bool	MirrorX;
	bool	MirrorY;
	int		RotationAngle;
	bool	MonoChrome;

	CmdReqImageAttr(LayersBase *base);
};

inline	CmdReqImageAttr::CmdReqImageAttr(LayersBase *base)
	:GUIDirectMessage(base)
{
	MirrorX	=false;
	MirrorY	=false;
	RotationAngle	=0;
	MonoChrome	=false;
}

class	CmdReqCurrentSize : public GUIDirectMessage
{
public:
	int		Index;
	int32	RetCamViewSizeX;
	int32	RetCamViewSizeY;
	int32	RetCamViewSizeBit;
	int32	RetCamViewFPS;

	CmdReqCurrentSize(LayersBase *base);
};

inline	CmdReqCurrentSize::CmdReqCurrentSize(LayersBase *base)
	:GUIDirectMessage(base)
{	
	RetCamViewSizeX		=0;
	RetCamViewSizeY		=0;
	RetCamViewSizeBit	=0;
	RetCamViewFPS		=0;
	Index				=0;
}

class	CmdSetProperty : public GUIDirectMessage
{
public:
	PropertyItem	*Item;
	PropertyItemPowerlineFrequency	*PowerlineFrequencyItem;

	CmdSetProperty(LayersBase *base):GUIDirectMessage(base){	Item=NULL;	PowerlineFrequencyItem=NULL;	}
};

class	CmdSetPropertyAll : public GUIDirectMessage
{
public:
	CmdSetPropertyAll(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdReqProperty : public GUIDirectMessage
{
public:
	CAPTURE_PROPETIES	Prop;
	PropertyItem	*Item;
	PropertyItemPowerlineFrequency	*PowerlineFrequencyItem;

	CmdReqProperty(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdResetCameraProperty: public GUIDirectMessage
{
public:
	CmdResetCameraProperty(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdGetAverageSpanTime: public GUIDirectMessage
{
public:
	double	SpanTime;
	CmdGetAverageSpanTime(LayersBase *base):GUIDirectMessage(base){}
};

struct	StructUSBCamInfo
{
	int32	CamViewSizeX;
	int32	CamViewSizeY;
	int32	CamViewFPS;
};

class	CmdReqStructUSBCamInfoList: public GUIDirectMessage
{
public:
	StructUSBCamInfo	Dim[100];
	int					StructUSBCamInfoCount;	

	CmdReqStructUSBCamInfoList(LayersBase *base):GUIDirectMessage(base){	StructUSBCamInfoCount=0;	}
};

class CameraInfoDetail : public CameraInfoDetailBase
{
public:
	DWORD	ErrorCode;

	CameraInfoDetail()	{	ErrorCode=0;	}
	~CameraInfoDetail()	{}

	virtual	const QString	GetCameraMessage(void){	return QString::number(ErrorCode,16);	}

};

#endif // CAMERAUSBSTANDARD_H