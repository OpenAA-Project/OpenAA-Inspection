#include "MeasureShowGridResource.h"
#include "MeasureShowGridForm.h"
#include "ui_MeasureShowGridForm.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

MeasureShowGridForm::MeasureShowGridForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::MeasureShowGridForm)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth(0,32);
	ui->tableWidget->setColumnWidth(1,64);
	ui->tableWidget->setColumnWidth(2,64);
	ui->tableWidget->setColumnWidth(3,48);
}

MeasureShowGridForm::~MeasureShowGridForm()
{
    delete ui;
}

static	int	SortFunc(const void *a ,const void *b)
{
	MeasureDataList	*ai=((MeasureDataList **)a)[0];
	MeasureDataList	*bi=((MeasureDataList **)b)[0];

	if(ai->Page>bi->Page){
		return 1;
	}
	if(ai->Page<bi->Page){
		return -1;
	}

	bool	aok;
	bool	bok;
	int	an=ai->Name.toInt(&aok);
	int	bn=bi->Name.toInt(&bok);
	if(aok==true && bok==true){
		return an-bn;
	}
	if(ai->Name>bi->Name){
		return 1;
	}
	if(ai->Name<bi->Name){
		return -1;
	}
	return 0;
}

void MeasureShowGridForm::ShowGrid(void)
{
	MData.RemoveAll();
	LayersBase	*LBase	=GetLayersBase();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=LBase->GetGlobalPageFromLocal(page);
		GUICmdReqMeasureData	RCmd(LBase,sRoot,sName,GlobalPage);
		GUICmdAckMeasureData	ACmd(LBase,sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage ,0,ACmd)==true){
			MData+=ACmd.Data;
		}
	}
	int	N=MData.count();
	MeasureDataList	**MTable=new MeasureDataList*[N];
	for(int i=0;i<N && MData.GetFirst()!=NULL;i++){
		MeasureDataList	*a=MData.GetFirst();
		MData.RemoveList(a);
		MTable[i]=a;
	}
	QSort(MTable,N,sizeof(MeasureDataList *),SortFunc);
	
	ui->tableWidget->setRowCount(N);
	for(int L=0;L<N;L++){
		MeasureDataList	*a=MTable[L];
		MData.AppendList(a);

		::SetDataToTable(ui->tableWidget ,0,L,QString::number(a->Page));
		::SetDataToTable(ui->tableWidget ,1,L,a->Name);
		::SetDataToTable(ui->tableWidget ,2,L,a->AlgoType);
		::SetDataToTable(ui->tableWidget ,3,L,QString::number(a->Value));
	}
	delete	[]MTable;
}

void	MeasureShowGridForm::ShowInPlayer(int64 shownInspectionID)
{
	ShowGrid();
}

void	MeasureShowGridForm::ShowInEdit	(void)
{
	ShowGrid();
}

void MeasureShowGridForm::on_pushButtonSaveCSV_clicked()
{

}

//==================================================================================

GUICmdReqMeasureData::GUICmdReqMeasureData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}

void	GUICmdReqMeasureData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMeasureData	*SendBack=GetSendBack(GUICmdAckMeasureData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase *LBase=(AlgorithmBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(LBase!=NULL){
		AlgorithmInPageRoot		*LPage=LBase->GetPageData(localPage);
		CmdReqMeasureDataPacket	Cmd(GetLayersBase());
		LPage->TransmitDirectly(&Cmd);
		SendBack->Data+=Cmd.Data;
	}
	AlgorithmBase *HBase=(AlgorithmBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
	if(LBase!=NULL){
		AlgorithmInPageRoot		*HPage=HBase->GetPageData(localPage);
		CmdReqMeasureDataPacket	Cmd(GetLayersBase());
		HPage->TransmitDirectly(&Cmd);
		SendBack->Data+=Cmd.Data;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}



GUICmdAckMeasureData::GUICmdAckMeasureData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}

bool	GUICmdAckMeasureData::Load(QIODevice *f)
{
	if(Data.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckMeasureData::Save(QIODevice *f)
{
	if(Data.Save(f)==false)
		return false;
	return true;
}