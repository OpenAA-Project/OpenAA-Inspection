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

#ifndef BUTTONFORMARKINGONFORM_H
#define BUTTONFORMARKINGONFORM_H

#include <QDialog>
#include "XGUIFormBase.h"

namespace Ui {
    class ButtonForMarkingOnForm;
}
class	SignalOperandInt;

class ButtonForMarkingOnForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit ButtonForMarkingOnForm(LayersBase *base ,QWidget *parent = 0);
    ~ButtonForMarkingOnForm();

	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	virtual void	Prepare(void)	override;

	SignalOperandInt	*ioMarkingON;

private slots:
        void on_toolButton_clicked();
		void	ResizeAction();
		void	OperandChanged();
private:
    Ui::ButtonForMarkingOnForm *ui;
};

#endif // BUTTONFORMARKINGONFORM_H