#include "PropertyGerberFastFormResource.h"
#include "MakeAlgorithmUpperDialog.h"
#include "ui_MakeAlgorithmUpperDialog.h"
#include "XLibraryType.h"
#include "XDataInLayer.h"
#include "XGerberFast.h"
#include "XGerberFastPacket.h"
#include "PropertyGerberFastForm.h"
#include "XGerberFastComposite.h"
#include "XRememberer.h"
#include "XGeneralDialog.h"

MakeAlgorithmUpperDialog::MakeAlgorithmUpperDialog(  AlgoGenerationalContainer &_CurrentMakeAlgoAllList
													,PropertyGerberFastForm *hparent
													,LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
	,Parent(hparent)
    ,ui(new Ui::MakeAlgorithmUpperDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	MakeAlgoAllList=_CurrentMakeAlgoAllList;

	pLibFolderSelect=new GeneralLibFolderForm(-1,GetLayersBase(),ui->frameLibFolderSelect);
	connect(pLibFolderSelect,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolderSelect(int,QString)));
	ui->tableWidgetLibListSelect->setColumnWidth (0, 40);
	ui->tableWidgetLibListSelect->setColumnWidth (1, 150);
	ui->tableWidgetSelected->setColumnWidth (0, 130);
	ui->tableWidgetSelected->setColumnWidth (1, 50);
	ui->tableWidgetSelected->setColumnWidth (2, 130);
	SetLibTypeInComboBox();

	ui->tableWidgetCrossedLayer->setColumnWidth(0,28);
	ui->tableWidgetCrossedLayer->setColumnWidth(1,100);
	ui->tableWidgetCrossedLayer->setColumnWidth(2,84);
	ui->tableWidgetCrossedLayer->setColumnWidth(3,220);
	ui->tableWidgetCrossedLayer->setColumnWidth(4,32);

	AlgoGenerationalContainer &BaseMakeAlgoAllList	=Parent->MakeAlgoAllList;
	GerberFastBase	*Base=hparent->GetGerberFastBase();
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
	ui->tableWidgetCrossedLayer->setRowCount(MakeAlgoAllList.GetCount());
	int	Row=0;
	for(AlgoGenerationalLine *a=MakeAlgoAllList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		if(AlgoGenerationalLine::IsLayer(a->AutoGenType)==true)
			::SetDataToTable(ui->tableWidgetCrossedLayer,0,Row,/**/"L");
		else
			::SetDataToTable(ui->tableWidgetCrossedLayer,0,Row,/**/"C");
		switch(a->AutoGenType){
			case AlgoGenerationalLine::_Gen_FromLayer				:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_42)/*"Gerber"*/);
				break;
			case AlgoGenerationalLine::_GenFromShiftable			:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_43)/*"Shiftable"*/);
				break;
			case AlgoGenerationalLine::_GenFromEnlarge			:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_44)/*"Enlarge"*/);
				break;
			case AlgoGenerationalLine::_GenFromShrinked			:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_45)/*"Shrinked"*/);
				break;
			case AlgoGenerationalLine::_GenFromUnstable			:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_46)/*"Unstable"*/);
				break;
			case AlgoGenerationalLine::_GenFromStable				:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_47)/*"Stable"*/);
				break;
			case AlgoGenerationalLine::_GenFromComposite			:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_48)/*"Composite"*/);
				break;
			case AlgoGenerationalLine::_GenFromCompositeShiftable	:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_49)/*"Comp/Shiftable"*/);
				break;
			case AlgoGenerationalLine::_GenFromCompositeEnlarge	:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_50)/*"Comp/Enlarge"*/);
				break;
			case AlgoGenerationalLine::_GenFromCompositeShrinked	:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_51)/*"Comp/Shrinked"*/);
				break;
			case AlgoGenerationalLine::_GenFromCompositeUnstable	:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_52)/*"Comp/Unstable"*/);
				break;
			case AlgoGenerationalLine::_GenFromCompositeStable	:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_53)/*"Comp/Stable"*/);
				break;
			default:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_54)/*"Unknown"*/);
		}
		if(AlgoGenerationalLine::IsLayer(a->AutoGenType)==true){
			::SetDataToTable(ui->tableWidgetCrossedLayer,2,Row,Parent->child[a->BaseLayerID]->GetLibName());
			QFileInfo	Info(Parent->child[a->BaseLayerID]->EditFileName.text());
			::SetDataToTable(ui->tableWidgetCrossedLayer,3,Row,Info.fileName());
		}
		else{
			if(a->BaseLayerID<0)
				::SetDataToTable(ui->tableWidgetCrossedLayer,2,Row,/**/"");
			else{
				GerberCompositeDefLayer	*s=Base->CompositeDef.Search(a->BaseLayerID);
				if(s!=NULL){
					::SetDataToTable(ui->tableWidgetCrossedLayer,2,Row,s->Name);
				}
				else{
					::SetDataToTable(ui->tableWidgetCrossedLayer,2,Row,/**/"");
				}
			}
			//::SetDataToTable(ui->tableWidgetCrossedLayer,2,Row,Parent->CompChild[a->BaseLayerID]->ComboBComposite.currentText());
			::SetDataToTable(ui->tableWidgetCrossedLayer,3,Row,Parent->CompChild[a->BaseLayerID]->EditRemark.text());
		}
	}
	ShowLibrariesCount();

	QString	DLLRoot,DLLName;
	Base->GetAlgorithmRootName(DLLRoot,DLLName);
	pLibFolderSelect->SetCurrentLibFolder(ControlRememberer::GetInt(DLLName+objectName()+pLibFolderSelect->objectName(),0));

	InstallOperationLog(this);
}

