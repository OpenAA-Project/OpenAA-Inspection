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

#ifndef INTEGRATIONCLEARNGTHUMBNAIL_H
#define INTEGRATIONCLEARNGTHUMBNAIL_H

#include "integrationclearngthumbnail_global.h"
#include "XGUIFormBase.h"
#include <QTranslator>
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"

class	IntegrationClearNGThumbnail: public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	NormalColor;
	QColor	PushedColor;
	QFont	CFont;

	IntegrationClearNGThumbnail(LayersBase *Base ,QWidget *parent);

	virtual	void	Prepare(void)	override;
private:

private slots:
	void	SlotClicked();
	void	ResizeAction();
};

#endif // INTEGRATIONCLEARNGTHUMBNAIL_H