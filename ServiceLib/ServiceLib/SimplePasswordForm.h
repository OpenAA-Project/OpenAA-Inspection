#ifndef SIMPLEPASSWORDFORM_H
#define SIMPLEPASSWORDFORM_H

#include <QDialog>

namespace Ui {
class SimplePasswordForm;
}

class SimplePasswordForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit SimplePasswordForm(QWidget *parent = 0);
    ~SimplePasswordForm();

    QString	Password;
private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::SimplePasswordForm *ui;
};

#endif // SIMPLEPASSWORDFORM_H
