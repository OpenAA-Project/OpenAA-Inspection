/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorBlock\PropertyColorBlockForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyColorBlockFormResource.h"
#include "PropertyColorBlockForm.h"
#include "XDLLOnly.h"
#include "ColorSelectBlockLibraryForm.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyColorBlockPacket.h"
#include "ColorBrightHistogramForm.h"
#include "ColorCreateManualBlockForm.h"
#include "EditColorBlockLibrary.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XGUIPacketGeneral.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyColorBlockForm::PropertyColorBlockForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent),ButtonR(false),ButtonG(false),ButtonB(false)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	ColorBlockBase	*BBase=GetColorBlockBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);
	ui.tableWidgetGeneratedLibList->setColumnWidth (0, 30);
	ui.tableWidgetGeneratedLibList->setColumnWidth (1, 80);	
	ui.tableWidgetBlockInfo->setColumnCount(3);
	ui.tableWidgetBlockInfo->setColumnWidth (0, 40);
	ui.tableWidgetBlockInfo->setColumnWidth (1, 160);
	ui.tableWidgetBlockInfo->setColumnWidth (2, 80);
	QStringList	HeaderLabel;
	HeaderLabel.append(LangSolver.GetString(PropertyColorBlockForm_LS,LID_37)/*"ID"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyColorBlockForm_LS,LID_38)/*"???C?u??????"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyColorBlockForm_LS,LID_39)/*"?u???b?N????"*/);
	ui.tableWidgetBlockInfo->setHorizontalHeaderLabels(HeaderLabel);

	TabBarBlockOnMouse.setParent(ui.frameBlockInfoOnMouse);
	TabBarBlockOnMouse.setGeometry(ui.frame->geometry().left(),ui.frame->geometry().top()-30,ui.frame->geometry().width(),30);
	for(int layer=0;layer<GetLayerNumb(0);layer++){
		TabBarBlockOnMouse.addTab (GetParamGlobal()->GetLayerName(layer));
	}
	connect(&TabBarBlockOnMouse,SIGNAL(currentChanged(int)),this,SLOT(TabBarBlockOnMouseChanged(int)));

	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		BInfo[i].ColorBlockInfoOnMouse=NULL;
	}

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempColorBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	if(TempLib!=NULL){
		TempLib->SetLibID(-1);
	}
	if(ui.toolButtonLibrary->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(0);
	}
	if(ui.toolButtonCreateBlock->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(1);
		ShowBlockInfoList();
	}

	ButtonR.setParent(ui.frame);
	ButtonG.setParent(ui.frame);
	ButtonB.setParent(ui.frame);

	ButtonR.setGeometry(ui.toolButtonR->geometry());
	ButtonG.setGeometry(ui.toolButtonG->geometry());
	ButtonB.setGeometry(ui.toolButtonB->geometry());

	ButtonR.setAutoExclusive(true);
	ButtonG.setAutoExclusive(true);
	ButtonB.setAutoExclusive(true);

	CurrentColor=0;
	ButtonR.setChecked(true);
	delete	ui.toolButtonR;
	ui.toolButtonR=NULL;
	delete	ui.toolButtonG;
	ui.toolButtonG=NULL;
	delete	ui.toolButtonB;
	ui.toolButtonB=NULL;

	ButtonR.setColor(GetParamGlobal()->GetOneGraphLayerColor(0));
	ButtonG.setColor(GetParamGlobal()->GetOneGraphLayerColor(1));
	ButtonB.setColor(GetParamGlobal()->GetOneGraphLayerColor(2));

	ButtonR.setText(GetParamGlobal()->GetLayerName(0));
	ButtonG.setText(GetParamGlobal()->GetLayerName(1));
	ButtonB.setText(GetParamGlobal()->GetLayerName(2));

	connect(&ButtonR,SIGNAL(clicked()),this,SLOT(on_ToolButton_clicked()));
	connect(&ButtonG,SIGNAL(clicked()),this,SLOT(on_ToolButton_clicked()));
	connect(&ButtonB,SIGNAL(clicked()),this,SLOT(on_ToolButton_clicked()));

	LibSortType	=KOS_ID_Up;
	connect(ui.tableWidgetLibList->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));
	
	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyColorBlockForm::~PropertyColorBlockForm()
{
	if(TempLib!=NULL)
		delete	TempLib;
}
ColorBlockBase	*PropertyColorBlockForm::GetColorBlockBase(void)
{
	return (ColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
}

void	PropertyColorBlockForm::MListSectionClicked ( int logicalIndex )
{
	switch(logicalIndex){
		case 0:
			if(LibSortType==KOS_ID_Up)
				LibSortType=KOS_ID_Dn;
			else
				LibSortType=KOS_ID_Up;
			break;
		case 1:
			if(LibSortType==KOS_Name_Up)
				LibSortType=KOS_Name_Dn;
			else
				LibSortType=KOS_Name_Up;
			break;
	}
	ShowLibList();
}

void	PropertyColorBlockForm::ShowTab(void)
{
	int	r=TabBarBlockOnMouse.currentIndex();
	while(TabBarBlockOnMouse.count()!=0){
		TabBarBlockOnMouse.removeTab(0);
	}
	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		if(BInfo[i].ColorBlockInfoOnMouse!=NULL){
			TabBarBlockOnMouse.addTab (QString(/**/"Page ")+QString::number(BInfo[i].Page));
		}
	}
	if(0<=r && TabBarBlockOnMouse.count()>r){
		TabBarBlockOnMouse.setCurrentIndex(r);
	}
}


