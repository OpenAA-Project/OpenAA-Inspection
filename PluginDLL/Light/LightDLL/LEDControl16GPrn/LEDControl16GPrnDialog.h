#ifndef LEDCONTROL16GPRNDIALOG_H
#define LEDCONTROL16GPRNDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include "LEDControl16GPrn.h"
#include "DeviceStruct.h"

namespace Ui {
class LEDControl16GPrnDialog;
}

class LEDControl16GPanel;

class LEDControl16GPrnDialog : public QDialog
{
    Q_OBJECT
    
	LEDControl16GPanel	*Panel;

public:
    explicit LEDControl16GPrnDialog(LEDControl16GPanel *p,QWidget *parent = 0);
    ~LEDControl16GPrnDialog();
    
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
    Ui::LEDControl16GPrnDialog *ui;
};

#endif // LEDCONTROL16GPRNDIALOG_H
