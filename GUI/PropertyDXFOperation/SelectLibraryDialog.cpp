#include "PropertyDXFOperationResource.h"
#include "SelectLibraryDialog.h"
#include "ui_SelectLibraryDialog.h"
#include "XRememberer.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "PropertyDXFOperationForm.h"
#include "XGeneralDialog.h"

SelectLibraryDialog::SelectLibraryDialog(DWORD AlgorithmType ,PropertyDXFOperationForm *p,LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
	,Parent(p)
    ,ui(new Ui::SelectLibraryDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmType)==true){
			LogicDLLPointerContainer.AppendList(new LogicDLLPointer(L));
		}
	}
	ui->tableWidgetAlgorithm	->setColumnWidth(0,120);
	ui->tableWidgetAlgorithm	->setColumnWidth(1,120);
	ui->tableWidgetAlgorithm	->setColumnWidth(2,240);

	ui->tableWidgetLibListSelect->setColumnWidth(0,52);
	ui->tableWidgetLibListSelect->setColumnWidth(1,180);

	pLibFolderSelect=new GeneralLibFolderForm(-1,GetLayersBase(),ui->frameLibFolderSelect);
	connect(pLibFolderSelect,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolderSelect(int,QString)));

	ui->tableWidgetAlgorithm->setRowCount(LogicDLLPointerContainer.GetCount());
	int	Row=0;
	for(LogicDLLPointer *L=LogicDLLPointerContainer.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetAlgorithm ,0 ,Row ,L->Pointer->GetDLLRoot());
		::SetDataToTable(ui->tableWidgetAlgorithm ,1 ,Row ,L->Pointer->GetDLLName());
		::SetDataToTable(ui->tableWidgetAlgorithm ,2 ,Row ,L->Pointer->GetExplain());
	}
	if(Row==1){
		LogicDLLPointer *L=LogicDLLPointerContainer.GetItem(Row);
		if(L!=NULL){
			AlgorithmLibraryContainer	*ALib=L->Pointer->GetLibContainer();
			if(ALib!=NULL){
				CurrentLibType=ALib->GetLibType();
				ShowFolder(CurrentLibType);
			}
		}
	}
}

SelectLibraryDialog::~SelectLibraryDialog()
{
    delete ui;
}

void SelectLibraryDialog::on_tableWidgetAlgorithm_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetAlgorithm->currentRow();
	if(Row<0)
		return;
	LogicDLLPointer *L=LogicDLLPointerContainer.GetItem(Row);
	if(L==NULL)
		return;
	AlgorithmLibraryContainer	*ALib=L->Pointer->GetLibContainer();
	if(ALib==NULL)
		return;
	CurrentLibType=ALib->GetLibType();
	ShowFolder(CurrentLibType);
}

void	SelectLibraryDialog::ShowFolder(int LibType)
{
	pLibFolderSelect->SetLibType(LibType);
}
void	SelectLibraryDialog::SlotSelectLibFolderSelect(int libFolderID ,QString FolderName)
{
	CurrentLibFolderID=libFolderID;

	DXFOperationBase	*BBase=Parent->GetDXFOperationBase();
	QString	DLLRoot,DLLName;
	BBase->GetAlgorithmRootName(DLLRoot,DLLName);
	ControlRememberer::SetValue(DLLName+objectName()+pLibFolderSelect->objectName() ,CurrentLibFolderID);

	ui->tableWidgetLibListSelect->setRowCount(0);
	AlgorithmLibraryContainerForEnum		LibList(GetLayersBase());
	LibIDListSelect.RemoveAll();
	//LibList.EnumLibrary(GetLayersBase()->GetDatabase(),CurrentLibType,CurrentLibFolderID ,LibIDListSelect);
	int	LibIDList[1000];
	int	LibIDNumb=LibList.EnumLibrary(GetLayersBase()->GetDatabase(),CurrentLibType,CurrentLibFolderID ,LibIDList,1000);
	for(int i=0;i<LibIDNumb;i++){
		QString	LibName=GetLayersBase()->GetLibraryName(CurrentLibType,LibIDList[i]);
		LibIDListSelect.AppendList(new AlgorithmLibraryList(CurrentLibType ,LibIDList[i] ,LibName));
	}
	int	row=0;
	ui->tableWidgetLibListSelect->setRowCount(LibIDListSelect.GetNumber());
	for(AlgorithmLibraryList *a=LibIDListSelect.GetFirst();a!=NULL;a=a->GetNext(),row++){
		::SetDataToTable(ui->tableWidgetLibListSelect,0,row ,QString::number(a->GetLibID()));
		::SetDataToTable(ui->tableWidgetLibListSelect,1,row ,a->GetLibName());
	}
}

void SelectLibraryDialog::on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}

void SelectLibraryDialog::on_pushButtonSelect_clicked()
{
	IntList	Rows;
	GetSelectedRows(ui->tableWidgetLibListSelect ,Rows);
	Selected.RemoveAll();
	for(IntClass *v=Rows.GetFirst();v!=NULL;v=v->GetNext()){
		int	Row=v->GetValue();
		AlgorithmLibraryList	*A=LibIDListSelect.GetItem(Row);
		LibIDListSelect.RemoveList(A);
		if(A!=NULL){
			Selected.AppendList(A);
		}
	}
	done(true);

}

void SelectLibraryDialog::on_pushButtonClose_clicked()
{
	done(false);
}
