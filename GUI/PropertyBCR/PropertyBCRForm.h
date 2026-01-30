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

#ifndef PROPERTYBCRFORM_H
#define PROPERTYBCRFORM_H

#include "XGUIFormBase.h"
#include "XBCRInspection.h"
#include "XStandardPropertyForm.h"
#include "XPropertyBCRPacket.h"
#include <QModelIndex>

namespace Ui {
class PropertyBCRForm;
}

class PropertyBCRForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit PropertyBCRForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyBCRForm();
    
	virtual	void	BuildForShow(void)  override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)  override;

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_pushButtonTest_clicked();
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyBCRForm *ui;

	void	ShowGrid(void);
	BCRContainer	GridList;
};

#endif // PROPERTYBCRFORM_H