void	PropertyColorBlockForm::TabBarBlockOnMouseChanged(int index)
{
	if(index>=0 && BInfo[index].ColorBlockInfoOnMouse!=NULL){
		ui.EditLibIDInBlock		->setText(QString::number(BInfo[index].ColorBlockInfoOnMouse->GetLibID()));
		ColorBlockBase	*BBase=GetColorBlockBase();
		CmdGetLibName	Cmd(GetLayersBase());
		Cmd.LibID	=BInfo[index].ColorBlockInfoOnMouse->GetLibID();
		BBase->TransmitDirectly(&Cmd);
		ui.EditLibNameInBlock	->setText(Cmd.LibName);

		if(ButtonR.isChecked()==true){
			ui.EditNBrightWidthL	->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.NBrightWidthL	);
			ui.EditNBrightWidthH	->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.NBrightWidthH	);
			ui.EditNOKDotL			->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.NOKDotL		);
			ui.EditNOKDotH			->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.NOKDotH		);
			ui.EditBBrightWidthL	->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.BBrightWidthL	);
			ui.EditBBrightWidthH	->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.BBrightWidthH	);
			ui.EditBOKDotL			->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.BOKDotL		);
			ui.EditBOKDotH			->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.BOKDotH		);
			ui.EditAdjustBlack		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.AdjustBlack	);
			ui.EditAdjustWhite		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.AdjustWhite	);

			ui.EditNMinNGCountL		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.NMinNGCountL);
			ui.EditNMinNGCountH		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.NMinNGCountH);
			ui.EditBMinNGCountL		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.BMinNGCountL);
			ui.EditBMinNGCountH		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsR.BMinNGCountH);
		}
		else if(ButtonG.isChecked()==true){
			ui.EditNBrightWidthL	->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.NBrightWidthL	);
			ui.EditNBrightWidthH	->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.NBrightWidthH	);
			ui.EditNOKDotL			->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.NOKDotL		);
			ui.EditNOKDotH			->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.NOKDotH		);
			ui.EditBBrightWidthL	->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.BBrightWidthL	);
			ui.EditBBrightWidthH	->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.BBrightWidthH	);
			ui.EditBOKDotL			->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.BOKDotL		);
			ui.EditBOKDotH			->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.BOKDotH		);
			ui.EditAdjustBlack		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.AdjustBlack	);
			ui.EditAdjustWhite		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.AdjustWhite	);

			ui.EditNMinNGCountL		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.NMinNGCountL);
			ui.EditNMinNGCountH		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.NMinNGCountH);
			ui.EditBMinNGCountL		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.BMinNGCountL);
			ui.EditBMinNGCountH		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsG.BMinNGCountH);
		}
		else if(ButtonB.isChecked()==true){
			ui.EditNBrightWidthL	->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.NBrightWidthL	);
			ui.EditNBrightWidthH	->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.NBrightWidthH	);
			ui.EditNOKDotL			->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.NOKDotL		);
			ui.EditNOKDotH			->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.NOKDotH		);
			ui.EditBBrightWidthL	->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.BBrightWidthL	);
			ui.EditBBrightWidthH	->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.BBrightWidthH	);
			ui.EditBOKDotL			->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.BOKDotL		);
			ui.EditBOKDotH			->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.BOKDotH		);
			ui.EditAdjustBlack		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.AdjustBlack	);
			ui.EditAdjustWhite		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.AdjustWhite	);

			ui.EditNMinNGCountL		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.NMinNGCountL);
			ui.EditNMinNGCountH		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.NMinNGCountH);
			ui.EditBMinNGCountL		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.BMinNGCountL);
			ui.EditBMinNGCountH		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->InsB.BMinNGCountH);
		}
		ui.checkBModeAdjustable	->setChecked(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->PointMove.ModeAdjustable	);

		ui.checkBModeWhiteMask	->setChecked(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->PointMove.ModeWhiteMask	);
		ui.checkBModeBlackMask	->setChecked(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->PointMove.ModeBlackMask	);

		ui.EditSelfSearch		->setValue(BInfo[index].ColorBlockInfoOnMouse->GetThresholdR()->SelfSearch		);
	}
	else{
		ui.EditLibIDInBlock		->clear();
		ui.EditLibNameInBlock	->clear();

		ui.EditNBrightWidthL	->clear();
		ui.EditNBrightWidthH	->clear();
		ui.EditNOKDotL			->clear();
		ui.EditNOKDotH			->clear();
		ui.EditBBrightWidthL	->clear();
		ui.EditBBrightWidthH	->clear();
		ui.EditBOKDotL			->clear();
		ui.EditBOKDotH			->clear();

		ui.EditNMinNGCountL		->clear();
		ui.EditNMinNGCountH		->clear();
		ui.EditBMinNGCountL		->clear();
		ui.EditBMinNGCountH		->clear();

		ui.checkBModeAdjustable	->setChecked(false);
		ui.EditAdjustBlack		->clear();
		ui.EditAdjustWhite		->clear();

		ui.checkBModeWhiteMask		->setChecked(false);
		ui.checkBModeBlackMask		->setChecked(false);

		ui.EditSelfSearch		->clear();
	}
}

