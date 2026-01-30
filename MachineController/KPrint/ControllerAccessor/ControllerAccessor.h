/*
 * Copyright (C) 2021
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

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ControllerAccessor.h"
#include <QTcpSocket>
#include <QString>
#include <QWidget>
#include "XControllerHeader.h"

#define	PortNoOfController	17780


class ControllerAccessor : public QMainWindow
{
    Q_OBJECT

	struct ControllerInfo	CInfo;
	QString	AddressOfController;
public:
	QTcpSocket	Socket;

public:
    ControllerAccessor(QWidget *parent = Q_NULLPTR);

private slots:
    void on_pushButtonSend_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonSignal_clicked();

private:
    Ui::ControllerAccessorClass ui;

	void	ShowInfo(void);
	void	GetInfoFromWindow(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};