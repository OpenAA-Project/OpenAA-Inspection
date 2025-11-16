#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "SetectSearchItemDialog.h"
#include "ui_SetectSearchItemDialog.h"
#include "XParamGlobal.h"
#include "XIntClass.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGeneralFunc.h"
#include "XDataAlgorithm.h"
#include "SelectItemForm.h"


SetectSearchItemDialog::SetectSearchItemDialog(AlgorithmBase *_Algo ,ListPageLayerIDLibNamePack &itemIDList ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(_Algo->GetLayersBase())
    ,ui(new Ui::SetectSearchItemDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
	LangDISolver.SetUI(this);

	Algo		=_Algo;

	ui->tableWidgetItems	->setColumnWidth(0,52);
	ui->tableWidgetItems	->setColumnWidth(1,52);
	ui->tableWidgetItems	->setColumnWidth(2,72);
	ui->tableWidgetItems	->setColumnWidth(3,72);
	ui->tableWidgetItems	->setColumnWidth(4,200);
	ui->tableWidgetItems	->setColumnWidth(5,185);

	ItemIDList=itemIDList;
	ShowList();

	InstallOperationLog(this);
}

SetectSearchItemDialog::~SetectSearchItemDialog()
{
    delete ui;
}

void	SetectSearchItemDialog::ShowList(void)
{
	LibIDNameContainer	LibIDStock;
	for(ListPageLayerIDLibName *d=ItemIDList.GetFirst();d!=NULL;d=d->GetNext()){
		LibIDNameList	*s=LibIDStock.IsInclude(d->LibID);
		if(s==NULL){
			s=new LibIDNameList();
			s->LibID=d->LibID;
			LibIDStock.AppendList(s);
		}
	}
	for(LibIDNameList	*s=LibIDStock.GetFirst();s!=NULL;s=s->GetNext()){
		s->LibName=Algo->GetLibraryContainer()->GetLibraryName(s->LibID);
	}
	ui->tableWidgetItems->setUpdatesEnabled(false);
	int	Row=0;
	ui->tableWidgetItems->setRowCount(ItemIDList.GetCount());
	for(ListPageLayerIDLibName *d=ItemIDList.GetFirst();d!=NULL;d=d->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetItems ,0,Row ,QString::number(d->Page));
		::SetDataToTable(ui->tableWidgetItems ,1,Row ,QString::number(d->Layer));
		::SetDataToTable(ui->tableWidgetItems ,2,Row ,QString::number(d->ID));
		::SetDataToTable(ui->tableWidgetItems ,3,Row ,QString::number(d->LibID));
		//QString	LibName=Algo->GetLibraryContainer()->GetLibraryName(d->LibID);
		LibIDNameList	*s=LibIDStock.IsInclude(d->LibID);
		if(s!=NULL)
			::SetDataToTable(ui->tableWidgetItems ,4,Row ,s->LibName);
		else
			::SetDataToTable(ui->tableWidgetItems ,4,Row ,/**/"");
		::SetDataToTable(ui->tableWidgetItems ,5,Row ,d->ItemName);
	}
	ui->tableWidgetItems->setUpdatesEnabled(true);
}

void	SetectSearchItemDialog::SelectOnes(void)
{
	SelectedItems.RemoveAll();
	IntList Rows;
	::GetSelectedRows(ui->tableWidgetItems,Rows);
	for(IntClass *d=Rows.GetFirst();d!=NULL;d=d->GetNext()){
		ListPageLayerIDLibName	*c=ItemIDList.GetItem(d->GetValue());
		if(c!=NULL){
			SelectedItems.AppendList(new ListPageLayerID(c->Page,c->Layer,c->ID));
		}
	}
}

