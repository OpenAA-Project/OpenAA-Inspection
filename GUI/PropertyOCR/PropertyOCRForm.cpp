#include "PropertyOCRForm.h"
#include "ui_PropertyOCRForm.h"
#include "EditOCRItemDialog.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XGUI.h"
#include "XGeneralDialog.h"
#include "ImageControlTools.h"
#include <omp.h>
#include "XDataInLayerCommander.h"
#include "XPropertyOCRPacket.h"
#include "SelectOnePage.h"
#include "AddMonoManualItemForm.h"
#include "AddManualItemForm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyOCRForm::PropertyOCRForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyOCRForm)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth(0,32);
	ui->tableWidget->setColumnWidth(1,32);
	ui->tableWidget->setColumnWidth(2,96);
	ui->tableWidget->setColumnWidth(3,120);
}

PropertyOCRForm::~PropertyOCRForm()
{
    delete ui;
}

void	PropertyOCRForm::BuildForShow(void)
{
	ShowGrid();
}

void	PropertyOCRForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdOCRInspectionDrawPacket	*CmdOCRInspectionDrawVar=dynamic_cast<CmdOCRInspectionDrawPacket *>(packet);
	if(CmdOCRInspectionDrawVar!=NULL){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create OCR area");

		IntList PageList;
		int		SelectedPage;
		GetLayersBase()->GetLocalPageFromArea(CmdOCRInspectionDrawVar->Area,PageList);
		if(PageList.GetCount()>1){
			SelectOnePage	P(GetLayersBase(),PageList);
			if(P.exec()!=true)
				return;
			SelectedPage=P.SelectedPage;
		}
		else if(PageList.GetCount()==1){
			SelectedPage=PageList[0];
		}
		else{
			return;
		}

		EditOCRItemDialog	E(GetLayersBase());
		if(E.exec()==1){
			DataInPage	*pdata=GetLayersBase()->GetPageData(SelectedPage);
			FlexArea	A=CmdOCRInspectionDrawVar->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				int	GlobalPage=SelectedPage;
				GUICmdAddOCRArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
				Cmd.AbsLR			=E.AbsLR;
				Cmd.AbsHR			=E.AbsHR;
				Cmd.AbsLG			=E.AbsLG;
				Cmd.AbsHG			=E.AbsHG;
				Cmd.AbsLB			=E.AbsLB;
				Cmd.AbsHB			=E.AbsHB;
				Cmd.EnsmallDot		=E.EnsmallDot;
				Cmd.EnlargeDot		=E.EnlargeDot;
				Cmd.BlockWidth		=E.BlockWidth;
				Cmd.BlockHeight		=E.BlockHeight;
				Cmd.MinSize			=E.MinSize;
				Cmd.Mergin			=E.Mergin;
				Cmd.MaskingColor	=E.MaskingColor;
				Cmd.UseColorLogic	=E.UseColorLogic;
				Cmd.Rotation		=E.Rotation;
			
				Cmd.Area					=A;
				Cmd.ItemName				=E.ItemName;
				Cmd.RegNumber				=E.RegNumber;
				Cmd.InspectMatching			=E.InspectMatching;
				Cmd.SaveIntoResult			=E.SaveIntoResult;
				Cmd.OKByFailingRecognition	=E.OKByFailingRecognition;
				Cmd.CorrectList				=E.CorrectList;
				Cmd.SendOnly(GlobalPage,0);
			}
		}
		
		ShowGrid();
		return;
	}
}

void	PropertyOCRForm::ShowGrid(void)
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
	GUICmdAckOCRList	**BmpReceiver=new GUICmdAckOCRList*[GetParamGlobal()->PageNumb];
	GUICmdReqOCRList	**BmpRequester=new GUICmdReqOCRList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page]	=new GUICmdAckOCRList	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]	=new GUICmdReqOCRList	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	}
	int row=0;
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page])==true
		&& BmpReceiver[page]->IsReceived()==true){
			GridList+=BmpReceiver[page]->OCR;
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
	for(OCRList *L=GridList.GetFirst();L!=NULL;L=L->GetNext() ,row++){
		SetDataToTable(ui->tableWidget ,0,row,L->GlobalPage);
		SetDataToTable(ui->tableWidget ,1,row,QString::number(L->ItemID));
		SetDataToTable(ui->tableWidget ,2,row,L->ItemName);
		QString	s;
		s  =(L->InspectMatching==true)?QString("Ins"):QString("NoIns");
		s +=::GetSeparator();
		s +=(L->SaveIntoResult==true)?QString("Save"):QString("NoSave");
		s +=::GetSeparator();
		s +=(L->OKByFailingRecognition==true)?QString("OK"):QString("NG");
		SetDataToTable(ui->tableWidget ,3,row,s);
	}

	ReEntrant=false;
}

