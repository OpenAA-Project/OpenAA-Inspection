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

#ifndef EDITFILTERBANK_H
#define EDITFILTERBANK_H

#include <QWidget>
#include <QModelIndex>
#include"XParamGlobal.h"
#include "XServiceForLayers.h"
#include "WEditParameterTab.h"

namespace Ui {
class EditFilterBank;
}

class EditFilterBank : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    WEditParameterTab	*WTab;
public:
    explicit EditFilterBank(LayersBase *base ,QWidget *parent = 0);
    ~EditFilterBank();

    QStringList		FilterFileNames;

signals:
    void	SignalClose();
private slots:
    void on_tableWidgetFilter_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonLoadFiles_clicked();
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();
    void on_pushButtonDelete_clicked();

private:
    Ui::EditFilterBank *ui;

    void	ShowGrid(void);};

#endif // EDITFILTERBANK_H