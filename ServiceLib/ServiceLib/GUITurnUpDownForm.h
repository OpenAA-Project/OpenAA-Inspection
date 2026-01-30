/*
 * Copyright (C) 2023
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


#ifndef GUITURNUPDOWNFORM_H
#define GUITURNUPDOWNFORM_H

#include <QDialog>
#include <QTabWidget>
#include <QStackedWidget>

namespace Ui {
class GUITurnUpDownForm;
}
class	GUIFormBase;

class GUITurnUpDownForm : public QDialog
{
    Q_OBJECT

    QWidgetList	TabList;
    QTabWidget		*SelectedTabSheet;
    QStackedWidget	*SelectedStackedSheet;
    GUIFormBase		*Form;

public:
    explicit GUITurnUpDownForm(const QWidgetList &list,GUIFormBase *Form ,QWidget *parent = 0);
    ~GUITurnUpDownForm();

    void	ShowList(void);

private slots:
    void on_comboBTabSheet_currentIndexChanged(int index);
    void on_pushButtonOK_clicked();
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();

private:
    Ui::GUITurnUpDownForm *ui;
    virtual	void closeEvent ( QCloseEvent * event ) 	override;
};

#endif // GUITURNUPDOWNFORM_H