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
