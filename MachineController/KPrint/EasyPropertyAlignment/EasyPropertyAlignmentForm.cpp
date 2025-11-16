#include "EasyPropertyAlignmentResource.h"
#include "EasyPropertyAlignmentForm.h"
#include "ui_EasyPropertyAlignmentForm.h"
#include "PropertyAlignmentFlexAreaPacket.h"
#include "CartonMenuForm.h"
#include "XParamCustomized.h"
#include "XDotColorMatchingLibrary.h"
#include "EditSearchDotDialog.h"
#include "XIntegrationSimpleImagePanel.h"
#include "SelectActionLibraryDialog.h"
#include "SelectAlignmentAreaForm.h"
#include "XAlgorithmLibrary.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

EasyPropertyAlignmentForm::EasyPropertyAlignmentForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::EasyPropertyAlignmentForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	SlaveNo						=0;
	SelectAlignmentAreaFormInst	=NULL;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	ui->toolButtonAreaMode->setChecked(false);
}

EasyPropertyAlignmentForm::~EasyPropertyAlignmentForm()
{
    delete ui;
	if(SelectAlignmentAreaFormInst!=NULL){
		SelectAlignmentAreaFormInst->deleteLater();
		SelectAlignmentAreaFormInst=NULL;
	}
}
void	EasyPropertyAlignmentForm::ReadyParam(void)
{
	on_toolButtonAreaMode_clicked();

	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		if(GProp->Param.GeneratePartialAlignment==false){
			ui->toolButtonAreaPriority->setChecked(true);
			on_toolButtonAreaPriority_clicked();
		}
	}
	GUIFormBase *PanelGUI[100];
	int N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint" ,/**/"EasyAlignmentImagePanel" ,PanelGUI ,sizeof(PanelGUI)/sizeof(PanelGUI[0]));
	for(int i=0;i<N;i++){
		IntegrationSimpleImagePanel	*Panel=dynamic_cast<IntegrationSimpleImagePanel *>(PanelGUI[i]);
		if(Panel!=NULL && Panel->GetSlaveNo()==SlaveNo){
			connect(Panel,SIGNAL(SignalChangedItems()),this,SLOT(SlotChangedItems()));
		}
	}
}
void	EasyPropertyAlignmentForm::ResizeAction()
{
	::SetColumnWidthInTable(ui->tableWidgetMarkList,0, 50);
	::SetColumnWidthInTable(ui->tableWidgetMarkList,1, 50);

	::SetColumnWidthInTable(ui->tableWidgetLimitedLib,0, 20);
	::SetColumnWidthInTable(ui->tableWidgetLimitedLib,1, 80);
}
void	EasyPropertyAlignmentForm::StartInitial(void)
{
	AreaIDList	.RemoveAll();
	Marks		.RemoveAll();
}
void	EasyPropertyAlignmentForm::BuildForShow(void)
{
	ShowPointList();
	on_toolButtonAreaPriority_clicked();
}
void	EasyPropertyAlignmentForm::StartPage	(void)
{
	ShowPointList();
	on_toolButtonAreaPriority_clicked();
}
void	EasyPropertyAlignmentForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAlignmentFlexAreaDrawModePacket	*CmdAlignmentFlexAreaDrawModePacketVar=dynamic_cast<CmdAlignmentFlexAreaDrawModePacket *>(packet);
	if(CmdAlignmentFlexAreaDrawModePacketVar!=NULL){
		CmdAlignmentFlexAreaDrawModePacketVar->DrawGeneratedArea=true;
		CmdAlignmentFlexAreaDrawModePacketVar->DrawOutlineArea	=true;
		CmdAlignmentFlexAreaDrawModePacketVar->DrawWholeMatch	=false;
		CmdAlignmentFlexAreaDrawModePacketVar->DrawBaseMatch	=false;
		CmdAlignmentFlexAreaDrawModePacketVar->SelectedArea.Add(0);		//Use for item view
		//CmdAlignmentFlexAreaDrawModePacketVar->SelectWholeMatch;
		//CmdAlignmentFlexAreaDrawModePacketVar->CurrentBaseMatchRow;

		return;
	}
	CmdEasyAlignmentDrawModePacket	*CmdEasyAlignmentDrawModePacketVar=dynamic_cast<CmdEasyAlignmentDrawModePacket *>(packet);
	if(CmdEasyAlignmentDrawModePacketVar!=NULL){
		CmdEasyAlignmentDrawModePacketVar->AreaIDList=AreaIDList;
		if(ui->toolButtonAreaPriority->isChecked()==false){
			CmdEasyAlignmentDrawModePacketVar->AreaPriority.Add(XAlignmentLargeArea::_PriorityGlobal);
		}
		else{
			CmdEasyAlignmentDrawModePacketVar->AreaPriority.Add(XAlignmentLargeArea::_PriorityMiddle);
			CmdEasyAlignmentDrawModePacketVar->AreaPriority.Add(XAlignmentLargeArea::_PriorityLow);
		}
		return;
	}
	IntegrationGenerateAutomatically	*IntegrationGenerateAutomaticallyVar=dynamic_cast<IntegrationGenerateAutomatically *>(packet);
	if(IntegrationGenerateAutomaticallyVar!=NULL){
		GenerateAutomatically();
		GetLayersBase()->GetIntegrationBasePointer()->ExecuteInitialAfterEdit(SlaveNo);
		on_toolButtonAreaPriority_clicked();
		return;
	}
	CmdReqAreaMode	*CmdReqAreaModeVar=dynamic_cast<CmdReqAreaMode *>(packet);
	if(CmdReqAreaModeVar!=NULL){
		CmdReqAreaModeVar->AreaMode		=ui->toolButtonAreaMode->isChecked();
		ReqAreaID();
		CmdReqAreaModeVar->AreaIDList	=AreaIDList;
		if(ui->toolButtonAreaPriority->isChecked()==false){
			CmdReqAreaModeVar->AreaPriority.Add(XAlignmentLargeArea::_PriorityGlobal);
		}
		else{
			CmdReqAreaModeVar->AreaPriority.Add(XAlignmentLargeArea::_PriorityMiddle);
			CmdReqAreaModeVar->AreaPriority.Add(XAlignmentLargeArea::_PriorityLow);
		}
		CmdReqAreaModeVar->CharacterMode	=false;
		return;
	}
	IntegrationGenerateAlignmentMark	*IntegrationGenerateAlignmentMarkVar=dynamic_cast<IntegrationGenerateAlignmentMark *>(packet);
	if(IntegrationGenerateAlignmentMarkVar!=NULL){
		IntegrationAutoGenerateMark	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.AreaIDList	=AreaIDList;
		RCmd.Send(NULL,SlaveNo,0);
		return;
	}
}

