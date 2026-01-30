/*
 * Copyright (C) 2015
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

#ifndef SHOWTABLEDIALOG_H
#define SHOWTABLEDIALOG_H

#include <QDialog>

namespace Ui {
class ShowTableDialog;
}
class	XMLElementRoot;
class	XMLServerComm;

class ShowTableDialog : public QDialog
{
    Q_OBJECT
	XMLServerComm	*ServerCommData;
	XMLElementRoot	*SRoot;
public:
    explicit ShowTableDialog(XMLElementRoot *s, XMLServerComm *ServerCommDataParent ,QWidget *parent = 0);
    ~ShowTableDialog();

private slots:
    void on_pushButtonSave_clicked();
    void on_pushButtonRemove_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::ShowTableDialog *ui;
};

#endif // SHOWTABLEDIALOG_H