static	int	FuncIDUp(const void *a ,const void *b)
{
	AlgorithmLibraryList	*pa=((AlgorithmLibraryList **)a)[0];
	AlgorithmLibraryList	*pb=((AlgorithmLibraryList **)b)[0];
	return pa->GetLibID() - pb->GetLibID();
}

static	int	FuncIDDn(const void *a ,const void *b)
{
	AlgorithmLibraryList	*pa=((AlgorithmLibraryList **)a)[0];
	AlgorithmLibraryList	*pb=((AlgorithmLibraryList **)b)[0];
	return pb->GetLibID() - pa->GetLibID();
}

static	int	FuncNameUp(const void *a ,const void *b)
{
	AlgorithmLibraryList	*pa=((AlgorithmLibraryList **)a)[0];
	AlgorithmLibraryList	*pb=((AlgorithmLibraryList **)b)[0];
	if(pa->GetLibName() < pb->GetLibName())
		return 1;
	if(pa->GetLibName() > pb->GetLibName())
		return -1;
	return 0;
}

static	int	FuncNameDn(const void *a ,const void *b)
{
	AlgorithmLibraryList	*pa=((AlgorithmLibraryList **)a)[0];
	AlgorithmLibraryList	*pb=((AlgorithmLibraryList **)b)[0];
	if(pa->GetLibName() < pb->GetLibName())
		return -1;
	if(pa->GetLibName() > pb->GetLibName())
		return 1;
	return 0;
}

