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

#ifndef PROPERTYCHECKBRIGHTNESSFORM_H
#define PROPERTYCHECKBRIGHTNESSFORM_H

#include <QWidget>
#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include"XPropertyCheckBrightnessPacket.h"

namespace Ui {
class PropertyCheckBrightnessForm;
}

class PropertyCheckBrightnessForm : public GUIFormBase
{
    Q_OBJECT
    CheckBrightnessInfoContainer	GridList;

public:
    explicit PropertyCheckBrightnessForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyCheckBrightnessForm();
    
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	BuildForShow(void)		override;
private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyCheckBrightnessForm *ui;

	void	ShowItemGrid(void);
};

#endif // PROPERTYCHECKBRIGHTNESSFORM_H