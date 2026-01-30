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

#if	!defined(XEVObjCamera_H)
#define	XEVObjCamera_H

#include "XExecuteVisualizer.h"

class	CameraOutputCapturedConnector : public RunnerConnectorOut
{
public:
	CameraOutputCapturedConnector(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Captured");		}
	virtual	bool		GetOutputBool(void);
};

class	CameraOutputErrorConnector : public RunnerConnectorOut
{
public:
	CameraOutputErrorConnector(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Error");		}
	virtual	bool		GetOutputBool(void);
};

class	CameraInputStartCaptureConnector : public RunnerConnectorIn
{
public:
	CameraInputStartCaptureConnector(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("StartCapture");	}
	virtual	void	SetInputBool(bool b);
};

class	CameraInputCancelConnector : public RunnerConnectorIn
{
public:
	CameraInputCancelConnector(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Cancel");		}
	virtual	void	SetInputBool(bool b);
};

#define	StateCamera_Nothing				1
#define	StateCamera_Waiting				2
#define	StateCamera_Captured			3
#define	StateCamera_CapturedAndWaiting	4

class	RunnerCamera : public RunnerObject
{
	QImage	*Nothing[6];
	QImage	*Waiting[1];
	QImage	*Captured[4];
	QImage	*CapturedAndWaiting[4];
	int		ShowingNumber;
	bool	ErrorOccured;
public:
	bool	StartCaptureMode;

	RunnerCamera(LayersBase *Base ,RunnerMap *rmap);
	~RunnerCamera(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override;
	virtual	void	IntervalExecute(void)						override;

	bool			DoesErrorOccured(void);
	void			StartCapture(void);
	void			CancelCapture(void);

private:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

#endif