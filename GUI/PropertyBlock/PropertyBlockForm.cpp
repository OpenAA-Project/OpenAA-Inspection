/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBlock\PropertyBlockForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyBlockFormResource.h"
#include "PropertyBlockForm.h"
#include "XDLLOnly.h"
#include "SelectBlockLibraryForm.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyBlockPacket.h"
#include "BrightHistogramForm.h"
#include "CreateManualBlockForm.h"
#include "EditBlockLibrary.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XPropertyBlockCommon.h"
#include "XGUIPacketGeneral.h"
#include<QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyBlockForm::PropertyBlockForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	LibFolderID=-1;

	BlockBase	*BBase=GetBlockBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	int	Page=0;
	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);
	ui.tableWidgetGeneratedLibList->setColumnWidth (0, 30);
	ui.tableWidgetGeneratedLibList->setColumnWidth (1, 80);	
	ui.tableWidgetBlockInfo->setColumnCount(3+GetLayerNumb(Page));
	ui.tableWidgetBlockInfo->setColumnWidth (0, 30);
	ui.tableWidgetBlockInfo->setColumnWidth (1, 100);
	ui.tableWidgetBlockInfo->setColumnWidth (2, 60);
	QStringList	HeaderLabel;
	HeaderLabel.append(LangSolver.GetString(PropertyBlockForm_LS,LID_33)/*"ID"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyBlockForm_LS,LID_34)/*"???C?u??????"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyBlockForm_LS,LID_35)/*"?u???b?N????"*/);
	for(int layer=0;layer<GetLayerNumb(Page);layer++){
		ui.tableWidgetBlockInfo->setColumnWidth (3+layer, 50);
		HeaderLabel.append(GetParamGlobal()->GetLayerName(layer));
	}
	ui.tableWidgetBlockInfo->setHorizontalHeaderLabels(HeaderLabel);

	TabBarBlockOnMouse.setParent(ui.frameBlockInfoOnMouse);
	TabBarBlockOnMouse.setGeometry(ui.frame->geometry().left(),ui.frame->geometry().top()-30,ui.frame->geometry().width(),30);
	connect(&TabBarBlockOnMouse,SIGNAL(currentChanged(int)),this,SLOT(TabBarBlockOnMouseChanged(int)));

	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		BInfo[i].BlockInfoOnMouse=NULL;
	}

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempBlockLibraryPacket	Packet(GetLayersBase());
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

	LibSortType	=KOS_ID_Up;
	connect(ui.tableWidgetLibList->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));
	
	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyBlockForm::~PropertyBlockForm()
{
	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}
void	PropertyBlockForm::MListSectionClicked ( int logicalIndex )
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


void	PropertyBlockForm::ShowTab(void)
{
	int	r=TabBarBlockOnMouse.currentIndex();
	while(TabBarBlockOnMouse.count()!=0){
		TabBarBlockOnMouse.removeTab(0);
	}
	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		if(BInfo[i].BlockInfoOnMouse!=NULL){
			TabBarBlockOnMouse.addTab (QString::number(BInfo[i].Page)
										+LangSolver.GetString(PropertyBlockForm_LS,LID_36)/*"-"*/
										+GetParamGlobal()->GetLayerName(BInfo[i].Layer));
		}
	}
	if(0<=r && TabBarBlockOnMouse.count()>r){
		TabBarBlockOnMouse.setCurrentIndex(r);
	}
}

