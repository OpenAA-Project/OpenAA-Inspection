#ifndef IODELIVERERDIALOG_H
#define IODELIVERERDIALOG_H

#include <QDialog>

namespace Ui {
class IODelivererDialog;
}

class	LEDControl16CPanel;

class IODelivererDialog : public QDialog
{
    Q_OBJECT

	LEDControl16CPanel	*Panel;
public:
    explicit IODelivererDialog(LEDControl16CPanel *p,QWidget *parent = 0);
    ~IODelivererDialog();

private slots:
    void on_pushButtonStart_clicked();

private:
    Ui::IODelivererDialog *ui;
};

#endif // IODELIVERERDIALOG_H