void EasyPropertyAlignmentForm::on_toolButtonAutoGenerate_clicked()
{
	GenerateAutomatically();
	GetLayersBase()->GetIntegrationBasePointer()->ExecuteInitialAfterEdit(SlaveNo);

	emit	SignalBusy();

	bool	NowOnIdle;
	do{
		NowOnIdle=true;
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			int	SNo=m->GetIntegrationSlaveNo();
			if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SNo)==false){
				NowOnIdle=false;
			}
		}
	}while(NowOnIdle==false);

	emit	SignalIdle();

	BroadcastRepaintAll();
}

void	EasyPropertyAlignmentForm::GenerateAutomatically(void)
{
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		IntegrationCmdGenerateAreaAndItem	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		//if(GProp->Param.AlignmentLib1>0)
		//	RCmd.ItemLibIDs.Add(GProp->Param.AlignmentLib1);
		//if(GProp->Param.AlignmentLib2>0)
		//	RCmd.ItemLibIDs.Add(GProp->Param.AlignmentLib2);
		//if(GProp->Param.AlignmentLib3>0)
		//	RCmd.ItemLibIDs.Add(GProp->Param.AlignmentLib3);
		//if(GProp->Param.AlignmentLib4>0)
		//	RCmd.ItemLibIDs.Add(GProp->Param.AlignmentLib4);
		//if(GProp->Param.AlignmentLib5>0)
		//	RCmd.ItemLibIDs.Add(GProp->Param.AlignmentLib5);
		//if(GProp->Param.AlignmentLib6>0)
		//	RCmd.ItemLibIDs.Add(GProp->Param.AlignmentLib6);
		//if(GProp->Param.AlignmentLib7>0)
		//	RCmd.ItemLibIDs.Add(GProp->Param.AlignmentLib7);
		//if(GProp->Param.AlignmentLib8>0)
		//	RCmd.ItemLibIDs.Add(GProp->Param.AlignmentLib8);
		if(SlaveNo==0){
			if(GProp->ParamInMaster.Slave0LibID.GetCount()!=0){
				RCmd.ItemLibIDs.Merge(GProp->ParamInMaster.Slave0LibID);
			}
			else{
				RCmd.ItemLibIDs.Add(GProp->Param.DotColorMatchLibPattern1);
				RCmd.ItemLibIDs.Add(GProp->Param.DotColorMatchLibFlat1);
			}
		}
		if(SlaveNo==1){
			if(GProp->ParamInMaster.Slave1LibID.GetCount()!=0){
				RCmd.ItemLibIDs.Merge(GProp->ParamInMaster.Slave1LibID);
			}
			else{
				RCmd.ItemLibIDs.Add(GProp->Param.DotColorMatchLibPattern1);
				RCmd.ItemLibIDs.Add(GProp->Param.DotColorMatchLibFlat1);
			}
		}
		if(SlaveNo==2){
			if(GProp->ParamInMaster.Slave2LibID.GetCount()!=0){
				RCmd.ItemLibIDs.Merge(GProp->ParamInMaster.Slave2LibID);
			}
			else{
				RCmd.ItemLibIDs.Add(GProp->Param.DotColorMatchLibPattern1);
				RCmd.ItemLibIDs.Add(GProp->Param.DotColorMatchLibFlat1);
			}
		}
		RCmd.GeneratePartialAlignment	=GProp->Param.GeneratePartialAlignment;
		RCmd.AlignmntAreaErosion		=GProp->Param.AlignmntAreaErosion;
		RCmd.AlignmntPointSize			=GProp->Param.AlignmntPointSize;
		RCmd.AlignmntSearchAreaDot		=GProp->Param.AlignmntSearchAreaDot;
		RCmd.AlignmntSearchAreaDot2		=GProp->Param.AlignmntSearchAreaDot2;
		RCmd.AlignmntSearchAreaDotMiddle=GProp->Param.AlignmntSearchAreaDotMiddle;
		if(GProp->Param.AlignmntSearchAreaDotY!=0)
			RCmd.AlignmntSearchAreaDotY		=GProp->Param.AlignmntSearchAreaDotY;
		else
			RCmd.AlignmntSearchAreaDotY		=GProp->Param.AlignmntSearchAreaDot;

		if(GProp->Param.AlignmntSearchAreaDotY!=0)
			RCmd.AlignmntSearchAreaDot2Y	=GProp->Param.AlignmntSearchAreaDot2Y;
		else
			RCmd.AlignmntSearchAreaDot2Y	=GProp->Param.AlignmntSearchAreaDot2;

		if(GProp->Param.AlignmntSearchAreaDotMiddleY!=0)
			RCmd.AlignmntSearchAreaDotMiddleY=GProp->Param.AlignmntSearchAreaDotMiddleY;
		else
			RCmd.AlignmntSearchAreaDotMiddleY=GProp->Param.AlignmntSearchAreaDotMiddle;
		RCmd.AlignmntGeneratedLayer		=GProp->Param.AlignmntGeneratedLayer;
		RCmd.AlignmntJudgeWithBrDif		=GProp->Param.AlignmntJudgeWithBrDif;

		RCmd.Send(NULL,SlaveNo,0);
	}
}
void EasyPropertyAlignmentForm::on_toolButtonAreaMode_clicked()
{
	if(ui->toolButtonAreaMode->isChecked()==false){
		ui->toolButtonAreaMode->setText(LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_1)/*"郢晄ｧｭｽ郢ｧｯ"*/);
	}
	else{
		ui->toolButtonAreaMode->setText(LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_2)/*"鬯ｼ懈ｲｺ"*/);
	}

	//ReqAreaID();
	
	IntegrationCmdSetAreaMode	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.AreaMode	=ui->toolButtonAreaMode->isChecked();
	if(ui->toolButtonAreaPriority->isChecked()==false){
		RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityGlobal);
	}
	else{
		RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityMiddle);
		RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityLow);
	}
	RCmd.Send(NULL,SlaveNo,0);

	ShowPointList();
	ShowLimitedLib();

	BroadcastRepaintAll();
}

