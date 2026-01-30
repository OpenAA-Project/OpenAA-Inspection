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

#ifndef BUTTONSELECTMULTIDELIVERYDIALOG_H
#define BUTTONSELECTMULTIDELIVERYDIALOG_H

#include <QDialog>
#include <QBuffer>
#include <QByteArray>
#include <QIODevice>
#include "XServiceForLayers.h"
#include "XDateTime.h"
#include "XIntClass.h"


namespace Ui {
class ButtonSelectMultiDeliveryDialog;
}

class	GUIFormBase;

class ButtonSelectMultiDeliveryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	GUIFormBase	*ParentGUI;
public:
    explicit ButtonSelectMultiDeliveryDialog(LayersBase *Base ,QWidget *parent = 0);
    ~ButtonSelectMultiDeliveryDialog();

	bool	RetMode;

	IntList 	SelectedLotAutoCount;
	QString		SelectedLotID;
	QString		SelectedLotName;
	XDateTime	SelectedLastUpdated;
	QString		SelectedRemark;
	IntList		SubLotNumber;

	bool	RxSync(QByteArray &f);
	bool	RxSync(QIODevice &Buff);

	virtual	void	TxSync(QBuffer &f);

	void	CreateNewLot(const QString &LotID ,const QString &LotName ,bool Synchronized=true);
private slots:
    void on_ButtonCreate_clicked();
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::ButtonSelectMultiDeliveryDialog *ui;

	IntList	LotAutoCounts;

	bool SelectLotAction(void);
	bool ExecuteCreateNew(void);
};

#endif // BUTTONSELECTMULTIDELIVERYDIALOG_H