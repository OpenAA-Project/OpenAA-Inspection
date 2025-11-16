/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PIOWatch\PIOWatch\PIOWatch.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include "PIOWatch.h"
#include "XPIOInterface.h"
#include "XPIOButton.h"
/*
//#define PIO64
#define PIO32
//#define PIO16
#if defined(PIO8)
	const int PIOBit=8;
#elif defined(PIO16)
	const int PIOBit=16;
#elif defined(PIO32)
	const int PIOBit=32;
#elif defined(PIO64)
	const int PIOBit=64;
#endif
*/
PIOClass    PIO(NULL,false);

static int IOInBitCount[2];
static int IOOutBitCount[2];

PIOWatch::PIOWatch(QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	tPIORead[0]		.SetBoardNumber(0);
	tPIORead[1]		.SetBoardNumber(1);
	tPIOReadOut[0]	.SetBoardNumber(0);
	tPIOReadOut[1]	.SetBoardNumber(1);

	connect(ui.pbRefer,			SIGNAL(clicked()),								this,SLOT(pbReferClicked()));
	connect(ui.twOUT,			SIGNAL(itemChanged(QTableWidgetItem *)),		this,SLOT(twOUTitemChanged(QTableWidgetItem *)));
	connect(ui.twOUT_2,			SIGNAL(itemChanged(QTableWidgetItem *)),		this,SLOT(twOUT_2itemChanged(QTableWidgetItem *)));
	connect(ui.pbClose,			SIGNAL(clicked()),								this,SLOT(pbCloseClicked()));
	connect(&tPIORead[0],		SIGNAL(SignalOnCheck(Qt::CheckState *,int)),	this,SLOT(SlotOnCheck(Qt::CheckState *,int)));
	connect(&tPIORead[1],		SIGNAL(SignalOnCheck(Qt::CheckState *,int)),	this,SLOT(SlotOnCheck(Qt::CheckState *,int)));
	connect(&tPIOReadOut[0],	SIGNAL(SignalOnCheckOut(Qt::CheckState *,int)),	this,SLOT(SlotOnCheckOut(Qt::CheckState *,int)));
	connect(&tPIOReadOut[1],	SIGNAL(SignalOnCheckOut(Qt::CheckState *,int)),	this,SLOT(SlotOnCheckOut(Qt::CheckState *,int)));
	connect(ui.chkEchoBack,		SIGNAL(toggled(bool)),							this,SLOT(chkEchoBackToggled(bool)));
	connect(ui.chkEchoBack_2,	SIGNAL(toggled(bool)),							this,SLOT(chkEchoBack_2Toggled(bool)));

	//PIOSetting.datの読み込み
	QString strPIODLL;
	QFile file(/**/"./PIOSetting.dat");
	if(file.open(QIODevice::ReadOnly)){
		QTextStream myStream(&file);
		strPIODLL=myStream.readLine();
		ui.lePIODLL->setText(strPIODLL);
		file.close();
	}

	if(strPIODLL.isEmpty()==true){
		setMinimumSize(520,height());
		setMaximumSize(520,height());
	}
	else if(PIODLLInit(strPIODLL)==false){
		QMessageBox::warning(this,tr("Error"),tr("DLL Initial Error."));
	}
}

PIOWatch::~PIOWatch()
{
}

void PIOWatch::closeEvent(QCloseEvent *event)
{
	tPIORead[0]		.SetStopped(true);
	tPIORead[1]		.SetStopped(true);
	tPIOReadOut[0]	.SetStopped(true);
	tPIOReadOut[1]	.SetStopped(true);
	if(maybeClose()){
		//PIO.PIOBrd=NULL;
		event->accept();
	}
	else{
		tPIORead[0]		.SetStopped(false);
		tPIORead[1]		.SetStopped(false);
		tPIOReadOut[0]	.SetStopped(false);
		tPIOReadOut[1]	.SetStopped(false);
		tPIORead[0].start();
		tPIORead[1].start();
		if(ui.chkEchoBack->checkState()==Qt::Checked){
			tPIOReadOut[0].start();
		}
		if(ui.chkEchoBack_2->checkState()==Qt::Checked){
			tPIOReadOut[1].start();
		}
		event->ignore();
	}
}

