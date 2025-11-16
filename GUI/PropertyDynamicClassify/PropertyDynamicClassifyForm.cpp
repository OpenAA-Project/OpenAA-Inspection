#include "EditDynamicClassifyLibraryResource.h"
#include "PropertyDynamicClassifyForm.h"
#include "EditDynamicClassifyLibrary.h"
#include "XDynamicClassifyPacket.h"
#include "PickupColorForm.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyDynamicClassifyForm::PropertyDynamicClassifyForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LibFolderID =-1;
	DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);
	ui.tableWidgetGeneratedLibList	->setColumnWidth (0, 30);
	ui.tableWidgetGeneratedLibList	->setColumnWidth (1, 80);	

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempDynamicClassifyLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
}

PropertyDynamicClassifyForm::~PropertyDynamicClassifyForm()
{

}
	
DynamicClassifyBase	*PropertyDynamicClassifyForm::GetDynamicClassifyBase(void)
{
	return (DynamicClassifyBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DynamicClassify");
}

void	PropertyDynamicClassifyForm::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReqDynamicClassifyDrawMode	*GUICmdReqDynamicClassifyDrawModeVar=dynamic_cast<GUICmdReqDynamicClassifyDrawMode *>(packet);
	if(GUICmdReqDynamicClassifyDrawModeVar!=NULL){
		if(ui.toolButtonCoreArea->isChecked()==true)
			GUICmdReqDynamicClassifyDrawModeVar->ShowCore=true;
		else
			GUICmdReqDynamicClassifyDrawModeVar->ShowCore=false;

		if(ui.toolButtonMaxZone->isChecked()==true)
			GUICmdReqDynamicClassifyDrawModeVar->ShowMaxZone=true;
		else
			GUICmdReqDynamicClassifyDrawModeVar->ShowMaxZone=false;

		if(ui.toolButtonMinZone->isChecked()==true)
			GUICmdReqDynamicClassifyDrawModeVar->ShowMinZone=true;
		else
			GUICmdReqDynamicClassifyDrawModeVar->ShowMinZone=false;

		if(ui.toolButtonBareArea->isChecked()==true)
			GUICmdReqDynamicClassifyDrawModeVar->ShowBare=true;
		else
			GUICmdReqDynamicClassifyDrawModeVar->ShowBare=false;

		if(ui.toolButtonInsideArea->isChecked()==true)
			GUICmdReqDynamicClassifyDrawModeVar->ShowInside=true;
		else
			GUICmdReqDynamicClassifyDrawModeVar->ShowInside=false;

		if(ui.toolButtonCoreArea->isChecked()==true)
			GUICmdReqDynamicClassifyDrawModeVar->ShowCore=true;
		else
			GUICmdReqDynamicClassifyDrawModeVar->ShowCore=false;

		if(ui.toolButtonOutlineIArea->isChecked()==true)
			GUICmdReqDynamicClassifyDrawModeVar->ShowOutlineI=true;
		else
			GUICmdReqDynamicClassifyDrawModeVar->ShowOutlineI=false;

		if(ui.toolButtonOutlineTArea->isChecked()==true)
			GUICmdReqDynamicClassifyDrawModeVar->ShowOutlineT=true;
		else
			GUICmdReqDynamicClassifyDrawModeVar->ShowOutlineT=false;

		if(ui.toolButtonOutlineOArea->isChecked()==true)
			GUICmdReqDynamicClassifyDrawModeVar->ShowOutlineO=true;
		else
			GUICmdReqDynamicClassifyDrawModeVar->ShowOutlineO=false;
		return;
	}

	CmdDynamicClassifyDrawEnd	*CmdDynamicClassifyDrawEndVar=dynamic_cast<CmdDynamicClassifyDrawEnd *>(packet);
	if(CmdDynamicClassifyDrawEndVar!=NULL){
		//GlobalPickupArea+=BlockDEnd->Area;
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(CmdDynamicClassifyDrawEndVar->GlobalArea,PageList);
		if(PageList.GetFirst()==NULL){
			return;
		}
		RGBStock	RGBColors;
		for(IntClass *PageClass=PageList.GetFirst();PageClass!=NULL;PageClass=PageClass->GetNext()){
			int	globalPage=PageClass->GetValue();
			FlexArea	A;
			//A=GlobalPickupArea;
			A=CmdDynamicClassifyDrawEndVar->GlobalArea;
			GetLayersBase()->GetPageData(globalPage)->ClipMoveAreaFromGlobal(A);

			GUICmdReqRGBStockFromArea	RCmd(GetLayersBase(),sRoot,sName,globalPage);
			GUICmdSendRGBStockFromArea	SCmd(GetLayersBase(),sRoot,sName,globalPage);
			RCmd.Area=A;
			RCmd.Send(globalPage,0,SCmd);
			RGBColors+=SCmd.RGBColors;
		}
		PickupColorForm	D(GetLayersBase()
							,&RGBColors
							,&ColorGenerator.Cube
							,this);
		if(D.exec()==(int)true){
			ColorGenerator.Cube=D.ColorPanel.Cube;
			ColorGenerator.InitializedDoneCube();
			ColorGenerator.Repaint();
			DynamicClassifyLibrary	*ALib=dynamic_cast<DynamicClassifyLibrary *>(TempLib->GetLibrary());
			ALib->PickupColor	=D.ColorPanel.Cube;
		}
		return;
	}

	CmdSetDynamicClassifyShowingState	*CmdSetDynamicClassifyShowingStateVar=dynamic_cast<CmdSetDynamicClassifyShowingState *>(packet);
	if(CmdSetDynamicClassifyShowingStateVar!=NULL){
		ShowAreaList();
		ui.toolButtonCoreArea		->setChecked(CmdSetDynamicClassifyShowingStateVar->ModeCoreArea);
		ui.toolButtonMaxZone		->setChecked(CmdSetDynamicClassifyShowingStateVar->ModeMaxZone);
		ui.toolButtonMinZone		->setChecked(CmdSetDynamicClassifyShowingStateVar->ModeMinZone);
		ui.toolButtonBareArea		->setChecked(CmdSetDynamicClassifyShowingStateVar->ModeBareArea);
		ui.toolButtonInsideArea		->setChecked(CmdSetDynamicClassifyShowingStateVar->ModeInsideArea);
		ui.toolButtonOutlineIArea	->setChecked(CmdSetDynamicClassifyShowingStateVar->ModeOutlineIArea);
		ui.toolButtonOutlineTArea	->setChecked(CmdSetDynamicClassifyShowingStateVar->ModeOutlineTArea);
		ui.toolButtonOutlineOArea	->setChecked(CmdSetDynamicClassifyShowingStateVar->ModeOutlineOArea);

		ui.tableWidgetAreaList->clearSelection();
		for(IntClass *c=CmdSetDynamicClassifyShowingStateVar->ShowingLibIDs.GetFirst();c!=NULL;c=c->GetNext()){
			int	Row=0;
			for(DClassifyInfoList *b=DCInfos.GetFirst();b!=NULL;b=b->GetNext(),Row++){
				if(b->ID==c->GetValue()){
					break;
				}
			}
			//for(int Col=0;Col<ui.tableWidgetAreaList->columnCount();Col++){
			//	QTableWidgetItem *Item=ui.tableWidgetAreaList->item (Row, Col);
			//	Item->setSelected(true);
			//}
		}
		return;
	}

	CmdDynamicClassifyGenerate	*CmdDynamicClassifyGenerateVar=dynamic_cast<CmdDynamicClassifyGenerate *>(packet);
	if(CmdDynamicClassifyGenerateVar!=NULL){
		//Generate
		on_ButtonGenerateLibs_clicked();
/*
		if(TempLib==NULL){
			return;
		}
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			GUICmdGenerateDynamicClassifys	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
			Cmd.LibList		=SelectedLibList.GetIDList();
			Cmd.Send(NULL,page,0);
		}
*/
		return;
	}
}

