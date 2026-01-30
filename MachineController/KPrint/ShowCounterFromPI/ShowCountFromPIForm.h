/*
 * Copyright (C) 2025
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

#ifndef SHOWCOUNTFROMPIFORM_H
#define SHOWCOUNTFROMPIFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XGUIPacketForDLL.h"
#include <QModelIndex>
#include <QTimer>
#include "XCommToTrigger.h"

namespace Ui {
class ShowCountFromPIForm;
}

class CartonMenuForm;
class WindowMismatchForm;

class ShowCountFromPIForm : public GUIFormBase
{
    Q_OBJECT

    QTimer  TM;
    CartonMenuForm	*CartonProp;
	WindowMismatchForm  *WindowMismatchFormInst;
public:
    explicit ShowCountFromPIForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ShowCountFromPIForm();

	virtual void	ReadyParam(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)  override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

private slots:
	void	ResizeAction();
    void    SlotTimeOut();
private:
    Ui::ShowCountFromPIForm *ui;

    void    ShowMismatch(void);
};

#endif // SHOWCOUNTFROMPIFORM_H