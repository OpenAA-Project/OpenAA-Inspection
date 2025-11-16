#include "CreateManualEulerRingFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyEulerRing\PropertyEulerRingForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyEulerRingForm.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyEulerRingPacket.h"
#include "EulerRingPickupForm.h"
#include "EditEulerRingLibrary.h"
#include "XDatabaseLoader.h"
#include "CreateManualEulerRingForm.h"
#include "XDisplayImagePacket.h"
#include "XGUIPacketGeneral.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyEulerRingForm::PropertyEulerRingForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	//LangSolver.SetUI(this);

	LibFolderID =-1;
	EulerRingBase	*BBase=GetEulerRingBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);
	ui.tableWidgetGeneratedLibList->setColumnWidth (0, 30);
	ui.tableWidgetGeneratedLibList->setColumnWidth (1, 80);	

	ui.tableWidgetBlockInfo->setColumnCount(3);
	ui.tableWidgetBlockInfo->setColumnWidth (0, 30);
	ui.tableWidgetBlockInfo->setColumnWidth (1, 150);
	ui.tableWidgetBlockInfo->setColumnWidth (2, 80);
	QStringList	HeaderLabel;
	HeaderLabel.append(LangSolver.GetString(PropertyEulerRingForm_LS,LID_10)/*"ID"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyEulerRingForm_LS,LID_11)/*"ライブラリ名"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyEulerRingForm_LS,LID_12)/*"ブロック総数"*/);
	ui.tableWidgetBlockInfo->setHorizontalHeaderLabels(HeaderLabel);

	TabBarBlockOnMouse.setParent(ui.frameBlockInfoOnMouse);
	TabBarBlockOnMouse.setGeometry(ui.frame->geometry().left(),ui.frame->geometry().top()-30,ui.frame->geometry().width(),30);
	connect(&TabBarBlockOnMouse,SIGNAL(currentChanged(int)),this,SLOT(TabBarBlockOnMouseChanged(int)));

	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		BInfo[i].EulerRingInfoOnMouse=NULL;
	}

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempEulerRingLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ColorGeneratorH	.setParent(ui.frameGenerateH);
	ColorGeneratorC	.setParent(ui.frameGenerateC);
	ColorInspection	.setParent(ui.frameInspectionPanel);
	ColorGeneratorH	.Fit(ui.frameGenerateH);
	ColorGeneratorC	.Fit(ui.frameGenerateC);
	ColorInspection	.Fit(ui.frameInspectionPanel);

	if(ui.toolButtonLibrary->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(0);
	}
	if(ui.toolButtonCreateBlock->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(1);
		ShowBlockInfoList();
	}
	
	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyEulerRingForm::~PropertyEulerRingForm()
{
	if(TempLib!=NULL)
		delete	TempLib;
}

EulerRingBase	*PropertyEulerRingForm::GetEulerRingBase(void)
{
	return (EulerRingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRing");
}

void	PropertyEulerRingForm::ShowTab(void)
{
	int	r=TabBarBlockOnMouse.currentIndex();
	while(TabBarBlockOnMouse.count()!=0){
		TabBarBlockOnMouse.removeTab(0);
	}
	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		if(BInfo[i].EulerRingInfoOnMouse!=NULL){
			TabBarBlockOnMouse.addTab (QString(/**/"Page-") + QString::number(BInfo[i].Page));
		}
	}
	if(0<=r && TabBarBlockOnMouse.count()>r){
		TabBarBlockOnMouse.setCurrentIndex(r);
	}
}

