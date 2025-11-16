#include "ItemListForm.h"
#include "ui_ItemListForm.h"
#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "XDisplayImagePacket.h"
#include "EditItemsDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

static	int ItemIDDecendSortFunc(const BlockListInfo **a,const BlockListInfo **b)
{
	if((*a)->BlockListData.ItemID<(*b)->BlockListData.ItemID)
		return 1;
	if((*a)->BlockListData.ItemID>(*b)->BlockListData.ItemID)
		return -1;
	return 0;
}
static	int ItemIDAcendSortFunc(const BlockListInfo **a,const BlockListInfo **b)
{
	if((*a)->BlockListData.ItemID<(*b)->BlockListData.ItemID)
		return -1;
	if((*a)->BlockListData.ItemID>(*b)->BlockListData.ItemID)
		return 1;
	return 0;
}
static	int AreaSearchDecendSortFunc(const BlockListInfo **a,const BlockListInfo **b)
{
	if((*a)->BlockListData.AreaSearchX<(*b)->BlockListData.AreaSearchX)
		return 1;
	if((*a)->BlockListData.AreaSearchX>(*b)->BlockListData.AreaSearchX)
		return -1;
	if((*a)->BlockListData.AreaSearchY<(*b)->BlockListData.AreaSearchY)
		return 1;
	if((*a)->BlockListData.AreaSearchY>(*b)->BlockListData.AreaSearchY)
		return -1;
	return 0;
}
static	int AreaSearchAcendSortFunc(const BlockListInfo **a,const BlockListInfo **b)
{
	if((*a)->BlockListData.AreaSearchX<(*b)->BlockListData.AreaSearchX)
		return -1;
	if((*a)->BlockListData.AreaSearchX>(*b)->BlockListData.AreaSearchX)
		return 1;
	if((*a)->BlockListData.AreaSearchY<(*b)->BlockListData.AreaSearchY)
		return -1;
	if((*a)->BlockListData.AreaSearchY>(*b)->BlockListData.AreaSearchY)
		return 1;
	return 0;
}
static	int SelfSearchDecendSortFunc(const BlockListInfo **a,const BlockListInfo **b)
{
	if((*a)->BlockListData.SelfSearch<(*b)->BlockListData.SelfSearch)
		return 1;
	if((*a)->BlockListData.SelfSearch>(*b)->BlockListData.SelfSearch)
		return -1;
	return 0;
}
static	int SelfSearchAcendSortFunc(const BlockListInfo **a,const BlockListInfo **b)
{
	if((*a)->BlockListData.SelfSearch<(*b)->BlockListData.SelfSearch)
		return -1;
	if((*a)->BlockListData.SelfSearch>(*b)->BlockListData.SelfSearch)
		return 1;
	return 0;
}
static	int OKDotBDecendSortFunc(const BlockListInfo **a,const BlockListInfo **b)
{
	if((*a)->BlockListData.OKDotB<(*b)->BlockListData.OKDotB)
		return 1;
	if((*a)->BlockListData.OKDotB>(*b)->BlockListData.OKDotB)
		return -1;
	return 0;
}
static	int OKDotBAcendSortFunc(const BlockListInfo **a,const BlockListInfo **b)
{
	if((*a)->BlockListData.OKDotB<(*b)->BlockListData.OKDotB)
		return -1;
	if((*a)->BlockListData.OKDotB>(*b)->BlockListData.OKDotB)
		return 1;
	return 0;
}
static	int OKDotNDecendSortFunc(const BlockListInfo **a,const BlockListInfo **b)
{
	if((*a)->BlockListData.OKDotN<(*b)->BlockListData.OKDotN)
		return 1;
	if((*a)->BlockListData.OKDotN>(*b)->BlockListData.OKDotN)
		return -1;
	return 0;
}
static	int OKDotNAcendSortFunc(const BlockListInfo **a,const BlockListInfo **b)
{
	if((*a)->BlockListData.OKDotN<(*b)->BlockListData.OKDotN)
		return -1;
	if((*a)->BlockListData.OKDotN>(*b)->BlockListData.OKDotN)
		return 1;
	return 0;
}

//================================================================================
ItemListForm::ItemListForm(LayersBase *Base ,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),
    ui(new Ui::ItemListForm)
{
    ui->setupUi(this);
	setWindowFlags(Qt::WindowStaysOnTopHint | windowFlags());

	SortType=0;
	Decendant=true;

	QHeaderView *H=ui->tableWidget->horizontalHeader();
	bool	Ret=connect(H,SIGNAL(sectionClicked(int)),this,SLOT(SlotTableSectionClicked(int)));

	InstallOperationLog(this);
}

ItemListForm::~ItemListForm()
{
    delete ui;
}
void	ItemListForm::closeEvent(QCloseEvent *event)
{
	event->ignore();
	hide();
}
void    ItemListForm::Initial(void)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqBlockListInfo	ReqCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckBlockListInfo	AckCmd(GetLayersBase(),sRoot,sName,GlobalPage);

		if(ReqCmd.Send(ReqCmd.GetGlobalPage(),0,AckCmd)==true){
			BlockListInfoContainerData+=AckCmd.BlockListInfoContainerData;
		}
	}
	BlockListInfoContainerData.Sort(ItemIDDecendSortFunc);
	ShowGrid();
}