void	PropertyBlockForm::TabBarBlockOnMouseChanged(int index)
{
	if(index>=0 && BInfo[index].BlockInfoOnMouse!=NULL){
		ui.EditLibIDnBlock		->setText(QString::number(BInfo[index].BlockInfoOnMouse->GetLibID()));
		BlockBase	*BBase=GetBlockBase();
		CmdGetLibName	Cmd(GetLayersBase());
		Cmd.LibID	=BInfo[index].BlockInfoOnMouse->GetLibID();
		BBase->TransmitDirectly(&Cmd);
		ui.EditLibNameInBlock	->setText(Cmd.LibName);

		ui.EditNBrightWidthL	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.NBrightWidthL	);
		ui.EditNBrightWidthH	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.NBrightWidthH	);
		ui.EditNOKDotL			->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.NOKDotL		);
		ui.EditNOKDotH			->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.NOKDotH		);
		ui.EditBBrightWidthL	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.BBrightWidthL	);
		ui.EditBBrightWidthH	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.BBrightWidthH	);
		ui.EditBOKDotL			->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.BOKDotL		);
		ui.EditBOKDotH			->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.BOKDotH		);

		ui.EditNMinNGCountL		->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.NMinNGCountL);
		ui.EditNMinNGCountH		->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.NMinNGCountH);
		ui.EditBMinNGCountL		->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.BMinNGCountL);
		ui.EditBMinNGCountH		->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.BMinNGCountH);

		ui.checkBModeAdjustable	->setChecked(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.PointMove.ModeAdjustable	);
		ui.EditAdjustBlack		->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.AdjustBlack	);
		ui.EditAdjustWhite		->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.AdjustWhite	);

		ui.checkBModeWhiteMask	->setChecked(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.PointMove.ModeWhiteMask	);
		ui.checkBModeBlackMask	->setChecked(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.PointMove.ModeBlackMask	);

		ui.EditSelfSearch		->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshouldBag.SelfSearch		);
	}
	else{
		ui.EditLibIDnBlock		->clear();
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

BlockBase	*PropertyBlockForm::GetBlockBase(void)
{
	return (BlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
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

void	PropertyBlockForm::ShowLibList(void)
{
	ui.tableWidgetLibList->setRowCount(0);
	BlockBase	*BBase=GetBlockBase();
	if(BBase!=NULL){
		CmdGetBlockLibraryListPacket	Packet(GetLayersBase());
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
void	PropertyBlockForm::ShowInEdit(void)
{
	ShowBlockInfoList();
}
void	PropertyBlockForm::StartPage(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui.labelLibFolderName->setText(FolderName);
	}
	on_toolButtonLibrary_clicked();
	on_toolButtonCreateBlock_clicked();
}
void	PropertyBlockForm::BuildForShow(void)
{
	StartPage();
}
void	PropertyBlockForm::SetupLibFolder(int _LibFolderID,int originalLibFolder)
{
	LibFolderID=_LibFolderID;
	QString	LibFolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
	SetLibFolder(LibFolderID,LibFolderName);
}
void	PropertyBlockForm::TransmitDirectly(GUIDirectMessage *packet)
{
	BlockBase	*BBase=GetBlockBase();
	CmdBlockDrawModePacket	*BDrawModePacket=dynamic_cast<CmdBlockDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		if(ui.toolButtonLibrary->isChecked()==true)
			BDrawModePacket->Mode=CmdBlockDrawModePacket::_LibTest;
		else if(ui.toolButtonCreateBlock->isChecked()==true)
			BDrawModePacket->Mode=CmdBlockDrawModePacket::_CreatedBlock;
		if(ui.toolButtonArea->isChecked()==true)
			BDrawModePacket->DType=CmdBlockDrawModePacket::_Area;
		else if(ui.toolButtonEdge->isChecked()==true)
			BDrawModePacket->DType=CmdBlockDrawModePacket::_Edge;
		else if(ui.toolButtonInside->isChecked()==true)
			BDrawModePacket->DType=CmdBlockDrawModePacket::_Inside;
		else if(ui.toolButtonBeforeShrink->isChecked()==true)
			BDrawModePacket->DType=CmdBlockDrawModePacket::_BeforeShrink;
		BDrawModePacket->DrawDirUp				=ui.toolButtonDirUp				->isChecked();
		BDrawModePacket->DrawDirLeft			=ui.toolButtonDirLeft			->isChecked();
		BDrawModePacket->DrawDirRight			=ui.toolButtonDirRight			->isChecked();
		BDrawModePacket->DrawDirBottom			=ui.toolButtonDirBottom			->isChecked();
		BDrawModePacket->DrawDirSkip			=ui.toolButtonSkipSearch		->isChecked();
		BDrawModePacket->DrawOmitMatchLineArea	=ui.toolButtonOmitMatchLineArea	->isChecked();
		return;
	}
	CmdBlockDrawEnd	*BlockDEnd=dynamic_cast<CmdBlockDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		if(ui.toolButtonLibrary->isChecked()==true){
			if(TempLib->GetLibID()>=0){
				//GlobalPickupArea+=BlockDEnd->Area;
				BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(TempLib->GetLibrary());
				BrightHistogramForm	D(BlockDEnd->Area,BlockDEnd->ImagePanelPoint
									  ,ALib->PickupL,ALib->PickupH,this);
				D.Reflect(ALib->PickupL,ALib->PickupH);
				if(D.exec()==(int)true){
					ALib->PickupL	=D.PickupL;
					ALib->PickupH	=D.PickupH;
				}
			}
		}
		else if(ui.toolButtonCreateBlock->isChecked()==true){
			int	Layer=0;
			if(BlockDEnd->LayerList.GetCount()!=0)
				Layer=BlockDEnd->LayerList.GetFirst()->GetValue();
			CreateManualBlockForm	D(GetLayersBase(),Layer,NULL);
			if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual Block");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=BlockDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdSendAddManualBlock	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
						Cmd.Area=A;
						CmdCreateByteArrayFromBlockItemPacket	BCmd(GetLayersBase());
						BCmd.Point=D.BItem;
						BBase->TransmitDirectly(&BCmd);
						Cmd.BItem=BCmd.Buff;
						Cmd.LayerList=BlockDEnd->LayerList;
						Cmd.SendOnly(GlobalPage,0);
					}
				}
				ShowBlockInfoList();
			}
		}
		return;
	}
	CmdBlockShowAttrPacket	*ShowAttr=dynamic_cast<CmdBlockShowAttrPacket *>(packet);
	if(ShowAttr!=NULL){

	}
	CmdExecuteMouseLDown	*CmdExecuteMouseLDownVar=dynamic_cast<CmdExecuteMouseLDown *>(packet);
	if(CmdExecuteMouseLDownVar!=NULL){
		for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
			//if(BInfo[i].BlockInfoOnMouse!=NULL)
			//	delete	BInfo[i].BlockInfoOnMouse;
			BInfo[i].BlockInfoOnMouse=NULL;
		}
		int	N=0;
		for(IntClass *p=CmdExecuteMouseLDownVar->PageList.GetFirst();p!=NULL;p=p->GetNext()){
			int page=p->GetValue();
			for(int layer=0;layer<GetLayerNumb(page);layer++){
				ListLayerAndIDPack	Items;
				if(N>=sizeof(BInfo)/sizeof(BInfo[0]))
					break;
				for(ListPageLayerID *a=CmdExecuteMouseLDownVar->CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->Page==page && a->Layer==layer){
						Items.AppendList(new ListLayerAndID(a->Layer,a->ID));
					}
				}
				if(Items.GetNumber()!=NULL){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdReqBlockFromList	ReqCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					GUICmdAckBlockFromList	AckCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					ReqCmd.CurrentItem=Items;
					ReqCmd.Send(GlobalPage,0,AckCmd);
					for(int i=0;i<sizeof(AckCmd.BlockInfoOnMouse)/sizeof(AckCmd.BlockInfoOnMouse[0]);i++){
						if(AckCmd.BlockInfoOnMouse[i]!=NULL){
							BInfo[N].BlockInfoOnMouse=AckCmd.BlockInfoOnMouse[i];
							AckCmd.BlockInfoOnMouse[i]=NULL;
							BInfo[N].Page=page;
							BInfo[N].Layer=layer;
							N++;
							if(N>=sizeof(BInfo)/sizeof(BInfo[0]))
								break;
						}
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
			GUICmdReqSelectedBlockItemAttr	ReqCmd(GetLayersBase(),sRoot,sName,page);
			ReqCmd.LayerList=ShiftRight->LayerList;
			GUICmdSendSelectedBlockItemAttr	SendCmd(GetLayersBase(),sRoot,sName,page);
			if(ReqCmd.Send(ReqCmd.GetGlobalPage(),0,SendCmd)==true
			&& SendCmd.IsReceived()==true){
				if(SendCmd.ExistSelected==true){
					BlockItemData=SendCmd.BItem;
					break;
				}
			}
		}
		if(BlockItemData.size()!=0){
			CreateManualBlockForm	D(GetLayersBase(),NULL);
			CmdLoadBlockItemPacketFromByteArray	CmdPacket;
			CmdPacket.Buff=BlockItemData;
			CmdPacket.BItemPoint=D.BItem;
			BBase->TransmitDirectly(&CmdPacket);
			D.Reflect();
			if(D.exec()==(int)true){
				IntList PageList;
				for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					GUICmdSendModifySelectedBlock	Cmd(GetLayersBase(),sRoot,sName,page);
					CmdCreateByteArrayFromBlockItemPacket	BCmd;
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
		return;
	}
	CmdSelectBlockLibraryDialog	*CmdSelectBlockLibraryDialogVar=dynamic_cast<CmdSelectBlockLibraryDialog *>(packet);
	if(CmdSelectBlockLibraryDialogVar!=NULL){
		SelectBlockLibraryForm	D(GetLayersBase(),NULL);
		if(D.exec()==QDialog::Accepted){
			CmdSelectBlockLibraryDialogVar->LibID=D.SelectedLibID;
		}
		return;
	}
	CmdUpdateBlockCommon	*CmdUpdateBlockCommonVar=dynamic_cast<CmdUpdateBlockCommon *>(packet);
	if(CmdUpdateBlockCommonVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdUpdateBlockCommon	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.LibID			=CmdUpdateBlockCommonVar->LibID;
			Cmd.ThresholdInfo	=CmdUpdateBlockCommonVar->ThresholdInfo;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
	CmdGenerateBlockCommon	*CmdGenerateBlockCommonVar=dynamic_cast<CmdGenerateBlockCommon *>(packet);
	if(CmdGenerateBlockCommonVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdGenerateBlockCommon	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.Infos			=CmdGenerateBlockCommonVar->Infos;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
	UpdateBlockLibrary	*UpdateBlockLibraryVar=dynamic_cast<UpdateBlockLibrary *>(packet);
	if(UpdateBlockLibraryVar!=NULL){
		if(BBase!=NULL){
			CmdCreateTempBlockLibraryPacket	CPacket(GetLayersBase());
			BBase->TransmitDirectly(&CPacket);
			AlgorithmLibraryLevelContainer	*SLib=CPacket.Point;

			SLib->SetLibID(UpdateBlockLibraryVar->LibID);
			CmdLoadBlockLibraryPacket	LPacket(GetLayersBase());
			LPacket.Point=SLib;
			BBase->TransmitDirectly(&LPacket);

			AlgorithmLibraryLevelContainer	*BLib=LPacket.Point;
			if(UpdateBlockLibraryVar->SpaceToOutline>=0){
				BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(BLib->GetLibrary());
				ALib->SpaceToOutline	=UpdateBlockLibraryVar->SpaceToOutline;
			}
			CmdUpdateBlockLibraryPacket	UPacket(GetLayersBase());
			UPacket.Point=BLib;
			BBase->TransmitDirectly(&UPacket);

			delete	SLib;
		}
		return;
	}
	CmdRemoveAllOriginalBlockItems	*CmdRemoveAllOriginalBlockItemsVar=dynamic_cast<CmdRemoveAllOriginalBlockItems *>(packet);
	if(CmdRemoveAllOriginalBlockItemsVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqRemoveAllOriginal	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.GeneratedOrigin	=CmdRemoveAllOriginalBlockItemsVar->GeneratedOrigin;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
	ChangeBlocksThresholdCommon	*ChangeBlocksThresholdCommonVar=dynamic_cast<ChangeBlocksThresholdCommon *>(packet);
	if(ChangeBlocksThresholdCommonVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdChangeBlocksThreshold	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.BlockLibID	=ChangeBlocksThresholdCommonVar->BlockLibID;
			Cmd.InfosData	=ChangeBlocksThresholdCommonVar->InfosData;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
}

bool	PropertyBlockForm::SaveContent(QIODevice *f)
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
bool	PropertyBlockForm::LoadContent(QIODevice *f)
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

void	PropertyBlockForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(data.GetLibrary());
	ui.EditMinBlockSize		->setValue(ALib->MinBlockSize);
	ui.EditMaxBlockSize		->setValue(ALib->MaxBlockSize);
	ui.EditMinBlockDots		->setValue(ALib->MinBlockDots);
	ui.EditMaxBlockDots		->setValue(ALib->MaxBlockDots);
	ui.EditLimitBlockSize	->setValue(ALib->LimitBlockSize);
	ui.EditSpaceToOutline	->setValue(ALib->SpaceToOutline);
	ui.checkBPlusHalfDotIsolation	->setChecked(ALib->GenerationMode.PlusHalfDotIsolation);
	ui.EditNoiseSize		->setValue(ALib->NoiseSize);
	ui.EditNoiseSizePinHole	->setValue(ALib->NoiseSizePinHole);
	ui.EditPriority			->setValue(ALib->Priority);
	ui.EditOutlineGeneration->setValue(ALib->OutlineGeneration);
}

void	PropertyBlockForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(data.GetLibrary());
	ALib->MinBlockSize		=ui.EditMinBlockSize	->value();
	ALib->MaxBlockSize		=ui.EditMaxBlockSize	->value();
	ALib->MinBlockDots		=ui.EditMinBlockDots	->value();
	ALib->MaxBlockDots		=ui.EditMaxBlockDots	->value();
	ALib->LimitBlockSize	=ui.EditLimitBlockSize	->value();
	ALib->SpaceToOutline	=ui.EditSpaceToOutline	->value();
	ALib->GenerationMode.PlusHalfDotIsolation	=ui.checkBPlusHalfDotIsolation	->isChecked();
	ALib->NoiseSize			=ui.EditNoiseSize		->value();
	ALib->NoiseSizePinHole	=ui.EditNoiseSizePinHole->value();
	ALib->Priority			=ui.EditPriority		->value();
	ALib->OutlineGeneration	=ui.EditOutlineGeneration->value();
}


void PropertyBlockForm::on_ButtonLibSave_clicked()
{
	if(TempLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
										, LangSolver.GetString(PropertyBlockForm_LS,LID_39)/*"Warning"*/
										, LangSolver.GetString(PropertyBlockForm_LS,LID_40)/*"No Library Name"*/
										, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	BlockBase	*BBase=GetBlockBase();
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

void PropertyBlockForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		BlockBase	*BBase=GetBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(TempLib->GetAdaptedPickLayers());
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL
									, LangSolver.GetString(PropertyBlockForm_LS,LID_41)/*"Library error"*/
									, LangSolver.GetString(PropertyBlockForm_LS,LID_42)/*"Not loaded this library record"*/);
			}
		}
	}
}
void PropertyBlockForm::SetLayersFromLib(IntList &LayerList)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"BlockImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->SetActiveLayerList(LayerList);
		}
	}
}

void PropertyBlockForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		BlockBase	*BBase=GetBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(TempLib->GetAdaptedPickLayers());
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL
								, LangSolver.GetString(PropertyBlockForm_LS,LID_43)/*"Library error"*/
								, LangSolver.GetString(PropertyBlockForm_LS,LID_44)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyBlockForm::on_tableWidgetLibList_doubleClicked(QModelIndex)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyBlockForm::on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex Index)
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

void	PropertyBlockForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	BlockBase	*BBase=GetBlockBase();
	if(BBase!=NULL){
		CmdCreateTempBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;
		BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(SLib->GetLibrary());
		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());
			CmdLoadBlockLibraryPacket	Packet(GetLayersBase());
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


void PropertyBlockForm::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyBlockForm_LS,LID_0)/*"Pickup Test"*/,7);

	GetLibraryFromWindow(*TempLib);

	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"BlockImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibPoint	=TempLib;
		Cmd.LayerList	=LayerList;
		Cmd.SendOnly(GlobalPage,0);
	}

	GetLayersBase()->CloseProcessingForm();
}


void PropertyBlockForm::on_ButtonGenerateLibs_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate Blocks automatically");

	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"BlockImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}
	
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyBlockForm_LS,LID_1)/*"Generating items"*/,false,SelectedLibList.GetCount()*(7+7));
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGenerateBlocks	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.LayerList	=LayerList;
		Cmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}


void PropertyBlockForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.Send(NULL,GlobalPage,0);
	}
}

void PropertyBlockForm::on_toolButtonLibrary_clicked()
{
	if(ui.toolButtonLibrary->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(0);
		if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReqSetButtonMode	RCmd(GetLayersBase() ,sRoot,sName ,GlobalPage);
				RCmd.Mode=GUICmdReqSetButtonMode::_LibraryTest;
				RCmd.InstForm=GetName();
				RCmd.Send(NULL,GlobalPage,0);
			}
		}
	}
	GetLayersBase()->SetStatusModes(this,/**/"LibraryMode");

	BroadcastShowInEdit();
}

void PropertyBlockForm::on_toolButtonCreateBlock_clicked()
{
	if(ui.toolButtonCreateBlock->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(1);
		if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReqSetButtonMode	RCmd(GetLayersBase() ,sRoot,sName ,GlobalPage);
				RCmd.Mode=GUICmdReqSetButtonMode::_CreateBlock;
				RCmd.InstForm=GetName();
				RCmd.Send(NULL,GlobalPage,0);
			}
		}
		ShowBlockInfoList();
	}
	GetLayersBase()->SetStatusModes(this,/**/"BlockMode");
	BroadcastShowInEdit();
}


void PropertyBlockForm::ShowBlockInfoList(void)
{
	BlockInfos.RemoveAll();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqBlockInfoList	CmdReq (GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendBlockInfoList	CmdSend(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.Send(GlobalPage,0,CmdSend);

		for(BlockInfoList *a=CmdSend.BlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
			BlockInfoList *b;
			for(b=BlockInfos.GetFirst();b!=NULL;b=b->GetNext()){
				if(a->LibID==b->LibID && b->Page==page){
					for(int layer=0;layer<GetLayerNumb(page);layer++){
						IntClass	*d=b->BlockCount.GetItem(layer);
						IntClass	*s=a->BlockCount.GetItem(layer);
						d->SetValue(d->GetValue()+s->GetValue());
					}
					break;
				}
			}
			if(b==NULL){
				b=new BlockInfoList();
				b->LibID=a->LibID;
				b->Page	=page;
				for(int layer=0;layer<GetLayerNumb(page);layer++){
					IntClass	*s=a->BlockCount.GetItem(layer);
					b->BlockCount.Add(s->GetValue());
				}
				BlockInfos.AppendList(b);
			}
		}
	}
	int	N=BlockInfos.GetNumber();
	ui.tableWidgetBlockInfo->setRowCount(N);
	AlgorithmLibraryListContainer LibIDList;
	for(BlockInfoList *a=BlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList	*k=new AlgorithmLibraryList();
		k->SetLibID(a->GetLibID());
		LibIDList.AppendList(k);
	}
	BlockBase	*BBase=GetBlockBase();
	GetLayersBase()->GetDatabaseLoader()->G_GetLibraryNames(*GetLayersBase()->GetDataBase(),BBase->GetLibraryContainer(),LibIDList);
	int	row=0;
	for(BlockInfoList *a=BlockInfos.GetFirst();a!=NULL;a=a->GetNext(),row++){
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
			W->setFlags(Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->LibID));

		W=ui.tableWidgetBlockInfo->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetBlockInfo->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsEnabled);
		}
		W->setText(LibName);

		W=ui.tableWidgetBlockInfo->item ( row, 2);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetBlockInfo->setItem ( row, 2,W);
			W->setFlags(Qt::ItemIsEnabled);
		}
		int	TotalCount=0;
		for(IntClass *h=a->BlockCount.GetFirst();h!=NULL;h=h->GetNext()){
			TotalCount+=h->GetValue();
		}
		W->setText(QString::number(TotalCount));

		for(int layer=0;layer<GetLayerNumb(a->Page);layer++){
			W=ui.tableWidgetBlockInfo->item ( row, 3+layer);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetBlockInfo->setItem ( row, 3+layer,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			IntClass *h=a->BlockCount.GetItem(layer);
			W->setText(QString::number(h->GetValue()));
		}
	}
}

