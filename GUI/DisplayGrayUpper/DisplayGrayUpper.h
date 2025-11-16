/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayGrayUpper\DisplayGrayUpper.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef DISPLAYGRAYUPPER_H
#define DISPLAYGRAYUPPER_H
#include <QTranslator>
#include "displaygrayupper_global.h"
#include "XDisplayImage.h"

class	DisplayGrayUpperImage : public DisplayImage
{
	Q_OBJECT
public:
	DisplayGrayUpperImage(LayersBase *Base ,QWidget *parent);
	~DisplayGrayUpperImage(void){}

};
#endif // DISPLAYGRAYUPPER_H
