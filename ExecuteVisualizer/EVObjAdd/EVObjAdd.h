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

#ifndef EVOBJADD_H
#define EVOBJADD_H

#include "evobjadd_global.h"
#include "XExecuteVisualizer.h"

class	AddOutput : public RunnerConnectorOut
{
public:
	AddOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Output");		}

	virtual	int		GetOutputInt(void);
};

class	AddInput : public RunnerConnectorIn
{
public:
	int	Number;

	AddInput(RunnerObject *parent ,int n) : RunnerConnectorIn(parent),Number(n){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueInt;				}
	virtual	QString					GetName(void)	{	return QString("Input")+QString::number(Number);	}
};

class	EVObjAdd : public RunnerObject
{
public:
	int	InputNumb;
	int	Value;

	EVObjAdd(LayersBase *Base ,RunnerMap *rmap);
	~EVObjAdd(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;

	void	SetInputConnectors(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	int		GetValue(void)	{	return Value;	}
protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

#endif // EVOBJADD_H