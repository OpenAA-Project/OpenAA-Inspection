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
