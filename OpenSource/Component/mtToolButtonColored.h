/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtToolButtonColored.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef MTTOOLBUTTONCOLOERED_H
#define MTTOOLBUTTONCOLOERED_H

#include <QToolButton>
#include "mtButtonWithBalloon.h"
#include <QTimer>

class	mtToolButtonColored : public QToolButton,public mtButtonWithBalloonBase
{
    Q_OBJECT

	QColor	Col;
	QColor	PressedCol;
	bool	ColorDialogOnLClick;
	QTimer	TM;
	bool	Pressed;

public:
	explicit	mtToolButtonColored(bool ColorDialogOnLClick ,QWidget *parent = 0);
	explicit	mtToolButtonColored(bool ColorDialogOnLClick ,const QColor &col ,QWidget *parent = 0);
	~mtToolButtonColored(void);

	QColor	color(void)			const;
	void	setColor(const QColor &col);
	void	setColor(const QString &ColString);
	void	setPressedColor(const QColor &col);
	QColor	pressedColor(void)	const	{	return PressedCol;	}

signals:
	void	SignalEnter();
	void	colorChanged();
protected slots:
	void	SlotMessageMouseMove(int x ,int y);
	void	SlotTimeOut();
protected:
	virtual	void mousePressEvent ( QMouseEvent * event )	override;
	virtual void paintEvent ( QPaintEvent * event )			override;
	virtual void mouseMoveEvent ( QMouseEvent * event )		override;
	virtual void enterEvent ( QEnterEvent * event )				override;
	virtual void closeEvent ( QCloseEvent * event )			override;

};

#endif