/*
 * Copyright (C) 2022
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

#ifndef SENDMESSAGERFORM_H
#define SENDMESSAGERFORM_H

#include "XGUIFormBase.h"
#include "ui_SendMessagerForm.h"
#include <QPushButton>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMessagerClient.h"

class SendMessagerForm : public GUIFormBase
{
	Q_OBJECT

	MessagerClient	MClient;
public:
	QString	IPAddress;

	SendMessagerForm(LayersBase *Base ,QWidget *parent = 0);
	~SendMessagerForm();

	virtual	void	Prepare(void)	override;

private:
	Ui::SendMessagerFormClass ui;

private slots:
	void on_pushButtonSend_clicked();
};


#endif // SENDMESSAGERFORM_H