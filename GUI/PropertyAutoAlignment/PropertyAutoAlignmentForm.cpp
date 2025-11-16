/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoAlignment\PropertyAutoAlignmentForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyAutoAlignmentFormResource.h"
#include "PropertyAutoAlignmentForm.h"
#include "EditLibraryAutoAlignment.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XAutoAlignmentPacket.h"
#include "EditLibraryMono.h"
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyAutoAlignmentForm::PropertyAutoAlignmentForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);
	ui.tableWidgetGeneratedLibList	->setColumnWidth (0, 30);
	ui.tableWidgetGeneratedLibList	->setColumnWidth (1, 80);	
	ui.tableWidgetAreaList			->setColumnWidth (0, 30);
	ui.tableWidgetAreaList			->setColumnWidth (1, 80);
	ui.tableWidgetAreaList			->setColumnWidth (2, 30);
	ui.tableWidgetAreaList			->setColumnWidth (3, 50);

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAutoAlignmentLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}

	//connect
	connect(ui.ButtonPickupTest			 ,SIGNAL(clicked())		,this,SLOT(ButtonPickupTestClicked()));
	connect(ui.radioButtonSheetPickupTest,SIGNAL(toggled(bool))	,this,SLOT(radioButtonSheetPickupTestToggled(bool)));
}

PropertyAutoAlignmentForm::~PropertyAutoAlignmentForm()
{

}

