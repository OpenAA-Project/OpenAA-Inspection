/*
 * Copyright (C) 2022
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

#ifndef SELECTLOTFORM_H
#define SELECTLOTFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XServiceForLayers.h"
#include "XIntegrationBase.h"
#include "PQSystemService.h"

namespace Ui {
class SelectLotForm;
}
class LotList;


class SelectLotForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
public:
    NPListPack<LotListWithResult>	LotContainer;
	LotListWithResult	*CurrentLot;

    explicit SelectLotForm(LayersBase *Base ,QWidget *parent = 0);
    ~SelectLotForm();
    
	void	Clear(void);
	void	Update();

signals:
	void	SignalSelectLine();
private slots:
    void on_tableWidget_itemSelectionChanged();
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonSearch_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectLotForm *ui;

protected:
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // SELECTLOTFORM_H