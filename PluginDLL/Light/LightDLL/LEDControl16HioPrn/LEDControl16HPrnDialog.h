#ifndef LEDCONTROL16HPRNDIALOG_H
#define LEDCONTROL16HPRNDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include "LEDControl16HioPrn.h"
#include "DeviceStruct.h"

namespace Ui {
class LEDControl16HPrnDialog;
}

class LEDControl16HioPanel;

class LEDControl16HPrnDialog : public QDialog
{
    Q_OBJECT
    
	LEDControl16HioPanel	*Panel;

public:
    explicit LEDControl16HPrnDialog(LEDControl16HioPanel *p,QWidget *parent = 0);
    ~LEDControl16HPrnDialog();
    
	void	ShowData(void);
	void	GetDataFromWindow(void);
private slots:
    void on_pushButtonSend_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonRequire_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonDefineSignals_clicked();
    void on_pushButtonShowTiming_clicked();

private:
    Ui::LEDControl16HPrnDialog *ui;
};

#endif // LEDCONTROL16HPRNDIALOG_H
