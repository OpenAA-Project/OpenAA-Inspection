#ifndef SETLANGUAGEDETAILFORM_H
#define SETLANGUAGEDETAILFORM_H

#include <QDialog>

namespace Ui {
    class SetLanguageDetailForm;
}

class	LanguageClass;

class SetLanguageDetailForm : public QDialog
{
    Q_OBJECT

public:
    explicit SetLanguageDetailForm(	LanguageClass *a,QWidget *parent = 0);
    ~SetLanguageDetailForm();

	LanguageClass	*LangData;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SetLanguageDetailForm *ui;
};

#endif // SETLANGUAGEDETAILFORM_H
