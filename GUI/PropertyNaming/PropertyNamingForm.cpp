/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyNaming\PropertyNamingForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyNamingFormResource.h"
#include "PropertyNamingForm.h"
#include "XDisplayImage.h"
#include "XGUI.h"
#include "XPropertyNamingPacket.h"
#include "XGeneralDialog.h"
#include "ImageControlTools.h"
#include "InputNamingNameForm.h"
#include <omp.h>
#include "XDisplayImagePacket.h"
#include "swap.h"
#include "InputGroupDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyNamingForm::PropertyNamingForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base ,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	ui.tableWidgetNamingList->setColumnWidth (0,40);
	ui.tableWidgetNamingList->setColumnWidth (1,120);
	ui.tableWidgetNamingList->setColumnWidth (2,180);

	connect(ui.pushButtonGenerateIndex,SIGNAL(clicked()),this,SLOT(on_pushButtonGenerateIndex_clicked()));
	ShowGrid();
}

PropertyNamingForm::~PropertyNamingForm()
{

}

void	PropertyNamingForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AddNamingAreaPacket	*NamingAP=dynamic_cast<AddNamingAreaPacket *>(packet);
	if(NamingAP!=NULL){
		if(ui.toolButtonAutoCount->isChecked()==false){
			InputNamingNameForm	*DForm=new InputNamingNameForm(GetLayersBase());
			GeneralDialog	D(GetLayersBase(),DForm,this);
			D.exec();
			if(DForm->RetOK==true){
				CreateArea(DForm->InputedName,NamingAP->Area,DForm->Column,DForm->Row,0);
				ShowGrid();
			}
		}
		else{
			ui.toolButtonAutoCount->setChecked(false);
			int		X1,Y1,X2,Y2;
			NamingAP->Area.GetXY(X1,Y1,X2,Y2);
			if(X1>X2)
				swap(X1,X2);
			if(Y1>Y2)
				swap(Y1,Y2);

			AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Naming");
			int	CountX	=ui.spinBoxAutoCountX->value();
			int	CountY	=ui.spinBoxAutoCountY->value();
			double	CellX=(X2-X1)/((double)CountX);
			double	CellY=(Y2-Y1)/((double)CountY);

			MakeAreaNamePacket	MPacket(GetLayersBase());
			MPacket.FormatStr	=ui.lineEditCountFormat	->text();
			MPacket.CountX=CountX-1;
			MPacket.CountY=CountY-1;

			for(int y=0;y<CountY;y++){
				for(int x=0;x<CountX;x++){
					MPacket.X	=x;
					MPacket.Y	=y;
					Ab->TransmitDirectly(&MPacket);
							
					FlexArea	Area;
					Area.SetRectangle((int)(X1+CellX*x)			,(int)(Y1+CellY*y)
									, (int)(X1+CellX*(x+1)-1)	,(int)(Y1+CellY*(y+1)-1));

					CreateArea(MPacket.AreaName,Area,MPacket.Column,MPacket.Row
								,ui.spinBoxAutoExpand->value());
				}
			}
			ShowGrid();
		}
		return;
	}
	/*
	CmdMaskingDeleteItemPacket	*MaskDel=dynamic_cast<CmdMaskingDeleteItemPacket *>(packet);
	if(MaskDel!=NULL){
		ShowGrid();
	}
	*/
	GetCountPacket	*GetCountPacketVar=dynamic_cast<GetCountPacket *>(packet);
	if(GetCountPacketVar!=NULL){
		GetCountPacketVar->EnabledCountMode	=ui.toolButtonAutoCount->isChecked();
		GetCountPacketVar->Format			=ui.lineEditCountFormat	->text();
		GetCountPacketVar->CountX	=ui.spinBoxAutoCountX->value();
		GetCountPacketVar->CountY	=ui.spinBoxAutoCountY->value();
		return;
	}
	CancelCountPacket	*CancelCountPacketVar=dynamic_cast<CancelCountPacket *>(packet);
	if(CancelCountPacketVar!=NULL){
		ui.toolButtonAutoCount->setChecked(false);
		return;
	}
}
void	PropertyNamingForm::BuildForShow(void)
{
	ShowGrid();
}
void	PropertyNamingForm::ShowInEdit(void)
{
	ShowGrid();
}
void	iSetDataToTable(QTableWidget *W ,int col ,int row ,const QVariant &value)
{
	W->model()->setData(W->model()->index(row,col),value);
}
void	PropertyNamingForm::ShowGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendNamingList	**BmpReceiver=new GUICmdSendNamingList*[GetParamGlobal()->PageNumb];
	GUICmdReqNamingList		**BmpRequester=new GUICmdReqNamingList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page] =new GUICmdSendNamingList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]=new GUICmdReqNamingList (GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	}

	NamingInfo.RemoveAll();
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page])==true
		&& BmpReceiver[page]->IsReceived()==true){
			NamingInfo+=BmpReceiver[page]->NamingInfo;
		}
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	int	N=0;
	int	Numb=NamingInfo.GetNumber();
	ui.tableWidgetNamingList->setRowCount(Numb);
	NamingListForPacket **LTable=new NamingListForPacket*[Numb];
	int	n=0;
	for(NamingListForPacket *L=NamingInfo.GetFirst();L!=NULL;L=L->GetNext(),N++){
		LTable[N]=L;
	}
	
	ui.tableWidgetNamingList->setUpdatesEnabled(false);
	for(int i=0;i<N;i++){
		NamingListForPacket *L=LTable[i];
		//for(MaskingListForPacket *L=MaskInfo.GetFirst();L!=NULL;L=L->GetNext()){

		iSetDataToTable(ui.tableWidgetNamingList ,0 ,i ,QString::number(L->Page));
		iSetDataToTable(ui.tableWidgetNamingList ,1 ,i 
						,QString(/**/"(")
						+QString::number(L->x1)+QString(/**/",")+QString::number(L->y1)
						+QString(/**/")-(")
						+QString::number(L->x2)+QString(/**/",")+QString::number(L->y2)
						+QString(/**/")"));
		iSetDataToTable(ui.tableWidgetNamingList ,2 ,i ,L->AreaName);

	}
	ui.tableWidgetNamingList->setUpdatesEnabled(true);
	delete	[]LTable;

	ReEntrant=false;
}

