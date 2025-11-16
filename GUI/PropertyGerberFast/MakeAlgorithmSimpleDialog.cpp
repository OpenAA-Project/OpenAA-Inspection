#include "PropertyGerberFastFormResource.h"
#include "MakeAlgorithmSimpleDialog.h"
#include "ui_MakeAlgorithmSimpleDialog.h"
#include "XLibraryType.h"
#include "XDataInLayer.h"
#include "XGerberFast.h"
#include "XGerberFastPacket.h"
#include "PropertyGerberFastForm.h"
#include "XGerberFastComposite.h"
#include "XRememberer.h"
#include "XGeneralDialog.h"

MakeAlgorithmSimpleDialog::MakeAlgorithmSimpleDialog(AlgoGenerationalContainer &_CurrentMakeAlgoAllList
													,int _BaseRow
													,PropertyGerberFastForm *hparent
													,LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
 	,Parent(hparent)
	,ui(new Ui::MakeAlgorithmSimpleDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	BaseRow=_BaseRow;
	MakeAlgoAllList=_CurrentMakeAlgoAllList;

	pLibFolderSelect=new GeneralLibFolderForm(-1,GetLayersBase(),ui->frameLibFolderSelect);
	connect(pLibFolderSelect,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolderSelect(int,QString)));
	ui->tableWidgetLibListSelect->setColumnWidth (0, 40);
	ui->tableWidgetLibListSelect->setColumnWidth (1, 150);
	ui->tableWidgetSelected->setColumnWidth (0, 130);
	ui->tableWidgetSelected->setColumnWidth (1, 50);
	ui->tableWidgetSelected->setColumnWidth (2, 130);
	SetLibTypeInComboBox();


	AlgoGenerationalContainer &BaseMakeAlgoAllList	=Parent->MakeAlgoAllList;
	GerberFastBase	*Base=Parent->GetGerberFastBase();
	if(Base==NULL)
		return;

	int		N=0;
	for(AlgoGenerationalLine *t=BaseMakeAlgoAllList.GetFirst();t!=NULL;t=t->GetNext(),N++){
		if(MakeAlgoAllList[N]==NULL){
			int	id=MakeAlgoAllList.GetMaxID()+1;
			AlgoGenerationalLine	*aLayer=new AlgoGenerationalLine(id);
			aLayer->BaseLayerID	=t->BaseLayerID;
			aLayer->AutoGenType	=t->AutoGenType;
			MakeAlgoAllList.AppendList(aLayer);
		}
	}
	Libraries	=MakeAlgoAllList[BaseRow]->Libraries;
	ShowLibraries();

	QString	DLLRoot,DLLName;
	Base->GetAlgorithmRootName(DLLRoot,DLLName);
	pLibFolderSelect->SetCurrentLibFolder(ControlRememberer::GetInt(DLLName+objectName()+pLibFolderSelect->objectName(),0));

	InstallOperationLog(this);
}

MakeAlgorithmSimpleDialog::~MakeAlgorithmSimpleDialog()
{
    delete ui;
}

void	MakeAlgorithmSimpleDialog::SetLibTypeInComboBox(void)
{
	ui->comboBoxLibTypeSelect->clear();
	for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
		if(ABase!=NULL){
			ui->comboBoxLibTypeSelect->addItem(ABase->GetNameByCurrentLanguage(),(int)L->GetLibType());
		}
	}
}
void	MakeAlgorithmSimpleDialog::ShowFolder(int LibType)
{
	pLibFolderSelect->SetLibType(LibType);
}
void	MakeAlgorithmSimpleDialog::SlotSelectLibFolderSelect(int libFolderID ,QString FolderName)
{
	CurrentLibFolderID=libFolderID;

	GerberFastBase	*BBase=Parent->GetGerberFastBase();
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
void MakeAlgorithmSimpleDialog::ShowLibraries(void)
{
	ui->tableWidgetSelected->setRowCount(Libraries.GetCount());
	int	row=0;
	for(AlgorithmLibraryList *a=Libraries.GetFirst();a!=NULL;a=a->GetNext(),row++){
		LibraryTypeList	*LType=GetLayersBase()->GetInstalledLibType()->FindLibraryType(a->GetLibType());
		if(LType!=NULL){
			AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase((int)LType->GetLibType());
			if(ABase!=NULL){
				::SetDataToTable(ui->tableWidgetSelected,0,row ,ABase->GetNameByCurrentLanguage());
			}
			else{
				::SetDataToTable(ui->tableWidgetSelected,0,row ,LType->GetLibName());
			}
		}
		else{
			::SetDataToTable(ui->tableWidgetSelected,0,row ,LangSolver.GetString(MakeAlgorithmSimpleDialog_LS,LID_41)/*"Not registered"*/);
		}
		::SetDataToTable(ui->tableWidgetSelected,1,row ,QString::number(a->GetLibID()));
		::SetDataToTable(ui->tableWidgetSelected,2,row ,a->GetLibName());
	}
}

void MakeAlgorithmSimpleDialog::on_comboBoxLibTypeSelect_currentIndexChanged(int index)
{
	int	Index=ui->comboBoxLibTypeSelect->currentIndex();
	if(Index<0)
		return;
	
	QVariant V=ui->comboBoxLibTypeSelect->itemData (Index);

	//LibraryTypeList *L=GetLayersBase()->GetLibType()->GetItem(Index);
	//if(L==NULL)
	//	return;
	//CurrentLibType=L->LibType;
	CurrentLibType=V.toInt();
	ShowFolder(CurrentLibType);
	LibIDListSelect.RemoveAll();
	ui->tableWidgetLibListSelect->setRowCount(0);
}

void MakeAlgorithmSimpleDialog::on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelectButton_clicked();
}

void MakeAlgorithmSimpleDialog::on_pushButtonSelectButton_clicked()
{
	int	r=ui->tableWidgetLibListSelect->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=LibIDListSelect[r];
	if(a==NULL)
		return;
	AlgorithmLibraryList	*d=new AlgorithmLibraryList(*a);
	Libraries.AppendList(d);

	ShowLibraries();
}

void MakeAlgorithmSimpleDialog::on_tableWidgetSelected_doubleClicked(const QModelIndex &index)
{
	int	r=ui->tableWidgetSelected->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*d=Libraries[r];
	if(d!=NULL){
		Libraries.RemoveList(d);
		delete	d;
		ShowLibraries();
	}
}

void MakeAlgorithmSimpleDialog::on_pushButtonUpdate_clicked()
{
	AlgoGenerationalLine	*a=MakeAlgoAllList[BaseRow];
	if(a==NULL)
		return;
	a->Libraries=Libraries;

	done(true);
}

void MakeAlgorithmSimpleDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
