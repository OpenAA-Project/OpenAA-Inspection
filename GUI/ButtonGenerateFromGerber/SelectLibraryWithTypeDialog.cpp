#include "SelectLibraryWithTypeDialog.h"
#include "ui_SelectLibraryWithTypeDialog.h"
#include "XLibraryType.h"
#include "XDataInLayer.h"
#include "XRememberer.h"
#include "XDatabaseLoader.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XGeneralDialog.h"

extern	const	char	*AlgoRoot;
extern	const	char	*AlgoName;

SelectLibraryWithTypeDialog::SelectLibraryWithTypeDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SelectLibraryWithTypeDialog)
{
    ui->setupUi(this);
	CurrentLibType	=-1;
	SelectedLibID	=-1;
		
	pLibFolderSelect=new GeneralLibFolderForm(-1,GetLayersBase(),ui->frameLibFolderSelect);
	connect(pLibFolderSelect,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolderSelect(int,QString)));
	ui->tableWidgetLibListSelect->setColumnWidth (0, 60);
	ui->tableWidgetLibListSelect->setColumnWidth (1, 150);

	SetLibTypeInComboBox();

	InstallOperationLog(this);
}

SelectLibraryWithTypeDialog::~SelectLibraryWithTypeDialog()
{
    delete ui;
}
void	SelectLibraryWithTypeDialog::Initial(void)
{
	if(CurrentLibType>=0){
		ShowFolder(CurrentLibType);

		if(SelectedLibID>=0){
			int		FolderID=GetLayersBase()->GetDatabaseLoader()->S_GetLibraryFolderID(*GetLayersBase()->GetDataBase() ,CurrentLibType,SelectedLibID);
			if(FolderID>=0){
				SlotSelectLibFolderSelect(FolderID,/**/"");
				int	row=0;
				IntList Rows;
				for(AlgorithmLibraryList *a=LibIDListSelect.GetFirst();a!=NULL;a=a->GetNext(),row++){
					if(a->GetLibID()==SelectedLibID){
						Rows.Add(row);
					}
				}
				::SetSelectedRows(ui->tableWidgetLibListSelect ,Rows);
			}
		}
	}
}

GerberFastBase	*SelectLibraryWithTypeDialog::GetGerberFastBase(void)
{
	GerberFastBase	*Base=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	return Base;
}

void	SelectLibraryWithTypeDialog::SetLibTypeInComboBox(void)
{
	ui->comboBoxLibTypeSelect->clear();
	for(LibraryTypeList *L=GetLayersBase()->GetLibType()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase((int)L->GetLibType());
		if(ABase!=NULL){
			ui->comboBoxLibTypeSelect->addItem(ABase->GetNameByCurrentLanguage(),(int)L->GetLibType());
		}
	}
}
void	SelectLibraryWithTypeDialog::ShowFolder(int LibType)
{
	pLibFolderSelect->SetLibType(LibType);
}
void	SelectLibraryWithTypeDialog::SlotSelectLibFolderSelect(int libFolderID ,QString FolderName)
{
	CurrentLibFolderID=libFolderID;

	GerberFastBase	*BBase=GetGerberFastBase();
	QString	DLLRoot,DLLName;
	BBase->GetAlgorithmRootName(DLLRoot,DLLName);
	ControlRememberer::SetValue(DLLName+objectName()+pLibFolderSelect->objectName() ,CurrentLibFolderID);

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

void SelectLibraryWithTypeDialog::on_comboBoxLibTypeSelect_currentIndexChanged(int index)
{
	int	Index=ui->comboBoxLibTypeSelect->currentIndex();
	if(Index<0)
		return;
	
	QVariant V=ui->comboBoxLibTypeSelect->itemData (Index);
	CurrentLibType=V.toInt();
	ShowFolder(CurrentLibType);
	LibIDListSelect.RemoveAll();
	ui->tableWidgetLibListSelect->setRowCount(0);
}

void SelectLibraryWithTypeDialog::on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}

void SelectLibraryWithTypeDialog::on_pushButtonSelect_clicked()
{
	int	r=ui->tableWidgetLibListSelect->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=LibIDListSelect[r];
	if(a==NULL)
		return;
	SelectedLibID	=a->GetLibID();
	done(true);
}

void SelectLibraryWithTypeDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
