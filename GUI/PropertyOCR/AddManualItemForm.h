/*
 * Copyright (C) 2026
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

#ifndef ADDMANUALITEMFORM_H
#define ADDMANUALITEMFORM_H

#include <QDialog>
#include "ui_AddManualItemForm.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XDataInLayer.h"
#include "XServiceForLayers.h"

class AddManualItemForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	AddManualItemForm(LayersBase *Base, QWidget *parent);
	~AddManualItemForm();

	void	Initial(void);

	int			Mergin;


private:
	Ui::AddManualItemFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
	void on_pushButtonSetMergin_clicked();
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonAddColor_clicked();
	void	SlotColorSampleBeforeSave();
	void	SlotColorSampleSelectOne();
};

#endif // ADDMANUALITEMFORM_H