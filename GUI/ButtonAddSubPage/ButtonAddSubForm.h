/*
 * Copyright (C) 2025
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

#ifndef BUTTONADDSUBFORM_H
#define BUTTONADDSUBFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ButtonAddSubForm;
}

class ButtonAddSubForm : public GUIFormBase
{
    Q_OBJECT

public:
    bool    CopyAllAlgorithm;
    bool    CopyAllFilters;

    explicit ButtonAddSubForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ButtonAddSubForm();

    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_toolButtonAdd_clicked();
    void on_toolButtonSub_clicked();

private:
    Ui::ButtonAddSubForm *ui;
};

#endif // BUTTONADDSUBFORM_H