void PropertyBlockForm::on_tableWidgetBlockInfo_cellClicked(int,int)
{
	BlockBase	*BBase=GetBlockBase();

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReleaseSelectImagePanel	Cmd(GetLayersBase(),sRoot,sName ,GlobalPage);
		Cmd.AlgoRoot=/**/"Basic";
		Cmd.AlgoName=/**/"BlockInspection";
		Cmd.SendOnly(GlobalPage,0);
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectByLibs	Cmd(BBase,sRoot,sName,GlobalPage);
		for(int row=0;row<ui.tableWidgetBlockInfo->rowCount();row++){
			BlockInfoList *a=BlockInfos.GetItem(row);
			for(int layer=0;layer<GetLayerNumb(page);layer++){
				int	c=layer+3;
				QTableWidgetItem *item=ui.tableWidgetBlockInfo->item(row,c);
				if(item==NULL)
					continue;
				if(item->isSelected()==true){
					SelectLibList	*v=new SelectLibList();
					v->LibType	=BBase->GetLibType();
					v->LibID	=a->LibID;
					v->Layer=layer;
					Cmd.SelectedList.AppendList(v);
				}
			}
		}
		Cmd.SendOnly(GlobalPage,1);
	}
	BroadcastShowInEdit();
}

void PropertyBlockForm::on_pushButtonEditLibrary_clicked()
{
	EditBlockLibrary	D(GetLayersBase(),this);
	D.exec();

	ShowLibList();
	if(TempLib!=NULL){
		CmdLoadBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		BlockBase	*BBase=GetBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
		}
	}
}

