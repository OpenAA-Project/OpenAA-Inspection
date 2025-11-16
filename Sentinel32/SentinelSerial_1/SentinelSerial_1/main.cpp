/*******************************************************************************
** Copyright (C) 2005-2009 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Sentinel\SentinelSerial_1\SentinelSerial_1\main.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <QApplication>
#include "sentinelserial_1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SentinelSerial_1 w;
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    return a.exec();
}
