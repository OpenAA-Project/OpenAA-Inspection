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

#ifndef EVOBJBUTTONAUTOINSPECTION_H
#define EVOBJBUTTONAUTOINSPECTION_H

#include "evobjbuttonautoinspection_global.h"
#include "XExecuteVisualizer.h"

class	ButtonAutoInspectionOutput : public RunnerConnectorOut
{
public:
	ButtonAutoInspectionOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("AutoMode");		}

	virtual	bool	GetOutputBool(void);
};

#define	AutoMode_On		1
#define	AutoMode_Off	2

class	RunnerButtonAutoInspection : public RunnerObject
{
	QImage	*ImageModeOn[2];
	QImage	*ImageModeOff[2];
	int		ShowingNumber;
public:
	RunnerButtonAutoInspection(LayersBase *Base ,RunnerMap *rmap);
	~RunnerButtonAutoInspection(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override;
	virtual	void	IntervalExecute(void)						override;

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

#endif // EVOBJBUTTONAUTOINSPECTION_H