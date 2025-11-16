#include "ShowMarkListForm.h"
#include "ui_ShowMarkListForm.h"
#include "PropertyAlignmentFlexAreaPacket.h"
#include "XGeneralFunc.h"
#include "XDisplayImagePacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowMarkListForm::ShowMarkListForm(LayersBase *base ,QWidget *parent) :
    QWidget(parent),ServiceForLayers(base),
    ui(new Ui::ShowMarkListForm)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth (0, 48);
	ui->tableWidget->setColumnWidth (1, 68);
	ui->tableWidget->setColumnWidth (2, 110);

	PageDim=NULL;
}

ShowMarkListForm::~ShowMarkListForm()
{
    delete ui;
	if(PageDim!=NULL){
		delete	[]PageDim;
		PageDim=NULL;
	}
}
void ShowMarkListForm::Initial(int AreaID ,int LibID)
{
	if(PageDim!=NULL){
		delete	[]PageDim;
	}
	PageDim=new AlignmentFlexAreaItemListPack[GetPageNumb()];

	int	RowCount=0;
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlignmentFlexAreaItemPack	CmdReq (GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.AreaID	=AreaID;
		CmdReq.LibID	=LibID;
		GUICmdAckAlignmentFlexAreaItemPack	CmdSend(GetLayersBase(),sRoot,sName,GlobalPage);
		if(CmdReq.Send(GlobalPage,0,CmdSend)==true){
			PageDim[page]=CmdSend.Items;
			RowCount+=PageDim[page].GetCount();
		}
	}
	int	Row=0;
	ui->tableWidget->setRowCount(RowCount);
	for(int page=0;page<GetPageNumb();page++){
		for(AlignmentFlexAreaItemList *a=PageDim[page].GetFirst();a!=NULL;a=a->GetNext()){
			::SetDataToTable(ui->tableWidget ,0,Row ,QString::number(page));
			::SetDataToTable(ui->tableWidget ,1,Row ,QString::number(a->Data.ItemID));
			::SetDataToTable(ui->tableWidget ,2,Row ,QString::number(a->Data.CenterX)+QString(/**/",")+QString::number(a->Data.CenterY));
			Row++;
		}
	}
}
void ShowMarkListForm::resizeEvent ( QResizeEvent * event )
{
	ui->tableWidget->resize(width(),height()-ui->pushButtonClose->height()-4);
	ui->pushButtonClose->move((width()-ui->pushButtonClose->width())/2,ui->tableWidget->height()+2);
}
void ShowMarkListForm::on_tableWidget_clicked(const QModelIndex &index)
{
	int	R=ui->tableWidget->currentRow();
	if(R<0)
		return;
	int	Row=0;
	for(int page=0;page<GetPageNumb();page++){
		for(AlignmentFlexAreaItemList *a=PageDim[page].GetFirst();a!=NULL;a=a->GetNext()){
			if(Row==R){
				DataInPage	*P=GetLayersBase()->GetPageData(page);
				if(P!=NULL){
					CmdDrawImageRectPacket	Cmd( GetLayersBase()
						,a->Data.x1+P->GetOutlineOffset()->x,a->Data.y1+P->GetOutlineOffset()->y
						,a->Data.x2+P->GetOutlineOffset()->x,a->Data.y2+P->GetOutlineOffset()->y);
					GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AlignmentFlexAreaImagePanel" ,/**/"");
					if(GProp!=NULL)
						GProp->TransmitDirectly(&Cmd);
					CmdDrawImageActivate	ACmd(GetLayersBase(),page,0,a->Data.ItemID);
					if(GProp!=NULL){
						GProp->TransmitDirectly(&ACmd);
					}
					return;
				}
			}
			Row++;
		}
	}
}

void ShowMarkListForm::on_pushButtonClose_clicked()
{
	close();
}
