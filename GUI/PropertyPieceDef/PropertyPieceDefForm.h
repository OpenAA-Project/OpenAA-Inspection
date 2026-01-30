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

#ifndef PROPERTYPIECEDEFFORM_H
#define PROPERTYPIECEDEFFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include"XPropertyPieceDefPacket.h"

namespace Ui {
class PropertyPieceDefForm;
}

class PropertyPieceDefForm : public GUIFormBase
{
    Q_OBJECT
    
	PieceDefInfoContainer	DefList;
public:
    explicit PropertyPieceDefForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyPieceDefForm();
    
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	ShowItemGrid(void);

private slots:
    void on_pushButtonStartSearch_clicked();
    void on_tableWidgetResult_clicked(const QModelIndex &index);
    void on_pushButtonCopyByFoundItems_clicked();
    void on_pushButtonMatchClosed_clicked();

private:
    Ui::PropertyPieceDefForm *ui;
};



#endif // PROPERTYPIECEDEFFORM_H