#include "PropertyPalletizeForm.h"
#include "ui_PropertyPalletizeForm.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyPalletizePacket.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XPalletizeLibrary.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"
#include "EditLibraryDialog.h"
#include "SelectLibraryDialog.h"
#include "XGeneralFunc.h"

extern	const   char	*sRoot;
extern	const   char	*sName;

PropertyPalletizeForm::PropertyPalletizeForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyPalletizeForm)
{
    ui->setupUi(this);

	SetColumnWidthInTable(ui->tableWidgetResult ,0, 14);
	SetColumnWidthInTable(ui->tableWidgetResult ,1, 14);
	SetColumnWidthInTable(ui->tableWidgetResult ,2, 14);
	SetColumnWidthInTable(ui->tableWidgetResult ,3, 14);
	SetColumnWidthInTable(ui->tableWidgetResult ,4, 14);
	SetColumnWidthInTable(ui->tableWidgetResult ,5, 14);

	Sock.connectToServer(/**/"Robot");
}

PropertyPalletizeForm::~PropertyPalletizeForm()
{
    delete ui;
}
PalletizeBase	*PropertyPalletizeForm::GetPalletizeBase(void)
{
	return (PalletizeBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Palletize");
}

void PropertyPalletizeForm::on_pushButtonEditLibrary_clicked()
{
    EditLibraryDialog   D(GetLayersBase());
    D.exec();
}

void	PropertyPalletizeForm::TransmitDirectly(GUIDirectMessage *packet)
{
	PalletizeBase	*BBase=GetPalletizeBase();
	//CmdPalletizeDrawModePacket	*BDrawModePacket=dynamic_cast<CmdPalletizeDrawModePacket *>(packet);
	//if(BDrawModePacket!=NULL){
	//	BDrawModePacket->ModeShowItem		=ui->toolButtonShowItem			->isChecked();
	//	BDrawModePacket->ModeShowRegulation	=ui->toolButtonShowRegulation	->isChecked();
	//	return;
	//}
	CmdPalletizeDrawEnd	*PalletizeDEnd=dynamic_cast<CmdPalletizeDrawEnd *>(packet);
	if(PalletizeDEnd!=NULL){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual Palletize");
		
		SelectLibraryDialog	D(GetLayersBase());
		if(D.exec()==QDialog::Accepted){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(PalletizeDEnd->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=PalletizeDEnd->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdSendAddManualPalletize	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
					Cmd.Area=A;
					Cmd.LibID=D.SelectedLibID;
					Cmd.SendOnly(GlobalPage,0);
				}
			}
			//ShowPalletizeInfoList();
		}
	}
}
void	PropertyPalletizeForm::ShowInEdit(void)
{
}
void	PropertyPalletizeForm::BuildForShow(void)
{
}
void	PropertyPalletizeForm::StartPage	(void)
{
}

void	PropertyPalletizeForm::ShowInPlayer		(int64 shownInspectionID)
{
	PalletizeItem	*Item=NULL;
	PalletizeBase	*ABase	=(PalletizeBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Palletize");
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(0);
		if(Ah!=NULL){
			PalletizeInPage		*Ap=(PalletizeInPage *)Ah->GetPageData(1);
			if(Ap!=NULL){
				Item=Ap->tGetFirstData();
			}
		}
	}
	if(Item!=NULL){
		IntList         CurrentIndexMasterPosList;
		ui->tableWidgetResult->setRowCount(Item->Results.ResultCount);
		for(int row=0;row<Item->Results.ResultCount;row++){
			::SetDataToTable(ui->tableWidgetResult, 0, row, QString::number(Item->Results.ResultList[row].ResultPosX));
			::SetDataToTable(ui->tableWidgetResult, 1, row, QString::number(Item->Results.ResultList[row].ResultPosY));
			int	RotatedIndex=Item->Results.ResultList[row].RotatedIndex;
			CmdPalletizeResultInItem	RCmd(GetLayersBase());
			RCmd.ResultIndex=row;
			Item->TransmitDirectly(&RCmd);
			::SetDataToTable(ui->tableWidgetResult, 2, row, QString::number(RCmd.Radian*180.0/M_PI));

			::SetDataToTable(ui->tableWidgetResult, 3, row, QString::number(Item->Results.ResultList[row].DiffX));
			::SetDataToTable(ui->tableWidgetResult, 4, row, QString::number(Item->Results.ResultList[row].DiffY));
			::SetDataToTable(ui->tableWidgetResult, 5, row, QString::number(Item->Results.ResultList[row].IndexMasterPos));
			CurrentIndexMasterPosList.Add(Item->Results.ResultList[row].IndexMasterPos);
		}
		for(IntClass *v=LastIndexMasterPosList.GetFirst();v!=NULL;v=v->GetNext()){
			if(CurrentIndexMasterPosList.IsInclude(v->GetValue())==false){				
				int	IndexMasterPos=v->GetValue();
				ShowResultGrid(Item ,IndexMasterPos,LastResult.ResultList);
			}
		}
		if(LastIndexMasterPosList.GetCount()==0
		&& CurrentIndexMasterPosList.GetCount()!=0){
			int	IndexMasterPos=CurrentIndexMasterPosList.GetFirst()->GetValue();
			ShowResultGrid(Item ,IndexMasterPos,Item->Results.ResultList);
		}
		LastResult=Item->Results;

		LastIndexMasterPosList=CurrentIndexMasterPosList;
	}
}

