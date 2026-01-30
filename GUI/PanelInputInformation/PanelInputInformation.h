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

#ifndef PANELINPUTINFORMATION_H
#define PANELINPUTINFORMATION_H

#include "panelinputinformation_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"
#include <QLabel>
#include <QToolButton>
#include <QLineEdit>
#include <QString>
#include <QStringList>
#include <QColor>
#include <QFont>

class PanelInputInformation: public GUIFormBase
{
	Q_OBJECT

	struct	InformationItem
	{
		QLabel		ItemLabel;
		QLineEdit	Edit;
	};
	struct	InformationItem	*ItemControls;
	int		CountOfItemControls;
public:
	QFont	InputFont;
	QFont	TitleFont;
	QColor	TitleColor;
	QColor	InputColor;
	int		ItemHeight;
	int		TitleWidth;
	QStringList	ItemTitles;

	PanelInputInformation(LayersBase *Base ,QWidget *parent);
	~PanelInputInformation(void);

	virtual void	Prepare(void)		override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
	void		ReflectToWindow(QStringList &Str);
	QStringList	GetListFromWindow(void);

private slots:
	void	ResizeAction();
};

class CmdReqInputInformationPacket : public GUIDirectMessage
{
public:
	QStringList	Titles;
	QStringList	Datas;

	CmdReqInputInformationPacket(LayersBase *base):GUIDirectMessage(base){}
};
#endif // PANELINPUTINFORMATION_H