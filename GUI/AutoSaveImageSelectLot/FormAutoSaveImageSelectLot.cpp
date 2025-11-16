#include "AutoSaveImageSelectLotResource.h"
#include "FormAutoSaveImageSelectLot.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XLotInformation.h"

FormAutoSaveImageSelectLot::FormAutoSaveImageSelectLot(LayersBase *Base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
	,RCmd(Base)
{
	ui.setupUi(this);
	ui.tableWidget->setColumnWidth(0,200);
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection",/**/"AutoSaveImageViewList",/**/"");
	if(f!=NULL){
		f->TransmitDirectly(&RCmd);
		ui.tableWidget->setRowCount(RCmd.LotList.count());
		for(int i=0;i<RCmd.LotList.count();i++){
			SetDataToTable(ui.tableWidget,0,i,RCmd.LotList[i]);
		}
	}
	InstallOperationLog(this);
}

FormAutoSaveImageSelectLot::~FormAutoSaveImageSelectLot()
{

}


void FormAutoSaveImageSelectLot::on_pushButtonSelect_clicked()
{
	int	row=ui.tableWidget->currentRow();
	if(row<0){
		return;
	}
	CmdSetLotString	SCmd(GetLayersBase());
	SCmd.LotString=RCmd.LotList[row];
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection",/**/"AutoSaveImageViewList",/**/"");
	if(f!=NULL){
		f->TransmitDirectly(&SCmd);
	}
	GetLayersBase()->GetLotBase()->SetLotName(SCmd.LotString);
	done(true);
}

void FormAutoSaveImageSelectLot::on_pushButtonCancel_clicked()
{
	done(false);
}

void FormAutoSaveImageSelectLot::on_tableWidget_doubleClicked(QModelIndex)
{
	on_pushButtonSelect_clicked();
}