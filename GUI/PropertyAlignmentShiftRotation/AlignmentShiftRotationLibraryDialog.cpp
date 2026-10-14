#include "AlignmentShiftRotationLibraryDialog.h"
#include "ui_AlignmentShiftRotationLibraryDialog.h"
#include <QMessageBox>
#include <QDrag>
#include <QMimeData>
#include "XGeneralDialog.h"
#include "EditAngleRangeDialog.h"
#include "XPacketAlignmentShiftRotation.h"


AlignmentShiftRotationLibraryDialog::AlignmentShiftRotationLibraryDialog(LayersBase *Base ,QWidget *parent)
    : QDialog(parent)
    ,ServiceForLayers(Base)
    , ui(new Ui::AlignmentShiftRotationLibraryDialog)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);
	
	bool	Ret;

	LibFolderID =-1;
	AlignmentShiftRotationBase	*BBase=GetAlignmentShiftRotationBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	LLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAlignmentShiftRotationLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	
	::SetColumnWidthInTable(ui->tableWidgetAngleList,0, 45);
	::SetColumnWidthInTable(ui->tableWidgetAngleList,1, 45);

	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	Ret=(connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString))))?true:false;
	Ret=(connect(pLibFolderForm,SIGNAL(SignalDrop(int ,int , QWidget *)),this,SLOT(SlotDrop(int ,int , QWidget *))))?true:false;
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
	InstallOperationLog(this);

}

AlignmentShiftRotationLibraryDialog::~AlignmentShiftRotationLibraryDialog()
{
    delete ui;
}

AlignmentShiftRotationBase	*AlignmentShiftRotationLibraryDialog::GetAlignmentShiftRotationBase(void)
{
	return (AlignmentShiftRotationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentShiftRotation");
}
void	AlignmentShiftRotationLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	AlignmentShiftRotationBase	*BBase=GetAlignmentShiftRotationBase();
	if(BBase!=NULL){
		CmdGetAlignmentShiftRotationLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
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
void	AlignmentShiftRotationLibraryDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}

void AlignmentShiftRotationLibraryDialog::on_tableWidgetLibList_itemSelectionChanged()
{
	int	r=ui->tableWidgetLibList->currentRow();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadAlignmentShiftRotationLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentShiftRotationBase	*BBase=GetAlignmentShiftRotationBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}


void AlignmentShiftRotationLibraryDialog::on_ButtonLibNew_clicked()
{
	if(LLib==NULL)
		return;
	LLib->Reset();
	CmdClearAlignmentShiftRotationLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	AlignmentShiftRotationBase	*BBase=GetAlignmentShiftRotationBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*LLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}


void AlignmentShiftRotationLibraryDialog::on_ButtonLibDelete_clicked()
{
	if(LLib==NULL)
		return;
	if(LLib->GetLibID()<0)
		return;
	QString  msg=QString(/**/"Delete OK?");
	int	ret=QMessageBox::question(NULL, /**/"Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteAlignmentShiftRotationLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentShiftRotationBase	*BBase=GetAlignmentShiftRotationBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}


void AlignmentShiftRotationLibraryDialog::on_ButtonLibSaveNew_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);

	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	LLib->SetLibFolderID(LibFolderID);
	CmdInsertAlignmentShiftRotationLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	AlignmentShiftRotationBase	*BBase=GetAlignmentShiftRotationBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*LLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}


void AlignmentShiftRotationLibraryDialog::on_ButtonLibSave_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(LLib->GetLibID()<0){
		LLib->SetLibFolderID(LibFolderID);

		CmdInsertAlignmentShiftRotationLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentShiftRotationBase	*BBase=GetAlignmentShiftRotationBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*LLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateAlignmentShiftRotationLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentShiftRotationBase	*BBase=GetAlignmentShiftRotationBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}


void	AlignmentShiftRotationLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	AlignmentShiftRotationLibrary	*ALib=static_cast<AlignmentShiftRotationLibrary *>(data.GetLibrary());


	ui->EditThreshold	->setValue(ALib->Threshold	);
	ui->EditLineCount	->setValue(ALib->LineCount	);
	ui->EditTargetLayer	->setValue(ALib->TargetLayer	);
	ui->EditLineLen		->setValue(ALib->LineLen		);
	ui->EditSearchDotX	->setValue(ALib->SearchDotX	);
	ui->EditSearchDotY	->setValue(ALib->SearchDotY	);
	ui->EditSparseAngle	->setValue(ALib->SparseAngle	);

	Rotation=ALib->Rotation;
	ShowAngleRange();
}

void	AlignmentShiftRotationLibraryDialog::ShowAngleRange(void)
{
	int	row = 0;
	ui->tableWidgetAngleList->setRowCount(Rotation.GetCount());
	for(RotationRange *r=Rotation.GetFirst();r!=NULL;r=r->GetNext(),row++){
		::SetDataToTable(ui->tableWidgetAngleList, 0, row, QString::number(r->MinAngleDegree,'f',2));
		::SetDataToTable(ui->tableWidgetAngleList, 1, row, QString::number(r->MaxAngleDegree,'f',2));
	}
}

void	AlignmentShiftRotationLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	AlignmentShiftRotationLibrary	*ALib=static_cast<AlignmentShiftRotationLibrary *>(data.GetLibrary());

	ALib->Threshold		=ui->EditThreshold	->value();
	ALib->LineCount		=ui->EditLineCount	->value();
	ALib->TargetLayer	=ui->EditTargetLayer->value();
	ALib->LineLen		=ui->EditLineLen	->value();
	ALib->SearchDotX	=ui->EditSearchDotX	->value();
	ALib->SearchDotY	=ui->EditSearchDotY	->value();
	ALib->SparseAngle	=ui->EditSparseAngle->value();
	ALib->Rotation		=Rotation;
}

void AlignmentShiftRotationLibraryDialog::on_pushButtonClose_clicked()
{
	close();
}


void AlignmentShiftRotationLibraryDialog::on_pushButtonAddAngle_clicked()
{
	EditAngleRangeDialog	D;
	if(D.exec()==(int)true){
		RotationRange	*R=new RotationRange();
		R->MinAngleDegree=D.RetMinAngle;
		R->MaxAngleDegree=D.RetMaxAngle;
		Rotation.AppendList(R);
		ShowAngleRange();
	}
}


void AlignmentShiftRotationLibraryDialog::on_pushButtonSubAngle_clicked()
{
	int	R = ui->tableWidgetAngleList->currentRow();
	RotationRange	*r=Rotation[R];
	if(r!=NULL){
		Rotation.RemoveList(r);
		delete	r;
		ShowAngleRange();
	}
}


void AlignmentShiftRotationLibraryDialog::on_tableWidgetAngleList_cellDoubleClicked(int row, int column)
{
	int	R = ui->tableWidgetAngleList->currentRow();
	RotationRange	*r=Rotation[R];
	if(r!=NULL){
		EditAngleRangeDialog	D;
		D.Initial(r->MinAngleDegree,r->MaxAngleDegree);
		if(D.exec()==(int)true){
			r->MinAngleDegree=D.RetMinAngle;
			r->MaxAngleDegree=D.RetMaxAngle;
			ShowAngleRange();
		}
	}
}