MakeAlgorithmUpperDialog::~MakeAlgorithmUpperDialog()
{
    delete ui;
}

void	MakeAlgorithmUpperDialog::ShowLibrariesCount(void)
{
	int	Row=0;
	for(AlgoGenerationalLine *a=MakeAlgoAllList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetCrossedLayer,4,Row,QString::number(a->Libraries.GetCount()));
	}
}

void	MakeAlgorithmUpperDialog::SetLibTypeInComboBox(void)
{
	ui->comboBoxLibTypeSelect->clear();
	for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
		if(ABase!=NULL){
			ui->comboBoxLibTypeSelect->addItem(ABase->GetNameByCurrentLanguage(),(int)L->GetLibType());
		}
	}
}
void	MakeAlgorithmUpperDialog::ShowFolder(int LibType)
{
	pLibFolderSelect->SetLibType(LibType);
}
void	MakeAlgorithmUpperDialog::SlotSelectLibFolderSelect(int libFolderID ,QString FolderName)
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

void MakeAlgorithmUpperDialog::on_tableWidgetCrossedLayer_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetCrossedLayer->currentRow();
	if(Row<0)
		return;
	AlgoGenerationalLine	*a=MakeAlgoAllList[Row];
	if(a==NULL)
		return;
	Libraries	=a->Libraries;
	ShowLibraries();
}

void MakeAlgorithmUpperDialog::ShowLibraries(void)
{
	ui->tableWidgetSelected->setRowCount(Libraries.GetCount());
	int	row=0;
	for(AlgorithmLibraryList *a=Libraries.GetFirst();a!=NULL;a=a->GetNext(),row++){
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
			::SetDataToTable(ui->tableWidgetSelected,0,row ,LangSolver.GetString(MakeAlgorithmUpperDialog_LS,LID_55)/*"Not registered"*/);
		}
		::SetDataToTable(ui->tableWidgetSelected,1,row ,QString::number(a->GetLibID()));
		::SetDataToTable(ui->tableWidgetSelected,2,row ,a->GetLibName());
	}
}

void MakeAlgorithmUpperDialog::on_comboBoxLibTypeSelect_currentIndexChanged(int index)
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

void MakeAlgorithmUpperDialog::on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelectButton_clicked();
}

void MakeAlgorithmUpperDialog::on_pushButtonSelectButton_clicked()
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

void MakeAlgorithmUpperDialog::on_tableWidgetSelected_doubleClicked(const QModelIndex &index)
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

void MakeAlgorithmUpperDialog::on_pushButtonUpdate_clicked()
{
	int	Row=ui->tableWidgetCrossedLayer->currentRow();
	if(Row<0)
		return;
	AlgoGenerationalLine	*a=MakeAlgoAllList[Row];
	if(a==NULL)
		return;
	a->Libraries=Libraries;
	ShowLibrariesCount();
}

void MakeAlgorithmUpperDialog::on_pushButtonClose_clicked()
{
	close();
}
