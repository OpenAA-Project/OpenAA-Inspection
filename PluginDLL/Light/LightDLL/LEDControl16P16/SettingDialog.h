#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include "LEDControl16P16.h"

namespace Ui {
class SettingDialog;
}


class SettingDialog : public QDialog
{
    Q_OBJECT
	LEDControl16P16Panel	*Panel;
	QTimer	TM;

	class	LineWindow
	{
	public:
		QLabel		Label;
		QSpinBox	EditValue;
		QLineEdit	EditComment;

		LineWindow(QWidget *parent);
		void	SetY(int n);
		void	Show(void);
	};

	LineWindow	*LineData[16];

	int		LastLightNo;
	int		LastRegPatternNo;
	int		LastShowPaatternNo;


public:
    explicit SettingDialog(LEDControl16P16Panel *p,QWidget *parent = 0);
    ~SettingDialog();

	QProgressBar	*GetBar(void);

private slots:
    void on_pushButtonTransfer_clicked();
    void on_toolButtonON_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonShowIO_clicked();
    void on_comboBoxPatternNo_currentIndexChanged(int index);
    void on_comboBoxPatternNoOperation_currentIndexChanged(int index);
    void on_comboBoxLightNo_currentIndexChanged(int index);

private:
    Ui::SettingDialog *ui;

	void	InitialWindow	 (int LightNo ,int PatternNo);
	void	ShowData		 (int LightNo ,int PatternNo);
	void	GetDataFromWindow(int LightNo ,int PatternNo);

	int		GetCurrentLightNo(void);
	int		GetCurrentRegPattern(void);
	int		GetCurrentShowPattern(void);
};

#endif // SETTINGDIALOG_H
