/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\ViewerUI.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "ViewerUI.h"

ViewerUI::ViewerUI(LanguageStocker &_CurrentLanguageStocker,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	CurrentLanguageStocker=&_CurrentLanguageStocker;
	int	Numb=CurrentLanguageStocker->UIStringR.GetNumber();
	ui.tableWidget->setRowCount(Numb);
	int	N=0;
	for(UIStringResource *a=CurrentLanguageStocker->UIStringR.GetFirst();a!=NULL;a=a->GetNext(),N++){
		QTableWidgetItem *w;
		w=ui.tableWidget->item (N, 0);
		if(w==NULL)
			ui.tableWidget->setItem(N,0,(w=new QTableWidgetItem()));
		w->setText(a->UIClassName);
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		
		w=ui.tableWidget->item (N, 1);
		if(w==NULL)
			ui.tableWidget->setItem(N,1,(w=new QTableWidgetItem()));
		w->setText(a->ClassTypeName);
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		
		w=ui.tableWidget->item (N, 2);
		if(w==NULL)
			ui.tableWidget->setItem(N,2,(w=new QTableWidgetItem()));
		w->setText(a->ControlName);
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		
		w=ui.tableWidget->item (N, 3);
		if(w==NULL)
			ui.tableWidget->setItem(N,3,(w=new QTableWidgetItem()));
		w->setText(a->PropertyName);
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		
		
		for(int i=0;i<10;i++){
			LanguageString *q=a->GetLanguageString(i);
			if(q==NULL)
				break;
			w=ui.tableWidget->item (N, 4+i);
			if(w==NULL)
				ui.tableWidget->setItem(N,4+i,(w=new QTableWidgetItem()));
			w->setText(q->GetFirstString());
			w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
	}
}

ViewerUI::~ViewerUI()
{

}


void ViewerUI::on_pushButton_clicked()
{
	close();
}