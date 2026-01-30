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

#ifndef INTEGRATIONIMAGEBANKFORM_H
#define INTEGRATIONIMAGEBANKFORM_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XIntegrationPacketComm.h"
#include "IntegrationLib.h"
#include "IntegrationImageBank.h"

namespace Ui {
class IntegrationImageBankForm;
}
class	IntegrationImageBank;

class IntegrationImageBankForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    IntegrationImageBank    *Parent;
    ListImageBankPointerContainerContainer  GridList;

public:
    explicit IntegrationImageBankForm(LayersBase *Base,IntegrationImageBank *p ,QWidget *parent = 0);
    ~IntegrationImageBankForm();
    
    void ShowGrid(void);

private slots:
    void on_tableWidgetImages_doubleClicked(const QModelIndex &index);
    void on_pushButtonCountSet_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonClose_clicked();
    void on_toolButtonStoreOnlyOK_clicked();
    void on_toolButtonStoreOnlyNG_clicked();
    void on_pushButtonBankON_clicked();

private:
    Ui::IntegrationImageBankForm *ui;
};

#endif // INTEGRATIONIMAGEBANKFORM_H