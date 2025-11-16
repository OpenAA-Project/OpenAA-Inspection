#include "PropertyCheckDataValidationForm.h"
#include "ui_PropertyCheckDataValidationForm.h"
#include "ExistItemAreaDialog.h"
#include "ExistItemVectorDialog.h"
#include "MinMaxDialog.h"
#include "ProhibiteItemDialog.h"
#include "XDisplayImagePacket.h"
#include "ShowNGMessageForm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyCheckDataValidationForm::PropertyCheckDataValidationForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyCheckDataValidationForm)
{
    ui->setupUi(this);

	::SetColumnWidthInTable(ui->tableWidget ,0, 15);
	::SetColumnWidthInTable(ui->tableWidget ,1, 15);
	::SetColumnWidthInTable(ui->tableWidget ,2, 20);
	::SetColumnWidthInTable(ui->tableWidget ,3, 40);

	ModeShowNGMessage=true;
	NGMessageWindow	=NULL;

	GetParamGUI()->SetParam(&ModeShowNGMessage, /**/"PropertyCheckDataValidation",/**/"ModeShowNGMessage"	
												,"Mode to show NG message"		);

}

PropertyCheckDataValidationForm::~PropertyCheckDataValidationForm()
{
    delete ui;
}

CheckDataValidationBase	*PropertyCheckDataValidationForm::GetCheckDataValidationBase(void)
{
    return (CheckDataValidationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckDataValidation");
}

void	PropertyCheckDataValidationForm::ReadyParam(void)
{
	CheckDataValidationBase	*ABase=GetCheckDataValidationBase();
	if(ABase!=NULL){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(phase);
			for(int page=0;page<GetPageNumb();page++){
				CheckDataValidationInPage	*Ap=dynamic_cast<CheckDataValidationInPage *>(Ah->GetPageData(page));
				connect(Ap,SIGNAL(SignalNGOccurs(int,int)),this,SLOT(SlotShowNGMessage(int,int)),Qt::QueuedConnection);
			}
		}
	}
}

void	PropertyCheckDataValidationForm::ShowInEdit(void)
{
}
void	PropertyCheckDataValidationForm::StartPage(void)
{
}
void	PropertyCheckDataValidationForm::BuildForShow(void)
{
}

void	PropertyCheckDataValidationForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CheckDataValidationBase	*BBase=GetCheckDataValidationBase();

	CmdCheckDataValidationDrawModePacket	*BDrawModePacket=dynamic_cast<CmdCheckDataValidationDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		CheckDataValidationType	VType;
		if(ui->toolButtonExistItemArea->isChecked()==true){
			VType=CheckDataValidation_ExistItemArea;
		}
		else
		if(ui->toolButtonExistItemVector->isChecked()==true){
			VType=CheckDataValidation_ExistItemVector;
		}
		else
		if(ui->toolButtonMinMax->isChecked()==true){
			VType=CheckDataValidation_MinMax;
		}
		else
		if(ui->toolButtonProhibiteItem->isChecked()==true){
			VType=CheckDataValidation_ProhibiteItem;
		}
		BDrawModePacket->VType=VType;
		return;
	}
	CmdCheckDataValidationDrawEnd	*CheckDataValidationDEnd=dynamic_cast<CmdCheckDataValidationDrawEnd *>(packet);
	if(CheckDataValidationDEnd!=NULL){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual CheckDataValidation");
		
		QByteArray	WArray;
		int32	SelectedLibType	;
		int32	SelectedLibID	;
		CheckDataValidationBase	*ABase=GetCheckDataValidationBase();
		CheckDataValidationType	VType;
		if(ui->toolButtonExistItemArea->isChecked()==true){
			VType=CheckDataValidation_ExistItemArea;
			ExistItemAreaDialog	D(GetLayersBase());
			if(D.exec()!=1)
				return;
			CmdCreateThreshold	CCmd(GetLayersBase());
			CCmd.VType=VType;
			ABase->TransmitDirectly(&CCmd);
			SelectedLibType	=D.SelectedLibType;
			SelectedLibID	=D.SelectedLibID;
			CheckDataValidationExistItemAreaThreshold	*TmpThreshold=(CheckDataValidationExistItemAreaThreshold *)CCmd.Thr;
			D.GetCurrentItem(TmpThreshold);
			CmdSaveThreshold	SCmd(GetLayersBase());
			SCmd.Thr=TmpThreshold;
			ABase->TransmitDirectly(&SCmd);
			WArray=SCmd.Data;
			delete	CCmd.Thr;
		}
		else
		if(ui->toolButtonExistItemVector->isChecked()==true){
			VType=CheckDataValidation_ExistItemVector;
			ExistItemVectorDialog	D(GetLayersBase());
			if(D.exec()!=1)
				return;
			CmdCreateThreshold	CCmd(GetLayersBase());
			CCmd.VType=VType;
			ABase->TransmitDirectly(&CCmd);
			SelectedLibType	=D.SelectedLibType;
			SelectedLibID	=D.SelectedLibID;
			CheckDataValidationExistItemVectorThreshold	*TmpThreshold=(CheckDataValidationExistItemVectorThreshold *)CCmd.Thr;
			D.GetCurrentItem(TmpThreshold);
			CmdSaveThreshold	SCmd(GetLayersBase());
			SCmd.Thr=TmpThreshold;
			ABase->TransmitDirectly(&SCmd);
			WArray=SCmd.Data;
			delete	CCmd.Thr;
		}
		else
		if(ui->toolButtonMinMax->isChecked()==true){
			VType=CheckDataValidation_MinMax;
			MinMaxDialog	D(GetLayersBase());
			if(D.exec()!=1)
				return;
			CmdCreateThreshold	CCmd(GetLayersBase());
			CCmd.VType=VType;
			ABase->TransmitDirectly(&CCmd);
			SelectedLibType	=D.SelectedLibType;
			SelectedLibID	=D.SelectedLibID;
			CheckDataValidationCheckMinMaxThreshold	*TmpThreshold=(CheckDataValidationCheckMinMaxThreshold *)CCmd.Thr;
			D.GetCurrentItem(TmpThreshold);
			CmdSaveThreshold	SCmd(GetLayersBase());
			SCmd.Thr=TmpThreshold;
			ABase->TransmitDirectly(&SCmd);
			WArray=SCmd.Data;
			delete	CCmd.Thr;
		}
		else
		if(ui->toolButtonProhibiteItem->isChecked()==true){
			VType=CheckDataValidation_ProhibiteItem;
			ProhibiteItemDialog	D(GetLayersBase());
			if(D.exec()!=1)
				return;
			CmdCreateThreshold	CCmd(GetLayersBase());
			CCmd.VType=VType;
			ABase->TransmitDirectly(&CCmd);
			SelectedLibType	=D.SelectedLibType;
			SelectedLibID	=D.SelectedLibID;
			CheckDataValidationProhibiteItemThreshold	*TmpThreshold=(CheckDataValidationProhibiteItemThreshold *)CCmd.Thr;
			D.GetCurrentItem(TmpThreshold);
			CmdSaveThreshold	SCmd(GetLayersBase());
			SCmd.Thr=TmpThreshold;
			ABase->TransmitDirectly(&SCmd);
			WArray=SCmd.Data;
			delete	CCmd.Thr;
		}

		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(CheckDataValidationDEnd->Area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			int	page=P->GetValue();
			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
			FlexArea	A=CheckDataValidationDEnd->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdSendAddManualCheckDataValidation	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
				Cmd.Area=A;
				Cmd.LayerList=CheckDataValidationDEnd->LayerList;
				Cmd.LibID	=SelectedLibID;
				Cmd.LibType	=SelectedLibType;
				Cmd.BItem	=WArray;
				Cmd.VType	=VType;
				Cmd.SendOnly(GlobalPage,0);
			}
		}
		ShowList();
	}
	//CmdCheckDataValidationShowAttrPacket	*ShowAttr=dynamic_cast<CmdCheckDataValidationShowAttrPacket *>(packet);
	//if(ShowAttr!=NULL){
	//
	//}
}
void    PropertyCheckDataValidationForm::SlotShowNGMessage(int phase ,int page)
{
	if(ModeShowNGMessage==true){
		if(NGMessageWindow==NULL){
			NGMessageWindow=new ShowNGMessageForm();
		}
		CheckDataValidationBase	*ABase=GetCheckDataValidationBase();
		if(ABase!=NULL){
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(phase);
			if(Ah!=NULL){
				CheckDataValidationInPage	*Ap=dynamic_cast<CheckDataValidationInPage *>(Ah->GetPageData(page));
				if(Ap!=NULL){
					NGMessageWindow->show();
					NGMessageWindow->SetMessage(Ap->NGMessage);
					NGMessageWindow->raise();
				}
			}
		}
	}
}

