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

#ifndef ACTIVATIONDIALOG_H
#define ACTIVATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ActivationDialog;
}

class   TypeDefinition;

class ActivationDialog : public QDialog
{
    Q_OBJECT
    TypeDefinition  *Parent;

public:
    explicit ActivationDialog(TypeDefinition *p,QWidget *parent = 0);
    ~ActivationDialog();
    
private slots:
    void on_checkBoxOrderCode_clicked();
    void on_checkBoxLicenseFile_clicked();
    void on_checkBoxActivationCode_clicked();
    void on_pushButtonActivateByOrderCode_clicked();
    void on_pushButtonSelectLicenseFiile_clicked();
    void on_pushButtonActivateByLicenseFile_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonLoadLicenseFiile_clicked();
    void on_pushButtonWriteReqActivationFile_clicked();
    void on_pushButtonLoadActivationFile_clicked();

private:
    Ui::ActivationDialog *ui;

    void    SetFrame(void);
    void    ShowResult(void);
};

#endif // ACTIVATIONDIALOG_H