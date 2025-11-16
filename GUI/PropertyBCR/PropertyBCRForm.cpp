#include "PropertyBCRResource.h"
#include "PropertyBCRForm.h"
#include "ui_PropertyBCRForm.h"

#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XGUI.h"
#include "XGeneralFunc.h"
#include "XGeneralDialog.h"
#include "ImageControlTools.h"
#include <omp.h>
#include "XDataInLayerCommander.h"
#include "AddBCodeInspectionDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyBCRForm::PropertyBCRForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyBCRForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	::SetColumnWidthInTable(ui->tableWidget ,0, 15);
	::SetColumnWidthInTable(ui->tableWidget ,1, 15);
	::SetColumnWidthInTable(ui->tableWidget ,2, 55);
	::SetColumnWidthInTable(ui->tableWidget ,3, 15);
}

PropertyBCRForm::~PropertyBCRForm()
{
    delete ui;
}
	
void	PropertyBCRForm::BuildForShow(void)
{
	ShowGrid();
}

void	PropertyBCRForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdBCRInspectionDrawPacket	*CmdBCRInspectionDrawVar=dynamic_cast<CmdBCRInspectionDrawPacket *>(packet);
	if(CmdBCRInspectionDrawVar!=NULL){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create BCode area");

		AddBCodeInspectionDialog	D(GetLayersBase());
		if(D.exec()==(int)true){

			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(CmdBCRInspectionDrawVar->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
				FlexArea	A=CmdBCRInspectionDrawVar->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(pdata->GetPage());
					GUICmdAddBCodeArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
					Cmd.Area				=A;
					Cmd.BCRType				=0;
					Cmd.CheckType			=D.CheckType			;
					Cmd.QuilityGrade		=D.QuilityGrade			;
					Cmd.GradeList			=D.GradeList			;
					Cmd.BarcodeOrientation	=D.BarcodeOrientation	;
					Cmd.BarcodeType			=D.BarcodeType			;
					Cmd.BarcodeIsOnlyDigit	=D.BarcodeIsOnlyDigit	;
					Cmd.SendOnly(GlobalPage,0);
				}
			}
			ShowGrid();
		}
		return;
	}
	CmdReqBCode	*CmdReqBCodeVar=dynamic_cast<CmdReqBCode *>(packet);
	if(CmdReqBCodeVar!=NULL){
		ShowGrid();
		CmdReqBCodeVar->GridList=GridList;
		return;
	}
	CmdReqBCodeInfoByItem	*CmdReqBCodeInfoByItemVar=dynamic_cast<CmdReqBCodeInfoByItem *>(packet);
	if(CmdReqBCodeInfoByItemVar!=NULL){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(CmdReqBCodeInfoByItemVar->Page);
		GUICmdReqBCodeInfoByID	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		RCmd.Phase=GetLayersBase()->GetCurrentPhase();
		RCmd.ItemID=CmdReqBCodeInfoByItemVar->ItemID;
		GUICmdAckBCodeInfoByID	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			CmdReqBCodeInfoByItemVar->CheckType			=ACmd.CheckType			;
			CmdReqBCodeInfoByItemVar->QuilityGrade		=ACmd.QuilityGrade		;
			CmdReqBCodeInfoByItemVar->GradeList			=ACmd.GradeList			;
			CmdReqBCodeInfoByItemVar->BarcodeOrientation=ACmd.BarcodeOrientation;
			CmdReqBCodeInfoByItemVar->BarcodeType		=ACmd.BarcodeType		;
			CmdReqBCodeInfoByItemVar->BarcodeIsOnlyDigit=ACmd.BarcodeIsOnlyDigit;
		}
		return;
	}
	CmdSetBCodeInfoByItem	*CmdSetBCodeInfoByItemVar=dynamic_cast<CmdSetBCodeInfoByItem *>(packet);
	if(CmdSetBCodeInfoByItemVar!=NULL){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(CmdSetBCodeInfoByItemVar->Page);
		GUICmdSetBCodeInfoByID	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		RCmd.Phase=GetLayersBase()->GetCurrentPhase();
		RCmd.ItemID				=CmdSetBCodeInfoByItemVar->ItemID				;
		RCmd.BCRType			=CmdSetBCodeInfoByItemVar->BCRType				;
		RCmd.CheckType			=CmdSetBCodeInfoByItemVar->CheckType			;
		RCmd.QuilityGrade		=CmdSetBCodeInfoByItemVar->QuilityGrade			;
		RCmd.GradeList			=CmdSetBCodeInfoByItemVar->GradeList			;	
		RCmd.BarcodeOrientation	=CmdSetBCodeInfoByItemVar->BarcodeOrientation	;	
		RCmd.BarcodeType		=CmdSetBCodeInfoByItemVar->BarcodeType			;
		RCmd.BarcodeIsOnlyDigit	=CmdSetBCodeInfoByItemVar->BarcodeIsOnlyDigit	;	
		RCmd.Send(NULL,GlobalPage,0);
		return;
	}
}

