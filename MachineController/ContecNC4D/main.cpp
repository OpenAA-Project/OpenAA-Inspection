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

#include "ContecNC4D.h"
#include <QApplication>

char *SMCDeviceName ="SMC001" ;
char *PIODeviceName ="DIO000" ;

int main(int argc, char *argv[])
{
	for(int i=1;i<argc;i++){
		if((*argv[i]=='D' || *argv[i]=='d')){
			char	*fp=argv[i]+1;
			SMCDeviceName	=fp;
		}
		if((*argv[i]=='P' || *argv[i]=='p')){
			char	*fp=argv[i]+1;
			PIODeviceName	=fp;
		}
	}

	QApplication a(argc, argv);
	ContecNC4D w(SMCDeviceName ,PIODeviceName);
	w.show();
	return a.exec();
}