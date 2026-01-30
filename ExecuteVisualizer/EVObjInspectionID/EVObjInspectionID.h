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

#ifndef EVOBJINSPECTIONID_H
#define EVOBJINSPECTIONID_H

#include "evobjinspectionid_global.h"
#include "XExecuteVisualizer.h"

class	InspectionIDOutput : public RunnerConnectorOut
{
public:
	InspectionIDOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Output");		}
	virtual	int		GetOutputInt(void);
};

class	InspectionIDInput : public RunnerConnectorIn
{
public:
	InspectionIDInput(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Input");		}
	virtual	void	SetInputInt(int d);
};

class	RunnerInspectionID : public RunnerObject
{
public:
	RunnerInspectionID(LayersBase *Base ,RunnerMap *rmap);
	~RunnerInspectionID(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;
protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

#endif // EVOBJINSPECTIONID_H