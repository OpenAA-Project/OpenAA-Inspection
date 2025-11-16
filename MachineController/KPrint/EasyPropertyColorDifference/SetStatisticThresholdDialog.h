#ifndef SETSTATISTICTHRESHOLDDIALOG_H
#define SETSTATISTICTHRESHOLDDIALOG_H

#include <QDialog>

namespace Ui {
class SetStatisticThresholdDialog;
}

class SetStatisticThresholdDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SetStatisticThresholdDialog(QWidget *parent = 0);
    ~SetStatisticThresholdDialog();
    
	double	SigmaH;
	double	SigmaS;
	double	SigmaV;

private slots:
    void on_pushButtonSet_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonPanelH_clicked();
    void on_pushButtonPanelS_clicked();
    void on_pushButtonPanelV_clicked();

private:
    Ui::SetStatisticThresholdDialog *ui;
};

#endif // SETSTATISTICTHRESHOLDDIALOG_H
