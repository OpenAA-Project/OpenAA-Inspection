/*
 * Copyright (C) 2020
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

#ifndef SELECTDIRECTORYDIALOG_H
#define SELECTDIRECTORYDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QTreeView>

namespace Ui {
class SelectDirectoryDialog;
}

class SelectDirectoryDialog : public QDialog
{
    Q_OBJECT
    QFileSystemModel	Model;
public:
    explicit SelectDirectoryDialog(const QString &Path ,QWidget *parent = 0);
    ~SelectDirectoryDialog();
    
	QString	Directory;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::SelectDirectoryDialog *ui;
};

#endif // SELECTDIRECTORYDIALOG_H