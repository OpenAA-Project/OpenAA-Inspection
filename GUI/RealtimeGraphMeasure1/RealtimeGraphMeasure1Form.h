/*
 * Copyright (C) 2021
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

#ifndef REALTIMEGRAPHMEASURE1FORM_H
#define REALTIMEGRAPHMEASURE1FORM_H

#include "XGUIFormBase.h"
#include "ui_RealtimeGraphMeasure1Form.h"

class	ThreadFocus;

class RealtimeGraphMeasure1Form : public GUIFormBase
{
	Q_OBJECT

	ThreadFocus		*ThreadDim[3][3];
	GUIFormBase		*PropertyRealtimeGraphPointer;
public:
	volatile	int		CamNo;
	volatile	bool	Calclating;
	QMutex		MutexCalc;

	RealtimeGraphMeasure1Form(LayersBase *Base ,QWidget *parent = 0);
	~RealtimeGraphMeasure1Form();

	virtual void	AfterStartSequence(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	virtual void	ShowInScanning(int64 shownInspectionID=-1)	override;

private:
	Ui::RealtimeGraphMeasure1FormClass ui;

	void	CalcFocus(void);

private slots:
	void	ResizeAction();
};

#endif // REALTIMEGRAPHMEASURE1FORM_H