void	PropertyBCRForm::ShowGrid(void)
{
	GridList.RemoveAll();

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqBCodeList	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdAckBCodeList	SCmd(GetLayersBase(),sRoot,sName,globalPage);
		if(RCmd.Send(globalPage,0,SCmd)==true){
			BCRList	*k;
			while((k=SCmd.BCode.GetFirst())!=NULL){
				SCmd.BCode.RemoveList(k);
				k->LocalPage=page;
				GridList.AppendList(k);
			}
		}
	}
	
	ui->tableWidget->setRowCount(GridList.GetCount());
	int	L=0;
	for(BCRList	*c=GridList.GetFirst();c!=NULL;c=c->GetNext(),L++){
		::SetDataToTable(ui->tableWidget ,0,L,QString::number(c->LocalPage));
		::SetDataToTable(ui->tableWidget ,1,L,QString::number(c->ItemID));
		::SetDataToTable(ui->tableWidget ,2,L,QString(/**/"(")+QString::number(c->X1)+QString(/**/",")+QString::number(c->Y1)+QString(/**/")-(")
														 	  +QString::number(c->X2)+QString(/**/",")+QString::number(c->Y2)+QString(/**/")"));
		::SetDataToTable(ui->tableWidget ,3,L,QString::number(c->BCRType));
	}
}

void PropertyBCRForm::on_tableWidget_clicked(const QModelIndex &index)
{
	BCRList *L=GridList.GetItem(index.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->LocalPage);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->X1+P->GetOutlineOffset()->x,L->Y1+P->GetOutlineOffset()->y
									,L->X2+P->GetOutlineOffset()->x,L->Y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"BCRImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->LocalPage,0,L->ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

void PropertyBCRForm::on_pushButtonTest_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	BCRList *L=GridList.GetItem(Row);
	if(L==NULL)
		return;
	int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),L->LocalPage);
	GUICmdReqBCodeTest	RCmd(GetLayersBase(),sRoot,sName,globalPage);
	RCmd.ItemID=L->ItemID;
	DisplayImage	*GProp=(DisplayImage *)GetLayersBase()->FindByName(/**/"Inspection" ,/**/"BCRImagePanel" ,/**/"");
	if(GProp!=NULL){
		if(GProp->GetDisplayType()==DisplayImage::__Master)
			RCmd.Mastered=true;
		else
			RCmd.Mastered=false;
	}
	GUICmdAckBCodeTest	SCmd(GetLayersBase(),sRoot,sName,globalPage);
	if(RCmd.Send(globalPage,0,SCmd)==true){
		ui->labelTestBCode->setText(SCmd.Result);
	}
}

void PropertyBCRForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	BCRList *L=GridList.GetItem(Row);
	if(L==NULL)
		return;
	int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),L->LocalPage);
	GUICmdReqBCodeInfoByID	RCmd(GetLayersBase(),sRoot,sName,globalPage);
	RCmd.ItemID	=L->ItemID;
	RCmd.Phase	=GetLayersBase()->GetCurrentPhase();
	GUICmdAckBCodeInfoByID	ACmd(GetLayersBase(),sRoot,sName,globalPage);
	if(RCmd.Send(globalPage,0,ACmd)==true){
		AddBCodeInspectionDialog	D(GetLayersBase());
		D.CheckType			=ACmd.CheckType			;		    
		D.QuilityGrade		=ACmd.QuilityGrade		;
		D.GradeList			=ACmd.GradeList			;
		D.BarcodeOrientation=ACmd.BarcodeOrientation;	
		D.BarcodeType		=ACmd.BarcodeType		;
		D.BarcodeIsOnlyDigit=ACmd.BarcodeIsOnlyDigit;
		D.SetDataToWindow();
		if(D.exec()==true){
			GUICmdSetBCodeInfoByID	SCmd(GetLayersBase(),sRoot,sName,globalPage);
			SCmd.Phase				=GetLayersBase()->GetCurrentPhase();
			SCmd.ItemID				=L->ItemID;
			SCmd.CheckType			=D.CheckType			;		    
			SCmd.QuilityGrade		=D.QuilityGrade			;
			SCmd.GradeList			=D.GradeList			;
			SCmd.BarcodeOrientation	=D.BarcodeOrientation	;	
			SCmd.BarcodeType		=D.BarcodeType			;
			SCmd.BarcodeIsOnlyDigit	=D.BarcodeIsOnlyDigit	;
			if(SCmd.Send(NULL,globalPage,0)==true){
				ShowGrid();
			}
		}
	}
}

