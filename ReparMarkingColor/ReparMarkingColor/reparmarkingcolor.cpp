/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ReparMarkingColor\ReparMarkingColor\reparmarkingcolor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "reparmarkingcolor.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QHeaderView>
bool	DLL_GetName(QString &str)
{
	str="Default Graphin Camera";
	return true;
}
void	DLL_FormShow(void)
{
	cform=new colorForm();
	QFile file("./AlgorithmList.dat");
   // if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    //    return;
	file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
	QStringList itemList;
	QString item;
    while (!in.atEnd()) {
		item=in.readLine();
		if(item.left(2)!="//")
	        itemList.append(item.left(item.indexOf(".dll")));
    }
	file.close();
	cform->ui.comboBox->addItems(itemList);
	
	QFile cfile("./Color.dat");
	QTextStream cin(&cfile);
	QStringList citemList;
	QString citem;
	//if (!cfile.open(QIODevice::ReadOnly | QIODevice::Text))
    //     return;
	cfile.open(QIODevice::ReadOnly | QIODevice::Text);
     while (!cin.atEnd()) {
		 citem=cin.readLine();
         citemList.append(citem);
     }
	 cfile.close(); 	

	int count=citemList.count();
	/*
	cform->ui.tableWidget->setColumnCount(2);
	cform->ui.tableWidget->setRowCount(count/2);
	cform->ui.tableWidget->setHorizontalHeaderLabels(QStringList() <<("Name")<< ("Color"));
	cform->ui.tableWidget->horizontalHeader()->resizeSection(0,150);
	cform->ui.tableWidget->horizontalHeader()->resizeSection(1,100);
	*/
	cform->ui.tableWidget->setColumnCount(2);
	cform->ui.tableWidget->setRowCount(count/2);
	cform->ui.tableWidget->setHorizontalHeaderLabels(QStringList() <<("Name")<< ("Color"));
	cform->ui.tableWidget->horizontalHeader()->resizeSection(0,150);
	cform->ui.tableWidget->horizontalHeader()->resizeSection(1,100);
	QTableWidgetItem *nameItem;
	int n=0;
	for(int i=0; i<count; i++, n++){
		nameItem = new QTableWidgetItem(citemList.at(i));
		i++;
		cform->ui.tableWidget->setItem(n, 0, nameItem);		
		
		QPalette palette;
		palette.setColor(QPalette::Base, QColor(citemList.at(i)));
		int y=1;
		QTableWidgetItem *colorItem = new QTableWidgetItem(/**/"");
		colorItem->setBackgroundColor(palette.color(QPalette::Base));
		cform->ui.tableWidget->setItem(n, y, colorItem);
	}
	if(!cform->exec())
		return;
	/*
	cform->show();
	cform->raise();
	cform->activateWindow();
	*/
}