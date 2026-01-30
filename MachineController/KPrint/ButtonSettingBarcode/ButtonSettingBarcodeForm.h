/*
 * Copyright (C) 2021
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

#ifndef BUTTONSETTINGBARCODEFORM_H
#define BUTTONSETTINGBARCODEFORM_H

#include <QWidget>
#include <QString>
#include <QColor>
#include <QFont>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"

namespace Ui {
class ButtonSettingBarcodeForm;
}

class ButtonSettingBarcodeForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	int32	SlaveNo;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	
	explicit ButtonSettingBarcodeForm(LayersBase *Base, QWidget *parent = 0);
    ~ButtonSettingBarcodeForm();
    
	virtual	void	Prepare(void) override;
private slots:
    void on_PushButtonThreshold_clicked();
	void	ResizeAction();
private:
    Ui::ButtonSettingBarcodeForm *ui;
};

#endif // BUTTONSETTINGBARCODEFORM_H