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

#ifndef GENERALPANELFROMSEQ_H
#define GENERALPANELFROMSEQ_H

#include "generalpanelfromseq_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"
#include <QLabel>
#include <QColor>
#include <QTranslator>
#include <QString>
#include <QFont>
#include "XGUIFormBase.h"

class	SignalOperandString;

class	GeneralPanelFromSeq : public GUIFormBase
{
	Q_OBJECT

	QLabel	Label;
	QColor	PanelColor;
public:
	QTranslator Translator;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	AlignAttr;

	enum	CAlignment{
		AlignLeft
		,AlignCenter
	};
	SignalOperandString	*iMessageStr;
	SignalOperandString	*iColorStr;

	GeneralPanelFromSeq(LayersBase *Base ,QWidget *parent);
	~GeneralPanelFromSeq(void);

	virtual void	Prepare(void)	override;

protected:
	virtual	void	paintEvent ( QPaintEvent * event )	override;

private slots:
	void	ResizeAction();
	void	OperandChanged();
	void	OperandColorChanged();
};

#endif // GENERALPANELFROMSEQ_H