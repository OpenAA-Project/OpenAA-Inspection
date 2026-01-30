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


#ifndef INPUTALIGNMENTAREAFORM_H
#define INPUTALIGNMENTAREAFORM_H

#include <QDialog>
#include "ui_InputAlignmentAreaForm.h"
#include "XAlgorithmLibrary.h"
#include "SelectLibrariesForAnyType.h"
#include "XServiceForLayers.h"
#include "XAlignmentLarge.h"
#include "PropertyAlignmentLargePacket.h"

class InputAlignmentAreaForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	InputAlignmentAreaForm(bool ModifyMode ,LayersBase *base ,QString areaName ,QWidget *parent);
	~InputAlignmentAreaForm();

	QString	AreaName;
	SelectLibrariesForAnyType		Libs;
	XAlignmentLargeArea::_EnumPriority	Priority;
	bool	DeleteMode;
	void	Reflect(AlignmentLargeAreaList *a);
	void	Reflect(void);
private:
	Ui::InputAlignmentAreaFormClass ui;

private slots:
	void on_ButtonDelete_clicked();
	void on_ButtonOK_clicked();
	void on_ButtonCancel_clicked();
};

#endif // INPUTALIGNMENTAREAFORM_H