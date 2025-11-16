#include "PropertyAreaFilterResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAreaFilter\PropertyAreaFilterForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyAreaFilterForm.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "SelectAreaFilterLibrary.h"
#include "XDisplayImagePacket.h"
#include <QMessageBox>
#include "XGeneralFunc.h"
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


PropertyAreaFilterForm::PropertyAreaFilterForm(LayersBase *Base ,QWidget *parent)
: GUIFormBase(Base,parent), qdoublevalidator(parent)
{
	ui.setupUi(this);
	LibFolderID =-1;
	AreaFilterBase	*BBase=GetAreaFilterBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	
	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);
	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAreaFilterLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}

	//ui.lineEditSliceUpperBlocksByValue->setValidator( &qdoublevalidator );

	ui.tableWidgetItems	->setColumnWidth(0,42);
	ui.tableWidgetItems	->setColumnWidth(1,42);
	ui.tableWidgetItems	->setColumnWidth(2,42);
	ui.tableWidgetItems	->setColumnWidth(3,42);
	ui.tableWidgetItems	->setColumnWidth(4,80);

	SynchronizeModeAndProperty();
}

PropertyAreaFilterForm::~PropertyAreaFilterForm()
{
	if(TempLib!=NULL)
		delete	TempLib;
}
AreaFilterBase	*PropertyAreaFilterForm::GetAreaFilterBase(void)
{
	return (AreaFilterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AreaFilter");
}
void	PropertyAreaFilterForm::BuildForShow(void)
{
	ShowItemGrid();
}
void	PropertyAreaFilterForm::ShowInEdit(void)
{
	ShowItemGrid();
}
void	PropertyAreaFilterForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	SlotSelectLibFolder(_LibFolderID ,LinFolderName);
}
void	PropertyAreaFilterForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	AreaFilterBase	*BBase=GetAreaFilterBase();
	if(BBase!=NULL){
		CmdGetAreaFilterLibraryListPacket	Packet(GetLayersBase());
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

void	PropertyAreaFilterForm::TransmitDirectly(GUIDirectMessage *packet)
{
	//AreaFilterBase	*BBase=GetAreaFilterBase();
	CmdAreaFilterDrawModePacket	*BDrawModePacket=dynamic_cast<CmdAreaFilterDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		return;
	}
	CmdAreaFilterDrawEnd	*AreaFilterDEnd=dynamic_cast<CmdAreaFilterDrawEnd *>(packet);
	if(AreaFilterDEnd!=NULL){
		SelectAreaFilterLibrary	D(GetLayersBase(),NULL);
		if(D.exec()==(int)true){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(AreaFilterDEnd->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=AreaFilterDEnd->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					GUICmdSendAddManualAreaFilter	Cmd(GetLayersBase(),sRoot,sName,page);
					Cmd.Area=A;
					Cmd.SelectedLibID	=D.SelectedLibID;
					Cmd.LayerList=AreaFilterDEnd->LayerList;
					Cmd.SendOnly(GetLayersBase()->GetGlobalPageFromLocal(page),0);
				}
			}
		}
		ShowItemGrid();
	}
}


void PropertyAreaFilterForm::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void PropertyAreaFilterForm::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(PropertyAreaFilterForm_LS,LID_0)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(PropertyAreaFilterForm_LS,LID_1)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetLibID()==TempLib->GetLibID()){
				SelectedLibList.RemoveList(a);
				delete	a;
				break;
			}
		}
		CmdDeleteAreaFilterLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AreaFilterBase	*BBase=GetAreaFilterBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void PropertyAreaFilterForm::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(PropertyAreaFilterForm_LS,LID_2)/*"Warning"*/, LangSolver.GetString(PropertyAreaFilterForm_LS,LID_3)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);

	CmdInsertAreaFilterLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AreaFilterBase	*BBase=GetAreaFilterBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");

}

void PropertyAreaFilterForm::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(PropertyAreaFilterForm_LS,LID_4)/*"Warning"*/, LangSolver.GetString(PropertyAreaFilterForm_LS,LID_5)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertAreaFilterLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AreaFilterBase	*BBase=GetAreaFilterBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateAreaFilterLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AreaFilterBase	*BBase=GetAreaFilterBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");

}

void PropertyAreaFilterForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadAreaFilterLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AreaFilterBase	*BBase=GetAreaFilterBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
}

