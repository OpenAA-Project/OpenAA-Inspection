/*
 * Copyright (C) 2025
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

#ifndef CHANGESERVER_H
#define CHANGESERVER_H

#include <QMainWindow>
#include "ui_ChangeServer.h"
#include "XChangeServer.h"

class ChangeServer : public QMainWindow
{
	Q_OBJECT

public:
	ChangeServer(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ChangeServer();

	ChangeServerContainer	ServerContainer;

	void	ShowCurrent(void);
	void	ShowGrid(void);
	bool	SaveContainer(void);

private:
	Ui::ChangeServerClass ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButtonEdit_clicked();
	void on_pushButtonSelect_clicked();
	void on_tableWidgetServers_doubleClicked(QModelIndex);
};

#endif // CHANGESERVER_H