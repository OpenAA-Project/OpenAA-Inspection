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

#ifndef PROCESSINGFORM_H
#define PROCESSINGFORM_H

#include <QWidget>
#include "ui_ProcessingForm.h"

class ProcessingForm : public QWidget
{
//	Q_OBJECT

public:
	ProcessingForm(QWidget *parent = 0);
	~ProcessingForm();

	void SetUpdate(int value);

private:
	Ui::ProcessingFormClass ui;
};

#endif // PROCESSINGFORM_H