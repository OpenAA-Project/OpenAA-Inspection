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

#ifndef CHECKCYCLETIMEFORM_H
#define CHECKCYCLETIMEFORM_H

#include <QDialog>
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class CheckCycleTimeForm;
}
class	SignalOperandBit;

class	CycleTimeList : public NPList<CycleTimeList>
{
	DWORD	CycleTime;
public:
	CycleTimeList(DWORD d)	{	CycleTime=d;	}

	int	GetCycleTime(void)	{	return CycleTime;	}
};

class	CycleTimeContainer : public NPListPack<CycleTimeList>
{
public:
	CycleTimeContainer(void){}

	void	AddCycleTime(DWORD d);
	bool	IsAverageTimeAvailable(void);
	DWORD	GetAverageCycleTime(void);
};


class CheckCycleTimeForm : public GUIFormBase
{
    Q_OBJECT
    
	CycleTimeContainer	CTime;
	DWORD				LastTime;
public:
	SignalOperandBit	*iCycleDone;
	SignalOperandBit	*iError;

    explicit CheckCycleTimeForm(LayersBase *Base ,QWidget *parent = 0);
    ~CheckCycleTimeForm();
    
    virtual	void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;

private slots:
    void on_pushButtonSet_clicked();
	void	OperandChanged();
	void	OperandClearChanged();
private:
    Ui::CheckCycleTimeForm *ui;
};

#endif // CHECKCYCLETIMEFORM_H