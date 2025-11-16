#include "ShowHistgramSelectFormResource.h"
#include "ShowHistgramSelectForm.h"
#include "ui_ShowHistgramSelectForm.h"
#include "XShowHistgramTotalPacket.h"
#include "XGeneralFunc.h"
#include "ShowTotalHistgramGraphForm.h"
#include "XAlgorithmLibrary.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowHistgramSelectForm::ShowHistgramSelectForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ShowHistgramSelectForm)
{
    ui->setupUi(this);

	::SetColumnWidthInTable(ui->tableWidget,0, 30);
	::SetColumnWidthInTable(ui->tableWidget,1, 35);
	::SetColumnWidthInTable(ui->tableWidget,2, 35);

	::SetColumnWidthInTable(ui->tableWidget_2,0, 20);
	::SetColumnWidthInTable(ui->tableWidget_2,1, 100);
	::SetColumnWidthInTable(ui->tableWidget_2,2, 30);
}

ShowHistgramSelectForm::~ShowHistgramSelectForm()
{
    delete ui;
}

int	HistgramTypeListFunc(const void *a ,const void *b)
{
	HistgramTypeList	**ha=(HistgramTypeList	**)a;
	HistgramTypeList	**hb=(HistgramTypeList	**)b;

	if(ha[0]->AlgoRoot>hb[0]->AlgoRoot)
		return 1;
	if(ha[0]->AlgoRoot<hb[0]->AlgoRoot)
		return -1;

	if(ha[0]->AlgoName>hb[0]->AlgoName)
		return 1;
	if(ha[0]->AlgoName<hb[0]->AlgoName)
		return -1;

	if(ha[0]->HistID>hb[0]->HistID)
		return 1;
	if(ha[0]->HistID<hb[0]->HistID)
		return -1;
	return 0;
}

void ShowHistgramSelectForm::on_pushButtonReDraw_clicked()
{
	HContainer.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqHistgramTypeList	RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
		GUICmdSendHistgramTypeList	SCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
		if(RCmd.Send(GlobalPage,0,SCmd)==true){
			for(HistgramTypeList *a=SCmd.HContainer.GetFirst();a!=NULL;a=a->GetNext()){
				HistgramTypeList *b;
				for(b=HContainer.GetFirst();b!=NULL;b=b->GetNext()){
					if(*b==*a){
						break;
					}
				}
				if(b==NULL){
					b=new HistgramTypeList();
					*b=*a;
					HContainer.AppendList(b);
				}
			}
		}
	}
	HistgramTypeList	**LList=new HistgramTypeList*[HContainer.GetCount()];
	int	N=0;
	HistgramTypeList *a;
	while((a=HContainer.GetFirst())!=NULL){
		HContainer.RemoveList(a);
		LList[N]=a;
		N++;
	}
	QSort(LList,N,sizeof(HistgramTypeList *),HistgramTypeListFunc);
	for(int i=0;i<N;i++){
		HContainer.AppendList(LList[i]);
	}
	delete	[]LList;

	ui->tableWidget->setRowCount(HContainer.GetCount());
	int	Row=0;
	for(HistgramTypeList *m=HContainer.GetFirst();m!=NULL;m=m->GetNext()){
		::SetDataToTable(ui->tableWidget ,0,Row,m->AlgoRoot);
		::SetDataToTable(ui->tableWidget ,1,Row,m->AlgoName);
		::SetDataToTable(ui->tableWidget ,2,Row,m->HistName);
		Row++;
	}
}

void ShowHistgramSelectForm::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	HistgramTypeList *point=HContainer[Row];
	if(point==NULL)
		return;
	LibContainer.RemoveAll();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqHistgramLibrary	RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
		GUICmdSendHistgramLibrary	SCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
		RCmd.PointData=*point;
		if(RCmd.Send(GlobalPage,0,SCmd)==true){
			for(LibraryItemList *a=SCmd.LibData.GetFirst();a!=NULL;a=a->GetNext()){
				LibraryItemList	*b=LibContainer.GetLibraryItemList(a->LibID);
				if(b==NULL){
					LibraryItemList	*L=new LibraryItemList();
					*L=*a;
					LibContainer.AppendList(L);
				}
				else{
					b->ItemCount+=a->ItemCount;
				}
			}
		}
	}
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(point->AlgoRoot,point->AlgoName);
	if(ABase==NULL)
		return;
	ui->tableWidget_2->setRowCount(LibContainer.GetCount());
	int	RowL=0;
	for(LibraryItemList *a=LibContainer.GetFirst();a!=NULL;a=a->GetNext()){
		QString	LibName=ABase->GetLibraryContainer()->GetLibraryName(a->LibID);
		::SetDataToTable(ui->tableWidget_2 ,0,RowL,a->LibID);
		::SetDataToTable(ui->tableWidget_2 ,1,RowL,LibName);
		::SetDataToTable(ui->tableWidget_2 ,2,RowL,a->ItemCount);
		RowL++;
	}
}

void ShowHistgramSelectForm::on_tableWidget_2_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}

void ShowHistgramSelectForm::on_pushButtonSelect_clicked()
{
	int	RowH=ui->tableWidget->currentRow();
	if(RowH<0)
		return;
	HistgramTypeList *pointH=HContainer[RowH];
	if(pointH==NULL)
		return;

	int	Row=ui->tableWidget_2->currentRow();
	LibraryItemList *pointL=NULL;
	if(Row>=0){
		pointL=LibContainer[Row];
	}
	if(pointL!=NULL && pointH!=NULL){
		ShowTotalHistgramGraphForm	Graph(*pointH,*pointL,GetLayersBase());
		Graph.exec();
	}
}

