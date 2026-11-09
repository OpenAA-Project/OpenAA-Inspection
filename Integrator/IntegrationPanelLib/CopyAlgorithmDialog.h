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

#ifndef COPYALGORITHMDIALOG_H
#define COPYALGORITHMDIALOG_H

#include <QDialog>
#include <QPushButton>
#include "XServiceForLayers.h"

namespace Ui {
class CopyAlgorithmDialog;
}

class IntegrationAlgoSimpleImagePanel;

class SlaveButton : public QPushButton
{
    Q_OBJECT

    int SlaveNo;
public:
	SlaveButton(int _SlaveNo);
	~SlaveButton(void);

signals:
    void    SignalClicked(int slaveNo);
private slots:
    void    SlotClicked(bool);
};


class CopyAlgorithmDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    IntegrationAlgoSimpleImagePanel *Parent;
    SlaveButton     *RxSlaveButton[100];
    QPushButton     *TxButtonDim[4];

public:
    explicit CopyAlgorithmDialog(LayersBase *base
                                ,IntegrationAlgoSimpleImagePanel *P
                                ,QWidget *parent = nullptr);
    ~CopyAlgorithmDialog();

private slots:
    void on_toolButtonRx_clicked();
    void on_toolButtonTx_clicked();
    void on_pushButtonExeTx_clicked();
    void    SlotRxClicked(int slaveNo);

private:
    Ui::CopyAlgorithmDialog *ui;
};

#endif // COPYALGORITHMDIALOG_H