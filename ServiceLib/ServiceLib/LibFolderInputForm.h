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

#ifndef LIBFOLDERINPUTFORM_H
#define LIBFOLDERINPUTFORM_H

#include <QDialog>

namespace Ui {
class LibFolderInputForm;
}
class	LayersBase;

class LibFolderInputForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit LibFolderInputForm(LayersBase *lbase ,const QString &folderName ,QWidget *parent = 0);
    ~LibFolderInputForm();

    QString	FolderName;
private slots:
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::LibFolderInputForm *ui;
};

#endif // LIBFOLDERINPUTFORM_H