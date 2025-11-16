#ifndef ADJUSTTRIGGERFORM_H
#define ADJUSTTRIGGERFORM_H

#include <QWidget>
#include "XCommToTrigger.h"

namespace Ui {
class AdjustTriggerForm;
}

class	CartonMenuForm;


class AdjustTriggerForm : public QWidget
{
    Q_OBJECT
    CartonMenuForm	*Parent;
	CommToTrigger	Trigger;

	struct	TriggerInfo	TriggerInfoData;
	struct	TriggerInfo	BackupTriggerInfoData;

public:
    explicit AdjustTriggerForm(CartonMenuForm *p ,QWidget *parent = 0);
    ~AdjustTriggerForm();
    
private slots:
    void on_horizontalSlider1_valueChanged(int value);
    void on_horizontalSlider2_valueChanged(int value);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_spinBox1_valueChanged(int arg1);
    void on_spinBox2_valueChanged(int arg1);
    void on_horizontalSliderDrop_valueChanged(int value);
    void on_spinBoxDrop_valueChanged(int arg1);
    void on_horizontalSlider3_valueChanged(int value);
    void on_horizontalSlider4_valueChanged(int value);
    void on_spinBox3_valueChanged(int arg1);
    void on_spinBox4_valueChanged(int arg1);

private:
    Ui::AdjustTriggerForm *ui;


};

#endif // ADJUSTTRIGGERFORM_H
