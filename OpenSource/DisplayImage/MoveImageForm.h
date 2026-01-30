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

#ifndef MOVEIMAGEFORM_H
#define MOVEIMAGEFORM_H

#include <QWidget>
#include "XServiceForLayers.h"

namespace Ui {
class MoveImageForm;
}

class MoveImageForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit MoveImageForm(LayersBase *Base,QWidget *parent = 0);
    ~MoveImageForm();

    bool	FlagMaster;
    bool	FlagTarget;

    int		XDir,YDir;
    bool	RetMode;

signals:
    void	SignalClose();

private slots:
    void on_pushButtonGo_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::MoveImageForm *ui;
};

#endif // MOVEIMAGEFORM_H