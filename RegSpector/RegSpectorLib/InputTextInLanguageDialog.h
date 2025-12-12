#ifndef INPUTTEXTINLANGUAGEDIALOG_H
#define INPUTTEXTINLANGUAGEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QString>
#include "XCSV.h"
#include "NList.h"
#include "XServiceRegSpector.h"

class InputTextInLanguageDialog : public QDialog
{
    Q_OBJECT

    QSqlDatabase    database;
public:
    TextContainer   TextCode;

    explicit InputTextInLanguageDialog(const QSqlDatabase &dbase ,int TextClass ,int IndexAutoCount ,QWidget *parent = nullptr);
    explicit InputTextInLanguageDialog(const QSqlDatabase &dbase ,const TextContainer &text ,QWidget *parent = nullptr);
    ~InputTextInLanguageDialog();

protected:
    virtual void resizeEvent(QResizeEvent *event)  override;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void    SlotDefaultChecked(int column,int row ,bool b);
private:
    Ui::InputTextInLanguageDialog *ui;
};

QString GetTextInLanguage(const QSqlDatabase &dbase ,int TextClass ,int IndexAutoCount,const QString &CountryCode);
bool StoreTextInLanguageInDB(const QSqlDatabase &dbase ,int TextClass ,int IndexAutoCount,const TextContainer &TextCode);
bool LoadTextInLanguageFromDB(const QSqlDatabase &dbase ,int TextClass ,int IndexAutoCount,TextContainer &TextCode);

#endif // INPUTTEXTINLANGUAGEDIALOG_H
