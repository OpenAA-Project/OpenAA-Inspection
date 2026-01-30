/*
 * Copyright (C) 2012
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

#ifndef LOADOUTLINEOFFSETFORM_H
#define LOADOUTLINEOFFSETFORM_H

#include <QDialog>
#include "ui_LoadOutlineOffsetForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"

class LoadOutlineOffsetForm : public QDialog
{
	Q_OBJECT

public:
	LoadOutlineOffsetForm(LayersBase *Base,QWidget *parent = 0);
	~LoadOutlineOffsetForm();

private:
	Ui::LoadOutlineOffsetFormClass ui;

	LayersBase *LBase;
	QStringList MFieldNames;

private slots:
	void on_pbCancel_clicked();
	void on_pbOK_clicked();
};

#endif // LOADOUTLINEOFFSETFORM_H