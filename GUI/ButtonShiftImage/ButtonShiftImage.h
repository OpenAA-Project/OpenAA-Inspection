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

#pragma once

#include "buttonshiftimage_global.h"
#include <QPushButton>
#include <QTranslator>
#include <QProcess>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XYCross.h"
#include <QToolButton>
#include <QIODevice>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonShiftImage : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonShiftImage(LayersBase *Base ,QWidget *parent);
	~ButtonShiftImage(void);

	virtual	void	Prepare(void)	override;

	void	ExeShiftY(bool ModeMasterImage,bool ModeTargetImage,int X1,int X2,int ShiftY);
	void	ExeShiftX(bool ModeMasterImage,bool ModeTargetImage,int Y1,int Y2,int ShiftX);
private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};
//==================================================================================

class	GUICmdReqShiftImage : public GUICmdPacketBase
{
public:
	bool	ModeY;
    bool    ModeMasterImage;
    bool    ModeTargetImage;
	int		StartPos,EndPos;
	int		ShiftN;

	GUICmdReqShiftImage(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	Shift(DataInLayer *Lp ,ImageBuffer *P);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};