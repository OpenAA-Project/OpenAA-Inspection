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


#ifndef CLOSEMESSAGEFORM_H
#define CLOSEMESSAGEFORM_H

#include <QDialog>
#include "ui_CloseMessageForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"

class CloseMessageForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	CloseMessageForm(LayersBase *Base ,QWidget *parent);
	~CloseMessageForm();

private:
	Ui::CloseMessageFormClass ui;

private slots:
	void on_pushButtonCalcen_clicked();
	void on_pushButtonCloseOne_clicked();
	void on_pushButtonCloseAll_clicked();
};

#endif // CLOSEMESSAGEFORM_H