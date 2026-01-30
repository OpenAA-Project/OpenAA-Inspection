/*
 * Copyright (C) 2019
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

#ifndef INTEGRATIONSELECTMASTERFORM_H
#define INTEGRATIONSELECTMASTERFORM_H

#include <QWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QSqlTableModel>
#include <QTableView>
#include "IntegrationLib.h"

namespace Ui {
class IntegrationSelectMasterForm;
}

class IntegrationSelectMasterForm;
class	QSqlLoadRelationModel : public QSqlTableModel
{
	IntegrationSelectMasterForm	*ParentWindow;
public:
	QSqlLoadRelationModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;
};

class IntegrationSelectMasterForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	QTableView *MListView;
public:
    explicit IntegrationSelectMasterForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationSelectMasterForm();

private slots:
    void on_pushButtonSelect_clicked();
	void	ResizeAction();
	void	SlotClicked			(const QModelIndex &Index);
	void	SlotDoubleClicked	(const QModelIndex &Index);

private:
    Ui::IntegrationSelectMasterForm *ui;

	void	ShowListHeader(void);
};

#endif // INTEGRATIONSELECTMASTERFORM_H