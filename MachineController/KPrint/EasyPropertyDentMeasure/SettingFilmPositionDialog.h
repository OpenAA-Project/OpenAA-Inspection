/*
 * Copyright (C) 2024
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

#ifndef SETTINGFILMPOSITIONDIALOG_H
#define SETTINGFILMPOSITIONDIALOG_H

#include <QDialog>

namespace Ui {
class SettingFilmPositionDialog;
}

class	EasyPropertyDentMeasureForm;

class SettingFilmPositionDialog : public QDialog
{
    Q_OBJECT

    EasyPropertyDentMeasureForm *Parent;
public:
    explicit SettingFilmPositionDialog(EasyPropertyDentMeasureForm *p ,int FilmIndex,int FilmPointNo ,QWidget *parent = nullptr);
    ~SettingFilmPositionDialog();

    int FilmIndex;
    int FilmPointNo;

private slots:
    void on_PushButtonOK_clicked();
    void on_PushButtonCancel_clicked();
    void	SlotEndPointClicked(int EndNo,int MeasureNo);
private:
    Ui::SettingFilmPositionDialog *ui;
};

#endif // SETTINGFILMPOSITIONDIALOG_H