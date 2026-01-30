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

#ifndef BUTTONSETOFFSETFORM_H
#define BUTTONSETOFFSETFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ButtonSetOffsetForm;
}

class	SignalOperandBit;
class ButtonSetOffsetForm : public GUIFormBase
{
    Q_OBJECT
    
	SignalOperandBit	*iButton;
public:
    explicit ButtonSetOffsetForm(LayersBase *base ,QWidget *parent = 0);
    ~ButtonSetOffsetForm();
    
	virtual void	Prepare(void)	override;
private slots:
    void on_pushButtonSetOffset_clicked();
	void	ResizeAction();
	void	OperandChanged();
private:
    Ui::ButtonSetOffsetForm *ui;
};

#endif // BUTTONSETOFFSETFORM_H