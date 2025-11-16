#ifndef IODELIVERERDIALOG_H
#define IODELIVERERDIALOG_H

#include <QDialog>

namespace Ui {
class IODelivererDialog;
}

class	LEDControl16EPanel;

class IODelivererDialog : public QDialog
{
    Q_OBJECT

	LEDControl16EPanel	*Panel;
public:
    explicit IODelivererDialog(LEDControl16EPanel *p,QWidget *parent = 0);
    ~IODelivererDialog();

private slots:
    void on_pushButtonStart_clicked();

private:
    Ui::IODelivererDialog *ui;
};

#endif // IODELIVERERDIALOG_H
