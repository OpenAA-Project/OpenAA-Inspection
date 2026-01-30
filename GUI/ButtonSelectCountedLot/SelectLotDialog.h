/*
 * Copyright (C) 2015
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

#ifndef SELECTLOTDIALOG_H
#define SELECTLOTDIALOG_H

#include <QDialog>
#include "SelectLotForm.h"
#include "XServiceForLayers.h"
#include "XLotInformation.h"

namespace Ui {
    class SelectLotDialog;
}
class	SelectLotDialog;

class	SelectLotFormForDialog : public SelectLotForm
{
	SelectLotDialog	*ParentDialog;
public:
	SelectLotFormForDialog(LayersBase *pbase ,SelectLotDialog *_ParentDialog,QWidget *parent,QWidget *rootParent)
		:SelectLotForm(pbase ,parent,rootParent,1000){	ParentDialog=_ParentDialog;	}

	virtual	void	TxSync(QBuffer &Buff);
};

class	LotInformationWithCounted : public LotInformation
{
	int	Counter;
public:
	LotInformationWithCounted(LayersBase *base):LotInformation(base){	Counter=0;	}

	virtual	void	ExecuteEveryInspectInMaster(int InspectionID);
	virtual	void	ExecuteEveryInspectInSlave(int InspectionID,int Phase ,int Page);
};

//---------------------------------------------------------------------------

class SelectLotDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	SelectLotFormForDialog	*SelectLot;
public:
    explicit SelectLotDialog(LayersBase *Base,QWidget *parent = 0);
    ~SelectLotDialog();

	int		LotCountNumber;

	bool	RetMode;
	int			SelectedLotAutoCount;
	QString		SelectedLotID;
	QString		SelectedLotName;
	XDateTime	SelectedLastUpdated;
	QString		SelectedRemark;

	bool	RxSync(QByteArray &f);
	void	LoadFromWindow(void);

private slots:
	void	SlotClose();
private:
    Ui::SelectLotDialog *ui;
};

#endif // SELECTLOTDIALOG_H