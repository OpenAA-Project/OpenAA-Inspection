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


#ifndef SHOWTHRESHOLDFILENAMEFORM_H
#define SHOWTHRESHOLDFILENAMEFORM_H

#include "XGUIFormBase.h"
#include "ui_ShowThresholdFileNameForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ShowThresholdFileNameForm : public GUIFormBase
{
	Q_OBJECT

public:
	bool	ShowThresholdFile;
	QString	TitleThresholdFile;
	bool	ShowHeadThresholdFile;

	QString	AlignAttr;
	QColor	CharColor;
	QColor	BackColor;
	bool	TransparentBackColor;
	QColor	BorderColor;
	int		BorderWidth;
	QString	BorderStyle;
	QFont	CFont;

	QString	HeadAlignAttr;
	QColor	HeadCharColor;
	QColor	HeadBackColor;
	bool	HeadTransparentBackColor;
	QColor	HeadBorderColor;
	int		HeadBorderWidth;
	QString	HeadBorderStyle;
	QFont	HeadCFont;

	int		HeadWidth;

	ShowThresholdFileNameForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowThresholdFileNameForm();

	virtual void	Prepare(void)	override;
	virtual void	BuildForShow(void)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	Ui::Form ui;
private slots:
	void	ResizeAction();
};

#endif // SHOWTHRESHOLDFILENAMEFORM_H