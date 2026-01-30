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

#ifndef PROPERTYFrameDEFFORM_H
#define PROPERTYFrameDEFFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include"XPropertyFrameDefPacket.h"
#include "XFrameDef.h"

namespace Ui {
class PropertyFrameDefForm;
}

class PropertyFrameDefForm : public GUIFormBase
{
    Q_OBJECT
    FrameContainer		FrameGrid;
public:
    explicit PropertyFrameDefForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyFrameDefForm();
    
	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	ShowItemGrid(void);

private slots:

    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_toolButtonOverlap_clicked();

private:
    Ui::PropertyFrameDefForm *ui;
};



#endif // PROPERTYFrameDEFFORM_H