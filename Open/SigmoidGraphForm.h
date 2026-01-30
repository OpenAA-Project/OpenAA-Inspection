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

#ifndef SIGMOIDGRAPHFORM_H
#define SIGMOIDGRAPHFORM_H

#include <QDialog>
#include "ui_SigmoidGraphForm.h"

class mtLineGraph;
class RepairBase;

/********** �V�O���C�h�֐�
			  1
	f(x)=������������	e�̒l���A1 < e < XXX �ƕω������ăO���t���`��
		  1 + e^(-x)
**********/

class SigmoidGraphForm : public QDialog
{
	Q_OBJECT

public:
	SigmoidGraphForm(RepairBase *ParentClass,QWidget *parent);
	~SigmoidGraphForm();

private slots:
	void dsbVolumeChanged	(double value);
	void sbBrightnessChanged(int value);
	void pbOKClicked		();
	void pbCancelClicked	();

private:
	Ui::SigmoidGraphFormClass ui;

	RepairBase		*PClass;
	mtLineGraph		*SigGraph;
	int				wBrightness[256];
};

#endif // SIGMOIDGRAPHFORM_H