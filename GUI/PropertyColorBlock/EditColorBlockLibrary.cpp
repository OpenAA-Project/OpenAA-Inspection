/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorBlock\EditColorBlockLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyColorBlockFormResource.h"
#include "EditColorBlockLibrary.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ColorSelectBlockLibraryForm.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyColorBlockPacket.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditColorBlockLibrary::EditColorBlockLibrary(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base),ButtonR(false),ButtonG(false),ButtonB(false)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	ColorBlockBase	*BBase=GetColorBlockBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	ui.tableWidgetSubtractLibList->setColumnWidth (0, 30);
	ui.tableWidgetSubtractLibList->setColumnWidth (1, 80);
	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempColorBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
	on_toolButtonPickup_clicked();
	on_toolButtonInspect_clicked();

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

	InstallOperationLog(this);
}

EditColorBlockLibrary::~EditColorBlockLibrary()
{
	if(TempLib!=NULL)
		delete	TempLib;
}

ColorBlockBase	*EditColorBlockLibrary::GetColorBlockBase(void)
{
	return (ColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
}

void	EditColorBlockLibrary::MListSectionClicked ( int logicalIndex )
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
void	EditColorBlockLibrary::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ShowLibList();
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
void	EditColorBlockLibrary::ShowLibList(void)
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

void EditColorBlockLibrary::on_tableWidgetLibList_clicked(const QModelIndex &Index)
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
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(EditColorBlockLibrary_LS,LID_46)/*"Library error"*/, LangSolver.GetString(EditColorBlockLibrary_LS,LID_47)/*"Not loaded this library record"*/);
			}
		}
	}
}

void EditColorBlockLibrary::on_ButtonAddSubtractLib_3_clicked()
{
	if(TempLib==NULL)
		return;
	ColorSelectBlockLibraryForm	D(GetLayersBase(),this);
	if(D.exec()==QDialog::Accepted){
		int	LibID=D.SelectedLibID;
		ColorBlockLibrary	*ALib=dynamic_cast<ColorBlockLibrary *>(TempLib->GetLibrary());
		if(ALib->SubtractBlock.IsInclude(LibID)==true)
			return;
		ALib->SubtractBlock.Add(LibID);
		ShowSubtractList(*ALib);
	}
}

void EditColorBlockLibrary::on_ButtonDelSubtractLib_3_clicked()
{
	QModelIndex	RIndex=ui.tableWidgetSubtractLibList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	ColorBlockLibrary	*ALib=dynamic_cast<ColorBlockLibrary *>(TempLib->GetLibrary());
	IntClass *c=ALib->SubtractBlock.GetItem(R);
	if(c!=NULL){
		ALib->SubtractBlock.RemoveList(c);
		delete	c;
		ShowSubtractList(*ALib);
	}
}
void EditColorBlockLibrary::ShowSubtractList(ColorBlockLibrary &data)
{
	if(TempLib==NULL)
		return;
	CmdGetColorBlockLibraryNamePacket	LNamePacket(GetLayersBase());

	for(IntClass *c=data.SubtractBlock.GetFirst();c!=NULL;c=c->GetNext()){
		LNamePacket.AList.AppendList(new AlgorithmLibraryList(LibType,c->GetValue(),/**/""));
	}
	ColorBlockBase	*BBase=GetColorBlockBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&LNamePacket);
	}
	int	row=0;
	ui.tableWidgetSubtractLibList->setRowCount(data.SubtractBlock.GetCount());
	for(IntClass *c=data.SubtractBlock.GetFirst();c!=NULL;c=c->GetNext(),row++){
		QTableWidgetItem *W;
		W=ui.tableWidgetSubtractLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetSubtractLibList->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(c->GetValue()));
		AlgorithmLibraryList	*a=LNamePacket.AList.GetItem(row);
		W=ui.tableWidgetSubtractLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetSubtractLibList->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
	}
}

