#ifndef CHOOSENEXTDIALOG_H
#define CHOOSENEXTDIALOG_H

#include <QDialog>

namespace Ui {
class ChooseNextDialog;
}

class ChooseNextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseNextDialog(QWidget *parent = 0);
    ~ChooseNextDialog();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::ChooseNextDialog *ui;
};

#endif // CHOOSENEXTDIALOG_H
