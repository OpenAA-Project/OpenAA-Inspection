#include "PropertyEulerRingL1Resource.h"
#include "CreateManualEulerRingL1Dialog.h"
#include "ui_CreateManualEulerRingL1Dialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

CreateManualEulerRingL1Dialog::CreateManualEulerRingL1Dialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::CreateManualEulerRingL1Dialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	SelectedLibID=-1;
	EulerRingL1LibID	 =-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempEulerRingL1ItemPacket	ItemPacket(GetLayersBase());
		Ab->TransmitDirectly(&ItemPacket);
		BItem=(EulerRingL1Item *)ItemPacket.Point;
		CmdCreateTempEulerRingL1LibraryPacket	LibPacket(GetLayersBase());
		Ab->TransmitDirectly(&LibPacket);
		TempLib=LibPacket.Point;
	LibType=Ab->GetLibType();
	}
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	
	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetLibList->setRowCount(0);
	ui->ButtonOK->setEnabled(false);

	InstallOperationLog(this);
}

CreateManualEulerRingL1Dialog::~CreateManualEulerRingL1Dialog()
{
    delete ui;
	if(BItem!=NULL)
		delete	BItem;
	BItem=NULL;
	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}

void	CreateManualEulerRingL1Dialog::Reflect(void)
{
	ui->EditLibID			->setText(QString::number(BItem->GetLibID()));
	EulerRingL1LibID=BItem->GetLibID();
	CmdGetLibName	LibPacket(GetLayersBase());
	LibPacket.LibID=BItem->GetLibID();
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&LibPacket);
	}
	ui->EditLibName				->setText(LibPacket.LibName);

}

void	CreateManualEulerRingL1Dialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
	if(Ab!=NULL){
		CmdGetEulerRingL1LibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		Ab->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui->tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui->tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}

void CreateManualEulerRingL1Dialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	TempLib->SetLibID(a->GetLibID());

	CmdLoadEulerRingL1LibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);

		if(Packet.Success==true){
			EulerRingL1LibID			=TempLib->GetLibID();
			ui->EditLibID				->setText(QString::number(TempLib->GetLibID()));
			ui->EditLibName				->setText(a->GetLibName());

			EulerRingL1Library	*ALib=dynamic_cast<EulerRingL1Library *>(TempLib->GetLibrary());
			ui->ButtonOK->setEnabled(true);
			if(BItem!=NULL){
				BItem->SetLibID(TempLib->GetLibID());
			}
			ui->EditDarkWidth				->setValue(ALib->DarkWidth);
			ui->EditLightWidth				->setValue(ALib->LightWidth);
			ui->EditConnectLen				->setValue(ALib->ConnectLen);
			ui->EditMinHoleDiameter			->setValue(ALib->MinHoleDiameter);
			ui->EditMaxHoleDiameter			->setValue(ALib->MaxHoleDiameter);
			ui->EditMaxShiftHole			->setValue(ALib->MaxShiftHole);

			ui->checkModeEnabled				->setChecked(ALib->PointMove.ModeEnabled);
			ui->checkModeAbsoluteBright			->setChecked(ALib->PointMove.ModeAbsoluteBright);
			ui->checkModeDynamicMask			->setChecked(ALib->PointMove.ModeMakeDynamicMask);
			ui->checkModeEnableHoleCheck		->setChecked(ALib->PointMove.ModeEnableHoleCheck);
			ui->checkModeCenterBrightFromParts	->setChecked(ALib->PointMove.ModeCenterBrightFromParts);
			ui->checkModeEnableOpenRingCheck	->setChecked(ALib->PointMove.ModeEnableOpenRingCheck);

			ui->EditAdjustBlack					->setValue	(ALib->AdjustBlack);
			ui->EditAdjustWhite					->setValue	(ALib->AdjustWhite);
			ui->EditExpandForDynamicMask		->setValue	(ALib->ExpandForDynamicMask);
			ui->EditHoleBrightnessAsReference	->setValue	(ALib->HoleBrightnessAsReference);
		}
		else{
			QMessageBox::critical(NULL	, LangSolver.GetString(CreateManualEulerRingL1Dialog_LS,LID_6)/*"Library error"*/
										, LangSolver.GetString(CreateManualEulerRingL1Dialog_LS,LID_7)/*"Not loaded this library record"*/);
		}
	}
}

void CreateManualEulerRingL1Dialog::on_ButtonOK_clicked()
{
	done(true);
}

void CreateManualEulerRingL1Dialog::on_ButtonCancel_clicked()
{
	done(false);
}
