#include "AddSourceItemDialogResource.h"
#include "SearchItemDialog.h"
#include "ui_SearchItemDialog.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

SearchItemDialog::SearchItemDialog(LayersBase *Base,AlgorithmBase *abase,int _GlobalPage ,int _Layer,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::SearchItemDialog)
{
    ui->setupUi(this);
	ABase		=abase;
	GlobalPage	=_GlobalPage;
	Layer		=_Layer;

	GUICmdReqSourceAllItemsInfo		RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	GUICmdSendSourceAllItemsInfo	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	RCmd.Layer	=Layer;
	ABase->GetAlgorithmRootName(RCmd.AlgoRoot,RCmd.AlgoName);
	if(RCmd.Send(GlobalPage,0,ACmd)==true){
		ItemList	=ACmd.ItemInfos;
	}

	ui->tableWidgetItems	->setColumnWidth(0,48);
	ui->tableWidgetItems	->setColumnWidth(1,100);
	ui->tableWidgetItems	->setColumnWidth(2,200);
	ui->tableWidgetItems	->setColumnWidth(3,48);
	ui->tableWidgetItems	->setColumnWidth(4,240);

	for(ItemInfoList *K=ItemList.GetFirst();K!=NULL;K=K->GetNext()){
		LibIDList	*s=LibIDStock.IsInclude(K->LibID);
		if(s==NULL){
			s=new LibIDList();
			s->LibID=K->LibID;
			LibIDStock.AppendList(s);
		}
	}
	for(LibIDList	*s=LibIDStock.GetFirst();s!=NULL;s=s->GetNext()){
		s->LibName=ABase->GetLibraryContainer()->GetLibraryName(s->LibID);
	}	

	ShowList();

	InstallOperationLog(this);
}

SearchItemDialog::~SearchItemDialog()
{
    delete ui;
}


LibIDList	*LibIDContainer::IsInclude(int LibID)
{
	for(LibIDList *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->LibID==LibID){
			return s;
		}
	}
	return NULL;
}


void	SearchItemDialog::ShowList(void)
{
	ui->tableWidgetItems->setUpdatesEnabled(false);
	ui->tableWidgetItems->setRowCount(ItemList.GetCount());
	int	Row=0;
	for(ItemInfoList *K=ItemList.GetFirst();K!=NULL;K=K->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetItems ,0,Row ,QString::number(K->ItemID));
		::SetDataToTable(ui->tableWidgetItems ,1,Row ,K->ItemName);
		::SetDataToTable(ui->tableWidgetItems ,2,Row ,QString(/**/"(")
													+ QString::number(K->x1)+QString(/**/",")+QString::number(K->y1)
													+ QString(/**/")-(")
													+ QString::number(K->x2)+QString(/**/",")+QString::number(K->y2)
													+ QString(/**/")"));
		::SetDataToTable(ui->tableWidgetItems ,3,Row ,QString::number(K->LibID));
		LibIDList	*s=LibIDStock.IsInclude(K->LibID);
		if(s!=NULL){
			::SetDataToTable(ui->tableWidgetItems ,4,Row ,s->LibName);
		}
	}
	ui->tableWidgetItems->setUpdatesEnabled(true);
}

class	ItemInfoListPointerID : public NPList<ItemInfoListPointerID>
{
public:
	ItemInfoList	*P;

	ItemInfoListPointerID(ItemInfoList *p):P(p){}

	int	Compare(ItemInfoListPointerID &src){	return P->ItemID - src.P->ItemID;	}
};


void SearchItemDialog::on_pushButtonSortByID_clicked()
{
	NPListPack<ItemInfoListPointerID>	IDContainer;
	ItemInfoList	*p;
	while((p=ItemList.GetFirst())!=NULL){
		ItemList.RemoveList(p);
		ItemInfoListPointerID	*s=new ItemInfoListPointerID(p);
		IDContainer.AppendList(s);
	}
	IDContainer.Sort();
	for(ItemInfoListPointerID *q=IDContainer.GetFirst();q!=NULL;q=q->GetNext()){
		ItemList.AppendList(q->P);
	}
	ShowList();
	int	Row=0;
	int	TopID=ui->spinBoxTopID->value();
	for(ItemInfoList *p=ItemList.GetFirst();p!=NULL;p=p->GetNext(),Row++){
		if(p->ItemID>=TopID){
			break;
		}
	}
	if(Row<ItemList.GetCount()){
		ui->tableWidgetItems->setCurrentCell(Row,0);
		QModelIndex RIndex=ui->tableWidgetItems->currentIndex();
		ui->tableWidgetItems->scrollTo(RIndex);
	}
}

class	ItemInfoListPointerName : public NPList<ItemInfoListPointerName>
{
public:
	ItemInfoList	*P;

	ItemInfoListPointerName(ItemInfoList *p):P(p){}

	int	Compare(ItemInfoListPointerName &src)
	{	
		if(P->ItemName>src.P->ItemName)
			return 1;
		if(P->ItemName<src.P->ItemName)
			return -1;
		return 0;
	}
};


void SearchItemDialog::on_pushButtonSortByName_clicked()
{
	NPListPack<ItemInfoListPointerName>	NameContainer;
	ItemInfoList	*p;
	while((p=ItemList.GetFirst())!=NULL){
		ItemList.RemoveList(p);
		ItemInfoListPointerName	*s=new ItemInfoListPointerName(p);
		NameContainer.AppendList(s);
	}
	NameContainer.Sort();
	for(ItemInfoListPointerName *q=NameContainer.GetFirst();q!=NULL;q=q->GetNext()){
		ItemList.AppendList(q->P);
	}
	ShowList();
	int	Row=0;
	QString	TopName=ui->lineEditTopName->text();
	for(ItemInfoList *p=ItemList.GetFirst();p!=NULL;p=p->GetNext(),Row++){
		if(p->ItemName>=TopName){
			break;
		}
	}
	if(Row<ItemList.GetCount()){
		ui->tableWidgetItems->setCurrentCell(Row,0);
		QModelIndex RIndex=ui->tableWidgetItems->currentIndex();
		ui->tableWidgetItems->scrollTo(RIndex);
	}
}

void SearchItemDialog::on_pushButtonOK_clicked()
{
	int	R=ui->tableWidgetItems->currentRow();
	if(R<0)
		return;
	ItemInfoList *p=ItemList[R];
	ItemID=p->ItemID;

	done(true);
}

void SearchItemDialog::on_pushButtonCancel_clicked()
{
	done(false);
}


class	ItemInfoListPointerLib : public NPList<ItemInfoListPointerLib>
{
public:
	ItemInfoList	*P;

	ItemInfoListPointerLib(ItemInfoList *p):P(p){}

	int	Compare(ItemInfoListPointerLib &src){	return P->LibID - src.P->LibID;	}
};


void SearchItemDialog::on_pushButtonSortByLibID_clicked()
{
	NPListPack<ItemInfoListPointerLib>	IDContainer;
	ItemInfoList	*p;
	while((p=ItemList.GetFirst())!=NULL){
		ItemList.RemoveList(p);
		ItemInfoListPointerLib	*s=new ItemInfoListPointerLib(p);
		IDContainer.AppendList(s);
	}
	IDContainer.Sort();
	for(ItemInfoListPointerLib *q=IDContainer.GetFirst();q!=NULL;q=q->GetNext()){
		ItemList.AppendList(q->P);
	}
	ShowList();
}
