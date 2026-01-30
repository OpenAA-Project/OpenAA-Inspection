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

#ifndef INTEGRATIONSELECTLOTFORM_H
#define INTEGRATIONSELECTLOTFORM_H

#include <QWidget>
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"

namespace Ui {
class IntegrationSelectLotForm;
}

class IntegrationSelectLotForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

    bool    ReEntrant;
	NPListPack<LotList>	LotContainer;
public:

    explicit IntegrationSelectLotForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationSelectLotForm();

	virtual void	BuildForShow(void)	override;

private slots:
    void on_listWidget_doubleClicked(const QModelIndex &index);
    void on_toolButtonSelect_clicked();
    void on_toolButtonSetFilter_clicked();
    void on_toolButtonUpdate_clicked();
	void	ResizeAction();
private:
    Ui::IntegrationSelectLotForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
};

#endif // INTEGRATIONSELECTLOTFORM_H