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

#ifndef NGTYPEDIALOG_H
#define NGTYPEDIALOG_H

#include <QDialog>
#include "ui_NGTypeDialog.h"
#include "XServiceForLayers.h"

class	BlockLibNGTypeItem;

class NGTypeDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT

	BlockLibNGTypeItem *Item;

public:
	NGTypeDialog(LayersBase *base, BlockLibNGTypeItem *Item ,QWidget *parent = 0);
	~NGTypeDialog();

private:
	Ui::NGTypeDialogClass ui;

private slots:
	void on_pushButtonOK_clicked();
};

#endif // NGTYPEDIALOG_H