/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\XmlServer\XmlServer\xmlapi.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XMLAPI_H
#define XMLAPI_H

#include <QObject>
//using namespace DbXml;
#include "MTXMLLib.h"
class XmlAPI : public QObject
{
	Q_OBJECT

public:
    XmlAPI(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	XMLMainStock *XMLMain[100];
	XMLMainStock *XMLM;
private:  
};

#endif // XMLCONT_H
