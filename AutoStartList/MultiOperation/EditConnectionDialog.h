#ifndef EDITCONNECTIONDIALOG_H
#define EDITCONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class EditConnectionDialog;
}

class EditConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditConnectionDialog(QWidget *parent = 0);
    ~EditConnectionDialog();

private slots:
    void on_pushButtonSet_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::EditConnectionDialog *ui;
};

#endif // EDITCONNECTIONDIALOG_H
