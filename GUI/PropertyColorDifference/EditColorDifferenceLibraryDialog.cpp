#include "ColorDifferenceResource.h"
#include "EditColorDifferenceLibraryDialog.h"
#include "ui_EditColorDifferenceLibraryDialog.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyColorDifferencePacket.h"
#include "XColorDifferenceLibrary.h"
#include <QMessageBox>
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"

EditColorDifferenceLibraryDialog::EditColorDifferenceLibraryDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::EditColorDifferenceLibraryDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	OnChanging	=false;
	LibFolderID =-1;
	ColorDifferenceBase	*BBase=GetColorDifferenceBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	if(BBase!=NULL){
		CmdCreateTempColorDifferenceLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	else{
		LLib=new AlgorithmLibraryLevelContainer(BBase);
	}
	ui->tableWidgetLibList	->setColumnWidth(0,48);
	ui->tableWidgetLibList	->setColumnWidth(1,120);

	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);

	InstallOperationLog(this);
}

EditColorDifferenceLibraryDialog::~EditColorDifferenceLibraryDialog()
{
    delete ui;
	if(LLib!=NULL){
		delete	LLib;
		LLib=NULL;
	}
}

ColorDifferenceBase	*EditColorDifferenceLibraryDialog::GetColorDifferenceBase(void)
{
	return (ColorDifferenceBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
}

void	EditColorDifferenceLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	//ui->tableWidgetLibList->clear();
	ui->tableWidgetLibList->setRowCount(0);
	ColorDifferenceBase	*BBase=GetColorDifferenceBase();
	if(BBase!=NULL){
		CmdGetColorDifferenceLibraryListPacket	Packet(GetLayersBase());
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
void EditColorDifferenceLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadColorDifferenceLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		ColorDifferenceBase	*BBase=GetColorDifferenceBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL
									, LangSolver.GetString(EditColorDifferenceLibraryDialog_LS,LID_0)/*"Library error"*/
									, LangSolver.GetString(EditColorDifferenceLibraryDialog_LS,LID_1)/*"Not loaded this library record"*/);
			}
		}
	}
}

void	EditColorDifferenceLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	ColorDifferenceLibrary	*d=dynamic_cast<ColorDifferenceLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->doubleSpinBoxGenDeltaE				->setValue(d->GenDeltaE);
	ui->spinBoxMaxLength					->setValue(d->MaxLength);
	ui->spinBoxGenBlockResolution			->setValue(d->GenBlockResolution);
	ui->spinBoxGenMinArea					->setValue(d->GenMinArea);
	ui->spinBoxGenMaxArea					->setValue(d->GenMaxArea);
	ui->doubleSpinBoxGenMaxVariable			->setValue(d->GenMaxVariable);
	ui->doubleSpinBoxGenMaxBrightDifference	->setValue(d->GenMaxBrightDifference);
	ui->spinBoxGenSurroundMergin			->setValue(d->GenSurroundMergin);

	ui->comboBoxJudgeMethod					->setCurrentIndex(d->JudgeMethod);
	ui->doubleSpinBoxAdoptedRate			->setValue(d->AdoptedRate);
	ui->doubleSpinBoxTHDeltaE				->setValue(d->THDeltaE);
	ui->doubleSpinBoxdH						->setValue(d->dH);
	ui->doubleSpinBoxdSL					->setValue(d->dSL);
	ui->doubleSpinBoxdSH					->setValue(d->dSH);
	ui->doubleSpinBoxdVL					->setValue(d->dVL);
	ui->doubleSpinBoxdVH					->setValue(d->dVH);
	ui->toolButtonItem						->setChecked((d->ItemClass==0)?true:false);
	ui->toolButtonReference					->setChecked((d->ItemClass==1)?true:false);
	ui->checkBoxAdaptAlignment				->setChecked(d->AdaptAlignment);
}

void	EditColorDifferenceLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	ColorDifferenceLibrary	*d=dynamic_cast<ColorDifferenceLibrary *>(data.GetLibrary());
	data.SetLibName(ui->EditLibName	->text());

	d->GenDeltaE				=ui->doubleSpinBoxGenDeltaE		->value();
	d->MaxLength				=ui->spinBoxMaxLength			->value();
	d->GenBlockResolution		=ui->spinBoxGenBlockResolution	->value();
	d->GenMinArea				=ui->spinBoxGenMinArea			->value();
	d->GenMaxArea				=ui->spinBoxGenMaxArea			->value();
	d->GenMaxVariable			=ui->doubleSpinBoxGenMaxVariable->value();
	d->GenMaxBrightDifference	=ui->doubleSpinBoxGenMaxBrightDifference->value();
	d->GenSurroundMergin		=ui->spinBoxGenSurroundMergin			->value();

	d->AdoptedRate				=ui->doubleSpinBoxAdoptedRate	->value();
	d->JudgeMethod				=ui->comboBoxJudgeMethod		->currentIndex();
	d->THDeltaE					=ui->doubleSpinBoxTHDeltaE		->value();
	d->dH						=ui->doubleSpinBoxdH			->value();
	d->dSL						=ui->doubleSpinBoxdSL			->value();
	d->dSH						=ui->doubleSpinBoxdSH			->value();
	d->dVL						=ui->doubleSpinBoxdVL			->value();
	d->dVH						=ui->doubleSpinBoxdVH			->value();

	if(ui->toolButtonItem	->isChecked()==true)
		d->ItemClass=0;
	else
	if(ui->toolButtonReference	->isChecked()==true)
		d->ItemClass=1;

	d->AdaptAlignment			=ui->checkBoxAdaptAlignment		->isChecked();
}
void EditColorDifferenceLibraryDialog::on_ButtonLibNew_clicked()
{
	if(LLib==NULL)
		return;
	LLib->Reset();
	CmdClearColorDifferenceLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	ColorDifferenceBase	*BBase=GetColorDifferenceBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*LLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditColorDifferenceLibraryDialog::on_ButtonLibDelete_clicked()
{
	if(LLib==NULL)
		return;
	if(LLib->GetLibID()<0)
		return;
	QString  msg=QString(LangSolver.GetString(EditColorDifferenceLibraryDialog_LS,LID_2)/*"Delete OK?"*/);
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(EditColorDifferenceLibraryDialog_LS,LID_3)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteColorDifferenceLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		ColorDifferenceBase	*BBase=GetColorDifferenceBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditColorDifferenceLibraryDialog::on_ButtonLibSaveNew_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);

	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditColorDifferenceLibraryDialog_LS,LID_4)/*"Warning"*/
																, LangSolver.GetString(EditColorDifferenceLibraryDialog_LS,LID_5)/*"No Library Name"*/
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	LLib->SetLibFolderID(LibFolderID);
	CmdInsertColorDifferenceLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	ColorDifferenceBase	*BBase=GetColorDifferenceBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*LLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditColorDifferenceLibraryDialog::on_ButtonLibSave_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditColorDifferenceLibraryDialog_LS,LID_6)/*"Warning"*/
																, LangSolver.GetString(EditColorDifferenceLibraryDialog_LS,LID_7)/*"No Library Name"*/
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(LLib->GetLibID()<0){
		LLib->SetLibFolderID(LibFolderID);

		CmdInsertColorDifferenceLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		ColorDifferenceBase	*BBase=GetColorDifferenceBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*LLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateColorDifferenceLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		ColorDifferenceBase	*BBase=GetColorDifferenceBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditColorDifferenceLibraryDialog::on_pushButton_clicked()
{
	close();
}