void	PropertyEulerRingForm::TabBarBlockOnMouseChanged(int index)
{
	if(index>=0 && BInfo[index].EulerRingInfoOnMouse!=NULL){
		ui.EditLibIDInBlock		->setText(QString::number(BInfo[index].EulerRingInfoOnMouse->GetLibID()));
		EulerRingBase	*BBase=GetEulerRingBase();
		CmdGetLibName	Cmd(GetLayersBase());
		Cmd.LibID	=BInfo[index].EulerRingInfoOnMouse->GetLibID();
		BBase->TransmitDirectly(&Cmd);
		ui.EditLibNameInBlock	->setText(Cmd.LibName);

		ui.EditExpandedDot		->setValue(BInfo[index].EulerRingInfoOnMouse->GetThresholdR()->ExpandedDot	);
		ui.EditMergin			->setValue(BInfo[index].EulerRingInfoOnMouse->GetThresholdR()->Mergin		);

		ui.EditAdjustBlack		->setValue(BInfo[index].EulerRingInfoOnMouse->GetThresholdR()->AdjustBlack	);
		ui.EditAdjustWhite		->setValue(BInfo[index].EulerRingInfoOnMouse->GetThresholdR()->AdjustWhite	);
	}
	else{
		ui.EditLibIDInBlock		->clear();
		ui.EditLibNameInBlock	->clear();

		ui.EditExpandedDot		->clear();
		ui.EditMergin			->clear();

		ui.EditAdjustBlack		->clear();
		ui.EditAdjustWhite		->clear();
	}
}

void	PropertyEulerRingForm::ShowLibList(void)
{
	ui.tableWidgetLibList->setRowCount(0);
	EulerRingBase	*BBase=GetEulerRingBase();
	if(BBase!=NULL){
		CmdGetEulerRingLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui.tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui.tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui.tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}
void	PropertyEulerRingForm::ShowInEdit(void)
{
	ShowBlockInfoList();
}
void	PropertyEulerRingForm::StartPage(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui.labelLibFolderName->setText(FolderName);
	}
}
void	PropertyEulerRingForm::BuildForShow(void)
{
	ShowBlockInfoList();
}

