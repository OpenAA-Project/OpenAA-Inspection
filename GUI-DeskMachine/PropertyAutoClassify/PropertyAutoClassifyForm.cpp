/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBlock\PropertyBlockForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyAutoClassifyForm.h"
#include "XDLLOnly.h"
#include "EditAutoClassifyLibrary.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "SetAreaColorDialog.h"
#include "XGUIPacketGeneral.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

extern	char	*sRoot;
extern	char	*sName;

PropertyAutoClassifyForm::PropertyAutoClassifyForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);

	LibFolderID=-1;

	AutoClassifyBase	*BBase=GetAutoClassifyBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);
	ui.tableWidgetGeneratedLibList->setColumnWidth (0, 30);
	ui.tableWidgetGeneratedLibList->setColumnWidth (1, 80);	

	QStringList	HeaderLabel;
	HeaderLabel.append(QString("ID"));
	HeaderLabel.append(QString("ライブラリ名"));
	HeaderLabel.append(QString("エリア総数"));
	ui.tableWidgetBlockInfo->setHorizontalHeaderLabels(HeaderLabel);

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAutoClassifyLibraryPacket	Packet(Base);
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
}

PropertyAutoClassifyForm::~PropertyAutoClassifyForm()
{
	if(TempLib!=NULL)
		delete	TempLib;
}

AutoClassifyBase	*PropertyAutoClassifyForm::GetAutoClassifyBase(void)
{
	return (AutoClassifyBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoClassify");
}

void	PropertyAutoClassifyForm::ShowLibList(void)
{
	ui.tableWidgetLibList->setRowCount(0);
	AutoClassifyBase	*BBase=GetAutoClassifyBase();
	if(BBase!=NULL){
		CmdGetAutoClassifyLibraryListPacket	Packet(GetLayersBase());
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
void	PropertyAutoClassifyForm::ShowInEdit(void)
{
	ShowAreaInfoList();
}
void	PropertyAutoClassifyForm::StartPage(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui.labelLibFolderName->setText(FolderName);
	}
	on_toolButtonAreaMode_clicked();
}

void	PropertyAutoClassifyForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AutoClassifyBase	*BBase=GetAutoClassifyBase();
	CmdAutoClassifyDrawModePacket	*BDrawModePacket=dynamic_cast<CmdAutoClassifyDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		if(ui.toolButtonAreaMode->isChecked()==false)
			BDrawModePacket->Mode=CmdAutoClassifyDrawModePacket::_LibTest;
		else{
			BDrawModePacket->Mode=CmdAutoClassifyDrawModePacket::_CreatedArea;
		}
		return;
	}
	CmdAutoClassifyDrawEnd	*BlockDEnd=dynamic_cast<CmdAutoClassifyDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		if(ui.toolButtonAreaMode->isChecked()==false){
			if(TempLib->GetLibID()>=0){
				//GlobalPickupArea+=BlockDEnd->Area;
				AutoClassifyLibrary	*ALib=dynamic_cast<AutoClassifyLibrary *>(TempLib->GetLibrary());
				SetAreaColorDialog	D(ALib->TeacherColor ,BlockDEnd->Area
									,GetLayersBase(),this);
				if(D.exec()==(int)true){
				}
			}
		}
		/*
		else{
			CreateManualBlockForm	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
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
						Cmd.SendOnly(page,0);
					}
				}
				ShowBlockInfoList();
			}
		}
		*/
	}
	/*
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

			ListLayerAndIDPack	Items;
				if(N>=sizeof(BInfo)/sizeof(BInfo[0]))
					break;
				for(ListPageLayerID *a=CmdExecuteMouseLDownVar->CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->Page==page && a->Layer==layer){
						Items.AppendList(new ListLayerAndID(a->Layer,a->ID));
					}
				}
				if(Items.GetNumber()!=NULL){
					GUICmdReqBlockFromList	ReqCmd(GetLayersBase(),sRoot,sName,page);
					GUICmdAckBlockFromList	AckCmd(GetLayersBase(),sRoot,sName,page);
					ReqCmd.CurrentItem=Items;
					ReqCmd.Send(page,0,AckCmd);
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
	*/

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
			ui.toolButtonAreaMode->setChecked(false);
		}
		if(CmdReqSetButtonModeVar->Mode==GUICmdReqSetButtonMode::_CreateBlock){
			ui.toolButtonAreaMode->setChecked(true);
		}
	}
}


void	PropertyAutoClassifyForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	AutoClassifyLibrary	*ALib=dynamic_cast<AutoClassifyLibrary *>(data.GetLibrary());
	ui.EditSpaceToOutline	->setValue(ALib->SpaceToOutline);
	ui.EditNoiseSize		->setValue(ALib->NoiseSize);
	ui.EditPriority			->setValue(ALib->Priority);
}

void	PropertyAutoClassifyForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	AutoClassifyLibrary	*ALib=dynamic_cast<AutoClassifyLibrary *>(data.GetLibrary());
	ALib->SpaceToOutline=ui.EditSpaceToOutline	->value();
	ALib->NoiseSize		=ui.EditNoiseSize		->value();
	ALib->Priority		=ui.EditPriority		->value();
}


