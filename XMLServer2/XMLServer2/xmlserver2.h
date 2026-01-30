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

#ifndef XMLSERVER2_H
#define XMLSERVER2_H

#include <QWidget>
#include "ui_xmlserver2.h"
#include "clsTcpSvr.h"

class XMLServer2 : public QWidget
{
    Q_OBJECT

public:
    XMLServer2(QWidget *parent = 0);
    ~XMLServer2();

    clsTcpSvr *objSvr;
    void drawRowMstId(int port, const QByteArray &MstId);

private slots:
	void exitApp();
	void drawRequest(int port, QString svr, QString sts);
	void popParam();

private:
    Ui::XMLServer2Class ui;
    void addRow(int port, QString svr, QString sts);
};

#endif // XMLSERVER2_H