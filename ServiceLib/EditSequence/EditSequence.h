/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\EditSequence\EditSequence.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef EDITSEQUENCE_H
#define EDITSEQUENCE_H

#include <QMainWindow>
#include "ui_EditSequence.h"
#include "XServiceForLayers.h"

class	SeqControlParam;

class EditSequence : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

public:
	EditSequence(LayersBase *base,SeqControlParam *s ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~EditSequence();

private:
	Ui::EditSequenceClass ui;

private slots:
	void on_actionShow_triggered();
	void on_actionStart_triggered();
	virtual	void MessageOutFunc(int N);
};

#endif // EDITSEQUENCE_H
