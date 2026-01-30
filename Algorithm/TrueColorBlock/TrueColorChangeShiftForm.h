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



#ifndef TRUECOLORCHANGESHIFTFORM_H
#define TRUECOLORCHANGESHIFTFORM_H

#include <QWidget>
#include "ui_TrueColorChangeShiftForm.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

class TrueColorChangeShiftForm : public QWidget,public ServiceForLayers
{
	Q_OBJECT
	QWidget *ImageParent;
public:
	TrueColorChangeShiftForm(LayersBase *Base,QWidget *parent = 0);
	~TrueColorChangeShiftForm();
	void	Initial(QWidget *parent ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private:
	Ui::TrueColorChangeShiftFormClass ui;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmItemIndependentPack	*IData;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButton_clicked();
};

#endif // TRUECOLORCHANGESHIFTFORM_H