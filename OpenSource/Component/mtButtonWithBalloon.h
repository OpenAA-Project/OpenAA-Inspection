/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtButtonWithBalloon.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(MTBUTTONWITHBALLOON_H)
#define	MTBUTTONWITHBALLOON_H

#include<QWidget>
#include<QLabel>
#include<QTimer>
#include<QStringList>
#include<QLabel>
#include<QPoint>
#include <QMouseEvent>

class	mtButtonWithBalloonBase;

class	mtBalloonWindow : public QWidget
{
    Q_OBJECT
public:
	QLabel		Label;
	explicit	mtBalloonWindow(QWidget *parent=NULL);

	virtual void mouseMoveEvent ( QMouseEvent * event );
};

class	mtQTimer : public QTimer
{
	mtButtonWithBalloonBase	*BParent;
	int		Counter;
public:
	explicit	mtQTimer(mtButtonWithBalloonBase *parent):Counter(0){	BParent=parent;	}
	void Start ( int msec );
protected:
	void timerEvent ( QTimerEvent * event );
};

class	mtButtonWithBalloonBase
{
	mtBalloonWindow		MessageWindow;
	mtQTimer			BallonTimer;
	QWidget				*MThis;
	enum	MessageMode{
			_Leave
			,_Waiting
			,_Showing
			,_Off};
	MessageMode	Mode;
	QPoint		LastPoint;
	QPoint		LastGlobalPoint;
	QString		Message;
	bool		Pushed;
public:
	mtButtonWithBalloonBase(void);
	virtual	~mtButtonWithBalloonBase(void);

	void	closeBalloon(void);
	void	Close();
	void	setMessage(const QString &msg);
	void	TimerEvent (void);
	void	CheckEvent (void);
	void	MousePressEvent();

protected:
	void	MouseMoveEvent ( QMouseEvent * event );
	void	EnterEvent ( QWidget *_this);
private:
	void	CloseChildBaloon(QWidget *CurrentWidget ,QWidget *exceptionWindow);
};


#endif