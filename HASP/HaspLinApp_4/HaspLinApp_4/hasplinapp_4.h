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

#ifndef HASPLINAPP_4_H
#define HASPLINAPP_4_H

#include <QMainWindow>
#include "ui_hasplinapp_4.h"
#include <QFileDialog>
#include  <QMessageBox>
#include "hasp_hl.h"
#include  <QDomDocument>

class HaspLinApp_4 : public QMainWindow
{
    Q_OBJECT

public:
    HaspLinApp_4(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~HaspLinApp_4();

private:
    Ui::HaspLinApp_4Class ui;
	hasp_handle_t   Handle;
	QByteArray Info;
	int HaspID;
	QByteArray ReData;
	QByteArray Fuku;
	QByteArray DeData;
	QStringList Ret;

	bool HaspLogin(hasp_handle_t &handle);
	bool Session(hasp_handle_t handle, QByteArray &info);
	void GetHaspID(QByteArray haspInfo,int &haspID);
	bool ReadHasp(hasp_handle_t handle, QByteArray &readData);
	void Fukugou(int ID,QByteArray ReData, QByteArray &fukugou);
	bool Decrypt(hasp_handle_t handle, QByteArray hasp, QByteArray &deCereal);
	void Return(QByteArray InData,QStringList &RetData);
private slots:
	void on_pushButton_clicked();
};

#endif // HASPLINAPP_4_H