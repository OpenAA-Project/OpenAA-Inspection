/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Proofreader\ExecuteHalcon.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef EXECUTEHALCON_H
#define EXECUTEHALCON_H

class ExecuteHalcon
{
public:
	ExecuteHalcon();
	~ExecuteHalcon();

	void Hgen_image1(int iDotPerLine,int iMaxLines,unsigned char *image);
	void Hgen_image3(int iDotPerLine,int iMaxLines,unsigned char *image1,unsigned char *image2,unsigned char *image3);
};
#endif
