/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\InspectionPlayer\InspectionPlayer\InspectionPlayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "InspectionPlayerResource.h"
#include "InspectionPlayer.h"

InspectionPlayer::InspectionPlayer(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
	QTranslator Translator;
	Translator.load(/**/"/Regulus64v2/InspectionPlayer/InspectionPlayer/inspectionplayer_ja");
	qApp->installTranslator(&Translator);
	ui.setupUi(this);
}

InspectionPlayer::~InspectionPlayer()
{

}
