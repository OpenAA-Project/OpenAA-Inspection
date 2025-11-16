#include "PropertyZRegulationForm.h"
#include "XGeneralFunc.h"
#include "XPropertyZRegulationPacket.h"
#include "EditAxisIDForm.h"

extern	char	*sRoot;
extern	char	*sName;

PropertyZRegulationForm::PropertyZRegulationForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);

	ui.tableWidget->setColumnWidth (0, 36);
	ui.tableWidget->setColumnWidth (1, 36);	
	ui.tableWidget->setColumnWidth (2, 80);	
	ui.tableWidget->setColumnWidth (3, 30);	
	ui.tableWidget->setColumnWidth (4, 50);	
	ui.tableWidget->setColumnWidth (5, 50);	
	ui.tableWidget->setColumnWidth (6, 50);	
	ui.tableWidget->setColumnWidth (7, 30);
}

PropertyZRegulationForm::~PropertyZRegulationForm()
{

}

void	PropertyZRegulationForm::BuildForShow(void)
{
	ShowGrid();
}
void	PropertyZRegulationForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AddZRegulationAreaPacket	*AddZRegulationAreaVar=dynamic_cast<AddZRegulationAreaPacket *>(packet);
	if(AddZRegulationAreaVar!=NULL){
		EditAxisIDForm	D(this);
		if(D.exec()==(int)true){
			IntList		PageList;
			GetLayersBase()->GetLocalPageFromArea(AddZRegulationAreaVar->Area,PageList);
			for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
				int	Page=p->GetValue();
				GUICmdAddItem	RCmd(GetLayersBase(),sRoot,sName,Page);
				RCmd.Area			=AddZRegulationAreaVar->Area;
				DataInPage	*P		=GetLayersBase()->GetPageData(Page);
				P->ClipMoveAreaFromGlobal(RCmd.Area);
				RCmd.Layers			=AddZRegulationAreaVar->Layers;
				RCmd.AxisID			=D.AxisID;
				RCmd.CenterInMaster	=D.CenterInMaster;
				RCmd.OKZone			=D.OKZone;
				RCmd.Send(NULL,Page,0);
			}
		}
		ShowGrid();
		return;
	}
}

void PropertyZRegulationForm::on_pushButtonCalc_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdExecuteCalc	RCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.Send(NULL,page,0);
	}

	GUIFormBase *ZAxisViewerPointer[100];
	int N=GetLayersBase()->EnumGUIInst(/**/"Inspection" ,/**/"ZAxisViewer",ZAxisViewerPointer ,100);
	for(int i=0;i<N;i++){
		CmdStartCalc	RCmd(GetLayersBase());
		ZAxisViewerPointer[i]->TransmitDirectly(&RCmd);
	}
	ShowGrid();
}

void PropertyZRegulationForm::ShowGrid(void)
{
	int	N=0;
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqItemInfo	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckItemInfo	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			ItemInfoList *a;
			while((a=ACmd.Infos.GetFirst())!=NULL){
				ACmd.Infos.RemoveList(a);
				LList[N]=a;
				a->Page=page;
				N++;
			}
		}
	}
	ui.tableWidget->setRowCount(N);
	for(int i=0;i<N;i++){
		SetDataToTable(ui.tableWidget ,0,i,QString::number(GetLayersBase()->GetGlobalPageFromLocal(LList[i]->Page)));
		SetDataToTable(ui.tableWidget ,1,i,QString::number(LList[i]->Layer));
		QString	M=QString("(")+QString::number(LList[i]->x1)+QString(",")+QString::number(LList[i]->y1)+QString(")-(")
							  +QString::number(LList[i]->x2)+QString(",")+QString::number(LList[i]->y2)+QString(")");
		SetDataToTable(ui.tableWidget ,2,i,M);
		SetDataToTable(ui.tableWidget ,3,i,QString::number(LList[i]->AxisID));
		SetDataToTable(ui.tableWidget ,4,i,QString::number(LList[i]->CenterInMaster));
		SetDataToTable(ui.tableWidget ,5,i,QString("+/-")+QString::number(LList[i]->OKZone));
		SetDataToTable(ui.tableWidget ,6,i,QString::number(LList[i]->ResultCenter));
		SetDataToTable(ui.tableWidget ,7,i,(LList[i]->ResultOK==true)?"OK":"NG");
	}
}