void    ItemListForm::ShowGrid(void)
{
	ui->tableWidget->setRowCount(BlockListInfoContainerData.GetCount());
	int	Row=0;
	for(BlockListInfo *b=BlockListInfoContainerData.GetFirst();b!=NULL;b=b->GetNext(),Row++){
		::SetDataToTable(ui->tableWidget, 0, Row, QString::number(b->BlockListData.Page));
		::SetDataToTable(ui->tableWidget, 1, Row, QString::number(b->BlockListData.ItemID));
		::SetDataToTable(ui->tableWidget, 2, Row, QString::number(b->BlockListData.LibID));
		::SetDataToTable(ui->tableWidget, 3, Row, QString::number(b->BlockListData.AreaSearchX));
		::SetDataToTable(ui->tableWidget, 4, Row, QString::number(b->BlockListData.AreaSearchY));
		::SetDataToTable(ui->tableWidget, 5, Row, QString::number(b->BlockListData.SelfSearch));
		::SetDataToTable(ui->tableWidget, 6, Row, QString::number(b->BlockListData.OKDotB));
		::SetDataToTable(ui->tableWidget, 7, Row, QString::number(b->BlockListData.OKDotN));
	}
}

void ItemListForm::on_tableWidget_clicked(const QModelIndex &index)
{
	on_tableWidget_itemSelectionChanged();
}

void    ItemListForm::SlotTableSectionClicked(int logicalIndex)
{
	if(logicalIndex==1){
		if(Decendant==true)
			BlockListInfoContainerData.Sort(ItemIDDecendSortFunc);
		else
			BlockListInfoContainerData.Sort(ItemIDAcendSortFunc);
		Decendant=!Decendant;
	}
	else if(logicalIndex==3){
		if(Decendant==true)
			BlockListInfoContainerData.Sort(AreaSearchDecendSortFunc);
		else
			BlockListInfoContainerData.Sort(AreaSearchAcendSortFunc);
		Decendant=!Decendant;
	}
	else if(logicalIndex==4){
		if(Decendant==true)
			BlockListInfoContainerData.Sort(SelfSearchDecendSortFunc);
		else
			BlockListInfoContainerData.Sort(SelfSearchAcendSortFunc);
		Decendant=!Decendant;
	}
	else if(logicalIndex==5){
		if(Decendant==true)
			BlockListInfoContainerData.Sort(OKDotBDecendSortFunc);
		else
			BlockListInfoContainerData.Sort(OKDotBAcendSortFunc);
		Decendant=!Decendant;
	}
	else if(logicalIndex==6){
		if(Decendant==true)
			BlockListInfoContainerData.Sort(OKDotNDecendSortFunc);
		else
			BlockListInfoContainerData.Sort(OKDotNAcendSortFunc);
		Decendant=!Decendant;
	}
	ShowGrid();
}

void ItemListForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0){
		return;
	}
	BlockListInfo *b=BlockListInfoContainerData[Row];

	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(b->BlockListData.Page);
	GUICmdReqItemsByLibID	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	RCmd.ItemID	=b->BlockListData.ItemID;
	RCmd.LibID	=b->BlockListData.LibID;
	GUICmdAckItemsByLibID	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
	if(RCmd.Send(GlobalPage,0,ACmd)==true){
		EditItemsDialog	D(GetLayersBase());
		D.SetItemInfo(ACmd.MasterNoOriginCode
					 ,ACmd.SubLibIDs
					 ,ACmd.ExpandToSubBlock);
		if(D.exec()==true){
			GUICmdSetItemsByLibID	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			SCmd.LibID=b->BlockListData.LibID;
			SCmd.ItemID	=b->BlockListData.ItemID;
			SCmd.AvailableMasterNo	=D.AvailableMasterNo;
			SCmd.MasterNoOriginCode	=D.MasterNoOriginCode;
			SCmd.AvailableSubBlock	=D.AvailableSubBlock;
			SCmd.SubBlockList		=D.SubBlockList;
			SCmd.ExpandToSubBlock	=D.ExpandToSubBlock;
			SCmd.Send(NULL,GlobalPage,0);
		}
	}

}
void    ItemListForm::resizeEvent(QResizeEvent *)
{
	::SetColumnWidthInTable(ui->tableWidget ,0, 11);
	::SetColumnWidthInTable(ui->tableWidget ,1, 11);
	::SetColumnWidthInTable(ui->tableWidget ,2, 11);
	::SetColumnWidthInTable(ui->tableWidget ,3, 11);
	::SetColumnWidthInTable(ui->tableWidget ,4, 11);
	::SetColumnWidthInTable(ui->tableWidget ,5, 11);
	::SetColumnWidthInTable(ui->tableWidget ,6, 11);
	::SetColumnWidthInTable(ui->tableWidget ,7, 11);

	ui->tableWidget->resize(width(),height());
}

void ItemListForm::on_tableWidget_itemSelectionChanged()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;

	BlockListInfo *b=BlockListInfoContainerData[Row];
	if(b==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(b->BlockListData.Page);
	if(P!=NULL){
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DotColorMatchingImagePanel" ,/**/"");
		if(GProp!=NULL){
			CmdDrawImageRectPacket	Cmd( GetLayersBase()
										,b->BlockListData.x1+P->GetOutlineOffset()->x,b->BlockListData.y1+P->GetOutlineOffset()->y
										,b->BlockListData.x2+P->GetOutlineOffset()->x,b->BlockListData.y2+P->GetOutlineOffset()->y);
			GProp->TransmitDirectly(&Cmd);
		}
		CmdDrawImageActivate	ACmd(GetLayersBase(),b->BlockListData.Page,0,b->BlockListData.ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

