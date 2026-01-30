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

#ifndef HASPVIEWER_H
#define HASPVIEWER_H

#include <QWidget>
#include "ui_Haspviewer.h"
//#include "hasp_hl.h"
#include "hasp_api.h"
#include <QMessageBox>

class HaspViewer : public QWidget
{
	Q_OBJECT

public:
	HaspViewer(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~HaspViewer();

	
	void View(void);
	void clearUI(void);
	QString GetID(char *C);
	bool ErrorCheck(const hasp_status_t &status);

	//void Fukugou(QString &str_ID,unsigned char *Data);
	void Fukugou(int ID,QByteArray ReData,QByteArray &fukugou);

	void setDateList(unsigned char *Data,QStringList &DateList);
	void setTypeList(unsigned char *Data,QStringList &TypeList);
	void showCode(const QString &Code,const QString &Date);
	hasp_status_t Login(hasp_handle_t &handle);
private slots:
        void on_pbUpdate_clicked();

        void on_pbEND_clicked();

private:
	Ui::HaspViewerClass ui;

	hasp_handle_t   handle;
	QMessageBox Mbox;
};

#endif // HASPVIEWER_H