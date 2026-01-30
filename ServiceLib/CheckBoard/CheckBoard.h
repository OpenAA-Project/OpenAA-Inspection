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

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CheckBoard.h"
#include <QTimer>
#include "NList.h"

class BoardInfoList : public NPList<BoardInfoList>
{
public:
	QString	BoardName;
	int     LinkWidth;
	QString HardwareID;

    BoardInfoList(void){
        BoardName="";
        LinkWidth=0;
	}

private:

};




class CheckBoard : public QMainWindow
{
    Q_OBJECT

    QTimer  TM;

    const QString BoardName;
    bool    CheckExistence;
    int	    LinkWidth;
    int     WaitingSec;

	int	    CurrentSec;

public:
    CheckBoard(const QString &BoardName
                ,bool    CheckExistence
                ,int	    LinkWidth
                ,int     WaitingSec
                ,QWidget *parent = nullptr);
    ~CheckBoard();

private slots:
    void on_pushButtonStopCheck_clicked();
    void OnTimerTicked();
    void SlotReboot();
private:
    Ui::CheckBoardClass ui;	

	bool GetBoardInfo(NPListPack<BoardInfoList> &BoardInfo);
};


