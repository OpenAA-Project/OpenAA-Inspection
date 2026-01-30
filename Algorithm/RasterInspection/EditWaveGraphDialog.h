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

#ifndef EDITWAVEGRAPHDIALOG_H
#define EDITWAVEGRAPHDIALOG_H

#include <QDialog>
#include <QString>
#include "XServiceForLayers.h"

namespace Ui {
class EditWaveGraphDialog;
}

class ReferencePDF;

class EditWaveGraphDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    ReferencePDF *RefPDF;
    QImage      *GraphImage;
public:
    explicit EditWaveGraphDialog(ReferencePDF *R,LayersBase *Base
                                ,QWidget *parent = nullptr);
    ~EditWaveGraphDialog();

    void    SetDeletable(bool Deletable);
    QString ReferenceName;

private slots:
    void on_pushButtonDelete_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonUpdateName_clicked();

private:
    Ui::EditWaveGraphDialog *ui;

    void MakeGraph(void);
};

#endif // EDITWAVEGRAPHDIALOG_H