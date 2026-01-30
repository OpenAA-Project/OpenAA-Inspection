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

#ifndef EDITITEMDIALOG_H
#define EDITITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include"XPropertySkipMarkPacket.h"

namespace Ui {
class EditItemDialog;
}

class EditItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	bool AdditionalMode;
	AlgorithmBasePointerContainer	AlgoBases;
	NamingInfoListContainer			NamingContainer;
public:
    explicit EditItemDialog(bool AdditionalMode ,LayersBase *Base,int globalPage ,int Layer ,QWidget *parent = 0);
    ~EditItemDialog();

	int			GlobalPage;
	int			Layer;

	QString		ItemName;
	QString		NamingDLLRoot;
	QString		NamingDLLName;
	int32		NamingID;

	void	Reflect(void);
private slots:
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditItemDialog *ui;

	void	ShowList(void);
};

#endif // EDITITEMDIALOG_H