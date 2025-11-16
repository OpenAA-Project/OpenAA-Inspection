#ifndef SETLANGUAGEFORM_H
#define SETLANGUAGEFORM_H

#include <QDialog>
#include <QModelIndex>

namespace Ui {
    class SetLanguageForm;
}
class	LanguagePack;

class SetLanguageForm : public QDialog
{
    Q_OBJECT

	LanguagePack	&LangPack;
public:
    explicit SetLanguageForm(LanguagePack &Lang,QWidget *parent = 0);
    ~SetLanguageForm();

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonInsertNew_clicked();
    void on_pushButtonChange_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SetLanguageForm *ui;

	void ShowList(void);
};

#endif // SETLANGUAGEFORM_H