void	PropertyEulerRingForm::TransmitDirectly(GUIDirectMessage *packet)
{
	EulerRingBase	*BBase=GetEulerRingBase();
	CmdEulerRingDrawModePacket	*BDrawModePacket=dynamic_cast<CmdEulerRingDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		if(ui.toolButtonLibrary->isChecked()==true)
			BDrawModePacket->Mode=EulerRingDrawAttr::_LibTest;
		else if(ui.toolButtonCreateBlock->isChecked()==true)
			BDrawModePacket->Mode=EulerRingDrawAttr::_CreatedBlock;
		return;
	}
	CmdEulerRingDrawEnd	*BlockDEnd=dynamic_cast<CmdEulerRingDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		if(ui.toolButtonLibrary->isChecked()==true){
			int		LPage=GetLayersBase()->GetLocalPageFromAreaFromDrawingTop(BlockDEnd->Area);
			if(LPage>=0){
				ImagePointerContainer Images;
				GetLayersBase()->GetPageData(LPage)->GetMasterImages(Images);
				RGBStock	PickupSamples;
				FlexArea	area;
				area=BlockDEnd->Area;
				GetLayersBase()->GetPageData(LPage)->ClipMoveAreaFromGlobal(area);
				area.CreateRGBStock(Images, PickupSamples);
				EulerRingPickupForm	D(GetLayersBase()
									,&PickupSamples
									,this);
				if(D.exec()==(int)true){
					EulerRingLibrary	*ALib=dynamic_cast<EulerRingLibrary *>(TempLib->GetLibrary());
					if(ui.toolButtonHole->isChecked()==true){
						ColorGeneratorH.Cube=D.ColorPanel.Cube;
						ColorGeneratorH.InitializedDoneCube();
						ColorGeneratorH.Repaint();
						ALib->HoleColor	=D.ColorPanel.Cube;
					}
					else{
						ColorGeneratorC.Cube=D.ColorPanel.Cube;
						ColorGeneratorC.InitializedDoneCube();
						ColorGeneratorC.Repaint();
						ALib->CupperColor	=D.ColorPanel.Cube;
					}
				}
			}
		}
		else if(ui.toolButtonCreateBlock->isChecked()==true){
			CreateManualEulerRingForm	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=BlockDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						GUICmdSendAddManualEulerRing	Cmd(GetLayersBase(),sRoot,sName,page);
						Cmd.Area=A;
						CmdCreateByteArrayFromEulerRingItemPacket	BCmd(GetLayersBase());
						BCmd.Point=D.BItem;
						BBase->TransmitDirectly(&BCmd);
						Cmd.BItem=BCmd.Buff;
						Cmd.Send(NULL,page,0);
					}
				}
				ShowBlockInfoList();
			}
		}
	}
	CmdEulerRingShowAttrPacket	*ShowAttr=dynamic_cast<CmdEulerRingShowAttrPacket *>(packet);
	if(ShowAttr!=NULL){

	}
	CmdExecuteMouseLDown	*CmdExecuteMouseLDownVar=dynamic_cast<CmdExecuteMouseLDown *>(packet);
	if(CmdExecuteMouseLDownVar!=NULL){
		for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
			//if(BInfo[i].BlockInfoOnMouse!=NULL)
			//	delete	BInfo[i].BlockInfoOnMouse;
			BInfo[i].EulerRingInfoOnMouse=NULL;
		}
		int	N=0;
		for(IntClass *p=CmdExecuteMouseLDownVar->PageList.GetFirst();p!=NULL;p=p->GetNext()){
			int page=p->GetValue();
			ListLayerAndIDPack	Items;
			if(N>=sizeof(BInfo)/sizeof(BInfo[0]))
				break;
			for(ListPageLayerID *a=CmdExecuteMouseLDownVar->CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Page==page){
					Items.AppendList(new ListLayerAndID(0,a->ID));
				}
			}
			if(Items.GetNumber()!=NULL){
				GUICmdReqEulerRingFromList	ReqCmd(GetLayersBase(),sRoot,sName,page);
				GUICmdAckEulerRingFromList	AckCmd(GetLayersBase(),sRoot,sName,page);
				ReqCmd.CurrentItem=Items;
				ReqCmd.Send(page,0,AckCmd);
				for(int i=0;i<sizeof(AckCmd.EulerRingInfoOnMouse)/sizeof(AckCmd.EulerRingInfoOnMouse[0]);i++){
					if(AckCmd.EulerRingInfoOnMouse[i]!=NULL){
						BInfo[N].EulerRingInfoOnMouse=AckCmd.EulerRingInfoOnMouse[i];
						AckCmd.EulerRingInfoOnMouse[i]=NULL;
						BInfo[N].Page=page;
						BInfo[N].Layer=0;
						N++;
						if(N>=sizeof(BInfo)/sizeof(BInfo[0]))
							break;
					}
				}
			}
		}
		ShowTab();
		return;
	}
	CmdExecuteMouseRDownWithShift	*ShiftRight=dynamic_cast<CmdExecuteMouseRDownWithShift *>(packet);
	if(ShiftRight!=NULL){
		QByteArray	BlockItemData;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
			GUICmdReqSelectedEulerRingItemAttr		ReqCmd(GetLayersBase(),sRoot,sName,page);
			GUICmdSendSelectedEulerRingItemAttr	SendCmd(GetLayersBase(),sRoot,sName,page);
			if(ReqCmd.Send(ReqCmd.GetGlobalPage(),0,SendCmd)==true
			&& SendCmd.IsReceived()==true){
				if(SendCmd.ExistSelected==true){
					BlockItemData=SendCmd.BItem;
					break;
				}
			}
		}
		if(BlockItemData.size()!=0){
			/*
			TrueColorCreateManualBlockForm	D(GetLayersBase(),NULL);
			CmdLoadEulerRingItemPacketFromByteArray	CmdPacket;
			CmdPacket.Buff=BlockItemData;
			CmdPacket.BItemPoint=D.BItem;
			BBase->TransmitDirectly(&CmdPacket);
			D.Reflect();
			if(D.exec()==(int)true){
				IntList PageList;
				for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					GUICmdSendModifySelectedColorBlock	Cmd(GetLayersBase(),sRoot,sName,page);
					CmdCreateByteArrayFromEulerRingItemPacket	BCmd;
					BCmd.Point=D.BItem;
					BBase->TransmitDirectly(&BCmd);
					Cmd.BItem=BCmd.Buff;
					Cmd.Send(NULL,page,0);					
				}
			}
			*/
		}
	}
}


