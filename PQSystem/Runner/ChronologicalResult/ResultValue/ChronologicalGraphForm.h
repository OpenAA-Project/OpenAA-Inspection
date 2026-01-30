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

#ifndef CHRONOLOGICALGRAPHFORM_H
#define CHRONOLOGICALGRAPHFORM_H

#include <QWidget>

namespace Ui {
class ChronologicalGraphForm;
}

class ChronologicalGraphForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit ChronologicalGraphForm(QWidget *parent = 0);
    ~ChronologicalGraphForm();
    
private slots:
    void on_comboBoxTimeSpan_currentIndexChanged(int index);

private:
    Ui::ChronologicalGraphForm *ui;
};

#endif // CHRONOLOGICALGRAPHFORM_H