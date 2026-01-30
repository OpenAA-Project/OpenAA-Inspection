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

#ifndef BUTTONLEARNINGSAVEMODEFORM_H
#define BUTTONLEARNINGSAVEMODEFORM_H

#include "XGUIFormBase.h"
#include "ui_ButtonLearningSaveModeForm.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class ButtonLearningSaveModeForm : public GUIFormBase
{
	Q_OBJECT

public:
	QString	Msg;
	QFont	CFont;

	bool	DefaultPushed;	ButtonLearningSaveModeForm(LayersBase *Base,QWidget *parent = 0);
	~ButtonLearningSaveModeForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
	Ui::ButtonLearningSaveModeFormClass ui;

private slots:
	void on_toolButton_toggled(bool checked);
	void	ResizeAction();
};

//--------------------------------------------------------------------

class	GUICmdReqLearningSaveMode : public GUICmdPacketBase
{
public:

	GUICmdReqLearningSaveMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{		return true;	}
	virtual	bool	Save(QIODevice *f)	{		return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckLearningSaveMode : public GUICmdPacketBase
{
public:
	bool	Mode;

	GUICmdAckLearningSaveMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUISetLearningSaveMode : public GUICmdPacketBase
{
public:
	bool	Mode;

	GUISetLearningSaveMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};




#endif // BUTTONLEARNINGSAVEMODEFORM_H