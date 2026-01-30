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

#include "buttonalignmentoffset_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	SetAlignmentOffsetForm;

class	ButtonAlignmentOffset : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	SetAlignmentOffsetForm	*Window;

	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	MaxOffsetXDot;
	int32	MaxOffsetYDot;

	ButtonAlignmentOffset(LayersBase *Base ,QWidget *parent);
	~ButtonAlignmentOffset(void);
	virtual void	Prepare(void)	override;

private:

private slots:
	void	SlotClicked();
	void	ResizeAction();
};
//---------------------------------------------------------------------------------------------

class	GUICmdReqAlignmentOffset : public GUICmdPacketBase
{
public:
	GUICmdReqAlignmentOffset(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckAlignmentOffset : public GUICmdPacketBase
{
public:
	int		OffsetX;
	int		OffsetY;

	GUICmdAckAlignmentOffset(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};
class	GUICmdSetAlignmentOffset : public GUICmdPacketBase
{
public:
	int		OffsetX;
	int		OffsetY;

	GUICmdSetAlignmentOffset(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};