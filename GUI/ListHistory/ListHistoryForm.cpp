/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListHistory\ListHistoryForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ListHistoryFormResource.h"
#include "ListHistoryForm.h"
#include "XDLLOnly.h"
#include "XDataInLayer.h"
#include "XResultDLLManager.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XSyncGUI.h"
#include "XWriteResultThread.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ListHistoryForm::ListHistoryForm(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	SyncMode		=false;
	ColorOK			=Qt::white;
	ColorNG			=Qt::red;
	ColorNot		=Qt::gray;
	ColorIrregular	=Qt::yellow;
	LocalMode		=false;

	ShowColumnID	=true;
	ShowColumnTime	=true;
	ShowColumnOKNG	=true;
	ShowColumnSV	=true;
	ShowColumnMS	=true;

	ColumnNoID		=0;
	ColumnNoTime	=1;
	ColumnNoOKNG	=2;
	ColumnNoSV		=3;
	ColumnNoMS		=4;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	ui.tableWidgetHistory->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableWidgetHistory->setSelectionBehavior(QAbstractItemView::SelectRows);

	EditMode=false;
}

ListHistoryForm::~ListHistoryForm()
{

}

void	ListHistoryForm::Prepare(void)
{
	int	ColumnNo=0;
	if(ShowColumnID==true){
		ColumnNoID=ColumnNo;
		ui.tableWidgetHistory->setColumnWidth (ColumnNo,40);
		QTableWidgetItem *w=ui.tableWidgetHistory->horizontalHeaderItem(ColumnNo);
		w->setText("ID");
		ColumnNo++;
	}
	if(ShowColumnTime==true){
		ColumnNoTime=ColumnNo;
		ui.tableWidgetHistory->setColumnWidth (ColumnNo,100);
		QTableWidgetItem *w=ui.tableWidgetHistory->horizontalHeaderItem(ColumnNo);
		w->setText("Date/Time");
		ColumnNo++;
	}
	if(ShowColumnOKNG==true){
		ColumnNoOKNG=ColumnNo;
		ui.tableWidgetHistory->setColumnWidth (ColumnNo,30);
		QTableWidgetItem *w=ui.tableWidgetHistory->horizontalHeaderItem(ColumnNo);
		w->setText("NG");
		ColumnNo++;
	}
	if(ShowColumnSV==true){
		ColumnNoSV=ColumnNo;
		ui.tableWidgetHistory->setColumnWidth (ColumnNo,30);
		QTableWidgetItem *w=ui.tableWidgetHistory->horizontalHeaderItem(ColumnNo);
		w->setText("SV");
		ColumnNo++;
	}

	ResizeAction();
	if((GetParamComm()->Mastered==true && GetParamGlobal()->TotalCameraNumb!=0 && GetParamComm()->ConnectedPCNumb==0)
	|| (GetParamComm()->Mastered==false && GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID))!=0){
		if(ShowColumnMS==true){
			ColumnNoMS=ColumnNo;
			ColumnNo++;
			LocalMode=true;
			QTableWidgetItem *w=ui.tableWidgetHistory->horizontalHeaderItem(ColumnNoMS);
			w->setText("ms");		
			ui.tableWidgetHistory->setColumnWidth (ColumnNoMS,40);
		}
	}
	ui.tableWidgetHistory->setColumnCount(ColumnNo);
}
void	ListHistoryForm::ReadyParam(void)
{
	StrResultNot	=LangSolver.GetString(ListHistoryForm_LS,LID_1)/*"Not"*/;
	StrResultOK		=LangSolver.GetString(ListHistoryForm_LS,LID_2)/*"OK"*/;
	StrResultTMHalt	=LangSolver.GetString(ListHistoryForm_LS,LID_3)/*"TM-Halt"*/;
	StrResultErHalt	=LangSolver.GetString(ListHistoryForm_LS,LID_4)/*"Er-Halt"*/;
	StrResultNG		=LangSolver.GetString(ListHistoryForm_LS,LID_5)/*"NG"*/;
	StrResultNGOther=LangSolver.GetString(ListHistoryForm_LS,LID_6)/*"NG Other"*/;
	StrWrittenTrue	=LangSolver.GetString(ListHistoryForm_LS,LID_7)/*"*"*/;
	StrWrittenFalse	=LangSolver.GetString(ListHistoryForm_LS,LID_8)/*"X"*/;
}

void	ListHistoryForm::ResizeAction()
{
	ui.frame->move(0,height()-ui.frame->height());
	ui.frame->resize(width()-1,ui.frame->height());
	ui.tableWidgetHistory->move(0,0);
	ui.tableWidgetHistory->resize(width()-1,height()-ui.frame->height());
}