void	PropertyAreaFilterForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
	ui.EditLibID	->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	AreaFilterLibrary	*ALib=dynamic_cast<AreaFilterLibrary *>(data.GetLibrary());
	if(ALib->FilterType==AreaFilterLibrary::_PatternInverted){
		ui.radioButtonTypePatternInverted->setChecked(true);
	}
	if(ALib->FilterType==AreaFilterLibrary::_VerticalEmphasize){
		ui.radioButtonTypeVerticalEmphasize->setChecked(true);
	}
	if(ALib->FilterType==AreaFilterLibrary::_LineEmphasize){
		ui.radioButtonTypeLineEmphasize->setChecked(true);
		ui.spinBoxBlockSize		->setValue(ALib->BlockSize);
		ui.spinBoxEmphasizeRate	->setValue(ALib->EmphasizeRate);
		ui.spinBoxUpperBlocksPercentageByVariance->setValue(ALib->UpperBlocksPercentageByVariance);
		//ui.lineEditSliceUpperBlocksByValue->setText(QString::number(data.SliceUpperBlocksByValue,'e',5));
		//ui.checkBoxSliceUpperBlocksByValue->setChecked(data.BoolSliceUpperBlocksByValue);
		ui.spinBoxSkipSita		->setValue(ALib->SkipTheta);
		ui.spinBoxSkipKy		->setValue(ALib->SkipKy);
		ui.spinBoxUnifiedLineNumb->setValue(ALib->UnifiedLineNumb);
	}
	if(ALib->FilterType==AreaFilterLibrary::_LargeEnflat){
		ui.radioButtonTypeLineLargeEnflat->setChecked(true);
		ui.spinBoxLineLargeEnflat_BlockSize	->setValue	(ALib->BlockSize);
		ui.checkBoxMoveByAlignment			->setChecked(ALib->MoveByAlignment);
		ui.spinBoxSkipDot					->setValue	(ALib->SkipDot);
		ui.spinBoxGeneratedBrightness		->setValue	(ALib->GeneratedBrightness);
		ui.doubleSpinBoxAdoptedRate			->setValue	(ALib->AdoptedRate	);
	}
	if(ALib->FilterType==AreaFilterLibrary::_HorizontalEmphasize){
		ui.radioButtonTypeHorizontalEmphasize->setChecked(true);
		ui.spinBoxHorizEmphaBlockSize		->setValue	(ALib->BlockSize);
		ui.checkBoxMoveByAlignment2			->setChecked(ALib->MoveByAlignment);
		ui.spinBoxEmphasizeRate2			->setValue	(ALib->EmphasizeRate);
		ui.spinBoxSkipDot2					->setValue	(ALib->SkipDot);
		ui.spinBoxBlockHeight				->setValue	(ALib->BlockHeight);
	}
	if(ALib->FilterType==AreaFilterLibrary::_Differential){
		ui.radioButtonTypeDifferential		->setChecked(true);
		ui.spinBoxDifferentialBlockSize		->setValue	(ALib->BlockSize);
		ui.spinBoxBlockDifferentialShrinkRate->setValue	(ALib->ShrinkRate);
	}
}

void	PropertyAreaFilterForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	AreaFilterLibrary	*ALib=dynamic_cast<AreaFilterLibrary *>(data.GetLibrary());
	if(ui.radioButtonTypePatternInverted->isChecked()==true)
		ALib->FilterType=AreaFilterLibrary::_PatternInverted;
	else if(ui.radioButtonTypeVerticalEmphasize->isChecked()==true)
		ALib->FilterType=AreaFilterLibrary::_VerticalEmphasize;
	else if(ui.radioButtonTypeLineEmphasize->isChecked()==true){
		ALib->FilterType=AreaFilterLibrary::_LineEmphasize;
		ALib->BlockSize=ui.spinBoxBlockSize->value();
		ALib->EmphasizeRate=ui.spinBoxEmphasizeRate->value();
		ALib->UpperBlocksPercentageByVariance=ui.spinBoxUpperBlocksPercentageByVariance->value();
		//ALib->SliceUpperBlocksByValue=ui.lineEditSliceUpperBlocksByValue->text().toDouble();
		//ALib->BoolSliceUpperBlocksByValue=ui.checkBoxSliceUpperBlocksByValue->isChecked();
		ALib->SkipTheta=ui.spinBoxSkipSita->value();
		ALib->SkipKy=ui.spinBoxSkipKy->value();
		ALib->UnifiedLineNumb=ui.spinBoxUnifiedLineNumb->value();
	}
	else if(ui.radioButtonTypeLineLargeEnflat->isChecked()==true){
		ALib->FilterType=AreaFilterLibrary::_LargeEnflat;
		ALib->BlockSize		=ui.spinBoxLineLargeEnflat_BlockSize->value();
		ALib->MoveByAlignment=ui.checkBoxMoveByAlignment		->isChecked();
		ALib->SkipDot		=ui.spinBoxSkipDot					->value();
		ALib->GeneratedBrightness	=ui.spinBoxGeneratedBrightness->value();
		ALib->AdoptedRate	=ui.doubleSpinBoxAdoptedRate		->value();
	}
	else if(ui.radioButtonTypeHorizontalEmphasize->isChecked()==true){
		ALib->FilterType=AreaFilterLibrary::_HorizontalEmphasize;
		ALib->BlockSize			=ui.spinBoxHorizEmphaBlockSize	->value	();
		ALib->MoveByAlignment	=ui.checkBoxMoveByAlignment2	->isChecked();
		ALib->EmphasizeRate		=ui.spinBoxEmphasizeRate2		->value	();
		ALib->SkipDot			=ui.spinBoxSkipDot2				->value	();
		ALib->BlockHeight		=ui.spinBoxBlockHeight			->value();
	}
	else if(ui.radioButtonTypeDifferential->isChecked()==true){
		ALib->FilterType=AreaFilterLibrary::_Differential;
		ALib->BlockSize	=ui.spinBoxDifferentialBlockSize		->value();
		ALib->ShrinkRate	=ui.spinBoxBlockDifferentialShrinkRate->value();
	}
}

