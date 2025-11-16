#ifndef CREATEPASSWORDFORM_H
#define CREATEPASSWORDFORM_H

#include <QDialog>
#include "XTypeDef.h"
namespace Ui {
class CreatePasswordForm;
}

class CreatePasswordForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreatePasswordForm(QWidget *parent = 0);
    ~CreatePasswordForm();

    QString	Password;

    void	Initial(const QString &Name);
    void	ShowData(void);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::CreatePasswordForm *ui;
};

#endif // CREATEPASSWORDFORM_H
