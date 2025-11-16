/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtPushButtonColored.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef MTPUSHBUTTONCOLOERED_H
#define MTPUSHBUTTONCOLOERED_H

#include <QPushButton>
#include <QColor>

class	mtPushButtonColored : public QPushButton
{
    Q_OBJECT

	QColor	Col;

public:
	explicit	mtPushButtonColored(QWidget *parent = 0);
	explicit	mtPushButtonColored(const QColor &col ,QWidget *parent = 0);
	~mtPushButtonColored(void);

	QColor	color(void);
	void	setColor(const QColor &col);
	void	setColor(const QString &ColString);

private slots:
	void	SlotClicked();
signals:
	void	SignalClicked();
protected:
	virtual void	paintEvent ( QPaintEvent * event )	override;
};

#endif