void	EditColorBlockLibrary::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	ColorBlockLibrary	*ALib=dynamic_cast<ColorBlockLibrary *>(data.GetLibrary());
	ShowSubtractList(*ALib);

	ui.EditPickupRL			->setValue(ALib->PickupRL);
	ui.EditPickupRH			->setValue(ALib->PickupRH);
	ui.EditPickupGL			->setValue(ALib->PickupGL);
	ui.EditPickupGH			->setValue(ALib->PickupGH);
	ui.EditPickupBL			->setValue(ALib->PickupBL);
	ui.EditPickupBH			->setValue(ALib->PickupBH);
	ui.EditMinBlockSize		->setValue(ALib->MinBlockSize);
	ui.EditMaxBlockSize		->setValue(ALib->MaxBlockSize);
	ui.EditMinBlockDots		->setValue(ALib->MinBlockDots);
	ui.EditMaxBlockDots		->setValue(ALib->MaxBlockDots);
	ui.EditLimitBlockSize	->setValue(ALib->LimitBlockSize);
	ui.EditSpaceToOutline	->setValue(ALib->SpaceToOutline);
	ui.EditNoiseSize		->setValue(ALib->NoiseSize);
	ui.EditNoiseSizePinHole	->setValue(ALib->NoiseSizePinHole);
	ui.EditPriority			->setValue(ALib->Priority);
	ui.comboBGenerationCategory	->setCurrentIndex((int)ALib->GenerationCategory);
	ui.checkBTransparent	->setChecked(ALib->GenerationMode.Transparent);
	ui.checkBLeftPickup		->setChecked(ALib->GenerationMode.LeftPickup);
	ui.checkBOverlappedGen	->setChecked(ALib->GenerationMode.OverlappedGen);

	if(ButtonR.isChecked()==true){
		ui.EditNBrightWidthL	->setValue(ALib->InsR.NBrightWidthL);
		ui.EditNBrightWidthH	->setValue(ALib->InsR.NBrightWidthH);
		ui.EditNOKDotL			->setValue(ALib->InsR.NOKDotL);
		ui.EditNOKDotH			->setValue(ALib->InsR.NOKDotH);
		ui.EditBBrightWidthL	->setValue(ALib->InsR.BBrightWidthL);
		ui.EditBBrightWidthH	->setValue(ALib->InsR.BBrightWidthH);
		ui.EditBOKDotL			->setValue(ALib->InsR.BOKDotL);
		ui.EditBOKDotH			->setValue(ALib->InsR.BOKDotH);
		ui.EditAdjustBlack		->setValue(ALib->InsR.AdjustBlack);
		ui.EditAdjustWhite		->setValue(ALib->InsR.AdjustWhite);
		ui.EditNMinNGCountL		->setValue(ALib->InsR.NMinNGCountL);
		ui.EditNMinNGCountH		->setValue(ALib->InsR.NMinNGCountH);
		ui.EditBMinNGCountL		->setValue(ALib->InsR.BMinNGCountL);
		ui.EditBMinNGCountH		->setValue(ALib->InsR.BMinNGCountH);
		ui.EditNOKLengthL		->setValue(ALib->InsR.NOKLengthL);
		ui.EditNOKLengthH		->setValue(ALib->InsR.NOKLengthH);
		ui.EditBOKLengthL		->setValue(ALib->InsR.BOKLengthL);
		ui.EditBOKLengthH		->setValue(ALib->InsR.BOKLengthH);
	}
	else if(ButtonG.isChecked()==true){
		ui.EditNBrightWidthL	->setValue(ALib->InsG.NBrightWidthL);
		ui.EditNBrightWidthH	->setValue(ALib->InsG.NBrightWidthH);
		ui.EditNOKDotL			->setValue(ALib->InsG.NOKDotL);
		ui.EditNOKDotH			->setValue(ALib->InsG.NOKDotH);
		ui.EditBBrightWidthL	->setValue(ALib->InsG.BBrightWidthL);
		ui.EditBBrightWidthH	->setValue(ALib->InsG.BBrightWidthH);
		ui.EditBOKDotL			->setValue(ALib->InsG.BOKDotL);
		ui.EditBOKDotH			->setValue(ALib->InsG.BOKDotH);
		ui.EditAdjustBlack		->setValue(ALib->InsG.AdjustBlack);
		ui.EditAdjustWhite		->setValue(ALib->InsG.AdjustWhite);
		ui.EditNMinNGCountL		->setValue(ALib->InsG.NMinNGCountL);
		ui.EditNMinNGCountH		->setValue(ALib->InsG.NMinNGCountH);
		ui.EditBMinNGCountL		->setValue(ALib->InsG.BMinNGCountL);
		ui.EditBMinNGCountH		->setValue(ALib->InsG.BMinNGCountH);
		ui.EditNOKLengthL		->setValue(ALib->InsG.NOKLengthL);
		ui.EditNOKLengthH		->setValue(ALib->InsG.NOKLengthH);
		ui.EditBOKLengthL		->setValue(ALib->InsG.BOKLengthL);
		ui.EditBOKLengthH		->setValue(ALib->InsG.BOKLengthH);
	}
	else if(ButtonB.isChecked()==true){
		ui.EditNBrightWidthL	->setValue(ALib->InsB.NBrightWidthL);
		ui.EditNBrightWidthH	->setValue(ALib->InsB.NBrightWidthH);
		ui.EditNOKDotL			->setValue(ALib->InsB.NOKDotL);
		ui.EditNOKDotH			->setValue(ALib->InsB.NOKDotH);
		ui.EditBBrightWidthL	->setValue(ALib->InsB.BBrightWidthL);
		ui.EditBBrightWidthH	->setValue(ALib->InsB.BBrightWidthH);
		ui.EditBOKDotL			->setValue(ALib->InsB.BOKDotL);
		ui.EditBOKDotH			->setValue(ALib->InsB.BOKDotH);
		ui.EditAdjustBlack		->setValue(ALib->InsB.AdjustBlack);
		ui.EditAdjustWhite		->setValue(ALib->InsB.AdjustWhite);
		ui.EditNMinNGCountL		->setValue(ALib->InsB.NMinNGCountL);
		ui.EditNMinNGCountH		->setValue(ALib->InsB.NMinNGCountH);
		ui.EditBMinNGCountL		->setValue(ALib->InsB.BMinNGCountL);
		ui.EditBMinNGCountH		->setValue(ALib->InsB.BMinNGCountH);
		ui.EditNOKLengthL		->setValue(ALib->InsB.NOKLengthL);
		ui.EditNOKLengthH		->setValue(ALib->InsB.NOKLengthH);
		ui.EditBOKLengthL		->setValue(ALib->InsB.BOKLengthL);
		ui.EditBOKLengthH		->setValue(ALib->InsB.BOKLengthH);
	}
	ui.checkBModeEnabled	->setChecked(ALib->PointMove.ModeEnabled);
	ui.checkBModeAbsoluteBright	->setChecked(ALib->PointMove.ModeAbsoluteBright);
	ui.checkBModeNGCluster		->setChecked(ALib->PointMove.ModeNGCluster);
	ui.checkBModeDiffer			->setChecked(ALib->PointMove.ModeDiffer);
	ui.checkBModeOnlyMatching	->setChecked(ALib->PointMove.ModeOnlyMatching);
	ui.checkBModeWhiteMask		->setChecked(ALib->PointMove.ModeWhiteMask);
	ui.checkBModeBlackMask		->setChecked(ALib->PointMove.ModeBlackMask);
	ui.checkBModeCenterBrightFromParts	->setChecked(ALib->PointMove.ModeCenterBrightFromParts);
	ui.checkBModeAdjustable		->setChecked(ALib->PointMove.ModeAdjustable);
	ui.checkBModeCommonMovable	->setChecked(ALib->PointMove.ModeCommonMovable);
	ui.EditSelfSearch		->setValue(ALib->SelfSearch);
	ui.EditCommonMoveDot	->setValue(ALib->CommonMoveDot);
}

