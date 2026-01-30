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


#ifndef STARTSTATISTICSCANBUTTONFORM_H
#define STARTSTATISTICSCANBUTTONFORM_H

#include "XGUIFormBase.h"
#include "ui_StartStatisticScanButtonForm.h"
#include <QToolButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"
#include "StartStatisticScanBase.h"

class StartStatisticScanButtonForm : public GUIFormBase , public StartStatisticScanBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
public:
	int		Counter;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QColor	NormalColor;
	QColor	PushedColor;
public:
	StartStatisticScanButtonForm(LayersBase *Base ,QWidget *parent = 0);
	~StartStatisticScanButtonForm();

	virtual void	Prepare(void)	override;
	virtual	void	keyPressEvent ( QKeyEvent * event )	override;

private:
	Ui::StartStatisticScanButtonFormClass ui;

protected:
	virtual	bool OnIdle(void)		override;

	virtual	void OnIdleEnd(void)	override;
	virtual	void OnToggled(void)	override;

private slots:
	//void SlotClicked (bool checked);
	void	SlotToggled (bool checked);
	void	ResizeAction();
};
//==============================================================

#endif // STARTSTATISTICSCANBUTTONFORM_H