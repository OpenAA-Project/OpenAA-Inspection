#include "PropertyRasterResource.h"
#include "EditRasterLibraryDialog.h"
#include "ui_EditRasterLibraryDialog.h"
#include "XRaster.h"
#include "XRasterLibrary.h"
#include "XRasterPacket.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"
#include "XAlgorithmLibrary.h"
#include "XLibraryType.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

EditRasterLibraryDialog::EditRasterLibraryDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::EditRasterLibraryDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	RasterBase	*BBase=GetRasterBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	pLibFolderSelect=new GeneralLibFolderForm(-1,GetLayersBase(),ui->frameLibFolderSelect);
	connect(pLibFolderSelect,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolderSelect(int,QString)));
	ui->tableWidgetLibListSelect->setColumnWidth (0, 40);
	ui->tableWidgetLibListSelect->setColumnWidth (1, 150);
	ui->tableWidgetSelected->setColumnWidth (0, 130);
	ui->tableWidgetSelected->setColumnWidth (1, 50);
	ui->tableWidgetSelected->setColumnWidth (2, 130);
	SetLibTypeInComboBox();

	if(BBase!=NULL){
		CmdCreateTempRasterLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	else{
		LLib=new AlgorithmLibraryLevelContainer(BBase);
	}

	ui->tableWidgetLibList	->setColumnWidth(0,56);
	ui->tableWidgetLibList	->setColumnWidth(1,110);
	ui->ButtonLibUpdate	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);

	ui->toolButtonStatic->setChecked(true);

	ControlRememberer::RestoreForm(this);
	InstallOperationLog(this);
}

EditRasterLibraryDialog::~EditRasterLibraryDialog()
{
    delete ui;
}

RasterBase	*EditRasterLibraryDialog::GetRasterBase(void)
{
	return (RasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Raster");
}
void	EditRasterLibraryDialog::SetLibTypeInComboBox(void)
{
	ui->comboBoxLibTypeSelect->clear();
	for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
		if(ABase!=NULL){
			ui->comboBoxLibTypeSelect->addItem(ABase->GetNameByCurrentLanguage()
												,(int)L->GetLibType());
		}
	}
}
void	EditRasterLibraryDialog::ShowFolder(int LibType)
{
	pLibFolderSelect->SetLibType(LibType);
}

void	EditRasterLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	RasterBase	*BBase=GetRasterBase();
	if(BBase!=NULL){
		CmdGetRasterLibraryListPacket	Packet(GetLayersBase());
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
void	EditRasterLibraryDialog::SlotSelectLibFolderSelect(int libFolderID ,QString FolderName)
{
	CurrentLibFolderID=libFolderID;
	ui->tableWidgetLibListSelect->setRowCount(0);
	AlgorithmLibraryContainerForEnum		LibList(GetLayersBase());
	LibIDListSelect.RemoveAll();
	LibList.EnumLibrary(GetLayersBase()->GetDatabase(),CurrentLibType,CurrentLibFolderID ,LibIDListSelect);

	int	row=0;
	ui->tableWidgetLibListSelect->setRowCount(LibIDListSelect.GetNumber());
	for(AlgorithmLibraryList *a=LibIDListSelect.GetFirst();a!=NULL;a=a->GetNext(),row++){
		::SetDataToTable(ui->tableWidgetLibListSelect,0,row ,QString::number(a->GetLibID()));
		::SetDataToTable(ui->tableWidgetLibListSelect,1,row ,a->GetLibName());
	}
}
void	EditRasterLibraryDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	//LibIDList.RemoveAll();
	//LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}

void EditRasterLibraryDialog::on_ButtonLibNew_clicked()
{
	if(LLib==NULL)
		return;
	LLib->Reset();
	CmdClearRasterLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	RasterBase	*BBase=GetRasterBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*LLib);
	ui->ButtonLibUpdate	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditRasterLibraryDialog::on_ButtonLibDelete_clicked()
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
		CmdDeleteRasterLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=LLib;
		RasterBase	*BBase=GetRasterBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditRasterLibraryDialog::on_ButtonLibSaveNew_clicked()
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
	CmdInsertRasterLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	RasterBase	*BBase=GetRasterBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*LLib);
		ui->ButtonLibUpdate	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditRasterLibraryDialog::on_ButtonLibUpdate_clicked()
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

		CmdInsertRasterLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		RasterBase	*BBase=GetRasterBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*LLib);
			ui->ButtonLibUpdate	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateRasterLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		RasterBase	*BBase=GetRasterBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditRasterLibraryDialog::on_tableWidgetLibList_itemSelectionChanged()
{
	int	r=ui->tableWidgetLibList->currentRow();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadRasterLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		RasterBase	*BBase=GetRasterBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
				ui->ButtonLibUpdate	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}

void EditRasterLibraryDialog::on_pushButtonClose_clicked()
{
	ControlRememberer::SaveForm(this);
	close();
}

void	EditRasterLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	RasterLibrary	*d=dynamic_cast<RasterLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->EditMaxShrinkDot		->setValue(d->MaxShrinkDot	);
	ui->EditMaxShiftDot			->setValue(d->MaxShiftDot	);
	ui->spinBoxShrinkDot		->setValue(d->ShrinkDot		);
	ui->spinBoxInsideEdgeWidth	->setValue(d->InsideEdgeWidth);
	ui->spinBoxOutsideEdgeWidth	->setValue(d->OutsideEdgeWidth);

	LimitedLibrariesStatic		=d->AllocatedStaticLib		;
	LimitedLibrariesInsideEdge	=d->AllocatedInsideEdgeLib	;
	LimitedLibrariesOutsideEdge	=d->AllocatedOutsideEdgeLib	;

	ShowTableSelect();
}