void	PropertyNamingForm::ShowGroupGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;
	NamingGroupData.RemoveAll();
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdSendNamingGroupList		BmpReceiver	(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdReqNamingGroupList		BmpRequester(GetLayersBase(),sRoot,sName,globalPage);
		if(BmpRequester.Send(BmpRequester.GetGlobalPage(),0,BmpReceiver)==true){
			for(NamingGroupList *a=BmpReceiver.GroupData.GetFirst();a!=NULL;a=a->GetNext()){
				NamingGroupList *c;
				for(c=NamingGroupData.GetFirst();c!=NULL;c=c->GetNext()){
					if(a->GroupID==c->GroupID){
						break;
					}
				}
				if(c==NULL){
					NamingGroupList	*k=new NamingGroupList();
					k->GroupID	=a->GroupID;
					k->GroupName=a->GroupName;
					NamingGroupData.AppendList(k);
				}
			}
		}
	}

	int	Numb=NamingGroupData.GetNumber();
	ui.listWidgetGroup->clear();
	for(int i=0;i<Numb;i++){
		NamingGroupList	*L=NamingGroupData[i];
		ui.listWidgetGroup->addItem(L->GroupName);
	}

	ReEntrant=false;
}

void PropertyNamingForm::on_tableWidget_cellDoubleClicked(int,int)
{
	QModelIndex	RIndex=ui.tableWidgetNamingList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	NamingListForPacket *L=NamingInfo.GetItem(R);
	if(L==NULL)
		return;
	InputNamingNameForm	*DForm=new InputNamingNameForm(GetLayersBase());
	GeneralDialog	D(GetLayersBase(),DForm,this);
	DForm->SetNamingItem(L);
	D.exec();
	if(DForm->RetOK==false)
		return;

	GUICmdChangeNamingAttr	Cmd(GetLayersBase(),sRoot,sName,L->Page);
	Cmd.ItemID		=L->ItemID;
	Cmd.GlobalPage	=L->Page;
	Cmd.AreaName	=L->AreaName;
	Cmd.Row			=L->Row;
	Cmd.Column		=L->Column;
	Cmd.SendOnly(L->Page,0);
	ShowGrid();
}

void PropertyNamingForm::on_pushButtonExecute_clicked()
{
	AddNamingGenerateName	RCmd(GetLayersBase());
	RCmd.FormatStr=ui.lineEditFormat->text();

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqSelectedNamingItems	ReqLister(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdSendSelectedNamingItems	AckLister(GetLayersBase(),sRoot,sName,globalPage);
		if(ReqLister.Send(globalPage,0,AckLister)==true && AckLister.IsReceived()==true){
			for(NamingPointer *c= AckLister.Stocker.GetFirst();c!=NULL;c=c->GetNext()){
				c->GlobalPage=globalPage;
			}
			RCmd.Stocker += AckLister.Stocker;
		}
	}

	AlgorithmBase	*NamingBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Naming");
	if(NamingBase==NULL)
		return;
	NamingBase->TransmitDirectly(&RCmd);

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdSetSelectedNamingItems	CmdSet(GetLayersBase(),sRoot,sName,globalPage);
		for(NamingPointer *a=RCmd.Stocker.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GlobalPage==globalPage){
				NamingPointer *c=new NamingPointer();
				*c=*a;
				CmdSet.Stocker.AppendList(c);
			}
		}
		CmdSet.SendOnly(globalPage,0);
	}
	ShowGrid();
}

