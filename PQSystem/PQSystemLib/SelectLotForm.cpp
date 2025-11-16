#include "SelectLotForm.h"
#include "ui_SelectLotForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XIntegrationBase.h"
#include "IntegrationLib.h"
#include "SearchLotDialog.h"
#include "PQSystemService.h"

SelectLotForm::SelectLotForm(LayersBase *Base ,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(Base)
	,ui(new Ui::SelectLotForm)
{
    ui->setupUi(this);
	CurrentLot	=NULL;

	LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
	QStringList	Labels;
	Labels.append(LBase->GetParamPQSystem()->TitleLotID		);
	Labels.append(LBase->GetParamPQSystem()->TitleLotNumber	);
	Labels.append(LBase->GetParamPQSystem()->TitleSubCode	);
	ui->tableWidget->setHorizontalHeaderLabels(Labels);
}

SelectLotForm::~SelectLotForm()
{
    delete ui;
}

void	SelectLotForm::resizeEvent(QResizeEvent *event)
{
	ui->frame->setGeometry(0,height()-ui->frame->height()-2,width(),ui->frame->height());
	ui->tableWidget->resize(width()-2,height()-ui->frame->height()-2);

	::SetColumnWidthInTable(ui->tableWidget,0, 25);
	::SetColumnWidthInTable(ui->tableWidget,1, 25);
	::SetColumnWidthInTable(ui->tableWidget,2, 25);
	::SetColumnWidthInTable(ui->tableWidget,3, 25);
}
void SelectLotForm::on_tableWidget_itemSelectionChanged()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row>=0){
		CurrentLot=LotContainer[Row];
	}
	emit	SignalSelectLine();
}
void	SelectLotForm::Clear(void)
{
	CurrentLot=NULL;
	ui->tableWidget->setRowCount(0);
}
void SelectLotForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}
struct	MergeLotStruct
{
	LotList		*Lot;
	EachMaster	*Master;
};

int	MergeLotStructFuncByNumber(const void *a ,const void *b)
{
	struct	MergeLotStruct	*aa=(struct	MergeLotStruct *)a;
	struct	MergeLotStruct	*bb=(struct	MergeLotStruct *)b;
	int	n=aa->Lot->GlobalID<bb->Lot->GlobalID;
	return n;
}
int	MergeLotStructFuncByLotName(const void *a ,const void *b)
{
	struct	MergeLotStruct	*aa=(struct	MergeLotStruct *)a;
	struct	MergeLotStruct	*bb=(struct	MergeLotStruct *)b;
	if(aa->Lot->LotName<bb->Lot->LotName)
		return 1;
	if(aa->Lot->LotName>bb->Lot->LotName)
		return -1;
	return 0;
}
void SelectLotForm::Update()
{
	LotContainer.RemoveAll();
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		GetLayersBase()->GetIntegrationBasePointer()->LoadLotData();

		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			int	AllLotCount=m->GetLotCount();
		
			struct	MergeLotStruct	*Dim=new struct	MergeLotStruct[AllLotCount];
			int	Index=0;
			for(LotList *L=m->GetLotFirst();L!=NULL;L=L->GetNext()){
				Dim[Index].Lot=L;
				Dim[Index].Master	=m;
				Index++;
			}
			qsort(Dim,AllLotCount,sizeof(struct	MergeLotStruct),MergeLotStructFuncByLotName);
			int	GlobalID=-1;
			QString	LastLotName;
			for(int i=0;i<AllLotCount;i++){
				LotListWithResult	*L;
				for(L=LotContainer.GetFirst();L!=NULL;L=L->GetNext()){
					if(L->CurrentInspection.GetFirst()->LotListData.LotName==Dim[i].Lot->LotName){
						Dim[i].Lot->GlobalID=L->CurrentInspection.GetFirst()->LotListData.GlobalID;
						break;
					}
				}
				if(L==NULL){
					GlobalID=LotContainer.GetCount();
					L=new LotListWithResult();
					InspectionListByMaster	*LotM=new InspectionListByMaster();
					L->CurrentInspection.AppendList(LotM);
					LotM->MachineID=m->GetMachineCode();
					LotM->LotListData	=*Dim[i].Lot;
					LotM->LotListData.GlobalID		=GlobalID;
					Dim[i].Lot->GlobalID	=GlobalID;
					LotContainer.AppendList(L);
				}
			}
			delete	[]Dim;
		}
		ui->tableWidget->setRowCount(LotContainer.GetCount());
		int	Row=0;
		for(LotListWithResult *L=LotContainer.GetFirst();L!=NULL;L=L->GetNext(),Row++){
			::SetDataToTable(ui->tableWidget, 0, Row, L->CurrentInspection.GetFirst()->LotListData.LotID);
			::SetDataToTable(ui->tableWidget, 1, Row, L->CurrentInspection.GetFirst()->LotListData.LotName);
		}
	}
}
void SelectLotForm::on_pushButtonSelect_clicked()
{
	int	CurrentRow=ui->tableWidget->currentRow();
	LotListWithResult *L=LotContainer[CurrentRow];
	if(L!=NULL){
		if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
			GetLayersBase()->GetIntegrationBasePointer()->SelectLot(L->CurrentInspection.GetFirst()->LotListData.GlobalID);
			//BroadcastStartLot();
		}
	}
}

void SelectLotForm::on_pushButtonSearch_clicked()
{
	SearchLotDialog	D(GetLayersBase());
	if(D.exec()==true){
		NPListPack<LotListWithResult>	TmpContainer;
		for(LotListWithResult *L=LotContainer.GetFirst();L!=NULL;){
			LotListWithResult *NextL=L->GetNext();

			if(L->CurrentInspection.GetFirst()->LotListData.LotName==D.SelectedLotID
			|| L->CurrentInspection.GetFirst()->LotListData.LotID	 ==D.SelectedLotNumber
			|| L->CurrentInspection.GetFirst()->LotListData.Remark ==D.SelectedSubCode){
				LotContainer.RemoveList(L);
				TmpContainer.AppendList(L);
			}
			L=NextL;
		}
		LotContainer.RemoveAll();
		LotListWithResult	*t;
		while((t=TmpContainer.GetFirst())!=NULL){
			TmpContainer.RemoveList(t);
			LotContainer.AppendList(t);
		}
		int	Row=0;
		for(LotListWithResult *L=LotContainer.GetFirst();L!=NULL;L=L->GetNext(),Row++){
			::SetDataToTable(ui->tableWidget, 0, Row, L->CurrentInspection.GetFirst()->LotListData.LotID);
			::SetDataToTable(ui->tableWidget, 1, Row, L->CurrentInspection.GetFirst()->LotListData.LotName);
		}
	}
}

void SelectLotForm::on_pushButtonCancel_clicked()
{
	close();
}
