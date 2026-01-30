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

#ifndef PANELMAXSTOCKFORM_H
#define PANELMAXSTOCKFORM_H

#include "XGUIFormBase.h"
#include <QStringList>
#include <QLabel>
#include <QSpinBox>

namespace Ui {
class PanelMaxStockForm;
}

class	SignalOperandInt;

class PanelMaxStockForm : public GUIFormBase
{
    Q_OBJECT

	SignalOperandInt	**iRegMaxStock;
public:
	int		*CurrentMaxStock;
	int		TopRegNumber;
	QStringList	StockStringList;
	int			StockStringListCount;

	class	StockLine : public QFrame
	{
	public:
		int			Row;
		QLabel		StockName;
		QSpinBox	StockValue;

		StockLine(PanelMaxStockForm *parent,int row);
	};
	StockLine	**StockLineData;

    explicit PanelMaxStockForm(LayersBase *Base ,QWidget *parent = 0);
    ~PanelMaxStockForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
private slots:
    void on_pushButtonSet_clicked();
	void	OperandChanged();
private:
    Ui::PanelMaxStockForm *ui;
};

#endif // PANELMAXSTOCKFORM_H