#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QLineEdit>
#include "LEDControl32.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

	QSpinBox	*pEditBrightnrss[LEDCountInSheet];
	QLineEdit	*pEditText[LEDCountInSheet];
	LEDControl32	*Panel;
	LEDControl32::LEDDataStruct	LEDData;

	int	LastPatternNo;
	int	LastBoardNo;

public:
    explicit SettingDialog(LEDControl32 *Src ,QWidget *parent = 0);
    ~SettingDialog();

	void	ShowCurrent();
	void	StoreCurrent(int BoardNo ,int PatternNo);

private slots:
    void on_comboBoxPattern_currentIndexChanged(int index);
    void on_comboBoxBoard_currentIndexChanged(int index);
    void on_verticalSliderBrightnrss_valueChanged(int value);
    void on_spinBoxBrightness_valueChanged(int arg1);
    void on_pushButtonTransfer_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_toolButtonLightON_clicked();

    void on_radioButtonOutputA_clicked();

    void on_radioButtonOutputB_clicked();

    void on_comboBoxPatternBuffA_currentIndexChanged(int index);

    void on_comboBoxPatternBuffB_currentIndexChanged(int index);

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