AutoAlignmentBase	*PropertyAutoAlignmentForm::GetAutoAlignmentBase(void)
{
	return (AutoAlignmentBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
}

void PropertyAutoAlignmentForm::on_pushButtonEditLibrary_clicked()
{
	if(GetLayerNumb(0)>=3){
		EditLibraryAutoAlignment	D(GetLayersBase(),this);
		D.exec();
	}
	else if(GetLayerNumb(0)==1){
		EditLibraryMono				D(GetLayersBase(),this);
		D.exec();
	}
}

void PropertyAutoAlignmentForm::on_pushButtonEditLibFolder_clicked()
{
	AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyAutoAlignmentForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui.labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void	PropertyAutoAlignmentForm::BuildForShow(void)
{
	ShowAreaList();
	on_pushButtonUpdateView_clicked();
}

void	PropertyAutoAlignmentForm::ShowLibList(void)
{
	ui.tableWidgetLibList->setRowCount(0);
	AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
	if(BBase!=NULL){
		CmdGetAutoAlignmentLibraryListPacket	Packet(GetLayersBase());
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
struct	AlgorithmLibraryListClass
{
	AlgorithmLibraryList	*a;
};

void	PropertyAutoAlignmentForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
	if(BBase!=NULL){
		CmdCreateTempAutoAlignmentLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadAutoAlignmentLibraryPacket	Packet(GetLayersBase());
			Packet.Point=SLib;
			BBase->TransmitDirectly(&Packet);
		}
		for(;;){
			AlgorithmLibraryList *a=SelectedLibList.GetFirst();
			if(a==NULL)
				break;
			SelectedLibList.RemoveList(a);
		}
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

void PropertyAutoAlignmentForm::on_tableWidgetLibList_doubleClicked(QModelIndex)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyAutoAlignmentForm::on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex)
{
	on_pushButtonGetBack_clicked();
}

void PropertyAutoAlignmentForm::on_pushButtonSetFrom_clicked()
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

void PropertyAutoAlignmentForm::on_pushButtonGetBack_clicked()
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

void PropertyAutoAlignmentForm::on_ButtonGenerateLibs_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdCreateAutoAlignmentSheet	RCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.SelectedLibList=SelectedLibList;
		RCmd.Send(NULL,page,0);
	}
}

void PropertyAutoAlignmentForm::on_pushButtonUpdateView_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqAutoAlignmentInfo	RCmd(GetLayersBase(),sRoot,sName,page);
		GUICmdSendAutoAlignmentInfo	SCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.Send(page,0,SCmd);
		SheetLevels=SCmd.SheetLevels;
	}
	ui.comboBoxMonoLevel->clear();
	int	N=0;
	for(IntClass *a=SheetLevels.GetFirst();a!=NULL;a=a->GetNext(),N++){
		ui.comboBoxMonoLevel->addItem(QString::number(a->GetValue()),N);
	}
}
void	PropertyAutoAlignmentForm::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReqAutoAlignmentDrawMode	*GUICmdReqAutoAlignmentDrawModeVar=dynamic_cast<GUICmdReqAutoAlignmentDrawMode *>(packet);
	if(GUICmdReqAutoAlignmentDrawModeVar!=NULL){
		if(ui.radioButtonSheetNone->isChecked()==true)
			GUICmdReqAutoAlignmentDrawModeVar->DrawSheetMode=0;
		else if(ui.radioButtonSheetArea->isChecked()==true)
			GUICmdReqAutoAlignmentDrawModeVar->DrawSheetMode=1;
		else if(ui.radioButtonSheetPickup->isChecked()==true)
			GUICmdReqAutoAlignmentDrawModeVar->DrawSheetMode=2;
		else if(ui.radioButtonSheetPickupTest->isChecked()==true)
			GUICmdReqAutoAlignmentDrawModeVar->DrawSheetMode=3;

		if(ui.checkBoxMonoView->isChecked()==true)
			GUICmdReqAutoAlignmentDrawModeVar->DrawMono=true;
		else
			GUICmdReqAutoAlignmentDrawModeVar->DrawMono=false;
		GUICmdReqAutoAlignmentDrawModeVar->MonoLevel=ui.comboBoxMonoLevel->itemData(ui.comboBoxMonoLevel->currentIndex()).toInt();

		GUICmdReqAutoAlignmentDrawModeVar->DrawPico=0;
		if(ui.checkBoxPicoTransView->isChecked()==true)
			GUICmdReqAutoAlignmentDrawModeVar->DrawPico|=1;
		if(ui.checkBoxPicoPickupView->isChecked()==true)
			GUICmdReqAutoAlignmentDrawModeVar->DrawPico|=2;
		if(ui.checkBoxPicoOtherView->isChecked()==true)
			GUICmdReqAutoAlignmentDrawModeVar->DrawPico|=4;
		if(ui.checkBoxPicoInfo->isChecked()==true)
			GUICmdReqAutoAlignmentDrawModeVar->DrawPico|=8;
		if(ui.checkBoxFringeArea->isChecked()==true)
			GUICmdReqAutoAlignmentDrawModeVar->DrawPico|=16;

		for(int i=0;i<ui.tableWidgetAreaList->selectedItems().count();i++){
			QTableWidgetItem	*s=ui.tableWidgetAreaList->selectedItems()[i];
			if(s->column()==0){
				GUICmdReqAutoAlignmentDrawModeVar->SelectedLDList.Add(AAInfos.GetItem(s->row())->ID,AAInfos.GetItem(s->row())->CreatedManual);
			}
		}
		return;
	}
	CmdGetAutoAlignmentResult	*CmdGetAutoAlignmentResultVar=dynamic_cast<CmdGetAutoAlignmentResult *>(packet);
	if(CmdGetAutoAlignmentResultVar!=NULL){
		ui.lineEditXFromMaster->setText(QString::number(CmdGetAutoAlignmentResultVar->ShiftXFromMaster));
		ui.lineEditYFromMaster->setText(QString::number(CmdGetAutoAlignmentResultVar->ShiftYFromMaster));
		ui.lineEditXFromTarget->setText(QString::number(CmdGetAutoAlignmentResultVar->ShiftXFromTarget));
		ui.lineEditYFromTarget->setText(QString::number(CmdGetAutoAlignmentResultVar->ShiftYFromTarget));
		ui.lineEditRelativeXFromMaster->setText(QString::number(CmdGetAutoAlignmentResultVar->ShiftRelativeXFromMaster));
		ui.lineEditRelativeYFromMaster->setText(QString::number(CmdGetAutoAlignmentResultVar->ShiftRelativeYFromMaster));
		ui.lineEditRelativeXFromTarget->setText(QString::number(CmdGetAutoAlignmentResultVar->ShiftRelativeXFromTarget));
		ui.lineEditRelativeYFromTarget->setText(QString::number(CmdGetAutoAlignmentResultVar->ShiftRelativeYFromTarget));
		return;
	}
	CmdAutoAlignmentExecuteDrawEnd	*CmdAutoAlignmentExecuteDrawEndVar=dynamic_cast<CmdAutoAlignmentExecuteDrawEnd *>(packet);
	if(CmdAutoAlignmentExecuteDrawEndVar!=NULL){
		int	Page=GetLayersBase()->GetLocalPageFromAreaFromDrawingTop(CmdAutoAlignmentExecuteDrawEndVar->GlobalArea);
		GUICmdSetAutoAlignmentLibColor	RCmd(GetLayersBase(),sRoot,sName,Page);
		RCmd.LocalArea=CmdAutoAlignmentExecuteDrawEndVar->GlobalArea;
		DataInPage	*P=GetLayersBase()->GetPageData(Page);
		P->ClipAreaGlobal(RCmd.LocalArea);
		for(int i=0;i<ui.tableWidgetAreaList->selectedItems().count();i++){
			QTableWidgetItem	*s=ui.tableWidgetAreaList->selectedItems()[i];
			if(s->column()==0){
				RCmd.LibID=AAInfos.GetItem(s->row())->ID;
				break;
			}
		}

		RCmd.Send(NULL,Page,0);
		return;
	}
	CmdAutoAlignmentAddManualSheetDrawEnd	*AutoAlignmentAddManualSheetVar=dynamic_cast<CmdAutoAlignmentAddManualSheetDrawEnd *>(packet);
	if(AutoAlignmentAddManualSheetVar!=NULL){
		int	r=ui.tableWidgetGeneratedLibList->currentRow();
		int	AdditionalItemID;
		if(r<0){
			AASheetInfoList *b=AAInfos.GetFirst();
			if(b==NULL){
				return;
			}
			AdditionalItemID=b->ID;
		}
		else{
			AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
			if(a==NULL){
				return;
			}
			AdditionalItemID=a->GetLibID();
		}
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(AutoAlignmentAddManualSheetVar->GlobalArea,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
			FlexArea	A=AutoAlignmentAddManualSheetVar->GlobalArea;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				GUICmdAddAutoAlignmentSheet	RCmd(GetLayersBase(),sRoot,sName,pdata->GetPage());
				RCmd.LocalArea	=A;
				RCmd.LibID		=AdditionalItemID;
				RCmd.Send(NULL,pdata->GetPage(),0);
			}
		}

		ShowAreaList();
		return;
	}

	CmdSetAutoAlignmentShowingState	*CmdSetAutoAlignmentShowingStateVar=dynamic_cast<CmdSetAutoAlignmentShowingState *>(packet);
	if(CmdSetAutoAlignmentShowingStateVar!=NULL){
		ShowAreaList();
		switch(CmdSetAutoAlignmentShowingStateVar->ModeShowingSheet){
			case CmdSetAutoAlignmentShowingState::_None:
				ui.radioButtonSheetNone->setChecked(true);
				break;
			case CmdSetAutoAlignmentShowingState::_Area:
				ui.radioButtonSheetArea->setChecked(true);
				break;
			case CmdSetAutoAlignmentShowingState::_PickupArea:
				ui.radioButtonSheetPickup->setChecked(true);
				break;
			case CmdSetAutoAlignmentShowingState::_PickupAreaTest:
				ui.radioButtonSheetPickupTest->setChecked(true);
				break;
		}
		ui.checkBoxMonoView->setChecked(CmdSetAutoAlignmentShowingStateVar->ModeShowingMono);
		int	N=0;
		for(IntClass *a=SheetLevels.GetFirst();a!=NULL;a=a->GetNext(),N++){
			if(a->GetValue()==CmdSetAutoAlignmentShowingStateVar->MonoLevel){
				ui.comboBoxMonoLevel->setCurrentIndex(N);
				break;
			}
		}
		ui.checkBoxPicoTransView	->setChecked(CmdSetAutoAlignmentShowingStateVar->ModeShowingPicoTransArea);
		ui.checkBoxPicoPickupView	->setChecked(CmdSetAutoAlignmentShowingStateVar->ModeShowingPicoPickupArea);
		ui.checkBoxPicoOtherView	->setChecked(CmdSetAutoAlignmentShowingStateVar->ModeShowingPicoOtherArea);
		ui.checkBoxFringeArea		->setChecked(CmdSetAutoAlignmentShowingStateVar->ModeShowingPicoFringeArea);
		ui.checkBoxPicoInfo			->setChecked(CmdSetAutoAlignmentShowingStateVar->ModeShowingPicoInfo);

		if(CmdSetAutoAlignmentShowingStateVar->ShowingLibIDs.GetFirst()!=NULL){
			ui.tableWidgetAreaList->clearSelection();
			for(AAListAttr *c=CmdSetAutoAlignmentShowingStateVar->ShowingLibIDs.GetFirst();c!=NULL;c=c->GetNext()){
				int	Row=0;
				for(AASheetInfoList *b=AAInfos.GetFirst();b!=NULL;b=b->GetNext(),Row++){
					if(b->ID==c->LibID){
						break;
					}
				}
				for(int Col=0;Col<ui.tableWidgetAreaList->columnCount();Col++){
					QTableWidgetItem *Item=ui.tableWidgetAreaList->item (Row, Col);
					Item->setSelected(true);
				}
			}
		}

		if(CmdSetAutoAlignmentShowingStateVar->ModeClickPickupAreaTest==true){
			//???o?e?X?g
			ButtonPickupTestClicked();
		}

		return;
	}
}