void	PropertyDynamicClassifyForm::ShowLibList(void)
{
	ui.tableWidgetLibList->setRowCount(0);
	DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
	if(BBase!=NULL){
		CmdGetDynamicClassifyLibraryListPacket	Packet(GetLayersBase());
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

void	PropertyDynamicClassifyForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
	if(BBase!=NULL){
		CmdCreateTempDynamicClassifyLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadDynamicClassifyLibraryPacket	Packet(GetLayersBase());
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

void PropertyDynamicClassifyForm::ShowAreaList(void)
{
	DCInfos.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqDynamicClassifyInfo	RCmd(GetLayersBase(),sRoot,sName,page);
		GUICmdSendDynamicClassifyInfo	SCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.Send(page,0,SCmd);
		for(DClassifyInfoList *a=SCmd.DCInfoData.GetFirst();a!=NULL;a=a->GetNext()){
			DClassifyInfoList *b;
			for(b=DCInfos.GetFirst();b!=NULL;b=b->GetNext()){
				if(a->ID==b->ID){
					break;
				}
			}
			if(b==NULL){
				DCInfos.AppendList(new DClassifyInfoList(*a));
			}
		}
	}

	DynamicClassifyBase *PBase=(DynamicClassifyBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DynamicClassify");
	ui.tableWidgetAreaList->setRowCount(DCInfos.GetCount());
	int	Row=0;
	for(DClassifyInfoList *b=DCInfos.GetFirst();b!=NULL;b=b->GetNext(),Row++){
		SetDataToTable(ui.tableWidgetAreaList ,0,Row ,b->ID);
		CmdGetDynamicClassifyLibraryNamePacket	GCmd(GetLayersBase());
		GCmd.LibID=b->ID;
		PBase->TransmitDirectly(&GCmd);
		if(GCmd.Success==true){
			SetDataToTable(ui.tableWidgetAreaList ,1,Row ,GCmd.LibName);
		}
		else{
			SetDataToTable(ui.tableWidgetAreaList ,1,Row ,/**/"");
		}
		//SetDataToTable(ui.tableWidgetAreaList ,2,Row ,b->MinDiameter);
		//SetDataToTable(ui.tableWidgetAreaList ,3,Row ,b->MaxDiameter);
	}

	if(DCInfos.GetFirst()!=NULL){
		TempLib->SetLibID(DCInfos.GetFirst()->ID);
		CmdLoadDynamicClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, LangSolver.GetString(PropertyDynamicClassifyForm_LS,LID_8)/*"Library error"*/
											, LangSolver.GetString(PropertyDynamicClassifyForm_LS,LID_9)/*"Not loaded this library record"*/);
			}
		}
	}
}

