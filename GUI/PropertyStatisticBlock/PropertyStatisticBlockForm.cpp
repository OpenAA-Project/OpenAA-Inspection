#include "EditStatisticBlockLibraryResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyStatisticBlock\PropertyStatisticBlockForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyStatisticBlockForm.h"
#include "XDLLOnly.h"
//#include "SelectBlockLibraryForm.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyStatisticBlockPacket.h"
#include "StatisticBrightHistogramForm.h"
//#include "CreateManualStatisticBlockForm.h"
#include "EditStatisticBlockLibrary.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XGUIPacketGeneral.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyStatisticBlockForm::PropertyStatisticBlockForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LibFolderID=-1;

	StatisticBlockBase	*BBase=GetStatisticBlockBase();
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
	HeaderLabel.append(LangSolver.GetString(PropertyStatisticBlockForm_LS,LID_6)/*"ID"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyStatisticBlockForm_LS, LID_7)/*"ライブラリ名"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyStatisticBlockForm_LS,LID_8)/*"ブロック総数"*/);
	for(int layer=0;layer<GetLayerNumb(Page);layer++){
		ui.tableWidgetBlockInfo->setColumnWidth (3+layer, 50);
		HeaderLabel.append(GetParamGlobal()->GetLayerName(layer));
	}
	ui.tableWidgetBlockInfo->setHorizontalHeaderLabels(HeaderLabel);

	TabBarStatisticBlockOnMouse.setParent(ui.frameBlockInfoOnMouse);
	TabBarStatisticBlockOnMouse.setGeometry(ui.frame->geometry().left(),ui.frame->geometry().top()-30,ui.frame->geometry().width(),30);
	connect(&TabBarStatisticBlockOnMouse,SIGNAL(currentChanged(int)),this,SLOT(TabBarBlockOnMouseChanged(int)));

	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		BInfo[i].StatisticBlockInfoOnMouse=NULL;
	}

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempStatisticBlockLibraryPacket	Packet(GetLayersBase());
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

	if(BBase!=NULL)
		new GUICmdSelectByLibs				(BBase,sRoot,sName);
}

PropertyStatisticBlockForm::~PropertyStatisticBlockForm()
{
	if(TempLib!=NULL)
		delete	TempLib;
}

void	PropertyStatisticBlockForm::ShowTab(void)
{
	int	r=TabBarStatisticBlockOnMouse.currentIndex();
	while(TabBarStatisticBlockOnMouse.count()!=0){
		TabBarStatisticBlockOnMouse.removeTab(0);
	}
	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		if(BInfo[i].StatisticBlockInfoOnMouse!=NULL){
			TabBarStatisticBlockOnMouse.addTab (QString::number(BInfo[i].Page)
										+QString(/**/"-")
										+GetParamGlobal()->GetLayerName(BInfo[i].Layer));
		}
	}
	if(0<=r && TabBarStatisticBlockOnMouse.count()>r){
		TabBarStatisticBlockOnMouse.setCurrentIndex(r);
	}
}

void	PropertyStatisticBlockForm::TabBarBlockOnMouseChanged(int index)
{
	if(BInfo[index].StatisticBlockInfoOnMouse!=NULL){
		ui.EditLibIDnBlock		->setText(QString::number(BInfo[index].StatisticBlockInfoOnMouse->GetLibID()));
		StatisticBlockBase	*BBase=GetStatisticBlockBase();
		CmdGetLibName	Cmd(GetLayersBase());
		Cmd.LibID	=BInfo[index].StatisticBlockInfoOnMouse->GetLibID();
		BBase->TransmitDirectly(&Cmd);
		ui.EditLibNameInBlock	->setText(Cmd.LibName);

		ui.EditBrightWidthL		->setText(QString::number(BInfo[index].StatisticBlockInfoOnMouse->GetThresholdR()->BrightWidthL	));
		ui.EditBrightWidthH		->setText(QString::number(BInfo[index].StatisticBlockInfoOnMouse->GetThresholdR()->BrightWidthH	));
		ui.EditOKDotL			->setValue(BInfo[index].StatisticBlockInfoOnMouse->GetThresholdR()->OKDotL		);
		ui.EditOKDotH			->setValue(BInfo[index].StatisticBlockInfoOnMouse->GetThresholdR()->OKDotH		);

		ui.EditAdjustBlack		->setValue(BInfo[index].StatisticBlockInfoOnMouse->GetThresholdR()->AdjustWhite	);
		ui.EditAdjustWhite		->setValue(BInfo[index].StatisticBlockInfoOnMouse->GetThresholdR()->AdjustBlack	);

		ui.checkBModeWhiteMask	->setChecked(BInfo[index].StatisticBlockInfoOnMouse->GetThresholdR()->PointMove.ModeWhiteMask	);
		ui.checkBModeBlackMask	->setChecked(BInfo[index].StatisticBlockInfoOnMouse->GetThresholdR()->PointMove.ModeBlackMask	);
	}
	else{
		ui.EditLibIDnBlock		->clear();
		ui.EditLibNameInBlock	->clear();

		ui.EditBrightWidthL	->clear();
		ui.EditBrightWidthH	->clear();
		ui.EditOKDotL			->clear();
		ui.EditOKDotH			->clear();

		ui.EditAdjustBlack		->clear();
		ui.EditAdjustWhite		->clear();

		ui.checkBModeWhiteMask		->setChecked(false);
		ui.checkBModeBlackMask		->setChecked(false);
	}
}

