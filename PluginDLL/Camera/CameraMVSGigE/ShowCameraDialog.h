#ifndef SHOWCAMERADIALOG_H
#define SHOWCAMERADIALOG_H

#include <QDialog>
#include "CameraMVSGigE.h"

namespace Ui {
class ShowCameraDialog;
}

class  CameraMVSGigE;

class ShowCameraDialog : public QDialog
{
    Q_OBJECT

    CameraMVSGigE   *Parent;
public:

	float		ExposureTime;
	float		Gain;
	float		FrameRate;
	bool		bSoftWareTriggerCheck;
    int			TriggerMode;                       // en:Trigger Mode
    int			TriggerSource;                     // en:Trigger Source

    explicit ShowCameraDialog(CameraMVSGigE *p,QWidget *parent = nullptr);
    ~ShowCameraDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::ShowCameraDialog *ui;
};

#endif // SHOWCAMERADIALOG_H
