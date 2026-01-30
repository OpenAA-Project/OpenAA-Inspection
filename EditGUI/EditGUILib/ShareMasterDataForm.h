/*
 * Copyright (C) 2014
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

#ifndef SHAREMASTERDATAFORM_H
#define SHAREMASTERDATAFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XServiceForLayers.h"

namespace Ui {
class ShareMasterDataForm;
}

class ShareMasterDataForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
	int	IndexNumber;
public:
    explicit ShareMasterDataForm(LayersBase *Base,QWidget *parent = 0);
    ~ShareMasterDataForm();
    
	void	ShowGrid(void);
	void	GetFromWindow(int machineID);

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_comboBoxMachineID_currentIndexChanged(int index);

    void on_pushButtonAddDestination_clicked();

    void on_pushButtonDelDestination_clicked();

private:
    Ui::ShareMasterDataForm *ui;
};

#endif // SHAREMASTERDATAFORM_H