/*
 * Copyright (C) 2016
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
#include "XTypeDef.h"
#include <QString>
#include "XServiceForLayers.h"

namespace Ui {
class EditItemDialog;
}

class EditItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditItemDialog(LayersBase *base ,bool Editable ,QWidget *parent = 0);
    ~EditItemDialog();

	int32			Priority;
	bool			SaveTargetImage;
	bool			SaveOnlyInNG;
	int32			BufferType;
	QString			ItemName;

	void	Initial(void);

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonEdit_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::EditItemDialog *ui;
};

#endif // EDITITEMDIALOG_H