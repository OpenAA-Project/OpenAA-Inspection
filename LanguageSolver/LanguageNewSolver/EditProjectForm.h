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

#ifndef EDITPROJECTFORM_H
#define EDITPROJECTFORM_H

#include <QDialog>
#include "XLSProjectNew.h"

namespace Ui {
    class EditProjectForm;
}

class EditProjectForm : public QDialog
{
    Q_OBJECT
	LSProjectItem	*Project;

public:
    explicit EditProjectForm(LSProjectItem *a,QWidget *parent = 0);
    ~EditProjectForm();

private slots:
    void on_pushButtonFolderReference_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditProjectForm *ui;
};

#endif // EDITPROJECTFORM_H