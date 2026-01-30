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

#ifndef SETMechanicalOFFSETFORM_H
#define SETMechanicalOFFSETFORM_H

#include "XGUIFormBase.h"

namespace Ui {
    class SetMechanicalOffsetForm;
}

class	SignalOperandInt;

class SetMechanicalOffsetForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit SetMechanicalOffsetForm(LayersBase *Base,QWidget *parent = 0);
    ~SetMechanicalOffsetForm();

	int		MechanicalOffset;
	SignalOperandInt	*ioMechanicalOffset;

	virtual	void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;

private slots:
    void on_pushButtonSet_clicked();
	void	OperandChanged();

private:
    Ui::SetMechanicalOffsetForm *ui;
};

#endif // SETMechanicalOFFSETFORM_H