void	EditColorBlockLibrary::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	ColorBlockLibrary	*ALib=dynamic_cast<ColorBlockLibrary *>(data.GetLibrary());
	ALib->PickupRL		=ui.EditPickupRL		->value();
	ALib->PickupRH		=ui.EditPickupRH		->value();
	ALib->PickupGL		=ui.EditPickupGL		->value();
	ALib->PickupGH		=ui.EditPickupGH		->value();
	ALib->PickupBL		=ui.EditPickupBL		->value();
	ALib->PickupBH		=ui.EditPickupBH		->value();
	ALib->MinBlockSize	=ui.EditMinBlockSize	->value();
	ALib->MaxBlockSize	=ui.EditMaxBlockSize	->value();
	ALib->MinBlockDots	=ui.EditMinBlockDots	->value();
	ALib->MaxBlockDots	=ui.EditMaxBlockDots	->value();
	ALib->LimitBlockSize=ui.EditLimitBlockSize	->value();
	ALib->SpaceToOutline=ui.EditSpaceToOutline	->value();
	ALib->NoiseSize		=ui.EditNoiseSize		->value();
	ALib->NoiseSizePinHole	=ui.EditNoiseSizePinHole->value();
	ALib->Priority		=ui.EditPriority		->value();
	ALib->GenerationCategory	=(ColorBlockLibrary::_GenerationCategory)ui.comboBGenerationCategory	->currentIndex();
	ALib->GenerationMode.Transparent	=ui.checkBTransparent	->isChecked();
	ALib->GenerationMode.LeftPickup		=ui.checkBLeftPickup	->isChecked();
	ALib->GenerationMode.OverlappedGen=ui.checkBOverlappedGen->isChecked();

	if(CurrentColor==0){
		ALib->InsR.NBrightWidthL=ui.EditNBrightWidthL	->value();
		ALib->InsR.NBrightWidthH=ui.EditNBrightWidthH	->value();
		ALib->InsR.NOKDotL		=ui.EditNOKDotL			->value();
		ALib->InsR.NOKDotH		=ui.EditNOKDotH			->value();
		ALib->InsR.BBrightWidthL=ui.EditBBrightWidthL	->value();
		ALib->InsR.BBrightWidthH=ui.EditBBrightWidthH	->value();
		ALib->InsR.BOKDotL		=ui.EditBOKDotL			->value();
		ALib->InsR.BOKDotH		=ui.EditBOKDotH			->value();
		ALib->InsR.AdjustBlack	=ui.EditAdjustBlack		->value();
		ALib->InsR.AdjustWhite	=ui.EditAdjustWhite		->value();
		ALib->InsR.NMinNGCountL	=ui.EditNMinNGCountL	->value();
		ALib->InsR.NMinNGCountH	=ui.EditNMinNGCountH	->value();
		ALib->InsR.BMinNGCountL	=ui.EditBMinNGCountL	->value();
		ALib->InsR.BMinNGCountH	=ui.EditBMinNGCountH	->value();
		ALib->InsR.NOKLengthL	=ui.EditNOKLengthL		->value();
		ALib->InsR.NOKLengthH	=ui.EditNOKLengthH		->value();
		ALib->InsR.BOKLengthL	=ui.EditBOKLengthL		->value();
		ALib->InsR.BOKLengthH	=ui.EditBOKLengthH		->value();
	}
	else if(CurrentColor==1){
		ALib->InsG.NBrightWidthL=ui.EditNBrightWidthL	->value();
		ALib->InsG.NBrightWidthH=ui.EditNBrightWidthH	->value();
		ALib->InsG.NOKDotL		=ui.EditNOKDotL			->value();
		ALib->InsG.NOKDotH		=ui.EditNOKDotH			->value();
		ALib->InsG.BBrightWidthL=ui.EditBBrightWidthL	->value();
		ALib->InsG.BBrightWidthH=ui.EditBBrightWidthH	->value();
		ALib->InsG.BOKDotL		=ui.EditBOKDotL			->value();
		ALib->InsG.BOKDotH		=ui.EditBOKDotH			->value();
		ALib->InsG.AdjustBlack	=ui.EditAdjustBlack		->value();
		ALib->InsG.AdjustWhite	=ui.EditAdjustWhite		->value();
		ALib->InsG.NMinNGCountL	=ui.EditNMinNGCountL	->value();
		ALib->InsG.NMinNGCountH	=ui.EditNMinNGCountH	->value();
		ALib->InsG.BMinNGCountL	=ui.EditBMinNGCountL	->value();
		ALib->InsG.BMinNGCountH	=ui.EditBMinNGCountH	->value();
		ALib->InsG.NOKLengthL	=ui.EditNOKLengthL		->value();
		ALib->InsG.NOKLengthH	=ui.EditNOKLengthH		->value();
		ALib->InsG.BOKLengthL	=ui.EditBOKLengthL		->value();
		ALib->InsG.BOKLengthH	=ui.EditBOKLengthH		->value();
	}
	else if(CurrentColor==2){
		ALib->InsB.NBrightWidthL=ui.EditNBrightWidthL	->value();
		ALib->InsB.NBrightWidthH=ui.EditNBrightWidthH	->value();
		ALib->InsB.NOKDotL		=ui.EditNOKDotL			->value();
		ALib->InsB.NOKDotH		=ui.EditNOKDotH			->value();
		ALib->InsB.BBrightWidthL=ui.EditBBrightWidthL	->value();
		ALib->InsB.BBrightWidthH=ui.EditBBrightWidthH	->value();
		ALib->InsB.BOKDotL		=ui.EditBOKDotL			->value();
		ALib->InsB.BOKDotH		=ui.EditBOKDotH			->value();
		ALib->InsB.AdjustBlack	=ui.EditAdjustBlack		->value();
		ALib->InsB.AdjustWhite	=ui.EditAdjustWhite		->value();
		ALib->InsB.NMinNGCountL	=ui.EditNMinNGCountL	->value();
		ALib->InsB.NMinNGCountH	=ui.EditNMinNGCountH	->value();
		ALib->InsB.BMinNGCountL	=ui.EditBMinNGCountL	->value();
		ALib->InsB.BMinNGCountH	=ui.EditBMinNGCountH	->value();
		ALib->InsB.NOKLengthL	=ui.EditNOKLengthL		->value();
		ALib->InsB.NOKLengthH	=ui.EditNOKLengthH		->value();
		ALib->InsB.BOKLengthL	=ui.EditBOKLengthL		->value();
		ALib->InsB.BOKLengthH	=ui.EditBOKLengthH		->value();
	}
	ALib->PointMove.ModeEnabled				=ui.checkBModeEnabled			->isChecked();
	ALib->PointMove.ModeAbsoluteBright		=ui.checkBModeAbsoluteBright	->isChecked();
	ALib->PointMove.ModeNGCluster			=ui.checkBModeNGCluster			->isChecked();
	ALib->PointMove.ModeDiffer				=ui.checkBModeDiffer			->isChecked();
	ALib->PointMove.ModeOnlyMatching		=ui.checkBModeOnlyMatching		->isChecked();
	ALib->PointMove.ModeWhiteMask			=ui.checkBModeWhiteMask			->isChecked();
	ALib->PointMove.ModeBlackMask			=ui.checkBModeBlackMask			->isChecked();
	ALib->PointMove.ModeCenterBrightFromParts=ui.checkBModeCenterBrightFromParts	->isChecked();
	ALib->PointMove.ModeAdjustable			=ui.checkBModeAdjustable		->isChecked();
	ALib->PointMove.ModeCommonMovable		=ui.checkBModeCommonMovable	->isChecked();
	ALib->SelfSearch						=ui.EditSelfSearch		->value();
	ALib->CommonMoveDot						=ui.EditCommonMoveDot	->value();
}

