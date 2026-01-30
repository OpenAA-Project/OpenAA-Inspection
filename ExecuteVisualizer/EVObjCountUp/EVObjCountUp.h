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

#ifndef EVOBJCOUNTUP_H
#define EVOBJCOUNTUP_H

#include "evobjcountup_global.h"
#include "XExecuteVisualizer.h"

class	CountUpOutput : public RunnerConnectorOut
{
public:
	CountUpOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Output");		}

	virtual	int		GetOutputInt(void);
};

class	CountUpInput : public RunnerConnectorIn
{
public:
	CountUpInput(RunnerObject *parent) : RunnerConnectorIn(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Input");		}

	virtual	void	SetInputInt(int d);
};

class	RunnerCountUp : public RunnerObject
{
public:
	int	Value;

	RunnerCountUp(LayersBase *Base ,RunnerMap *rmap);
	~RunnerCountUp(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;

	int		GetValue(void)	{	return Value;	}
protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

#endif // EVOBJCOUNTUP_H