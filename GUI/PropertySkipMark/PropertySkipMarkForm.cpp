#include "AddSourceItemDialogResource.h"
#include "PropertySkipMarkForm.h"
#include "ui_PropertySkipMarkForm.h"
#include"XPropertySkipMarkPacket.h"
#include "XDisplayImagePacket.h"
#include "EditItemDialog.h"
#include "XSkipMark.h"
#include <QMenu>
#include "EditSourceDialog.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertySkipMarkForm::PropertySkipMarkForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertySkipMarkForm)
{
    ui->setupUi(this);

	ui->tableWidgetList->setColumnWidth (0,36);
	ui->tableWidgetList->setColumnWidth (1,36);
	ui->tableWidgetList->setColumnWidth (2,100);
	ui->tableWidgetList->setColumnWidth (3,100);
	ui->tableWidgetList->setColumnWidth (4,36);

}

PropertySkipMarkForm::~PropertySkipMarkForm()
{
    delete ui;
}

void	PropertySkipMarkForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateSkipMarkManualPacket	*CmdCreateSkipMarkManualPacketVer=dynamic_cast<CmdCreateSkipMarkManualPacket *>(packet);
	if(CmdCreateSkipMarkManualPacketVer!=NULL){
		for(IntClass *LayerClass=CmdCreateSkipMarkManualPacketVer->LayerList.GetFirst();LayerClass!=NULL;LayerClass=LayerClass->GetNext()){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(CmdCreateSkipMarkManualPacketVer->Area, PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				EditItemDialog	D(true,GetLayersBase(),GlobalPage,LayerClass->GetValue());
				D.Reflect();
				if(D.exec()==1){
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	Area=CmdCreateSkipMarkManualPacketVer->Area;
					pdata->ClipMoveAreaFromGlobal(Area);
					if(Area.GetPatternByte()>0){
						GUICmdAddAreaManual	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
						Cmd.Area			=Area;
						Cmd.Layer			=LayerClass->GetValue();
						Cmd.ItemName		=D.ItemName;
						Cmd.NamingDLLRoot	=D.NamingDLLRoot;
						Cmd.NamingDLLName	=D.NamingDLLName;
						Cmd.NamingID		=D.NamingID;
							
						Cmd.SendOnly(GlobalPage,0);
					}
				}
			}
		}
		ShowItemGrid();
		return;
	}
}

void	PropertySkipMarkForm::BuildForShow(void)
{
	ShowItemGrid();
}

void	PropertySkipMarkForm::ShowItemGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	GridList.RemoveAll();
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendGridList	**BmpReceiver=new GUICmdSendGridList*[GetParamGlobal()->PageNumb];
	GUICmdReqGridList	**BmpRequester=new GUICmdReqGridList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page]	=new GUICmdSendGridList	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]	=new GUICmdReqGridList	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	}
	int row=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		GetLayersBase()->TF_SetCurrentScanPhaseNumber(phase);
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page])==true
			&& BmpReceiver[page]->IsReceived()==true){
				BmpReceiver[page]->GridList.SetPage(page);
				GridList+=BmpReceiver[page]->GridList;
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
	int	Numb=GridList.GetNumber();
	ui->tableWidgetList->setRowCount(Numb);
	for(SkipMarkInfo *L=GridList.GetFirst();L!=NULL;L=L->GetNext() ,row++){
		::SetDataToTable(ui->tableWidgetList ,0,row,QString::number(L->GlobalPage));
		::SetDataToTable(ui->tableWidgetList ,1,row,QString::number(L->Layer));

		QString	s=L->NamingDLLRoot + QString(/**/":")+L->NamingDLLName;
		::SetDataToTable(ui->tableWidgetList ,2,row,s);

		SetDataToTable(ui->tableWidgetList ,3,row,L->NamingItemName);
		SetDataToTable(ui->tableWidgetList ,4,row,QString::number(L->NamingItemID));
	}

	ReEntrant=false;
}

void PropertySkipMarkForm::on_tableWidgetList_clicked(const QModelIndex &index)
{
	SkipMarkInfo *L=GridList.GetItem(index.row());
	if(L==NULL)
		return;

	int	Page=GetLayersBase()->GetLocalPageFromGlobal(L->GlobalPage);
	DataInPage	*P=GetLayersBase()->GetPageData(Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"SkipMarkImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),Page,L->Layer,L->ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

void PropertySkipMarkForm::on_tableWidgetList_doubleClicked(const QModelIndex &index)
{
	QMenu	Menu(this);

	Menu.addAction(LangSolver.GetString(PropertySkipMarkForm_LS,LID_0)/*"Destination(Changed result)"*/ ,this ,SLOT(AddDestination()));
	Menu.addAction(LangSolver.GetString(PropertySkipMarkForm_LS,LID_1)/*"Source(Judge NG items)"*/ ,this ,SLOT(AddSource()));
	QPoint	Q=ui->tableWidgetList->mapToGlobal(ui->tableWidgetList->geometry().center());
	Menu.exec(Q);
}

void	PropertySkipMarkForm::AddDestination()
{
	int	R=ui->tableWidgetList->currentRow();
	if(R<0)
		return;
	SkipMarkInfo *L=GridList.GetItem(R);
	if(L==NULL)
		return;
	DisplayImage	*GProp=dynamic_cast<DisplayImage *>(GetLayersBase()->FindByName(/**/"Inspection" ,/**/"SkipMarkImagePanel" ,/**/""));
	if(GProp!=NULL){
		IntList LayerList;
		int	GlobalPage=L->GlobalPage;
			
		GUICmdReqItemInfo	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		GUICmdSendItemInfo	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.ItemID=L->ItemID;
		Cmd.Layer=L->Layer;
		if(Cmd.Send(GlobalPage,0,ACmd)==true){
			EditItemDialog	D(false,GetLayersBase(),L->GlobalPage ,L->Layer);
			D.Layer		=L->Layer;
			D.ItemName	=ACmd.ItemName;
			D.NamingDLLRoot	=ACmd.NamingDLLRoot;
			D.NamingDLLName	=ACmd.NamingDLLName;
			D.NamingID		=ACmd.NamingID;

			D.Reflect();
			if(D.exec()==2){
				GUICmdSetItemInfo	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
				Cmd.ItemID			=ACmd.ItemID;
				Cmd.Layer			=D.Layer;
				Cmd.ItemName		=D.ItemName;
				Cmd.NamingDLLRoot	=D.NamingDLLRoot;
				Cmd.NamingDLLName	=D.NamingDLLName;
				Cmd.NamingID		=D.NamingID;

				Cmd.SendOnly(GlobalPage,0);
			}
		}
		ShowItemGrid();
	}
}

void	PropertySkipMarkForm::AddSource()
{
	int	R=ui->tableWidgetList->currentRow();
	if(R<0)
		return;
	SkipMarkInfo *L=GridList.GetItem(R);
	if(L==NULL)
		return;
	EditSourceDialog	D(GetLayersBase(),L,this);
	D.exec();
}