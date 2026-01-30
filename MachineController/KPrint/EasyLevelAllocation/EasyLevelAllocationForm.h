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

#ifndef EASYLEVELALLOCATIONFORM_H
#define EASYLEVELALLOCATIONFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"


namespace Ui {
class EasyLevelAllocationForm;
}

class EasyLevelAllocationForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	
	explicit EasyLevelAllocationForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyLevelAllocationForm();
    virtual	void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;

private slots:
    void on_PushButtonOpen_clicked();
	void	ResizeAction();
private:
    Ui::EasyLevelAllocationForm *ui;
};

class	IntegrationShowLevelDialog : public GUIDirectMessage
{
public:
	IntegrationShowLevelDialog(LayersBase *base):GUIDirectMessage(base){}
	IntegrationShowLevelDialog(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif // EASYLEVELALLOCATIONFORM_H