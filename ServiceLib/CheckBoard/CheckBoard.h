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



