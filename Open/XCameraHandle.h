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

#if	!defined(XCameraHandle_h)
#define	XCameraHandle_h

#include <QObject>
#include"XServiceForLayers.h"
#include "XTypeDef.h"
#include <QIODevice>
#include "XParamGlobal.h"
#include "XCameraCommon.h"

class	ExecuteInitialAfterEditInfo;

class	CameraHandle : public QObject
					  ,public ServiceForLayers
					  ,public IdentifiedClass
{
	Q_OBJECT

	int32		CamNo;

public:
	CameraHandle(int _CamNo ,LayersBase *base);

	virtual void	InitialPrepare(void){}
	virtual void	Prepare(void)		{}
	virtual void	AfterPrepare(void)	{}
	virtual void	ReadyParam(void)	{}
	virtual void	AfterStartSequence(void){}

	virtual	bool	MakeExecuteInitialAfterEditInfo	(int ExeID ,ExecuteInitialAfterEditInfo &EInfo)	{	return true;	}

	virtual	bool	Save(QIODevice *f)	{		return true;	}
	virtual	bool	Load(QIODevice *f)	{		return true;	}
	virtual	bool	GetCurrentInfo(CameraReqInfo &RetInfo)	{	return false;	}

	int		GetCamNo(void)	{	return CamNo;	}
	void	SetCamNo(int n)	{	CamNo=n;		}

	int		GetDotPerLine(void);
	int		GetMaxLines(void);
	virtual	bool	IsAlive(void)	{	return true;	}

	virtual	bool	SetTriggerMode(bool b)	{	return true;	}
	virtual	bool	GetTriggerMode(void)	{	return true;	}

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)					{	return true;	}
	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)	{	return true;	}
	virtual	bool	ReallocateMasterCount(int CountMaster)								{	return true;	}
	virtual	bool	InsertPage(int IndexPage)	{	return true;	}
	virtual	bool	RemovePage(int IndexPage)	{	return true;	}

	virtual	void	EmitSignalCaptured(void);
signals:
	void	CameraHandleSignalCaptured();
};

#endif