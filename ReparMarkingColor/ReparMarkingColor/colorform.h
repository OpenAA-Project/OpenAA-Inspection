/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ReparMarkingColor\ReparMarkingColor\colorform.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef COLORFORM_H
#define COLORFORM_H

#include <QDialog>
#include "ui_colorform.h"
 #include <QCloseEvent>
class colorForm : public QDialog
{
	Q_OBJECT
protected:
	void closeEvent(QCloseEvent *event);
public:
	colorForm(QWidget *parent = 0);
	~colorForm();
	Ui::colorFormClass ui;
private:
	bool cPalette(QPalette &palette);
    void widgetSetColor(QPalette palette, int x);
private slots:
	void on_tableWidget_cellClicked(int,int);
	void on_tableWidget_doubleClicked(QModelIndex);
	void on_pushButton_clicked();
	void on_lineEdit_selectionChanged();
};

#endif // COLORFORM_H
