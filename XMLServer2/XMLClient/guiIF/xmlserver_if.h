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

#ifndef XMLSERVER_IF_H
#define XMLSERVER_IF_H

#include <QWidget>
#include "ui_xmlserver_if.h"

#include "XMLServerHandle.h"

class XMLServer_IF : public QWidget
{
    Q_OBJECT

public:
    XMLServer_IF(QWidget *parent = 0);
    ~XMLServer_IF();

public slots:
	void showMess(QString mess);

private slots:
	void exitApp();
	void connectSvr();
	void chkStats();
	void disConnectSvr();

	void selectXML();
	void firstXML();
	void nextXML();

	void addXML();
	void appendXML();

	void updXML();
	void delXML();

private:
    Ui::XMLServer_IFClass ui;

    XMLServerHandle *handle;
};

#endif // XMLSERVER_IF_H