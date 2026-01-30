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

#ifndef RULEALGORITHMITEMDIALOG_H
#define RULEALGORITHMITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XRuleOfBinder.h"
#include"XPropertyResultBinderPacket.h"

namespace Ui {
class RuleAlgorithmItemDialog;
}

class RuleAlgorithmItemDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

	ItemIDNameContainer	ItemIDNameData;
public:
    explicit RuleAlgorithmItemDialog(LayersBase *Base ,bool CreateMode ,QWidget *parent = 0);
    ~RuleAlgorithmItemDialog();

	QString	SelectedDLLRoot;
	QString	SelectedDLLName;
	int	SelectedPage;
	int	SelectedLayer;
	int	SelectedItemID;
	QString	SelectedItemName;
	QString	RuleName;
	QString	RuleRemark;
	bool	Conclusion;

	void	Initial(ChildOfRuleAlgorithmItem *rule);

private slots:
    void on_pushButtonFindItem_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonDelete_clicked();

private:
    Ui::RuleAlgorithmItemDialog *ui;
};

#endif // RULEALGORITHMITEMDIALOG_H