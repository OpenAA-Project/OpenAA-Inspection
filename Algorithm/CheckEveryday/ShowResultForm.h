#ifndef SHOWRESULTFORM_H
#define SHOWRESULTFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XPasswordQWidget.h"
#include "XDataInLayer.h"

namespace Ui {
class ShowResultForm;
}

class ShowResultForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

public:
    explicit ShowResultForm(LayersBase *Base,QWidget *parent = 0);
    ~ShowResultForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
private slots:
    void on_pushButtonSet_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::ShowResultForm *ui;
};

#endif // SHOWRESULTFORM_H