void PropertyAutoAlignmentForm::ShowAreaList(void)
{
	AAInfos.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqAutoAlignmentSheet		RCmd(GetLayersBase(),sRoot,sName,page);
		GUICmdSendAutoAlignmentSheet	SCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.Send(page,0,SCmd);
		for(AASheetInfoList *a=SCmd.AASheetInfoData.GetFirst();a!=NULL;a=a->GetNext()){
			AASheetInfoList *b;
			for(b=AAInfos.GetFirst();b!=NULL;b=b->GetNext()){
				if(a->ID==b->ID && a->CreatedManual==b->CreatedManual){
					break;
				}
			}
			if(b==NULL){
				AAInfos.AppendList(new AASheetInfoList(a->ID,a->PicoShift,a->CreatedManual));
			}
		}
	}

	AutoAlignmentBase *PBase=(AutoAlignmentBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	ui.tableWidgetAreaList->setRowCount(AAInfos.GetCount());
	int	Row=0;
	for(AASheetInfoList *b=AAInfos.GetFirst();b!=NULL;b=b->GetNext(),Row++){
		SetDataToTable(ui.tableWidgetAreaList ,0,Row ,b->ID);
		CmdGetAutoAlignmentLibraryNamePacket	GCmd(GetLayersBase());
		GCmd.LibID=b->ID;
		PBase->TransmitDirectly(&GCmd);
		if(GCmd.Success==true){
			SetDataToTable(ui.tableWidgetAreaList ,1,Row ,GCmd.LibName);
		}
		else{
			SetDataToTable(ui.tableWidgetAreaList ,1,Row ,/**/"");
		}
		SetDataToTable(ui.tableWidgetAreaList ,2,Row ,b->PicoShift);
		if(b->CreatedManual==true)
			SetDataToTable(ui.tableWidgetAreaList ,3,Row ,/**/"Manual");
		else
			SetDataToTable(ui.tableWidgetAreaList ,3,Row ,/**/"Auto");
	}
}

