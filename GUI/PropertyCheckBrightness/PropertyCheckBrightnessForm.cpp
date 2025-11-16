#include "AddItemDialogResource.h"
#include "PropertyCheckBrightnessForm.h"
#include "ui_PropertyCheckBrightnessForm.h"
#include"XPropertyCheckBrightnessPacket.h"
#include "XDisplayImagePacket.h"
#include "AddItemDialog.h"
#include "XCheckBrightness.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyCheckBrightnessForm::PropertyCheckBrightnessForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyCheckBrightnessForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ui->tableWidget->setColumnWidth (0,100);
	ui->tableWidget->setColumnWidth (1,36);
	ui->tableWidget->setColumnWidth (2,36);
	ui->tableWidget->setColumnWidth (3,100);
	ui->tableWidget->setColumnWidth (4,70);
	ui->tableWidget->setColumnWidth (5,30);
	ui->tableWidget->setColumnWidth (6,30);
}

PropertyCheckBrightnessForm::~PropertyCheckBrightnessForm()
{
    delete ui;
}
void	PropertyCheckBrightnessForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateCheckBrightnessManualPacket	*CmdCreateCheckBrightnessManualPacketVer=dynamic_cast<CmdCreateCheckBrightnessManualPacket *>(packet);
	if(CmdCreateCheckBrightnessManualPacketVer!=NULL){
		AddItemDialog	D(GetLayersBase());
		if(D.exec()==(int)true){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(CmdCreateCheckBrightnessManualPacketVer->Area, PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
				FlexArea	Area=CmdCreateCheckBrightnessManualPacketVer->Area;
				pdata->ClipMoveAreaFromGlobal(Area);
				if(Area.GetPatternByte()>0){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(pdata->GetPage());
					GUICmdAddAreaManual	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
					Cmd.Area=Area;
					Cmd.LayerList=CmdCreateCheckBrightnessManualPacketVer->LayerList;
					Cmd.ItemName	=D.ItemName;
					Cmd.ThreshL		=D.ThreshL;
					Cmd.ThreshH		=D.ThreshH;
					Cmd.RepeatableCount	=D.RepeatableCount;
					Cmd.RegNumber	=D.RegNumber;
					Cmd.Condition	=D.Condition;
					Cmd.SendOnly(GlobalPage,0);
				}
			}
		}
		ShowItemGrid();
		return;
	}
}
void	PropertyCheckBrightnessForm::BuildForShow(void)
{
	ShowItemGrid();
}