void	PropertyColorBlockForm::ShowLibList(void)
{
	ui.tableWidgetLibList->setRowCount(0);
	ColorBlockBase	*BBase=GetColorBlockBase();
	if(BBase!=NULL){
		CmdGetColorBlockLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		//LibList	=Packet.AList;
		LibList.RemoveAll();

		AlgorithmLibraryList	**Dim=new AlgorithmLibraryList*[Packet.AList.GetCount()];
		int	row=0;
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			Dim[row]=a;
		}
		if(LibSortType==KOS_ID_Up)
			QSort(Dim,row,sizeof(Dim[0]),FuncIDUp);
		else if(LibSortType==KOS_ID_Dn)
			QSort(Dim,row,sizeof(Dim[0]),FuncIDDn);
		else if(LibSortType==KOS_Name_Up)
			QSort(Dim,row,sizeof(Dim[0]),FuncNameUp);
		else if(LibSortType==KOS_Name_Dn)
			QSort(Dim,row,sizeof(Dim[0]),FuncNameDn);

		for(int i=0;i<row;i++){
			Packet.AList.RemoveList(Dim[i]);
			LibList.AppendList(Dim[i]);
		}
		delete	[]Dim;

		row=0;
		ui.tableWidgetLibList->setRowCount(LibList.GetNumber());
		for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
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

void	PropertyColorBlockForm::ShowInEdit(void)
{
	ShowBlockInfoList();
}
void	PropertyColorBlockForm::StartPage(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui.labelLibFolderName->setText(FolderName);
	}
}

void	PropertyColorBlockForm::BuildForShow(void)
{
	ShowBlockInfoList();
}

