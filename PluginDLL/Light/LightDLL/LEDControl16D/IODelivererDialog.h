#ifndef IODELIVERERDIALOG_H
#define IODELIVERERDIALOG_H

#include <QDialog>

namespace Ui {
class IODelivererDialog;
}

class	LEDControl16DPanel;

class IODelivererDialog : public QDialog
{
    Q_OBJECT

	LEDControl16DPanel	*Panel;
public:
    explicit IODelivererDialog(LEDControl16DPanel *p,QWidget *parent = 0);
    ~IODelivererDialog();

private slots:
    void on_pushButtonStart_clicked();

private:
    Ui::IODelivererDialog *ui;
};

#endif // IODELIVERERDIALOG_H
