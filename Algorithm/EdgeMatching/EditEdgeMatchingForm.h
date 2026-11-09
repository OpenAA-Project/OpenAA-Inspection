#ifndef EDITEDGEMATCHINGFORM_H
#define EDITEDGEMATCHINGFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XEdgeMatching.h"

namespace Ui {
class EditEdgeMatchingForm;
}

class EditEdgeMatchingForm : public QWidget, public ServiceForLayers, public PasswordInQWodget
{
    Q_OBJECT

public:
    explicit EditEdgeMatchingForm(LayersBase *Base, QWidget *parent = nullptr);
    ~EditEdgeMatchingForm();

    void Initial(AlgorithmBase *InstBase, AlgorithmItemIndependentPack &Data);
    void GetDataFromWindow(void);
    void ShowDataToWindow(void);

    AlgorithmItemIndependentPack *IData;

private slots:
    void on_EditFocusRadius_valueChanged(int arg1);
    void on_EditLayer_valueChanged(int arg1);
    void on_EditSearchDotX_valueChanged(int arg1);
    void on_EditSearchDotY_valueChanged(int arg1);
    void on_EditSearchByPixel_valueChanged(int arg1);
    void on_EditThresholdDiv_valueChanged(double arg1);
    void on_EditThresholdDirection_valueChanged(double arg1);

    void on_pushButtonReflectOnly_clicked();
    void on_pushButtonReflectAll_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::EditEdgeMatchingForm *ui;

    int GlobalPage;
    bool OnChanging;
};

#endif // EDITEDGEMATCHINGFORM_H
