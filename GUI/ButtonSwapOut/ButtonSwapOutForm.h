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

#ifndef BUTTONSWAPOUTFORM_H
#define BUTTONSWAPOUTFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ButtonSwapOutForm;
}

class ButtonSwapOutForm : public GUIFormBase
{
    Q_OBJECT

public:
	QString	Msg;
	QFont	CFont;
	QColor	ButtonColor;
	bool	MasterImage;
	
   	explicit ButtonSwapOutForm(LayersBase *base ,QWidget *parent = 0);
    ~ButtonSwapOutForm();

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	
	void	CommandSwapOut(void);
private slots:
    void on_pushButton_clicked();
	void	ResizeAction();
private:
    Ui::ButtonSwapOutForm *ui;
};

#endif // BUTTONSWAPOUTFORM_H