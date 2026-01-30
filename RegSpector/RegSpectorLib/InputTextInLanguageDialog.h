/*
 * Copyright (C) 2021
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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