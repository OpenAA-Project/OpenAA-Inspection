#include "SelectDialog.h"
#include "ui_SelectDialog.h"
#include "CameraXtumiPx8LineTrigger.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"
#include "XCameraClass.h"
#include "XEntryPoint.h"

SelectDialog::SelectDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);

	
	ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		CameraClass	*C=E->GetCamera(0);
		if(C!=NULL){
			CmdGetStockedCount	RCmd(GetLayersBase());
			C->TransmitDirectly(&RCmd);
			for(int i=0;i<RCmd.Count;i++){
				ui->listWidget->addItem(QString::number(i));
			}
		}
	}
}

SelectDialog::~SelectDialog()
{
    delete ui;
}

void SelectDialog::on_listWidget_currentRowChanged(int currentRow)
{

}

void SelectDialog::on_listWidget_doubleClicked(const QModelIndex &index)
{
	int	R=ui->listWidget->currentRow();
	if(R<0)
		return;
	ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		CameraClass	*C=E->GetCamera(0);
		if(C!=NULL){
			CmdSetImageToTarget	RCmd(GetLayersBase());
			RCmd.Number=R;
			C->TransmitDirectly(&RCmd);
		}
	}

}

void SelectDialog::on_pushButtonSelect_clicked()
{

}

void SelectDialog::on_pushButtonSave_clicked()
{
	ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		CameraClass	*C=E->GetCamera(0);
		if(C!=NULL){
			QString FileName=QFileDialog::getSaveFileName ( 0, QString("Save image"), QString(), "Image file(*.img)");
			CmdSaveImage	RCmd(GetLayersBase());
			RCmd,FileName=FileName;
			RCmd.CurrentMode=true;
			C->TransmitDirectly(&RCmd);
		}
	}
}

void SelectDialog::on_pushButtonSaveAll_clicked()
{
	int	R=ui->listWidget->currentRow();
	if(R<0)
		return;
	ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		CameraClass	*C=E->GetCamera(0);
		if(C!=NULL){
			QString FileName=QFileDialog::getSaveFileName ( 0, QString("Save image"), QString(), "Image file(*.img)");
			CmdSaveImage	RCmd(GetLayersBase());
			RCmd,FileName=FileName;
			RCmd.CurrentMode=false;
			C->TransmitDirectly(&RCmd);
		}
	}

}

void SelectDialog::on_pushButtonLoadAppend_clicked()
{
	int	R=ui->listWidget->currentRow();
	if(R<0)
		return;
	ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		CameraClass	*C=E->GetCamera(0);
		if(C!=NULL){
			CmdLoadImage	RCmd(GetLayersBase());
			C->TransmitDirectly(&RCmd);
		}
	}

}

void SelectDialog::on_pushButtonClear_clicked()
{
	ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		CameraClass	*C=E->GetCamera(0);
		if(C!=NULL){
			CmdClearImage	RCmd(GetLayersBase());
			C->TransmitDirectly(&RCmd);
		}
	}
}
