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


#ifndef SELECTLIBFOLDERDIALOG_H
#define SELECTLIBFOLDERDIALOG_H

#include <QDialog>


namespace Ui {
class SelectLibFolderDialog;
}
class	LayersBase;
class   LibFolderForm;

class SelectLibFolderDialog : public QDialog
{
    Q_OBJECT
    LibFolderForm	*pLibFolderForm;

public:
    explicit SelectLibFolderDialog(int LibType ,LayersBase * base, QWidget *parent = 0);
    ~SelectLibFolderDialog();

    int		SelectedLibFolderID;
    QString SelectedFolderName;

private slots:
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);

private:
    Ui::SelectLibFolderDialog *ui;
    virtual	void closeEvent ( QCloseEvent * event ) 	override;
};

#endif // SELECTLIBFOLDERDIALOG_H