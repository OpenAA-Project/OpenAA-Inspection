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

#ifndef SELECTCAMERADIALOG_H
#define SELECTCAMERADIALOG_H

#include <QDialog>
#include "ui_SelectCameraDialog.h"
#include <QButtonGroup>
#include "XIntClass.h"
#include "XServiceForLayers.h"

class SelectCameraDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT

	QWidget			ScrollBack;
	QButtonGroup	CamButtons;

public:
	SelectCameraDialog(LayersBase *base ,QWidget *parent);
	~SelectCameraDialog();

	IntList			CamList;
	int	CamNo;

private:
	Ui::SelectCameraDialogClass ui;
private slots:
	void SlotButtonClicked (int Cam);
};

#endif // SELECTCAMERADIALOG_H