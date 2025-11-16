#ifndef TESTSTENCILDIALOG_H
#define TESTSTENCILDIALOG_H

#include <QDialog>

namespace Ui {
class TestStencilDialog;
}
class	LEDControl16DPanel;

class TestStencilDialog : public QDialog
{
    Q_OBJECT

	LEDControl16DPanel	*Panel;
	int				LastUnit;
	int				LastBoard;
public:
    explicit TestStencilDialog(LEDControl16DPanel *p,QWidget *parent = 0);
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

	virtual	void	showEvent (QShowEvent * event)		override;
	virtual	void 	closeEvent ( QCloseEvent * event )	override;
};

#endif // TESTSTENCILDIALOG_H