void	EasyPropertyAlignmentForm::ReqAreaID(void)
{
	AreaIDList.RemoveAll();
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationCmdReqAlignmentAreaID	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationCmdAckAlignmentAreaID	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.Phase=m->GetCurrentPhase();
			if(ui->toolButtonAreaPriority->isChecked()==false){
				RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityGlobal);
			}
			else{
				RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityMiddle);
				RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityLow);
			}
			if(RCmd.Send(SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){
				AreaIDList+=ACmd.AreaID;
			}
		}
	}
}

void EasyPropertyAlignmentForm::on_toolButtonDeleteAll_clicked()
{
	IntegrationCmdClearAll	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.AreaMode	=ui->toolButtonAreaMode->isChecked();
	if(ui->toolButtonAreaPriority->isChecked()==false){
		RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityGlobal);
	}
	else{
		RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityMiddle);
		RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityLow);
	}
	RCmd.Send(NULL,SlaveNo,0);

	ShowPointList();
	BroadcastRepaintAll();
}

IntList	EasyPropertyAlignmentForm::GetCurrentAreaPriority(void)
{
	bool	AreaMode	=ui->toolButtonAreaPriority->isChecked();
	IntList	A;
	if(AreaMode==false){		
		A.Add(XAlignmentLargeArea::_PriorityGlobal);
		return A;
	}
	else{
		A.Add(XAlignmentLargeArea::_PriorityMiddle);
		A.Add(XAlignmentLargeArea::_PriorityLow);
		return A;
	}
}
void	EasyPropertyAlignmentForm::ShowByAreaID(int _AreaID)
{
	ReqAreaID();
	ListPhasePageLayerItemPack		TmpAreaIDList;
	for(ListPhasePageLayerItem *a=AreaIDList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Data.ItemID==_AreaID
		&& a->Data.Layer==0){
			TmpAreaIDList.Merge(*a);
		}
	}
	AreaIDList=TmpAreaIDList;
	ShowAreaName();
	BroadcastRepaintAll();
}



