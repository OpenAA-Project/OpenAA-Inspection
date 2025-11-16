#ifndef CONTROLLERACCESSSELFFORM_H
#define CONTROLLERACCESSSELFFORM_H

#include <QWidget>
#include "XCommToTrigger.h"
#include "XServiceForLayers.h"

namespace Ui {
class ControllerAccessSelfForm;
}
class	ConfirmForm;

class ControllerAccessSelfForm : public QWidget, public ServiceForLayers
{
    Q_OBJECT
    CartonMenuForm	*Parent;
	CommToTrigger	Trigger;

	struct	TriggerInfo	    TriggerInfoData;
	struct	TriggerInfo	    BackupTriggerInfoData;
	struct	DropPassInfo	DropPassInfoData;
	struct	DropPassInfo	BackupDropPassInfoData;

public:
    explicit ControllerAccessSelfForm(LayersBase *Base,CartonMenuForm *p,QWidget *parent = nullptr);
    ~ControllerAccessSelfForm();

private slots:
    void on_horizontalSlider1_valueChanged(int value);
    void on_horizontalSlider2_valueChanged(int value);
    void on_horizontalSlider3_valueChanged(int value);
    void on_horizontalSlider4_valueChanged(int value);
    void on_spinBox1_valueChanged(int arg1);
    void on_spinBox2_valueChanged(int arg1);
    void on_spinBox3_valueChanged(int arg1);
    void on_spinBox4_valueChanged(int arg1);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::ControllerAccessSelfForm *ui;
};

#endif // CONTROLLERACCESSSELFFORM_H
