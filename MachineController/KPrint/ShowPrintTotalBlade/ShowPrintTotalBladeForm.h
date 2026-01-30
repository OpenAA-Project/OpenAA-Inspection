/*
 * Copyright (C) 2024
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

#ifndef SHOWPRINTTOTALBLADEFORM_H
#define SHOWPRINTTOTALBLADEFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "libxl.h"
using namespace libxl;

namespace Ui {
class ShowPrintTotalBladeForm;
}


#define		MaxCountOfMeasureBlade	10

class	BladeResult
{
public:
	int32	InspectionID;
	double	ResultDouble[MaxCountOfMeasureBlade];
};

class	BladeResultInMachine
{
public:
	int				CountingPoint;
	BladeResult		*ResultDim;
	int				ResultCount;
	int				AllocatedResultCount;
	int				BladeNGCount;

	BladeResultInMachine(void);
	~BladeResultInMachine(void);

	void	SetResultPage(InspectionList *n);
	void	RemoveAll(void);

};


class ShowPrintTotalBladeForm : public GUIFormBase
{
    Q_OBJECT

	int	TopCount;
	int	BottomCount;
	int	MonoCount;
	int	TopNG;
	int	BottomNG;
	int	MonoNG;
 
public:
	BladeResultInMachine	BladeResultTop;
	BladeResultInMachine	BladeResultBottom;

    explicit ShowPrintTotalBladeForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowPrintTotalBladeForm();

	virtual void	ReadyParam(void)	override;
    
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
private:
    Ui::ShowPrintTotalBladeForm *ui;
	void	ShowData(void);

signals:
	void	SignalUpdated();
private slots:
	void	SlotDoneLoadResult(InspectionList *n);
    void on_pushButtonExcelSave_clicked();
    void on_PushButtonReset_clicked();

private:
	Book	*XLSXBook;
	Sheet	*XLSXSheet;
	Format	*Lang;
	Font	*Fnt;

	void	WriteCell(int Row, int Col ,const QString &Str);
	void	WriteCellV(int Row, int Col ,const QVariant &Data);
	QImage	LoadDataFromMaster(int masterCode);
	int	SetNGImageToExcel(InspectionList *L, int Printout_MaxCountfNGImage,int N,int &Row);
};

#endif // SHOWPRINTTOTALBLADEFORM_H