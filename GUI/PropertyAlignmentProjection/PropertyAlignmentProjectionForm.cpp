#include "PropertyAlignmentProjectionForm.h"
#include "ui_PropertyAlignmentProjectionForm.h"
#include "XGeneralFunc.h"
#include "XPacketAlignmentProjection.h"
#include "AddItemDialog.h"
#include "ImageControlTools.h"
#include "XDisplayImagePacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyAlignmentProjectionForm::PropertyAlignmentProjectionForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyAlignmentProjectionForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	ui->tableWidgetPoint->setColumnWidth (0,40);
	ui->tableWidgetPoint->setColumnWidth (1,40);
	ui->tableWidgetPoint->setColumnWidth (2,40);
	ui->tableWidgetPoint->setColumnWidth (3,90);
	ui->tableWidgetPoint->setColumnWidth (4,40);
	InstallIgnoreKeyForChild();
}

PropertyAlignmentProjectionForm::~PropertyAlignmentProjectionForm()
{
    delete ui;
}

AlignmentProjectionBase	*PropertyAlignmentProjectionForm::GetAlignmentProjectionBase(void)
{
	AlignmentProjectionBase *BBase=(AlignmentProjectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentProjection");
	return BBase;
}
void	PropertyAlignmentProjectionForm::BuildForShow(void)
{
	ShowPointList();
}

void	PropertyAlignmentProjectionForm::ShowInEdit	(void)
{
	ShowPointList();
}

void	PropertyAlignmentProjectionForm::StartPage(void)
{
	ShowPointList();
}

void PropertyAlignmentProjectionForm::ShowPointList(void)
{
	PointList.RemoveAll();
	for(int Page=0;Page<GetPageNumb();Page++){
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			int	GlobalPage=Page;
			GUICmdReqAlignmentProjectionPointListPack	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdSendAlignmentProjectionPointListPack	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);

			RCmd.Phase	=Phase;
			if(RCmd.Send(GlobalPage,0,SCmd)==true){
				PointList.AddMove(SCmd.List);
			}
		}
	}

	ui->tableWidgetPoint->setRowCount(PointList.GetNumber());
	int	Row=0;
	for(AlignmentProjectionPointList *a=PointList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		SetDataToTable(ui->tableWidgetPoint ,0 ,Row ,QString::number(a->Phase));
		SetDataToTable(ui->tableWidgetPoint ,1 ,Row ,QString::number(a->Page));
		SetDataToTable(ui->tableWidgetPoint ,2 ,Row ,QString::number(a->ItemID));
		SetDataToTable(ui->tableWidgetPoint ,3 ,Row ,QString::number(a->Cx)+QString(",")+QString::number(a->Cy));
		SetDataToTable(ui->tableWidgetPoint ,4 ,Row ,QString::number(a->PeakCount));
	}
}

void	PropertyAlignmentProjectionForm::TransmitDirectly(GUIDirectMessage *packet)
{
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdAlignmentProjectionDrawEnd	*Da=dynamic_cast<GUICmdAlignmentProjectionDrawEnd *>(packet);
	if(Da!=NULL){
		AddItemDialog	D(GetLayersBase(),NULL);
		if(D.exec()==(int)true){
			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create AlignmentProjection point");

			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(Da->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=Da->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdReqAlignmentProjectionPutPoint	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
					Cmd.Area=A;
					Cmd.ItemName	=D.ItemName;
					Cmd.PeakCount	=D.PeakCount;
					Cmd.Angle		=D.Angle;
					Cmd.UsageLayer	=D.UsageLayer;
					Cmd.AbandonRateL=D.AbandonRateL;
					Cmd.AbandonRateH=D.AbandonRateH;
					Cmd.Send(NULL,GlobalPage,0);
				}
			}
			ShowPointList();
		}
		return;
	}
	GUICmdReqAlignmentProjectionDrawMode	*DMode=dynamic_cast<GUICmdReqAlignmentProjectionDrawMode *>(packet);
	if(DMode!=NULL){
		return;
	}
}

void	PropertyAlignmentProjectionForm::CreateAlignmentPoint(FlexArea &area ,int GlobalPage ,int PeakCount ,double Angle, int UsageLayer)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create AlignmentProjection point");

	int	LocalPage	=GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);

	GUICmdReqAlignmentProjectionPutPoint	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
	Cmd.Area=area;
	Cmd.PeakCount	=PeakCount;
	Cmd.Angle		=Angle;
	Cmd.UsageLayer	=UsageLayer;
	Cmd.AbandonRateL=0.1;
	Cmd.AbandonRateH=0.2;
	Cmd.SendOnly(GlobalPage,0);
	
	ShowPointList();
}
void PropertyAlignmentProjectionForm::on_tableWidgetPoint_doubleClicked(const QModelIndex &Index)
{
	int	R=Index.row();
	AlignmentProjectionPointList *a=PointList.GetItem(R);
	if(a==NULL)
		return;

	int	GlobalPage=a->Page;
	GUICmdReqAlignmentProjectionPoint	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	GUICmdSendAlignmentProjectionPoint	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);

	RCmd.Phase	=a->Phase;
	RCmd.ItemID	=a->ItemID;
	if(RCmd.Send(GlobalPage,0,SCmd)==true){

		AddItemDialog	D(GetLayersBase(),NULL);
		D.SetInitial(SCmd.ItemName,SCmd.PeakCount,SCmd.Angle,SCmd.PeakIsolation
					,SCmd.UsageLayer
					,SCmd.AbandonRateL,SCmd.AbandonRateH);
		if(D.exec()==(int)true){
			GUICmdReqAlignmentProjectionModifyPoint	DModMsg(GetLayersBase(),sRoot,sName,GlobalPage);
			DModMsg.ItemName	=D.ItemName;
			DModMsg.PeakCount	=D.PeakCount;
			DModMsg.Angle		=D.Angle;
			DModMsg.UsageLayer	=D.UsageLayer;
			DModMsg.ItemID		=a->ItemID;
			DModMsg.AbandonRateL=D.AbandonRateL;
			DModMsg.AbandonRateH=D.AbandonRateH;
			DModMsg.Send(NULL,GlobalPage ,0);					
		}
		ShowPointList();
	}
}


void PropertyAlignmentProjectionForm::on_tableWidgetPoint_clicked(const QModelIndex &MIndex)
{
	AlignmentProjectionPointList *L=PointList.GetItem(MIndex.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->Cx-L->XSize/2+P->GetOutlineOffset()->x,L->Cy-L->YSize/2+P->GetOutlineOffset()->y
									,L->Cx+L->XSize/2+P->GetOutlineOffset()->x,L->Cy+L->YSize/2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AlignmentProjectionImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->Page,0,L->ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}
