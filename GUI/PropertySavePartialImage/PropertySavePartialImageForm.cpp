#include "PropertySavePartialImageForm.h"
#include "ui_PropertySavePartialImageForm.h"
#include "XPropertySavePartialImagePacket.h"
#include "XGeneralFunc.h"

extern	char	*sRoot;
extern	char	*sName;

PropertySavePartialImageForm::PropertySavePartialImageForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertySavePartialImageForm)
{
    ui->setupUi(this);
}

PropertySavePartialImageForm::~PropertySavePartialImageForm()
{
    delete ui;
}

void	PropertySavePartialImageForm::BuildForShow(void)
{
}

void	PropertySavePartialImageForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetDrawAttr	*CmdGetDrawAttrVar=dynamic_cast<CmdGetDrawAttr *>(packet);
	if(CmdGetDrawAttrVar!=NULL){
		if(ui->toolButtonImage->isChecked()==true)
			CmdGetDrawAttrVar->DMode=SavePartialImageDrawAttr::_SPI_Image;
		else
			CmdGetDrawAttrVar->DMode=SavePartialImageDrawAttr::_SPI_Area;
		return;
	}
	CmdCreateSavePartialImageManualPacket	*CmdCreateSavePartialImageManualPacketVar=dynamic_cast<CmdCreateSavePartialImageManualPacket *>(packet);
	if(CmdCreateSavePartialImageManualPacketVar!=NULL){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(CmdCreateSavePartialImageManualPacketVar->Area, PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
			FlexArea	Area=CmdCreateSavePartialImageManualPacketVar->Area;
			pdata->ClipMoveAreaFromGlobal(Area);
			if(Area.GetPatternByte()>0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(pdata->GetPage());
				GUICmdAddAreaManual	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
				Cmd.Area=Area;
				Cmd.SendOnly(GlobalPage,0);
			}
		}
		ShowGrid();
		return;
	}

}

void	PropertySavePartialImageForm::ShowGrid(void)
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

