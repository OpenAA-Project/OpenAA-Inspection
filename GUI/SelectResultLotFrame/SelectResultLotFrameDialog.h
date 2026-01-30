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

#ifndef SELECTRESULTLOTFRAMEDIALOG_H
#define SELECTRESULTLOTFRAMEDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QByteArray>
#include <QIODevice>
#include <QBuffer>
#include "XIntClass.h"
#include "XServiceForLayers.h"
#include "XDateTime.h"

namespace Ui {
class SelectResultLotFrameDialog;
}
class	GUIFormBase;

class SelectResultLotFrameDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	GUIFormBase	*ParentGUI;
public:
    explicit SelectResultLotFrameDialog(bool ShowMode ,LayersBase *Base ,QWidget *parent = 0, QWidget *parentGUI=0);
    ~SelectResultLotFrameDialog();

	bool		RetMode;
	int			SelectedLotAutoCount;
	QString		SelectedLotID;
	int			SelectedIDNumber;
	QString		SelectedLotName;
	XDateTime	SelectedLastUpdated;
	QString		SelectedRemark;

	bool	RxSync(QByteArray &f);
	bool	RxSync(QIODevice &Buff);

	virtual	void	TxSync(QBuffer &f);

private slots:
    void on_ButtonCreate_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::SelectResultLotFrameDialog *ui;

	IntList	LotAutoCounts;

	bool ExecuteCreateNew(void);
};

#endif // SELECTRESULTLOTFRAMEDIALOG_H