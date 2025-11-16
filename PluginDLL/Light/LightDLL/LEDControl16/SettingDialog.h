#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include "LEDControl16.h"

namespace Ui {
class SettingDialog;
}


class SettingDialog : public QDialog
{
    Q_OBJECT
	LEDControl16Panel	*Panel;
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

	LineWindow	*LineData[256];

	int	LastLight;

public:
    explicit SettingDialog(LEDControl16Panel *p,QWidget *parent = 0);
    ~SettingDialog();

	QProgressBar	*GetBar(void);

private slots:
    void on_toolButtonRed_clicked();
    void on_toolButtonGreen_clicked();
    void on_toolButtonBlue_clicked();
    void on_pushButtonTransfer_clicked();
    void on_toolButtonON_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonSetAll_clicked();

    void on_pushButtonWriteEPROM_clicked();

    void on_pushButtonShowIO_clicked();

    void on_pushButtonTemporaryON_clicked();

private:
    Ui::SettingDialog *ui;


	int	GetCurrentPortNumber(void);
	void	InitialWindow	 (LEDControl16Panel::PortData &Data);
	void	ShowData		 (int n,LEDControl16Panel::PortData &Data ,int PatternNumber);
	void	GetDataFromWindow(int n,LEDControl16Panel::PortData &Data ,int PatternNumber);
	QString	GetColorStr(int ColorType);
};

#endif // SETTINGDIALOG_H
