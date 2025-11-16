/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\ViewerStrings.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "ViewerStrings.h"

ViewerStrings::ViewerStrings(LanguageStocker &_CurrentLanguageStocker,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	CurrentLanguageStocker=&_CurrentLanguageStocker;
	int	Numb=CurrentLanguageStocker->LStringR.GetNumber();
	ui.tableWidget->setRowCount(Numb);
	int	N=0;
	for(LanguageStringResource *a=CurrentLanguageStocker->LStringR.GetFirst();a!=NULL;a=a->GetNext(),N++){
		QTableWidgetItem *w;
		w=ui.tableWidget->item (N, 0);
		if(w==NULL)
			ui.tableWidget->setItem(N,0,(w=new QTableWidgetItem()));
		w->setText(a->GetFileName());
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		
		w=ui.tableWidget->item (N, 1);
		if(w==NULL)
			ui.tableWidget->setItem(N,1,(w=new QTableWidgetItem()));
		w->setText(QString::number(a->GetID()));
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		
		for(int i=0;i<10;i++){
			LanguageString *q=a->GetLanguageString(i);
			if(q==NULL)
				break;
			w=ui.tableWidget->item (N, 2+i);
			if(w==NULL)
				ui.tableWidget->setItem(N,2+i,(w=new QTableWidgetItem()));
			w->setText(q->GetFirstString());
			w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
	}
}

ViewerStrings::~ViewerStrings()
{

}


void ViewerStrings::on_pushButton_clicked()
{
	close();
}