void	EasyPropertyAlignmentForm::SetByAreaID(int _AreaID)
{
	ReqAreaID();
	ListPhasePageLayerItemPack		TmpAreaIDList;
	for(ListPhasePageLayerItem *a=AreaIDList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Data.ItemID==_AreaID
		&& a->Data.Layer==0){
			TmpAreaIDList.Merge(*a);
		}
	}
	AreaIDList=TmpAreaIDList;
	ShowLimitedLib();
	ShowPointList();
	ShowAreaName();
	BroadcastRepaintAll();
}

void	EasyPropertyAlignmentForm::ShowAreaName(void)
{
	IntList	AreaPriority=GetCurrentAreaPriority();
	int	AreaID=-1;
	if(AreaIDList.IsEmpty()==false){
		AreaID=AreaIDList.GetFirst()->Data.ItemID;
	}
	if(AreaPriority.IsInclude(XAlignmentLargeArea::_PriorityGlobal)==true){
		ui->labelAreaName->setText(QString(LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_0)/*"陞滄摩ｽ｢ : Area"*/)
								  +QString::number(AreaID));
	}
	else{
		ui->labelAreaName->setText(QString(LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_5)/*"郢昜ｻ｣縺｡郢晢ｽｼ郢晢ｽｳ : Area"*/)
								  +QString::number(AreaID));
	}
}

void EasyPropertyAlignmentForm::on_toolButtonAreaPriority_clicked()
{
	if(ui->toolButtonAreaPriority->isChecked()==false){
		ui->toolButtonAreaPriority->setText(LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_3)/*"陞滄摩ｽ｢"*/);
	}
	else{
		ui->toolButtonAreaPriority->setText(LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_4)/*"郢昜ｻ｣縺｡郢晢ｽｼ郢晢ｽｳ"*/);
	}
	IntegrationCmdSetAreaMode	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.AreaMode	=ui->toolButtonAreaMode->isChecked();
	if(ui->toolButtonAreaPriority->isChecked()==false){
		RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityGlobal);
	}
	else{
		RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityMiddle);
		RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityLow);
	}
	RCmd.Send(NULL,SlaveNo,0);
	ReqAreaID();
	ShowPointList();
	ShowLimitedLib();
	ShowAreaName();
	BroadcastRepaintAll();
}

