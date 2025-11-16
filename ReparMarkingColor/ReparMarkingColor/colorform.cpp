/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ReparMarkingColor\ReparMarkingColor\colorform.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "colorform.h"
#include <QColor>
#include <QColorDialog>
#include <QMessageBox>
#include <QFile>
colorForm::colorForm(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

colorForm::~colorForm()
{

}


void colorForm::on_lineEdit_selectionChanged()
{
	QPalette palette;
	if(cPalette(palette)==false)
		return ;
	ui.lineEdit->setPalette(palette);
	return;
}
bool colorForm::cPalette(QPalette &palette)
{
	QColor col;
	col = QColorDialog::getColor();//col, 0
    if (!col.isValid())
        return false;
	palette.setColor(QPalette::Base, col);
	return true;
}

void colorForm::on_pushButton_clicked()
{
	QPalette pale=ui.lineEdit->palette();
	QString Str=ui.comboBox->currentText();
	int row=ui.tableWidget->currentRow();
	ui.tableWidget->insertRow(row+1);
	QTableWidgetItem *nameItem = new QTableWidgetItem(Str);
	ui.tableWidget->setItem(row+1, 0, nameItem);
	widgetSetColor(pale, row+1);
	return;
}

void colorForm::on_tableWidget_doubleClicked(QModelIndex index)
{
 	int row=index.row();
	if(row == -1)
		return;
	if(QMessageBox::information(this, tr("Delete "), "Delete OK?", QMessageBox::Yes,QMessageBox::No)==QMessageBox::No)
		return ;
	ui.tableWidget->removeRow(row);
}

void colorForm::on_tableWidget_cellClicked(int x,int y)
{
	if(y == 0)
		return;
	QPalette palette;
	if(cPalette(palette)==false)
		return ;
	widgetSetColor(palette, x);
}
void colorForm::widgetSetColor(QPalette palette, int x)
{
	int y=1;
	QTableWidgetItem *colorItem = new QTableWidgetItem(/**/"");
	colorItem->setBackgroundColor(palette.color(QPalette::Base));
	ui.tableWidget->setItem(x, y, colorItem);
}
void colorForm::closeEvent(QCloseEvent *event)
{
	if(QMessageBox::information(this, tr("Exit "), "Exit OK?", QMessageBox::Yes,QMessageBox::No)==QMessageBox::No){
		event->ignore();
		return;
	}
    QString item; 
	QString color; 
	QList<QPair<QString, QString> > list;
	QFile file("./Color.dat");
	 if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return;
	 int row=ui.tableWidget->rowCount();
	 for (int i=0; i<row; i++){
		 item= ui.tableWidget->item(i, 0)->text();
		 color=ui.tableWidget->item(i, 1)->backgroundColor().name();
		 item	=item+QString("\n");
		 color	=color+QString("\n");
		 file.write(item.toLocal8Bit());
		 file.write(color.toLocal8Bit());
		// list.append(QPair<QString, QString>(item, color));
		 //file.write(list);
	 }
	 file.close();
	event->accept();//èIóπ
}