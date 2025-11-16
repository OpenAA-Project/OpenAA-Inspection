#include "PropertyMaskingPIResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMaskingPI\PropertyMaskingPIForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyMaskingPIForm.h"
#include "XDisplayImage.h"
#include "XGUI.h"
#include "PropertyMaskingPI.h"
#include "XPropertyMaskingPIPacket.h"
#include "SelectLibraryInMaskForm.h"
#include "XGeneralDialog.h"
#include "ImageControlTools.h"
#include <omp.h>
#include "XDisplayImagePacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyMaskingPIForm::PropertyMaskingPIForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	//LangSolver.SetUI(this);
	ui.tableWidgetMaskingList->setColumnWidth (0,40);
	ui.tableWidgetMaskingList->setColumnWidth (1,40);
	ui.tableWidgetMaskingList->setColumnWidth (2,50);
	ui.tableWidgetMaskingList->setColumnWidth (3,40);
	ui.tableWidgetMaskingList->setColumnWidth (4,150);
}

PropertyMaskingPIForm::~PropertyMaskingPIForm()
{

}
void	PropertyMaskingPIForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AddMaskingPIAreaPacket	*MaskAP=dynamic_cast<AddMaskingPIAreaPacket *>(packet);
	if(MaskAP!=NULL){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(MaskAP->Area,PageList);

		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
			FlexArea	A=MaskAP->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				GUICmdAddMaskingPIArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),pdata->GetPage());
				Cmd.MaskArea=A;
				Cmd.Effective=MaskAP->Effective;
				Cmd.LimitedLib=MaskAP->LimitedLib;
				Cmd.Send(NULL,pdata->GetPage(),0);
			}
		}
		ShowAreaGrid();
	}
	CmdMaskingPIDeleteItemPacket	*MaskDel=dynamic_cast<CmdMaskingPIDeleteItemPacket *>(packet);
	if(MaskDel!=NULL){
		ShowAreaGrid();
	}
	CmdMaskingPIDrawOnOffPacket	*MDrawOnOff=dynamic_cast<CmdMaskingPIDrawOnOffPacket *>(packet);
	if(MDrawOnOff!=NULL){
		if(ui.toolButtonEffective->isChecked()==true)
			MDrawOnOff->Effective=true;
		if(ui.toolButtonIneffective->isChecked()==true)
			MDrawOnOff->Ineffective=true;
	}
}
void	PropertyMaskingPIForm::BuildForShow(void)
{
	ShowAreaGrid();
}
void	PropertyMaskingPIForm::ShowInEdit(void)
{
	ShowAreaGrid();
}

void	PropertyMaskingPIForm::ShowAreaGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendMaskPIList	**BmpReceiver=new GUICmdSendMaskPIList*[GetParamGlobal()->PageNumb];
	GUICmdReqMaskPIList		**BmpRequester=new GUICmdReqMaskPIList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page]=new GUICmdSendMaskPIList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]=new GUICmdReqMaskPIList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		if(ui.toolButtonEffective->isChecked()==true)
			BmpRequester[page]->EffectiveMode=true;
		if(ui.toolButtonIneffective->isChecked()==true)
			BmpRequester[page]->IneffectiveMode=true;
	}

	MaskInfo.RemoveAll();
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page])==true
		&& BmpReceiver[page]->IsReceived()==true){
			MaskInfo+=BmpReceiver[page]->MaskInfo;
		}
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	int	N=0;
	int	Numb=MaskInfo.GetNumber();
	ui.tableWidgetMaskingList->setRowCount(Numb);
	MaskingPIListForPacket **LTable=new MaskingPIListForPacket*[Numb];
	for(MaskingPIListForPacket *L=MaskInfo.GetFirst();L!=NULL;L=L->GetNext(),N++){
		LTable[N]=L;
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<N;i++){
			MaskingPIListForPacket *L=LTable[i];
		//for(MaskingListForPacket *L=MaskInfo.GetFirst();L!=NULL;L=L->GetNext()){
			QTableWidgetItem *w;
			w=ui.tableWidgetMaskingList->item (i, 0);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(i,0,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(QString::number(L->Page));
		
			w=ui.tableWidgetMaskingList->item (i, 1);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(i,1,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			if(L->Effective==true)
				w->setText(LangSolver.GetString(PropertyMaskingPIForm_LS,LID_0)/*"ON"*/);
			else
				w->setText(LangSolver.GetString(PropertyMaskingPIForm_LS,LID_1)/*"OFF"*/);
	
			w=ui.tableWidgetMaskingList->item (i, 2);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(i,2,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			int	LibNumb=L->LimitedLib.GetNumber();
			w->setText(QString::number(LibNumb));
	
			w=ui.tableWidgetMaskingList->item (i, 3);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(i,3,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(	 QString(/**/"(")
						+QString::number(L->x1)+QString(/**/",")+QString::number(L->y1)
						+QString(/**/")-(")
						+QString::number(L->x2)+QString(/**/",")+QString::number(L->y2)
						+QString(/**/")"));
		}
	}
	delete	[]LTable;

	ReEntrant=false;
}


void PropertyMaskingPIForm::on_tableWidgetMaskingList_clicked(const QModelIndex &MIndex)
{
	MaskingPIListForPacket *L=MaskInfo.GetItem(MIndex.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"MaskingImagePIPanel",/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->Page,0,L->ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}

}

void PropertyMaskingPIForm::on_tableWidgetMaskingList_doubleClicked(QModelIndex)
{
	QModelIndex	RIndex=ui.tableWidgetMaskingList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	MaskingPIListForPacket *L=MaskInfo.GetItem(R);
	if(L==NULL)
		return;
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(false,GetLayersBase());
	GeneralDialog	D(GetLayersBase(),DForm,this);
	DForm->SetSelected(L->LimitedLib);
	D.exec();
	if(DForm->RetOK==false)
		return;

	GUICmdChangeMaskingPIAttr	Cmd(GetLayersBase(),sRoot,sName,L->Page);
	Cmd.ItemID		=L->ItemID;
	Cmd.GlobalPage	=L->Page;
	Cmd.Effective	=DForm->Effective;
	Cmd.LimitedLib	=DForm->GetSelectedList();
	Cmd.Send(NULL,L->Page,0);
	ShowAreaGrid();
}

void PropertyMaskingPIForm::on_toolButtonEffective_clicked()
{
	ShowAreaGrid();
}

void PropertyMaskingPIForm::on_toolButtonIneffective_clicked()
{
	ShowAreaGrid();
}