void	EasyPropertyAlignmentForm::ShowPointList(void)
{
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
		Marks.RemoveAll();
		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationCmdReqAlignmentMark	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationCmdAckAlignmentMark	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.Phase		=m->GetCurrentPhase();
			RCmd.AreaIDList	=AreaIDList;
			if(ui->toolButtonAreaPriority->isChecked()==false){
				RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityGlobal);
			}
			else{
				RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityMiddle);
				RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityLow);
			}
			if(RCmd.Send(SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){
				Marks+=ACmd.Marks;
			}
		}
		ui->tableWidgetMarkList->setRowCount(Marks.GetCount());
		int	Row=0;
		for(AlignmentLargePointList *L=Marks.GetFirst();L!=NULL;L=L->GetNext(),Row++){
			QString	S1	=QString('(')
						+QString::number(L->MoveDotX)+QString(',')+QString::number(L->MoveDotY)
						+QString(LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_8)/*")=("*/)
						+QString::number(m->TransformPixelToUnit(L->MoveDotX))
						+QString(',')
						+QString::number(m->TransformPixelToUnit(L->MoveDotY))
						+QString(LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_9)/*")mm"*/);

			::SetDataToTable(ui->tableWidgetMarkList, 0, Row,S1);

			QString	S2	=QString('(')
						+QString::number(L->MoveDotX2)+QString(',')+QString::number(L->MoveDotY2)
						+QString(LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_10)/*")=("*/)
						+QString::number(m->TransformPixelToUnit(L->MoveDotX2))
						+QString(',')
						+QString::number(m->TransformPixelToUnit(L->MoveDotY2))
						+QString(LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_11)/*")mm"*/);

			::SetDataToTable(ui->tableWidgetMarkList, 1, Row,S2);
		}
	}
}

void EasyPropertyAlignmentForm::on_tableWidgetMarkList_itemSelectionChanged()
{
	int	Row=ui->tableWidgetMarkList->currentRow();
	if(Row<0)
		return;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
		AlignmentLargePointList *L=Marks[Row];
		if(L!=NULL){
			GUIFormBase *PanelGUI[100];
			int N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint" ,/**/"EasyAlignmentImagePanel" ,PanelGUI ,sizeof(PanelGUI)/sizeof(PanelGUI[0]));
			for(int i=0;i<N;i++){
				IntegrationSimpleImagePanel	*Panel=dynamic_cast<IntegrationSimpleImagePanel *>(PanelGUI[i]);
				if(Panel!=NULL && Panel->GetSlaveNo()==SlaveNo){
					XYData	*XY=m->GetOutlineOffset(m->GetCurrentPhase(), L->Page);
					for(int z=1;z<100;z++){
						if(Panel->ZoomRectU( XY->x+L->Cx-L->XSize*z,XY->y+L->Cy-L->YSize*z
											,XY->x+L->Cx+L->XSize*z,XY->y+L->Cy+L->YSize*z)==true){
							break;
						}
					}
				}
			}
		}
	}
}


void EasyPropertyAlignmentForm::on_tableWidgetMarkList_itemDoubleClicked(QTableWidgetItem *item)
{
	int	Row=ui->tableWidgetMarkList->currentRow();
	if(Row<0)
		return;
	AlignmentLargePointList *L=Marks[Row];
	if(L!=NULL){
		EditSearchDotDialog	D(this,GetLayersBase(),L);
		if(D.exec()==true){
			IntegrationCmdSetAlignmentMark	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.Phase	=L->Phase;
			RCmd.Mark	=D.Data;
			RCmd.Send(NULL,SlaveNo,L->Page);
			ShowPointList();
		}
	}
}
void	EasyPropertyAlignmentForm::SlotChangedItems()
{
	ShowPointList();
}

void EasyPropertyAlignmentForm::ShowLimitedLib(void)
{
	LimitedLib.RemoveAll();
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationCmdReqAlignmentLimitedLib	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationCmdAckAlignmentLimitedLib	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.AreaID=AreaIDList;
			if(RCmd.Send(SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){
				LimitedLib.Merge(ACmd.LimitedLib);
			}
		}
	}
	ui->tableWidgetLimitedLib->setRowCount(LimitedLib.GetCount());
	int	Row=0;
	for(AlgorithmLibraryList *a=LimitedLib.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetLimitedLib,0, Row, QString::number(a->GetLibID()));
		QString	LibName=GetLayersBase()->GetLibraryName(a->GetLibType(),a->GetLibID());
		::SetDataToTable(ui->tableWidgetLimitedLib,1, Row, LibName);
	}
	//ui->toolButtonPriority->setText();
}

