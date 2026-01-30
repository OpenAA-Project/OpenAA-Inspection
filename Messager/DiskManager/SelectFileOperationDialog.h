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

#ifndef SELECTFILEOPERATIONDIALOG_H
#define SELECTFILEOPERATIONDIALOG_H

#include <QDialog>
#include "XDiskInfoCommon.h"

namespace Ui {
class SelectFileOperationDialog;
}

class SelectFileOperationDialog : public QDialog
{
    Q_OBJECT

	DiskFileInfo	Data;
public:
	QString	DestPath;

    explicit SelectFileOperationDialog(DiskFileInfo *data ,QWidget *parent = 0);
    ~SelectFileOperationDialog();

private slots:
    void on_pushButtonDelete_clicked();
    void on_pushButtonSelectDestination_clicked();
    void on_pushButtonMoveStart_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SelectFileOperationDialog *ui;
};

#endif // SELECTFILEOPERATIONDIALOG_H