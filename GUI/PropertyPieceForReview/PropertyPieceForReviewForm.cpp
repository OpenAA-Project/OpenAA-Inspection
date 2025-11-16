#include "AddItemDialogResource.h"
#include "PropertyPieceForReviewResource.h"
#include "PropertyPieceForReviewForm.h"
#include "ui_PropertyPieceForReviewForm.h"
#include "XPieceForReview.h"
#include "XPieceForReviewPacket.h"
#include "XGeneralFunc.h"
#include "XGUIPacketForDLL.h"
#include "AddItemDialog.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyPieceForReviewForm::PropertyPieceForReviewForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyPieceForReviewForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ui->tableWidget->setColumnWidth(0,30);
	ui->tableWidget->setColumnWidth(1,30);
	ui->tableWidget->setColumnWidth(2,150);
	ui->tableWidget->setColumnWidth(3,30);
}

PropertyPieceForReviewForm::~PropertyPieceForReviewForm()
{
    delete ui;
}

void	PropertyPieceForReviewForm::BuildForShow(void)
{
	ShowInEdit();
}
void	PropertyPieceForReviewForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPieceForReviewDrawAttr	*CmdPieceForReviewDrawAttrVar=dynamic_cast<CmdPieceForReviewDrawAttr *>(packet);
	if(CmdPieceForReviewDrawAttrVar!=NULL){
		if(ui->toolButtonOverlap->isChecked()==true){
			CmdPieceForReviewDrawAttrVar->Attr->OverlapImage=true;
		}
		else{
			CmdPieceForReviewDrawAttrVar->Attr->OverlapImage=false;
		}
		return;
	}
	CmdPieceForReviewDrawEnd	*CmdPieceForReviewDrawEndVar=dynamic_cast<CmdPieceForReviewDrawEnd *>(packet);
	if(CmdPieceForReviewDrawEndVar!=NULL){
		//GlobalPickupArea+=BlockDEnd->Area;

		int	ItemCount=0;
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			GUICmdReqItemListPieceForReview	RCmd(GetLayersBase(),sRoot,sName,globalPage);
			GUICmdAckItemListPieceForReview	ACmd(GetLayersBase(),sRoot,sName,globalPage);

			if(RCmd.Send(globalPage,0,ACmd)==true
			&& ACmd.IsReceived()==true){
				ItemCount+=ACmd.ListData.GetCount();
			}
		}
		if(ItemCount!=0){
			QMessageBox::warning (NULL, LangSolver.GetString(PropertyPieceForReviewForm_LS,LID_0)/*"Warning"*/
								, LangSolver.GetString(PropertyPieceForReviewForm_LS,LID_1)/*"1?A?E?a?I?I?a?d?C?O?E?i?Ê?E?e?}?A?I?A?á?U?1?n?B?R?s?[?@?\?d?g?p?ƒÊ?A?-???3?‘"*/);
			return;
		}

		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(CmdPieceForReviewDrawEndVar->GlobalArea,PageList);
		if(PageList.GetFirst()==NULL){
			return;
		}
		RGBStock	RGBColors;
		for(IntClass *PageClass=PageList.GetFirst();PageClass!=NULL;PageClass=PageClass->GetNext()){
			int	globalPage=PageClass->GetValue();

			AddItemDialog	ADialog(globalPage,GetLayersBase());
			if(ADialog.exec()==(int)true){
				FlexArea	A;
				//A=GlobalPickupArea;
				A=CmdPieceForReviewDrawEndVar->GlobalArea;
				GetLayersBase()->GetPageData(globalPage)->ClipMoveAreaFromGlobal(A);

				GUICmdAddItemPieceForReview	RCmd(GetLayersBase(),sRoot,sName,globalPage);
				RCmd.Area		=A;
				RCmd.AreaNumber	=ADialog.AreaNumber;
				RCmd.AreaName	=ADialog.AreaName;
				RCmd.SysRegNumber=ADialog.SysRegNumber;
				RCmd.Send(NULL,globalPage,0);
			}
		}
		ShowInEdit();
		return;
	}
}
void	PropertyPieceForReviewForm::ShowInEdit(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	ListData.RemoveAll();
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqItemListPieceForReview	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdAckItemListPieceForReview	ACmd(GetLayersBase(),sRoot,sName,globalPage);

		if(RCmd.Send(globalPage,0,ACmd)==true
		&& ACmd.IsReceived()==true){
			ListData+=ACmd.ListData;
		}
	}

	int	N=0;
	int	Numb=ListData.GetNumber();
	ui->tableWidget->setRowCount(Numb);

	for(ItemsListPieceForReview *L=ListData.GetFirst();L!=NULL;L=L->GetNext() ,N++){
		SetDataToTable(ui->tableWidget ,0,N,QString::number(L->AreaNumber));
		SetDataToTable(ui->tableWidget ,1,N,QString::number(L->GlobalPage));
		SetDataToTable(ui->tableWidget ,2,N,L->AreaName);
		SetDataToTable(ui->tableWidget ,3,N,QString::number(L->SysRegNumber));
	}

	ReEntrant=false;
}

void PropertyPieceForReviewForm::on_tableWidget_clicked(const QModelIndex &MIndex)
{
	ItemsListPieceForReview *L=ListData.GetItem(MIndex.row());
	if(L==NULL)
		return;
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(L->GlobalPage);
	if(LocalPage<0)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(LocalPage);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->X1+P->GetOutlineOffset()->x,L->Y1+P->GetOutlineOffset()->y
									,L->X2+P->GetOutlineOffset()->x,L->Y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"PieceForReviewImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
	}
}

void PropertyPieceForReviewForm::on_tableWidget_doubleClicked(const QModelIndex &MIndex)
{
	ItemsListPieceForReview *L=ListData.GetItem(MIndex.row());
	if(L==NULL)
		return;
	AddItemDialog	ADialog(L->GlobalPage,GetLayersBase(),NULL
							,L->AreaNumber
							,L->AreaName
							,L->SysRegNumber);
	if(ADialog.exec()==(int)true){
		GUICmdChangeItemPieceForReview	RCmd(GetLayersBase(),sRoot,sName,L->GlobalPage);
		RCmd.ItemID			=L->ItemID;
		RCmd.AreaNumber		=ADialog.AreaNumber;
		RCmd.AreaName		=ADialog.AreaName;
		RCmd.SysRegNumber	=ADialog.SysRegNumber;
		RCmd.Send(NULL,L->GlobalPage,0);

		ShowInEdit();
	}
}

void PropertyPieceForReviewForm::on_toolButtonOverlap_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"PieceForReviewImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->Repaint();
	}
}
