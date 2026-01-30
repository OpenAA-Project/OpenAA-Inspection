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

#ifndef ADDSOURCEITEMDIALOG_H
#define ADDSOURCEITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include"XPropertySkipMarkPacket.h"

namespace Ui {
class AddSourceItemDialog;
}

class AddSourceItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	int GlobalPage;
	int	Layer;
	AlgorithmBasePointerContainer AlgoBases;
public:
    explicit AddSourceItemDialog(LayersBase *Base,int GlobalPage ,int _Layer,QWidget *parent = 0);
    ~AddSourceItemDialog();

	QString	AlgoRoot;
	QString	AlgoName;
	int		ItemID;

private slots:
    void on_pushButtonSearch_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::AddSourceItemDialog *ui;
};

#endif // ADDSOURCEITEMDIALOG_H