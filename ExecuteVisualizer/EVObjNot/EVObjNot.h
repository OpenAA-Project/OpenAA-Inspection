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

#ifndef EVOBJNOT_H
#define EVOBJNOT_H

#include "evobjnot_global.h"
#include "XExecuteVisualizer.h"

class	NotOutput : public RunnerConnectorOut
{
public:
	NotOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Output");		}

	virtual	bool		GetOutputBool(void);
};

class	NotInput : public RunnerConnectorIn
{
public:
	NotInput(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Input");		}
};

class	EVObjNot : public RunnerObject
{
public:
	bool	Value;

	EVObjNot(LayersBase *Base ,RunnerMap *rmap);
	~EVObjNot(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;

	bool	GetValue(void)	{	return Value;	}

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};
#endif // EVOBJNOT_H