#ifndef LEDCONTROL16JPRNDIALOG_H
#define LEDCONTROL16JPRNDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include "LEDControl16JioPrn.h"
#include "DeviceStruct.h"

namespace Ui {
class LEDControl16JPrnDialog;
}

class LEDControl16JioPanel;

class LEDControl16JPrnDialog : public QDialog
{
    Q_OBJECT
    
	LEDControl16JioPanel	*Panel;

public:
    explicit LEDControl16JPrnDialog(LEDControl16JioPanel *p,QWidget *parent = 0);
    ~LEDControl16JPrnDialog();
    
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
    Ui::LEDControl16JPrnDialog *ui;
};

#endif // LEDCONTROL16JPRNDIALOG_H
