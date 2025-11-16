#include "PropertyColorCorrectorForm.h"
#include "ui_PropertyColorCorrectorForm.h"
#include "XGeneralFunc.h"
#include "EditItemDialog.h"
#include "XColorCorrector.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyColorCorrectorForm::PropertyColorCorrectorForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyColorCorrectorForm)
{
    ui->setupUi(this);

	::SetColumnWidthInTable(ui->tableWidget ,0, 15);
	::SetColumnWidthInTable(ui->tableWidget ,1, 15);
	::SetColumnWidthInTable(ui->tableWidget ,2, 20);
	::SetColumnWidthInTable(ui->tableWidget ,3, 40);

}

PropertyColorCorrectorForm::~PropertyColorCorrectorForm()
{
    delete ui;
}

ColorCorrectorBase	*PropertyColorCorrectorForm::GetColorCorrectorBase(void)
{
    return (ColorCorrectorBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorCorrector");
}

void	PropertyColorCorrectorForm::TransmitDirectly(GUIDirectMessage *packet)
{
	ColorCorrectorBase	*ABase=GetColorCorrectorBase();

	CmdColorCorrectorDrawModePacket	*BDrawModePacket=dynamic_cast<CmdColorCorrectorDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		ColorCorrectorType	VType;
		if(ui->toolButtonColorShiftV->isChecked()==true){
			VType=ItemClassColorShiftV;
		}
		else
		if(ui->toolButtonColorChangeV->isChecked()==true){
			VType=ItemClassColorChangeV;
		}

		BDrawModePacket->VType=VType;
		return;
	}
	CmdColorCorrectorDrawEnd	*ColorCorrectorDEnd=dynamic_cast<CmdColorCorrectorDrawEnd *>(packet);
	if(ColorCorrectorDEnd!=NULL){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual ColorCorrector");
		
		QByteArray	WArray;
		ColorCorrectorType	VType;
		if(ui->toolButtonColorShiftV->isChecked()==true){
			VType=ItemClassColorShiftV;
			EditItemDialog	D(GetLayersBase());
			if(D.exec()!=1)
				return;
			CmdCreateThreshold	CCmd(GetLayersBase());
			CCmd.VType=VType;
			ABase->TransmitDirectly(&CCmd);
			ColorShiftVThreshold	*TmpThreshold=(ColorShiftVThreshold *)CCmd.Thr;
			D.GetCurrentItem(TmpThreshold);
			CmdSaveThreshold	SCmd(GetLayersBase());
			SCmd.Thr=TmpThreshold;
			ABase->TransmitDirectly(&SCmd);
			WArray=SCmd.Data;
			delete	CCmd.Thr;
		}
		else
		if(ui->toolButtonColorChangeV->isChecked()==true){
			VType=ItemClassColorChangeV;
		}

		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(ColorCorrectorDEnd->Area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			int	page=P->GetValue();
			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
			FlexArea	A=ColorCorrectorDEnd->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdSendAddManualColorCorrector	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
				Cmd.Area=A;
				Cmd.BItem	=WArray;
				Cmd.VType	=VType;
				Cmd.SendOnly(GlobalPage,0);
			}
		}
		ShowList();
	}
	//CmdColorCorrectorShowAttrPacket	*ShowAttr=dynamic_cast<CmdColorCorrectorShowAttrPacket *>(packet);
	//if(ShowAttr!=NULL){
	//
	//}
}
void PropertyColorCorrectorForm::on_tableWidget_cellClicked(int row, int column)
{

}


void PropertyColorCorrectorForm::on_pushButtonAutoGenerate_clicked()
{

}


void PropertyColorCorrectorForm::on_pushButtonExecuteTarget_clicked()
{

}

void PropertyColorCorrectorForm::ShowList(void)
{
	ColorCorrectorType	VType;
	if(ui->toolButtonColorShiftV->isChecked()==true){
		VType=ItemClassColorShiftV;
	}
	else
	if(ui->toolButtonColorChangeV->isChecked()==true){
		VType=ItemClassColorChangeV;
	}

	GridList.RemoveAll();
	int	Phase=GetLayersBase()->GetCurrentPhase();
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqGridList	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckGridList	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.Phase=Phase;
		RCmd.VType=VType;
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			GridList.AddMove(ACmd.ListData);
		}
	}
	ui->tableWidget->setRowCount(GridList.GetCount());
	int	Row=0;
	for(ColorCorrectorGridList *L=GridList.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		::SetDataToTable(ui->tableWidget, 0, Row, QString::number(L->Phase));
		::SetDataToTable(ui->tableWidget, 1, Row, QString::number(L->Page));
		::SetDataToTable(ui->tableWidget, 2, Row, QString::number(L->ItemID));
		::SetDataToTable(ui->tableWidget, 3, Row, QString("(")
												 +QString::number(L->x1)
												 +QString(",")
												 +QString::number(L->y1)
												 +QString("(,)-(")
												 +QString::number(L->x2)
												 +QString(",")
												 +QString::number(L->y2)
												 +QString(")"));
	}
}