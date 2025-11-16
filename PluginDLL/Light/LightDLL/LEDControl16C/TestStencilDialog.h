#ifndef TESTSTENCILDIALOG_H
#define TESTSTENCILDIALOG_H

#include <QDialog>

namespace Ui {
class TestStencilDialog;
}
class	LEDControl16CPanel;

class TestStencilDialog : public QDialog
{
    Q_OBJECT

	LEDControl16CPanel	*Panel;
	int				LastUnit;
	int				LastBoard;
public:
    explicit TestStencilDialog(LEDControl16CPanel *p,QWidget *parent = 0);
    ~TestStencilDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_toolButtonRelay_clicked();
    void on_pushButtonReqCameraResolution_clicked();
    void on_pushButtonSetCameraResolution_clicked();
    void on_pushButtonReqMotorCounter_clicked();
    void on_pushButtonReqEnableComparator_clicked();
    void on_pushButtonSetEnableComparator_clicked();
    void on_spinBoxUnitNo_valueChanged(int arg1);
    void on_spinBoxBoardNo_valueChanged(int arg1);

    void on_pushButtonAllOff_clicked();

    void on_pushButtonCalc_clicked();

    void on_pushButtonSetMotorCounter_clicked();

private:
    Ui::TestStencilDialog *ui;
};

#endif // TESTSTENCILDIALOG_H