static	int	SortByIDFunc(const void *a ,const void *b)
{
	ListPageLayerIDLibName	**ka=(ListPageLayerIDLibName **)a;
	ListPageLayerIDLibName	**kb=(ListPageLayerIDLibName **)b;
	int	d= ka[0]->ID - kb[0]->ID;
	if(d!=0)
		return d;
	d=ka[0]->Page - kb[0]->Page;
	if(d!=0)
		return d;
	d=ka[0]->Layer - kb[0]->Layer;
	if(d!=0)
		return d;
	return 0;
}
static	int	SortByLibIDFunc(const void *a ,const void *b)
{
	ListPageLayerIDLibName	**ka=(ListPageLayerIDLibName **)a;
	ListPageLayerIDLibName	**kb=(ListPageLayerIDLibName **)b;
	return ka[0]->LibID - kb[0]->LibID;
}
static	int	SortByItemNameFunc(const void *a ,const void *b)
{
	ListPageLayerIDLibName	**ka=(ListPageLayerIDLibName **)a;
	ListPageLayerIDLibName	**kb=(ListPageLayerIDLibName **)b;
	if(ka[0]->ItemName>kb[0]->ItemName)
		return 1;
	if(ka[0]->ItemName<kb[0]->ItemName)
		return -1;
	return 0;
}

void SetectSearchItemDialog::on_pushButtonSortByID_clicked()
{
	int	N=ItemIDList.GetCount();
	ListPageLayerIDLibName	**Dim=new ListPageLayerIDLibName*[N];
	
	for(int i=0;i<N;i++){
		ListPageLayerIDLibName	*p=ItemIDList.GetFirst();
		ItemIDList.RemoveList(p);
		Dim[i]=p;
	}
	QSort(Dim,N,sizeof(Dim[0]),SortByIDFunc);

	for(int i=0;i<N;i++){
		ItemIDList.AppendList(Dim[i]);
	}
	delete	[]Dim;

	ShowList();

	int	Row=0;
	int	TopID=ui->spinBoxTopID->value();
	for(ListPageLayerIDLibName *d=ItemIDList.GetFirst();d!=NULL;d=d->GetNext(),Row++){
		if(d->ID>=TopID){
			break;
		}
	}
	if(Row<ItemIDList.GetCount()){
		ui->tableWidgetItems->setCurrentCell(Row,0);
		QModelIndex RIndex=ui->tableWidgetItems->currentIndex();
		ui->tableWidgetItems->scrollTo(RIndex);
	}
}

void SetectSearchItemDialog::on_pushButtonSortByLibID_clicked()
{
	int	N=ItemIDList.GetCount();
	ListPageLayerIDLibName	**Dim=new ListPageLayerIDLibName*[N];
	
	for(int i=0;i<N;i++){
		ListPageLayerIDLibName	*p=ItemIDList.GetFirst();
		ItemIDList.RemoveList(p);
		Dim[i]=p;
	}
	QSort(Dim,N,sizeof(Dim[0]),SortByLibIDFunc);

	for(int i=0;i<N;i++){
		ItemIDList.AppendList(Dim[i]);
	}
	delete	[]Dim;

	ShowList();
}

void SetectSearchItemDialog::on_pushButtonSortByName_clicked()
{
	int	N=ItemIDList.GetCount();
	ListPageLayerIDLibName	**Dim=new ListPageLayerIDLibName*[N];
	
	for(int i=0;i<N;i++){
		ListPageLayerIDLibName	*p=ItemIDList.GetFirst();
		ItemIDList.RemoveList(p);
		Dim[i]=p;
	}
	QSort(Dim,N,sizeof(Dim[0]),SortByItemNameFunc);

	for(int i=0;i<N;i++){
		ItemIDList.AppendList(Dim[i]);
	}
	delete	[]Dim;

	ShowList();

	int	Row=0;
	QString	TopName=ui->lineEditTopName->text();
	for(ListPageLayerIDLibName *d=ItemIDList.GetFirst();d!=NULL;d=d->GetNext(),Row++){
		if(d->ItemName>=TopName){
			break;
		}
	}
	if(Row<ItemIDList.GetCount()){
		ui->tableWidgetItems->setCurrentCell(Row,0);
		QModelIndex RIndex=ui->tableWidgetItems->currentIndex();
		ui->tableWidgetItems->scrollTo(RIndex);
	}
}

void SetectSearchItemDialog::on_ButtonSelectAndView_clicked()
{
	SelectOnes();
	done(1);
}

void SetectSearchItemDialog::on_ButtonOnlyView_clicked()
{
	SelectOnes();
	done(2);
}

void SetectSearchItemDialog::on_pushButtonCancel_clicked()
{
	done(-1);
}

void SetectSearchItemDialog::on_pushButtonSortByItemID_clicked()
{

}