void EasyPropertyAlignmentForm::on_toolButtonPriority_clicked()
{
	if(SelectAlignmentAreaFormInst==NULL){
		SelectAlignmentAreaFormInst=new SelectAlignmentAreaForm(GetLayersBase(),this);
		SelectAlignmentAreaFormInst->Initial();
		SelectAlignmentAreaFormInst->show();
	}
	else{
		SelectAlignmentAreaFormInst->Initial();
		SelectAlignmentAreaFormInst->show();
	}
}

void EasyPropertyAlignmentForm::on_tableWidgetLimitedLib_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetLimitedLib->currentRow();
	SelectActionLibraryDialog	D(GetLayersBase(),this,true);
	int	Ret=D.exec();
	if(Ret==1){
		EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(m!=NULL){
			for(int page=0;page<m->GetPageNumb();page++){
				IntegrationCmdAddAlignmentLimitedLib	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				RCmd.AreaID=AreaIDList;
				RCmd.LimitedLib=D.Selected;
				RCmd.Send(NULL,SlaveNo,m->GetLocalPageFromGlobal(page));
			}
		}
		ShowLimitedLib();
	}
	else if(Ret==2){
		AlgorithmLibraryList	*c=LimitedLib[Row];
		if(c!=NULL){
			EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
			if(m!=NULL){
				for(int page=0;page<m->GetPageNumb();page++){
					IntegrationCmdDelAlignmentLimitedLib	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
					RCmd.AreaID=AreaIDList;
					RCmd.LimitedLib=*c;
					RCmd.Send(NULL,SlaveNo,m->GetLocalPageFromGlobal(page));
				}
			}
			ShowLimitedLib();
		}
	}
}

void EasyPropertyAlignmentForm::on_pushButtonAddLimitedLib_clicked()
{
	SelectActionLibraryDialog	D(GetLayersBase(),this,false);
	int	Ret=D.exec();
	if(Ret==1){
		EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(m!=NULL){
			for(int page=0;page<m->GetPageNumb();page++){
				IntegrationCmdAddAlignmentLimitedLib	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				RCmd.AreaID=AreaIDList;
				RCmd.LimitedLib=D.Selected;
				RCmd.Send(NULL,SlaveNo,m->GetLocalPageFromGlobal(page));
			}
		}
		ShowLimitedLib();
	}
}


void EasyPropertyAlignmentForm::on_toolButtonAreaFromMask_clicked()
{
	if(QMessageBox::question(NULL,LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_6)/*"遒ｺ隱*/
						,LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_7)/*"驕ｸ謚槭＠縺滄伜沺遞ｮ鬘槭〒縲∵里蟄倥鬆伜沺縺ｨ繝槭繧ｯ縺御ｸ譌ｦ蜑企勁縺輔ｌ縺ｾ縺*/
						,QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(m!=NULL){
			IntegrationCmdReqMakeAreaFromMask	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			if(ui->toolButtonAreaPriority->isChecked()==false){
				RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityGlobal);
			}
			else{
				RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityMiddle);
				RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityLow);
			}
			RCmd.Send(NULL,SlaveNo,0);
		}
		BroadcastRepaintAll();
	}
}


void EasyPropertyAlignmentForm::on_toolButtonAreaFromCAD_clicked()
{
	if(QMessageBox::question(NULL,LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_12)/*"遒ｺ隱*/
						,LangSolver.GetString(EasyPropertyAlignmentForm_LS,LID_13)/*"驕ｸ謚槭＠縺滄伜沺遞ｮ鬘槭〒縲∵里蟄倥鬆伜沺縺ｨ繝槭繧ｯ縺御ｸ譌ｦ蜑企勁縺輔ｌ縺ｾ縺*/
						,QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(m!=NULL){
			IntegrationCmdReqMakeAreaFromCAD	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			if(ui->toolButtonAreaPriority->isChecked()==false){
				RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityGlobal);
			}
			else{
				RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityMiddle);
				RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityLow);
			}
			RCmd.Send(NULL,SlaveNo,0);
		}
		BroadcastRepaintAll();
	}
}