void	PropertyCheckBrightnessForm::ShowItemGrid(void)
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
	ui->tableWidget->setRowCount(Numb);
	for(CheckBrightnessInfo *L=GridList.GetFirst();L!=NULL;L=L->GetNext() ,row++){
		SetDataToTable(ui->tableWidget ,0,row,L->ItemName);
		SetDataToTable(ui->tableWidget ,1,row,QString::number(L->Page));
		SetDataToTable(ui->tableWidget ,2,row,QString::number(L->Layer));
		QString	s=QString(/**/"(")
				+ QString::number(L->x1)+QString(/**/",")+QString::number(L->y1)
				+ QString(/**/")-(")
				+ QString::number(L->x2)+QString(/**/",")+QString::number(L->y2)
				+ QString(/**/")");
		SetDataToTable(ui->tableWidget ,3,row,s);
		switch(L->Condition){
			case CheckBrightnessItem::_AverageMustBeInside:
				SetDataToTable(ui->tableWidget ,4,row,/**/"Average Inside");
				break;
			case CheckBrightnessItem::_AllMustBeInside:
				SetDataToTable(ui->tableWidget ,4,row,/**/"All Inside");
				break;
			case CheckBrightnessItem::_OneMustBeInsideAtLeast:
				SetDataToTable(ui->tableWidget ,4,row,/**/"One Inside");
				break;
			case CheckBrightnessItem::_AverageMustBeOutside:
				SetDataToTable(ui->tableWidget ,4,row,/**/"Average Outside");
				break;
			case CheckBrightnessItem::_AllMustBeOutside:
				SetDataToTable(ui->tableWidget ,4,row,/**/"All Outside");
				break;
			case CheckBrightnessItem::_OneMustBeOutsideAtLeast:
				SetDataToTable(ui->tableWidget ,4,row,/**/"One Outside");
				break;
			default:
				SetDataToTable(ui->tableWidget ,4,row,/**/"Invalid");
		}

		SetDataToTable(ui->tableWidget ,5,row,QString::number(L->ThreshL));
		SetDataToTable(ui->tableWidget ,6,row,QString::number(L->ThreshH));
	}

	ReEntrant=false;
}
void PropertyCheckBrightnessForm::on_tableWidget_clicked(const QModelIndex &index)
{
	CheckBrightnessInfo *L=GridList.GetItem(index.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"CheckBrightnessImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->Page,L->Layer,L->ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

void PropertyCheckBrightnessForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	CheckBrightnessInfo *L=GridList.GetItem(index.row());
	if(L==NULL)
		return;
	DisplayImage	*GProp=dynamic_cast<DisplayImage *>(GetLayersBase()->FindByName(/**/"Inspection" ,/**/"CheckBrightnessImagePanel" ,/**/""));
	if(GProp!=NULL){
		IntList LayerList;
		int	GlobalPage=L->Page;
			
		GUICmdReqItemInfo	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		GUICmdSendItemInfo	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.ItemID=L->ItemID;
		Cmd.Layer=L->Layer;
		if(Cmd.Send(GlobalPage,0,ACmd)==true){
			AddItemDialog	D(GetLayersBase());
			D.ItemName	=ACmd.ItemName;
			D.ThreshH	=ACmd.ThreshH;
			D.ThreshL	=ACmd.ThreshL;
			D.RegNumber	=ACmd.RegNumber;
			D.RepeatableCount	=ACmd.RepeatableCount;
			D.Condition	=ACmd.Condition;
			D.Reflect();
			if(D.exec()==(int)true){
				GUICmdSetItemInfo	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
				Cmd.ItemID		=ACmd.ItemID;
				Cmd.ItemName	=D.ItemName;
				Cmd.Layer		=L->Layer;
				Cmd.ThreshL		=D.ThreshL;
				Cmd.ThreshH		=D.ThreshH;
				Cmd.RepeatableCount	=D.RepeatableCount;
				Cmd.RegNumber	=D.RegNumber;
				Cmd.Condition	=D.Condition;
				Cmd.SendOnly(GlobalPage,0);
			}
		}
	}
}

//================================================================================
GUICmdReqGridList::GUICmdReqGridList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqGridList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendGridList	*SendBack=GetSendBack(GUICmdSendGridList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"CheckBrightness");
	if(PBase==NULL)
		return;
	CheckBrightnessInPage	*PPage=dynamic_cast<CheckBrightnessInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqCheckBrightnessInfo	Da(GetLayersBase());
		Da.Info			=&SendBack->GridList;
		PPage->TransmitDirectly(&Da);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendGridList::GUICmdSendGridList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendGridList::Load(QIODevice *f)
{
	if(GridList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendGridList::Save(QIODevice *f)
{
	if(GridList.Save(f)==false)
		return false;
	return true;
}

GUICmdAddAreaManual::GUICmdAddAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ThreshL	=0;
	ThreshH	=0;
	RepeatableCount	=0;
	RegNumber		=400;
	Condition	=CheckBrightnessItem::_AverageMustBeInside;
}

bool	GUICmdAddAreaManual::Load(QIODevice *f)
{
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,ThreshL)==false)
		return false;
	if(::Load(f,ThreshH)==false)
		return false;
	if(::Load(f,RepeatableCount)==false)
		return false;
	if(::Load(f,RegNumber)==false)
		return false;
	int16	d;
	if(::Load(f,d)==false)
		return false;
	Condition	=(CheckBrightnessItem::_Condition)d;
	if(LayerList.Load(f)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAddAreaManual::Save(QIODevice *f)
{
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,ThreshL)==false)
		return false;
	if(::Save(f,ThreshH)==false)
		return false;
	if(::Save(f,RepeatableCount)==false)
		return false;
	if(::Save(f,RegNumber)==false)
		return false;
	int16	d=(int16)Condition;
	if(::Save(f,d)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAddAreaManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"CheckBrightness");
	if(PBase==NULL)
		return;
	CheckBrightnessInPage	*PPage=dynamic_cast<CheckBrightnessInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdAddAreaManual	Da(GetLayersBase());
		Da.ItemName	=ItemName;
		Da.ThreshL		=ThreshL;
		Da.ThreshH		=ThreshH;
		Da.RepeatableCount	=RepeatableCount;
		Da.RegNumber	=RegNumber;
		Da.Condition	=Condition;
		Da.LayerList	=LayerList;
		Da.Area			=Area;

		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

GUICmdReqItemInfo::GUICmdReqItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID	=0;
	Layer	=0;
}
bool	GUICmdReqItemInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}
	
