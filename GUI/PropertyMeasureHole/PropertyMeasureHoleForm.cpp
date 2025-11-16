#include "CreateManualMeasureHoleFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMeasureHole\PropertyMeasureHoleForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyMeasureHoleForm.h"
#include "CreateManualMeasureHoleForm.h"
#include "XMeasureHolePacket.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyMeasureHoleForm::PropertyMeasureHoleForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);

	LibFolderID =-1;
	MeasureHoleBase	*BBase=GetMeasureHoleBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempMeasureHoleLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ColorGenerator	.setParent(ui.frameColorCube);
	ColorGenerator	.Fit(ui.frameColorCube);

	if(GetLayerNumb(0)>=3){
		ui.stackedWidget->setCurrentIndex(1);
	}
	else if(GetLayerNumb(0)>=3){
		ui.stackedWidget->setCurrentIndex(0);
	}
}

PropertyMeasureHoleForm::~PropertyMeasureHoleForm()
{
	if(TempLib!=NULL)
		delete	TempLib;
}

MeasureHoleBase	*PropertyMeasureHoleForm::GetMeasureHoleBase(void)
{
	return (MeasureHoleBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHole");
}

void	PropertyMeasureHoleForm::BuildForShow(void)
{
}

void	PropertyMeasureHoleForm::TransmitDirectly(GUIDirectMessage *packet)
{
	MeasureHoleBase	*BBase=GetMeasureHoleBase();

	CmdMeasureHoleDrawEnd	*BlockDEnd=dynamic_cast<CmdMeasureHoleDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		CreateManualMeasureHoleForm	D(GetLayersBase(),NULL);
		if(D.exec()==(int)true){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=BlockDEnd->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					GUICmdSendAddManualMeasureHole	Cmd(GetLayersBase(),sRoot,sName,page);
					Cmd.Area=A;
					CmdCreateByteArrayFromMeasureHoleItemPacket	BCmd(GetLayersBase());
					BCmd.Point=D.BItem;
					BBase->TransmitDirectly(&BCmd);
					Cmd.BItem=BCmd.Buff;
					Cmd.Send(NULL,page,0);
				}
			}
		}
	}
	GUICmdMeasureHoleGetColorMap	*GUICmdMeasureHoleGetColorMapVar=dynamic_cast<GUICmdMeasureHoleGetColorMap *>(packet);
	if(GUICmdMeasureHoleGetColorMapVar!=NULL){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(GUICmdMeasureHoleGetColorMapVar->Area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			int	page=P->GetValue();
			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
			FlexArea	A=GUICmdMeasureHoleGetColorMapVar->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				CmdReqMeasureHoleColorMap	RCmd(GetLayersBase(),sRoot,sName,page);
				CmdAckMeasureHoleColorMap	ACmd(GetLayersBase(),sRoot,sName,page);
				RCmd.Area=A;
				RCmd.Send(page,0,ACmd);

				ColorGenerator.Cube=ACmd.Color;
				ColorGenerator.InitializedDoneCube();
				ColorGenerator.Repaint();
			}
		}
	}
}


void	PropertyMeasureHoleForm::ShowLibList(void)
{
	ui.tableWidgetLibList->setRowCount(0);
	MeasureHoleBase	*BBase=GetMeasureHoleBase();
	if(BBase!=NULL){
		CmdGetMeasureHoleLibraryListPacket	Packet(GetLayersBase());
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

			W=ui.tableWidgetLibList->item ( row, 2);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 2,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			//W->setText(QString::number(a->MinDiameter));

			W=ui.tableWidgetLibList->item ( row, 3);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 3,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			//W->setText(QString::number(a->MaxDiameter));
		}
	}
}
void PropertyMeasureHoleForm::on_pushButtonEditLibFolder_clicked()
{
	MeasureHoleBase	*BBase=GetMeasureHoleBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyMeasureHoleForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui.labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void PropertyMeasureHoleForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadMeasureHoleLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MeasureHoleBase	*BBase=GetMeasureHoleBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(PropertyMeasureHoleForm_LS,LID_2)/*"Library error"*/, LangSolver.GetString(PropertyMeasureHoleForm_LS,LID_3)/*"Not loaded this library record"*/);
			}
		}
	}
}

void	PropertyMeasureHoleForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	MeasureHoleLibrary	*ALib=dynamic_cast<MeasureHoleLibrary *>(data.GetLibrary());
	if(GetLayerNumb(0)>=3){
		ColorGenerator.Cube=ALib->CupperColor;
		ColorGenerator.InitializedDoneCube();
		ColorGenerator.Repaint();
	}
	else{
		int	ColL,ColH;
		ALib->CupperColor.GetMonoColorRange(ColL,ColH);
		ui.EditPickupL	->setValue(ColL);
		ui.EditPickupH	->setValue(ColH);
	}

	ui.EditMinDiameter	->setValue(ALib->MinDiameter);
	ui.EditMaxDiameter	->setValue(ALib->MaxDiameter);
	ui.EditNoiseSize	->setValue(ALib->NoiseSize);
	ui.EditSearchDot	->setValue(ALib->SearchDot);
}

void	PropertyMeasureHoleForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	MeasureHoleLibrary	*ALib=dynamic_cast<MeasureHoleLibrary *>(data.GetLibrary());
	ALib->MinDiameter	=ui.EditMinDiameter	->value();
	ALib->MaxDiameter	=ui.EditMaxDiameter	->value();
	ALib->NoiseSize		=ui.EditNoiseSize	->value();
	ALib->SearchDot		=ui.EditSearchDot	->value();

	if(GetLayerNumb(0)>=3){
		ALib->CupperColor	=ColorGenerator.Cube;
	}
	else{
		int	ColL=ui.EditPickupL	->value();
		int	ColH=ui.EditPickupH	->value();
		ALib->CupperColor.SetMonoColorRange(ColL,ColH,ColL,ColH,ColL,ColH);
	}
}

void PropertyMeasureHoleForm::on_pushButtonCreateNew_clicked()
{
	GetLibraryFromWindow(*TempLib);
	CmdInsertMeasureHoleLibraryPacket	Cmd(GetLayersBase());
	Cmd.Point=TempLib;
	TempLib->SetLibFolderID(LibFolderID);
	MeasureHoleBase	*BBase=GetMeasureHoleBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Cmd);
	}
	ShowLibList();
}

void PropertyMeasureHoleForm::on_pushButtonUpdate_clicked()
{
	GetLibraryFromWindow(*TempLib);
	CmdUpdateMeasureHoleLibraryPacket	Cmd(GetLayersBase());
	Cmd.Point=TempLib;
	TempLib->SetLibFolderID(LibFolderID);
	MeasureHoleBase	*BBase=GetMeasureHoleBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Cmd);
	}
	ShowLibList();
}
void PropertyMeasureHoleForm::on_pushButtonCreateNewMono_clicked()
{
	on_pushButtonCreateNew_clicked();
}

void PropertyMeasureHoleForm::on_pushButtonUpdateMono_clicked()
{
	on_pushButtonUpdate_clicked();
}
