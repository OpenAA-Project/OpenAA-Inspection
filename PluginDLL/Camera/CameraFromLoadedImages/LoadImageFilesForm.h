/*
 * Copyright (C) 2025
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

#ifndef LOADIMAGEFILESFORM_H
#define LOADIMAGEFILESFORM_H

#include <QWidget>

namespace Ui {
class LoadImageFilesForm;
}

class CameraFromLoadedImages;

class LoadImageFilesForm : public QWidget
{
    Q_OBJECT

    CameraFromLoadedImages  *Parent;
    QStringList FileLists;
public:
    explicit LoadImageFilesForm(CameraFromLoadedImages *p,QWidget *parent = nullptr);
    ~LoadImageFilesForm();

private slots:
    void on_pushButtonSeletFiles_clicked();
    void on_pushButtonLoadImages_clicked();
    void on_pushButtonTransferImages_clicked();
    void on_pushButtonResetStrategicNumber_clicked();
    void on_pushButtonResetScanPhaseNumber_clicked();

    void on_pushButtonLoadResetTransfer_clicked();

private:
    Ui::LoadImageFilesForm *ui;
};

#endif // LOADIMAGEFILESFORM_H