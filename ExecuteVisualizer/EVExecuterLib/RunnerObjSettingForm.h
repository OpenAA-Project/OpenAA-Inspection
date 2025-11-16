#ifndef RUNNEROBJSETTINGFORM_H
#define RUNNEROBJSETTINGFORM_H

#include <QDialog>

namespace Ui {
    class RunnerObjSettingForm;
}

class	RunnerObject;

class RunnerObjSettingForm : public QDialog
{
    Q_OBJECT

	RunnerObject	*Obj;
public:
    explicit RunnerObjSettingForm(RunnerObject *obj ,QWidget *parent = 0);
    ~RunnerObjSettingForm();

private slots:
    void on_pushButtonSetting_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonDelete_clicked();

private:
    Ui::RunnerObjSettingForm *ui;
};

#endif // RUNNEROBJSETTINGFORM_H
