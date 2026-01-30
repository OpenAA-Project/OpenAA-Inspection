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

#ifndef RULEALLITEMSINPAGEALGORITHMDIALOG_H
#define RULEALLITEMSINPAGEALGORITHMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XRuleOfBinder.h"
#include"XPropertyResultBinderPacket.h"

namespace Ui {
class RuleAllItemsInPageAlgorithmDialog;
}

class RuleAllItemsInPageAlgorithmDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit RuleAllItemsInPageAlgorithmDialog(LayersBase *Base ,bool CreateMode ,QWidget *parent = 0);
    ~RuleAllItemsInPageAlgorithmDialog();

	QString	SelectedDLLRoot;
	QString	SelectedDLLName;
	int	SelectedPage;
	QString	RuleName;
	QString	RuleRemark;
	bool	Conclusion;

	void	Initial(ChildOfRuleAllItemsInPageAlgorithm *rule);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonDelete_clicked();

private:
    Ui::RuleAllItemsInPageAlgorithmDialog *ui;
};

#endif // RULEALLITEMSINPAGEALGORITHMDIALOG_H