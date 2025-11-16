#include "PropertyRepeatControlForm.h"
#include "ui_PropertyRepeatControlForm.h"
#include "XGeneralFunc.h"
#include "XPropertyRepeatControlPacket.h"
//#include "XPropertyRepeatControlCommon.h"
#include "XRepeatControl.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"
#include "XStandardCommand.h"
#include "EditItemDialog.h"
#include "XDisplayImagePacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyRepeatControlForm::PropertyRepeatControlForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyRepeatControlForm)
{
    ui->setupUi(this);

	::SetColumnWidthInTable(ui->tableWidgetList ,0, 33);
	::SetColumnWidthInTable(ui->tableWidgetList ,1, 33);
	::SetColumnWidthInTable(ui->tableWidgetList ,2, 33);

}

PropertyRepeatControlForm::~PropertyRepeatControlForm()
{
    delete ui;
}
RepeatControlBase	*PropertyRepeatControlForm::GetRepeatControlBase(void)
{
	return (RepeatControlBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RepeatControl");
}

void	PropertyRepeatControlForm::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdRepeatControlDrawEnd	*GUICmdRepeatControlDrawEndVar=dynamic_cast<GUICmdRepeatControlDrawEnd *>(packet);
	if(GUICmdRepeatControlDrawEndVar!=NULL){
		EditItemDialog	D(GetLayersBase());
		if(D.exec()==(int)true){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(GUICmdRepeatControlDrawEndVar->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=GUICmdRepeatControlDrawEndVar->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdSendAddManualRepeatControl	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
					Cmd.Area=A;
					Cmd.RepeatCount		=D.RepeatCount		;
					Cmd.MeshSize		=D.MeshSize			;
					Cmd.SequenceOffset	=D.SequenceOffset	;
					Cmd.GatherAllPhase	=D.GatherAllPhase	;
					Cmd.Send(NULL,GlobalPage,0);
				}
			}
			ShowList();
		}
		return;
	}
	CmdRepeatControlDrawAttr	*CmdRepeatControlDrawAttrVar=dynamic_cast<CmdRepeatControlDrawAttr *>(packet);
	if(CmdRepeatControlDrawAttrVar!=NULL){
		RepeatControlBase	*ABase=GetRepeatControlBase();
		CmdRepeatControlDrawAttrVar->BlockColor0	=ABase->Color0;
		CmdRepeatControlDrawAttrVar->BlockColor1	=ABase->Color1;
		CmdRepeatControlDrawAttrVar->BlockColor2	=ABase->Color2;
		CmdRepeatControlDrawAttrVar->BlockColor3	=ABase->Color3;
		CmdRepeatControlDrawAttrVar->BlockColor4	=ABase->Color4;
		CmdRepeatControlDrawAttrVar->BlockColor5	=ABase->Color5;
		CmdRepeatControlDrawAttrVar->BlockColor6	=ABase->Color6;
		CmdRepeatControlDrawAttrVar->BlockColor7	=ABase->Color7;
		CmdRepeatControlDrawAttrVar->ShowingItemID	=0;
		return;
	}
}

void	PropertyRepeatControlForm::StartPage(void)
{
	ShowList();
}
void	PropertyRepeatControlForm::BuildForShow(void)
{
	RepeatControlBase	*BBase=GetRepeatControlBase();
	ui->spinBoxWholeRepeatCount->setValue(BBase->DefaultRepeatCount);
	ShowList();
}

void PropertyRepeatControlForm::ShowList(void)
{
	RepeatControlBase	*BBase=GetRepeatControlBase();
	if(BBase==NULL)
		return;
	ItemList.RemoveAll();

	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqRepeatControlInfoList	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdAckRepeatControlInfoList	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.Phase=phase;
			if(RCmd.Send(GlobalPage,0,SCmd)==true){
				ItemList+=SCmd.RepeatControlInfos;
			}
		}
	}

	ui->tableWidgetList->setRowCount(ItemList.GetCount());
	int	Row=0;
	for(RepeatControlInfoList *L=ItemList.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetList, 0, Row, QString::number(L->RepeatCount));
		::SetDataToTable(ui->tableWidgetList, 1, Row, QString::number(L->MeshSize));
		::SetDataToTable(ui->tableWidgetList, 2, Row, QString::number(L->SequenceOffset));
	}
}

void PropertyRepeatControlForm::on_tableWidgetList_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetList->currentRow();
	if(Row>=0){
		RepeatControlInfoList *L=ItemList[Row];
		if(L!=NULL){
			DataInPage	*P=GetLayersBase()->GetPageData(L->Index.Data.Page);
			if(P!=NULL){
				GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"RepeatControlImagePanel" ,/**/"");
				if(GProp!=NULL){
					CmdDrawImageRectPacket	Cmd( GetLayersBase()
												,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
												,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
					GProp->TransmitDirectly(&Cmd);
				}
				CmdDrawImageActivate	ACmd(GetLayersBase(),L->Index.Data.Page,L->Index.Data.Layer,L->Index.Data.ItemID);
				if(GProp!=NULL){
					GProp->TransmitDirectly(&ACmd);
				}
			}
		}
	}
}


void PropertyRepeatControlForm::on_tableWidgetList_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetList->currentRow();
	if(Row>=0){
		RepeatControlInfoList *L=ItemList[Row];
		if(L!=NULL){
			EditItemDialog	D(GetLayersBase());
			D.RepeatCount	    =L->RepeatCount	    ;
			D.MeshSize	    	=L->MeshSize	    ;
			D.SequenceOffset	=L->SequenceOffset	;
			D.GatherAllPhase  	=L->GatherAllPhase  ;
			D.Initial();
			if(D.exec()==(int)true){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(L->Index.Data.Page);
				GUICmdSendModifyRepeatControl	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
				Cmd.Index=L->Index;
				Cmd.RepeatCount		=D.RepeatCount		;
				Cmd.MeshSize		=D.MeshSize			;
				Cmd.SequenceOffset	=D.SequenceOffset	;
				Cmd.GatherAllPhase	=D.GatherAllPhase	;
				Cmd.Send(NULL,GlobalPage,0);
			}
			ShowList();
		}
	}
}

void PropertyRepeatControlForm::on_pushButtonCreateWhole_clicked()
{
	int	RepeatCount=ui->spinBoxWholeRepeatCount->value();

	CreateWhole(RepeatCount);
}

void    PropertyRepeatControlForm::CreateWhole(int RepeatCount)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdCreateWholeRepeatControl	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.RepeatCount=RepeatCount;
			RCmd.Send(NULL,GlobalPage,0);
		}
	}
	ShowList();
}


