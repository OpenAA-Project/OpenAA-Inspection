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

#ifndef WORKERSELECTFORM_H
#define WORKERSELECTFORM_H

#include <QDialog>
#include "ui_WorkerSelectForm.h"

class RepairBase;

class WorkerSelectForm : public QDialog
{
    Q_OBJECT

public:
	WorkerSelectForm(RepairBase *ParentClass,QWidget *parent=0);
	~WorkerSelectForm();

protected:

signals:
	void SignalClose();

private slots:
	void pbOKClicked();
	void WorkerListChanged(const QModelIndex &CIndex);		//���Ǝ҃��X�g��Changed�C�x���g

private:
    Ui::WorkerSelectClass ui;
	QStringList WFieldNames;
	RepairBase *PClass;

	void SelectData();
};

#endif // WORKERSELECTFORM_H