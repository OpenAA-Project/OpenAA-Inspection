/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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