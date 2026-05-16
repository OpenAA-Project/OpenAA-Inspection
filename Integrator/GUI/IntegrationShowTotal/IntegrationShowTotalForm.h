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

#ifndef INTEGRATIONSHOWTOTALFORM_H
#define INTEGRATIONSHOWTOTALFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "xlsxwriter.h"


namespace Ui {
class IntegrationShowTotalForm;
}

struct	InfoOkNg
{
	int	OKCount;
	int	NGCount;
};


class IntegrationShowTotalForm : public GUIFormBase
{
    Q_OBJECT
    
	struct	InfoOkNg	*InfoOkNgDim;
	int					InfoOkNgDimCount;

public:
	bool	ModeShowTotal;
	bool	ModeShowAllResult;
	bool	ModeShowEachResult;


    explicit IntegrationShowTotalForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationShowTotalForm();
    
	virtual void	ReadyParam(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;

private slots:
    void on_PushButtonReset_clicked();
    void on_pushButtonExcelSave_clicked();
	void	SlotDoneLoadResult(InspectionList *n);
	void	ResizeAction();
private:
    Ui::IntegrationShowTotalForm *ui;
	void	ShowData(void);

	lxw_workbook	*XLSXBook	=NULL;
	lxw_worksheet	*XLSXSheet	=NULL;
	lxw_format		*Lang		=NULL;

	void	WriteCell(int Row, int Col ,const QString &Str);
	void	WriteCellV(int Row, int Col ,const QVariant &Data);
	QImage	LoadDataFromMaster(int masterCode);
	int			SetNGImageToExcel(InspectionList *L, int Printout_MaxCountfNGImage,int N,int &Row);
	QStringList	GetInformation(InspectionList *L,NGPoint *Rp);

signals:
	void	SignalUpdated();
};

#endif // INTEGRATIONSHOWTOTALFORM_H