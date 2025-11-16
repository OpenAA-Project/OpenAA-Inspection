/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\SelectCodecForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "SelectCodecForm.h"
#include "XLanguageSolver.h"
#include <QTextCodec>

extern	LanguageStocker	LStocker;

SelectCodecForm::SelectCodecForm(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QTextCodec *currentCodec=QTextCodec::codecForLocale();
	QList<QByteArray>	Q=QTextCodec::availableCodecs ();
	for(int i=0;i<Q.count();i++){
		QByteArray	q=Q.value(i);
		char	*s=(char *)q.data();
		ui.listWidgetCodec->addItem(s);
		if(currentCodec!=NULL){
			if(strcmp((char *)currentCodec->name().data(),s)==0){
				ui.listWidgetCodec->setCurrentRow(i);
			}
		}
	}
}

SelectCodecForm::~SelectCodecForm()
{
}


void SelectCodecForm::on_pushButtonSelect_clicked()
{
	QList<QByteArray>	Q=QTextCodec::availableCodecs ();
	QByteArray	q=Q.value(ui.listWidgetCodec->currentRow());
	char	*s=(char *)q.data();
	LStocker.SetCurrentCodec(s);
	LStocker.SaveSettingFile();
	close();

}

void SelectCodecForm::on_listWidgetCodec_doubleClicked(QModelIndex)
{
	on_pushButtonSelect_clicked();
}