/*
 * Copyright (C) 2023
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


#include "hasplib.h"

#include <QApplication>
#include <QTranslator>
#include "xmlserver.h"
bool XmlFlag;
bool	FinalMode=false;
int main(int argc, char *argv[])
{
	hasp_handle_t   Handle;
	Hasplib Hasp;
	Hasp.HaspLogin(Handle);

	QStringList RetList;
	if(Hasp.HaspExecute(RetList)==false)
		return false;



	//XMLServer����
	for(int i=0; i<argc; i++){
		if(*argv[i]=='A' || *argv[i]=='a')
			XmlFlag=true;
	}
    QApplication a(argc, argv);
//==�|��=======================================
	QTranslator Translator;
	a.installTranslator(&Translator);
//=============================================

	XmlServer w;
	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	bool	ret=a.exec();
	FinalMode=true;
    return ret;
}