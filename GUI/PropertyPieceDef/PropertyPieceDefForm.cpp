#include "PropertyPieceDefResource.h"
#include "PropertyPieceDefForm.h"
#include "ui_PropertyPieceDefForm.h"
#include"XPropertyPieceDefPacket.h"
#include "XDisplayImagePacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyPieceDefForm::PropertyPieceDefForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base ,parent),
    ui(new Ui::PropertyPieceDefForm)
{
    ui->setupUi(this);
}

PropertyPieceDefForm::~PropertyPieceDefForm()
{
    delete ui;
}
void	PropertyPieceDefForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreatePieceDefManualPacket	*CmdCreatePieceDefManualPacketVer=dynamic_cast<CmdCreatePieceDefManualPacket *>(packet);
	if(CmdCreatePieceDefManualPacketVer!=NULL){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(CmdCreatePieceDefManualPacketVer->Area, PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
			FlexArea	Area=CmdCreatePieceDefManualPacketVer->Area;
			pdata->ClipMoveAreaFromGlobal(Area);
			if(Area.GetPatternByte()>0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(pdata->GetPage());
				GUICmdAddPieceAreaManual	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
				Cmd.Area=Area;
				Cmd.SendOnly(GlobalPage,0);
			}
		}
		return;
	}
}
void PropertyPieceDefForm::on_pushButtonStartSearch_clicked()
{
	FlexAreaImageBuffer	Seed;
	FlexArea			OriginalArea;
	int		SweepNumber=-1;
	int		GPage=-1;
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqSeed	ReqSeed(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdAckSeed	AckSeed(GetLayersBase(),sRoot,sName,globalPage);
		if(ReqSeed.Send(globalPage,0,AckSeed)==true && AckSeed.IsReceived()==true){
			if(AckSeed.Seed.IsNull()==false){
				Seed			=AckSeed.Seed;
				OriginalArea	=AckSeed.OriginalArea;
				SweepNumber		=AckSeed.SweepNumber;
				GPage=globalPage;
				break;
			}
		}
	}
	if(Seed.IsNull()==false){
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			GUICmdSweepSeed	Cmd(GetLayersBase(),sRoot,sName,globalPage);
			Cmd.Seed=Seed;
			Cmd.SweepNumber=SweepNumber;
			if(GPage==globalPage){
				Cmd.OriginalArea=OriginalArea;
			}
			Cmd.Send(NULL,globalPage,0);
		}
		ShowItemGrid();
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"PieceDefImagePanel",/**/"");
		if(GProp!=NULL){
			GProp->Repaint();
		}
	}
}


void	PropertyPieceDefForm::ShowItemGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	DefList.RemoveAll();
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendDefList	**BmpReceiver=new GUICmdSendDefList*[GetParamGlobal()->PageNumb];
	GUICmdReqDefList	**BmpRequester=new GUICmdReqDefList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page]	=new GUICmdSendDefList	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]	=new GUICmdReqDefList	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	}
	int row=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		GetLayersBase()->TF_SetCurrentScanPhaseNumber(phase);
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page])==true
			&& BmpReceiver[page]->IsReceived()==true){
				BmpReceiver[page]->DefList.SetPage(page);
				DefList+=BmpReceiver[page]->DefList;
			}
		}
	}
	GetLayersBase()->TF_SetCurrentScanPhaseNumber(0);
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	row=0;
	int	Numb=DefList.GetNumber();
	ui->tableWidgetResult->setRowCount(Numb);
	for(PieceDefInfo *L=DefList.GetFirst();L!=NULL;L=L->GetNext() ,row++){
		SetDataToTable(ui->tableWidgetResult ,0,row,QString::number(L->Page));
		QString	s=QString(/**/"(")
				+ QString::number(L->x1)+QString(/**/",")+QString::number(L->y1)
				+ QString(/**/")-(")
				+ QString::number(L->x2)+QString(/**/",")+QString::number(L->y2)
				+ QString(/**/")");
		SetDataToTable(ui->tableWidgetResult ,1,row,s);
		SetDataToTable(ui->tableWidgetResult ,2,row,QString::number(L->MatchingRate));
	}

	ReEntrant=false;
}

void PropertyPieceDefForm::on_tableWidgetResult_clicked(const QModelIndex &index)
{
	PieceDefInfo *L=DefList.GetItem(index.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"PieceDefImagePanel",/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		//CmdDrawImageActivate	ACmd(L->Page,0,L->ItemID);
		CmdDrawImageActivate ACmd(GetLayersBase(),L->Page,0,L->GetNumber());
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}

}

void PropertyPieceDefForm::on_pushButtonCopyByFoundItems_clicked()
{
	FlexAreaImageBuffer	Seed;
	FlexArea			OriginalArea;
	int		SweepNumber=-1;
	int		GPage=-1;
	int		SeedCount=0;
	QByteArray	SeedData;

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqSeedData	ReqSeed(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdAckSeedData	AckSeed(GetLayersBase(),sRoot,sName,globalPage);
		if(ReqSeed.Send(globalPage,0,AckSeed)==true && AckSeed.IsReceived()==true){
			if(AckSeed.SeedCount!=0){
				SeedData	=AckSeed.SeedData;
				SweepNumber		=AckSeed.SweepNumber;
				OriginalArea	=AckSeed.OriginalArea;
				GPage			=globalPage;
				SeedCount		=AckSeed.SeedCount;
				break;
			}
		}
	}
	if(GPage>=0){
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			GUICmdCopyItemFromOrg	Cmd(GetLayersBase(),sRoot,sName,globalPage);
			Cmd.OrgGlobalPage	=GPage;
			Cmd.SeedData		=SeedData;
			Cmd.SweepNumber		=SweepNumber;
			Cmd.OriginalArea	=OriginalArea;
			Cmd.SeedCount		=SeedCount;
			Cmd.Send(NULL,globalPage,0);
		}
	}
}

void PropertyPieceDefForm::on_pushButtonMatchClosed_clicked()
{
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdMatchItems	ReqSeed(GetLayersBase(),sRoot,sName,globalPage);
		ReqSeed.Send(NULL,globalPage,0);
	}
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"PieceDefImagePanel",/**/"");
	if(GProp!=NULL){
		GProp->Repaint();
	}
}
