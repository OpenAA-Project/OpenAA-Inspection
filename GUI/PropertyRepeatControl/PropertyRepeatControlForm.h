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

#ifndef PROPERTYREPEATCONTROLFORM_H
#define PROPERTYREPEATCONTROLFORM_H

#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XPropertyRepeatControlPacket.h"

namespace Ui {
class PropertyRepeatControlForm;
}

class RepeatControlBase;

class PropertyRepeatControlForm : public GUIFormBase
{
    Q_OBJECT

    RepeatControlInfoListContainer  ItemList;
public:
    explicit PropertyRepeatControlForm(LayersBase *Base,QWidget *parent = nullptr);
    ~PropertyRepeatControlForm();

    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override; 
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

    void    CreateWhole(int RepeatCount);
private slots:
    void on_tableWidgetList_clicked(const QModelIndex &index);
    void on_tableWidgetList_doubleClicked(const QModelIndex &index);
    void on_pushButtonCreateWhole_clicked();

private:
    Ui::PropertyRepeatControlForm *ui;

    void	ShowList(void);
    RepeatControlBase	*GetRepeatControlBase(void);
};

#endif // PROPERTYREPEATCONTROLFORM_H