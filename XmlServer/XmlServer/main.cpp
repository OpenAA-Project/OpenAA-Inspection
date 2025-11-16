/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\XmlServer\XmlServer\main.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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



	//XMLServerèàóù
	for(int i=0; i<argc; i++){
		if(*argv[i]=='A' || *argv[i]=='a')
			XmlFlag=true;
	}
    QApplication a(argc, argv);
//==ñ|ñÛ=======================================
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
