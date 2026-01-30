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

#ifndef WIZARDMASTERMENUFORM_H
#define WIZARDMASTERMENUFORM_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"


namespace Ui {
class WizardMasterMenuForm;
}

class	WizardMenuForm;

class WizardMasterMenuForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT
    
	WizardMenuForm	*Window;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	
	explicit WizardMasterMenuForm(LayersBase *Base ,QWidget *parent = 0);
    ~WizardMasterMenuForm();
    virtual void	Prepare(void)	override;
	virtual void	ReadyParam(void)override;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	void	ExecuteSwitchImage(void);
private slots:
    void on_PushButtonMasterData_clicked();
	void	ResizeAction();
	void	SlotBusy();
	void	SlotIdle();
private:
    Ui::WizardMasterMenuForm *ui;
};

#endif // WIZARDMASTERMENUFORM_H