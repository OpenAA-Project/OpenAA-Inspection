/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\HASP\HaspChosaku_2\HaspChosaku_2\main.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <QApplication>
#include "haspchosaku_2.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HaspChosaku_2 w;
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    return a.exec();
}
