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

#ifndef BUTTONARRANGEPAGE_H
#define BUTTONARRANGEPAGE_H

#include "buttonarrangepage_global.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	SignalOperandBit;

class	ButtonArrangePage : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	ArrangeMethod;

	ButtonArrangePage(LayersBase *Base ,QWidget *parent);
	~ButtonArrangePage(void);
	
	virtual void	Prepare(void)	override;

private:

private slots:
	void	SlotClicked();
	void	ResizeAction();
};

class	GUICmdReqArrangePage : public GUICmdPacketBase
{
public:
	QString	ArrangeMethod;

	GUICmdReqArrangePage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONARRANGEPAGE_H