/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\XML\MTXMLServer\MTXMLServer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "MTXMLServer.h"
#include <QFileDialog>
#include "XGeneralFunc.h"

MTXMLServer::MTXMLServer(QWidget *parent, Qt::WindowFlags flags)
	//: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	XMLMain=NULL;
	Element=NULL;
	Answer=NULL;
	wAnswer=NULL;
	MatchTag1=NULL;
	MatchTag2=NULL;
}

MTXMLServer::~MTXMLServer()
{
}

void MTXMLServer::on_ButtonFileName_clicked()
{
	if(XMLMain!=NULL)
		return;

	QString	FileName=QFileDialog::getOpenFileName ( 0, QString("XML File"));
	if(FileName.isEmpty()==false){
		XMLMain=new XMLMainStock(FileName);
		XMLMain->LoadFromStream();
	}
}

void MTXMLServer::on_ButtonAddElement_clicked()
{
	if(XMLMain==NULL)
		return;
	QString	Q=ui.textSrc->document()->toPlainText();
	int	len=Q.length();
	char	*buff=new char[len*2+1];
	int	n=::QString2Char(Q, buff ,len*2+1);
	QByteArray AA=QByteArray(buff);
	XMLMain->Append(XMLMain->ID, AA.data());
	delete	[]buff;
}

void MTXMLServer::on_ButtonCreateFileName_clicked()
{
	if(XMLMain!=NULL)
		return;
	QString	FileName=QFileDialog::getSaveFileName( 0, QString("Create XML File"));
	if(FileName.isEmpty()==false){
		XMLMain=new XMLMainStock(FileName);
		XMLMain->Create();
	}
}

void MTXMLServer::on_ButtonAddInListElement_clicked()
{
	if(XMLMain==NULL)
		return;
	QString	Q=ui.textSrc->document()->toPlainText();
	int	len=Q.length();
	char	*buff=new char[len+2];
	int	n=::QString2Char(Q,buff ,len+2);
	XMLMain->Append(Answer->ID,buff);
	delete	[]buff;	
}
void MTXMLServer::on_ButtonSearch_clicked()
{
	if(XMLMain==NULL)
		return;
	QString	Q=ui.EditSearch->text();
	char	*buff=new char[Q.length()+2];
	int	n=::QString2Char(Q, buff, Q.length()+2);
	Answer=XMLMain->FindFirstByTag(buff);
	delete []buff;
	if (Answer!=NULL){
		int len = Answer->Size();
		char	*strbuff=new char[len+2];		
		Answer->MakeStr(strbuff, len+2);
		QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
		QString RetStr=code->toUnicode(QByteArray(strbuff));
		ui.textSearch->document()->setPlainText(RetStr);
		delete []strbuff;
	}else{
		ui.textSearch->document()->setPlainText(QString(""));
	}
}
void MTXMLServer::on_ButtonSearchNext_clicked()
{
	//if(XMLMain==NULL)
	if(Answer==NULL)
		return;
	QString	Q=ui.EditSearch->text();
	char	*buff=new char[Q.length()+2];
	int	n=::QString2Char(Q, buff, Q.length()+2);
	Answer=XMLMain->FindNextByTag(Answer, buff);
	delete []buff;
	
	if (Answer!=NULL){
		int len = Answer->Size();
		char	*strbuff=new char[len+2];
		Answer->MakeStr(strbuff, len+2);
		ui.textSearch->document()->setPlainText(strbuff);
		delete	[]strbuff;
	}else{
		ui.textSearch->document()->setPlainText(QString(""));
	}
}

void MTXMLServer::on_ButtonDelete_clicked()
{
	QString NGJ;
	if(XMLMain->Delete(Answer->ID, NGJ)==true){
		ui.textSearch->document()->setPlainText(QString(""));
	}
	
}

void MTXMLServer::on_ButtonSearchTag_clicked()
{
	if(XMLMain==NULL)
		return;
	QString	Q=ui.EditSearchTag->text();

	bool	Finished;
	XMLTag	MTag(NULL);
	char	*Tagbuff=new char[Q.length()+2];
	int	n=::QString2Char(Q, Tagbuff, Q.length()+2);
	MTag.Analyze(Tagbuff,Finished);
	delete []Tagbuff;

	Answer=XMLMain->MatchFirst(MTag);	
	if (Answer!=NULL){
		int len = Answer->Size();
		char	*buff=new char[len+1];
		Answer->MakeStr(buff, len+1);
		ui.textSearch->document()->setPlainText(buff);
		delete []buff;
	}else{
		ui.textSearch->document()->setPlainText(QString(""));
	}
}

