/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\XML\MTXMLServer\MTXMLServer.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef MTXMLSERVER_H
#define MTXMLSERVER_H

#include <QMainWindow>
#include "ui_MTXMLServer.h"
#include "MTXMLLib.h"

class MTXMLServer : public QMainWindow
{
	Q_OBJECT

public:
	MTXMLServer(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);//
	~MTXMLServer();

private:
	Ui::MTXMLServerClass ui;

	XMLMainStock	*XMLMain;
	XMLElement		*Answer;
	XMLElement		*Element;
XMLElement		*wAnswer;
	XMLTag			*MatchTag1;
	XMLTag			*MatchTag2;

private slots:
	void on_ButtonLast_clicked();
	void on_ButtonDelete_2_clicked();
	void on_ButtonSearchNextTagToTag_clicked();
	void on_ButtonSearchTagToTag_clicked();
	void on_ButtonSearchNextTag_clicked();
	void on_ButtonSearchTag_clicked();
	void on_ButtonDelete_clicked();
	void on_ButtonSearchNext_clicked();
	void on_ButtonAddInListElement_clicked();
	void on_ButtonCreateFileName_clicked();
	void on_ButtonSearch_clicked();
	void on_ButtonAddElement_clicked();
	void on_ButtonFileName_clicked();
};

#endif // MTXMLSERVER_H
