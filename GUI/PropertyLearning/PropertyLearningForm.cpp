#include "AddFileDialogResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyLearning\PropertyLearningForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyLearningForm.h"
#include "XDataInLayer.h"
#include "XLearningPacket.h"
#include "ManualInputForm.h"
#include "swap.h"
#include "XLotInformation.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyLearningForm::PropertyLearningForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	AddFileDialogVar=NULL;
	StoredList=NULL;
	PickedList=NULL;
	SelectedPickupList=0;
}

PropertyLearningForm::~PropertyLearningForm()
{
	if(AddFileDialogVar!=NULL)
		delete	AddFileDialogVar;
	AddFileDialogVar=NULL;

	if(StoredList!=NULL)
		delete	[]StoredList;
	StoredList=NULL;

	if(PickedList!=NULL)
		delete	[]PickedList;
	PickedList=NULL;
}

void	PropertyLearningForm::BuildForShow(void)
{
	if(StoredList==NULL)
		StoredList=new LearningFileListContainer[GetPageNumb()];
	if(PickedList==NULL)
		PickedList=new LearningFileListContainer[GetPageNumb()];

	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqPickedFileList	RCmd(GetLayersBase(),sRoot,sName ,page);
		GUICmdAckPickedFileList	ACmd(GetLayersBase(),sRoot,sName ,page);
		RCmd.Send(page,0,ACmd);
		PickedList[page]=ACmd.List;
	}
	ShowTrialList();

	#ifdef _MSC_VER
	_CrtCheckMemory();
	#endif
}
void	PropertyLearningForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AddLearningArea	*AddLearningAreaVar=dynamic_cast<AddLearningArea *>(packet);
	if(AddLearningAreaVar!=NULL){
		ManualInputForm	D(GetLayersBase(),this);
		if(D.exec()==(int)true){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(AddLearningAreaVar->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
				FlexArea	A=AddLearningAreaVar->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					GUICmdAddLearningArea	Cmd(GetLayersBase(),sRoot,sName,pdata->GetPage());
					Cmd.Area=A;
					Cmd.Ok=D.Ok;
					Cmd.NGLevel=D.NGLevel;
					Cmd.Send(NULL,pdata->GetPage(),0);
				}
			}
			ShowAreaGrid();
		}
	}
}
void	PropertyLearningForm::ShowInEdit(void)
{
}

void PropertyLearningForm::on_tableWidgetTrialList_doubleClicked(QModelIndex)
{
	SelectedPickupList=ui.tableWidgetTrialList->currentRow();
	ui.listWidgetFileNamePerPage->clear();
	for(int page=0;page<GetPageNumb();page++){
		LearningFileList	*L=PickedList[page].GetItem(SelectedPickupList);
		ui.listWidgetFileNamePerPage->addItem(L->FileName);
	}

	for(int page=0;page<GetPageNumb();page++){
		GUICmdChangeLearningList	RCmd(GetLayersBase(),sRoot,sName ,page);
		RCmd.SelectedListNumber=SelectedPickupList;
		RCmd.Send(NULL,page,0);
	}
	ShowAreaGrid();
	BroadcastShowInEdit();
}

void PropertyLearningForm::on_tableWidgetAreaList_clicked(const QModelIndex &)
{

}

void PropertyLearningForm::on_pushButtonAddTrialFile_clicked()
{
	if(StoredList==NULL){
		return;
	}
	if(AddFileDialogVar==NULL){
		AddFileDialogVar=new AddFileDialog(GetLayersBase(),this);
	}
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqStoredFileList	RCmd(GetLayersBase(),sRoot,sName ,page);
		GUICmdAckStoredFileList	ACmd(GetLayersBase(),sRoot,sName ,page);
		RCmd.MasterCode		=GetLayersBase()->GetMasterCode();
		RCmd.LotAutoCount	=GetLayersBase()->GetLot(page)->GetLotAutoCount();
		RCmd.Send(page,0,ACmd);
		StoredList[page]=ACmd.List;
	}
	if(AddFileDialogVar->exec()==(int)true){
		int	Page=AddFileDialogVar->SelectedPage;
		int	R=ui.tableWidgetTrialList->currentRow();
		if(R<0)
			R=0;
		for(LearningFileList *L=AddFileDialogVar->SelectedList.GetFirst();L!=NULL;L=L->GetNext()){
			LearningFileList	*a=PickedList[Page].GetItem(R);
			if(a==NULL){
				a=new LearningFileList();
				PickedList[Page].AppendList(a);
			}
			GUICmdLearningAddFile	RCmd(GetLayersBase(),sRoot,sName,Page);
			RCmd.FileName	=L->FileName;
			RCmd.Index		=R;
			RCmd.Send(NULL,Page,0);
			*a=*L;
			R++;
		}
		ShowTrialList();
	}
}
		
