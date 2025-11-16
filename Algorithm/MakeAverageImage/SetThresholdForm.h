#ifndef SETTHRESHOLDFORM_H
#define SETTHRESHOLDFORM_H

#include <QWidget>
#include <QToolBar>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XMakeAverageImage.h"

namespace Ui {
class SetThresholdForm;
}

class SetThresholdForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT
    int     HistgramPage;
    bool	OnChanging;
public:
    explicit SetThresholdForm(LayersBase *Base,QWidget *parent = 0);
    ~SetThresholdForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);

	AlgorithmItemIndependentPack	*IData;
	HistgramTypeListInAlgoContainer	HContainer;    

private slots:
    void on_pushButtonSetOne_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonClose_clicked();

    void on_spinBoxSearchDot_valueChanged(int arg1);

    void on_doubleSpinBoxSearchDotUnit_valueChanged(double arg1);

private:
    Ui::SetThresholdForm *ui;
};

#endif // SETTHRESHOLDFORM_H