void	ListHistoryForm::ShowInPlayer(int64 shownInspectionID)
{
	LayersBase	*LBase=GetLayersBase();
	int	row=0;
	ui.tableWidgetHistory->setUpdatesEnabled(false);
	ui.tableWidgetHistory->setRowCount(LBase->GetResultHistryData()->GetNumber());
	for(ResultHistry *a=LBase->GetResultHistryData()->GetLast();a!=NULL;a=a->GetPrev(),row++){
		QTableWidgetItem *W;
		if(ShowColumnID==true){
			W=ui.tableWidgetHistory->item ( row, ColumnNoID);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetHistory->setItem ( row, ColumnNoID,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(QString::number(a->InspectionID));
		}
		if(ShowColumnTime==true){
			W=ui.tableWidgetHistory->item ( row, ColumnNoTime);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetHistory->setItem ( row, ColumnNoTime,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->ResultTime.toString(/**/"yy/MM/dd hh:mm:ss"));
		}
		if(ShowColumnOKNG==true){
			W=ui.tableWidgetHistory->item ( row, ColumnNoOKNG);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetHistory->setItem ( row, ColumnNoOKNG,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			switch(a->Result){
				case 0:	W->setText(StrResultNot);
						W->setBackground(QBrush(ColorNot));
						break;
				case 1:	W->setText(StrResultOK);
						W->setBackground(QBrush(ColorOK));
						break;
				case 2:	if(a->TimeOutBreak==true)
							W->setText(StrResultTMHalt);
						else if(a->MaxErrorBreak==true)
							W->setText(StrResultErHalt);
						else
							W->setText(StrResultNG);
						W->setBackground(QBrush(ColorIrregular));
						break;
				default:	
						W->setText(StrResultNGOther);
						W->setBackground(QBrush(ColorIrregular));
						break;
			}
		}
		if(ShowColumnSV==true){
			W=ui.tableWidgetHistory->item ( row, ColumnNoSV);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetHistory->setItem ( row, ColumnNoSV,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			if(a->Written==true)
				W->setText(StrWrittenTrue);
			else
				W->setText(StrWrittenFalse);
		}
		if(LocalMode==true && ShowColumnMS==true){
			W=ui.tableWidgetHistory->item (row, ColumnNoMS);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetHistory->setItem ( row, ColumnNoMS,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(QString::number(a->ProcessMilisec));
		}
	}
	ui.tableWidgetHistory->setUpdatesEnabled(true);
	ui.labelOK ->setText(QString::number(LBase->GetResultHistryData()->GetCount(1)));
	ui.labelNG ->setText(QString::number(LBase->GetResultHistryData()->GetCount(2)));
	ui.labelSUM->setText(QString::number(LBase->GetResultHistryData()->GetAllCount()));

	if(OutputFileName.isEmpty()==false){
		QFile	F(OutputFileName);
		if(F.open(QIODevice::WriteOnly)==true){
			LBase->GetResultHistryData()->Save(&F);
		}
	}
}
void	ListHistoryForm::BuildForShow(void)
{
	ShowInPlayer(-1);
}

void ListHistoryForm::on_ButtonReset_clicked()
{
	GetLayersBase()->GetResultHistryData()->Reset();

	if(SyncMode==false){
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			bool	checked=true;
			::Save(&Buff,checked);
			TxSync(Buff.buffer());
		}
	}

	ShowInPlayer(-1);
}

void	ListHistoryForm::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);

	bool checked;
	::Load(&Buff,checked);

	SyncMode=true;
	on_ButtonReset_clicked();
	SyncMode=true;
}

void ListHistoryForm::on_tableWidgetHistory_doubleClicked(QModelIndex)
{
	int	row=ui.tableWidgetHistory->currentRow();
	if(row<0)
		return;
	int	n=0;
	ResultHistry *resultHistory=NULL;
	for(ResultHistry *a=GetLayersBase()->GetResultHistryData()->GetLast();a!=NULL;a=a->GetPrev(),n++){
		if(n==row){
			resultHistory=a;
			break;
		}
	}
	if(resultHistory==NULL)
		return;
	GetLayersBase()->GetResultThread()->SetCastAll();
	GetLayersBase()->GetResultThread()->WaitForFinishingCast();

	if(QMessageBox::question ( NULL, LangSolver.GetString(ListHistoryForm_LS,LID_9)/*"Confirmation"*/, LangSolver.GetString(ListHistoryForm_LS,LID_10)/*"Delete OK? "*/, QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		if(EditMode==false){
			for(int page=0;page<GetPageNumb();page++){
				GUIReqRemoveHistry	RCmd(GetLayersBase(),sRoot,sName ,page);
				RCmd.SendOnly(NULL,page,0);
			}
			GetLayersBase()->GetResultDLLBase()->RemoveResult(GetLayersBase()->GetMachineID() ,resultHistory->ResultTime,resultHistory->Result);
			if(row==0){
				GetLayersBase()->DecrementInspectID();
			}
		}
		else{
			//?-????i??
			int i=0;
			for(ResultHistry *a=GetLayersBase()->GetResultHistryData()->GetLast();a!=NULL;a=a->GetPrev(),i++){
				if(i==row){
					GetLayersBase()->GetResultHistryData()->RemoveResult(a->ResultTime);
					break;
				}
			}
		}

		ShowInPlayer(-1);
	}
}

//==================================================================================
GUIReqRemoveHistry::GUIReqRemoveHistry(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUIReqRemoveHistry::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		for(int i=0;i<10;i++){
			int	N=GetLayersBase()->GetResultThread()->GetStockedCount();
			if(N==0){
				break;
			}
			GSleep(2000);
			int	M=GetLayersBase()->GetResultThread()->GetStockedCount();
			if(N==M){
				break;
			}
		}
		GetLayersBase()->GetResultThread()->SetCastAll();
		GetLayersBase()->GetResultThread()->WaitForFinishingCast();
	}
	SendAck(localPage);
}
