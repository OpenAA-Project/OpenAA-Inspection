#ifndef LEDCONTROL16KDSBELTDIALOG_H
#define LEDCONTROL16KDSBELTDIALOG_H

#include <QDialog>

namespace Ui {
class LEDControl16KDSBeltDialog;
}

class LEDControl16KDSBeltPanel;
class LEDControl16KDSBeltDialog : public QDialog
{
    Q_OBJECT
    LEDControl16KDSBeltPanel	*Panel;
public:
    explicit LEDControl16KDSBeltDialog(LEDControl16KDSBeltPanel *p,QWidget *parent = nullptr);
    ~LEDControl16KDSBeltDialog();

private slots:
    void on_toolButtonStartSequence_clicked();
    void on_toolButtonBlueLight_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::LEDControl16KDSBeltDialog *ui;
};

#endif // LEDCONTROL16KDSBELTDIALOG_H
