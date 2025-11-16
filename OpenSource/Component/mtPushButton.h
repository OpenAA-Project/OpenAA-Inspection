/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtPushButton.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef mtPushButton_H
#define mtPushButton_H

#include <QPushButton>

class	mtPushButton : public QPushButton
{
    Q_OBJECT

	QColor	NormalCol;
	QColor	PushedCol;

public:
	explicit	mtPushButton(QWidget *parent = 0);
	explicit	mtPushButton(const QColor &normalcol,const QColor &pushedcol ,QWidget *parent = 0);

	QColor	NormalColor(void);
	QColor	PushedColor(void);
	void	setColor(const QColor &normalcol,const QColor &pushedcol);

signals:
	void	SignalRightClick();

protected:
	virtual	void mousePressEvent ( QMouseEvent * e )	override;
};

#endif