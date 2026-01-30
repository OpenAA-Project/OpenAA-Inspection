/*
 * Copyright (C) 2012
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

#ifndef SHOWLOADEDINFOFORM_H
#define SHOWLOADEDINFOFORM_H

#include <QDialog>
#include "ui_ShowLoadedInfoForm.h"
#include "XServiceForLayers.h"
class	LayersBase;

class ShowLoadedInfoForm : public QWidget,public ServiceForLayers
{
	Q_OBJECT

public:
	ShowLoadedInfoForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowLoadedInfoForm();

private:
	Ui::ShowLoadedInfoFormClass ui;

	void	ShowList(void);
signals:
	void	SignalClose();
private slots:
	void on_pushButtonOK_clicked();
	void on_toolButtonByName_clicked();
	void on_toolButtonByPage_clicked();
};

#endif // SHOWLOADEDINFOFORM_H