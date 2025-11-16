/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtPushButtonWithBalloon.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(MTPUSHBUTTONWITHBALLOON_H)
#define	MTPUSHBUTTONWITHBALLOON_H

#include<QPushButton>
#include<QTimer>
#include<QStringList>
#include<QWidget>
#include<QLabel>
#include<QPoint>
#include "mtButtonWithBalloon.h"


class	mtPushButtonWithBalloon : public QPushButton ,public mtButtonWithBalloonBase
{
    Q_OBJECT
private:
public:

	explicit	mtPushButtonWithBalloon(QWidget *parent=NULL);
	~mtPushButtonWithBalloon();

protected:
	virtual void mouseMoveEvent ( QMouseEvent * event )		override;
	virtual void enterEvent ( QEnterEvent * event )				override;
	virtual void closeEvent ( QCloseEvent * event )			override;
	virtual void	mousePressEvent ( QMouseEvent * event )	override;

signals:
	void	SignalEnter();
	
private slots:
	void	SlotMessageMouseMove(int x ,int y);
};


#endif