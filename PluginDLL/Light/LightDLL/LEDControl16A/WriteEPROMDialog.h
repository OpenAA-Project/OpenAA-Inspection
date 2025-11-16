#ifndef WRITEEPROMDIALOG_H
#define WRITEEPROMDIALOG_H

#include <QDialog>
#include "LightUnitStruct.h"

namespace Ui {
class WriteEPROMDialog;
}
class	LEDControl16APanel;
class WriteEPROMDialog : public QDialog
{
    Q_OBJECT

	LEDControl16APanel	*Panel;
	struct        LightUnit   EPROMData;

public:
    explicit WriteEPROMDialog(LEDControl16APanel *p,QWidget *parent = 0);
    ~WriteEPROMDialog();

private slots:
    void on_comboBoxSelectBoard_currentIndexChanged(int index);
    void on_comboBoxSelectPort_currentIndexChanged(int index);
    void on_spinBoxLineCount_valueChanged(int arg1);
    void on_comboBoxLineNumber_currentIndexChanged(int index);
    void on_comboBoxColorType_currentIndexChanged(int index);
    void on_spinBoxMaxCurrent_valueChanged(int arg1);
    void on_pushButtonRead_clicked();
    void on_pushButtonWrite_clicked();

    void on_pushButtonSetAll_clicked();

    void on_pushButtonReadStatus_clicked();

private:
    Ui::WriteEPROMDialog *ui;

	void ShowData(void);
};

#endif // WRITEEPROMDIALOG_H