void PIOWatch::pbReferClicked()
{
	//PIODLLの選択
	QString strPIODLL=QFileDialog::getOpenFileName(
							this,tr("Please choose a '.dll' or '.so' files."),/**/"","Library (*.dll *.so)");

	//PIOSetting.datの書き込み
	QFile file(/**/"./PIOSetting.dat");
	if(file.open(QIODevice::WriteOnly)){
		QTextStream myStream(&file);
		myStream << strPIODLL << "\n";
		file.close();
	}
	if(strPIODLL==/**/""){
		return;
	}
	ui.lePIODLL->setText(strPIODLL);
	PIODLLInit(strPIODLL);
}

void PIOWatch::twOUTitemChanged(QTableWidgetItem *item)
{
	BYTE data=0;
	for(int Row=(item->row()&0xF8);Row<(item->row()&0xF8)+8;Row++){
		if(ui.twOUT->item(Row,0)->checkState()==Qt::Checked)
			data|=(0x01<<(Row&0x07));
	}
	PIO.SetByte(0,((item->row()&0xF8))>>3,data);
}

void PIOWatch::twOUT_2itemChanged(QTableWidgetItem *item)
{
	BYTE data=0;
	for(int Row=(item->row()&0xF8);Row<(item->row()&0xF8)+8;Row++){
		if(ui.twOUT_2->item(Row,0)->checkState()==Qt::Checked)
			data|=(0x01<<(Row&0x07));
	}
	PIO.SetByte(1,((item->row()&0xF8))>>3,data);
}

void PIOWatch::pbCloseClicked()
{
	close();
}

//終了判定
bool PIOWatch::maybeClose()
{
	int ret=QMessageBox::information(this, tr("Message"),
				tr("Do you want to close the application?"),
				QMessageBox::Yes | QMessageBox::Default,
				QMessageBox::Cancel | QMessageBox::Escape);
	if (ret == QMessageBox::Yes)
		return true;
	else
		return false;
}

void PIOWatch::SlotOnCheck(Qt::CheckState *State,int BoardNumber)
{
	for(int Row=0;Row<IOInBitCount[BoardNumber];Row++){
		if(!tPIORead[BoardNumber].GetStopped()){
			twIN[BoardNumber]->item(Row,0)->setCheckState(State[Row]);
		}
	}
}

void PIOWatch::SlotOnCheckOut(Qt::CheckState *State,int BoardNumber)
{
	for(int Row=0;Row<IOOutBitCount[BoardNumber];Row++){
		if(!tPIOReadOut[BoardNumber].GetStopped()){
			twOUT[BoardNumber]->item(Row,0)->setCheckState(State[Row]);
		}
	}
}

