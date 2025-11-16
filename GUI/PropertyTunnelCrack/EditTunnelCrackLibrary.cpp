#include "CreateTunnelFormResource.h"
#include "EditTunnelCrackLibrary.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
//#include "XGUI.h"
#include "XGeneralDialog.h"

EditTunnelCrackLibrary::EditTunnelCrackLibrary(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);

	LibFolderID =-1;
	TunnelCrackBase	*BBase=GetTunnelCrackBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempTunnelCrackLibraryPacket	Packet;
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

EditTunnelCrackLibrary::~EditTunnelCrackLibrary()
{
	if(TempLib!=NULL){
		delete	TempLib;
		TempLib=NULL;
	}
}
TunnelCrackBase	*EditTunnelCrackLibrary::GetTunnelCrackBase(void)
{
	return (TunnelCrackBase *)GetLayersBase()->GetAlgorithmBase(/**/"Customized",/**/"TunnelCrack");
}

void	EditTunnelCrackLibrary::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	TunnelCrackBase	*BBase=GetTunnelCrackBase();
	if(BBase!=NULL){
		CmdGetTunnelCrackLibraryListPacket	Packet;
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

void	EditTunnelCrackLibrary::GetLibraryFromWindow(TunnelCrackLibrary &data)
{
	data.SetLibName(ui.EditLibName	->text());
	data.LibData.Item1.Enabled			=ui.checkBoxItem1Enabled->isChecked();
	data.LibData.Item1.LengthLow		=ui.spinBoxItem1LengthLow->value();
	data.LibData.Item1.WidthL			=ui.spinBoxItem1WidthL->value();
	data.LibData.Item1.WidthH			=ui.spinBoxItem1WidthH->value();
	data.LibData.Item1.CrackNo			=ui.spinBoxItem1CrackNo->value();
	data.LibData.Item1.CrackWidth		=ui.spinBoxItem1CrackWidth->value();
	data.LibData.Item1.CrackCenterValue	=ui.spinBoxItem1CrackCenterValue->value();
	data.LibData.Item1.CrackResultValue	=ui.spinBoxItem1CrackResultValue->value();

	data.LibData.Item2.Enabled	=ui.checkBoxItem2Enabled->isChecked();
	data.LibData.Item2.LengthLow=ui.spinBoxItem2LengthLow->value();
	bool	Ok;
	data.LibData.Item2.Gain		=ui.lineEditItem2Gain->text().toDouble(&Ok);
	if(Ok==false)
		data.LibData.Item2.Gain=1.0;
	data.LibData.Item2.VarL		=ui.spinBoxItem2VarL->value();
	data.LibData.Item2.VarH		=ui.spinBoxItem2VarH->value();

	data.LibData.Item3.Enabled	=ui.checkBoxItem3Enabled->isChecked();
	data.LibData.Item3.LengthLow=ui.spinBoxItem3LengthLow->value();
	data.LibData.Item3.Gain		=ui.lineEditItem3Gain->text().toDouble(&Ok);
	if(Ok==false)
		data.LibData.Item3.Gain=1.0;

	data.LibData.Item4.Enabled	=ui.checkBoxItem4Enabled->isChecked();
	data.LibData.Item4.LengthLow=ui.spinBoxItem4LengthLow->value();
	data.LibData.Item4.Gain		=ui.lineEditItem4Gain->text().toDouble(&Ok);
	if(Ok==false)
		data.LibData.Item4.Gain=1.0;

	data.LibData.Item5.Enabled	=ui.checkBoxItem5Enabled->isChecked();
	data.LibData.Item5.LengthLow=ui.spinBoxItem5LengthLow->value();
	//Cmd.Item5.Gain		=ui.lineEditItem5Gain->text().toDouble(&Ok);
	if(Ok==false)
		data.LibData.Item5.Gain=1.0;

	data.LibData.BinarizedBlockSize		=ui.spinBoxBinarizedBlockSize->value();
	data.LibData.BinarizedOutsideLRate	=ui.doubleSpinBoxBinarizedOutsideLRate->value();
	data.LibData.BinarizedOutsideHRate	=ui.doubleSpinBoxBinarizedOutsideHRate->value();
	data.LibData.BinarizedAlpha			=ui.doubleSpinBoxBinarizedAlpha->value();
	data.LibData.BinarizedThickness		=ui.spinBoxBinarizedThickness->value();
	data.LibData.BinarizedMinDot		=ui.spinBoxBinarizedMinDot->value();

	data.LibData.Item7.Enabled			=ui.checkBoxItem7Enabled->isChecked();
	data.LibData.Item7.BrightnessCable	=ui.spinBoxItem7BrightnessCable	->value();
	data.LibData.Item7.EnlargeCable		=ui.spinBoxItem7EnlargeCable		->value();
	data.LibData.Item7.EnsmallCable		=ui.spinBoxItem7EnsmallCable		->value();
	data.LibData.Item7.BrightnessMetal	=ui.spinBoxItem7BrightnessMetal	->value();
	data.LibData.Item7.EnlargeMetal		=ui.spinBoxItem7EnlargeMetal		->value();
	data.LibData.Item7.EnsmallMetal		=ui.spinBoxItem7EnsmallMetal		->value();
	data.LibData.Item7.BrightnessPanelL	=ui.spinBoxItem7BrightnessPanelL	->value();
	data.LibData.Item7.BrightnessPanelH	=ui.spinBoxItem7BrightnessPanelH	->value();
	data.LibData.Item7.LineDotPanel		=ui.spinBoxItem7LineDotPanel		->value();

	data.LibData.Item8.Enabled			=ui.checkBoxItem8Enabled->isChecked();
	//data.LibData.Item8.Brightness		=ui.spinBoxItem8Brightness		->value();
	data.LibData.Item8.MinimumDot		=ui.spinBoxItem8MinimumDot		->value();
	data.LibData.Item8.ThresholdDiffL	=ui.spinBoxItem8ThresholdDiffL	->value();
	data.LibData.Item8.ThresholdDiffH	=ui.spinBoxItem8ThresholdDiffH	->value();
	data.LibData.Item8.ShiftXY			=ui.spinBoxItem8ShiftXY			->value();
	/*
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase("Customized" ,"TunnelCrack");
	if(L==NULL)
		return;
	AlgorithmInPagePLI	 *PData=(AlgorithmInPagePLI *)L->GetPageData(0);
	if(PData==NULL)
		return;
	AlgorithmInLayerRoot *LData=PData->GetLayerData(0);

	LData->TransmitDirectly(&Cmd);
	*/
}

void EditTunnelCrackLibrary::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearTunnelCrackLibraryPacket	Packet;
	Packet.Point=TempLib;
	TunnelCrackBase	*BBase=GetTunnelCrackBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void EditTunnelCrackLibrary::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(EditTunnelCrackLibrary_LS,LID_0)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(EditTunnelCrackLibrary_LS,LID_1)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteTunnelCrackLibraryPacket	Packet;
		Packet.Point=TempLib;
		TunnelCrackBase	*BBase=GetTunnelCrackBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}



