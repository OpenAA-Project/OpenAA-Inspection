#ifndef CREATECLASSFORM_H
#define CREATECLASSFORM_H

#include <QDialog>
#include "XTypeDef.h"
namespace Ui {
class CreateClassForm;
}

class CreateClassForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateClassForm(QWidget *parent = 0);
    ~CreateClassForm();

    void	Initial(const QString &Name);

    QString	ClassName;

    void	ShowData(void);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::CreateClassForm *ui;
};

#endif // CREATECLASSFORM_H
