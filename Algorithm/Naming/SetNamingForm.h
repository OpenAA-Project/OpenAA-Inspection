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

#ifndef SETNAMINGFORM_H
#define SETNAMINGFORM_H

#include <QWidget>
#include "ui_SetNamingForm.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

class SetNamingForm : public QWidget,public ServiceForLayers
{
	Q_OBJECT

public:
	SetNamingForm(ShowAndSetItemsBaseClass *Something ,LayersBase *Base,QWidget *parent = 0);
	~SetNamingForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private:
	Ui::SetNamingFormClass ui;

	AlgorithmItemIndependentPack	*IData;
	QString		AreaName;

private slots:
	void on_pushButtonOK_clicked();
};

#endif // SETNAMINGFORM_H