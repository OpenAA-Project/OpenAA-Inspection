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

#ifndef DISPLAYPRODUCTIVITYFORM_H
#define DISPLAYPRODUCTIVITYFORM_H

#include <QString>
#include <QStringList>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include "XTypeDef.h"

namespace Ui {
class DisplayProductivityForm;
}

class DisplayProductivityForm : public GUIFormBase
{
    Q_OBJECT

    DWORD   InspectedTimeMilisec[100];
    int     CountInspected;
    int     WPoint;
public:
    QString CountType;

    explicit DisplayProductivityForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~DisplayProductivityForm();

	virtual void	Prepare(void)		override;
    virtual void	ShowInPlayer(int64 shownInspectionID)		override;
private:
    Ui::DisplayProductivityForm *ui;
};

#endif // DISPLAYPRODUCTIVITYFORM_H