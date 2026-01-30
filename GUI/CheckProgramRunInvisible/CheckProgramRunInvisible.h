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

#ifndef CHECKPROGRAMRUNINVISIBLE_H
#define CHECKPROGRAMRUNINVISIBLE_H

#include "checkprogramruninvisible_global.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"
#include "XMessagerClient.h"

class	ThreadCheckProgramRun : public QThread,public ServiceForLayers
{
	Q_OBJECT

	bool	StopRunning;
public:
	bool	FinMode;

	ThreadCheckProgramRun(LayersBase *Base ,QObject * parent):QThread(parent),ServiceForLayers(Base){	StopRunning=false;	FinMode=false;	}

	virtual void run ();
signals:
	void	MessageOutFunc(void);
};


class	CheckProgramRunInvisible : public GUIFormBase
{
	Q_OBJECT

	ThreadCheckProgramRun	ThreadCheckProgramRunInst;
public:
	QString	ProcessName;
	bool	BlockExecute;
	QString	MessageerIPAddress;
	bool	MessageOut;
	bool	NowOnMessageOut;
	MessagerClient	MClient;

	CheckProgramRunInvisible(LayersBase *Base ,QWidget *parent);
	~CheckProgramRunInvisible(void);

	virtual	void	Prepare(void)	override;

private slots:
	void	SlotMessageOutFunc(void);
};

#endif // CHECKPROGRAMRUNINVISIBLE_H