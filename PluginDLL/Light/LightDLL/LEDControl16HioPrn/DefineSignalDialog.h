#ifndef DEFINESIGNALDIALOG_H
#define DEFINESIGNALDIALOG_H

#include <QDialog>

namespace Ui {
class DefineSignalDialog;
}
class LEDControl16HioPanel;

class DefineSignalDialog : public QDialog
{
    Q_OBJECT
    LEDControl16HioPanel	*Panel;
public:
    explicit DefineSignalDialog(LEDControl16HioPanel *p,QWidget *parent = 0);
    ~DefineSignalDialog();
    
private slots:
    void on_pushButtonUpdate_clicked();

private:
    Ui::DefineSignalDialog *ui;
};

#endif // DEFINESIGNALDIALOG_H
