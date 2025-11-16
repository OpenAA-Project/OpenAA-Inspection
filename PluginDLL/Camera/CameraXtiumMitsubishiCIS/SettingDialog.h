#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}
class  CameraXtiumMitsubishiCIS;

class SettingDialog : public QDialog
{
    Q_OBJECT
    
	CameraXtiumMitsubishiCIS	*Cam;

	QString			ConfigFileName;
	int				CameraType;	/*	0:KD6R309AX3
									1:KD6R617AX3
									2:KD6R926AX3
								*/
	int				LineClock;
	int				BoardCount;
	int				Resolution;
	bool			OuterTrigger;
	int				LEDControl;
	double			LEDDutyFull;
	double			LEDDutyA;
	double			LEDDutyB;
	int				LEDDivide;
	bool			Gain;
	double			GainR;
	double			GainG;
	double			GainB;
	bool			YDirection;
	bool			Gamma;

	int				EvenOffsetY	;
	int				OddOffsetY	;
	bool			ModeAdjustWhite;

public:
    explicit SettingDialog(CameraXtiumMitsubishiCIS *cam ,QWidget *parent = 0);
    ~SettingDialog();
    
private slots:
    void on_pushButtonConfigFileName_clicked();
    void on_checkBoxGainMode_clicked();
    void on_comboBoxType_currentIndexChanged(int index);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonAdjustBlack_clicked();
    void on_pushButtonAdjustWhite_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
