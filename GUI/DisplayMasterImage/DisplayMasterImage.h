/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayMasterImage\DisplayMasterImage.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef DISPLAYMASTERIMAGE_H
#define DISPLAYMASTERIMAGE_H
#include <QTranslator>
#include "displaymasterimage_global.h"
#include "XDisplayImage.h"

class	DisplayMasterImage : public DisplayImage
{
	Q_OBJECT
public:
	bool						tModeShowOnlyTopTurn;
	DisplayMasterImage(LayersBase *Base ,QWidget *parent);
	~DisplayMasterImage(void){}

};

#endif // DISPLAYMASTERIMAGE_H