void EditColorBlockLibrary::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void EditColorBlockLibrary::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(EditColorBlockLibrary_LS,LID_48)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(EditColorBlockLibrary_LS,LID_49)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		ColorBlockBase	*BBase=GetColorBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditColorBlockLibrary::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditColorBlockLibrary_LS,LID_50)/*"Warning"*/, LangSolver.GetString(EditColorBlockLibrary_LS,LID_51)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertColorBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	ColorBlockBase	*BBase=GetColorBlockBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditColorBlockLibrary::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditColorBlockLibrary_LS,LID_52)/*"Warning"*/, LangSolver.GetString(EditColorBlockLibrary_LS,LID_53)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);
		CmdInsertColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		ColorBlockBase	*BBase=GetColorBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		ColorBlockBase	*BBase=GetColorBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditColorBlockLibrary::on_pushButtonClose_clicked()
{
	close();
}

void EditColorBlockLibrary::on_toolButtonPickup_clicked()
{
	if(ui.toolButtonPickup->isChecked()==true)
		ui.stackedWidget->setCurrentIndex(0);
}

void EditColorBlockLibrary::on_toolButtonInspect_clicked()
{
	if(ui.toolButtonInspect->isChecked()==true)
		ui.stackedWidget->setCurrentIndex(1);
}

void EditColorBlockLibrary::on_toolButtonR_clicked()
{
	GetLibraryFromWindow(*TempLib);
	CurrentColor=0;
	ShowLibrary(*TempLib);
}


void EditColorBlockLibrary::on_toolButtonG_clicked()
{
	GetLibraryFromWindow(*TempLib);
	CurrentColor=1;
	ShowLibrary(*TempLib);
}

void EditColorBlockLibrary::on_toolButtonB_clicked()
{
	GetLibraryFromWindow(*TempLib);
	CurrentColor=2;
	ShowLibrary(*TempLib);
}

void EditColorBlockLibrary::on_ToolButton_clicked()
{
	GetLibraryFromWindow(*TempLib);
	if(ButtonR.isChecked()==true)
		CurrentColor=0;
	else if(ButtonG.isChecked()==true)
		CurrentColor=1;
	else if(ButtonB.isChecked()==true)
		CurrentColor=2;
	ShowLibrary(*TempLib);
}
