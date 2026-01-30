/*
 * Copyright (C) 2017
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

#ifndef RULECONDITIONALDIALOG_H
#define RULECONDITIONALDIALOG_H

#include <QDialog>
#include "XRuleOfBinder.h"
#include "XRuleOfBinderCommon.h"
#include "XServiceForLayers.h"

namespace Ui {
class RuleConditionalDialog;
}

class RuleConditionalDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	int InputNumb;
public:
    explicit RuleConditionalDialog(LayersBase *base, int InputNumb ,QWidget *parent = 0);
    ~RuleConditionalDialog();

	ConditionListContainer	ConditionData;
	QString	RuleName;
	QString	RuleRemark;
	bool	Conclusion;
	bool	NGOthers;

	void	Initial(ChildOfRuleOperationConditional *rule ,int InputNumb);
private slots:
    void on_pushButtonInsertNew_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_listWidgetCondition_currentRowChanged(int currentRow);

private:
    Ui::RuleConditionalDialog *ui;

	void ShowConditionList(void);
	int	GetCondition(const QString &CondStr);
};

#endif // RULECONDITIONALDIALOG_H