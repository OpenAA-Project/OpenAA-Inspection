/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\CodecListSelecterForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "CodecListSelecterForm.h"
#include "XLanguageSolver.h"
#include <QTextCodec>
#include "XGeneralFunc.h"

extern	LanguageStocker	LStocker;

CodecListSelecterForm::CodecListSelecterForm(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ComboListPointer[0]=ui.comboBoxLang1;
	ComboListPointer[1]=ui.comboBoxLang2;
	ComboListPointer[2]=ui.comboBoxLang3;
	ComboListPointer[3]=ui.comboBoxLang4;
	ComboListPointer[4]=ui.comboBoxLang5;
	ComboListPointer[5]=ui.comboBoxLang6;
	ComboListPointer[6]=ui.comboBoxLang7;
	ComboListPointer[7]=ui.comboBoxLang8;
	ComboListPointer[8]=ui.comboBoxLang9;
	ComboListPointer[9]=ui.comboBoxLang10;

	QList<QByteArray>	Q=QTextCodec::availableCodecs ();
	for(int i=0;i<Q.count();i++){
		QByteArray	q=Q.value(i);
		char	*s=(char *)q.data();

		for(int j=0;j<MAXLANGUAGECOUNT;j++){
			ComboListPointer[j]->addItem(s);
			if(LStocker.CodecList[j]!=NULL){
				if(strcmp(LStocker.CodecList[j],s)==0){
					ComboListPointer[j]->setCurrentIndex(i);
				}
			}
		}
	}
}

CodecListSelecterForm::~CodecListSelecterForm()
{

}


void CodecListSelecterForm::on_pushButtonOK_clicked()
{
	char	buff[1000];

	for(int j=0;j<MAXLANGUAGECOUNT;j++){
		if(ComboListPointer[j]->currentIndex()>=0){
			QString	s=ComboListPointer[j]->itemText(ComboListPointer[j]->currentIndex());
			QString2Char(s ,buff,sizeof(buff)-1);
			if(LStocker.CodecList[j]!=NULL)
				delete	[]LStocker.CodecList[j];
			LStocker.CodecList[j]=new char[strlen(buff)+1];
			strcpy(LStocker.CodecList[j],buff);
		}
	}
	LStocker.SaveSettingFile();
	close();
}