void EditTunnelCrackLibrary::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditTunnelCrackLibrary_LS,LID_2)/*"Warning"*/, LangSolver.GetString(EditTunnelCrackLibrary_LS,LID_3)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertTunnelCrackLibraryPacket	Packet;
	Packet.Point=TempLib;
	TunnelCrackBase	*BBase=GetTunnelCrackBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditTunnelCrackLibrary::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditTunnelCrackLibrary_LS,LID_4)/*"Warning"*/, LangSolver.GetString(EditTunnelCrackLibrary_LS,LID_5)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);
		CmdInsertTunnelCrackLibraryPacket	Packet;
		Packet.Point=TempLib;
		TunnelCrackBase	*BBase=GetTunnelCrackBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateTunnelCrackLibraryPacket	Packet;
		Packet.Point=TempLib;
		TunnelCrackBase	*BBase=GetTunnelCrackBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditTunnelCrackLibrary::on_pushButton_clicked()
{
	done(true);
}

void EditTunnelCrackLibrary::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadTunnelCrackLibraryPacket	Packet;
		Packet.Point=TempLib;
		TunnelCrackBase	*BBase=GetTunnelCrackBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(EditTunnelCrackLibrary_LS,LID_6)/*"Library error"*/, LangSolver.GetString(EditTunnelCrackLibrary_LS,LID_7)/*"Not loaded this library record"*/);
			}
		}
	}
}
void	EditTunnelCrackLibrary::ShowLibrary(TunnelCrackLibrary &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	ui.checkBoxItem1Enabled->setChecked(data.LibData.Item1.Enabled);
	ui.spinBoxItem1LengthLow->setValue(data.LibData.Item1.LengthLow);
	ui.spinBoxItem1WidthL->setValue(data.LibData.Item1.WidthL);
	ui.spinBoxItem1WidthH->setValue(data.LibData.Item1.WidthH);
	ui.spinBoxItem1CrackNo->setValue(data.LibData.Item1.CrackNo);
	ui.spinBoxItem1CrackWidth->setValue(data.LibData.Item1.CrackWidth);
	ui.spinBoxItem1CrackCenterValue->setValue(data.LibData.Item1.CrackCenterValue);
	ui.spinBoxItem1CrackResultValue->setValue(data.LibData.Item1.CrackResultValue);

	ui.checkBoxItem2Enabled->setChecked(data.LibData.Item2.Enabled);
	ui.spinBoxItem2LengthLow->setValue(data.LibData.Item2.LengthLow);
	ui.lineEditItem2Gain->setText(QString::number(data.LibData.Item2.Gain));
	ui.spinBoxItem2VarL->setValue(data.LibData.Item2.VarL);
	ui.spinBoxItem2VarH->setValue(data.LibData.Item2.VarH);

	ui.checkBoxItem3Enabled->setChecked(data.LibData.Item3.Enabled);
	ui.spinBoxItem3LengthLow->setValue(data.LibData.Item3.LengthLow);
	ui.lineEditItem3Gain->setText(QString::number(data.LibData.Item3.Gain));

	ui.checkBoxItem4Enabled->setChecked(data.LibData.Item4.Enabled);
	ui.spinBoxItem4LengthLow->setValue(data.LibData.Item4.LengthLow);
	ui.lineEditItem4Gain->setText(QString::number(data.LibData.Item4.Gain));

	ui.checkBoxItem5Enabled->setChecked(data.LibData.Item5.Enabled);
	ui.spinBoxItem5LengthLow->setValue(data.LibData.Item5.LengthLow);

	ui.spinBoxBinarizedBlockSize			->setValue(data.LibData.BinarizedBlockSize);
	ui.doubleSpinBoxBinarizedOutsideLRate	->setValue(data.LibData.BinarizedOutsideLRate);
	ui.doubleSpinBoxBinarizedOutsideHRate	->setValue(data.LibData.BinarizedOutsideHRate);
	ui.doubleSpinBoxBinarizedAlpha			->setValue(data.LibData.BinarizedAlpha);
	ui.spinBoxBinarizedThickness			->setValue(data.LibData.BinarizedThickness);
	ui.spinBoxBinarizedMinDot				->setValue(data.LibData.BinarizedMinDot);

	ui.checkBoxItem7Enabled->setChecked(data.LibData.Item7.Enabled);
	ui.spinBoxItem7BrightnessCable	->setValue(data.LibData.Item7.BrightnessCable	);
	ui.spinBoxItem7EnlargeCable		->setValue(data.LibData.Item7.EnlargeCable		);
	ui.spinBoxItem7EnsmallCable		->setValue(data.LibData.Item7.EnsmallCable		);
	ui.spinBoxItem7BrightnessMetal	->setValue(data.LibData.Item7.BrightnessMetal	);
	ui.spinBoxItem7EnlargeMetal		->setValue(data.LibData.Item7.EnlargeMetal		);
	ui.spinBoxItem7EnsmallMetal		->setValue(data.LibData.Item7.EnsmallMetal		);
	ui.spinBoxItem7BrightnessPanelL	->setValue(data.LibData.Item7.BrightnessPanelL	);
	ui.spinBoxItem7BrightnessPanelH	->setValue(data.LibData.Item7.BrightnessPanelH	);
	ui.spinBoxItem7LineDotPanel		->setValue(data.LibData.Item7.LineDotPanel		);

	ui.checkBoxItem8Enabled->setChecked(data.LibData.Item8.Enabled);
//	ui.spinBoxItem8Brightness	->setValue(data.LibData.Item8.Brightness);
	ui.spinBoxItem8MinimumDot	->setValue(data.LibData.Item8.MinimumDot);
	ui.spinBoxItem8ThresholdDiffL	->setValue(data.LibData.Item8.ThresholdDiffL);
	ui.spinBoxItem8ThresholdDiffH	->setValue(data.LibData.Item8.ThresholdDiffH);
	ui.spinBoxItem8ShiftXY			->setValue(data.LibData.Item8.ShiftXY);
}