//============================================================================
IntegrationCmdGenerateAreaAndItem::IntegrationCmdGenerateAreaAndItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdGenerateAreaAndItem::Load(QIODevice *f)
{
	if(::Load(f,GeneratePartialAlignment)==false)		return false;
	if(ItemLibIDs.Load(f)==false)						return false;
	if(::Load(f,AlignmntAreaErosion)==false)			return false;
	if(::Load(f,AlignmntPointSize)==false)				return false;
	if(::Load(f,AlignmntSearchAreaDot)==false)			return false;
	if(::Load(f,AlignmntSearchAreaDot2)==false)			return false;
	if(::Load(f,AlignmntSearchAreaDotMiddle)==false)	return false;
	if(::Load(f,AlignmntSearchAreaDotY)==false)			return false;
	if(::Load(f,AlignmntSearchAreaDot2Y)==false)		return false;
	if(::Load(f,AlignmntSearchAreaDotMiddleY)==false)	return false;
	if(::Load(f,AlignmntGeneratedLayer)==false)			return false;
	if(::Load(f,AlignmntJudgeWithBrDif)==false)			return false;
	return true;
}
bool	IntegrationCmdGenerateAreaAndItem::Save(QIODevice *f)
{
	if(::Save(f,GeneratePartialAlignment)==false)		return false;
	if(ItemLibIDs.Save(f)==false)						return false;
	if(::Save(f,AlignmntAreaErosion)==false)			return false;
	if(::Save(f,AlignmntPointSize)==false)				return false;
	if(::Save(f,AlignmntSearchAreaDot)==false)			return false;
	if(::Save(f,AlignmntSearchAreaDot2)==false)			return false;
	if(::Save(f,AlignmntSearchAreaDotMiddle)==false)	return false;
	if(::Save(f,AlignmntSearchAreaDotY)==false)			return false;
	if(::Save(f,AlignmntSearchAreaDot2Y)==false)		return false;
	if(::Save(f,AlignmntSearchAreaDotMiddleY)==false)	return false;
	if(::Save(f,AlignmntGeneratedLayer)==false)			return false;
	if(::Save(f,AlignmntJudgeWithBrDif)==false)			return false;
	return true;
}

void	IntegrationCmdGenerateAreaAndItem::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyAlignmentLargeForm",/**/"");
	if(f!=NULL){
		{
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"ClearAllAreas", Args, ExeReturn);
		}
		if(GeneratePartialAlignment==true){
			{
				QStringList Args;
				bool ExeReturn;
				Args.append(/**/"4");	//Global priority
				Args.append(QString::number(AlignmntAreaErosion));
				f->ExecuteMacro(/**/"CreateAreaInMask", Args, ExeReturn);
			}
			{
				QStringList Args;
				bool ExeReturn;
				Args.append(QString::number(AlignmntPointSize));
				Args.append(QString::number(AlignmntSearchAreaDot));
				Args.append(QString::number(AlignmntSearchAreaDotY));
				Args.append(QString::number(AlignmntSearchAreaDot2));
				Args.append(QString::number(AlignmntSearchAreaDot2Y));
				Args.append(QString::number(AlignmntGeneratedLayer));
				Args.append(QString::number(4));
				Args.append(QString(/**/"true"));
				if(AlignmntJudgeWithBrDif==true)
					Args.append(QString(/**/"true"));
				else
					Args.append(QString(/**/"false"));
				f->ExecuteMacro(/**/"AutoCreatePoint", Args, ExeReturn);
			}
			{
				QStringList Args;
				bool ExeReturn;
				Args.append(/**/"2");	//Middle priority
				Args.append(QString::number(AlignmntAreaErosion));
				f->ExecuteMacro(/**/"CreateAreaInMask", Args, ExeReturn);
			}
			{
				QStringList Args;
				bool ExeReturn;
				Args.append(QString::number(AlignmntPointSize));
				Args.append(QString::number(AlignmntSearchAreaDotMiddle));
				Args.append(QString::number(AlignmntSearchAreaDotMiddleY));
				Args.append(QString::number(AlignmntGeneratedLayer));
				Args.append(QString::number(2));
				Args.append(QString(/**/"true"));
				int	LimitedLib=-1;
				if(ItemLibIDs.GetFirst()!=NULL){
					LimitedLib=ItemLibIDs.GetFirst()->GetValue();
				}
				Args.append(QString::number(DefLibTypeDotColorMatchingInspect));
				Args.append(QString::number(LimitedLib));
				if(AlignmntJudgeWithBrDif==true)
					Args.append(QString(/**/"true"));
				else
					Args.append(QString(/**/"false"));
				f->ExecuteMacro(/**/"AutoCreatePointWithLib", Args, ExeReturn);
			}
		}
		else{
			{
				QStringList Args;
				bool ExeReturn;
				Args.append(/**/"2");	//Middle priority
				Args.append(QString::number(AlignmntAreaErosion));
				f->ExecuteMacro(/**/"CreateAreaInMask", Args, ExeReturn);
			}
			{
				QStringList Args;
				bool ExeReturn;
				Args.append(QString::number(AlignmntPointSize));
				Args.append(QString::number(AlignmntSearchAreaDot));
				Args.append(QString::number(AlignmntSearchAreaDotY));
				Args.append(QString::number(AlignmntSearchAreaDot2));
				Args.append(QString::number(AlignmntSearchAreaDot2Y));
				Args.append(QString::number(AlignmntGeneratedLayer));
				Args.append(QString::number(2));
				Args.append(QString(/**/"false"));
				if(AlignmntJudgeWithBrDif==true)
					Args.append(QString(/**/"true"));
				else
					Args.append(QString(/**/"false"));
				f->ExecuteMacro(/**/"AutoCreatePoint", Args, ExeReturn);
			}
		}
	}
}

