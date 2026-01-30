/*
 * Copyright (C) 2022
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

#ifndef OPERATEVRSFORM_H
#define OPERATEVRSFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class OperateVRSForm;
}
class	ShowVRSOperation;

class OperateVRSForm : public GUIFormBase
{
    Q_OBJECT

	GUIFormBase	*VRSOpe;
    
public:
    explicit OperateVRSForm(LayersBase *base ,QWidget *parent = 0);
    ~OperateVRSForm();

    virtual void	Prepare(void)	override;

private slots:
    void on_pushButtonOrigin_clicked();
    void on_pushButtonEscape_clicked();
    void on_pushButtonXP1_clicked();
    void on_pushButtonXP10_clicked();
    void on_pushButtonXP100_clicked();
    void on_pushButtonXM1_clicked();
    void on_pushButtonXM10_clicked();
    void on_pushButtonXM100_clicked();
    void on_pushButtonYP1_clicked();
    void on_pushButtonYP10_clicked();
    void on_pushButtonYP100_clicked();
    void on_pushButtonYM10_clicked();
    void on_pushButtonYM100_clicked();
    void on_pushButtonYM1_clicked();

private:
    Ui::OperateVRSForm *ui;
};

#endif // OPERATEVRSFORM_H