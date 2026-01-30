/*
 * Copyright (C) 2023
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


#ifndef STARTINSPECTIONBUTTON_H
#define STARTINSPECTIONBUTTON_H

#include "startinspectionbutton_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
//#include "mtImageToolButtonColored.h"
#include "mtImageButtonColored.h"
#include "XGUIFormBase.h"

class	StartInspectionButton : public GUIFormBase
{
	Q_OBJECT

//	mtImageToolButtonColored	Button;
	mtImageButtonColored	Button;
	bool	Started;
public:
	QColor	PushedColor;
	bool	IsNecessaryLot;

	StartInspectionButton(LayersBase *Base ,QWidget *parent);
	~StartInspectionButton(void);
	
	virtual void	Prepare(void)						override;
	virtual	void keyPressEvent ( QKeyEvent * event )	override;
protected:
	virtual	bool OnIdle(void)	override;
public slots:
//	void SlotClicked (bool checked);
	void SlotClicked ();
private slots:
	void	ResizeAction();
};

//==============================================================
class	GUICmdStartInspect : public GUICmdPacketBase
{
public:
	XDateTime	StartInspectionTime;
	int64		CurrentInspectID;
	int32		Layer;
	int32		StrategicNumber;

	GUICmdStartInspect(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
	~GUICmdStartInspect(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplyInspect : public GUICmdPacketBase
{
public:

	GUICmdReplyInspect(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
	~GUICmdReplyInspect(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};



#endif // STARTINSPECTIONBUTTON_H