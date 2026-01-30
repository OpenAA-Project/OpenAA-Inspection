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

#ifndef LOTSELECTFORM_H
#define LOTSELECTFORM_H

#include <QDialog>
#include "ui_LotSelectForm.h"

class RepairBase;
class ProcessingForm;

class LotSelectForm : public QDialog
{
    Q_OBJECT

public:
	LotSelectForm(RepairBase *ParentClass,QWidget *parent = 0);
	~LotSelectForm();

	bool GetResult()			{	return Result;	}
	void SetBoth(bool Flag)		{	IsBoth=Flag;	}
	bool GetBoth()				{	return IsBoth;	}
	bool ExecSelectLot(QString LotName,QString LotID);

protected:

signals:
	void SignalClose();

private slots:
	void pbSearchClicked();
	void leSearchLotNameTextChanged(QString text);
	void pbSelectClicked();
	void pbAllSelectClicked();
	void pbCancelClicked();

private:
    Ui::LotSelectClass ui;
	RepairBase			*PClass;
	QStringList			 LFieldNames;
	QList<QByteArray>	 RetList;
//	ProcessingForm		*LotProcessing;

	bool Result;
	bool IsBoth;
};

#endif // LOTSELECTFORM_H