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

#ifndef DISPLAYPOINTINGFORM_H
#define DISPLAYPOINTINGFORM_H

#include "ui_DisplayPointingForm.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class DisplayPointingForm : public GUIFormBase
{
	Q_OBJECT

public:
	QString	RelatedPanel;

	DisplayPointingForm(LayersBase *Base,QWidget *parent = 0);
	~DisplayPointingForm();

private:
	Ui::DisplayPointingFormClass ui;

	virtual	void	Prepare(void)	override;
	virtual	void	showEvent ( QShowEvent * event ) override;
signals:
	void	SignalDrawFromOutside(QStringList &data);

private slots:
	void	SlotDrawMessage(const QStringList &title ,const QStringList &msg);
	void	ResizeAction();

};

#endif // DISPLAYPOINTINGFORM_H