void	PropertyColorBlockForm::TransmitDirectly(GUIDirectMessage *packet)
{
	ColorBlockBase	*BBase=GetColorBlockBase();
	CmdColorBlockDrawModePacket	*BDrawModePacket=dynamic_cast<CmdColorBlockDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		if(ui.toolButtonLibrary->isChecked()==true)
			BDrawModePacket->Mode=CmdColorBlockDrawModePacket::_LibTest;
		else if(ui.toolButtonCreateBlock->isChecked()==true)
			BDrawModePacket->Mode=CmdColorBlockDrawModePacket::_CreatedBlock;
		if(ui.toolButtonArea->isChecked()==true)
			BDrawModePacket->DType=CmdColorBlockDrawModePacket::_Area;
		else if(ui.toolButtonEdge->isChecked()==true)
			BDrawModePacket->DType=CmdColorBlockDrawModePacket::_Edge;
		else if(ui.toolButtonInside->isChecked()==true)
			BDrawModePacket->DType=CmdColorBlockDrawModePacket::_Inside;
		return;
	}
	CmdColorBlockDrawEnd	*BlockDEnd=dynamic_cast<CmdColorBlockDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		if(ui.toolButtonLibrary->isChecked()==true){
			//GlobalPickupArea+=BlockDEnd->Area;
			ColorBlockLibrary	*ALib=dynamic_cast<ColorBlockLibrary *>(TempLib->GetLibrary());
			ColorBrightHistogramForm	D(BlockDEnd->Area,BlockDEnd->ImagePanelPoint
											,ALib->PickupRL,ALib->PickupRH
											,ALib->PickupGL,ALib->PickupGH
											,ALib->PickupBL,ALib->PickupBH
											,this);
			D.Reflect(ALib->PickupRL,ALib->PickupRH
					, ALib->PickupGL,ALib->PickupGH
					, ALib->PickupBL,ALib->PickupBH);
			if(D.exec()==(int)true){
				ALib->PickupRL	=D.PickupRL;
				ALib->PickupRH	=D.PickupRH;
				ALib->PickupGL	=D.PickupGL;
				ALib->PickupGH	=D.PickupGH;
				ALib->PickupBL	=D.PickupBL;
				ALib->PickupBH	=D.PickupBH;
			}
		}
		else if(ui.toolButtonCreateBlock->isChecked()==true){
			ColorCreateManualBlockForm	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual ColorBlock");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=BlockDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						GUICmdSendAddManualColorBlock	Cmd(GetLayersBase(),sRoot,sName,page);
						Cmd.Area=A;
						CmdCreateByteArrayFromColorBlockItemPacket	BCmd(GetLayersBase());
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
	CmdColorBlockShowAttrPacket	*ShowAttr=dynamic_cast<CmdColorBlockShowAttrPacket *>(packet);
	if(ShowAttr!=NULL){

	}
	CmdExecuteMouseLDown	*CmdExecuteMouseLDownVar=dynamic_cast<CmdExecuteMouseLDown *>(packet);
	if(CmdExecuteMouseLDownVar!=NULL){
		for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
			//if(BInfo[i].BlockInfoOnMouse!=NULL)
			//	delete	BInfo[i].BlockInfoOnMouse;
			BInfo[i].ColorBlockInfoOnMouse=NULL;
		}
		int	N=0;
		for(IntClass *p=CmdExecuteMouseLDownVar->PageList.GetFirst();p!=NULL;p=p->GetNext()){
			int page=p->GetValue();

			IntList	Items;
			if(N>=sizeof(BInfo)/sizeof(BInfo[0]))
				break;
			for(ListPageLayerID *a=CmdExecuteMouseLDownVar->CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Page==page){
					Items.Add(a->ID);
				}
			}
			if(Items.GetCount()!=NULL){
				GUICmdReqColorBlockFromList	ReqCmd(GetLayersBase(),sRoot,sName,page);
				GUICmdAckColorBlockFromList	AckCmd(GetLayersBase(),sRoot,sName,page);
				ReqCmd.CurrentItem=Items;
				ReqCmd.Send(page,0,AckCmd);
				for(int i=0;i<sizeof(AckCmd.ColorBlockInfoOnMouse)/sizeof(AckCmd.ColorBlockInfoOnMouse[0]);i++){
					if(AckCmd.ColorBlockInfoOnMouse[i]!=NULL){
						BInfo[N].ColorBlockInfoOnMouse=AckCmd.ColorBlockInfoOnMouse[i];
						AckCmd.ColorBlockInfoOnMouse[i]=NULL;
						BInfo[N].Page=page;
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

	/*
	CmdExecuteMouseRDownWithShift	*ShiftRight=dynamic_cast<CmdExecuteMouseRDownWithShift *>(packet);
	if(ShiftRight!=NULL){
		QByteArray	BlockItemData;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
			GUICmdReqSelectedColorBlockItemAttr	ReqCmd(GetLayersBase(),sRoot,sName,page);
			ReqCmd.LayerList=ShiftRight->LayerList;
			GUICmdSendSelectedColorBlockItemAttr	SendCmd(GetLayersBase(),sRoot,sName,page);
			if(ReqCmd.Send(ReqCmd.GetGlobalPage(),0,SendCmd)==true
			&& SendCmd.IsReceived()==true){
				if(SendCmd.ExistSelected==true){
					BlockItemData=SendCmd.BItem;
					break;
				}
			}
		}
		if(BlockItemData.size()!=0){
			ColorCreateManualBlockForm	D(GetLayersBase(),NULL);
			CmdLoadColorBlockItemPacketFromByteArray	CmdPacket;
			CmdPacket.Buff=BlockItemData;
			CmdPacket.BItemPoint=D.BItem;
			BBase->TransmitDirectly(&CmdPacket);
			D.Reflect();
			if(D.exec()==(int)true){
				IntList PageList;
				for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					GUICmdSendModifySelectedColorBlock	Cmd(GetLayersBase(),sRoot,sName,page);
					CmdCreateByteArrayFromColorBlockItemPacket	BCmd;
					BCmd.Point=D.BItem;
					BBase->TransmitDirectly(&BCmd);
					Cmd.BItem=BCmd.Buff;
					Cmd.LayerList=ShiftRight->LayerList;
					Cmd.Send(NULL,page,0);					
				}
			}
		}
	}
	*/
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

bool	PropertyColorBlockForm::SaveContent(QIODevice *f)
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
bool	PropertyColorBlockForm::LoadContent(QIODevice *f)
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
void	PropertyColorBlockForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	ColorBlockLibrary	*ALib=dynamic_cast<ColorBlockLibrary *>(data.GetLibrary());
	ui.EditMinBlockSize		->setValue(ALib->MinBlockSize);
	ui.EditMaxBlockSize		->setValue(ALib->MaxBlockSize);
	ui.EditMinBlockDots		->setValue(ALib->MinBlockDots);
	ui.EditMaxBlockDots		->setValue(ALib->MaxBlockDots);
	ui.EditLimitBlockSize	->setValue(ALib->LimitBlockSize);
	ui.EditSpaceToOutline	->setValue(ALib->SpaceToOutline);
	ui.EditNoiseSize		->setValue(ALib->NoiseSize);
	ui.EditNoiseSizePinHole	->setValue(ALib->NoiseSizePinHole);
	ui.EditPriority			->setValue(ALib->Priority);
}

void	PropertyColorBlockForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	ColorBlockLibrary	*ALib=dynamic_cast<ColorBlockLibrary *>(data.GetLibrary());
	ALib->MinBlockSize		=ui.EditMinBlockSize	->value();
	ALib->MaxBlockSize		=ui.EditMaxBlockSize	->value();
	ALib->MinBlockDots		=ui.EditMinBlockDots	->value();
	ALib->MaxBlockDots		=ui.EditMaxBlockDots	->value();
	ALib->LimitBlockSize	=ui.EditLimitBlockSize	->value();
	ALib->SpaceToOutline	=ui.EditSpaceToOutline	->value();
	ALib->NoiseSize			=ui.EditNoiseSize		->value();
	ALib->NoiseSizePinHole	=ui.EditNoiseSizePinHole->value();
	ALib->Priority			=ui.EditPriority		->value();
}

void PropertyColorBlockForm::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL || TempLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(PropertyColorBlockForm_LS,LID_9)/*"Warning"*/, LangSolver.GetString(PropertyColorBlockForm_LS,LID_10)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateColorBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	ColorBlockBase	*BBase=GetColorBlockBase();
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

void PropertyColorBlockForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		ColorBlockBase	*BBase=GetColorBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(PropertyColorBlockForm_LS,LID_40)/*"Library error"*/, LangSolver.GetString(PropertyColorBlockForm_LS,LID_41)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyColorBlockForm::on_ButtonGenerateLibs_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate ColorBlocks automatically");

	CmdReqImageLayer	DrawMode(GetLayersBase(),GetLayerNumb(0));
	GUIFormBase	*GProp=GetImageControlToolsPointer();
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyColorBlockForm_LS,LID_0)/*"Generating items"*/
								,DrawMode.LayerList.GetCount()*GetLayersBase()->GetPageNumb()*10);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdGenerateColorBlocks	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}