void PropertyZRegulationForm::on_tableWidget_doubleClicked(QModelIndex)
{
	int	R=ui.tableWidget->currentRow();

	if(R>=0){
		EditAxisIDForm	D(this);
		D.SetData(LList[R]->AxisID,LList[R]->CenterInMaster ,LList[R]->OKZone);
		if(D.exec()==(int)true){
			LList[R]->AxisID=D.AxisID;
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(LList[R]->Page);
			GUICmdSetItemInfo	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.AxisID			=LList[R]->AxisID;
			RCmd.Layer			=LList[R]->Layer;
			RCmd.Page			=LList[R]->Page;
			RCmd.ItemID			=LList[R]->ItemID;
			RCmd.CenterInMaster	=D.CenterInMaster;
			RCmd.OKZone			=D.OKZone;
			RCmd.Send(NULL,GlobalPage,0);
			ShowGrid();
		}
	}
}

//====================================================================================
GUICmdAddItem::GUICmdAddItem(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AxisID		=0;
	CenterInMaster=0;
	OKZone		=0;
}

bool	GUICmdAddItem::Load(QIODevice *f)
{
	if(Area.Load(f)==false){
		return false;
	}
	if(Layers.Load(f)==false){
		return false;
	}
	if(::Load(f,AxisID)==false){
		return false;
	}
	if(::Load(f,CenterInMaster)==false){
		return false;
	}
	if(::Load(f,OKZone)==false){
		return false;
	}

	return true;
}
bool	GUICmdAddItem::Save(QIODevice *f)
{
	if(Area.Save(f)==false){
		return false;
	}
	if(Layers.Save(f)==false){
		return false;
	}
	if(::Save(f,AxisID)==false){
		return false;
	}
	if(::Save(f,CenterInMaster)==false){
		return false;
	}
	if(::Save(f,OKZone)==false){
		return false;
	}
	return true;
}

void	GUICmdAddItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	QString	AlgoRoot=/**/"Regulation";
	QString	AlgoName=/**/"ZAxis";
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	CmdAddArea	RCmd(GetLayersBase());
	RCmd.Area	=Area;
	RCmd.Layers	=Layers;
	RCmd.AxisID			=AxisID;
	RCmd.CenterInMaster	=CenterInMaster;
	RCmd.OKZone			=OKZone;
	Base->GetPageData(localPage)->TransmitDirectly(&RCmd);
}

//====================================================================================

GUICmdExecuteCalc::GUICmdExecuteCalc(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdExecuteCalc::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	QString	AlgoRoot=/**/"Regulation";
	QString	AlgoName=/**/"ZAxis";
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	CmdStartCalc	RCmd(GetLayersBase());
	Base->GetPageData(localPage)->TransmitDirectly(&RCmd);
}

//====================================================================================

GUICmdReqItemInfo::GUICmdReqItemInfo(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqItemInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckItemInfo	*SendBack=GetSendBack(GUICmdAckItemInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	QString	AlgoRoot=/**/"Regulation";
	QString	AlgoName=/**/"ZAxis";
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);

	CmdReqItemInfoList	RCmd(GetLayersBase());
	Base->GetPageData(localPage)->TransmitDirectly(&RCmd);
	SendBack->Infos	=RCmd.Infos;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckItemInfo::GUICmdAckItemInfo(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckItemInfo::Load(QIODevice *f)
{
	if(Infos.Load(f)==false){
		return false;
	}
	return true;
}

bool	GUICmdAckItemInfo::Save(QIODevice *f)
{
	if(Infos.Save(f)==false){
		return false;
	}
	return true;
}

GUICmdSetItemInfo::GUICmdSetItemInfo(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AxisID		=0;
	CenterInMaster=0;
	OKZone		=0;
}
bool	GUICmdSetItemInfo::Load(QIODevice *f)
{
	if(::Load(f,AxisID)==false){
		return false;
	}
	if(::Load(f,ItemID)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,CenterInMaster)==false){
		return false;
	}
	if(::Load(f,OKZone)==false){
		return false;
	}
	return true;
}
bool	GUICmdSetItemInfo::Save(QIODevice *f)
{
	if(::Save(f,AxisID)==false){
		return false;
	}
	if(::Save(f,ItemID)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,CenterInMaster)==false){
		return false;
	}
	if(::Save(f,OKZone)==false){
		return false;
	}
	return true;
}

void	GUICmdSetItemInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	QString	AlgoRoot=/**/"Regulation";
	QString	AlgoName=/**/"ZAxis";
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);

	CmdSetItemInfo	RCmd(GetLayersBase());
	RCmd.ItemID	=ItemID;
	RCmd.Layer	=Layer;
	RCmd.AxisID	=AxisID;
	RCmd.CenterInMaster	=CenterInMaster;
	RCmd.OKZone			=OKZone;
	Base->GetPageData(localPage)->TransmitDirectly(&RCmd);
}


