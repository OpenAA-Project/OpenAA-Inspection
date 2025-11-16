#ifndef RULEOPERATIONDIALOG_H
#define RULEOPERATIONDIALOG_H

#include <QDialog>
#include "XRuleOfBinder.h"
#include "XServiceForLayers.h"

namespace Ui {
class RuleOperationDialog;
}

class RuleOperationDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit RuleOperationDialog(LayersBase *base, QWidget *parent = 0);
    ~RuleOperationDialog();

	QString	RuleName;
	QString	RuleRemark;
	bool	Conclusion;

	void	Initial(RuleOfBinderBase *rule);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::RuleOperationDialog *ui;
};

#endif // RULEOPERATIONDIALOG_H