//============================================================================
IntegrationCmdSetAreaMode::IntegrationCmdSetAreaMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSetAreaMode::Load(QIODevice *f)
{
	if(::Load(f,AreaMode)==false)	return false;
	if(AreaPriority.Load(f)==false)	return false;
	return true;
}
bool	IntegrationCmdSetAreaMode::Save(QIODevice *f)
{
	if(::Save(f,AreaMode)==false)	return false;
	if(AreaPriority.Save(f)==false)	return false;
	return true;
}

void	IntegrationCmdSetAreaMode::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyAlignmentLargeForm",/**/"");
	if(f!=NULL){
		if(AreaMode==true){
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"SetAreaMode", Args, ExeReturn);
		}
		else if(AreaMode==false){
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"SetPointMode", Args, ExeReturn);
		}		
	}
}

//============================================================================
IntegrationCmdClearAll::IntegrationCmdClearAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdClearAll::Load(QIODevice *f)
{
	if(::Load(f,AreaMode)==false)	return false;
	if(AreaPriority.Load(f)==false)	return false;
	return true;

}
bool	IntegrationCmdClearAll::Save(QIODevice *f)
{
	if(::Save(f,AreaMode)==false)	return false;
	if(AreaPriority.Save(f)==false)	return false;
	return true;
}

void	IntegrationCmdClearAll::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyAlignmentLargeForm",/**/"");
	if(f!=NULL){
		if(AreaMode==true){
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"ClearAllAreas", Args, ExeReturn);
		}
		else if(AreaMode==false){
			QStringList Args;
			bool ExeReturn;
			for(IntClass *c=AreaPriority.GetFirst();c!=NULL;c=c->GetNext()){
				int	iAreaPriority=c->GetValue();
				Args.append(QString::number(iAreaPriority));
				f->ExecuteMacro(/**/"ClearAllPointsByPriority", Args, ExeReturn);
			}
		}		
	}
}


IntegrationAutoGenerateMark::IntegrationAutoGenerateMark(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAutoGenerateMark::Load(QIODevice *f)
{
	if(AreaIDList.Load(f)==false)	return false;
	return true;
}
bool	IntegrationAutoGenerateMark::Save(QIODevice *f)
{
	if(AreaIDList.Save(f)==false)	return false;
	return true;
}

void	IntegrationAutoGenerateMark::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyAlignmentLargeForm",/**/"");
	if(f!=NULL){
		CmdAutoGenerateMark	RCmd(GetLayersBase());
		RCmd.AreaIDList	=AreaIDList;
		f->TransmitDirectly(&RCmd);
	}
}
