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

#ifndef EVOBJCHANGEDLOT_H
#define EVOBJCHANGEDLOT_H

#include "evobjchangedlot_global.h"
#include "XExecuteVisualizer.h"
#include "XTypeDef.h"

class	ChangedLotOutput : public RunnerConnectorOut
{
public:
	ChangedLotOutput(RunnerObject *parent) : RunnerConnectorOut(parent){}

	virtual	TypeOfRunnerConnector	GetType(void)	{	return __ValueBool;				}
	virtual	QString					GetName(void)	{	return QString("LotChanged");		}
	virtual	bool	GetOutputBool(void);
};

#define	ChangedLotMode_On	1
#define	ChangedLotMode_Off	2

class	RunnerChangedLot : public RunnerObject
{
	QImage		*ImageModeOn[6];
	QImage		*ImageModeOff[6];
	int			ShowingNumber;
	int32		LastLotAutoCount;
	DWORD		LastTimeToChange;
public:
	RunnerChangedLot(LayersBase *Base ,RunnerMap *rmap);
	~RunnerChangedLot(void);

	virtual	int		EnumStates(struct RunnerState pState[1000])	override;
	virtual	void	IntervalExecute(void)						override;
protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};
#endif // EVOBJCHANGEDLOT_H