/*
 * Copyright (C) 2025
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

#ifndef SAVETHRESHOLDDIALOG_H
#define SAVETHRESHOLDDIALOG_H

#include <QDialog>

namespace Ui {
class SaveThresholdDialog;
}

class SaveThresholdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveThresholdDialog(QWidget *parent = nullptr);
    ~SaveThresholdDialog();

private slots:
    void on_pushButtonCreateNew_clicked();

    void on_pushButtonModify_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonClose_clicked();

    void on_tableWidget_itemSelectionChanged();

private:
    Ui::SaveThresholdDialog *ui;
};

#endif // SAVETHRESHOLDDIALOG_H