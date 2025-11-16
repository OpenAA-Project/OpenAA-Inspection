#ifndef CONTROLLERACCESSGFORM_H
#define CONTROLLERACCESSGFORM_H

#include <QWidget>
#include "XCommToTrigger.h"
#include "XServiceForLayers.h"

namespace Ui {
class ControllerAccessGForm;
}
class	ConfirmForm;

class ControllerAccessGForm : public QWidget, public ServiceForLayers
{
    Q_OBJECT
    CartonMenuForm	*Parent;
	CommToTrigger	Trigger;

	struct	TriggerInfo	TriggerInfoData;
	struct	TriggerInfo	BackupTriggerInfoData;

public:
    explicit ControllerAccessGForm(LayersBase *Base,CartonMenuForm *p,QWidget *parent = nullptr);
    ~ControllerAccessGForm();

private slots:
    void on_horizontalSlider1_valueChanged(int value);
    void on_horizontalSlider2_valueChanged(int value);
    void on_horizontalSlider3_valueChanged(int value);
    void on_horizontalSlider4_valueChanged(int value);
    void on_horizontalSliderDrop_valueChanged(int value);
    void on_spinBox1_valueChanged(int arg1);
    void on_spinBox2_valueChanged(int arg1);
    void on_spinBox3_valueChanged(int arg1);
    void on_spinBox4_valueChanged(int arg1);
    void on_spinBoxDrop_valueChanged(int arg1);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::ControllerAccessGForm *ui;
};

#endif // CONTROLLERACCESSGFORM_H
