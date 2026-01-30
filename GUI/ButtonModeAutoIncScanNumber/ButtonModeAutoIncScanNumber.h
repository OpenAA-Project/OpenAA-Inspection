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

#ifndef BUTTONMODEAUTOINCSCANNUMBER_H
#define BUTTONMODEAUTOINCSCANNUMBER_H

#include "buttonmodeautoincscannumber_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QStringList>
#include <QString>
#include <QColor>
#include <QFont>
#include <QIODevice>

class	ButtonModeAutoIncScanNumber : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonModeAutoIncScanNumber(LayersBase *Base ,QWidget *parent);
	~ButtonModeAutoIncScanNumber(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

//-------------------------------------------------------
class	GUICmdSetModeAutoIncScanNumber: public GUICmdPacketBase
{
public:
	bool	ModeAutoIncScanNumber;

	GUICmdSetModeAutoIncScanNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};


#endif // BUTTONMODEAUTOINCSCANNUMBER_H