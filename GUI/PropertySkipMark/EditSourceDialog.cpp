#include "AddSourceItemDialogResource.h"
#include "EditSourceDialog.h"
#include "ui_EditSourceDialog.h"
#include"XPropertySkipMarkPacket.h"
#include "XSkipMark.h"
#include "AddSourceItemDialog.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

EditSourceDialog::EditSourceDialog(LayersBase *Base,SkipMarkInfo *Info ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base)
	,Sources(Base)
    ,ui(new Ui::EditSourceDialog)
{
    ui->setupUi(this);
	
	GlobalPage	=Info->GlobalPage;
	Layer		=Info->Layer;
	ItemID		=Info->ItemID;

	ui->labelPage	->setText(QString::number(GlobalPage));
	ui->labelLayer	->setText(QString::number(Layer));

	GUICmdReqSource		RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	GUICmdSendSource	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	RCmd.Layer	=Layer;
	RCmd.ItemID	=ItemID;
	if(RCmd.Send(GlobalPage,0,ACmd)==true){
		Sources	=ACmd.Sources;
	}
	ShowAlgorithm();
	if(Sources.GetCount()>0){
		ui->tableWidgetAlgorithm->setCurrentCell(0,0);
	}
	ShowItemList();
	ui->tableWidgetItems	->setColumnWidth(0,48);
	ui->tableWidgetItems	->setColumnWidth(1,100);
	ui->tableWidgetItems	->setColumnWidth(2,200);

	InstallOperationLog(this);
}

EditSourceDialog::~EditSourceDialog()
{
    delete ui;
}

void EditSourceDialog::ShowAlgorithm(void)
{
	ui->tableWidgetAlgorithm->setRowCount(Sources.GetCount());
	int	Row=0;
	for(SkipMarkSourceAlgoList *L=Sources.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		if(L->AlgoBase!=NULL){
			QString	DLLRoot;
			QString	DLLName;
			L->AlgoBase->GetAlgorithmRootName(DLLRoot,DLLName);
			::SetDataToTable(ui->tableWidgetAlgorithm ,0,Row ,DLLRoot);
			::SetDataToTable(ui->tableWidgetAlgorithm ,1,Row ,DLLName);
		}
		else{
			::SetDataToTable(ui->tableWidgetAlgorithm ,0,Row ,/**/"");
			::SetDataToTable(ui->tableWidgetAlgorithm ,1,Row ,/**/"");
		}
	}
}

void EditSourceDialog::on_tableWidgetAlgorithm_clicked(const QModelIndex &index)
{
	ShowItemList();
}

void	EditSourceDialog::ShowItemList(void)
{
	int	R=ui->tableWidgetAlgorithm->currentRow();
	if(R<0)
		return;
	SkipMarkSourceAlgoList *L=Sources[R];
	if(L!=NULL && L->AlgoBase!=NULL){
		GUICmdReqSourceItemInfo		RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		GUICmdSendSourceItemInfo	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		RCmd.Layer	=Layer;
		L->AlgoBase->GetAlgorithmRootName(RCmd.AlgoRoot,RCmd.AlgoName);
		RCmd.IDList	=L->IDList;
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			ItemList	=ACmd.ItemInfos;
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
			}
		}
	}
}

void EditSourceDialog::on_pushButtonDeleteLines_clicked()
{
	IntList Rows;
	::GetSelectedRows(ui->tableWidgetItems ,Rows);

	int	R=ui->tableWidgetAlgorithm->currentRow();
	if(R<0)
		return;
	SkipMarkSourceAlgoList *L=Sources[R];
	if(L!=NULL && L->AlgoBase!=NULL){
		for(IntClass *i=Rows.GetFirst();i!=NULL;i=i->GetNext()){
			if(ItemList[i->GetValue()]!=NULL){
				L->IDList.Remove(ItemList[i->GetValue()]->ItemID);
			}
		}
	}
	ShowItemList();
}

void EditSourceDialog::on_pushButtonAddItem_clicked()
{
	AddSourceItemDialog	D(GetLayersBase(),GlobalPage,Layer);
	if(D.exec()==(int)true){
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(D.AlgoRoot,D.AlgoName);
		if(ABase!=NULL){
			SkipMarkSourceAlgoList *L;
			for(L=Sources.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->AlgoBase==ABase){
					if(L->IDList.IsInclude(D.ItemID)==false){
						L->IDList.Add(D.ItemID);
					}
					break;
				}
			}
			if(L==NULL){
				L=new SkipMarkSourceAlgoList(GetLayersBase());
				L->AlgoBase	=ABase;
				L->IDList.Add(D.ItemID);
				Sources.AppendList(L);
				ShowAlgorithm();
			}
			ShowItemList();
		}
	}
}

void EditSourceDialog::on_pushButtonOK_clicked()
{
	GUICmdModifySourceItems	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	RCmd.Layer	=Layer;
	RCmd.ItemID	=ItemID;
	RCmd.Sources	=Sources;
	RCmd.Send(NULL,GlobalPage,0);
	done(true);
}

void EditSourceDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