void PropertyOCRForm::on_tableWidget_clicked(const QModelIndex &index)
{
	OCRList *L=GridList.GetItem(index.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->GlobalPage);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"OCRImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->GlobalPage,0,L->ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

void PropertyOCRForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	OCRList *L=GridList.GetItem(index.row());
	if(L==NULL)
		return;
	EditOCRItemDialog	E(GetLayersBase());

	E.AbsLR			=L->AbsLR;
	E.AbsHR			=L->AbsHR;
	E.AbsLG			=L->AbsLG;
	E.AbsHG			=L->AbsHG;
	E.AbsLB			=L->AbsLB;
	E.AbsHB			=L->AbsHB;
	E.EnsmallDot	=L->EnsmallDot;
	E.EnlargeDot	=L->EnlargeDot;
	E.BlockWidth	=L->BlockWidth;
	E.BlockHeight	=L->BlockHeight;
	E.MinSize		=L->MinSize;
	E.Mergin		=L->Mergin;
	E.MaskingColor	=L->MaskingColor;
	E.UseColorLogic	=L->UseColorLogic;
	E.Rotation		=L->Rotation;
		
	E.ItemName					=L->ItemName;
	E.RegNumber					=L->RegNumber;
	E.InspectMatching			=L->InspectMatching;
	E.SaveIntoResult			=L->SaveIntoResult;
	E.OKByFailingRecognition	=L->OKByFailingRecognition;
	E.CorrectList				=L->CorrectList;
	E.ReflectToWindow();
	int	Ret=E.exec();
	if(Ret==1){
		GUICmdReqOCRItem	RCmd(GetLayersBase() ,sRoot,sName ,L->GlobalPage);
		GUICmdAckOCRItem	ACmd(GetLayersBase() ,sRoot,sName ,L->GlobalPage);
		RCmd.ItemID	=L->ItemID;
		if(RCmd.Send(L->GlobalPage,0,ACmd)==true){
			GUICmdAddOCRArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),L->GlobalPage);
			Cmd.AbsLR			=E.AbsLR;
			Cmd.AbsHR			=E.AbsHR;
			Cmd.AbsLG			=E.AbsLG;
			Cmd.AbsHG			=E.AbsHG;
			Cmd.AbsLB			=E.AbsLB;
			Cmd.AbsHB			=E.AbsHB;
			Cmd.EnsmallDot		=E.EnsmallDot;
			Cmd.EnlargeDot		=E.EnlargeDot;
			Cmd.BlockWidth		=E.BlockWidth;
			Cmd.BlockHeight		=E.BlockHeight;
			Cmd.MinSize			=E.MinSize;
			Cmd.Mergin			=E.Mergin;
			Cmd.MaskingColor	=E.MaskingColor;
			Cmd.UseColorLogic	=E.UseColorLogic;
			Cmd.Rotation		=E.Rotation;

			Cmd.Area					=ACmd.Area;
			Cmd.ItemName				=E.ItemName;
			Cmd.RegNumber				=E.RegNumber;
			Cmd.InspectMatching			=E.InspectMatching;
			Cmd.SaveIntoResult			=E.SaveIntoResult;
			Cmd.OKByFailingRecognition	=E.OKByFailingRecognition;
			Cmd.CorrectList				=E.CorrectList;
			Cmd.SendOnly(L->GlobalPage,0);
		}
	}
	else if(Ret==2){
		GUICmdUpdateOCRArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),L->GlobalPage);
		Cmd.AbsLR			=E.AbsLR;
		Cmd.AbsHR			=E.AbsHR;
		Cmd.AbsLG			=E.AbsLG;
		Cmd.AbsHG			=E.AbsHG;
		Cmd.AbsLB			=E.AbsLB;
		Cmd.AbsHB			=E.AbsHB;
		Cmd.EnsmallDot		=E.EnsmallDot;
		Cmd.EnlargeDot		=E.EnlargeDot;
		Cmd.BlockWidth		=E.BlockWidth;
		Cmd.BlockHeight		=E.BlockHeight;
		Cmd.MinSize			=E.MinSize;
		Cmd.Mergin			=E.Mergin;
		Cmd.MaskingColor	=E.MaskingColor;
		Cmd.UseColorLogic	=E.UseColorLogic;
		Cmd.Rotation		=E.Rotation;

		Cmd.ItemID					=L->ItemID;
		Cmd.ItemName				=E.ItemName;
		Cmd.RegNumber				=E.RegNumber;
		Cmd.InspectMatching			=E.InspectMatching;
		Cmd.SaveIntoResult			=E.SaveIntoResult;
		Cmd.OKByFailingRecognition	=E.OKByFailingRecognition;
		Cmd.CorrectList				=E.CorrectList;
		Cmd.SendOnly(L->GlobalPage,0);
	}
	else if(Ret==3){
		GUICmdDeleteOCRArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),L->GlobalPage);
		Cmd.ItemID					=L->ItemID;
		Cmd.SendOnly(L->GlobalPage,0);
	}

	ShowGrid();
}

void PropertyOCRForm::on_pushButtonTest_clicked()
{
	int	R=ui->tableWidget->currentRow();
	if(R<0)
		return;
	OCRList *L=GridList.GetItem(R);
	if(L==NULL)
		return;
	GUICmdReqOCRTest	RCmd(GetLayersBase() ,sRoot,sName ,L->GlobalPage);
	GUICmdAckOCRTest	ACmd(GetLayersBase() ,sRoot,sName ,L->GlobalPage);
	RCmd.ItemID		=L->ItemID;
	RCmd.Mastered	=false;
	if(RCmd.Send(L->GlobalPage,0,ACmd)==true){
		ui->lineEditResult		->setText(ACmd.Result);
		ui->labelResultMatch	->setText((ACmd.Matched==true)?/**/"OK":/**/"NG");
	}
}
