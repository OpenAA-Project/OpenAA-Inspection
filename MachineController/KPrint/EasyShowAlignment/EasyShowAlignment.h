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

#pragma once

#include "easyshowalignment_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include <QImage>
#include <QString>
#include <QColor>
#include <QFont>
#include <QPushButton>

class EasyShowAlignmentForm;

class EasyShowAlignment: public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	EasyShowAlignmentForm	*Window;
	QImage	PanelImage;
public:
	int32	SlaveNo;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	
	EasyShowAlignment(LayersBase *Base ,QWidget *parent = 0);
	virtual	~EasyShowAlignment();

	virtual	void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	virtual void	ShowInPlayer		(int64 shownInspectionID=-1)	override;
private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};