/*
 * Copyright (C) 2023
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

#ifndef SELECTDISPATCHDIALOG_H
#define SELECTDISPATCHDIALOG_H

#include <QDialog>
#include "mtToolButtonColored.h"
#include "XServiceForLayers.h"
#include<QPushButton>

namespace Ui {
class SelectDispatchDialog;
}

class MasterButton : public QPushButton
{
    Q_OBJECT

    int ID;
public:
    MasterButton(int ID ,QWidget *obj=nullptr);

signals:
    void    SignalClicked(int ID);
private slots:
    void    SlotClicked();
};

class SelectDispatchDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    MasterButton    **MasterButtonDim;
    int             CountMasterButton;
public:
    explicit SelectDispatchDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~SelectDispatchDialog();

    int MasterNo;
private slots:
    void SlotMasterChanged(int ID);
private:
    Ui::SelectDispatchDialog *ui;
};

#endif // SELECTDISPATCHDIALOG_H