void PropertyLearningForm::ShowTrialList(void)
{
	int	MaxL=0;
	for(int page=0;page<GetPageNumb();page++){
		MaxL=max(MaxL,(int)PickedList[page].GetNumber());
	}
	ui.tableWidgetTrialList->setRowCount(MaxL);
	ui.tableWidgetTrialList->setColumnCount(1+GetPageNumb());
	ui.tableWidgetTrialList->setColumnWidth(0,32);
	for(int page=0;page<GetPageNumb();page++){
		ui.tableWidgetTrialList->setHorizontalHeaderItem(page+1,new QTableWidgetItem(QString(/**/"Page ")+QString::number(page)));
		ui.tableWidgetTrialList->setColumnWidth(page+1,100);
	}

	for(int i=0;i<MaxL;i++){
		QTableWidgetItem *w;
		w=ui.tableWidgetTrialList->item (i, 0);
		if(w==NULL){
			ui.tableWidgetTrialList->setItem(i,0,(w=new QTableWidgetItem()));
			w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		w->setText(QString::number(i));
	}

	for(int page=0;page<GetPageNumb();page++){
		int	i=0;
		for(LearningFileList *a=PickedList[page].GetFirst();a!=NULL;a=a->GetNext(),i++){
			QTableWidgetItem *w;
			w=ui.tableWidgetTrialList->item (i, 1+page);
			if(w==NULL){
				ui.tableWidgetTrialList->setItem(i,1+page,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(a->FileName);
		}
	}
}

void PropertyLearningForm::ShowAreaGrid(void)
{
	ui.tableWidgetAreaList->setColumnWidth(0,32);
	ui.tableWidgetAreaList->setColumnWidth(1,56);
	ui.tableWidgetAreaList->setColumnWidth(2,64);
	ui.tableWidgetAreaList->setColumnWidth(3,160);

	AreaList.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqLearningAreaListContainer	RCmd(GetLayersBase(),sRoot,sName ,page);
		GUICmdAckLearningAreaListContainer	ACmd(GetLayersBase(),sRoot,sName ,page);
		RCmd.Send(page,0,ACmd);
		AreaList+=ACmd.List;
	}
	ui.tableWidgetAreaList->setRowCount(AreaList.GetNumber());
	int	i=0;
	for(LearningAreaList *L=AreaList.GetFirst();L!=NULL;L=L->GetNext(),i++){
		QTableWidgetItem *w;
		w=ui.tableWidgetAreaList->item (i, 0);
		if(w==NULL){
			ui.tableWidgetAreaList->setItem(i,0,(w=new QTableWidgetItem()));
			w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		w->setText(QString::number(L->GlobalPage));

		w=ui.tableWidgetAreaList->item (i, 1);
		if(w==NULL){
			ui.tableWidgetAreaList->setItem(i,1,(w=new QTableWidgetItem()));
			w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		if(L->Ok==true)
			w->setText(LangSolver.GetString(PropertyLearningForm_LS,LID_0)/*"‹••ñ”rœ"*/);
		else
			w->setText(LangSolver.GetString(PropertyLearningForm_LS,LID_1)/*"‚m‚f”­•ñ"*/);

		w=ui.tableWidgetAreaList->item (i, 2);
		if(w==NULL){
			ui.tableWidgetAreaList->setItem(i,2,(w=new QTableWidgetItem()));
			w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		w->setText(QString::number(L->NGLevel));

		w=ui.tableWidgetAreaList->item (i, 3);
		if(w==NULL){
			ui.tableWidgetAreaList->setItem(i,3,(w=new QTableWidgetItem()));
			w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		w->setText(QString(/**/"(")	+QString::number(L->X1)+QString(/**/",")+QString::number(L->Y1)+QString(/**/")-(")
									+QString::number(L->X2)+QString(/**/",")+QString::number(L->Y2)+QString(/**/")"));
	}
}

void PropertyLearningForm::on_pushButtonDelTrialFile_clicked()
{

}