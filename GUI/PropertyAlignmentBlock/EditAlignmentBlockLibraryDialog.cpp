#include "EditAlignmentBlockLibraryDialog.h"
#include "ui_EditAlignmentBlockLibraryDialog.h"
#include <QMessageBox>
#include "XAlignmentBlockLibrary.h"

EditAlignmentBlockLibraryDialog::EditAlignmentBlockLibraryDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::EditAlignmentBlockLibraryDialog)
{
    ui->setupUi(this);

	OnChanging	=false;
	LibFolderID =-1;
	MasterNoOriginCode	=-1;
	AlignmentBlockBase	*BBase=GetAlignmentBlockBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	LLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAlignmentBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	ui->tableWidgetLibList	->setColumnWidth(0,48);
	ui->tableWidgetLibList	->setColumnWidth(1,120);

	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);

	ui->tabWidget			->setCurrentIndex(0);

	InstallOperationLog(this);
}

EditAlignmentBlockLibraryDialog::~EditAlignmentBlockLibraryDialog()
{
    delete ui;

	delete	LLib;
	LLib=NULL;
}

AlignmentBlockBase	*EditAlignmentBlockLibraryDialog::GetAlignmentBlockBase(void)
{
	return (AlignmentBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentBlock");
}

void	EditAlignmentBlockLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	//ui->tableWidgetLibList->clear();
	ui->tableWidgetLibList->setRowCount(0);
	AlignmentBlockBase	*BBase=GetAlignmentBlockBase();
	if(BBase!=NULL){
		CmdGetAlignmentBlockLibraryListPacket	Packet(GetLayersBase());
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
void EditAlignmentBlockLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadAlignmentBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentBlockBase	*BBase=GetAlignmentBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL
									, "Library error"
									, "Not loaded this library record");
			}
		}
	}
}


void	EditAlignmentBlockLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	AlignmentBlockLibrary *ALib=(AlignmentBlockLibrary *)data.GetLibrary();

	ui->EditMinAreaSize			->setValue	(ALib->MinAreaSize		);
	ui->EditMaxAreaSize			->setValue	(ALib->MaxAreaSize		);
	ui->EditMinAreaDots			->setValue	(ALib->MinAreaDots		);
	ui->EditMaxAreaDots			->setValue	(ALib->MaxAreaDots		);
	ui->EditOverlapDot			->setValue	(ALib->OverlapDot		);
	ui->EditLimitSize			->setValue	(ALib->LimitSize		);

	ui->EditNoisePinholeSize	->setValue	(ALib->NoisePinholeSize	);
	ui->EditNoiseIslandSize		->setValue	(ALib->NoiseIslandSize	);
	ui->EditExpandArea			->setValue	(ALib->ExpandArea		);

	ui->spinBoxSearchDot		->setValue	(ALib->SearchDot		);
	ui->doubleSpinBoxMaxDegree	->setValue	(ALib->MaxDegree		);
	ui->spinBoxLineLength		->setValue	(ALib->LineLength		);
	ui->doubleSpinBoxMinVar		->setValue	(ALib->MinVar			);
	ui->doubleSpinBoxThreDiv	->setValue	(ALib->ThreDiv			);
}

void	EditAlignmentBlockLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	AlignmentBlockLibrary *ALib=(AlignmentBlockLibrary *)data.GetLibrary();

	ALib->MinAreaSize		=ui->EditMinAreaSize		->value	();
	ALib->MaxAreaSize		=ui->EditMaxAreaSize		->value	();
	ALib->MinAreaDots		=ui->EditMinAreaDots		->value	();
	ALib->MaxAreaDots		=ui->EditMaxAreaDots		->value	();
	ALib->OverlapDot		=ui->EditOverlapDot			->value	();
	ALib->LimitSize			=ui->EditLimitSize			->value	();

	ALib->NoisePinholeSize	=ui->EditNoisePinholeSize	->value	();
	ALib->NoiseIslandSize	=ui->EditNoiseIslandSize	->value	();
	ALib->ExpandArea		=ui->EditExpandArea			->value	();

	ALib->SearchDot			=ui->spinBoxSearchDot		->value	();
	ALib->MaxDegree			=ui->doubleSpinBoxMaxDegree	->value	();
	ALib->LineLength		=ui->spinBoxLineLength		->value	();
	ALib->MinVar			=ui->doubleSpinBoxMinVar	->value	();
	ALib->ThreDiv			=ui->doubleSpinBoxThreDiv	->value	();

}
void EditAlignmentBlockLibraryDialog::on_ButtonLibNew_clicked()
{
	if(LLib==NULL)
		return;
	LLib->Reset();
	CmdClearAlignmentBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	AlignmentBlockBase	*BBase=GetAlignmentBlockBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*LLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}


void EditAlignmentBlockLibraryDialog::on_ButtonLibDelete_clicked()
{
	if(LLib==NULL)
		return;
	if(LLib->GetLibID()<0)
		return;
	QString  msg="Delete OK?";
	int	ret=QMessageBox::question(NULL, "Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteAlignmentBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentBlockBase	*BBase=GetAlignmentBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}


void EditAlignmentBlockLibraryDialog::on_ButtonLibSaveNew_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);

	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, "Warning"
																, "No Library Name"
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	LLib->SetLibFolderID(LibFolderID);
	CmdInsertAlignmentBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	AlignmentBlockBase	*BBase=GetAlignmentBlockBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*LLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}


void EditAlignmentBlockLibraryDialog::on_ButtonLibSave_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, "Warning"
																, "No Library Name"
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(LLib->GetLibID()<0){
		LLib->SetLibFolderID(LibFolderID);

		CmdInsertAlignmentBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentBlockBase	*BBase=GetAlignmentBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*LLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateAlignmentBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentBlockBase	*BBase=GetAlignmentBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}


void EditAlignmentBlockLibraryDialog::on_pushButtonClose_clicked()
{
	close();
}

