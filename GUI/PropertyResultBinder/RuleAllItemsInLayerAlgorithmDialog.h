/*
 * Copyright (C) 2024
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

#ifndef RULEALLITEMSINLAYERALGORITHMDIALOG_H
#define RULEALLITEMSINLAYERALGORITHMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XRuleOfBinder.h"
#include"XPropertyResultBinderPacket.h"

namespace Ui {
class RuleAllItemsInLayerAlgorithmDialog;
}

class RuleAllItemsInLayerAlgorithmDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit RuleAllItemsInLayerAlgorithmDialog(int Page,LayersBase *Base ,bool CreateMode ,QWidget *parent = 0);
    ~RuleAllItemsInLayerAlgorithmDialog();

	QString	SelectedDLLRoot;
	QString	SelectedDLLName;
	int	SelectedPage;
	int	SelectedLayer;
	QString	RuleName;
	QString	RuleRemark;
	bool	Conclusion;

	void	Initial(ChildOfRuleAllItemsInLayerAlgorithm *rule);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonDelete_clicked();

private:
    Ui::RuleAllItemsInLayerAlgorithmDialog *ui;
};

#endif // RULEALLITEMSINLAYERALGORITHMDIALOG_H