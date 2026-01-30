/*
 * Copyright (C) 2020
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

#ifndef BLADELOGFORM_H
#define BLADELOGFORM_H

#include <QWidget>
#include <QResizeEvent>
#include "XServiceForLayers.h"
#include "XDateTime.h"
#include "libxl.h"
using namespace libxl;

namespace Ui {
class BladeLogForm;
}
class GraphTrendKidaForm;

const	int	MaxNGCount=1000;

class BladeLogForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    GraphTrendKidaForm	*Parent;
	int		CountGraphLine;
	int		BladeItemID[100];
	int		*InspectionID;
	double	*NGList[100];
	int		RowCount;
	XDateTime			*InspectionTime;
	QStringList	Headers;

public:
    explicit BladeLogForm(GraphTrendKidaForm *p ,LayersBase *Base ,QWidget *parent = 0);
    ~BladeLogForm();
    
private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonExcel_clicked();

private:
    Ui::BladeLogForm *ui;

	Book	*XLSXBook;
	Sheet	*XLSXSheet;
	Format	*Lang;
	Font	*Fnt;

	virtual	void resizeEvent ( QResizeEvent * event ) override;
	void	WriteCell (int Row, int Col ,const QString &Str);
	void	WriteCellV(int Row, int Col ,const QVariant &Data);
};

#endif // BLADELOGFORM_H