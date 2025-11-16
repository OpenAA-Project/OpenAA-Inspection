#include "ShowMeasureHolePosResultListForm.h"
#include "ui_ShowMeasureHolePosResultListForm.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowMeasureHolePosResultListForm::ShowMeasureHolePosResultListForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowMeasureHolePosResultListForm)
{
    ui->setupUi(this);
}

ShowMeasureHolePosResultListForm::~ShowMeasureHolePosResultListForm()
{
    delete ui;
}

void    ShowMeasureHolePosResultListForm::resizeEvent(QResizeEvent *event)
{
	ui->tableWidget->setGeometry(0,0,width(),height());
	::SetColumnWidthInTable(ui->tableWidget ,0, 15);
	::SetColumnWidthInTable(ui->tableWidget ,1, 15);
	::SetColumnWidthInTable(ui->tableWidget ,2, 25);
	::SetColumnWidthInTable(ui->tableWidget ,3, 25);
	::SetColumnWidthInTable(ui->tableWidget ,4, 20);
}

void ShowMeasureHolePosResultListForm::on_tableWidget_itemSelectionChanged()
{

}


void ShowMeasureHolePosResultListForm::on_tableWidget_clicked(const QModelIndex &index)
{

}


void ShowMeasureHolePosResultListForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{

}

void ShowMeasureHolePosResultListForm::ShowGrid(void)
{
	MData.RemoveAll();
	LayersBase	*LBase	=GetLayersBase();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=LBase->GetGlobalPageFromLocal(page);
		GUICmdReqMeasureHolePosResultData	RCmd(LBase,sRoot,sName,GlobalPage);
		GUICmdAckMeasureHolePosResultData	ACmd(LBase,sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage ,0,ACmd)==true){
			MData+=ACmd.Data;
		}
	}
	int	N=MData.count();
	MeasureHolePosDataList	**MTable=new MeasureHolePosDataList*[N];
	for(int i=0;i<N && MData.GetFirst()!=NULL;i++){
		MeasureHolePosDataList	*a=MData.GetFirst();
		MData.RemoveList(a);
		MTable[i]=a;
	}
	
	ui->tableWidget->setRowCount(N);
	for(int L=0;L<N;L++){
		MeasureHolePosDataList	*a=MTable[L];
		MData.AppendList(a);

		::SetDataToTable(ui->tableWidget ,0,L,QString::number(a->HData.Page));
		::SetDataToTable(ui->tableWidget ,1,L,QString::number(a->HData.ItemID));
		::SetDataToTable(ui->tableWidget ,2,L,QString::number(a->HData.MasterCx,'f',2)
											+ QString(",")
											+ QString::number(a->HData.MasterCy,'f',2));
		::SetDataToTable(ui->tableWidget ,3,L,QString::number(a->HData.TargetCx,'f',2)
											+ QString(",")
											+ QString::number(a->HData.TargetCy,'f',2));
		::SetDataToTable(ui->tableWidget ,4,L,QString::number(a->HData.TargetRx-a->HData.MasterRx,'f',2)
											+ QString(",")
											+ QString::number(a->HData.TargetCy-a->HData.TargetRy,'f',2));
	}
	delete	[]MTable;
}

void	ShowMeasureHolePosResultListForm::ShowInPlayer(int64 shownInspectionID)
{
	ShowGrid();
}

void	ShowMeasureHolePosResultListForm::ShowInEdit	(void)
{
	ShowGrid();
}


//==================================================================================

GUICmdReqMeasureHolePosResultData::GUICmdReqMeasureHolePosResultData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}

void	GUICmdReqMeasureHolePosResultData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMeasureHolePosResultData	*SendBack=GetSendBack(GUICmdAckMeasureHolePosResultData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase *LBase=(AlgorithmBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(LBase!=NULL){
		AlgorithmInPageRoot		*LPage=LBase->GetPageData(localPage);
		CmdReqMeasureHolePosDataPacket	Cmd(GetLayersBase());
		LPage->TransmitDirectly(&Cmd);
		SendBack->Data+=Cmd.Data;
	}
	AlgorithmBase *HBase=(AlgorithmBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
	if(HBase!=NULL){
		AlgorithmInPageRoot		*HPage=HBase->GetPageData(localPage);
		CmdReqMeasureHolePosDataPacket	Cmd(GetLayersBase());
		HPage->TransmitDirectly(&Cmd);
		SendBack->Data+=Cmd.Data;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}



GUICmdAckMeasureHolePosResultData::GUICmdAckMeasureHolePosResultData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}

bool	GUICmdAckMeasureHolePosResultData::Load(QIODevice *f)
{
	if(Data.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckMeasureHolePosResultData::Save(QIODevice *f)
{
	if(Data.Save(f)==false)
		return false;
	return true;
}