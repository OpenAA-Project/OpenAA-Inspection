/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\ListHistoryButton\ListHistoryButtonForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ListHistoryButtonResource.h"
#include "ListHistoryButtonForm.h"
#include "XDLLOnly.h"
#include "XDataInLayer.h"
#include "XResultDLLManager.h"
#include "XGeneralFunc.h"
#include "ListHistoryButtonPacket.h"
#include "XWriteResultThread.h"
#include <QMessageBox>

extern	char	*sRoot;
extern	char	*sName;

ListHistoryButtonForm::ListHistoryButtonForm(LayersBase *Base ,QWidget *parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	LBase=Base;
	ParentWidget=(ListHistoryButton *)parent;

	ui.tableWidgetHistory->setColumnWidth (0,40);
	ui.tableWidgetHistory->setColumnWidth (1,100);
	ui.tableWidgetHistory->setColumnWidth (2,30);
	ui.tableWidgetHistory->setColumnWidth (3,30);
	ui.tableWidgetHistory->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableWidgetHistory->setSelectionBehavior(QAbstractItemView::SelectRows);

	connect(ui.tableWidgetHistory,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(tableWidgetHistoryDoubleClicked(QModelIndex)));
	connect(ui.ButtonReset		 ,SIGNAL(clicked())					,this,SLOT(ButtonResetClicked()));
}

ListHistoryButtonForm::~ListHistoryButtonForm()
{
}

void ListHistoryButtonForm::tableWidgetHistoryDoubleClicked(QModelIndex)
{
	int	row=ui.tableWidgetHistory->currentRow();
	if(row<0){
		return;
	}
	int	n=0;
	ResultHistry *resultHistory=NULL;
	for(ResultHistry *a=LBase->GetResultHistryData()->GetLast();a!=NULL;a=a->GetPrev(),n++){
		if(n==row){
			resultHistory=a;
			break;
		}
	}
	if(resultHistory==NULL){
		return;
	}

	if(QMessageBox::question ( NULL, LangSolver.GetString(ListHistoryButtonForm_LS,LID_8)/*"Confirmation"*/, LangSolver.GetString(ListHistoryButtonForm_LS,LID_9)/*"Delete OK? "*/, QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		for(int page=0;page<LBase->GetPageNumb();page++){
			GUIReqRemoveHistry	RCmd(LBase,sRoot,sName ,page);
			RCmd.SendOnly(NULL,page,0);
		}
		LBase->GetResultDLLBase()->RemoveResult(LBase->GetMachineID() ,resultHistory->ResultTime,resultHistory->Result);
		ParentWidget->ShowInPlayer(-1);

		//検査結果情報の更新
		ExecCmdListHistoryButtonUpdate();
	}
}

void ListHistoryButtonForm::ButtonResetClicked()
{
	LBase->GetResultHistryData()->Reset();
	ParentWidget->ShowInPlayer(-1);

	//検査結果情報の更新
	ExecCmdListHistoryButtonUpdate();
}

void ListHistoryButtonForm::ExecCmdListHistoryButtonUpdate()
{
	//TransmitDirectly
	GUIFormBase	*pShowMasterNames=LBase->FindByName(/**/"Panel",/**/"ShowResultInformation" ,/**/"");
	if(pShowMasterNames!=NULL){
		CmdListHistoryButtonUpdate	CmdResetFunc(LBase);
		pShowMasterNames->TransmitDirectly(&CmdResetFunc);
	}
}

//==================================================================================
GUIReqRemoveHistry::GUIReqRemoveHistry(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
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
