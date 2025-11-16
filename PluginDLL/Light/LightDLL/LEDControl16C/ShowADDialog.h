#ifndef SHOWADDIALOG_H
#define SHOWADDIALOG_H

#include <QDialog>

namespace Ui {
class ShowADDialog;
}

class	LEDControl16CPanel;

class ShowADDialog : public QDialog
{
    Q_OBJECT

	LEDControl16CPanel	*Panel;
public:
    explicit ShowADDialog(LEDControl16CPanel *p,QWidget *parent = 0);
    ~ShowADDialog();

private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonReqAD_clicked();

private:
    Ui::ShowADDialog *ui;
};

#endif // SHOWADDIALOG_H
