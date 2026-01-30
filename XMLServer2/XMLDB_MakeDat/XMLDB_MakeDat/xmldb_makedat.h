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

#ifndef XMLDB_MAKEDAT_H
#define XMLDB_MAKEDAT_H

#include <QWidget>
#include "ui_xmldb_makedat.h"
#include "clsMakeDat.h"

class XMLDB_MakeDat : public QWidget
{
    Q_OBJECT

public:
    XMLDB_MakeDat(QWidget *parent = 0);
    ~XMLDB_MakeDat();

    QString dbFile;

private slots:
	void addIst();
	void exitWin();
	void showMess(QString mess);
	void updLotID(QString lid);

	void fileSel();
	void execCreate();

private:
    Ui::XMLDB_MakeDatClass ui;

    clsMakeDat *objThr;
};

#endif // XMLDB_MAKEDAT_H