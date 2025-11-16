/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Data management\Data management\progressbar.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>
#include "ui_progressbar.h"

namespace Ui {
    class Progressbar;
}

class Progressbar : public QWidget
{
    Q_OBJECT

public:
    explicit Progressbar(QWidget *parent = 0);
    ~Progressbar();
	Ui::Progressbar P;

private:
    
};

#endif // PROGRESSBAR_H
