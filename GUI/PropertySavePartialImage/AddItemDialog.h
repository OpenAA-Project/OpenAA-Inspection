#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>

namespace Ui {
class AddItemDialog;
}

class AddItemDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddItemDialog(QWidget *parent = 0);
    ~AddItemDialog();
    
private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::AddItemDialog *ui;
};

#endif // ADDITEMDIALOG_H
