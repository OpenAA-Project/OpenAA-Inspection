/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PIOWatch\PIOWatch\PIOWatch.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef PIOWATCH_H
#define PIOWATCH_H

#include <QWidget>
#include <QThread>
#include "ui_PIOWatch.h"

class PIOReadThread : public QThread
{
	Q_OBJECT

public:
	PIOReadThread(int BoardNumber=0);

	void SetBoardNumber	(int BoardNumber)	{	BoardNumb=BoardNumber;	}
	void SetStopped		(bool Enabled)		{	Stopped=Enabled;		}
	bool GetStopped		()					{	return Stopped;			}

signals:
	void SignalOnCheck(Qt::CheckState *State,int BoardNumber);

protected:
	void run();

private:
	bool Stopped;
	int BoardNumb;
};

class PIOReadOutThread : public QThread
{
	Q_OBJECT

public:
	PIOReadOutThread(int BoardNumber=0);

	void SetBoardNumber	(int BoardNumber)	{	BoardNumb=BoardNumber;	}
	void SetStopped		(bool Enabled)		{	Stopped=Enabled;		}
	bool GetStopped		()					{	return Stopped;			}

signals:
	void SignalOnCheckOut(Qt::CheckState *State,int BoardNumber);

protected:
	void run();

private:
	bool Stopped;
	int BoardNumb;
};

class PIOWatch : public QWidget
{
	Q_OBJECT

public:
	PIOWatch(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~PIOWatch();

protected:
	virtual	void closeEvent(QCloseEvent *event)	override;		//closeイベント

private slots:
	void pbReferClicked();
	void twOUTitemChanged(QTableWidgetItem *item);
	void twOUT_2itemChanged(QTableWidgetItem *item);
	void pbCloseClicked();
	bool maybeClose();							//終了判定
	void SlotOnCheck(Qt::CheckState *State,int BoardNumber);
	void SlotOnCheckOut(Qt::CheckState *State,int BoardNumber);
	void chkEchoBackToggled(bool checked);
	void chkEchoBack_2Toggled(bool checked);

private:
	Ui::PIOWatchClass ui;
	PIOReadThread tPIORead[2]; 
	PIOReadOutThread tPIOReadOut[2]; 
	QPalette palette;
	QTableWidget *twIN[2];
	QTableWidget *twOUT[2];

	bool PIODLLInit(QString strDLLName);
};

#endif // PIOWATCH_H
