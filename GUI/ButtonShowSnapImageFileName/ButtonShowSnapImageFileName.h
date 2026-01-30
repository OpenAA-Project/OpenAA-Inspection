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

#ifndef BUTTONSHOWSNAPIMAGEFILENAME_H
#define BUTTONSHOWSNAPIMAGEFILENAME_H

#include "buttonshowsnapimagefilename_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XYCross.h"
#include <QLineEdit>
#include <QColor>
#include <QFont>

class	ButtonShowSnapImageFileName : public GUIFormBase
{
	Q_OBJECT

	QLineEdit	Label;
public:
	QColor	CharColor;
	QFont	CFont;

	ButtonShowSnapImageFileName(LayersBase *Base ,QWidget *parent);
	~ButtonShowSnapImageFileName(void);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)override;

private slots:

	void	ResizeAction();
};


class	CmdShowSnapImageFileName : public GUIDirectMessage
{
public:
	QString	FileName;

	CmdShowSnapImageFileName(LayersBase *base):GUIDirectMessage(base){}
	CmdShowSnapImageFileName(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif // BUTTONSHOWSNAPIMAGEFILENAME_H