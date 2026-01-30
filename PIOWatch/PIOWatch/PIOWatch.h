/*
 * Copyright (C) 2025
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
	virtual	void closeEvent(QCloseEvent *event)	override;		//close�C�x���g

private slots:
	void pbReferClicked();
	void twOUTitemChanged(QTableWidgetItem *item);
	void twOUT_2itemChanged(QTableWidgetItem *item);
	void pbCloseClicked();
	bool maybeClose();							//�I������
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