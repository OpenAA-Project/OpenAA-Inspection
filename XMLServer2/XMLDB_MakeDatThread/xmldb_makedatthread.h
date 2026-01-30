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

#ifndef XMLDB_MAKEDATTHREAD_H
#define XMLDB_MAKEDATTHREAD_H

#include <QWidget>
#include "ui_xmldb_makedatthread.h"

#include "clsMakeDat.h"

class XMLDB_MakeDatThread : public QWidget
{
    Q_OBJECT

public:
    XMLDB_MakeDatThread(QWidget *parent = 0);
    ~XMLDB_MakeDatThread();

private slots:
	void exitApp();
	void execMakeDat();
	void showMess1(QString mess,bool bWait);
	void showMess2(QString mess,bool bWait);

private:
    Ui::XMLDB_MakeDatThreadClass ui;

    clsMakeDat *thrMakeDat1;
    clsMakeDat *thrMakeDat2;
    void clearMakeDatObj();

    int nRow1;
    int nRow2;
    void setResRow(int nRow, QTableWidget *wid, double dMax, double dMin, double dAvg, double dCnt, double dSum);
};

#endif // XMLDB_MAKEDATTHREAD_H