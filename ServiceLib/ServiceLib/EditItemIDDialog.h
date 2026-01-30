/*
 * Copyright (C) 2024
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

#ifndef EDITITEMIDDIALOG_H
#define EDITITEMIDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditItemIDDialog;
}

class   AlgorithmBase;

class EditItemIDDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    AlgorithmBase *ABase;
    bool    EnableMessage;
    int     Phase;
    int     Page ;
    int     Layer;
public:
    explicit EditItemIDDialog(LayersBase *base,QWidget *parent = nullptr);
    ~EditItemIDDialog();

    void    Initial(AlgorithmBase *ABase
                    ,int Phase ,int Page ,int Layer
                    ,int OldItemID, int NewItemID
                    ,bool EnableMessage=true);
    int     NewItemID;

private slots:
    void on_pushButtonUpdate_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditItemIDDialog *ui;
};

#endif // EDITITEMIDDIALOG_H