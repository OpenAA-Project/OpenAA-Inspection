/*
 * Copyright (C) 2025
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

#include "setalignmentlargeheadline_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	AlignmentLargeBase;

class	SetAlignmentLargeHeadLine : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	SetAlignmentLargeHeadLine(LayersBase *Base ,QWidget *parent);
	~SetAlignmentLargeHeadLine(void);
	virtual void	Prepare(void)	override;

private:
	AlignmentLargeBase	*GetAlignmentLargeBase(void);
private slots:
	void	SlotClicked();
	void	ResizeAction();
};

class	GUICmdSetAlignmentLargeHeadLine : public GUICmdPacketBase
{
public:
	bool		UseHeadAlignment		;
	int			MaxHeadAlignmentX		;
	int			MaxHeadAlignmentY		;
	int			SkipHeadAlignmentX		;
	int			SkipHeadAlignmentY		;
	int			HeadAlignmentDifColor	;
	int			HeadAlignmentMinSize	;
	int			HeadAlignmentStep		;

	GUICmdSetAlignmentLargeHeadLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};