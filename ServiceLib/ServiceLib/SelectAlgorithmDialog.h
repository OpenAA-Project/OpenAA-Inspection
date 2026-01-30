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

#ifndef SELECTALGORITHMDIALOG_H
#define SELECTALGORITHMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XDataComponent.h"

namespace Ui {
class SelectAlgorithmDialog;
}

class SelectAlgorithmDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectAlgorithmDialog(LayersBase *base 
                                    ,const RootNameListContainer &_Selected
                                    ,QWidget *parent = nullptr);
    ~SelectAlgorithmDialog();

    RootNameListContainer   Selected;

private slots:
    void on_pushButtonAll_clicked();
    void on_pushButtonSelectOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectAlgorithmDialog *ui;

    virtual void resizeEvent(QResizeEvent *event)    override;
};

#endif // SELECTALGORITHMDIALOG_H