void PropertyNamingForm::on_tableWidgetNamingList_clicked(const QModelIndex &MIndex)
{
	NamingListForPacket *L=NamingInfo.GetItem(MIndex.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"NamingImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->Page,0,L->ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

void PropertyNamingForm::on_pushButton_CreateItemFromItsCoordinate_clicked()
{
	int Left    = ui.spinBox_ItemsLeft->value();
	int Top     = ui.spinBox_ItemsTop->value();
	int Width   = ui.spinBox_ItemsWidth->value();
	int Height  = ui.spinBox_ItemsHeight->value();
	double Resolution = ui.doubleSpinBox_Resolution->value();
	FlexArea Area;
	Area.SetRectangle( Left, Top,
	                   Left+(Width/Resolution), Top+(Height/Resolution) );

	QString AreaName = ui.lineEdit_ItemsName->text();
	
	IntList PageList;
	GetLayersBase()->GetLocalPageFromArea(Area, PageList);
	for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
		DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
		pdata->ClipMoveAreaFromGlobal(Area);
		if(Area.GetPatternByte()>0){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(pdata->GetPage());
			GUICmdAddNamingArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.Area=Area;
			Cmd.AreaName=AreaName;
			Cmd.SendOnly(GlobalPage,0);
		}
	}

	ShowGrid();
}

void	PropertyNamingForm::CreateArea(const QString &AreaName,FlexArea &Area 
										,int Column ,int Row
										,int Expand)
{
	IntList PageList;
	GetLayersBase()->GetLocalPageFromArea(Area,PageList);
	for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
		DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
		FlexArea	A=Area;
		pdata->ClipMoveAreaFromGlobal(A);
		if(A.GetPatternByte()>0){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(pdata->GetPage());
			GUICmdAddNamingArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.Area=A;
			if(Expand>0)
				Cmd.Area.FatAreaN(Expand);
			else if(Expand<0)
				Cmd.Area.ThinAreaN(-Expand);
			Cmd.AreaName=AreaName;
			Cmd.Row=Row;
			Cmd.Column=Column;
			Cmd.SendOnly(GlobalPage,0);
		}
	}
}
void PropertyNamingForm::on_toolButtonAutoCount_clicked()
{
	if(ui.toolButtonAutoCount->isChecked()==true){
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"NamingImagePanel" ,/**/"");
		if(GProp!=NULL){
			ChangeToCountModePacket	Cmd(GetLayersBase());
			GProp->TransmitDirectly(&Cmd);
		}
	}
}

void PropertyNamingForm::on_toolButtonMakeGroup_clicked()
{
	InputGroupDialog	D(GetLayersBase());
	D.exec();

	int	MaxGroupID=0;
	for(NamingGroupList *a=NamingGroupData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GroupID>MaxGroupID){
			MaxGroupID=a->GroupID;
		}
	}
	MaxGroupID++;

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqSetGroup	ReqGrouper(GetLayersBase(),sRoot,sName,globalPage);
		ReqGrouper.GroupString	=D.GroupString;
		ReqGrouper.GroupID		=MaxGroupID;
		ReqGrouper.Send(NULL,globalPage,0);
	}
	ShowGroupGrid();
}

void PropertyNamingForm::on_listWidgetGroup_clicked(const QModelIndex &index)
{

}

void PropertyNamingForm::on_pushButtonClearSelectedGroup_clicked()
{
	for(int r=0;r<ui.listWidgetGroup->count();r++){
		QListWidgetItem *R= ui.listWidgetGroup->item ( r );
		if(R->isSelected()==true){
			for(int page=0;page<GetParamGlobal()->PageNumb;page++){
				int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
				GUICmdReqClearGroup	ReqClrGrouper(GetLayersBase(),sRoot,sName,globalPage);
				ReqClrGrouper.GroupID	=NamingGroupData[r]->GroupID;
				ReqClrGrouper.Send(NULL,globalPage,0);
			}
		}
	}
	ShowGroupGrid();
}

void PropertyNamingForm::on_pushButtonGenerateIndex_clicked()
{
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqGenerateIndex	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Send(NULL,globalPage,0);
	}
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"NamingImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->Repaint();
	}
}