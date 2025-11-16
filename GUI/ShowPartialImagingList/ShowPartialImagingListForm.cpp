#include "ShowPartialImagingListResource.h"
#include "ShowPartialImagingListForm.h"
#include "ui_ShowPartialImagingListForm.h"
#include "XPropertyPartialImagingPacket.h"
#include "XPartialImaging.h"
#include "XGeneralFunc.h"

ShowPartialImagingListForm::ShowPartialImagingListForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowPartialImagingListForm)
{
    ui->setupUi(this);
	
	PageData			=NULL;
	AllocatedPageNumb	=0;
	WList				=NULL;
	WListNumb			=0;

	ui->tableWidgetList	->setColumnWidth(0,48);
	ui->tableWidgetList	->setColumnWidth(1,48);
	ui->tableWidgetList	->setColumnWidth(2,80);
	ui->tableWidgetList	->setColumnWidth(3,48);
}

ShowPartialImagingListForm::~ShowPartialImagingListForm()
{
    delete ui;

	Release();

	if(WList!=NULL){
		delete	[]WList;
		WList=NULL;
	}
}

PartialImagingBase	*ShowPartialImagingListForm::GetPartialImagingBase(void)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PartialImaging");
	return (PartialImagingBase *)PBase;
}

void	ShowPartialImagingListForm::Release(void)
{
	PartialImagingBase	*ABase=GetPartialImagingBase();
	if(ABase==NULL)
		return;

	CmdReleaseBufferedData	ACmd(GetLayersBase());
	ACmd.PointDim=PageData;
	ABase->TransmitDirectly(&ACmd);
	PageData=NULL;
	AllocatedPageNumb=0;
}

void	ShowPartialImagingListForm::BuildForShow(void)
{
	Release();
}

void	ShowPartialImagingListForm::StartLot	(void)
{
	PartialImagingBase	*ABase=GetPartialImagingBase();
	if(ABase==NULL)
		return;

	CmdReqBufferedData	ACmd(GetLayersBase());
	ABase->TransmitDirectly(&ACmd);

	PageData			=ACmd.PointDim;
	AllocatedPageNumb	=ACmd.PageNumb;

	ShowGrid();
}

void	ShowPartialImagingListForm::ShowGrid(void)
{
	if(PageData!=NULL){
		int	N=0;
		for(int page=0;page<AllocatedPageNumb;page++){
			N+=PageData[page].WriteBufferNumb;
		}
		if(WList!=NULL){
			delete	[]WList;
		}
		WList=new WriteBufferPointer[N];
		WListNumb=N;

		ui->tableWidgetList->setRowCount(N);
		int	Row=0;
		for(int page=0;page<AllocatedPageNumb;page++){
			for(int i=0;i<PageData[page].WriteBufferNumb;i++){
				WriteBufferInItem	*W=&PageData[page].BufferDim[i];
				WList[Row].Point=W;
				WList[Row].GlobalPage=page;
				Row++;
			}
		}
		Row=0;
		for(int i=0;i<N;i++){
			::SetDataToTable(ui->tableWidgetList,0,Row ,QString::number(WList[i].GlobalPage));
			::SetDataToTable(ui->tableWidgetList,1,Row ,QString::number(WList[i].Point->ItemID));
			::SetDataToTable(ui->tableWidgetList,2,Row ,WList[i].Point->ItemName);
			::SetDataToTable(ui->tableWidgetList,3,Row ,QString::number(WList[i].Point->GetPriority()));
			Row++;
		}
	}
}

void	ShowPartialImagingListForm::TransmitDirectly(GUIDirectMessage *packet)
{
}

void ShowPartialImagingListForm::on_tableWidgetList_clicked(const QModelIndex &index)
{
	int	R=ui->tableWidgetList->currentRow();
	if(R<0 || WList==NULL || WListNumb<=R)
		return;
	CmdSelectBufferInItem	PCmd(GetLayersBase());
	PCmd.Point	=WList[R].Point;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"List" ,/**/"ShowPartialImagingPanel" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&PCmd);
	}
}

void ShowPartialImagingListForm::on_tableWidgetList_doubleClicked(const QModelIndex &index)
{
	int	R=ui->tableWidgetList->currentRow();
	if(R<0 || WList==NULL || WListNumb<=R)
		return;
}

void ShowPartialImagingListForm::on_pushButtonUpdate_clicked()
{
	StartLot();
}
