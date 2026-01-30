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



#ifndef WHITEBALANCEFORM_H
#define WHITEBALANCEFORM_H

#include <QDialog>
#include "ui_WhiteBalanceForm.h"

class mtLineGraph;

class WhiteBalanceForm : public QDialog
{
	Q_OBJECT

public:
	WhiteBalanceForm(QList<int> *RDataList,QList<int> *GDataList,QList<int> *BDataList,int Offset=0);
	~WhiteBalanceForm();

	void SetDotPerLine(int Line)	{	DotPerLine=Line;	}

private slots:
	void sbRedAdjustNumb_valueChanged	(int value);
	void sbGreenAdjustNumb_valueChanged	(int value);
	void sbBlueAdjustNumb_valueChanged	(int value);
	void pbShading_clicked();
	void pbSave_clicked();
	void pbClose_clicked();

private:
	Ui::WhiteBalanceFormClass ui;
	mtLineGraph		*LineGraph;
	QList<int> *RGBDataList[3];

	int DotPerLine;
	int OffsetNumb;
};

#endif // WHITEBALANCEFORM_H