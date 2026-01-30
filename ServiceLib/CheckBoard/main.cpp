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

#include "CheckBoard.h"
#include <QtWidgets/QApplication>



int main(int argc, char *argv[])
{
    QString BoardName;
	bool    CheckExistence = false;
	int	    LinkWidth = 0;
    int     WaitingSec=10;

    for(int i=0;i<argc;i++){
        QString Param=QString::fromLocal8Bit(argv[i]);
        if(i==1){
            BoardName=Param;
        }
        else if(Param.compare("E",Qt::CaseInsensitive)==0){
            CheckExistence=true;
        }
        else if(Param.compare("X1",Qt::CaseInsensitive)==0){
            LinkWidth=1;
        }
        else if(Param.compare("X4",Qt::CaseInsensitive)==0){
            LinkWidth=4;
        }
        else if(Param.compare("X8",Qt::CaseInsensitive)==0){
            LinkWidth=8;
        }
        else if(Param.compare("X16",Qt::CaseInsensitive)==0){
            LinkWidth=16;
        }
	}

    QApplication app(argc, argv);
    CheckBoard window(BoardName,CheckExistence,LinkWidth,WaitingSec);
    window.show();
    return app.exec();
}