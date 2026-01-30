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

#ifndef PROPERTYPROCESS3DFORM_H
#define PROPERTYPROCESS3DFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XProcess3D.h"

namespace Ui {
class PropertyProcess3DForm;
}

class PropertyProcess3DForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyProcess3DForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyProcess3DForm();

	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_pushButtonEditLibrary_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyProcess3DForm *ui;
	Process3DBase	*GetProcess3DBase(void);

	Process3DLibrary	*TempLib;
	int						LibType;

	NPListPack<Process3DInfoList>	Process3DInfos;
	void	ShowList(void);

};

#endif // PROPERTYPROCESS3DFORM_H