void PropertyBlockForm::on_pushButtonEditLibFolder_clicked()
{
	BlockBase	*BBase=GetBlockBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyBlockForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui.labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void PropertyBlockForm::on_pushButtonSetFrom_clicked()
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

void PropertyBlockForm::on_pushButtonGetBack_clicked()
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


void PropertyBlockForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyBlockForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void	PropertyBlockForm::ClearLibList(void)
{
	on_pushButtonGetBackAll_clicked();
}

void	PropertyBlockForm::SetLib(int LibID)
{
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==LibID)
			return;
	}
	BlockBase	*BBase=GetBlockBase();
	if(BBase!=NULL){
		CmdGetLibName	Packet(GetLayersBase());
		Packet.LibID=LibID;
		BBase->TransmitDirectly(&Packet);

		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,LibID,Packet.LibName));
		ShowSelectedLibList();
	}
}

void	PropertyBlockForm::GenerateBlocks(void)
{
	on_ButtonGenerateLibs_clicked();
}
void PropertyBlockForm::on_pushButtonShrink_clicked()
{
	int	ShrinkDot=ui.spinBoxShrink->value();
	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"BlockImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Shrink");
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqShrinkArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.ShrinkDot	=ShrinkDot;
		Cmd.LayerList	=LayerList;
		Cmd.SendOnly(GlobalPage,0);
	}
}

