#ifndef PROPERTYSTEPLINEENHANCERLFORM_H
#define PROPERTYSTEPLINEENHANCERLFORM_H

#include <QWidget>

namespace Ui {
class PropertyStepLineEnhancerLForm;
}

class PropertyStepLineEnhancerLForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyStepLineEnhancerLForm(QWidget *parent = 0);
    ~PropertyStepLineEnhancerLForm();

private slots:
    void on_pushButtonEditLibFolder_clicked();

    void on_tableWidgetLibList_clicked(const QModelIndex &index);

    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);

    void on_ButtonPickupTest_clicked();

    void on_ButtonPickupClearTest_clicked();

    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);

    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);

    void on_pushButtonSetFrom_clicked();

    void on_pushButtonGetBack_clicked();

    void on_pushButtonSetFromAll_clicked();

    void on_pushButtonGetBackAll_clicked();

    void on_pushButtonEditLibrary_clicked();

    void on_ButtonGenerateLibs_clicked();

    void on_radioButtonPickupArea_clicked();

    void on_radioButtonBlock_clicked();

    void on_radioButtonCalc_clicked();

    void on_radioButtonMatching_clicked();

    void on_ButtonLibSave_clicked();

private:
    Ui::PropertyStepLineEnhancerLForm *ui;
};

#endif // PROPERTYSTEPLINEENHANCERLFORM_H
