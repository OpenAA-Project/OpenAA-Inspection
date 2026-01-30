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

#ifndef EVOBJPIOIN_H
#define EVOBJPIOIN_H

#include "evobjpioin_global.h"
#include "XExecuteVisualizer.h"

class	PIOInOutput : public RunnerConnectorOut
{
public:
	PIOInOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("OutBit");		}
	virtual	bool	GetOutputBool(void);
};

class	RunnerPIOIn : public RunnerObject
{
	QImage	*ImageOn[2];
	QImage	*ImageOff[2];
	int		ShowingNumber;
public:
	int		BoardNumber;
	int		Port;
	int		BitNumber;

	RunnerPIOIn(LayersBase *Base ,RunnerMap *rmap);
	~RunnerPIOIn(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override{	return 0;	}
	virtual	void	IntervalExecute(void)						override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	bool	GetPIOData(void);
protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;

};

#endif // EVOBJPIOIN_H