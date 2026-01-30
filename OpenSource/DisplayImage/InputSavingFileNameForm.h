/*
 * Copyright (C) 2021
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

#ifndef INPUTSAVINGFILENAMEFORM_H
#define INPUTSAVINGFILENAMEFORM_H

#include <QDialog>

namespace Ui {
class InputSavingFileNameForm;
}
class	LayersBase;

class InputSavingFileNameForm : public QDialog
{
    Q_OBJECT

    QString	PathFileName;
public:
    explicit InputSavingFileNameForm(LayersBase *Base,const QString &filename,QWidget *parent = 0);
    ~InputSavingFileNameForm();

    QString	GetPathFileName(void){	return PathFileName;	}

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputSavingFileNameForm *ui;
};

#endif // INPUTSAVINGFILENAMEFORM_H