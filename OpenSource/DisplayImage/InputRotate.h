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

#ifndef INPUTROTATE_H
#define INPUTROTATE_H

#include <QDialog>

namespace Ui {
class InputRotate;
}
class	LayersBase;

class InputRotate : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputRotate(LayersBase *Base,QWidget *parent = 0);
    ~InputRotate();

    int	Angle;

private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonSetDegree_clicked();
    void on_pushButton90Degree_clicked();
    void on_pushButton180Degree_clicked();
    void on_pushButton270Degree_clicked();

private:
    Ui::InputRotate *ui;
};

#endif // INPUTROTATE_H