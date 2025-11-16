/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtWidgetPosition.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef MTWIDGETPOSITION_H
#define MTWIDGETPOSITION_H

#include <QWidget>

class	mtWidgetPosition : public QWidget
{
	Q_OBJECT
	Q_ENUMS(AlighmentOfWidget)
	Q_PROPERTY(AlighmentOfWidget AlignOfWidget READ GetAOW WRITE SetAOW)

public:
	enum	AlighmentOfWidget{
			_None
			,_Client
			,_Left
			,_Right
			,_Top
			,_Bottom
	};
private:
	AlighmentOfWidget	AOWData;

public:
	explicit	mtWidgetPosition(QWidget * parent = 0);

	AlighmentOfWidget	GetAOW(void)	const	{	return(AOWData);	}
	void				SetAOW(AlighmentOfWidget data);

protected:
	virtual void resizeEvent ( QResizeEvent * event )	override;
	void	SetWindowPos(void);
	virtual void enterEvent ( QEnterEvent * event )			override;
	virtual void leaveEvent ( QEvent * event )			override;
signals:
	void	SignalEnter();
	void	SignalLeave();
private slots:
	void	On_geometryChanged();
};

#endif
