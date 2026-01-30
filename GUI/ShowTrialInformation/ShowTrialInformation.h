/*
 * Copyright (C) 2024
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

#pragma once

#include "showtrialinformation_global.h"
#include <QLabel>
#include <QColor>
#include <QFont>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ThreadCheckTrial;

class	ShowTrialInformation : public GUIFormBase
{
	Q_OBJECT

	int					IdleCount;
	ThreadCheckTrial	*CheckInThread;
	QString				LastMsg;
public:
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ShowTrialInformation(LayersBase *Base ,QWidget *parent);
	virtual	~ShowTrialInformation(void);

	virtual void	Prepare(void)	override;

	void	ShowMessage(void);

	virtual	bool OnIdle(void)	override;
};

class ThreadCheckTrial : public QThread
{
	ShowTrialInformation	*Parent;
public:
	volatile	int		CheckedCount;
	volatile	bool	Terminated;
	volatile	bool	PassedByHasp;
	volatile	bool	Passed;

	ThreadCheckTrial(ShowTrialInformation *p,QObject *parent);

	
private:
	virtual	void run()	override;
};