void	PropertyEulerRingForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	EulerRingLibrary	*ALib=dynamic_cast<EulerRingLibrary *>(data.GetLibrary());
	ColorGeneratorH.Cube=ALib->HoleColor;
	ColorGeneratorH.InitializedDoneCube();
	ColorGeneratorH.Repaint();
	ColorGeneratorC.Cube=ALib->CupperColor;
	ColorGeneratorC.InitializedDoneCube();
	ColorGeneratorC.Repaint();

	ui.EditNoiseSize		->setValue(ALib->NoiseSize);

	ColorInspection.Cube		=ALib->InspectionColor;
	ColorInspection.InitializedDoneCube();
	ColorInspection.Repaint();
}

void	PropertyEulerRingForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());
	EulerRingLibrary	*ALib=dynamic_cast<EulerRingLibrary *>(data.GetLibrary());

	ALib->NoiseSize			=ui.EditNoiseSize		->value();
	ALib->InspectionColor	=ColorInspection.Cube;
}


void PropertyEulerRingForm::on_toolButtonLibrary_clicked()
{
	if(ui.toolButtonLibrary->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(0);
	}
	BroadcastShowInEdit();
}

void PropertyEulerRingForm::on_toolButtonCreateBlock_clicked()
{
	if(ui.toolButtonCreateBlock->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(1);
		ShowBlockInfoList();
	}
	BroadcastShowInEdit();
}

void PropertyEulerRingForm::on_pushButtonEditLibFolder_clicked()
{
	EulerRingBase	*BBase=GetEulerRingBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyEulerRingForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui.labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void PropertyEulerRingForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadEulerRingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		EulerRingBase	*BBase=GetEulerRingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(PropertyEulerRingForm_LS,LID_13)/*"Library error"*/, LangSolver.GetString(PropertyEulerRingForm_LS,LID_14)/*"Not loaded this library record"*/);
			}
		}
	}
}

struct	AlgorithmLibraryListClass
{
	AlgorithmLibraryList	*a;
	int						Priority;
};

int	DDimFunc(const void *a ,const void *b)
{
	if(((struct AlgorithmLibraryListClass *)a)->Priority>((struct AlgorithmLibraryListClass *)b)->Priority)
		return 1;
	if(((struct AlgorithmLibraryListClass *)a)->Priority<((struct AlgorithmLibraryListClass *)b)->Priority)
		return -1;
	return 0;
}

void	PropertyEulerRingForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	EulerRingBase	*BBase=GetEulerRingBase();
	if(BBase!=NULL){
		CmdCreateTempEulerRingLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());
			CmdLoadEulerRingLibraryPacket	Packet(GetLayersBase());
			Packet.Point=SLib;
			BBase->TransmitDirectly(&Packet);
			DDim[row].Priority=1;	//SLib->Priority;
		}
		for(;;){
			AlgorithmLibraryList *a=SelectedLibList.GetFirst();
			if(a==NULL)
				break;
			SelectedLibList.RemoveList(a);
		}
		QSort(DDim,row,sizeof(DDim[0]),DDimFunc);
		for(int i=0;i<row;i++){
			SelectedLibList.AppendList(DDim[i].a);
		}
	}

	int	row=0;
	ui.tableWidgetGeneratedLibList->setRowCount(SelectedLibList.GetNumber());
	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		QTableWidgetItem *W;
		W=ui.tableWidgetGeneratedLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetGeneratedLibList->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->GetLibID()));
		W=ui.tableWidgetGeneratedLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetGeneratedLibList->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
	}
}

