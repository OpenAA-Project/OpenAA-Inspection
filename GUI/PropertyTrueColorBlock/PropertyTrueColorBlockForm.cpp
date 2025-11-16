/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTrueColorBlock\PropertyTrueColorBlockForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "TrueColorFormResource.h"
#include "PropertyTrueColorBlockForm.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyTrueColorBlockPacket.h"
#include "TrueColorPickupForm.h"
#include "EditTrueColorLibrary.h"
#include "XDatabaseLoader.h"
#include "TrueColorCreateManualBlockForm.h"
#include "XDisplayImagePacket.h"
#include "XGUIPacketGeneral.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyTrueColorBlockForm::PropertyTrueColorBlockForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
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
	HeaderLabel.append(LangSolver.GetString(PropertyTrueColorBlockForm_LS,LID_8)/*"ID"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyTrueColorBlockForm_LS,LID_9)/*"???C?u??????"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyTrueColorBlockForm_LS,LID_10)/*"?u???b?N????"*/);
	ui.tableWidgetBlockInfo->setHorizontalHeaderLabels(HeaderLabel);

	TabBarBlockOnMouse.setParent(ui.frameBlockInfoOnMouse);
	TabBarBlockOnMouse.setGeometry(ui.frame->geometry().left(),ui.frame->geometry().top()-30,ui.frame->geometry().width(),30);
	connect(&TabBarBlockOnMouse,SIGNAL(currentChanged(int)),this,SLOT(TabBarBlockOnMouseChanged(int)));

	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		BInfo[i].TrueColorBlockInfoOnMouse=NULL;
	}

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempTrueColorBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ColorGenerator	.setParent(ui.frameGenerate);
	ColorNarrow		.setParent(ui.frameNarrowPanel);
	ColorBroad		.setParent(ui.frameBroadPanel);

	ColorGenerator	.Fit(ui.frameGenerate);
	ColorNarrow		.Fit(ui.frameNarrowPanel);
	ColorBroad		.Fit(ui.frameBroadPanel);
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

PropertyTrueColorBlockForm::~PropertyTrueColorBlockForm()
{
	if(TempLib!=NULL)
		delete	TempLib;
}
TrueColorBlockBase	*PropertyTrueColorBlockForm::GetTrueColorBlockBase(void)
{
	return (TrueColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
}

void	PropertyTrueColorBlockForm::ShowTab(void)
{
	int	r=TabBarBlockOnMouse.currentIndex();
	while(TabBarBlockOnMouse.count()!=0){
		TabBarBlockOnMouse.removeTab(0);
	}
	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		if(BInfo[i].TrueColorBlockInfoOnMouse!=NULL){
			TabBarBlockOnMouse.addTab (QString(/**/"Page-") + QString::number(BInfo[i].Page));
		}
	}
	if(0<=r && TabBarBlockOnMouse.count()>r){
		TabBarBlockOnMouse.setCurrentIndex(r);
	}
}

