/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtColorFrame.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(MTCOLORFRAME_H)
#define	MTCOLORFRAME_H

#include <QFrame>

class mtColorFrame : public QFrame
{
    Q_OBJECT
	QColor	BaseColor;

public:
	
	explicit	mtColorFrame( QWidget * parent = 0, Qt::WindowFlags f = Qt::Widget );

	virtual	void 	paintEvent ( QPaintEvent * event )		override;

	void	SetColor(const QColor &col);
	QColor	GetColor(void){		return BaseColor;	}
};

#endif