void PropertyEulerRingForm::on_tableWidgetLibList_doubleClicked(QModelIndex)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyEulerRingForm::on_pushButtonSetFrom_clicked()
{
	int	r=ui.tableWidgetLibList->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==a->GetLibID())
			return;
	}
	SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	ShowSelectedLibList();
}

void PropertyEulerRingForm::on_pushButtonGetBack_clicked()
{
	int	r=ui.tableWidgetGeneratedLibList->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		SelectedLibList.RemoveList(a);
		delete	a;
		ShowSelectedLibList();
	}
}

void PropertyEulerRingForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadEulerRingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		EulerRingBase	*BBase=GetEulerRingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(PropertyEulerRingForm_LS,LID_15)/*"Library error"*/, LangSolver.GetString(PropertyEulerRingForm_LS,LID_16)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyEulerRingForm::on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex)
{
	on_pushButtonGetBack_clicked();
}

void PropertyEulerRingForm::on_pushButtonEditLibrary_clicked()
{
	EditEulerRingLibrary	D(GetLayersBase(),this);
	D.exec();
	//on_ButtonLibSave_clicked();
}

void PropertyEulerRingForm::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyEulerRingForm_LS,LID_17)/*"Pickup Test"*/);

	GetLibraryFromWindow(*TempLib);

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.LibPoint	=TempLib;
		Cmd.Send(NULL,page,0);
	}

	GetLayersBase()->CloseProcessingForm();
}

void PropertyEulerRingForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.Send(NULL,page,0);
	}
	BroadcastShowInEdit();
}

void PropertyEulerRingForm::on_ButtonGenerateLibs_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyEulerRingForm_LS,LID_18)/*"Generating items"*/,GetLayersBase()->GetPageNumb()*10);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdGenerateEulerRings	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyEulerRingForm::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL || TempLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(PropertyEulerRingForm_LS,LID_19)/*"Warning"*/, LangSolver.GetString(PropertyEulerRingForm_LS,LID_20)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateEulerRingLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	EulerRingBase	*BBase=GetEulerRingBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibID()==TempLib->GetLibID()){
			a->SetLibName(TempLib->GetLibName());
		}
	}
	ShowLibList();
	ShowSelectedLibList();
}