void PropertyBlockForm::on_pushButtonShrinkHalf_clicked()
{
	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"BlockImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Shrink half");
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqShrinkHalf	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LayerList	=LayerList;
		Cmd.SendOnly(GlobalPage,0);
	}
}

void PropertyBlockForm::on_pushButtonExpandHalf_clicked()
{
	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"BlockImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Expand half");
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqExpandHalf	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LayerList	=LayerList;
		Cmd.SendOnly(GlobalPage,0);
	}
}
	
bool	PropertyBlockForm::CommandSetOutlineInLib(int LibID,int OutlineDot)
{
	BlockBase	*BBase=GetBlockBase();
	AlgorithmLibraryLevelContainer	*Lib=NULL;
	if(BBase!=NULL){
		CmdCreateTempBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		Lib=Packet.Point;
	}
	if(Lib!=NULL){
		Lib->SetLibID(LibID);
		CmdLoadBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=Lib;
		BBase->TransmitDirectly(&Packet);
		BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(Lib->GetLibrary());
		ALib->SpaceToOutline=OutlineDot;

		CmdUpdateBlockLibraryPacket	UPacket(GetLayersBase());
		UPacket.Point=TempLib;
		BBase->TransmitDirectly(&UPacket);

		return true;
	}
	return false;
}
	
bool	PropertyBlockForm::CommandSetNGSizeInBlock(int LibID,int BlockType,int NGSize)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetNGSizeInBlock	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibID		=LibID;
		Cmd.BlockType	=BlockType;
		Cmd.NGSize		=NGSize;
		Cmd.SendOnly(GlobalPage,0);
	}
	return true;
}
	
bool	PropertyBlockForm::CommandSetSearchDotInBlock(int LibID,int SearchDot)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetSearchDotInBlock	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibID		=LibID;
		Cmd.SearchDot	=SearchDot;
		Cmd.SendOnly(GlobalPage,0);
	}
	return true;
}
void PropertyBlockForm::on_toolButtonArea_clicked()
{
    BroadcastShowInEdit();
}

void PropertyBlockForm::on_toolButtonEdge_clicked()
{
    BroadcastShowInEdit();
}

void PropertyBlockForm::on_toolButtonInside_clicked()
{
    BroadcastShowInEdit();
}

void PropertyBlockForm::on_toolButtonDirUp_clicked()
{
    BroadcastShowInEdit();
}

void PropertyBlockForm::on_toolButtonDirRight_clicked()
{
    BroadcastShowInEdit();
}

void PropertyBlockForm::on_toolButtonDirLeft_clicked()
{
    BroadcastShowInEdit();
}

void PropertyBlockForm::on_toolButtonDirBottom_clicked()
{
   BroadcastShowInEdit();
}

void PropertyBlockForm::on_toolButtonSkipSearch_clicked()
{
    BroadcastShowInEdit();
}

void PropertyBlockForm::on_toolButtonBeforeShrink_clicked()
{
	BroadcastShowInEdit();
}

void PropertyBlockForm::on_toolButtonOmitMatchLineArea_clicked()
{
    BroadcastShowInEdit();
}