void PropertyAutoAlignmentForm::on_tableWidgetAreaList_clicked(const QModelIndex &)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AutoAlignmentImagePanel" ,/**/"");
	GProp->Repaint();
}




void PropertyAutoAlignmentForm::SendState(void)
{
	if(GetParamComm()->Mastered==false)
		return;

	for(int page=0;page<GetPageNumb();page++){
		GUICmdSetAutoAlignmentShowingState	RCmd(GetLayersBase(),sRoot,sName,page);
		if(ui.radioButtonSheetNone->isChecked()==true)
			RCmd.State.ModeShowingSheet=CmdSetAutoAlignmentShowingState::_None;
		else if(ui.radioButtonSheetArea->isChecked()==true)
			RCmd.State.ModeShowingSheet=CmdSetAutoAlignmentShowingState::_Area;
		else if(ui.radioButtonSheetPickup->isChecked()==true)
			RCmd.State.ModeShowingSheet=CmdSetAutoAlignmentShowingState::_PickupArea;
		else if(ui.radioButtonSheetPickupTest->isChecked()==true)
			RCmd.State.ModeShowingSheet=CmdSetAutoAlignmentShowingState::_PickupAreaTest;

		if(ui.checkBoxMonoView->isChecked()==true)
			RCmd.State.ModeShowingMono=true;
		else
			RCmd.State.ModeShowingMono=false;
		RCmd.State.MonoLevel=ui.comboBoxMonoLevel->itemData(ui.comboBoxMonoLevel->currentIndex()).toInt();

		if(ui.checkBoxPicoTransView->isChecked()==true)
			RCmd.State.ModeShowingPicoTransArea=true;
		else
			RCmd.State.ModeShowingPicoTransArea=false;

		if(ui.checkBoxPicoPickupView->isChecked()==true)
			RCmd.State.ModeShowingPicoPickupArea=true;
		else
			RCmd.State.ModeShowingPicoPickupArea=false;

		if(ui.checkBoxPicoOtherView->isChecked()==true)
			RCmd.State.ModeShowingPicoOtherArea=true;
		else
			RCmd.State.ModeShowingPicoOtherArea=false;

		if(ui.checkBoxFringeArea->isChecked()==true)
			RCmd.State.ModeShowingPicoFringeArea=true;
		else
			RCmd.State.ModeShowingPicoFringeArea=false;

		if(ui.checkBoxPicoInfo->isChecked()==true)
			RCmd.State.ModeShowingPicoInfo=true;
		else
			RCmd.State.ModeShowingPicoInfo=false;

		for(int i=0;i<ui.tableWidgetAreaList->selectedItems().count();i++){
			QTableWidgetItem	*s=ui.tableWidgetAreaList->selectedItems()[i];
			if(s->column()==0){
				RCmd.State.ShowingLibIDs.Add(AAInfos.GetItem(s->row())->ID,AAInfos.GetItem(s->row())->CreatedManual);
			}
		}		
		RCmd.Send(NULL,page,0);
	}

}


