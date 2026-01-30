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

#ifndef REGISTHALCONFUNC_H
#define REGISTHALCONFUNC_H

#include <QDialog>
#include "ui_RegistHalconFunc.h"
#include "PropertyHalconForm.h"

class RegistHalconFunc : public QDialog
{
	Q_OBJECT

public:
	RegistHalconFunc(PropertyHalconForm *parent);
	~RegistHalconFunc();

private:
	Ui::RegistHalconFuncClass ui;

	QLabel		*HLabel[10];
	QComboBox	*ComboBox[10];
	QLabel		*FLabel[10];

	PropertyHalconForm *PClass;
	QStringList	ArgRegionList;
	QStringList	ArgTupleList;

	QStringList HLabelStringList;
	QStringList FLabelStringList;

	ArgType		ATypeList[10];
	QString		*HalconFuncString;

	void VisibleSet(bool Visible,int VisibleCnt);
	void SetCombInformation(ArgType Type1,int CntType1,ArgType Type2,int CntType2);
	void SetCombInformation(ArgType Type,int CntType,int Index=0);
	void SetCombInformation(char **List,int Index);

private slots:
	void cbFunCcurrentIndexChanged(int Index);
	void pbOKClicked();
	void pbCancelClicked();
};

#endif // REGISTHALCONFUNC_H