void	PropertyTrueColorBlockForm::TabBarBlockOnMouseChanged(int index)
{
	if(index>=0 && BInfo[index].TrueColorBlockInfoOnMouse!=NULL){
		ui.EditLibIDInBlock		->setText(QString::number(BInfo[index].TrueColorBlockInfoOnMouse->GetLibID()));
		TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
		CmdGetLibName	Cmd(GetLayersBase());
		Cmd.LibID	=BInfo[index].TrueColorBlockInfoOnMouse->GetLibID();
		BBase->TransmitDirectly(&Cmd);
		ui.EditLibNameInBlock	->setText(Cmd.LibName);

		ui.EditNOKDot			->setValue(BInfo[index].TrueColorBlockInfoOnMouse->GetThresholdR()->NOKDot		);
		ui.EditNMergin			->setValue(BInfo[index].TrueColorBlockInfoOnMouse->GetThresholdR()->NMergin		);
		ui.EditBOKDot			->setValue(BInfo[index].TrueColorBlockInfoOnMouse->GetThresholdR()->BOKDot		);
		ui.EditBMergin			->setValue(BInfo[index].TrueColorBlockInfoOnMouse->GetThresholdR()->BMergin		);

		ui.checkBModeAdjustable	->setChecked(BInfo[index].TrueColorBlockInfoOnMouse->GetThresholdR()->PointMove.ModeAdjustable	);
		ui.EditAdjustBlack		->setValue(BInfo[index].TrueColorBlockInfoOnMouse->GetThresholdR()->AdjustBlack	);
		ui.EditAdjustWhite		->setValue(BInfo[index].TrueColorBlockInfoOnMouse->GetThresholdR()->AdjustWhite	);

		ui.EditNMinNGCount		->setValue(BInfo[index].TrueColorBlockInfoOnMouse->GetThresholdR()->NMinNGCount);
		ui.EditBMinNGCount		->setValue(BInfo[index].TrueColorBlockInfoOnMouse->GetThresholdR()->BMinNGCount);

		ui.EditSelfSearch		->setValue(BInfo[index].TrueColorBlockInfoOnMouse->GetThresholdR()->SelfSearch		);
	}
	else{
		ui.EditLibIDInBlock		->clear();
		ui.EditLibNameInBlock	->clear();

		ui.EditNOKDot			->clear();
		ui.EditNMergin			->clear();
		ui.EditBOKDot			->clear();
		ui.EditBMergin			->clear();

		ui.EditNMinNGCount		->clear();
		ui.EditBMinNGCount		->clear();


		ui.checkBModeAdjustable	->setChecked(false);
		ui.EditAdjustBlack		->clear();
		ui.EditAdjustWhite		->clear();

		ui.EditSelfSearch		->clear();
	}
}