void PropertyAutoAlignmentForm::on_groupBox_toggled(bool)
{
	SendState();
}

void PropertyAutoAlignmentForm::on_checkBoxMonoView_stateChanged(int)
{
	SendState();
}

void PropertyAutoAlignmentForm::on_checkBoxPicoTransView_stateChanged(int)
{
	SendState();
}

void PropertyAutoAlignmentForm::on_checkBoxPicoPickupView_stateChanged(int)
{
	SendState();
}

void PropertyAutoAlignmentForm::on_checkBoxPicoOtherView_stateChanged(int)
{
	SendState();
}

void PropertyAutoAlignmentForm::on_checkBoxFringeArea_stateChanged(int)
{
	SendState();
}

void PropertyAutoAlignmentForm::on_checkBoxPicoInfo_stateChanged(int)
{
	SendState();
}


void PropertyAutoAlignmentForm::on_radioButtonSheetNone_toggled(bool)
{
	SendState();
}

void PropertyAutoAlignmentForm::on_radioButtonSheetArea_toggled(bool)
{
	SendState();
}

void PropertyAutoAlignmentForm::on_radioButtonSheetPickup_toggled(bool)
{
	SendState();
}

void PropertyAutoAlignmentForm::on_comboBoxMonoLevel_textChanged(const QString &)
{
	SendState();
}

void PropertyAutoAlignmentForm::radioButtonSheetPickupTestToggled(bool)
{
	SendState();
}

void PropertyAutoAlignmentForm::ButtonPickupTestClicked()
{
	if(TempLib==NULL){
		return;
	}

///	int	Row=ui.tableWidgetAreaList->currentRow();
///	if(Row<0){
///		return;
///	}
///	int i=0;
///	int LibID=-1;
///	for(AASheetInfoList *b=AAInfos.GetFirst();b!=NULL;b=b->GetNext(),i++){
///		if(i==Row){
///			LibID=b->ID;
///			break;
///		}
///	}
///	if(LibID==-1){
///		return;
///	}

///	//???C?u?????i?n?d?a??
///	AlgorithmBase	*AutoAlignmentBasePointer=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
///	if(AutoAlignmentBasePointer==NULL){
///		return;
///	}
///	//???C?u?????I???g?d?h?c?O???c?c?a??
///	//???C?u?????I?C???R?[?h?a?3?-?A?a???z?O???A?C???A??a?e
///	AutoAlignmentBasePointer->GetLibraryContainer()->GetLibrary(LibID,*TempLib);

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyAutoAlignmentForm_LS,LID_0)/*"Pickup Test"*/);

	//IntList LayerList;
	//GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"BlockImagePanel" ,/**/"");
	//if(GProp!=NULL){
	//	DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
	//	if(di!=NULL){
	//		di->GetActiveLayerList(LayerList);
	//	}
	//}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdPickupTest	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			//Cmd.LibID		=LibID;
			//Cmd.LibPoint	=TempLib;
			Cmd.PhaseNumb	=phase;
			Cmd.SendOnly(GlobalPage,0);
		}
	}

	GetLayersBase()->CloseProcessingForm();
}

void	PropertyAutoAlignmentForm::ClearLibList(void)
{
	on_pushButtonGetBackAll_clicked();
}

void	PropertyAutoAlignmentForm::SetLib(int LibID)
{
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==LibID)
			return;
	}
	AutoAlignmentBase *BBase=(AutoAlignmentBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	if(BBase!=NULL){
		CmdGetLibName	Packet(GetLayersBase());
		Packet.LibID=LibID;
		BBase->TransmitDirectly(&Packet);

		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,LibID,Packet.LibName));
		ShowSelectedLibList();
	}
}

void	PropertyAutoAlignmentForm::GenerateBlocks(void)
{
	on_ButtonGenerateLibs_clicked();
}
void PropertyAutoAlignmentForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyAutoAlignmentForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}
