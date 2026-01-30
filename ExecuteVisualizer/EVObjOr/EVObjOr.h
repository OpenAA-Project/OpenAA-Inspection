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

#ifndef EVOBJOR_H
#define EVOBJOR_H

#include "evobjor_global.h"
#include "XExecuteVisualizer.h"

class	OrOutput : public RunnerConnectorOut
{
public:
	OrOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Output");		}

	virtual	bool		GetOutputBool(void);
};

class	OrInput : public RunnerConnectorIn
{
public:
	int	Number;

	OrInput(RunnerObject *parent ,int n) : RunnerConnectorIn(parent),Number(n){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("Input")+QString::number(Number);	}
};

class	EVObjOr : public RunnerObject
{
public:
	int	InputNumb;
	bool	Value;

	EVObjOr(LayersBase *Base ,RunnerMap *rmap);
	~EVObjOr(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;

	void	SetInputConnectors(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	bool		GetValue(void)	{	return Value;	}

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};
#endif // EVOBJOR_H