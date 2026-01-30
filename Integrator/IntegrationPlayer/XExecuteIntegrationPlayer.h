/*
 * Copyright (C) 2022
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



#ifndef XExecuteIntegrationPlayerH
#define XExecuteIntegrationPlayerH

#include <QThread>
#include <QReadWriteLock>
#include "XExecuteInspectBase.h"
#include "XCameraClass.h"

class	GUIFormBase;
class	IntegrationPlayer;


class ExecuteIntegrationPlayer : public ExecuteInspectBase
{
	Q_OBJECT
		char	*DefaultCameraFileName;

	PageAndLayerFlagListContainer	CurrentCapturedPageLayer;
	QMutex				ChangingCameraInfo;

	ExecuteInspectState		CurrentState;
	IntegrationPlayer			*Parent;

public:
	ExecuteIntegrationPlayer(IntegrationPlayer *p, EntryPointBase *_EntryPoint);
	~ExecuteIntegrationPlayer(void);

	virtual	void	Initial(void);
	virtual	void	Release(void);

	virtual	ExecuteInspectState	GetState(void)	override{	return CurrentState;	}
	virtual	MotionMode			GetMode(void)	override{	return _CaptureInspect;	}

	virtual	bool	IsLocalCamera(void)		override	{	return true;	}
	virtual	bool	LoadDefault(void)		override	{	return true;	}
	virtual	bool	SaveDefault(void)		override	{	return true;	}
	virtual	bool	Load(QIODevice *file)	override	{	return true;	}
	virtual	bool	Save(QIODevice *file)	override	{	return true;	}
	virtual	CameraClass		*GetCamera(int n)	override{	return NULL;	}
	virtual	void	CamShowSetting(int CamNo)	override{}
	virtual	bool	LoadCameraSetting(const QString &CamFileName)override{	return NULL;	}

	void	SetScanInfo(int ScanNumber ,bool ScanMastered);

	static	ExecuteIntegrationPlayer	*StaticInstance;

protected:
	virtual	void run()	override;

	QReadWriteLock			MutexStateMode;


	virtual	void	GoInspect(void)					override{}
	virtual	void	GoInspectWithoutCapture(void)	override{}
	virtual	void	GoMasterCaptureOnly(void)		override{}
	virtual	void	GoTargetCaptureOnly(void)		override{}
	virtual	void	GoGray(void)					override{}
private:

signals:

private slots:

public slots:
	void	Exit(GUIFormBase *);
};

#endif