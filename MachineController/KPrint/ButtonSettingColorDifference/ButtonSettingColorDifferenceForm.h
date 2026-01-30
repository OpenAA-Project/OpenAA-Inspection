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

#ifndef BUTTONSETTINGCOLORDIFFERENCEFORM_H
#define BUTTONSETTINGCOLORDIFFERENCEFORM_H

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
class ButtonSettingColorDifferenceForm;
}

class ButtonSettingColorDifferenceForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	int32	SlaveNo;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	
	explicit ButtonSettingColorDifferenceForm(LayersBase *Base ,QWidget *parent = 0);
    ~ButtonSettingColorDifferenceForm();
    
	virtual	void	Prepare(void) override;
	int		GetSlaveNo(void)	{	return SlaveNo;		}
private slots:
    void on_PushButtonThreshold_clicked();
	void	ResizeAction();
private:
    Ui::ButtonSettingColorDifferenceForm *ui;
};

#endif // BUTTONSETTINGCOLORDIFFERENCEFORM_H