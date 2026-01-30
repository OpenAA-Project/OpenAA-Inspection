/*
 * Copyright (C) 2014
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

#ifndef MOVEALLFORM_H
#define MOVEALLFORM_H

#include <QDialog>
#include "ui_MoveAllForm.h"
#include "XIntClass.h"
#include "XServiceForLayers.h"

class MoveAllForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

	QCheckBox	**CheckedPage;
	int		AllocCheckedPage;
public:
	MoveAllForm(LayersBase *Base,QWidget *parent = 0);
	~MoveAllForm();

	int	MovX;
	int	MovY;
	bool	MoveMasterImage;
	bool	MoveTargetImage;
	IntList	AppliedPages;
	QLabel	FrameCheckBox;
private:
	Ui::MoveAllFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // MOVEALLFORM_H