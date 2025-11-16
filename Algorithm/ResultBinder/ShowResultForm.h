#ifndef SHOWRESULTFORM_H
#define SHOWRESULTFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XServiceForLayers.h"

namespace Ui {
class ShowResultForm;
}

class ShowResultForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit ShowResultForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowResultForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

	AlgorithmItemIndependentPack	*IData;
	int		ItemID;
	QString	ItemName;

	QString	RuleName;
	QString	RuleRemark;

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::ShowResultForm *ui;
};

#endif // SHOWRESULTFORM_H
