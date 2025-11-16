#ifndef SHOWCONNECTIONINFOFORM_H
#define SHOWCONNECTIONINFOFORM_H

#include <QDialog>

namespace Ui {
    class ShowConnectionInfoForm;
}

class	GlueRunner;

class ShowConnectionInfoForm : public QDialog
{
    Q_OBJECT

	GlueRunner *Glue;
public:
    explicit ShowConnectionInfoForm(GlueRunner *G ,QWidget *parent = 0);
    ~ShowConnectionInfoForm();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonDelete_clicked();

private:
    Ui::ShowConnectionInfoForm *ui;
};

#endif // SHOWCONNECTIONINFOFORM_H