void PropertyPalletizeForm::ShowResultGrid(PalletizeItem *Item 
											,int IndexMasterPos
											,MatchingResult *MatchingResultList)
{
	PalletizeBase	*ABase	=(PalletizeBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Palletize");
	for(int row=0;row<Item->Results.ResultCount;row++){
		if(MatchingResultList[row].IndexMasterPos==IndexMasterPos){
			int	Page=0;
			ui->spinBoxRegIndex->setValue(IndexMasterPos);
			::SetDataToTable(ui->tableWidgetControl, 0, 0, QString::number(MatchingResultList[row].ResultPosX));
			::SetDataToTable(ui->tableWidgetControl, 0, 1, QString::number(MatchingResultList[row].ResultPosY));
			::SetDataToTable(ui->tableWidgetControl, 0, 2, QString::number(MatchingResultList[row].DiffX));
			::SetDataToTable(ui->tableWidgetControl, 0, 3, QString::number(MatchingResultList[row].DiffY));
			
			double	XPos=GetParamGlobal()->TransformPixelToUnitX(Page,MatchingResultList[row].ResultPosX);
			double	YPos=GetParamGlobal()->TransformPixelToUnitY(Page,MatchingResultList[row].ResultPosY);
			double	XDif=GetParamGlobal()->TransformPixelToUnitX(Page,MatchingResultList[row].DiffX);
			double	YDif=GetParamGlobal()->TransformPixelToUnitY(Page,MatchingResultList[row].DiffY);
			double	RealXPos=ABase->AffinParam[0]*XPos+ABase->AffinParam[1]*YPos+ABase->AffinParam[2];
			double	RealYPos=ABase->AffinParam[3]*XPos+ABase->AffinParam[4]*YPos+ABase->AffinParam[5];
			double	RealXDiff=ABase->AffinParam[0]*XDif+ABase->AffinParam[1]*YDif;
			double	RealYDiff=ABase->AffinParam[3]*XDif+ABase->AffinParam[4]*YDif;
			::SetDataToTable(ui->tableWidgetControl, 1, 0, QString::number(RealXPos,'f',1));
			::SetDataToTable(ui->tableWidgetControl, 1, 1, QString::number(RealYPos,'f',1));
			::SetDataToTable(ui->tableWidgetControl, 1, 2, QString::number(RealXDiff,'f',1));
			::SetDataToTable(ui->tableWidgetControl, 1, 3, QString::number(RealYDiff,'f',1));

			double Dim[5];
			Dim[0]=RealXPos;
			Dim[1]=RealYPos;
			Dim[2]=0;
			Dim[3]=RealXDiff;
			Dim[4]=RealYDiff;
			TransferMotorData(Dim);
		}
	}
}

void PropertyPalletizeForm::on_pushButtonSend_clicked()
{
	double Dim[5];
	Dim[0]=GetDataToTable(ui->tableWidgetControl, 1, 0).toDouble();
	Dim[1]=GetDataToTable(ui->tableWidgetControl, 1, 1).toDouble();
	Dim[2]=0;
	Dim[3]=GetDataToTable(ui->tableWidgetControl, 1, 2).toDouble();
	Dim[4]=GetDataToTable(ui->tableWidgetControl, 1, 3).toDouble();
	TransferMotorData(Dim);
}

void PropertyPalletizeForm::TransferMotorData(double Dim[5])
{
	int	LenData[5];
	for(int i=0;i<5;i++){	
		LenData[i]=Dim[i]*10.0;
	}
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	for(int i=0;i<5;i++){
		::Save(&Buff,LenData[i]);
	}
	Sock.write(Buff.buffer());
	Sock.flush();
}


	