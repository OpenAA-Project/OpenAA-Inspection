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

#ifndef RWSHOWOBJECTPROPERTYFORM_H
#define RWSHOWOBJECTPROPERTYFORM_H

#include <QWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
namespace Ui {
class RWShowObjectPropertyForm;
}

class RWShowObjectPropertyForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit RWShowObjectPropertyForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~RWShowObjectPropertyForm();

private:
    Ui::RWShowObjectPropertyForm *ui;

    virtual void resizeEvent(QResizeEvent *event) override;
};

#endif // RWSHOWOBJECTPROPERTYFORM_H