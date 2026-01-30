/*
 * Copyright (C) 2012
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