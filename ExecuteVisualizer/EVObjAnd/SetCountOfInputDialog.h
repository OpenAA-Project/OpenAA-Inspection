#ifndef SETCOUNTOFINPUTDIALOG_H
#define SETCOUNTOFINPUTDIALOG_H

#include <QDialog>

namespace Ui {
    class SetCountOfInputDialog;
}

class SetCountOfInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetCountOfInputDialog(int inputNumb ,QWidget *parent = 0);
    ~SetCountOfInputDialog();

	int	InputNumb;
private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::SetCountOfInputDialog *ui;
};

#endif // SETCOUNTOFINPUTDIALOG_H