void PIOWatch::chkEchoBackToggled(bool checked)
{
	disconnect(ui.twOUT,SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(twOUTitemChanged(QTableWidgetItem *)));
	if(checked){
//		for(int Row=0;Row<PIOBit;Row++)
		for(int Row=0;Row<IOOutBitCount[0];Row++){
			ui.twOUT->item(Row,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		palette.setColor(QPalette::Base,QColor(Qt::cyan));
		ui.twOUT->setPalette(palette);
		tPIOReadOut[0].SetStopped(false);
		tPIOReadOut[0].start();	//OUT側のReadスレッドの開始
		return;
	}
	else{
		tPIOReadOut[0].SetStopped(true);	//OUT側のReadスレッドの停止
//		for(int Row=0;Row<PIOBit;Row++)
		for(int Row=0;Row<IOOutBitCount[0];Row++){
			ui.twOUT->item(Row,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
		}
		palette.setColor(QPalette::Base,QColor(Qt::white));
		ui.twOUT->setPalette(palette);
	}
	connect(ui.twOUT,SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(twOUTitemChanged(QTableWidgetItem *)));
}

void PIOWatch::chkEchoBack_2Toggled(bool checked)
{
	disconnect(ui.twOUT_2,SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(twOUT_2itemChanged(QTableWidgetItem *)));
	if(checked){
//		for(int Row=0;Row<PIOBit;Row++)
		for(int Row=0;Row<IOOutBitCount[1];Row++){
			ui.twOUT_2->item(Row,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		palette.setColor(QPalette::Base,QColor(Qt::cyan));
		ui.twOUT_2->setPalette(palette);
		tPIOReadOut[1].SetStopped(false);
		tPIOReadOut[1].start();	//OUT側のReadスレッドの開始
		return;
	}
	else{
		tPIOReadOut[1].SetStopped(true);	//OUT側のReadスレッドの停止
//		for(int Row=0;Row<PIOBit;Row++)
		for(int Row=0;Row<IOOutBitCount[1];Row++){
			ui.twOUT_2->item(Row,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
		}
		palette.setColor(QPalette::Base,QColor(Qt::white));
		ui.twOUT_2->setPalette(palette);
	}
	connect(ui.twOUT_2,SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(twOUT_2itemChanged(QTableWidgetItem *)));
}

bool PIOWatch::PIODLLInit(QString strDLLName)
{
	QString strIODefFile[2];
	strIODefFile[0]="./IODef.dat";
	strIODefFile[1]="./IODef-2.dat";

	PIO.ReadDefFileOfBoardName(strIODefFile[0]);
	PIO.ReadDefFileOfBoardName(strIODefFile[1]);
	if(!PIO.Initialize(this,strDLLName,false,"")){
		QMessageBox::warning(this,tr("Error"),strDLLName + tr("\nThe error occurred by initial of DLL."));
		tPIORead[0].SetStopped(true);
		tPIORead[1].SetStopped(true);
		return false;
	}

	//画面設定520
	int BoardCount=PIO.GetBoardCount();

	if(BoardCount==1){
		setMinimumSize(520,height());
		setMaximumSize(520,height());
	}
	else if(BoardCount==2){
		setMinimumSize(1040,height());
		setMaximumSize(1040,height());
	}

	twIN[0]=ui.twIN;
	twIN[1]=ui.twIN_2;

	twOUT[0]=ui.twOUT;
	twOUT[1]=ui.twOUT_2;

	disconnect(twOUT[0],SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(twOUTitemChanged(QTableWidgetItem *)));
	disconnect(twOUT[1],SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(twOUT_2itemChanged(QTableWidgetItem *)));

	for(int BoardCnt=0;BoardCnt<BoardCount;BoardCnt++){
		twIN[BoardCnt]->setColumnCount(1);
		twIN[BoardCnt]->horizontalHeader()->hide();
		twIN[BoardCnt]->verticalHeader()->hide();
		palette.setColor(QPalette::Base,QColor(Qt::cyan));
		twIN[BoardCnt]->setPalette(palette);
		ui.lePIODLL->setPalette(palette);

		twOUT[BoardCnt]->setColumnCount(1);
		twOUT[BoardCnt]->horizontalHeader()->hide();
		twOUT[BoardCnt]->verticalHeader()->hide();

		IOInBitCount[BoardCnt]	=PIO.GetPIOBrd(BoardCnt)->GetIOInBitCount();
		IOOutBitCount[BoardCnt]	=PIO.GetPIOBrd(BoardCnt)->GetIOOutBitCount();

		twIN[BoardCnt]->setRowCount(IOInBitCount[BoardCnt]);
		if(IOInBitCount[BoardCnt]<64){
			twIN[BoardCnt]->horizontalHeader()->resizeSection(0,247);
		}
		else{
			twIN[BoardCnt]->horizontalHeader()->resizeSection(0,231);
		}
		twOUT[BoardCnt]->setRowCount(IOOutBitCount[BoardCnt]);
		if(IOOutBitCount[BoardCnt]<64){
			twOUT[BoardCnt]->horizontalHeader()->resizeSection(0,247);
		}
		else{
			twOUT[BoardCnt]->horizontalHeader()->resizeSection(0,231);
		}

		QFile iodef(strIODefFile[BoardCnt]);
		if(!iodef.open(QFile::ReadOnly)){
			return false;
		}
		QTextStream iodefStream(&iodef);
		QString oneLine;
		QString pioInOut;
		QString pioName;
		int firstIndex;
		int lastIndex;
		QString InOut;

		int PIOBit[2];
		PIOBit[0]=IOInBitCount[BoardCnt];
		PIOBit[1]=IOOutBitCount[BoardCnt];
		for(int roop=0;roop<2;roop++){
			for(int i=0;i<PIOBit[roop];i++){
				if(iodefStream.atEnd()){
					break;
				}
				oneLine=iodefStream.readLine();
				firstIndex=oneLine.indexOf("\"");
				if(firstIndex==-1){
					i--;
					continue;
				}
				pioInOut=oneLine.left(firstIndex);
				if(roop==0){
					InOut="IN";
				}
				else{
					InOut="OUT";
				}
				if(pioInOut.trimmed()!=InOut.append(QString().setNum(i))){
					i--;
					continue;
				}
				lastIndex=oneLine.indexOf("\"",firstIndex+1);
				if(lastIndex==-1){
					i--;
					continue;
				}
				if(roop==0){
					QTableWidgetItem *itemIN=new QTableWidgetItem(pioInOut.trimmed().append("  ").append(oneLine.mid(firstIndex+1,lastIndex-firstIndex-1)));
					itemIN->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
					twIN[BoardCnt]->setItem(i,0,itemIN);
					itemIN->setCheckState(Qt::Unchecked);
					twIN[BoardCnt]->verticalHeader()->resizeSection(i,19);
				}
				else{
					QTableWidgetItem *itemOUT=new QTableWidgetItem(pioInOut.trimmed().append("  ").append(oneLine.mid(firstIndex+1,lastIndex-firstIndex-1)));
					itemOUT->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
					twOUT[BoardCnt]->setItem(i,0,itemOUT);
					itemOUT->setCheckState(Qt::Unchecked);
					twOUT[BoardCnt]->verticalHeader()->resizeSection(i,19);
				}
			}
		}
		iodef.close();
		tPIORead[BoardCnt]		.SetStopped(false);
		tPIOReadOut[BoardCnt]	.SetStopped(false);
		tPIORead[BoardCnt]		.start();	//IN側のReadスレッドの開始
	}
	connect(twOUT[0],SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(twOUTitemChanged(QTableWidgetItem *)));
	connect(twOUT[1],SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(twOUT_2itemChanged(QTableWidgetItem *)));

	return true;
}

PIOReadThread::PIOReadThread(int BoardNumber)
{
	Stopped		=false;
	BoardNumb	=BoardNumber;
}

void PIOReadThread::run()
{
	Qt::CheckState *StateArray=new Qt::CheckState[IOInBitCount[BoardNumb]];
	while(!Stopped){
		BYTE data;
		for(int Port=0;Port<(IOInBitCount[BoardNumb]>>3);Port++){
			data=PIO.GetByte(BoardNumb,Port);
			for(int Row=(Port<<3);Row<((Port+1)<<3);Row++){
				if((data&(0x01<<(Row&0x07)))!=0){
					StateArray[Row]=Qt::Checked;
				}
				else{
					StateArray[Row]=Qt::Unchecked;
				}
			}
		}
		emit SignalOnCheck(StateArray,BoardNumb);
		msleep(10);
	}
}

PIOReadOutThread::PIOReadOutThread(int BoardNumber)
{
	Stopped		=false;
	BoardNumb	=BoardNumber;
}

void PIOReadOutThread::run()
{
	Qt::CheckState *StateArray=new Qt::CheckState[IOOutBitCount[BoardNumb]];
	while(!Stopped){
		BYTE data;
		for(int Port=0;Port<(IOOutBitCount[BoardNumb]>>3);Port++){
			data=PIO.GetOutByte(BoardNumb,Port);
			for(int Row=(Port<<3);Row<((Port+1)<<3);Row++){
				if((data&(0x01<<(Row&0x07)))!=0)
					StateArray[Row]=Qt::Checked;
				else
					StateArray[Row]=Qt::Unchecked;
			}
		}
		emit SignalOnCheckOut(StateArray,BoardNumb);
		msleep(10);
	}
}