GUIFormBase	*PropertyColorBlockForm::GetImageControlToolsPointer(void)
{
	GUIFormBase *RetGUI[1000];
	int	N=GetLayersBase()->EnumGUIInst(/**/"Button" ,/**/"ImageControlTools" ,RetGUI ,sizeof(RetGUI)/sizeof(RetGUI[0]));

	GUIFormBase	*ImagePanel=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ColorBlockImagePanel" ,/**/"");
	if(ImagePanel==NULL)
		return NULL;
	QString	ImageName=ImagePanel->GetName();

	for(int i=0;i<N;i++){
		ImageControlTools	*ImageControlToolsPointer=dynamic_cast<ImageControlTools *>(RetGUI[i]);
		if(ImageControlToolsPointer!=NULL){
			if(ImageControlToolsPointer->RelatedPanels.contains(ImageName)==true){
				return ImageControlToolsPointer;
			}
		}
	}
	return NULL;
}

void PropertyColorBlockForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		ColorBlockBase	*BBase=GetColorBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(PropertyColorBlockForm_LS,LID_42)/*"Library error"*/, LangSolver.GetString(PropertyColorBlockForm_LS,LID_43)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyColorBlockForm::on_tableWidgetLibList_doubleClicked(QModelIndex Index)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyColorBlockForm::on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex Index)
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

void	PropertyColorBlockForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	ColorBlockBase	*BBase=GetColorBlockBase();
	if(BBase!=NULL){
		CmdCreateTempColorBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;
		ColorBlockLibrary	*ALib=dynamic_cast<ColorBlockLibrary *>(SLib->GetLibrary());
		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadColorBlockLibraryPacket	Packet(GetLayersBase());
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

void PropertyColorBlockForm::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyColorBlockForm_LS,LID_1)/*"Pickup Test"*/);

	GetLibraryFromWindow(*TempLib);

	CmdReqImageLayer	DrawMode(GetLayersBase(),GetLayerNumb(0));
	GUIFormBase	*GProp=GetImageControlToolsPointer();
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.LibPoint	=TempLib;
		Cmd.Send(NULL,page,0);
	}

	GetLayersBase()->CloseProcessingForm();

}

