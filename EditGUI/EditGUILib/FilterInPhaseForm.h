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

#ifndef FILTERINPHASEFORM_H
#define FILTERINPHASEFORM_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"

namespace Ui {
class FilterInPhaseForm;
}

class FilterInPhaseForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    int	PhaseNo;
    int	PageNo;
public:
    explicit FilterInPhaseForm(LayersBase *base ,int phaseNo,int pageNo,QWidget *parent = 0);
    ~FilterInPhaseForm();
    
private slots:
    void on_listWidgetFilterInstance_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonGet_clicked();
    void on_pushButtonReturn_clicked();

private:
    Ui::FilterInPhaseForm *ui;

    void	ShowFilterBank(void);
    void	ShowFilterInstance(void);
};

#endif // FILTERINPHASEFORM_H