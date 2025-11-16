/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\InspectionPlayer\InspectionPlayer\InspectionPlayer.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef INSPECTIONPLAYER_H
#define INSPECTIONPLAYER_H

#include <QMainWindow>
#include <QTranslator>
#include "ui_InspectionPlayer.h"

class InspectionPlayer : public QMainWindow
{
    Q_OBJECT

public:
    InspectionPlayer(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~InspectionPlayer();

private:
    Ui::InspectionPlayerClass ui;
};

#endif // INSPECTIONPLAYER_H