void PropertyAreaFilterForm::SynchronizeModeAndProperty()
{
	if(ui.radioButtonTypePatternInverted->isChecked())
		ui.stackedWidget->setCurrentIndex(0);
	else if(ui.radioButtonTypeVerticalEmphasize->isChecked())
		ui.stackedWidget->setCurrentIndex(1);
	else if(ui.radioButtonTypeLineEmphasize->isChecked())
		ui.stackedWidget->setCurrentIndex(2);
	else if(ui.radioButtonTypeLineLargeEnflat->isChecked())
		ui.stackedWidget->setCurrentIndex(3);
	else if(ui.radioButtonTypeHorizontalEmphasize->isChecked())
		ui.stackedWidget->setCurrentIndex(4);
	else if(ui.radioButtonTypeDifferential->isChecked())
		ui.stackedWidget->setCurrentIndex(5);
}


void PropertyAreaFilterForm::on_radioButtonTypePatternInverted_toggled(bool)
{
	SynchronizeModeAndProperty();
}

void PropertyAreaFilterForm::on_radioButtonTypeVerticalEmphasize_toggled(bool)
{
	SynchronizeModeAndProperty();
}

void PropertyAreaFilterForm::on_radioButtonTypeLineEmphasize_toggled(bool)
{
	SynchronizeModeAndProperty();
}
void PropertyAreaFilterForm::on_radioButtonTypeLineLargeEnflat_toggled(bool checked)
{
	SynchronizeModeAndProperty();
}

void PropertyAreaFilterForm::on_radioButtonTypeDifferential_toggled(bool checked)
{
	SynchronizeModeAndProperty();
}

void PropertyAreaFilterForm::on_radioButtonTypeHorizontalEmphasize_toggled(bool checked)
{
    SynchronizeModeAndProperty();
}
void	PropertyAreaFilterForm::ShowItemGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendAreaFilterList	**BmpReceiver =new GUICmdSendAreaFilterList*[GetParamGlobal()->PageNumb];
	GUICmdReqAreaFilterList		**BmpRequester=new GUICmdReqAreaFilterList *[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page]	=new GUICmdSendAreaFilterList	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]	=new GUICmdReqAreaFilterList	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	}

	ItemListInfo.RemoveAll();
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page],60000)==true
		&& BmpReceiver[page]->IsReceived()==true){
			ItemListInfo+=BmpReceiver[page]->ItemListInfo;
		}
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	int	Numb=ItemListInfo.GetNumber();
	ui.tableWidgetItems->setRowCount(Numb);
	ui.tableWidgetItems->setUpdatesEnabled(false);
	AreaFilterBase	*BBase=GetAreaFilterBase();
	int	Row=0;
	for(AreaFilterListForPacket *L=ItemListInfo.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		::SetDataToTable(ui.tableWidgetItems ,0,Row ,QString::number(L->Data.Page));
		::SetDataToTable(ui.tableWidgetItems ,1,Row ,QString::number(L->Data.Layer));
		::SetDataToTable(ui.tableWidgetItems ,2,Row ,QString::number(L->Data.ItemID));
		::SetDataToTable(ui.tableWidgetItems ,3,Row ,QString::number(L->Data.LibID));

		QString	LibName=BBase->GetLibraryContainer()->GetLibraryName(L->Data.LibID);
		::SetDataToTable(ui.tableWidgetItems ,4,Row ,LibName);
	}
	ui.tableWidgetItems->setUpdatesEnabled(true);

	ReEntrant=false;
}

void PropertyAreaFilterForm::on_tableWidgetItems_clicked(const QModelIndex &MIndex)
{
	AreaFilterListForPacket *L=ItemListInfo.GetItem(MIndex.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->Data.Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->Data.x1+P->GetOutlineOffset()->x,L->Data.y1+P->GetOutlineOffset()->y
									,L->Data.x2+P->GetOutlineOffset()->x,L->Data.y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"MaskingImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->Data.Page,L->Data.Layer,L->Data.ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}