void	EditRasterLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	RasterLibrary	*d=dynamic_cast<RasterLibrary *>(data.GetLibrary());
	data.SetLibName(ui->EditLibName	->text());

	d->MaxShrinkDot		=ui->EditMaxShrinkDot		->value();
	d->MaxShiftDot		=ui->EditMaxShiftDot		->value();
	d->ShrinkDot		=ui->spinBoxShrinkDot		->value();
	d->InsideEdgeWidth	=ui->spinBoxInsideEdgeWidth	->value();
	d->OutsideEdgeWidth	=ui->spinBoxOutsideEdgeWidth->value();

	d->AllocatedStaticLib		=LimitedLibrariesStatic;
	d->AllocatedInsideEdgeLib	=LimitedLibrariesInsideEdge;
	d->AllocatedOutsideEdgeLib	=LimitedLibrariesOutsideEdge;
}
void EditRasterLibraryDialog::on_comboBoxLibTypeSelect_currentIndexChanged(int index)
{
	int	Index=ui->comboBoxLibTypeSelect->currentIndex();
	LibraryTypeList *L=GetLayersBase()->GetLibType()->GetItem(Index);
	if(L==NULL)
		return;
	QVariant V=ui->comboBoxLibTypeSelect->itemData(Index);
	CurrentLibType=V.toInt();
	ShowFolder(CurrentLibType);
	LibIDListSelect.RemoveAll();
	ui->tableWidgetLibListSelect->setRowCount(0);
}

void EditRasterLibraryDialog::on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelectButton_clicked();
}

void EditRasterLibraryDialog::on_pushButtonSelectButton_clicked()
{
	int	r=ui->tableWidgetLibListSelect->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=LibIDListSelect[r];
	if(a==NULL)
		return;
	AlgorithmLibraryListContainer	*LibC=NULL;
	if(ui->toolButtonStatic->isChecked()==true)
		LibC=&LimitedLibrariesStatic;
	if(ui->toolButtonEdgeIn->isChecked()==true)
		LibC=&LimitedLibrariesInsideEdge;
	if(ui->toolButtonEdgeOut->isChecked()==true)
		LibC=&LimitedLibrariesOutsideEdge;

	AlgorithmLibraryList	*d=new AlgorithmLibraryList(*a);
	LibC->AppendList(d);

	ShowTableSelect();
}

void EditRasterLibraryDialog::on_tableWidgetSelected_doubleClicked(const QModelIndex &index)
{
	int	r=ui->tableWidgetSelected->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryListContainer	*LibC=NULL;
	if(ui->toolButtonStatic->isChecked()==true)
		LibC=&LimitedLibrariesStatic;
	if(ui->toolButtonEdgeIn->isChecked()==true)
		LibC=&LimitedLibrariesInsideEdge;
	if(ui->toolButtonEdgeOut->isChecked()==true)
		LibC=&LimitedLibrariesOutsideEdge;

	AlgorithmLibraryList	*d=LibC->GetItem(r);
	if(d!=NULL){
		LibC->RemoveList(d);
		delete	d;
		ShowTableSelect();
	}
}

void	EditRasterLibraryDialog::ShowTableSelect(void)
{
	AlgorithmLibraryListContainer	*LibC=NULL;
	if(ui->toolButtonStatic->isChecked()==true)
		LibC=&LimitedLibrariesStatic;
	if(ui->toolButtonEdgeIn->isChecked()==true)
		LibC=&LimitedLibrariesInsideEdge;
	if(ui->toolButtonEdgeOut->isChecked()==true)
		LibC=&LimitedLibrariesOutsideEdge;

	ui->tableWidgetSelected	->setRowCount(LibC->GetCount());
	int	row=0;
	for(AlgorithmLibraryList *a=LibC->GetFirst();a!=NULL;a=a->GetNext(),row++){
		LibraryTypeList	*LType=GetLayersBase()->GetInstalledLibType()->FindLibraryType(a->GetLibType());
		if(LType!=NULL){
			AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(LType->GetLibType());
			if(ABase!=NULL){
				::SetDataToTable(ui->tableWidgetSelected,0,row ,ABase->GetNameByCurrentLanguage());
			}
			else{
				::SetDataToTable(ui->tableWidgetSelected,0,row ,LType->GetLibName());
			}
		}
		else{
			::SetDataToTable(ui->tableWidgetSelected,0,row ,LangSolver.GetString(EditRasterLibraryDialog_LS,LID_7)/*"Not registered"*/);
		}
		::SetDataToTable(ui->tableWidgetSelected,1,row ,QString::number(a->GetLibID()));
		::SetDataToTable(ui->tableWidgetSelected,2,row ,a->GetLibName());
	}
}
void EditRasterLibraryDialog::on_toolButtonStatic_clicked()
{
	ShowTableSelect();
}

void EditRasterLibraryDialog::on_toolButtonEdgeIn_clicked()
{
	ShowTableSelect();
}

void EditRasterLibraryDialog::on_toolButtonEdgeOut_clicked()
{
	ShowTableSelect();
}
