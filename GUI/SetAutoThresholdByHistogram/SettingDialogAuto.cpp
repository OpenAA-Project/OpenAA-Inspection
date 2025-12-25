#include "SettingDialogAuto.h"
#include "ui_SettingDialogAuto.h"
#include "XLibraryType.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include <QColorDialog>
#include "XGeneralDialog.h"
#include "SetAutoThresholdByHistogramForm.h"

SettingDialogAuto::SettingDialogAuto(SetAutoThresholdByHistogramForm *p,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(p->GetLayersBase())
    ,Parent(p)
    ,ui(new Ui::SettingDialogAuto)
{
    ui->setupUi(this);
	LibType = Parent->LibType;
	LibID	= Parent->LibID;
	HistID	= Parent->HistID;
	ButtonName=Parent->ButtonName;

	pLibFolderSelect=new GeneralLibFolderForm(-1,GetLayersBase(),ui->frameLibFolderSelect);
	connect(pLibFolderSelect,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolderSelect(int,QString)));
	ui->tableWidgetLibListSelect->setColumnWidth (0, 40);
	ui->tableWidgetLibListSelect->setColumnWidth (1, 150);

	int	SelectedLibType=-1;
	ui->comboBoxLibTypeSelect->clear();
	int	row=0;
	for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
		if(ABase!=NULL){
			ui->comboBoxLibTypeSelect->addItem(ABase->GetNameByCurrentLanguage()
												,(int)L->GetLibType());
			if(L->GetLibType()==LibType){
				SelectedLibType=row;
			}
			row++;
		}
	}
	if(SelectedLibType>=0){
		ui->comboBoxLibTypeSelect->setCurrentIndex(SelectedLibType);

		on_comboBoxLibTypeSelect_currentIndexChanged(-1);
	}

	if(LibType>=0){
		ui->lineEditAlgorithmTypeName->setText(GetLayersBase()->GetLibTypeName(LibType));
		ui->spinBoxLibID->setValue(LibID);
		ui->lineEditLibName->setText(GetLayersBase()->GetLibraryName(LibType,LibID));

		ShowHistList();
		ShowUsageHistList();
	}
	ui->lineEditButtonName->setText(ButtonName);
}

SettingDialogAuto::~SettingDialogAuto()
{
    delete ui;
}
void	SettingDialogAuto::SlotSelectLibFolderSelect(int libFolderID ,QString FolderName)
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
void SettingDialogAuto::on_comboBoxLibTypeSelect_currentIndexChanged(int index)
{
	int	Index=ui->comboBoxLibTypeSelect->currentIndex();
	LibraryTypeList *L=GetLayersBase()->GetLibType()->GetItem(Index);
	if(L==NULL)
		return;
	QVariant V=ui->comboBoxLibTypeSelect->itemData(Index);
	CurrentLibType=V.toInt();
	pLibFolderSelect->SetLibType(CurrentLibType);
	LibIDListSelect.RemoveAll();
	ui->tableWidgetLibListSelect->setRowCount(0);
}


void SettingDialogAuto::on_tableWidgetLibListSelect_itemSelectionChanged()
{
	int	r=ui->tableWidgetLibListSelect->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=LibIDListSelect[r];
	if(a==NULL)
		return;

	LibType = a->GetLibType();
	ui->lineEditAlgorithmTypeName->setText(GetLayersBase()->GetLibTypeName(LibType));
	LibID = a->GetLibID();
	ui->spinBoxLibID->setValue(LibID);
	ui->lineEditLibName->setText(a->GetLibName());

	ShowHistList();
}

void SettingDialogAuto::ShowHistList(void)
{
	ui->listWidgetHistList->clear();

	AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		QStringList	HistNames;
		ABase->EnumHistgram(HistNames);
		ui->listWidgetHistList->addItems(HistNames);
	}
}

void SettingDialogAuto::ShowUsageHistList(void)
{
	ui->listWidgetCurrentUse->clear();

	AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		for(IntClass *HID=HistID.GetFirst();HID!=NULL;HID=HID->GetNext()){
			QString	HistName=ABase->GetHistgramName(HID->GetValue());
			ui->listWidgetCurrentUse->addItem(HistName);
		}
	}
}
void SettingDialogAuto::on_listWidgetHistList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonUseCurrent_clicked();
}


void SettingDialogAuto::on_listWidgetCurrentUse_doubleClicked(const QModelIndex &index)
{
	on_pushButtonReturnCurrent_clicked();
}


void SettingDialogAuto::on_pushButtonUseCurrent_clicked()
{
	int	row = ui->listWidgetHistList->currentRow();
	if(row>=0){
		AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(LibType);
		if(ABase!=NULL){
			int	HistIDSelect=ABase->GetHistgramID(row);
			if(HistID.IsInclude(HistIDSelect)==false){
				HistID.Add(HistIDSelect);
			}
			ShowUsageHistList();
		}
	}
}


void SettingDialogAuto::on_pushButtonReturnCurrent_clicked()
{
	int	row = ui->listWidgetCurrentUse->currentRow();
	if(row>=0){
		IntClass	*c=HistID.GetItem(row);
		if(c!=NULL){
			HistID.RemoveList(c);
			ShowUsageHistList();
		}
	}
}


void SettingDialogAuto::on_pushButtonOK_clicked()
{
	ButtonName = ui->lineEditButtonName->text();
	done(true);
}


void SettingDialogAuto::on_pushButtonCancel_clicked()
{
	done(false);
}

