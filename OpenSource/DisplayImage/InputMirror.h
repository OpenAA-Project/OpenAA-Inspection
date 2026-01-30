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

#ifndef INPUTMIRROR_H
#define INPUTMIRROR_H

#include <QDialog>
#include "XDisplayImage.h"
#include "XDataAlgorithm.h"

namespace Ui {
class InputMirror;
}

class	LayersBase;

class InputMirror : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputMirror(LayersBase *Base,QWidget *parent = 0);
    ~InputMirror();

    AlgorithmItemRoot::_MirrorMode	MirrorMode;
    
private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonYMirror_clicked();
    void on_pushButtonXMirror_clicked();

private:
    Ui::InputMirror *ui;
};

#endif // INPUTMIRROR_H