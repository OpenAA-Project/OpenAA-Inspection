/*
 * Copyright (C) 2017
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

#ifndef EDITLINEMOVEDIALOG_H
#define EDITLINEMOVEDIALOG_H

#include <QDialog>
#include "XMeasureLineMove.h"
#include "XMeasureLineMovePacket.h"
#include "XServiceForLayers.h"

namespace Ui {
    class EditLineMoveDialog;
}

class EditLineMoveDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
	MeasureLineMoveThreshold	*ThreData;
	QString						ItemName;

    explicit EditLineMoveDialog(LayersBase *base, QString &itemName ,MeasureLineMoveThreshold *_ThreData ,QWidget *parent = 0);
    ~EditLineMoveDialog();

private slots:
        void on_ButtonOK_clicked();
        void on_ButtonCancel_clicked();

private:
    Ui::EditLineMoveDialog *ui;
};

#endif // EDITLINEMOVEDIALOG_H