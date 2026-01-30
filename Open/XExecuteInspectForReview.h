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

#if	!defined(_XExecuteInspectForReview)
#define	_XExecuteInspectForReview

#include "XExecuteInspectBase.h"

class ExecuteInspectForReview : public ExecuteInspectBase
{

public:
	ExecuteInspectForReview(QObject *parent ,EntryPointBase *_EntryPointBaseData ,SeqLocalParam *_SeqParam)
		:ExecuteInspectBase(parent,_EntryPointBaseData ,_SeqParam){}
	virtual	~ExecuteInspectForReview(void){}

	virtual	bool	IsLocalCamera(void)			{	return false;	}
	virtual	ExecuteInspectBase::ExecuteInspectState	GetState(void)	{	return ExecuteInspectBase::_EI_IDLE;	}
	virtual	ExecuteInspectBase::MotionMode			GetMode(void)	{	return ExecuteInspectBase::_CaptureNone;	}
	virtual	bool	Load(QIODevice *f)	{	return true;		}
	virtual	bool	Save(QIODevice *f)	{	return true;		}
	virtual	bool	LoadDefault(void)	{	return true;		}
	virtual	bool	SaveDefault(void)	{	return true;		}
	
	virtual	CameraClass		*GetCamera(int n)	{	return NULL;	}

	//�������͊O�������̑���
	virtual	void	GoInspect(void)				{}
	virtual	void	GoInspectWithoutCapture(void){}
	virtual	void	GoMasterCaptureOnly(void)	{}
	virtual	void	GoTargetCaptureOnly(void)	{}
	virtual	void	GoGray(void)				{}
	virtual	void	CamShowSetting(int CamNo)	{}
	virtual	bool	LoadCameraSetting(const QString &CamFileName)	{	return true;	}

	
protected:
};



#endif