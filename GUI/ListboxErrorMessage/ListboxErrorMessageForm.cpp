#include "ListboxErrorMessageResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListboxErrorMessage\ListboxErrorMessageForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ListboxErrorMessageForm.h"
#include "XDLLOnly.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XResult.h"
#include "XGUIFormBase.h"
#include "XGeneralFunc.h"

ListboxErrorMessageForm::ListboxErrorMessageForm(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	ui.tableWidget->setColumnWidth(0,30);
	ui.tableWidget->setColumnWidth(1,60);
	ui.tableWidget->setColumnWidth(2,40);
	ui.tableWidget->setColumnWidth(3,50);
	ui.tableWidget->setColumnWidth(4,120);

	ui.tableWidgetPageStatus->setColumnCount(GetPageNumb());
	int	W=(ui.tableWidgetPageStatus->width()-16)/GetPageNumb();
	for(int page=0;page<GetPageNumb();page++){
		ui.tableWidgetPageStatus->setColumnWidth(page,W);
	}
}

ListboxErrorMessageForm::~ListboxErrorMessageForm()
{

}

void	ListboxErrorMessageForm::ShowInPlayer(int64 shownInspectionID)
{
	ui.tableWidget->setRowCount(GetLayersBase()->GetErrorCount());
	int	Row=0;
	for(ErrorCodeList *e=GetLayersBase()->GetErrorContainer()->GetLast();e!=NULL;e=e->GetPrev(),Row++){
		SetDataToTable(ui.tableWidget,0,Row,QString::number(e->GetPage()));
		SetDataToTable(ui.tableWidget,1,Row,e->GetErrorTime().toString(/**/"yy/MM/dd hh:mm:ss"));
		SetDataToTable(ui.tableWidget,2,Row,QString::number(e->GetErrorCode()));
		switch(e->GetLevel()){
			case ErrorCodeList::_Critical:
				SetDataToTable(ui.tableWidget,3,Row,LangSolver.GetString(ListboxErrorMessageForm_LS,LID_0)/*"Critical"*/);
				break;
			case ErrorCodeList::_Important:
				SetDataToTable(ui.tableWidget,3,Row,LangSolver.GetString(ListboxErrorMessageForm_LS,LID_1)/*"Important"*/);
				break;
			case ErrorCodeList::_Alart:
				SetDataToTable(ui.tableWidget,3,Row,LangSolver.GetString(ListboxErrorMessageForm_LS,LID_2)/*"Alart"*/);
				break;
			case ErrorCodeList::_Message:
				SetDataToTable(ui.tableWidget,3,Row,LangSolver.GetString(ListboxErrorMessageForm_LS,LID_3)/*"Message"*/);
				break;
			default:
				SetDataToTable(ui.tableWidget,3,Row,QString(/**/""));
		}
		::SetDataToTable(ui.tableWidget,4,Row,e->GetMessageStr());
	}
	ui.lineEditCount->setText(QString::number(Row));
	ShowStatus();
}
void	ListboxErrorMessageForm::BuildForShow(void)
{
}

void ListboxErrorMessageForm::ShowStatus(void)
{
	ResultInspection	*eRes=GetLayersBase()->GetCurrentResultForCalc();
	if(eRes!=NULL){
		DataInExecuter	*eRe=GetLayersBase()->GetExecuter(eRes);
		for(int page=0;page<GetPageNumb();page++){
			if(eRe->GetReceivedResultCounts()[page].Result==-1){
				SetDataToTable(ui.tableWidgetPageStatus,page,0,/**/"Not");
			}
			else{
				SetDataToTable(ui.tableWidgetPageStatus,page,0,/**/"Ok");
			}
		}
	}
}

void ListboxErrorMessageForm::on_pushButtonClear_clicked()
{
	GetLayersBase()->ClearErrorCount();
	ShowInPlayer(-1);
}
void ListboxErrorMessageForm::on_pushButtonUpdate_clicked()
{
	ShowStatus();
}
