/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayGrayLower\DisplayGrayLower.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef DISPLAYGRAYLOWER_H
#define DISPLAYGRAYLOWER_H
#include <QTranslator>
#include "displaygraylower_global.h"
#include "XDisplayImage.h"

class	DisplayGrayLowerImage : public DisplayImage
{
	Q_OBJECT
public:
	DisplayGrayLowerImage(LayersBase *Base ,QWidget *parent);
	~DisplayGrayLowerImage(void){}

};
#endif // DISPLAYGRAYLOWER_H
