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

#pragma once

#include "buttonswitchshade_global.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"

class ShadowButton : public QToolButton
{
	Q_OBJECT
public:
	int	Number;

	ShadowButton(int n);
	~ShadowButton();

signals:
	void	SignalClicked(int ButtonNumber);
private slots:
	void SlotClicked (bool checked);
};


class  ButtonSwitchShade: public GUIFormBase
{
	Q_OBJECT

	ShadowButton	**ButtonDim;
	int				AllocatedButtonCount;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonSwitchShade(LayersBase *Base ,QWidget *parent);
	~ButtonSwitchShade(void);

	virtual	void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit	(void)	override;
private slots:
	void SlotClicked (int ButtonNumber);
	void	ResizeAction();

private:
	void	ShowButtons(void);
};

class	GUICmdSetCurrentShadow: public GUICmdPacketBase
{
public:
	int	Shadow;

	GUICmdSetCurrentShadow(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};