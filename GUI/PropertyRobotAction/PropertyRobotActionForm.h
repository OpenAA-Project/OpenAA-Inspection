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

#ifndef PROPERTYROBOTACTIONFORM_H
#define PROPERTYROBOTACTIONFORM_H

#include "XGUIFormBase.h"
#include "XRobotAction.h"

namespace Ui {
class PropertyRobotActionForm;
}

class PropertyRobotActionForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyRobotActionForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PropertyRobotActionForm();

    virtual void	BuildForShow(void)  override;
    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private slots:
    void on_tableWidgetMarkList_clicked(const QModelIndex &index);
    void on_tableWidgetMarkList_doubleClicked(const QModelIndex &index);

    void on_pushButtonClearAll_clicked();

    void on_toolButtonTeachingMode_clicked();

private:
    Ui::PropertyRobotActionForm *ui;
    RobotActionBase	*GetRobotActionBase(void);
    GUIFormBase     *GetPanel(void);
    void    ShowList(void);
};

#endif // PROPERTYROBOTACTIONFORM_H