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


#ifndef INPUTALIGNMENTGROUPFORM_H
#define INPUTALIGNMENTGROUPFORM_H

#include <QDialog>
#include "ui_InputAlignmentGroupForm.h"
#include "XServiceForLayers.h"

class InputAlignmentGroupForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	InputAlignmentGroupForm(LayersBase *Base,QWidget *parent);
	~InputAlignmentGroupForm();
	
	int	Group;
private:
	Ui::InputAlignmentGroupFormClass ui;

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
};

#endif // INPUTALIGNMENTGROUPFORM_H