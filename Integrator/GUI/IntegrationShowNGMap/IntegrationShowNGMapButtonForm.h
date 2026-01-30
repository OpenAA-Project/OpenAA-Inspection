/*
 * Copyright (C) 2020
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

#ifndef INTEGRATIONSHOWNGMAPBUTTONFORM_H
#define INTEGRATIONSHOWNGMAPBUTTONFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class IntegrationShowNGMapButtonForm;
}

class IntegrationShowNGMapButtonForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	int32	SlaveNo;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	
	explicit IntegrationShowNGMapButtonForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationShowNGMapButtonForm();
    
	virtual	void	Prepare(void)	override;

private slots:
    void on_PushButtonNGMap_clicked();
	void	ResizeAction();
private:
    Ui::IntegrationShowNGMapButtonForm *ui;
};

#endif // INTEGRATIONSHOWNGMAPBUTTONFORM_H