void	PropertyDynamicClassifyForm::BuildForShow(void)
{
	ShowAreaList();
	on_ButtonLibSave_clicked();

	//tableWidgetLibList‚ÌList‚ð‘I‘ð‚³‚¹‚é
	if(ui.tableWidgetLibList->rowCount()>0){
		ui.tableWidgetLibList->selectRow(0);
	}
	on_pushButtonSetFrom_clicked();
}

void PropertyDynamicClassifyForm::on_toolButtonCoreArea_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/"");
	GProp->Repaint();
}

void PropertyDynamicClassifyForm::on_toolButtonMaxZone_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/"");
	GProp->Repaint();
}

void PropertyDynamicClassifyForm::on_toolButtonMinZone_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/"");
	GProp->Repaint();
}

void PropertyDynamicClassifyForm::on_toolButtonOutlineIArea_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/"");
	GProp->Repaint();
}

void PropertyDynamicClassifyForm::on_toolButtonOutlineTArea_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/"");
	GProp->Repaint();
}

void PropertyDynamicClassifyForm::on_toolButtonOutlineOArea_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/"");
	GProp->Repaint();
}

void PropertyDynamicClassifyForm::on_toolButtonBareArea_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/"");
	GProp->Repaint();
}

void PropertyDynamicClassifyForm::on_toolButtonInsideArea_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/"");
	GProp->Repaint();
}

