#include "PropertyRasterResource.h"
#include "SetAllocationDialog.h"
#include "ui_SetAllocationDialog.h"
#include "XLibraryType.h"
#include "XDataInLayer.h"
#include "XRaster.h"
#include "XRasterPacket.h"
#include "XRasterLibrary.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

SetAllocationDialog::SetAllocationDialog(bool NewMode,LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SetAllocationDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibType=DefLibTypeRaster;
	LibID=-1;
	RasterBase	*ABase=GetRasterBase();
	if(ABase!=NULL){
		LLib=new AlgorithmLibraryLevelContainer(ABase);
	}
	else{
		LLib=NULL;
	}
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
	
	ui->tableWidgetLibList	->setColumnWidth(0,56);
	ui->tableWidgetLibList	->setColumnWidth(1,110);

	if(NewMode==true){
		ui->pushButtonDelete->setVisible(false);
	}

	ControlRememberer::RestoreForm(this);

	InstallOperationLog(this);
}

SetAllocationDialog::~SetAllocationDialog()
{
    delete ui;
	if(LLib!=NULL){
		delete	LLib;
		LLib=NULL;
	}
}

void	SetAllocationDialog::Set(int _ShrinkDot
								,int _InsideEdgeWidth
								,int _OutsideEdgeWidth
								,AlgorithmLibraryListContainer &AllocatedStaticLib
								,AlgorithmLibraryListContainer &AllocatedInsideEdgeLib
								,AlgorithmLibraryListContainer &AllocatedOutsideEdgeLib)
{
	ShrinkDot		=_ShrinkDot;
	InsideEdgeWidth	=_InsideEdgeWidth;
	OutsideEdgeWidth=_OutsideEdgeWidth;
	LimitedLibrariesStatic		=AllocatedStaticLib		;
	LimitedLibrariesInsideEdge	=AllocatedInsideEdgeLib	;
	LimitedLibrariesOutsideEdge	=AllocatedOutsideEdgeLib;

	ui->spinBoxShrinkDot		->setValue(ShrinkDot);
	ui->spinBoxInsideEdgeWidth	->setValue(InsideEdgeWidth);
	ui->spinBoxOutsideEdgeWidth	->setValue(OutsideEdgeWidth);
	ShowTableSelect();
}

RasterBase	*SetAllocationDialog::GetRasterBase(void)
{
	return (RasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Raster");
}
void	SetAllocationDialog::SetLibTypeInComboBox(void)
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
void SetAllocationDialog::on_comboBoxLibTypeSelect_currentIndexChanged(int index)
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

void	SetAllocationDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
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
void	SetAllocationDialog::SlotSelectLibFolderSelect(int libFolderID ,QString FolderName)
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
void	SetAllocationDialog::ShowFolder(int LibType)
{
	pLibFolderSelect->SetLibType(LibType);
}

void SetAllocationDialog::on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelectButton_clicked();
}

void SetAllocationDialog::on_pushButtonSelectButton_clicked()
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

void SetAllocationDialog::on_tableWidgetSelected_doubleClicked(const QModelIndex &index)
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

void	SetAllocationDialog::ShowTableSelect(void)
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
			::SetDataToTable(ui->tableWidgetSelected,0,row ,LangSolver.GetString(SetAllocationDialog_LS,LID_8)/*"Not registered"*/);
		}
		::SetDataToTable(ui->tableWidgetSelected,1,row ,QString::number(a->GetLibID()));
		::SetDataToTable(ui->tableWidgetSelected,2,row ,a->GetLibName());
	}
}

void SetAllocationDialog::on_pushButtonOK_clicked()
{
	ShrinkDot			=ui->spinBoxShrinkDot		->value();
	InsideEdgeWidth		=ui->spinBoxInsideEdgeWidth	->value();
	OutsideEdgeWidth	=ui->spinBoxOutsideEdgeWidth->value();

	ControlRememberer::SaveForm(this);
	done(1);
}

void SetAllocationDialog::on_pushButtonCancel_clicked()
{
	done(0);
}

void SetAllocationDialog::on_pushButtonDelete_clicked()
{
	done(2);
}

void SetAllocationDialog::on_toolButtonStatic_clicked()
{
	ShowTableSelect();
}

void SetAllocationDialog::on_toolButtonEdgeIn_clicked()
{
	ShowTableSelect();
}

void SetAllocationDialog::on_toolButtonEdgeOut_clicked()
{
	ShowTableSelect();
}

void SetAllocationDialog::on_tableWidgetLibList_itemSelectionChanged()
{
	int	r=ui->tableWidgetLibList->currentRow();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL && LLib!=NULL){
		LibID=a->GetLibID();
		LLib->SetLibID(a->GetLibID());

		CmdLoadRasterLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		RasterBase	*BBase=GetRasterBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				RasterLibrary	*pLib=(RasterLibrary	*)LLib->GetLibrary();
				Set( pLib->ShrinkDot
					,pLib->InsideEdgeWidth
					,pLib->OutsideEdgeWidth
					,pLib->AllocatedStaticLib
					,pLib->AllocatedInsideEdgeLib
					,pLib->AllocatedOutsideEdgeLib);			
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}
