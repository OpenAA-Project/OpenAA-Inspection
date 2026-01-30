/*
 * Copyright (C) 2017
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

#ifndef EDITIMPORTANCEFORM_H
#define EDITIMPORTANCEFORM_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class EditImportanceForm;
}

class EditImportanceForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditImportanceForm(LayersBase *base, QWidget *parent = 0);
    ~EditImportanceForm();

	int		ImportanceLevel;
	void	SetImportanceLevel(int L);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonOKLevel_clicked();
    void on_pushButtonCancel_clicked();
    void on_radioButtonVeryHigh_clicked(bool checked);
    void on_radioButtonHigh_clicked(bool checked);
    void on_radioButtonNormal_clicked(bool checked);
    void on_radioButtonNotSoHigh_clicked(bool checked);
    void on_spinBoxLevel_valueChanged(int arg1);

private:
    Ui::EditImportanceForm *ui;
};

#endif // EDITIMPORTANCEFORM_H