void MTXMLServer::on_ButtonSearchNextTag_clicked()
{
	bool	Finished;
	if(XMLMain==NULL)
		return;
	QString	Q=ui.EditSearchTag->text();

	XMLTag	Tag(NULL);
	char	*Tagbuff=new char[Q.length()+2];
	int	n=::QString2Char(Q, Tagbuff, Q.length()+2);
	Tag.Analyze(Tagbuff, Finished);
	delete [] Tagbuff;
	Answer=XMLMain->MatchNext(Tag, Answer);


	if (Answer!=NULL){
		int len = Answer->Size();
		char	*buff=new char[len+2];
		Answer->MakeStr(buff, len+2);
		ui.textSearch->document()->setPlainText(buff);
		delete	[]buff;
	}else{
		ui.textSearch->document()->setPlainText(QString(""));
	}
}

void MTXMLServer::on_ButtonSearchTagToTag_clicked()
{
	if(XMLMain==NULL)
		return;
	QString	Q=ui.EditSearch->text();
	QString	Q1=ui.EditSearchTag->text();
	QString	Q2=ui.textSrc->toPlainText();

	char	*buff=new char[Q.length()+2];
	int	n=::QString2Char(Q, buff, Q.length()+2);
	XMLTag	MatchTag(NULL);
	bool	Finished;
	MatchTag.Analyze(buff, Finished);
	delete []buff;
	if(Q1!=""){
		char	*buff1=new char[Q1.length()+2];
		int	n1=::QString2Char(Q1, buff1, Q1.length()+2);
		MatchTag1=new XMLTag(NULL);
		bool	Finished1;
		MatchTag1->Analyze(buff1, Finished1);
		XMLMain->MatchXMLTag->append(MatchTag1);
		delete []buff1;
	}

	if(Q2!=""){
		char	*buff2=new char[Q2.length()+2];
		int	n2=::QString2Char(Q2, buff2, Q2.length()+2);
		MatchTag2=new XMLTag(NULL);
		bool	Finished2;
		MatchTag2->Analyze(buff2, Finished2);
		XMLMain->MatchXMLTag ->append(MatchTag2);
	}

	Answer=XMLMain->MatchFirst(MatchTag);
	if(Answer!=NULL){
		int len = Answer->Size();
		char	*strbuff=new char[len+2];
		Answer->MakeStr(strbuff, len+2);
		ui.textSearch->document()->setPlainText(strbuff);
		delete []strbuff;
	}else{
		ui.textSearch->document()->setPlainText(QString(""));
		XMLMain->MatchXMLTag->clear();
	}
	if(MatchTag1!=NULL){
		delete MatchTag1;
		MatchTag1=NULL;
	}
	if(MatchTag2!=NULL){
		delete MatchTag2;
		MatchTag2=NULL;
	}
}

void MTXMLServer::on_ButtonSearchNextTagToTag_clicked()
{
	if(XMLMain==NULL)
		return;
	QString	Q=ui.EditSearch->text();
	QString	Q1=ui.EditSearchTag->text();
	QString	Q2=ui.textSrc->toPlainText();

	char	*buff=new char[Q.length()+2];
	int	n=::QString2Char(Q, buff, Q.length()+2);
	XMLTag	MatchTag(NULL);
	bool	Finished;
	MatchTag.Analyze(buff, Finished);
	delete []buff;

	if(Q1!=""){
		char	*buff1=new char[Q1.length()+2];
		int	n1=::QString2Char(Q1, buff1, Q1.length()+2);
		MatchTag1=new XMLTag(NULL);
		bool	Finished1;
		MatchTag1->Analyze(buff1, Finished1);
		XMLMain->MatchXMLTag ->append(MatchTag1);
	}
	if(Q2!=""){
		char	*buff2=new char[Q2.length()+2];
		int	n2=::QString2Char(Q2, buff2, Q2.length()+2);
		MatchTag2=new XMLTag(NULL);
		bool	Finished2;
		MatchTag2->Analyze(buff2, Finished2);
		XMLMain->MatchXMLTag ->append(MatchTag2);
		delete []buff2;
	}

	Answer=XMLMain->MatchNext(MatchTag, Answer);
	if(Answer!=NULL){
		int len = Answer->Size();
		char	*strbuff=new char[len+2];
		Answer->MakeStr(strbuff, len+2);
		ui.textSearch->document()->setPlainText(strbuff);
	}else{
		ui.textSearch->document()->setPlainText(QString(""));
	}
	XMLMain->MatchXMLTag->clear();
	if(MatchTag1!=NULL){
		delete MatchTag1;
		MatchTag1=NULL;
	}
	if(MatchTag2!=NULL){
		delete MatchTag2;
		MatchTag2=NULL;
	}
}


void MTXMLServer::on_ButtonDelete_2_clicked()
{
	XMLMain->UpdateToStream();
}

void MTXMLServer::on_ButtonLast_clicked()
{
	char IST[4];
	strcpy(IST,"IST");
	Answer=XMLMain->FindLastByTag(IST);
	if (Answer!=NULL){
		int len = Answer->Size();
		char	*strbuff=new char[len+2];		
		Answer->MakeStr(strbuff, len+2);
		ui.textSearch->document()->setPlainText(strbuff);
		delete []strbuff;
	}else{
		ui.textSearch->document()->setPlainText(QString(""));
	}
}