StatisticBlockBase	*PropertyStatisticBlockForm::GetStatisticBlockBase(void)
{
	return (StatisticBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticBlock");
}

void	PropertyStatisticBlockForm::ShowLibList(void)
{
	ui.tableWidgetLibList->setRowCount(0);
	StatisticBlockBase	*BBase=GetStatisticBlockBase();
	if(BBase!=NULL){
		CmdGetStatisticBlockLibraryListPacket	Packet(GetLayersBase());
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
void	PropertyStatisticBlockForm::ShowInEdit(void)
{
	ShowBlockInfoList();
}
void	PropertyStatisticBlockForm::StartPage(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui.labelLibFolderName->setText(FolderName);
	}
	ShowBlockInfoList();
}
void	PropertyStatisticBlockForm::BuildForShow(void)
{
	StartPage();
}
void	PropertyStatisticBlockForm::TransmitDirectly(GUIDirectMessage *packet)
{
	StatisticBlockBase	*BBase=GetStatisticBlockBase();
	CmdStatisticBlockDrawModePacket	*BDrawModePacket=dynamic_cast<CmdStatisticBlockDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		if(ui.toolButtonLibrary->isChecked()==true)
			BDrawModePacket->Mode=CmdStatisticBlockDrawModePacket::_LibTest;
		else if(ui.toolButtonCreateBlock->isChecked()==true)
			BDrawModePacket->Mode=CmdStatisticBlockDrawModePacket::_CreatedBlock;
		return;
	}
	CmdStatisticBlockDrawEnd	*BlockDEnd=dynamic_cast<CmdStatisticBlockDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		if(ui.toolButtonLibrary->isChecked()==true){
			if(TempLib->GetLibID()>=0){
				StatisticBlockLibrary	*ALib=dynamic_cast<StatisticBlockLibrary *>(TempLib->GetLibrary());
				StatisticBrightHistogramForm	D(BlockDEnd->Area,BlockDEnd->ImagePanelPoint
												  ,ALib->PickupL,ALib->PickupH,this);
				D.Reflect(ALib->PickupL,ALib->PickupH);
				if(D.exec()==(int)true){
					ALib->PickupL	=D.PickupL;
					ALib->PickupH	=D.PickupH;
				}
			}
		}
		else if(ui.toolButtonCreateBlock->isChecked()==true){
			/*
			CreateManualBlockForm	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->d;
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=BlockDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						GUICmdSendAddManualBlock	Cmd(GetLayersBase(),sRoot,sName,page);
						Cmd.Area=A;
						CmdCreateByteArrayFromBlockItemPacket	BCmd;
						BCmd.Point=D.BItem;
						BBase->TransmitDirectly(&BCmd);
						Cmd.BItem=BCmd.Buff;
						Cmd.LayerList=BlockDEnd->LayerList;
						Cmd.Send(NULL,page,0);
					}
				}
				ShowBlockInfoList();
			}
			*/
		}
	}
	CmdStatisticBlockShowAttrPacket	*ShowAttr=dynamic_cast<CmdStatisticBlockShowAttrPacket *>(packet);
	if(ShowAttr!=NULL){

	}
	CmdExecuteMouseLDown	*CmdExecuteMouseLDownVar=dynamic_cast<CmdExecuteMouseLDown *>(packet);
	if(CmdExecuteMouseLDownVar!=NULL){
		for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
			//if(BInfo[i].BlockInfoOnMouse!=NULL)
			//	delete	BInfo[i].BlockInfoOnMouse;
			BInfo[i].StatisticBlockInfoOnMouse=NULL;
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
					GUICmdReqStatisticBlockFromList	ReqCmd(GetLayersBase(),sRoot,sName,page);
					GUICmdAckStatisticBlockFromList	AckCmd(GetLayersBase(),sRoot,sName,page);
					ReqCmd.CurrentItem=Items;
					ReqCmd.Send(page,0,AckCmd);
					for(int i=0;i<sizeof(AckCmd.StatisticBlockInfoOnMouse)/sizeof(AckCmd.StatisticBlockInfoOnMouse[0]);i++){
						if(AckCmd.StatisticBlockInfoOnMouse[i]!=NULL){
							BInfo[N].StatisticBlockInfoOnMouse=AckCmd.StatisticBlockInfoOnMouse[i];
							AckCmd.StatisticBlockInfoOnMouse[i]=NULL;
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

void	PropertyStatisticBlockForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	StatisticBlockBase	*BBase=GetStatisticBlockBase();
	if(BBase!=NULL){
		CmdCreateTempStatisticBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;
		StatisticBlockLibrary	*ALib=dynamic_cast<StatisticBlockLibrary *>(SLib->GetLibrary());
		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadStatisticBlockLibraryPacket	Packet(GetLayersBase());
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


void	PropertyStatisticBlockForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	StatisticBlockLibrary	*ALib=dynamic_cast<StatisticBlockLibrary *>(data.GetLibrary());
	ui.EditSpaceToOutline	->setValue(ALib->SpaceToOutline);
	ui.EditNoiseSize		->setValue(ALib->NoiseSize);
	ui.EditPriority			->setValue(ALib->Priority);
}

void	PropertyStatisticBlockForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	StatisticBlockLibrary	*ALib=dynamic_cast<StatisticBlockLibrary *>(data.GetLibrary());
	ALib->SpaceToOutline	=ui.EditSpaceToOutline	->value();
	ALib->NoiseSize		=ui.EditNoiseSize		->value();
	ALib->Priority		=ui.EditPriority		->value();
}

void PropertyStatisticBlockForm::ShowBlockInfoList(void)
{
	StatisticBlockInfos.RemoveAll();

	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqStatisticBlockInfoList		CmdReq (GetLayersBase(),sRoot,sName,page);
		GUICmdSendStatisticBlockInfoList	CmdSend(GetLayersBase(),sRoot,sName,page);
		CmdReq.Send(page,0,CmdSend);
		for(StatisticBlockInfoList *a=CmdSend.StatisticBlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
			StatisticBlockInfoList *b;
			for(b=StatisticBlockInfos.GetFirst();b!=NULL;b=b->GetNext()){
				if(a->LibID==b->LibID){
					for(int layer=0;layer<GetLayerNumb(page);layer++){
						IntClass	*d=b->StatisticBlockCount.GetItem(layer);
						IntClass	*s=a->StatisticBlockCount.GetItem(layer);
						d->SetValue(d->GetValue()+s->GetValue());
					}
					break;
				}
			}
			if(b==NULL){
				b=new StatisticBlockInfoList();
				b->LibID=a->LibID;
				for(int layer=0;layer<GetLayerNumb(page);layer++){
					IntClass	*s=a->StatisticBlockCount.GetItem(layer);
					b->StatisticBlockCount.Add(s->GetValue());
				}
				StatisticBlockInfos.AppendList(b);
			}
		}
	}
	int	N=StatisticBlockInfos.GetNumber();
	ui.tableWidgetBlockInfo->setRowCount(N);
	AlgorithmLibraryListContainer LibIDList;
	for(StatisticBlockInfoList *a=StatisticBlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList	*k=new AlgorithmLibraryList();
		k->SetLibID(a->GetLibID());
		LibIDList.AppendList(k);
	}
	StatisticBlockBase	*BBase=GetStatisticBlockBase();
	GetLayersBase()->GetDatabaseLoader()->G_GetLibraryNames(*GetLayersBase()->GetDataBase(),BBase->GetLibraryContainer(),LibIDList);
	int	row=0;
	for(StatisticBlockInfoList *a=StatisticBlockInfos.GetFirst();a!=NULL;a=a->GetNext(),row++){
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
		for(IntClass *h=a->StatisticBlockCount.GetFirst();h!=NULL;h=h->GetNext()){
			TotalCount+=h->GetValue();
		}
		W->setText(QString::number(TotalCount));

		for(int layer=0;layer<GetLayerNumb(0);layer++){
			W=ui.tableWidgetBlockInfo->item ( row, 3+layer);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetBlockInfo->setItem ( row, 3+layer,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			IntClass *h=a->StatisticBlockCount.GetItem(layer);
			W->setText(QString::number(h->GetValue()));
		}
	}
}

void PropertyStatisticBlockForm::on_pushButtonEditLibrary_clicked()
{
	EditStatisticBlockLibrary	D(GetLayersBase(),this);
	D.exec();
	//on_ButtonLibSave_clicked();
}

void PropertyStatisticBlockForm::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyStatisticBlockForm_LS,LID_9)/*"Pickup Test"*/);

	GetLibraryFromWindow(*TempLib);

	CmdReqImageLayer	DrawMode(GetLayersBase(),GetLayerNumb(0));
	GUIFormBase	*GProp=GetImageControlToolsPointer();
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.LibPoint	=TempLib;
		Cmd.LayerList	=DrawMode.LayerList;
		Cmd.SendOnly(page,0);
	}

	GetLayersBase()->CloseProcessingForm();
}
GUIFormBase	*PropertyStatisticBlockForm::GetImageControlToolsPointer(void)
{
	GUIFormBase *RetGUI[1000];
	int	N=GetLayersBase()->EnumGUIInst(/**/"Button" ,/**/"ImageControlTools" ,RetGUI ,sizeof(RetGUI)/sizeof(RetGUI[0]));

	GUIFormBase	*ImagePanel=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"StatisticBlockImagePanel" ,/**/"");
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

void PropertyStatisticBlockForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.Send(NULL,page,0);
	}
}

void PropertyStatisticBlockForm::on_ButtonGenerateLibs_clicked()
{
	if(TempLib==NULL)
		return;

	CmdReqImageLayer	DrawMode(GetLayersBase(),GetLayerNumb(0));
	GUIFormBase	*GProp=GetImageControlToolsPointer();
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyStatisticBlockForm_LS,LID_10)/*"Generating items"*/
										,DrawMode.LayerList.GetCount()*GetLayersBase()->GetPageNumb()*10);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdGenerateStatisticBlocks	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.LayerList	=DrawMode.LayerList;
		Cmd.SendOnly(page,0);
	}
	GetLayersBase()->CloseProcessingForm();
}

void PropertyStatisticBlockForm::on_ButtonLibSave_clicked()
{
	if(TempLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
															, LangSolver.GetString(PropertyStatisticBlockForm_LS,LID_11)/*"Warning"*/
															, LangSolver.GetString(PropertyStatisticBlockForm_LS,LID_12)/*"No Library Name"*/
															, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateStatisticBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	StatisticBlockBase	*BBase=GetStatisticBlockBase();
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

void PropertyStatisticBlockForm::on_toolButtonLibrary_clicked()
{
	if(ui.toolButtonLibrary->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(0);
	}
	BroadcastShowInEdit();
}

void PropertyStatisticBlockForm::on_toolButtonCreateBlock_clicked()
{
	if(ui.toolButtonCreateBlock->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(1);
		ShowBlockInfoList();
	}
	BroadcastShowInEdit();
}

void PropertyStatisticBlockForm::on_pushButtonEditLibFolder_clicked()
{
	StatisticBlockBase	*BBase=GetStatisticBlockBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyStatisticBlockForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui.labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}


void PropertyStatisticBlockForm::on_pushButtonSetFrom_clicked()
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

void PropertyStatisticBlockForm::on_pushButtonGetBack_clicked()
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

void PropertyStatisticBlockForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadStatisticBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		StatisticBlockBase	*BBase=GetStatisticBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
		}
	}
}

