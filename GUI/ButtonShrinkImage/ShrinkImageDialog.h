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

#ifndef SHRINKIMAGEDIALOG_H
#define SHRINKIMAGEDIALOG_H

#include <QDialog>
#include "ui_ShrinkImageDialog.h"
#include "XServiceForLayers.h"

class ShrinkImageDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	ShrinkImageDialog(LayersBase *base, QWidget *parent = 0);
	~ShrinkImageDialog();

	double	Rate;
	bool	ExeMaster;
	bool	ExeTarget;
private:
	Ui::ShrinkImageDialogClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOk_clicked();
};

#endif // SHRINKIMAGEDIALOG_H