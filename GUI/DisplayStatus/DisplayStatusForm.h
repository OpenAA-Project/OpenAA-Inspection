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

#ifndef DISPLAYSTATUSFORM_H
#define DISPLAYSTATUSFORM_H

#include "XGUIFormBase.h"
#include "ui_DisplayStatusForm.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XStatusController.h"

class DisplayStatusForm : public GUIFormBase
{
	Q_OBJECT

public:
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	DisplayStatusForm(LayersBase *Base ,QWidget *parent = 0);
	~DisplayStatusForm();

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	ShowComment(bool HTMLMode ,const QString &comment);
private:
	Ui::DisplayStatusFormClass ui;
	virtual	void	ResizeByScale(double ScaleX,double ScaleY)	override;
private slots:
	void	SlotShowComment(bool HTMLMode ,const QStringList &comment);
	void	ResizeAction();
};


#endif // DISPLAYSTATUSFORM_H