void PropertyColorBlockForm::ShowBlockInfoList(void)
{
	ColorBlockInfos.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqColorBlockInfoList		CmdReq (GetLayersBase(),sRoot,sName,page);
		GUICmdSendColorBlockInfoList	CmdSend(GetLayersBase(),sRoot,sName,page);
		CmdReq.Send(GetLayersBase()->GetGlobalPageFromLocal(page),0,CmdSend);
		for(ColorBlockInfoList *a=CmdSend.ColorBlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
			ColorBlockInfoList *b;
			for(b=ColorBlockInfos.GetFirst();b!=NULL;b=b->GetNext()){
				if(a->LibID==b->LibID){
					b->ColorBlockCount += a->ColorBlockCount;
					break;
				}
			}
			if(b==NULL){
				b=new ColorBlockInfoList();
				b->LibID=a->LibID;
				b->ColorBlockCount=a->ColorBlockCount;
				ColorBlockInfos.AppendList(b);
			}
		}
	}
	int	N=ColorBlockInfos.GetNumber();
	ui.tableWidgetBlockInfo->setRowCount(N);
	AlgorithmLibraryListContainer LibIDList;
	for(ColorBlockInfoList *a=ColorBlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList	*k=new AlgorithmLibraryList();
		k->SetLibID(a->GetLibID());
		LibIDList.AppendList(k);
	}
	ColorBlockBase	*BBase=GetColorBlockBase();
	GetLayersBase()->GetDatabaseLoader()->G_GetLibraryNames(*GetLayersBase()->GetDataBase(),BBase->GetLibraryContainer(),LibIDList);
	int	row=0;
	for(ColorBlockInfoList *a=ColorBlockInfos.GetFirst();a!=NULL;a=a->GetNext(),row++){
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
		int	TotalCount=a->ColorBlockCount;
		W->setText(QString::number(TotalCount));
	}
}

void PropertyColorBlockForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.Send(NULL,page,0);
	}
}

void PropertyColorBlockForm::on_pushButtonEditLibrary_clicked()
{
	EditColorBlockLibrary	D(GetLayersBase(),this);
	D.exec();

	ShowLibList();
	if(TempLib!=NULL){
		CmdLoadColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		ColorBlockBase	*BBase=GetColorBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
		}
	}
}

void PropertyColorBlockForm::on_pushButtonEditLibFolder_clicked()
{
	ColorBlockBase	*BBase=GetColorBlockBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyColorBlockForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui.labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void PropertyColorBlockForm::on_toolButtonLibrary_clicked()
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

void PropertyColorBlockForm::on_toolButtonCreateBlock_clicked()
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

void PropertyColorBlockForm::on_pushButtonSetFrom_clicked()
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

void PropertyColorBlockForm::on_pushButtonGetBack_clicked()
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

void PropertyColorBlockForm::on_tableWidgetBlockInfo_cellClicked(int,int)
{
	ColorBlockBase	*BBase=GetColorBlockBase();

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdReleaseSelectImagePanel	Cmd(GetLayersBase(),sRoot,sName ,page);
		Cmd.AlgoRoot=/**/"Basic";
		Cmd.AlgoName=/**/"ColorBlockInspection";
		Cmd.Send(NULL,page,0);
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdSelectByLibs	Cmd(BBase,sRoot,sName,page);
		for(int row=0;row<ui.tableWidgetBlockInfo->rowCount();row++){
			ColorBlockInfoList *a=ColorBlockInfos.GetItem(row);
			QTableWidgetItem *item=ui.tableWidgetBlockInfo->item(row,0);
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

void PropertyColorBlockForm::on_ToolButton_clicked()
{
	TabBarBlockOnMouseChanged(TabBarBlockOnMouse.currentIndex());
}


void PropertyColorBlockForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyColorBlockForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}