void PropertyEulerRingForm::on_pushButtonGColor_clicked()
{
	EulerRingPickupForm	D(GetLayersBase()
						,NULL
						,this);
	D.ColorPanel.Cube	=ColorGeneratorH.Cube;
	D.ColorPanel.InitializedDoneCube();
	if(D.exec()==(int)true){
		ColorGeneratorH.Cube=D.ColorPanel.Cube;
		ColorGeneratorH.InitializedDoneCube();
		ColorGeneratorH.Repaint();
		if(TempLib!=NULL){
			EulerRingLibrary	*ALib=dynamic_cast<EulerRingLibrary *>(TempLib->GetLibrary());
			ALib->HoleColor=D.ColorPanel.Cube;
		}
	}
}
void PropertyEulerRingForm::ShowBlockInfoList(void)
{
	EulerRingInfos.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqEulerRingInfoList		CmdReq (GetLayersBase(),sRoot,sName,page);
		GUICmdSendEulerRingInfoList		CmdSend(GetLayersBase(),sRoot,sName,page);
		CmdReq.Send(page,0,CmdSend);
		for(EulerRingInfoList *a=CmdSend.EulerRingInfos.GetFirst();a!=NULL;a=a->GetNext()){
			EulerRingInfoList *b;
			for(b=EulerRingInfos.GetFirst();b!=NULL;b=b->GetNext()){
				if(a->LibID==b->LibID){
					IntClass	*d=b->EulerRingCount.GetItem(0);
					IntClass	*s=a->EulerRingCount.GetItem(0);
					d->SetValue(d->GetValue()+s->GetValue());					
					break;
				}
			}
			if(b==NULL){
				b=new EulerRingInfoList();
				b->LibID=a->LibID;
				IntClass	*s=a->EulerRingCount.GetItem(0);
				b->EulerRingCount.Add(s->GetValue());
				EulerRingInfos.AppendList(b);
			}
		}
	}
	int	N=EulerRingInfos.GetNumber();
	ui.tableWidgetBlockInfo->setRowCount(N);
	AlgorithmLibraryListContainer LibIDList;
	for(EulerRingInfoList *a=EulerRingInfos.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList	*k=new AlgorithmLibraryList();
		k->SetLibID(a->GetLibID());
		LibIDList.AppendList(k);
	}
	EulerRingBase	*BBase=GetEulerRingBase();
	GetLayersBase()->GetDatabaseLoader()->G_GetLibraryNames(*GetLayersBase()->GetDataBase(),BBase->GetLibraryContainer(),LibIDList);
	int	row=0;
	for(EulerRingInfoList *a=EulerRingInfos.GetFirst();a!=NULL;a=a->GetNext(),row++){
		QString	LibName;
		for(AlgorithmLibraryList *m=LibIDList.GetFirst();m!=NULL;m=m->GetNext()){
			if(m->GetLibID()==a->GetLibID()){
				LibName=m->GetLibName();
				break;
			}
		}
		QTableWidgetItem *W;
		W=ui.tableWidgetBlockInfo->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetBlockInfo->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->LibID));

		W=ui.tableWidgetBlockInfo->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetBlockInfo->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(LibName);

		W=ui.tableWidgetBlockInfo->item ( row, 2);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetBlockInfo->setItem ( row, 2,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		int	TotalCount=0;
		for(IntClass *h=a->EulerRingCount.GetFirst();h!=NULL;h=h->GetNext()){
			TotalCount+=h->GetValue();
		}
		W->setText(QString::number(TotalCount));
	}
}


void PropertyEulerRingForm::on_tableWidgetBlockInfo_clicked(const QModelIndex &)
{
	EulerRingBase	*BBase=GetEulerRingBase();

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdReleaseSelectImagePanel	Cmd(GetLayersBase(),sRoot,sName ,page);
		Cmd.AlgoRoot=/**/"Basic";
		Cmd.AlgoName=/**/"EulerRing";
		Cmd.Send(NULL,page,0);
	}

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdSelectByLibs	Cmd(BBase,sRoot,sName,page);
		for(int row=0;row<ui.tableWidgetBlockInfo->rowCount();row++){
			EulerRingInfoList *a=EulerRingInfos.GetItem(row);
			int	c=2;
			QTableWidgetItem *item=ui.tableWidgetBlockInfo->item(row,c);
			if(item==NULL)
				continue;
			if(item->isSelected()==true){
				SelectLibList	*v=new SelectLibList();
				v->LibType	=BBase->GetLibType();
				v->LibID	=a->LibID;
				v->Layer=0;
				Cmd.SelectedList.AppendList(v);
			}
		}
		Cmd.Send(NULL,page,1);
	}
	BroadcastShowInEdit();
}

void PropertyEulerRingForm::on_pushButtonCColor_clicked()
{
	EulerRingPickupForm	D(GetLayersBase()
						,NULL
						,this);
	D.ColorPanel.Cube	=ColorGeneratorC.Cube;
	D.ColorPanel.InitializedDoneCube();
	if(D.exec()==(int)true){
		ColorGeneratorC.Cube=D.ColorPanel.Cube;
		ColorGeneratorC.InitializedDoneCube();
		ColorGeneratorC.Repaint();
		if(TempLib!=NULL){
			EulerRingLibrary	*ALib=dynamic_cast<EulerRingLibrary *>(TempLib->GetLibrary());
			ALib->CupperColor=D.ColorPanel.Cube;
		}
	}
}

void PropertyEulerRingForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyEulerRingForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}