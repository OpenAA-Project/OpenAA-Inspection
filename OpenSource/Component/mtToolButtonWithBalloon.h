/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtToolButtonWithBalloon.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(MTTOOLBUTTONWITHBALLOON_H)
#define	MTTOOLBUTTONWITHBALLOON_H

#include<QToolButton>
#include<QTimer>
#include<QStringList>
#include<QWidget>
#include<QLabel>
#include<QPoint>
#include "mtButtonWithBalloon.h"


class	mtToolButtonWithBalloon : public QToolButton ,public mtButtonWithBalloonBase
{
    Q_OBJECT
private:
public:

	explicit	mtToolButtonWithBalloon(QWidget *parent=NULL);
	~mtToolButtonWithBalloon();

protected:
	virtual void mouseMoveEvent ( QMouseEvent * event )		override;
	virtual void enterEvent ( QEnterEvent * event )				override;
	virtual void closeEvent ( QCloseEvent * event )			override;
	virtual void mousePressEvent ( QMouseEvent * event )	override;

signals:
	void	SignalEnter();
	void	RClick(QMouseEvent * event );
	
private slots:
	void	SlotMessageMouseMove(int x ,int y);
};


#endif