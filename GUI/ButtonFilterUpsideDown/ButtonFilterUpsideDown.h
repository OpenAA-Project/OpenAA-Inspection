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

#ifndef BUTTONFILTERUPSIDEDOWN_H
#define BUTTONFILTERUPSIDEDOWN_H

#include "buttonfilterupsidedown_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	SignalOperandBit;

class	ButtonFilterUpsideDown : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	DefaultPushed;
	int32	SystemRegisterNo;

	ButtonFilterUpsideDown(LayersBase *Base ,QWidget *parent);
	~ButtonFilterUpsideDown(void);
	
	virtual void	Prepare(void)	override;

private:
	SignalOperandBit	*ioMode;
private slots:
	void	SlotClicked();
	void	ResizeAction();
	void	OperandChanged();
};

class	GUICmdFilterUpsideDown : public GUICmdPacketBase
{
public:

	GUICmdFilterUpsideDown(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdFilterClearUpsideDown : public GUICmdPacketBase
{
public:

	GUICmdFilterClearUpsideDown(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif // BUTTONFILTERUPSIDEDOWN_H