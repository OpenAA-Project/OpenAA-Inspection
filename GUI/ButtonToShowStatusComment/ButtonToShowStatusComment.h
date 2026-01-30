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

#ifndef BUTTONTOSHOWSTATUSCOMMENT_H
#define BUTTONTOSHOWSTATUSCOMMENT_H

#include "buttontoshowstatuscomment_global.h"
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

class	ButtonToShowStatusComment : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;
	QProcess	*Process;
	QIcon		ButtonIcon;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	ExecStatusComment;
	bool	InitialPushed;

	ButtonToShowStatusComment(LayersBase *Base ,QWidget *parent);
	~ButtonToShowStatusComment(void);
	virtual void	ReadyParam(void)							override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	void	GetMenuInfo(MenuInfoContainer &Info)		override;
	virtual	void	ExecuteMenu(int ID)							override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	CmdSetStatusComment : public GUIDirectMessage
{
public:
	bool		ON;

	CmdSetStatusComment(LayersBase *base):GUIDirectMessage(base){}
	CmdSetStatusComment(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif // BUTTONTOSHOWSTATUSCOMMENT_H