void	PropertyTrueColorBlockForm::ShowLibList(void)
{
	ui.tableWidgetLibList->setRowCount(0);
	TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
	if(BBase!=NULL){
		CmdGetTrueColorBlockLibraryListPacket	Packet(GetLayersBase());
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
void	PropertyTrueColorBlockForm::ShowInEdit(void)
{
	ShowBlockInfoList();
}
void	PropertyTrueColorBlockForm::StartPage(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui.labelLibFolderName->setText(FolderName);
	}
	ShowBlockInfoList();
}
void	PropertyTrueColorBlockForm::BuildForShow(void)
{
	StartPage();
}
void	PropertyTrueColorBlockForm::TransmitDirectly(GUIDirectMessage *packet)
{
	TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
	CmdTrueColorBlockDrawModePacket	*BDrawModePacket=dynamic_cast<CmdTrueColorBlockDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		if(ui.toolButtonLibrary->isChecked()==true)
			BDrawModePacket->Mode=CmdTrueColorBlockDrawModePacket::_LibTest;
		else if(ui.toolButtonCreateBlock->isChecked()==true)
			BDrawModePacket->Mode=CmdTrueColorBlockDrawModePacket::_CreatedBlock;
		if(ui.toolButtonArea->isChecked()==true)
			BDrawModePacket->DType=CmdTrueColorBlockDrawModePacket::_Area;
		else if(ui.toolButtonEdge->isChecked()==true)
			BDrawModePacket->DType=CmdTrueColorBlockDrawModePacket::_Edge;
		else if(ui.toolButtonInside->isChecked()==true)
			BDrawModePacket->DType=CmdTrueColorBlockDrawModePacket::_Inside;
		return;
	}
	CmdTrueColorBlockDrawEnd	*BlockDEnd=dynamic_cast<CmdTrueColorBlockDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		if(ui.toolButtonLibrary->isChecked()==true){
			//GlobalPickupArea+=BlockDEnd->Area;
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
			if(PageList.GetFirst()==NULL){
				return;
			}
			RGBStock	RGBColors;
			for(IntClass *PageClass=PageList.GetFirst();PageClass!=NULL;PageClass=PageClass->GetNext()){
				int	globalPage=PageClass->GetValue();
				FlexArea	A;
				//A=GlobalPickupArea;
				A=BlockDEnd->Area;
				GetLayersBase()->GetPageData(globalPage)->ClipMoveAreaFromGlobal(A);

				GUICmdReqRGBStockFromArea	RCmd(GetLayersBase(),sRoot,sName,globalPage);
				GUICmdSendRGBStockFromArea	SCmd(GetLayersBase(),sRoot,sName,globalPage);
				RCmd.Area=A;
				RCmd.Send(globalPage,0,SCmd);
				RGBColors+=SCmd.RGBColors;
			}
			TrueColorPickupForm	D(GetLayersBase()
								,&RGBColors
								,&ColorGenerator.Cube
								,this);
			if(D.exec()==(int)true){
				ColorGenerator.Cube=D.ColorPanel.Cube;
				ColorGenerator.InitializedDoneCube();
				ColorGenerator.Repaint();
				TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(TempLib->GetLibrary());
				ALib->PickupColor	=D.ColorPanel.Cube;
			}
		}
		else if(ui.toolButtonCreateBlock->isChecked()==true){
			TrueColorCreateManualBlockForm	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual TrueColorBlock");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=BlockDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						GUICmdSendAddManualTrueColorBlock	Cmd(GetLayersBase(),sRoot,sName,page);
						Cmd.Area=A;
						CmdCreateByteArrayFromTrueColorBlockItemPacket	BCmd(GetLayersBase());
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
	CmdTrueColorBlockShowAttrPacket	*ShowAttr=dynamic_cast<CmdTrueColorBlockShowAttrPacket *>(packet);
	if(ShowAttr!=NULL){

	}
	CmdExecuteMouseLDown	*CmdExecuteMouseLDownVar=dynamic_cast<CmdExecuteMouseLDown *>(packet);
	if(CmdExecuteMouseLDownVar!=NULL){
		for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
			//if(BInfo[i].BlockInfoOnMouse!=NULL)
			//	delete	BInfo[i].BlockInfoOnMouse;
			BInfo[i].TrueColorBlockInfoOnMouse=NULL;
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
				GUICmdReqTrueColorBlockFromList	ReqCmd(GetLayersBase(),sRoot,sName,page);
				GUICmdAckTrueColorBlockFromList	AckCmd(GetLayersBase(),sRoot,sName,page);
				ReqCmd.CurrentItem=Items;
				ReqCmd.Send(page,0,AckCmd);
				for(int i=0;i<sizeof(AckCmd.TrueColorBlockInfoOnMouse)/sizeof(AckCmd.TrueColorBlockInfoOnMouse[0]);i++){
					if(AckCmd.TrueColorBlockInfoOnMouse[i]!=NULL){
						BInfo[N].TrueColorBlockInfoOnMouse=AckCmd.TrueColorBlockInfoOnMouse[i];
						AckCmd.TrueColorBlockInfoOnMouse[i]=NULL;
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
			GUICmdReqSelectedTrueColorBlockItemAttr		ReqCmd(GetLayersBase(),sRoot,sName,page);
			GUICmdSendSelectedTrueColorBlockItemAttr	SendCmd(GetLayersBase(),sRoot,sName,page);
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
			CmdLoadTrueColorBlockItemPacketFromByteArray	CmdPacket;
			CmdPacket.Buff=BlockItemData;
			CmdPacket.BItemPoint=D.BItem;
			BBase->TransmitDirectly(&CmdPacket);
			D.Reflect();
			if(D.exec()==(int)true){
				IntList PageList;
				for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					GUICmdSendModifySelectedColorBlock	Cmd(GetLayersBase(),sRoot,sName,page);
					CmdCreateByteArrayFromTrueColorBlockItemPacket	BCmd;
					BCmd.Point=D.BItem;
					BBase->TransmitDirectly(&BCmd);
					Cmd.BItem=BCmd.Buff;
					Cmd.Send(NULL,page,0);					
				}
			}
			*/
		}
	}
	CmdReqSetButtonMode	*CmdReqSetButtonModeVar=dynamic_cast<CmdReqSetButtonMode *>(packet);
	if(CmdReqSetButtonModeVar!=NULL){
		if(CmdReqSetButtonModeVar->Mode==GUICmdReqSetButtonMode::_LibraryTest){
			ui.toolButtonLibrary->setChecked(true);
		}
		if(CmdReqSetButtonModeVar->Mode==GUICmdReqSetButtonMode::_CreateBlock){
			ui.toolButtonCreateBlock->setChecked(true);
		}
	}
}


void	PropertyTrueColorBlockForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(data.GetLibrary());
	ColorGenerator.Cube=ALib->PickupColor;
	ColorGenerator.InitializedDoneCube();
	ColorGenerator.Repaint();

	ui.EditMinBlockSize		->setValue(ALib->MinBlockSize);
	ui.EditMaxBlockSize		->setValue(ALib->MaxBlockSize);
	ui.EditMinBlockDots		->setValue(ALib->MinBlockDots);
	ui.EditMaxBlockDots		->setValue(ALib->MaxBlockDots);
	ui.EditLimitBlockSize	->setValue(ALib->LimitBlockSize);
	ui.EditSpaceToOutline	->setValue(ALib->SpaceToOutline);
	ui.EditNoiseSize		->setValue(ALib->NoiseSize);
	ui.EditNoiseSizePinHole	->setValue(ALib->NoiseSizePinHole);
	ui.EditPriority			->setValue(ALib->Priority);

	//ui.EditNMergin			->setValue(data.NMergin);
	//ui.EditNOKDot			->setValue(data.NOKDot);
	ColorNarrow.Cube		=ALib->NInsColor;
	ColorNarrow.InitializedDoneCube();
	ColorNarrow.Repaint();

	//ui.EditBMergin			->setValue(data.BMergin);
	//ui.EditBOKDot			->setValue(data.BOKDot);
	ColorBroad.Cube			=ALib->BInsColor;
	ColorBroad.InitializedDoneCube();
	ColorBroad.Repaint();
}

void	PropertyTrueColorBlockForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(data.GetLibrary());
	ALib->MinBlockSize		=ui.EditMinBlockSize	->value();
	ALib->MaxBlockSize		=ui.EditMaxBlockSize	->value();
	ALib->MinBlockDots		=ui.EditMinBlockDots	->value();
	ALib->MaxBlockDots		=ui.EditMaxBlockDots	->value();
	ALib->LimitBlockSize	=ui.EditLimitBlockSize	->value();
	ALib->SpaceToOutline	=ui.EditSpaceToOutline	->value();
	ALib->NoiseSize			=ui.EditNoiseSize		->value();
	ALib->NoiseSizePinHole	=ui.EditNoiseSizePinHole->value();
	ALib->Priority			=ui.EditPriority		->value();

	//data.NMergin		=ui.EditNMergin			->value();
	//data.NOKDot		=ui.EditNOKDot			->value();
	ALib->NInsColor		=ColorNarrow.Cube;
	//data.BMergin		=ui.EditBMergin			->value();
	//data.BOKDot		=ui.EditBOKDot			->value();
	ALib->BInsColor		=ColorBroad.Cube;
}


void PropertyTrueColorBlockForm::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL || TempLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(PropertyTrueColorBlockForm_LS,LID_11)/*"Warning"*/, LangSolver.GetString(PropertyTrueColorBlockForm_LS,LID_12)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateTrueColorBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
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


void PropertyTrueColorBlockForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadTrueColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(PropertyTrueColorBlockForm_LS,LID_13)/*"Library error"*/, LangSolver.GetString(PropertyTrueColorBlockForm_LS,LID_14)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyTrueColorBlockForm::on_tableWidgetLibList_doubleClicked(QModelIndex Index)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyTrueColorBlockForm::on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex Index)
{
	on_pushButtonGetBack_clicked();
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

QColor	GetTableColor(int n)
{
	switch(n&7){
		case 0 :	return QColor(255,255,0);
		case 1 :	return QColor(235,255,0);
		case 2 :	return QColor(235,235,0);
		case 3 :	return QColor(215,235,0);
		case 4 :	return QColor(215,215,0);
		case 5 :	return QColor(195,215,0);
		case 6 :	return QColor(195,195,0);
		case 7 :	return QColor(175,195,0);
	}
	return Qt::white;
}


bool	PropertyTrueColorBlockForm::SaveContent(QIODevice *f)
{
	WORD	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,LibType)==false)
		return false;
	if(LibList.Save(f)==false)
		return false;
	if(SelectedLibList.Save(f)==false)
		return false;
	if(::Save(f,LibFolderID)==false)
		return false;
	if(GlobalPickupArea.Save(f)==false)
		return false;
	return true;
}
bool	PropertyTrueColorBlockForm::LoadContent(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,LibType)==false)
		return false;
	if(LibList.Load(f)==false)
		return false;
	if(SelectedLibList.Load(f)==false)
		return false;
	if(::Load(f,LibFolderID)==false)
		return false;
	if(GlobalPickupArea.Load(f)==false)
		return false;
	ShowLibList();
	ShowSelectedLibList();

	QString FolderName;
	int ParentID;
	int NumberInFolder;
	if(GetLayersBase()->GetDatabaseLoader()->S_LibFolderFindData(GetLayersBase()->GetDatabase(),LibFolderID ,FolderName ,ParentID ,NumberInFolder)==true){
		SetLibFolder(LibFolderID ,FolderName);
	}
	return true;
}

void	PropertyTrueColorBlockForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
	if(BBase!=NULL){
		CmdCreateTempTrueColorBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;
		TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(SLib->GetLibrary());
		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadTrueColorBlockLibraryPacket	Packet(GetLayersBase());
			Packet.Point=SLib;
			BBase->TransmitDirectly(&Packet);
			DDim[row].Priority=ALib->Priority;
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
	int	CuPriority=-1;
	int	ColNum=-1;
	ui.tableWidgetGeneratedLibList->setRowCount(SelectedLibList.GetNumber());
	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		if(CuPriority!=DDim[row].Priority){
			CuPriority=DDim[row].Priority;
			ColNum++;
		}
		QColor	Col=GetTableColor(ColNum);

		QTableWidgetItem *W;
		W=ui.tableWidgetGeneratedLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetGeneratedLibList->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->GetLibID()));
		W->setBackground(Col);

		W=ui.tableWidgetGeneratedLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetGeneratedLibList->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
		W->setBackground(Col);
	}
}


void PropertyTrueColorBlockForm::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyTrueColorBlockForm_LS,LID_19)/*"Pickup Test"*/);

	GetLibraryFromWindow(*TempLib);

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.LibPoint	=TempLib;
		Cmd.Send(NULL,page,0);
	}

	GetLayersBase()->CloseProcessingForm();

}

void PropertyTrueColorBlockForm::on_ButtonGenerateLibs_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate TrueColorBlocks automatically");

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyTrueColorBlockForm_LS,LID_20)/*"Generating items"*/,GetLayersBase()->GetPageNumb()*10);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdGenerateTrueColorBlocks	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyTrueColorBlockForm::on_pushButtonGColor_clicked()
{
	TrueColorPickupForm	D(GetLayersBase()
						,NULL
						,&ColorGenerator.Cube
						,this);
	//D.ColorPanel.Cube	=ColorGenerator.Cube;
	D.ColorPanel.InitializedDoneCube();
	if(D.exec()==(int)true){
		ColorGenerator.Cube=D.ColorPanel.Cube;
		ColorGenerator.InitializedDoneCube();
		ColorGenerator.Repaint();
		if(TempLib!=NULL){
			TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(TempLib->GetLibrary());
			ALib->PickupColor=D.ColorPanel.Cube;
		}
	}
}

void PropertyTrueColorBlockForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.Send(NULL,page,0);
	}
	BroadcastShowInEdit();
}

void PropertyTrueColorBlockForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadTrueColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(PropertyTrueColorBlockForm_LS,LID_15)/*"Library error"*/, LangSolver.GetString(PropertyTrueColorBlockForm_LS,LID_16)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyTrueColorBlockForm::on_toolButtonLibrary_clicked()
{
	if(ui.toolButtonLibrary->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(0);
		if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
			for(int page=0;page<GetPageNumb();page++){
				GUICmdReqSetButtonMode	RCmd(GetLayersBase() ,sRoot,sName ,page);
				RCmd.Mode=GUICmdReqSetButtonMode::_LibraryTest;
				RCmd.InstForm=GetName();
				RCmd.Send(NULL,page,0);
			}
		}
	}
	BroadcastShowInEdit();
}
void PropertyTrueColorBlockForm::on_toolButtonCreateBlock_clicked()
{
	if(ui.toolButtonCreateBlock->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(1);
		if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
			for(int page=0;page<GetPageNumb();page++){
				GUICmdReqSetButtonMode	RCmd(GetLayersBase() ,sRoot,sName ,page);
				RCmd.Mode=GUICmdReqSetButtonMode::_CreateBlock;
				RCmd.InstForm=GetName();
				RCmd.Send(NULL,page,0);
			}
		}
		ShowBlockInfoList();
	}
	BroadcastShowInEdit();
}

