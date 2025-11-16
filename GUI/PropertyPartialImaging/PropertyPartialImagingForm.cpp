#include "PropertyPartialImagingFormResource.h"
#include "PropertyPartialImagingForm.h"
#include "ui_PropertyPartialImagingForm.h"
#include "EditItemDialog.h"
#include "XDisplayImagePacket.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyPartialImagingForm::PropertyPartialImagingForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyPartialImagingForm)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth(0,48);
	ui->tableWidget->setColumnWidth(1,48);
	ui->tableWidget->setColumnWidth(2,128);
	ui->tableWidget->setColumnWidth(3,48);
	ui->tableWidget->setColumnWidth(4,64);
}

PropertyPartialImagingForm::~PropertyPartialImagingForm()
{
    delete ui;
}


PartialImagingBase	*PropertyPartialImagingForm::GetPartialImagingBase(void)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PartialImaging");
	return (PartialImagingBase *)PBase;
}

void	PropertyPartialImagingForm::ShowLibList(void)
{
	PInfoContainer.RemoveAll();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqPartialImagingInfoList		CmdReq (GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendPartialImagingInfoList	CmdSend(GetLayersBase(),sRoot,sName,GlobalPage);
		if(CmdReq.Send(GlobalPage,0,CmdSend)==true){
			PInfoContainer+=CmdSend.PInfoContainer;
		}
	}

	int	N=PInfoContainer.GetNumber();
	ui->tableWidget->setRowCount(N);

	PartialImagingBase	*BBase=GetPartialImagingBase();
	int	row=0;
	for(PartialImagingInfo *a=PInfoContainer.GetFirst();a!=NULL;a=a->GetNext(),row++){
		::SetDataToTable(ui->tableWidget ,0 ,row ,QString::number(a->GlobalPage));
		::SetDataToTable(ui->tableWidget ,1 ,row ,QString::number(a->ItemID));
		::SetDataToTable(ui->tableWidget ,2 ,row ,a->ItemName);
		::SetDataToTable(ui->tableWidget ,3 ,row ,QString::number(a->Priority));
		if(a->SaveTargetImage==true)
			if(a->SaveOnlyInNG==true)
				::SetDataToTable(ui->tableWidget ,4 ,row ,LangSolver.GetString(PropertyPartialImagingForm_LS,LID_0)/*"SV-NG"*/);
			else
				::SetDataToTable(ui->tableWidget ,4 ,row ,LangSolver.GetString(PropertyPartialImagingForm_LS,LID_1)/*"SV-All"*/);
		else
			::SetDataToTable(ui->tableWidget ,4 ,row ,LangSolver.GetString(PropertyPartialImagingForm_LS,LID_2)/*"No-SV"*/);
	}
}

void	PropertyPartialImagingForm::BuildForShow(void)
{
	ShowLibList();
}

void	PropertyPartialImagingForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaManualInPanel	*CmdAddAreaManualInPanelVar=dynamic_cast<CmdAddAreaManualInPanel *>(packet);
	if(CmdAddAreaManualInPanelVar!=NULL){
		EditItemDialog	D(GetLayersBase(),false,NULL);
		int	ret=D.exec();
		if(ret==1){
			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual PartialImaging");
			PartialImagingBase	*BBase=GetPartialImagingBase();
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(CmdAddAreaManualInPanelVar->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=CmdAddAreaManualInPanelVar->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdAddAreaManual	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
					Cmd.Area=A;
					Cmd.Priority	=D.Priority;
					Cmd.SaveTargetImage	=D.SaveTargetImage;
					Cmd.SaveOnlyInNG	=D.SaveOnlyInNG;
					Cmd.BufferType		=D.BufferType;
					Cmd.ItemName		=D.ItemName;
					Cmd.SendOnly(GlobalPage,0);
				}
			}
			ShowLibList();
		}
	}
}


bool	PropertyPartialImagingForm::SaveContent(QIODevice *f)
{
	return true;
}

bool	PropertyPartialImagingForm::LoadContent(QIODevice *f)
{
	return true;
}

void PropertyPartialImagingForm::on_tableWidget_clicked(const QModelIndex &index)
{
	int	R=ui->tableWidget->currentRow();
	if(R<0)
		return;
	PartialImagingInfo	*RIndex=PInfoContainer[R];

	if(RIndex!=NULL){
		DataInPage	*P=GetLayersBase()->GetPageData(RIndex->GlobalPage);
		if(P!=NULL){
			CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,RIndex->x1+P->GetOutlineOffset()->x,RIndex->y1+P->GetOutlineOffset()->y
									,RIndex->x2+P->GetOutlineOffset()->x,RIndex->y2+P->GetOutlineOffset()->y);
			GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"PartialImagingImagePanel" ,/**/"");
			if(GProp!=NULL)
				GProp->TransmitDirectly(&Cmd);
			CmdDrawImageActivate	ACmd(GetLayersBase(),RIndex->GlobalPage,0,RIndex->ItemID);
			if(GProp!=NULL)
				GProp->TransmitDirectly(&ACmd);
		}
	}
}

void PropertyPartialImagingForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	R=ui->tableWidget->currentRow();
	if(R<0)
		return;
	PartialImagingInfo	*RIndex=PInfoContainer[R];

	if(RIndex!=NULL){
		EditItemDialog	D(GetLayersBase(),true,NULL);
		D.Priority			=RIndex->Priority;
		D.SaveTargetImage	=RIndex->SaveTargetImage;
		D.SaveOnlyInNG		=RIndex->SaveOnlyInNG;
		D.BufferType		=RIndex->BufferType;
		D.ItemName			=RIndex->ItemName;
		D.Initial();
		int	ret=D.exec();
		if(ret==2){
			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Edit manual PartialImaging");
			PartialImagingBase	*BBase=GetPartialImagingBase();

			DataInPage	*pdata=GetLayersBase()->GetPageData(RIndex->GlobalPage);

			GUICmdEditAreaManual	Cmd(GetLayersBase(),sRoot,sName,RIndex->GlobalPage);
			Cmd.ItemID			=RIndex->ItemID;
			Cmd.Priority		=D.Priority;
			Cmd.SaveTargetImage	=D.SaveTargetImage;
			Cmd.SaveOnlyInNG	=D.SaveOnlyInNG;
			Cmd.BufferType		=D.BufferType;
			Cmd.ItemName		=D.ItemName;
			Cmd.SendOnly(RIndex->GlobalPage,0);
		}
		else if(ret==3){
			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"delete manual PartialImaging");
			PartialImagingBase	*BBase=GetPartialImagingBase();

			DataInPage	*pdata=GetLayersBase()->GetPageData(RIndex->GlobalPage);

			GUICmdDeleteAreaManual	Cmd(GetLayersBase(),sRoot,sName,RIndex->GlobalPage);
			Cmd.ItemID			=RIndex->ItemID;
			Cmd.SendOnly(RIndex->GlobalPage,0);
		}	
		ShowLibList();
	}		
}
