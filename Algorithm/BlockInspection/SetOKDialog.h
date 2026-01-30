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

#ifndef SETOKDIALOG_H
#define SETOKDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SetOKDialog;
}

class SetOKDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SetOKDialog(LayersBase *base, QWidget *parent = 0);
    ~SetOKDialog();
    
private slots:
    void on_pushButtonBOKBright_clicked();
    void on_pushButtonBOKSize_clicked();
    void on_pushButtonNOKBright_clicked();
    void on_pushButtonNOKSize_clicked();
    void on_pushButtonOKSearch_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SetOKDialog *ui;
};

#endif // SETOKDIALOG_H