void PropertyAutoClassifyForm::on_ButtonLibSave_clicked()
{
	if(TempLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, "Warning"
																	, "No Library Name"
																	, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateAutoClassifyLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AutoClassifyBase	*BBase=GetAutoClassifyBase();
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

void PropertyAutoClassifyForm::on_tableWidgetLibList_doubleClicked(QModelIndex)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyAutoClassifyForm::on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex)
{
	on_pushButtonGetBack_clicked();
}

void PropertyAutoClassifyForm::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm("Pickup test");
	GetLibraryFromWindow(*TempLib);

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.LibPoint	=TempLib;
		Cmd.SendOnly(page,0);
	}

	GetLayersBase()->CloseProcessingForm();
}

void PropertyAutoClassifyForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.Send(NULL,page,0);
	}
}

void PropertyAutoClassifyForm::on_ButtonGenerateLibs_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Generating items",GetLayersBase()->GetPageNumb()*10);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdGenerateAreas	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyAutoClassifyForm::on_pushButtonSetFrom_clicked()
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

void PropertyAutoClassifyForm::on_pushButtonGetBack_clicked()
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

void PropertyAutoClassifyForm::on_pushButtonEditLibFolder_clicked()
{
	AutoClassifyBase	*BBase=GetAutoClassifyBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ui.labelLibFolderName->setText(RetSelectedFolderName);
		LibFolderID=RetSelectedLibFolderID;
		ShowLibList();
	}
}

void PropertyAutoClassifyForm::on_pushButtonEditLibrary_clicked()
{
	EditAutoClassifyLibrary	D(GetLayersBase(),this);
	D.exec();
	//on_ButtonLibSave_clicked();
}

void PropertyAutoClassifyForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyAutoClassifyForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyAutoClassifyForm::on_tableWidgetBlockInfo_clicked(const QModelIndex &)
{
	AutoClassifyBase	*BBase=GetAutoClassifyBase();

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdReleaseSelectImagePanel	Cmd(GetLayersBase(),sRoot,sName ,page);
		Cmd.AlgoRoot=/**/"Basic";
		Cmd.AlgoName=/**/"AutoClassify";
		Cmd.SendOnly(page,0);
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdSelectByLibs	Cmd(BBase,sRoot,sName,page);
		for(int row=0;row<ui.tableWidgetBlockInfo->rowCount();row++){
			AreaInfoList *a=AreaInfos.GetItem(row);

			int	c=3;
			QTableWidgetItem *item=ui.tableWidgetBlockInfo->item(row,c);
			if(item==NULL)
				continue;
			if(item->isSelected()==true){
				SelectLibList	*v=new SelectLibList();
				v->LibType	=BBase->GetLibType();
				v->LibID	=a->LibID;
				Cmd.SelectedList.AppendList(v);
			}
		}
		Cmd.SendOnly(page,1);
	}
	BroadcastShowInEdit();
}

void PropertyAutoClassifyForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadAutoClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoClassifyBase	*BBase=GetAutoClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	,"Library error"
											, "Not loaded this library record");
			}
		}
	}

}

void PropertyAutoClassifyForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadAutoClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoClassifyBase	*BBase=GetAutoClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL, "Library error"
											, "Not loaded this library record");
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

void	PropertyAutoClassifyForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	AutoClassifyBase	*BBase=GetAutoClassifyBase();
	if(BBase!=NULL){
		CmdCreateTempAutoClassifyLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());
			CmdLoadAutoClassifyLibraryPacket	Packet(GetLayersBase());
			Packet.Point=SLib;
			BBase->TransmitDirectly(&Packet);
			AutoClassifyLibrary	*ALib=dynamic_cast<AutoClassifyLibrary *>(SLib->GetLibrary());
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
void PropertyAutoClassifyForm::ShowAreaInfoList(void)
{
	AreaInfos.RemoveAll();

	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqAreaInfoList	CmdReq (GetLayersBase(),sRoot,sName,page);
		GUICmdSendAreaInfoList	CmdSend(GetLayersBase(),sRoot,sName,page);
		CmdReq.Send(GetLayersBase()->GetGlobalPageFromLocal(page),0,CmdSend);
		for(AreaInfoList *a=CmdSend.AreaInfos.GetFirst();a!=NULL;a=a->GetNext()){
			AreaInfoList *b;
			for(b=AreaInfos.GetFirst();b!=NULL;b=b->GetNext()){
				if(a->LibID==b->LibID){
					b->AreaCount +=a->AreaCount;
				}
			}
			if(b==NULL){
				b=new AreaInfoList();
				b->LibID=a->LibID;
				b->AreaCount=a->AreaCount;
				AreaInfos.AppendList(b);
			}
		}
	}
	int	N=AreaInfos.GetNumber();
	ui.tableWidgetBlockInfo->setRowCount(N);
	AlgorithmLibraryListContainer LibIDList;
	for(AreaInfoList *a=AreaInfos.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList	*k=new AlgorithmLibraryList();
		k->SetLibID(a->GetLibID());
		LibIDList.AppendList(k);
	}
	AutoClassifyBase	*BBase=GetAutoClassifyBase();
	GetLayersBase()->GetDatabaseLoader()->G_GetLibraryNames(*GetLayersBase()->GetDataBase(),BBase->GetLibraryContainer(),LibIDList);
	int	row=0;
	for(AreaInfoList *a=AreaInfos.GetFirst();a!=NULL;a=a->GetNext(),row++){
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
		W->setText(QString::number(a->AreaCount));
	}
}


void PropertyAutoClassifyForm::on_toolButtonAreaMode_clicked()
{
	BroadcastShowInEdit();
}