void PropertyStatisticBlockForm::on_tableWidgetGeneratedLibList_cellDoubleClicked(int,int)
{

}

void PropertyStatisticBlockForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadStatisticBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		StatisticBlockBase	*BBase=GetStatisticBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
		}
	}

}

void PropertyStatisticBlockForm::on_tableWidgetLibList_cellDoubleClicked(int,int)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyStatisticBlockForm::on_tableWidgetGeneratedLibList_itemDoubleClicked(QTableWidgetItem*)
{
	on_pushButtonGetBack_clicked();
}

void PropertyStatisticBlockForm::on_tableWidgetBlockInfo_cellClicked(int,int)
{
	StatisticBlockBase	*BBase=GetStatisticBlockBase();

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdReleaseSelectImagePanel	Cmd(GetLayersBase(),sRoot,sName ,page);
		Cmd.AlgoRoot=/**/"Basic";
		Cmd.AlgoName=/**/"StatisticBlock";
		Cmd.SendOnly(page,0);
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdSelectByLibs	Cmd(BBase,sRoot,sName,page);
		for(int row=0;row<ui.tableWidgetBlockInfo->rowCount();row++){
			StatisticBlockInfoList *a=StatisticBlockInfos.GetItem(row);
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
		Cmd.SendOnly(page,1);
	}
	BroadcastShowInEdit();
}