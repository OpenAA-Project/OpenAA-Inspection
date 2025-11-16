/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Proofreader\WhiteBalanceForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef WHITEBALANCEFORM_H
#define WHITEBALANCEFORM_H

#include <QDialog>
#include "ui_WhiteBalanceForm.h"

class mtLineGraph;

class WhiteBalanceForm : public QDialog
{
	Q_OBJECT

public:
	WhiteBalanceForm(QList<int> *RDataList,QList<int> *GDataList,QList<int> *BDataList,int Offset=0);
	~WhiteBalanceForm();

	void SetDotPerLine(int Line)	{	DotPerLine=Line;	}

private slots:
	void sbRedAdjustNumb_valueChanged	(int value);
	void sbGreenAdjustNumb_valueChanged	(int value);
	void sbBlueAdjustNumb_valueChanged	(int value);
	void pbShading_clicked();
	void pbSave_clicked();
	void pbClose_clicked();

private:
	Ui::WhiteBalanceFormClass ui;
	mtLineGraph		*LineGraph;
	QList<int> *RGBDataList[3];

	int DotPerLine;
	int OffsetNumb;
};

#endif // WHITEBALANCEFORM_H
