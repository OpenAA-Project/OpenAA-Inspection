#ifndef INPUTCODEDIALOG_H
#define INPUTCODEDIALOG_H

#include <QDialog>

namespace Ui {
class InputCodeDialog;
}

class InputCodeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputCodeDialog(QWidget *parent = 0);
    ~InputCodeDialog();

	QString		BarCode;
    
private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::InputCodeDialog *ui;
};

#endif // INPUTCODEDIALOG_H