bool	GUICmdReqItemInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdReqItemInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendItemInfo	*SendBack=GetSendBack(GUICmdSendItemInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"CheckBrightness");
	if(PBase==NULL)
		return;
	CheckBrightnessInPage	*PPage=dynamic_cast<CheckBrightnessInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqItemInfo	Da(GetLayersBase());
		Da.ItemID	=ItemID;
		Da.Layer	=Layer;
		PPage->TransmitDirectly(&Da);
		SendBack->ItemID			=Da.ItemID;
		SendBack->ItemName			=Da.ItemName;
		SendBack->ThreshL			=Da.ThreshL;
		SendBack->ThreshH			=Da.ThreshH;
		SendBack->RepeatableCount	=Da.RepeatableCount;
		SendBack->RegNumber			=Da.RegNumber;
		SendBack->Condition			=Da.Condition;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdSendItemInfo::GUICmdSendItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendItemInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,ThreshL)==false)
		return false;
	if(::Load(f,ThreshH)==false)
		return false;
	if(::Load(f,RepeatableCount)==false)
		return false;
	if(::Load(f,RegNumber)==false)
		return false;
	int16	d;
	if(::Load(f,d)==false)
		return false;
	Condition	=(CheckBrightnessItem::_Condition)d;
	return true;
}
bool	GUICmdSendItemInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,ThreshL)==false)
		return false;
	if(::Save(f,ThreshH)==false)
		return false;
	if(::Save(f,RepeatableCount)==false)
		return false;
	if(::Save(f,RegNumber)==false)
		return false;
	int16	d=(int16)Condition;
	if(::Save(f,d)==false)
		return false;
	return true;
}

GUICmdSetItemInfo::GUICmdSetItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID	=-1;
	Layer	=-1;
	ThreshL	=0;
	ThreshH	=0;
	RepeatableCount	=0;
	RegNumber		=400;
	Condition		=CheckBrightnessItem::_AllMustBeInside;
}
bool	GUICmdSetItemInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,ThreshL)==false)
		return false;
	if(::Load(f,ThreshH)==false)
		return false;
	if(::Load(f,RepeatableCount)==false)
		return false;
	if(::Load(f,RegNumber)==false)
		return false;
	int16	d;
	if(::Load(f,d)==false)
		return false;
	Condition	=(CheckBrightnessItem::_Condition)d;
	return true;
}
bool	GUICmdSetItemInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,ThreshL)==false)
		return false;
	if(::Save(f,ThreshH)==false)
		return false;
	if(::Save(f,RepeatableCount)==false)
		return false;
	if(::Save(f,RegNumber)==false)
		return false;
	int16	d=(int16)Condition;
	if(::Save(f,d)==false)
		return false;
	return true;
}

void	GUICmdSetItemInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"CheckBrightness");
	if(PBase==NULL)
		return;
	CheckBrightnessInPage	*PPage=dynamic_cast<CheckBrightnessInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdUpdateManual	Da(GetLayersBase());
		Da.ItemName		=ItemName;
		Da.ItemID		=ItemID;
		Da.ThreshL		=ThreshL;
		Da.ThreshH		=ThreshH;
		Da.RepeatableCount	=RepeatableCount;
		Da.RegNumber	=RegNumber;
		Da.Condition	=Condition;
		Da.Layer		=Layer;

		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

