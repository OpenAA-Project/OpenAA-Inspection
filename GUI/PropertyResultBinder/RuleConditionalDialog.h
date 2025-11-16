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
