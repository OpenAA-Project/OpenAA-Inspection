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