void PropertyDynamicClassifyForm::on_pushButtonEditLibFolder_clicked()
{
	DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyDynamicClassifyForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui.labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void	PropertyDynamicClassifyForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	DynamicClassifyLibrary	*ALib=dynamic_cast<DynamicClassifyLibrary *>(data.GetLibrary());
	ColorGenerator.Cube=ALib->PickupColor;
	ColorGenerator.InitializedDoneCube();
	ColorGenerator.Repaint();

	ui.EditMinBlockSize		->setValue(ALib->MinAreaSize);
	ui.EditMaxBlockSize		->setValue(ALib->MaxAreaSize);
	ui.EditMinBlockDots		->setValue(ALib->MinAreaDots);
	ui.EditMaxBlockDots		->setValue(ALib->MaxAreaDots);
	
	ui.EditNoiseSize		->setValue(ALib->NoiseDot	);
	ui.EditShrinkDot		->setValue(ALib->ShrinkDot	);
	ui.EditPriority			->setValue(ALib->Priority	);
	ui.EditVariableWidth	->setValue(ALib->VariableWidth);
}

void	PropertyDynamicClassifyForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());
	DynamicClassifyLibrary	*ALib=dynamic_cast<DynamicClassifyLibrary *>(data.GetLibrary());

	ALib->MinAreaSize		=ui.EditMinBlockSize		->value();
	ALib->MaxAreaSize		=ui.EditMaxBlockSize		->value();
	ALib->MinAreaDots		=ui.EditMinBlockDots		->value();
	ALib->MaxAreaDots		=ui.EditMaxBlockDots		->value();
	
	ALib->NoiseDot			=ui.EditNoiseSize			->value();
	ALib->ShrinkDot			=ui.EditShrinkDot			->value();
	ALib->Priority			=ui.EditPriority			->value();
	ALib->VariableWidth		=ui.EditVariableWidth		->value();
}

void PropertyDynamicClassifyForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadDynamicClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, LangSolver.GetString(PropertyDynamicClassifyForm_LS,LID_10)/*"Library error"*/
											, LangSolver.GetString(PropertyDynamicClassifyForm_LS,LID_11)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyDynamicClassifyForm::on_tableWidgetLibList_doubleClicked(QModelIndex)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyDynamicClassifyForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadDynamicClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, LangSolver.GetString(PropertyDynamicClassifyForm_LS,LID_12)/*"Library error"*/
											, LangSolver.GetString(PropertyDynamicClassifyForm_LS,LID_13)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyDynamicClassifyForm::on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex)
{
	on_pushButtonGetBack_clicked();
}

void PropertyDynamicClassifyForm::on_pushButtonSetFrom_clicked()
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

void PropertyDynamicClassifyForm::on_pushButtonGetBack_clicked()
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

void PropertyDynamicClassifyForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyDynamicClassifyForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyDynamicClassifyForm::on_pushButtonEditLibrary_clicked()
{
	EditDynamicClassifyLibrary	D(GetLayersBase(),this);
	D.exec();

	ShowLibList();
	if(TempLib!=NULL){
		CmdLoadDynamicClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
		}
	}

}

void PropertyDynamicClassifyForm::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyDynamicClassifyForm_LS,LID_14)/*"Pickup Test"*/);

	GetLibraryFromWindow(*TempLib);

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.LibPoint	=TempLib;
		Cmd.SendOnly(page,0);
	}

	GetLayersBase()->CloseProcessingForm();
}

void PropertyDynamicClassifyForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.Send(NULL,page,0);
	}
}

void PropertyDynamicClassifyForm::on_ButtonGenerateLibs_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyDynamicClassifyForm_LS,LID_15)/*"Generating items"*/,GetLayersBase()->GetPageNumb()*10);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		GUICmdGenerateDynamicClassifys	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyDynamicClassifyForm::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL || TempLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
												, LangSolver.GetString(PropertyDynamicClassifyForm_LS,LID_16)/*"Warning"*/
												, LangSolver.GetString(PropertyDynamicClassifyForm_LS,LID_17)/*"No Library Name"*/
												, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateDynamicClassifyLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
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

