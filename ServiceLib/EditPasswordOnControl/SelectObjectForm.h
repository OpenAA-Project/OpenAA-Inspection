/*
 * Copyright (C) 2016
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

#ifndef SELECTOBJECTFORM_H
#define SELECTOBJECTFORM_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "XTypeDef.h"

namespace Ui {
    class SelectObjectForm;
}

class SelectObjectForm : public QDialog
{
    Q_OBJECT
	QWidget *StartObject;
public:
    explicit SelectObjectForm(QWidget *_StartObject, QWidget *parent = 0);
    ~SelectObjectForm();

	QString	SelectedObjPath;
	int32	ControlMode;
private slots:
    void on_pushButtonSelect_clicked();

    void on_pushButtonCancel_clicked();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    Ui::SelectObjectForm *ui;

	bool	SetObjectText(int Index,QTreeWidgetItem *ThisTree,QObject *thisObj);
	void	AddChild(int Index,QTreeWidgetItem *ParentTree,QObject *ParentObject);
	QString	GetSelectedObjPath(QObject *d);
	QObject *GetChildObject(const QStringList &ObjList ,int Index ,QObject *CurrentObject);
};

#endif // SELECTOBJECTFORM_H