void PropertyTrueColorBlockForm::ShowBlockInfoList(void)
{
	TrueColorBlockInfos.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqTrueColorBlockInfoList		CmdReq (GetLayersBase(),sRoot,sName,page);
		GUICmdSendTrueColorBlockInfoList	CmdSend(GetLayersBase(),sRoot,sName,page);
		CmdReq.Send(GetLayersBase()->GetGlobalPageFromLocal(page),0,CmdSend);
		for(TrueColorBlockInfoList *a=CmdSend.TrueColorBlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
			TrueColorBlockInfoList *b;
			for(b=TrueColorBlockInfos.GetFirst();b!=NULL;b=b->GetNext()){
				if(a->LibID==b->LibID){
					IntClass	*d=b->TrueColorBlockCount.GetItem(0);
					IntClass	*s=a->TrueColorBlockCount.GetItem(0);
					d->SetValue(d->GetValue()+s->GetValue());					
					break;
				}
			}
			if(b==NULL){
				b=new TrueColorBlockInfoList();
				b->LibID=a->LibID;
				IntClass	*s=a->TrueColorBlockCount.GetItem(0);
				b->TrueColorBlockCount.Add(s->GetValue());
				TrueColorBlockInfos.AppendList(b);
			}
		}
	}
	int	N=TrueColorBlockInfos.GetNumber();
	ui.tableWidgetBlockInfo->setRowCount(N);
	AlgorithmLibraryListContainer LibIDList;
	for(TrueColorBlockInfoList *a=TrueColorBlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList	*k=new AlgorithmLibraryList();
		k->SetLibID(a->GetLibID());
		LibIDList.AppendList(k);
	}
	TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
	GetLayersBase()->GetDatabaseLoader()->G_GetLibraryNames(*GetLayersBase()->GetDataBase(),BBase->GetLibraryContainer(),LibIDList);
	int	row=0;
	for(TrueColorBlockInfoList *a=TrueColorBlockInfos.GetFirst();a!=NULL;a=a->GetNext(),row++){
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
		for(IntClass *h=a->TrueColorBlockCount.GetFirst();h!=NULL;h=h->GetNext()){
			TotalCount+=h->GetValue();
		}
		W->setText(QString::number(TotalCount));
	}
}

void PropertyTrueColorBlockForm::on_pushButtonEditLibFolder_clicked()
{
	TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyTrueColorBlockForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui.labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}


void PropertyTrueColorBlockForm::on_pushButtonSetFrom_clicked()
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

void PropertyTrueColorBlockForm::on_pushButtonGetBack_clicked()
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

void PropertyTrueColorBlockForm::on_pushButtonEditLibrary_clicked()
{
	EditTrueColorLibrary	D(GetLayersBase(),this);
	D.exec();

	ShowLibList();
	if(TempLib!=NULL){
		CmdLoadTrueColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
		}
	}
}

void PropertyTrueColorBlockForm::on_tableWidgetBlockInfo_clicked(const QModelIndex &)
{
	TrueColorBlockBase	*BBase=GetTrueColorBlockBase();

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdReleaseSelectImagePanel	Cmd(GetLayersBase(),sRoot,sName ,page);
		Cmd.AlgoRoot=/**/"Basic";
		Cmd.AlgoName=/**/"TrueColorBlock";
		Cmd.Send(NULL,page,0);
	}

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdSelectByLibs	Cmd(BBase,sRoot,sName,page);
		for(int row=0;row<ui.tableWidgetBlockInfo->rowCount();row++){
			TrueColorBlockInfoList *a=TrueColorBlockInfos.GetItem(row);
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



void PropertyTrueColorBlockForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyTrueColorBlockForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}