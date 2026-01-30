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



#ifndef MTXMLSERVER_H
#define MTXMLSERVER_H

#include <QMainWindow>
#include "ui_MTXMLServer.h"
#include "MTXMLLib.h"

class MTXMLServer : public QMainWindow
{
	Q_OBJECT

public:
	MTXMLServer(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);//
	~MTXMLServer();

private:
	Ui::MTXMLServerClass ui;

	XMLMainStock	*XMLMain;
	XMLElement		*Answer;
	XMLElement		*Element;
XMLElement		*wAnswer;
	XMLTag			*MatchTag1;
	XMLTag			*MatchTag2;

private slots:
	void on_ButtonLast_clicked();
	void on_ButtonDelete_2_clicked();
	void on_ButtonSearchNextTagToTag_clicked();
	void on_ButtonSearchTagToTag_clicked();
	void on_ButtonSearchNextTag_clicked();
	void on_ButtonSearchTag_clicked();
	void on_ButtonDelete_clicked();
	void on_ButtonSearchNext_clicked();
	void on_ButtonAddInListElement_clicked();
	void on_ButtonCreateFileName_clicked();
	void on_ButtonSearch_clicked();
	void on_ButtonAddElement_clicked();
	void on_ButtonFileName_clicked();
};

#endif // MTXMLSERVER_H