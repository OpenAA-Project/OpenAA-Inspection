#ifndef SETDEFAULTFORM_H
#define SETDEFAULTFORM_H

#include <QDialog>

namespace Ui {
    class SetDefaultForm;
}

class SetDefaultForm : public QDialog
{
    Q_OBJECT

public:
    explicit SetDefaultForm(QWidget *parent = 0);
    ~SetDefaultForm();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SetDefaultForm *ui;
};

#endif // SETDEFAULTFORM_H