void PropertyCheckDataValidationForm::ShowList(void)
{
	CheckDataValidationType	VType;
	if(ui->toolButtonExistItemArea->isChecked()==true){
		VType=CheckDataValidation_ExistItemArea;
	}
	else
	if(ui->toolButtonExistItemVector->isChecked()==true){
		VType=CheckDataValidation_ExistItemVector;
	}
	else
	if(ui->toolButtonMinMax->isChecked()==true){
		VType=CheckDataValidation_MinMax;
	}
	else
	if(ui->toolButtonProhibiteItem->isChecked()==true){
		VType=CheckDataValidation_ProhibiteItem;
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
	for(CheckDataValidationGridList *L=GridList.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		::SetDataToTable(ui->tableWidget, 0, Row, QString::number(L->Page));
		::SetDataToTable(ui->tableWidget, 1, Row, QString::number(L->ItemID));
		::SetDataToTable(ui->tableWidget, 2, Row, QString::number(L->LibType)
												 +QString(":")
												 +GetLayersBase()->GetLibTypeName(L->LibType));
		::SetDataToTable(ui->tableWidget, 3, Row, QString::number(L->LibID)
												 +QString(":")
												 +GetLayersBase()->GetLibraryName(L->LibType,L->LibID));
	}
}

void PropertyCheckDataValidationForm::ReDrawImage(void)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"CheckDataValidationImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->Repaint();
	}
}

void PropertyCheckDataValidationForm::on_toolButtonExistItemArea_clicked()
{
	ShowList();
	ReDrawImage();
}


void PropertyCheckDataValidationForm::on_toolButtonExistItemVector_clicked()
{
	ShowList();
	ReDrawImage();
}


void PropertyCheckDataValidationForm::on_toolButtonMinMax_clicked()
{
	ShowList();
	ReDrawImage();
}


void PropertyCheckDataValidationForm::on_toolButtonProhibiteItem_clicked()
{
	ShowList();
	ReDrawImage();
}


void PropertyCheckDataValidationForm::on_tableWidget_clicked(const QModelIndex &index)
{
	static	bool	ReEntrant=false;
	if(ReEntrant==true)
		return;
	ReEntrant=true;

	int	row=ui->tableWidget->currentRow();
	if(row<0){
		ReEntrant=false;
		return;
	}
	CheckDataValidationGridList *L=GridList.GetItem(row);
	if(L==NULL){
		ReEntrant=false;
		return;
	}

	DataInPage	*P=GetLayersBase()->GetPageData(L->Page);
	if(P!=NULL){
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"CheckDataValidationImagePanel" ,/**/"");
		if(GProp!=NULL){
			CmdDrawImageRectPacket	Cmd( GetLayersBase()
										,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
										,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
			GProp->TransmitDirectly(&Cmd);
		}
	}
	ReEntrant=false;

}


void PropertyCheckDataValidationForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	static	bool	ReEntrant=false;
	if(ReEntrant==true)
		return;
	ReEntrant=true;

	int	row=ui->tableWidget->currentRow();
	if(row<0){
		ReEntrant=false;
		return;
	}
	CheckDataValidationGridList *L=GridList.GetItem(row);
	if(L==NULL){
		ReEntrant=false;
		return;
	}
	QByteArray	BItem;
	int	GlobalPage=L->Page;
	GUICmdReqCheckDataValidationItemData	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	GUICmdAckCheckDataValidationItemData	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
	RCmd.Phase	=GetLayersBase()->GetCurrentPhase();
	RCmd.Page	=L->Page;
	RCmd.ItemID	=L->ItemID;
	int	SelectedLibType	;
	int	SelectedLibID	;
	FlexArea	SelectedArea;

	if(RCmd.Send(GlobalPage,0,ACmd)==true){
		BItem=ACmd.BItem;
		SelectedLibType	=ACmd.LibType;
		SelectedLibID	=ACmd.LibID	 ;
		SelectedArea	=ACmd.Area;
	}
	QByteArray	WArray;
	int	Ret=-1;
	CheckDataValidationType	VType;
	CheckDataValidationBase	*ABase=GetCheckDataValidationBase();
	if(ui->toolButtonExistItemArea->isChecked()==true){
		VType=CheckDataValidation_ExistItemArea;

		CmdCreateThreshold	CCmd(GetLayersBase());
		CCmd.VType=VType;
		ABase->TransmitDirectly(&CCmd);
			
		CmdLoadThreshold	LCmd(GetLayersBase());
		LCmd.Thr=CCmd.Thr;
		LCmd.Data=BItem;
		ABase->TransmitDirectly(&LCmd);
		CheckDataValidationExistItemAreaThreshold	*TmpThreshold=(CheckDataValidationExistItemAreaThreshold *)CCmd.Thr;
		
		ExistItemAreaDialog	D(GetLayersBase());
		D.SetCurrentItem(TmpThreshold);
		Ret=D.exec();
		D.GetCurrentItem(TmpThreshold);
			
		CmdSaveThreshold	SCmd(GetLayersBase());
		SCmd.Thr=TmpThreshold;
		ABase->TransmitDirectly(&SCmd);
		WArray=SCmd.Data;
		delete	CCmd.Thr;
	}
	else
	if(ui->toolButtonExistItemVector->isChecked()==true){
		VType=CheckDataValidation_ExistItemVector;

		CmdCreateThreshold	CCmd(GetLayersBase());
		CCmd.VType=VType;
		ABase->TransmitDirectly(&CCmd);
			
		CmdLoadThreshold	LCmd(GetLayersBase());
		LCmd.Thr=CCmd.Thr;
		LCmd.Data=BItem;
		ABase->TransmitDirectly(&LCmd);
		CheckDataValidationExistItemVectorThreshold	*TmpThreshold=(CheckDataValidationExistItemVectorThreshold *)CCmd.Thr;
		
		ExistItemVectorDialog	D(GetLayersBase());
		D.SetCurrentItem(TmpThreshold);
		Ret=D.exec();
		D.GetCurrentItem(TmpThreshold);
			
		CmdSaveThreshold	SCmd(GetLayersBase());
		SCmd.Thr=TmpThreshold;
		ABase->TransmitDirectly(&SCmd);
		WArray=SCmd.Data;
		delete	CCmd.Thr;
	}
	else
	if(ui->toolButtonMinMax->isChecked()==true){
		VType=CheckDataValidation_MinMax;

		CmdCreateThreshold	CCmd(GetLayersBase());
		CCmd.VType=VType;
		ABase->TransmitDirectly(&CCmd);
			
		CmdLoadThreshold	LCmd(GetLayersBase());
		LCmd.Thr=CCmd.Thr;
		LCmd.Data=BItem;
		ABase->TransmitDirectly(&LCmd);
		CheckDataValidationCheckMinMaxThreshold	*TmpThreshold=(CheckDataValidationCheckMinMaxThreshold *)CCmd.Thr;
		
		MinMaxDialog	D(GetLayersBase());
		D.SetCurrentItem(TmpThreshold);
		Ret=D.exec();
		D.GetCurrentItem(TmpThreshold);
			
		CmdSaveThreshold	SCmd(GetLayersBase());
		SCmd.Thr=TmpThreshold;
		ABase->TransmitDirectly(&SCmd);
		WArray=SCmd.Data;
		delete	CCmd.Thr;
	}
	else
	if(ui->toolButtonProhibiteItem->isChecked()==true){
		VType=CheckDataValidation_ProhibiteItem;

		CmdCreateThreshold	CCmd(GetLayersBase());
		CCmd.VType=VType;
		ABase->TransmitDirectly(&CCmd);
			
		CmdLoadThreshold	LCmd(GetLayersBase());
		LCmd.Thr=CCmd.Thr;
		LCmd.Data=BItem;
		ABase->TransmitDirectly(&LCmd);
		CheckDataValidationProhibiteItemThreshold	*TmpThreshold=(CheckDataValidationProhibiteItemThreshold *)CCmd.Thr;
	
		ProhibiteItemDialog	D(GetLayersBase());
		D.SetCurrentItem(TmpThreshold);
		Ret=D.exec();
		D.GetCurrentItem(TmpThreshold);
			
		CmdSaveThreshold	SCmd(GetLayersBase());
		SCmd.Thr=TmpThreshold;
		ABase->TransmitDirectly(&SCmd);
		WArray=SCmd.Data;
		delete	CCmd.Thr;
	}

	if(Ret==1){	//New
		GUICmdSendAddManualCheckDataValidation	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		SCmd.Phase	=GetLayersBase()->GetCurrentPhase();
		SCmd.Area	=SelectedArea;
		SCmd.BItem	=WArray;
		SCmd.LibType=SelectedLibType;
		SCmd.LibID	=SelectedLibID;
		SCmd.VType	=VType;

		SCmd.Send(NULL,GlobalPage,0);
	}
	else
	if(Ret==2){	//Modify
		GUICmdSetCheckDataValidationItemData	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		SCmd.Phase	=GetLayersBase()->GetCurrentPhase();
		SCmd.Page	=L->Page;
		SCmd.ItemID	=L->ItemID;
		SCmd.BItem	=WArray;
		SCmd.LibType=SelectedLibType;
		SCmd.LibID	=SelectedLibID;

		SCmd.Send(NULL,GlobalPage,0);
	}
	else
	if(Ret==3){	//Delete
		GUICmdDeleteCheckDataValidationItem	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		SCmd.Phase	=GetLayersBase()->GetCurrentPhase();
		SCmd.Page	=L->Page;
		SCmd.ItemID	=L->ItemID;
		SCmd.Send(NULL,GlobalPage,0);
	}
	ShowList();
	ReDrawImage();

	ReEntrant=false;
}

