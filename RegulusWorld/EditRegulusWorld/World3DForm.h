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

#ifndef WORLD3DFORM_H
#define WORLD3DFORM_H

#include <QWidget>
#include "XDisplayImage3D.h"
namespace Ui {
class World3DForm;
}
class EditRegulusWorld;

class World3DForm : public QWidget
{
    Q_OBJECT

    EditRegulusWorld    *Parent;
    XDisplayImage3D     DisplayImage3D;
public:
    explicit World3DForm(EditRegulusWorld *p,QWidget *parent = nullptr);
    ~World3DForm();

private:
    Ui::World3DForm *ui;

    virtual	void resizeEvent(QResizeEvent *event)	override;
};

#endif // WORLD3DFORM_H