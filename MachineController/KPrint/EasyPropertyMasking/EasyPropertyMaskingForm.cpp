#include "EasyPropertyMaskingResource.h"
#include "EasyPropertyMaskingForm.h"
#include "ui_EasyPropertyMaskingForm.h"
#include "XMasking.h"
#include "XDataInLayer.h"
#include "XMaskingLibrary.h"
#include "CartonMenuForm.h"
#include "XParamCustomized.h"
#include "XDXFOperationPacket.h"
#include "XDotColorMatchingLibrary.h"
#include "SelectDeletionDialog.h"
#include <QColorDialog> 
#include "XIntegrationSimpleImagePanel.h"
#include "CreateOutlineDialog.h"
#include "CreatePatternEdgeDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

EasyPropertyMaskingForm::EasyPropertyMaskingForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::EasyPropertyMaskingForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	SlaveNo	=0;
	ReEntrant	=false;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	//ui->tableWidgetLimited->setColumnWidth(0,40);
	//ui->tableWidgetLimited->setColumnWidth(1,160);
	::SetColumnWidthInTable(ui->tableWidgetLimited,0, 20);
	::SetColumnWidthInTable(ui->tableWidgetLimited,1, 60);
	::SetColumnWidthInTable(ui->tableWidgetLimited,2, 20);

	connect(ui->tableWidgetLimited,SIGNAL(rightclicked(QTableWidgetItem *)),this,SLOT(SlotTableRightClicked(QTableWidgetItem *)));
}

EasyPropertyMaskingForm::~EasyPropertyMaskingForm()
{
    delete ui;
}

void	EasyPropertyMaskingForm::ReadyParam(void)
{
	on_spinBoxShrinkDotForCAD_valueChanged(0);

	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
		int	MachineCode=m->GetMachineCode();
		GUIFormBase *RetGUI[100];
		int	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint" ,/**/"EasyMaskingImagePanel" ,RetGUI ,sizeof(RetGUI)/sizeof(RetGUI[0]));
		for(int i=0;i<N;i++){
			IntegrationAlgoSimpleImagePanel	*a=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(RetGUI[i]);
			if(a!=NULL){
				if(a->MachineCode==MachineCode){
					connect(a,SIGNAL(SignalDrawEndAfterOperation(FlexArea &)),this,SLOT(SlotDrawEndAfterOperation(FlexArea &)));
					connect(a,SIGNAL(SignalChangedItems()),this,SLOT(SlotUpdateItemList()));
				}
			}
		}
	}

	TM.setInterval(300+SlaveNo*5);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();

}
void	EasyPropertyMaskingForm::ResizeAction()
{
}

void	EasyPropertyMaskingForm::StartPage(void)
{
	on_toolButtonEffective_clicked();
}

void	EasyPropertyMaskingForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdMaskingDrawInfo	*CmdMaskingDrawInfoVar=dynamic_cast<CmdMaskingDrawInfo *>(packet);
	if(CmdMaskingDrawInfoVar!=NULL){
		IntList Rows;
		::GetSelectedRows(ui->tableWidgetLimited ,Rows);
		CmdMaskingDrawInfoVar->Effective		=ui->toolButtonEffective->isChecked();
		CmdMaskingDrawInfoVar->Ineffective		=!ui->toolButtonEffective->isChecked();
		CmdMaskingDrawInfoVar->EffectiveLimited	=false;
		CmdMaskingDrawInfoVar->IneffectiveLimited=false;
		CmdMaskingDrawInfoVar->CutLine			=false;
		CmdMaskingDrawInfoVar->TransparentLevel	=ui->horizontalSlider->value();
		CmdMaskingDrawInfoVar->ShowOnlyLibID	=ui->toolButtonShowOnlyLibID->isChecked();

		if(ui->toolButtonSetAllPhases->isChecked()==true){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
			if(m!=NULL){
				for(int phase=0;phase<m->GetPhaseNumb();phase++){
					CmdMaskingDrawInfoVar->Phases.Add(phase);
				}
			}
		}

		int	SelectedRow=GetSelectedCurrentRow(ui->tableWidgetLimited);
		bool	LimitMaskMode=true;
		CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
		if(GProp!=NULL){
			int	LibID=0;
			if(SlaveNo==0){
				if(GProp->ParamInMaster.Slave0LibID.GetCount()>0)
					LibID=GProp->ParamInMaster.Slave0LibID.GetFirst()->GetValue();
				else
					LibID=GProp->Param.DotColorMatchLibPattern1		;
			}
			else if(SlaveNo==1){
				if(GProp->ParamInMaster.Slave1LibID.GetCount()>0)
					LibID=GProp->ParamInMaster.Slave1LibID.GetFirst()->GetValue();
				else
					LibID=GProp->Param.DotColorMatchLibFlat1		;
			}
			else if(SlaveNo==2){
				if(GProp->ParamInMaster.Slave2LibID.GetCount()>0)
					LibID=GProp->ParamInMaster.Slave2LibID.GetFirst()->GetValue();
				else
					LibID=GProp->Param.DotColorMatchLibFlat1		;
			}

			int	Row=0;
			for(AlgorithmLibraryList *L=LimitedLib.GetFirst();L!=NULL;L=L->GetNext(),Row++){
				if(SelectedRow==Row && L->GetLibID()==LibID){
					LimitMaskMode=false;
				}
			}
		}
		if(SelectedRow>=0){
			CmdMaskingDrawInfoVar->SelectedLibID=LimitedLib[SelectedRow]->GetLibID();
		}
		else{
			CmdMaskingDrawInfoVar->SelectedLibID=-1;
		}

		if(LimitMaskMode==true){
			for(IntClass *c=Rows.GetFirst();c!=NULL;c=c->GetNext()){
				AlgorithmLibraryList *L=LimitedLib.GetItem(c->GetValue());
				if(L!=NULL){
					AlgorithmLibraryList	*a=new AlgorithmLibraryList(*L);
					CmdMaskingDrawInfoVar->LimitedLib.AppendList(a);
				}
			}
		}
		if(CmdMaskingDrawInfoVar->Effective==false){
			CmdMaskingDrawInfoVar->LimitedLib.RemoveAll();
		}
		return;
	}
	IntegrationGenerateAutomatically	*IntegrationGenerateAutomaticallyVar=dynamic_cast<IntegrationGenerateAutomatically *>(packet);
	if(IntegrationGenerateAutomaticallyVar!=NULL){
		DeleteAutomaticItems();
		GenerateAutomatically();
		GetLayersBase()->GetIntegrationBasePointer()->ExecuteInitialAfterEdit(SlaveNo);
		return;
	}
}

void EasyPropertyMaskingForm::on_toolButtonEffective_clicked()
{
	if(ui->toolButtonEffective->isChecked()==true){
		ui->toolButtonEffective->setText(LangSolver.GetString(EasyPropertyMaskingForm_LS,LID_1)/*"?L?????"*/);
		ui->tableWidgetLimited->setVisible(true);

		IntegrationCmdReqLibrary	RCmd(GetLayersBase(),sRoot,sName,0);
		IntegrationCmdAckLibrary	ACmd(GetLayersBase(),sRoot,sName,0);
		if(RCmd.Send(0,0,ACmd)==true){
			LimitedLib=ACmd.LibContainer;
			ShowLimitTable();
		}

		CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
		if(GProp!=NULL){
			int	LibID=0;
			if(SlaveNo==0){
				if(GProp->ParamInMaster.Slave0LibID.GetCount()>0)
					LibID=GProp->ParamInMaster.Slave0LibID.GetFirst()->GetValue();
				else
					LibID=GProp->Param.DotColorMatchLibPattern1		;
			}
			else if(SlaveNo==1){
				if(GProp->ParamInMaster.Slave1LibID.GetCount()>0)
					LibID=GProp->ParamInMaster.Slave1LibID.GetFirst()->GetValue();
				else
					LibID=GProp->Param.DotColorMatchLibFlat1		;
			}
			else if(SlaveNo==2){
				if(GProp->ParamInMaster.Slave2LibID.GetCount()>0)
					LibID=GProp->ParamInMaster.Slave2LibID.GetFirst()->GetValue();
				else
					LibID=GProp->Param.DotColorMatchLibFlat1		;
			}

			int	Row=0;
			for(AlgorithmLibraryList *L=LimitedLib.GetFirst();L!=NULL;L=L->GetNext(),Row++){
				if(L->GetLibID()==LibID){
					::SetCurrentRow(ui->tableWidgetLimited, Row);
				}
			}
		}
	}
	else{
		ui->toolButtonEffective->setText(LangSolver.GetString(EasyPropertyMaskingForm_LS,LID_2)/*"???????"*/);
		ui->tableWidgetLimited->setVisible(false);
	}
	BroadcastRepaintAll();
}

void EasyPropertyMaskingForm::on_toolButtonAutoPickup_clicked()
{
	SelectDeletionDialog	D;
	if(D.exec()==(int)true){
		IntegrationDeleteAllMask	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.DeleteManualItems	=D.DeleteManualItems;
		RCmd.DeleteCADItems		=D.DeleteCADItems;
		if(RCmd.SendReqAck(NULL,SlaveNo,0)==true){

			emit	SignalBusy();
			GenerateAutomatically();
			GetLayersBase()->GetIntegrationBasePointer()->ExecuteInitialAfterEdit(SlaveNo);

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
	}
}
void	EasyPropertyMaskingForm::DeleteAutomaticItems(void)
{
	IntegrationDeleteAllMask	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.DeleteManualItems	=false;
	RCmd.DeleteCADItems		=false;
	RCmd.SendReqAck(NULL,SlaveNo,0);
}

void	EasyPropertyMaskingForm::DeleteOriginCAD(void)
{
	IntegrationDeleteOnlyCADMask	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.Send(NULL,SlaveNo,0);
}

void	EasyPropertyMaskingForm::SlotTimeOut()
{
	int	Row=ui->tableWidgetLimited->currentRow();
	if(Row>=0){
		QColor	Col0=::GetTableColor(ui->tableWidgetLimited, 0, Row);
		Col0=qRgb(~Col0.red(),~Col0.green(),~Col0.blue());
		::SetTableColor(ui->tableWidgetLimited, 0, Row, Col0);

		QColor	Col1=::GetTableColor(ui->tableWidgetLimited, 1, Row);
		Col1=qRgb(~Col1.red(),~Col1.green(),~Col1.blue());
		::SetTableColor(ui->tableWidgetLimited, 1, Row, Col1);
	}
}

void	EasyPropertyMaskingForm::GenerateAutomatically(void)
{
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		IntegrationCmdAutoPickup	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.MaskAutoPickupRL		=GProp->Param.MaskAutoPickupRL		;
		RCmd.MaskAutoPickupRH		=GProp->Param.MaskAutoPickupRH		;
		RCmd.MaskAutoPickupGL		=GProp->Param.MaskAutoPickupGL		;
		RCmd.MaskAutoPickupGH		=GProp->Param.MaskAutoPickupGH		;
		RCmd.MaskAutoPickupBL		=GProp->Param.MaskAutoPickupBL		;
		RCmd.MaskAutoPickupBH		=GProp->Param.MaskAutoPickupBH		;
		RCmd.MaskAutoLayer			=GProp->Param.MaskAutoLayer			;
		RCmd.MaskAutoMinPickupSize	=GProp->Param.MaskAutoMinPickupSize	;
		RCmd.MaskAutoMaxPickupSize	=GProp->Param.MaskAutoMaxPickupSize	;
		RCmd.MaskAutoMinPickupDots	=GProp->Param.MaskAutoMinPickupDots	;
		RCmd.MaskAutoMaxPickupDots	=GProp->Param.MaskAutoMaxPickupDots	;
		RCmd.MaskAutoErosion		=GProp->Param.MaskAutoErosion		;
		RCmd.LocalX					=GProp->Param.MaskAutoOutsideXPos	;
		RCmd.LocalY					=GProp->Param.MaskAutoOutsideYPos	;
		RCmd.MaskAutoExcludeLeftX	=GProp->Param.MaskAutoExcludeLeftX	;
		RCmd.MaskAutoExcludeRightX	=GProp->Param.MaskAutoExcludeRightX	;
		RCmd.MaskNoisePinhole 		=GProp->Param.MaskNoisePinhole		;
		RCmd.MaskNoiseSmallDot		=GProp->Param.MaskNoiseSmallDot		;

		RCmd.Mask2AutoPickupRL		=GProp->Param.Mask2AutoPickupRL;
		RCmd.Mask2AutoPickupRH		=GProp->Param.Mask2AutoPickupRH;
		RCmd.Mask2AutoPickupGL		=GProp->Param.Mask2AutoPickupGL;
		RCmd.Mask2AutoPickupGH		=GProp->Param.Mask2AutoPickupGH;
		RCmd.Mask2AutoPickupBL		=GProp->Param.Mask2AutoPickupBL;
		RCmd.Mask2AutoPickupBH		=GProp->Param.Mask2AutoPickupBH;
		RCmd.Mask2AutoMinPickupSize	=GProp->Param.Mask2AutoMinPickupSize;
		RCmd.Mask2AutoMaxPickupSize	=GProp->Param.Mask2AutoMaxPickupSize;
		RCmd.Mask2AutoMinPickupDots	=GProp->Param.Mask2AutoMinPickupDots;
		RCmd.Mask2AutoMaxPickupDots	=GProp->Param.Mask2AutoMaxPickupDots;
		RCmd.Mask2AutoErosion		=GProp->Param.Mask2AutoErosion;
		RCmd.Mask2AutoOutsideXPos	=GProp->Param.Mask2AutoOutsideXPos;
		RCmd.Mask2AutoOutsideYPos	=GProp->Param.Mask2AutoOutsideYPos;
		RCmd.Mask2NoisePinhole 		=GProp->Param.Mask2NoisePinhole		;
		RCmd.Mask2NoiseSmallDot		=GProp->Param.Mask2NoiseSmallDot	;

		RCmd.Mask3AutoPickupRL		=GProp->Param.Mask3AutoPickupRL;
		RCmd.Mask3AutoPickupRH		=GProp->Param.Mask3AutoPickupRH;
		RCmd.Mask3AutoPickupGL		=GProp->Param.Mask3AutoPickupGL;
		RCmd.Mask3AutoPickupGH		=GProp->Param.Mask3AutoPickupGH;
		RCmd.Mask3AutoPickupBL		=GProp->Param.Mask3AutoPickupBL;
		RCmd.Mask3AutoPickupBH		=GProp->Param.Mask3AutoPickupBH;
		RCmd.Mask3AutoMinPickupSize =GProp->Param.Mask3AutoMinPickupSize;
		RCmd.Mask3AutoMaxPickupSize =GProp->Param.Mask3AutoMaxPickupSize;
		RCmd.Mask3AutoMinPickupDots =GProp->Param.Mask3AutoMinPickupDots;
		RCmd.Mask3AutoMaxPickupDots =GProp->Param.Mask3AutoMaxPickupDots;
		RCmd.Mask3AutoErosion		=GProp->Param.Mask3AutoErosion;
		RCmd.Mask3AutoOutsideXPos	=GProp->Param.Mask3AutoOutsideXPos;
		RCmd.Mask3AutoOutsideYPos	=GProp->Param.Mask3AutoOutsideYPos;
		RCmd.Mask3NoisePinhole 		=GProp->Param.Mask3NoisePinhole		;
		RCmd.Mask3NoiseSmallDot		=GProp->Param.Mask3NoiseSmallDot	;

		RCmd.Mask4AutoPickupRL		=GProp->Param.Mask4AutoPickupRL;
		RCmd.Mask4AutoPickupRH		=GProp->Param.Mask4AutoPickupRH;
		RCmd.Mask4AutoPickupGL		=GProp->Param.Mask4AutoPickupGL;
		RCmd.Mask4AutoPickupGH		=GProp->Param.Mask4AutoPickupGH;
		RCmd.Mask4AutoPickupBL		=GProp->Param.Mask4AutoPickupBL;
		RCmd.Mask4AutoPickupBH		=GProp->Param.Mask4AutoPickupBH;
		RCmd.Mask4AutoMinPickupSize =GProp->Param.Mask4AutoMinPickupSize;
		RCmd.Mask4AutoMaxPickupSize =GProp->Param.Mask4AutoMaxPickupSize;
		RCmd.Mask4AutoMinPickupDots =GProp->Param.Mask4AutoMinPickupDots;
		RCmd.Mask4AutoMaxPickupDots =GProp->Param.Mask4AutoMaxPickupDots;
		RCmd.Mask4AutoErosion		=GProp->Param.Mask4AutoErosion;
		RCmd.Mask4AutoOutsideXPos	=GProp->Param.Mask4AutoOutsideXPos;
		RCmd.Mask4AutoOutsideYPos	=GProp->Param.Mask4AutoOutsideYPos;
		RCmd.Mask4NoisePinhole 		=GProp->Param.Mask4NoisePinhole		;
		RCmd.Mask4NoiseSmallDot		=GProp->Param.Mask4NoiseSmallDot	;
		RCmd.OmitX1					=GProp->Param.MaskAutoExcludeLeftX;
		RCmd.OmitY1					=0;
		RCmd.OmitX2					=GProp->Param.MaskAutoExcludeRightX;
		RCmd.OmitY2					=99999999;//m->GetMaxLines(0,0);

		if(SlaveNo==1){
			RCmd.LocalX				=GProp->Param.Mask2AutoOutsideXPos	;
			RCmd.LocalY				=GProp->Param.Mask2AutoOutsideYPos	;
			RCmd.MaskAutoErosion	=GProp->Param.Mask2AutoErosion;
			RCmd.MaskAutoMinPickupDots	=GProp->Param.Mask2AutoMinPickupDots;
			RCmd.MaskAutoMinPickupSize	=GProp->Param.Mask2AutoMinPickupSize;
			RCmd.MaskNoisePinhole 		=GProp->Param.Mask2NoisePinhole		;
			RCmd.MaskNoiseSmallDot		=GProp->Param.Mask2NoiseSmallDot	;
		}
		else
		if(SlaveNo==2){
			RCmd.LocalX				=GProp->Param.Mask3AutoOutsideXPos	;
			RCmd.LocalY				=GProp->Param.Mask3AutoOutsideYPos	;
			RCmd.MaskAutoErosion	=GProp->Param.Mask3AutoErosion;
			RCmd.MaskAutoMinPickupDots	=GProp->Param.Mask3AutoMinPickupDots;
			RCmd.MaskAutoMinPickupSize	=GProp->Param.Mask3AutoMinPickupSize;
			RCmd.MaskNoisePinhole 		=GProp->Param.Mask3NoisePinhole		;
			RCmd.MaskNoiseSmallDot		=GProp->Param.Mask3NoiseSmallDot	;
		}
		else
		if(SlaveNo==3){
			RCmd.LocalX				=GProp->Param.Mask4AutoOutsideXPos	;
			RCmd.LocalY				=GProp->Param.Mask4AutoOutsideYPos	;
			RCmd.MaskAutoErosion	=GProp->Param.Mask4AutoErosion;
			RCmd.MaskAutoMinPickupDots	=GProp->Param.Mask4AutoMinPickupDots;
			RCmd.MaskAutoMinPickupSize	=GProp->Param.Mask4AutoMinPickupSize;
			RCmd.MaskNoisePinhole 		=GProp->Param.Mask4NoisePinhole		;
			RCmd.MaskNoiseSmallDot		=GProp->Param.Mask4NoiseSmallDot	;
		}


		if(SlaveNo==1
		&& (GProp->Param.Mask2AutoPickupRL!=0
		 || GProp->Param.Mask2AutoPickupRH!=0
		 || GProp->Param.Mask2AutoPickupGL!=0
		 || GProp->Param.Mask2AutoPickupGH!=0
		 || GProp->Param.Mask2AutoPickupBL!=0
		 || GProp->Param.Mask2AutoPickupBH!=0)
		&& (RCmd.Mask2AutoMinPickupSize!=0
		 || RCmd.Mask2AutoMaxPickupSize!=0
		 || RCmd.Mask2AutoMinPickupDots!=0
		 || RCmd.Mask2AutoMaxPickupDots!=0)){
			RCmd.MaskAutoPickupRL		=RCmd.Mask2AutoPickupRL		;
			RCmd.MaskAutoPickupRH		=RCmd.Mask2AutoPickupRH		;
			RCmd.MaskAutoPickupGL		=RCmd.Mask2AutoPickupGL		;
			RCmd.MaskAutoPickupGH		=RCmd.Mask2AutoPickupGH		;
			RCmd.MaskAutoPickupBL		=RCmd.Mask2AutoPickupBL		;
			RCmd.MaskAutoPickupBH		=RCmd.Mask2AutoPickupBH		;
			RCmd.MaskAutoMinPickupSize	=RCmd.Mask2AutoMinPickupSize	;
			RCmd.MaskAutoMaxPickupSize	=RCmd.Mask2AutoMaxPickupSize	;
			RCmd.MaskAutoMinPickupDots	=RCmd.Mask2AutoMinPickupDots	;
			RCmd.MaskAutoMaxPickupDots	=RCmd.Mask2AutoMaxPickupDots	;
			RCmd.MaskAutoErosion		=RCmd.Mask2AutoErosion		;
			RCmd.MaskNoisePinhole 		=RCmd.Mask2NoisePinhole 	;
			RCmd.MaskNoiseSmallDot		=RCmd.Mask2NoiseSmallDot	;
		}
		if(SlaveNo==2
		&& (GProp->Param.Mask3AutoPickupRL!=0
		 || GProp->Param.Mask3AutoPickupRH!=0
		 || GProp->Param.Mask3AutoPickupGL!=0
		 || GProp->Param.Mask3AutoPickupGH!=0
		 || GProp->Param.Mask3AutoPickupBL!=0
		 || GProp->Param.Mask3AutoPickupBH!=0)
		&& (RCmd.Mask3AutoMinPickupSize!=0
		 || RCmd.Mask3AutoMaxPickupSize!=0
		 || RCmd.Mask3AutoMinPickupDots!=0
		 || RCmd.Mask3AutoMaxPickupDots!=0)){
			RCmd.MaskAutoPickupRL		=RCmd.Mask3AutoPickupRL		;
			RCmd.MaskAutoPickupRH		=RCmd.Mask3AutoPickupRH		;
			RCmd.MaskAutoPickupGL		=RCmd.Mask3AutoPickupGL		;
			RCmd.MaskAutoPickupGH		=RCmd.Mask3AutoPickupGH		;
			RCmd.MaskAutoPickupBL		=RCmd.Mask3AutoPickupBL		;
			RCmd.MaskAutoPickupBH		=RCmd.Mask3AutoPickupBH		;
			RCmd.MaskAutoMinPickupSize	=RCmd.Mask3AutoMinPickupSize	;
			RCmd.MaskAutoMaxPickupSize	=RCmd.Mask3AutoMaxPickupSize	;
			RCmd.MaskAutoMinPickupDots	=RCmd.Mask3AutoMinPickupDots	;
			RCmd.MaskAutoMaxPickupDots	=RCmd.Mask3AutoMaxPickupDots	;
			RCmd.MaskAutoErosion		=RCmd.Mask3AutoErosion		;
			RCmd.MaskNoisePinhole 		=RCmd.Mask3NoisePinhole 	;
			RCmd.MaskNoiseSmallDot		=RCmd.Mask3NoiseSmallDot	;
		}
		if(SlaveNo==3
		&& (GProp->Param.Mask4AutoPickupRL!=0
		 || GProp->Param.Mask4AutoPickupRH!=0
		 || GProp->Param.Mask4AutoPickupGL!=0
		 || GProp->Param.Mask4AutoPickupGH!=0
		 || GProp->Param.Mask4AutoPickupBL!=0
		 || GProp->Param.Mask4AutoPickupBH!=0)
		&& (RCmd.Mask4AutoMinPickupSize!=0
		 || RCmd.Mask4AutoMaxPickupSize!=0
		 || RCmd.Mask4AutoMinPickupDots!=0
		 || RCmd.Mask4AutoMaxPickupDots!=0)){
			RCmd.MaskAutoPickupRL		=RCmd.Mask4AutoPickupRL		;
			RCmd.MaskAutoPickupRH		=RCmd.Mask4AutoPickupRH		;
			RCmd.MaskAutoPickupGL		=RCmd.Mask4AutoPickupGL		;
			RCmd.MaskAutoPickupGH		=RCmd.Mask4AutoPickupGH		;
			RCmd.MaskAutoPickupBL		=RCmd.Mask4AutoPickupBL		;
			RCmd.MaskAutoPickupBH		=RCmd.Mask4AutoPickupBH		;
			RCmd.MaskAutoMinPickupSize	=RCmd.Mask4AutoMinPickupSize	;
			RCmd.MaskAutoMaxPickupSize	=RCmd.Mask4AutoMaxPickupSize	;
			RCmd.MaskAutoMinPickupDots	=RCmd.Mask4AutoMinPickupDots	;
			RCmd.MaskAutoMaxPickupDots	=RCmd.Mask4AutoMaxPickupDots	;
			RCmd.MaskAutoErosion		=RCmd.Mask4AutoErosion		;
			RCmd.MaskNoisePinhole 		=RCmd.Mask4NoisePinhole 	;
			RCmd.MaskNoiseSmallDot		=RCmd.Mask4NoiseSmallDot	;
		}

		RCmd.Send(NULL,SlaveNo,0);

		if(GProp->Param.DotColorMatchBladeLib1>0 || GProp->Param.DotColorMatchBladeLib2>0){
			if(SlaveNo==0 && GProp->Param.GenerateBradeTop==true){
				IntegrationCmdAutoPickup	ECmd(GetLayersBase(),sRoot,sName,SlaveNo);
				ECmd.MaskAutoPickupRL		=GProp->Param.BladeTopPickupRL		;
				ECmd.MaskAutoPickupRH		=GProp->Param.BladeTopPickupRH		;
				ECmd.MaskAutoPickupGL		=GProp->Param.BladeTopPickupGL		;
				ECmd.MaskAutoPickupGH		=GProp->Param.BladeTopPickupGH		;
				ECmd.MaskAutoPickupBL		=GProp->Param.BladeTopPickupBL		;
				ECmd.MaskAutoPickupBH		=GProp->Param.BladeTopPickupBH		;
				ECmd.MaskAutoLayer			=GProp->Param.MaskAutoLayer			;
				ECmd.MaskAutoMinPickupSize	=GProp->Param.MaskAutoMinPickupSize	;
				ECmd.MaskAutoMaxPickupSize	=GProp->Param.MaskAutoMaxPickupSize	;
				ECmd.MaskAutoMinPickupDots	=GProp->Param.MaskAutoMinPickupDots	;
				ECmd.MaskAutoMaxPickupDots	=GProp->Param.MaskAutoMaxPickupDots	;
				ECmd.MaskAutoErosion		=0;
				ECmd.MaskNoisePinhole 		=0;
				ECmd.MaskNoiseSmallDot		=0;
				ECmd.BladeAreaX1			=GProp->Param.BladeTopLeft;
				ECmd.BladeAreaY1			=0;
				ECmd.BladeAreaX2			=GProp->Param.BladeTopRight;
				ECmd.BladeAreaY2			=99999999;

				if(GProp->Param.DotColorMatchBladeLib1>0){
					AlgorithmLibraryList	*a=new AlgorithmLibraryList(DefLibTypeDotColorMatchingInspect,GProp->Param.DotColorMatchBladeLib1,/**/"");
					ECmd.LimitedLib.AppendList(a);
				}
				if(GProp->Param.DotColorMatchBladeLib2>0){
					AlgorithmLibraryList	*a=new AlgorithmLibraryList(DefLibTypeDotColorMatchingInspect,GProp->Param.DotColorMatchBladeLib2,/**/"");
					ECmd.LimitedLib.AppendList(a);
				}
				ECmd.LocalX					=-1;
				ECmd.LocalY					=-1;
				ECmd.BladeHoleMinArea		=GProp->Param.BladeHoleMinArea		;
				ECmd.BladeHoleErosionDot	=GProp->Param.BladeHoleErosionDot	;
				ECmd.OmitX1					=GProp->Param.MaskAutoExcludeLeftX;
				ECmd.OmitY1					=0;
				ECmd.OmitX2					=GProp->Param.MaskAutoExcludeRightX;
				ECmd.OmitY2					= 99999999;//m->GetMaxLines(0,0);
				ECmd.MaskNoisePinhole 		=0;
				ECmd.MaskNoiseSmallDot		=0;
				ECmd.Send(NULL,SlaveNo,0);
			}
			else
			if(SlaveNo==1 && GProp->Param.GenerateBradeBottom==true){
				IntegrationCmdAutoPickup	ECmd(GetLayersBase(),sRoot,sName,SlaveNo);
				ECmd.MaskAutoPickupRL		=GProp->Param.BladeBottomPickupRL		;
				ECmd.MaskAutoPickupRH		=GProp->Param.BladeBottomPickupRH		;
				ECmd.MaskAutoPickupGL		=GProp->Param.BladeBottomPickupGL		;
				ECmd.MaskAutoPickupGH		=GProp->Param.BladeBottomPickupGH		;
				ECmd.MaskAutoPickupBL		=GProp->Param.BladeBottomPickupBL		;
				ECmd.MaskAutoPickupBH		=GProp->Param.BladeBottomPickupBH		;
				ECmd.MaskAutoLayer			=GProp->Param.MaskAutoLayer			;
				ECmd.MaskAutoMinPickupSize	=GProp->Param.MaskAutoMinPickupSize	;
				ECmd.MaskAutoMaxPickupSize	=GProp->Param.MaskAutoMaxPickupSize	;
				ECmd.MaskAutoMinPickupDots	=GProp->Param.MaskAutoMinPickupDots	;
				ECmd.MaskAutoMaxPickupDots	=GProp->Param.MaskAutoMaxPickupDots	;
				ECmd.MaskAutoErosion		=0;
				ECmd.BladeAreaX1			=GProp->Param.BladeBottomLeft;
				ECmd.BladeAreaY1			=0;
				ECmd.BladeAreaX2			=GProp->Param.BladeBottomRight;
				ECmd.BladeAreaY2			=99999999;
				if(GProp->Param.DotColorMatchBladeLib1>0){
					AlgorithmLibraryList	*a=new AlgorithmLibraryList(DefLibTypeDotColorMatchingInspect,GProp->Param.DotColorMatchBladeLib1,/**/"");
					ECmd.LimitedLib.AppendList(a);
				}
				if(GProp->Param.DotColorMatchBladeLib2>0){
					AlgorithmLibraryList	*a=new AlgorithmLibraryList(DefLibTypeDotColorMatchingInspect,GProp->Param.DotColorMatchBladeLib2,/**/"");
					ECmd.LimitedLib.AppendList(a);
				}
				ECmd.LocalX					=-1;
				ECmd.LocalY					=-1;
				ECmd.BladeHoleMinArea		=GProp->Param.BladeHoleMinArea		;
				ECmd.BladeHoleErosionDot	=GProp->Param.BladeHoleErosionDot	;
				ECmd.OmitX1					=GProp->Param.MaskAutoExcludeLeftX;
				ECmd.OmitY1					=0;
				ECmd.OmitX2					=GProp->Param.MaskAutoExcludeRightX;
				ECmd.OmitY2					= 99999999;//m->GetMaxLines(0,0);
				ECmd.MaskNoisePinhole 		=0;
				ECmd.MaskNoiseSmallDot		=0;
				ECmd.Send(NULL,SlaveNo,0);
			}
		}
		GetLayersBase()->GetIntegrationBasePointer()->ExecuteInitialAfterEdit(SlaveNo);
	}
	BroadcastRepaintAll();
}

struct LibIDPriority
{
	int	LibID;
	int	PriorityToShow;
};
int	FuncDLib(const void *a ,const void *b)
{
	struct LibIDPriority	*pa=((struct LibIDPriority*)a);
	struct LibIDPriority	*pb=((struct LibIDPriority*)b);
	int d=pa->PriorityToShow-pb->PriorityToShow;
	d*=10000;
	if(d==0){
		d+=pa->LibID-pb->LibID;
	}
	return d;
}

void	EasyPropertyMaskingForm::SlotDrawEndAfterOperation(FlexArea &ResultArea)
{
	ShowLimitTable();
}

void EasyPropertyMaskingForm::SlotUpdateItemList()
{
	ShowLimitTable();
}

void	EasyPropertyMaskingForm::ShowLimitTable(void)
{
	struct LibIDPriority	*DLibDim=new struct LibIDPriority[LimitedLib.GetCount()];
	int	LibNumb=0;
	int	CurrentRow=ui->tableWidgetLimited->currentRow();

	ui->tableWidgetLimited->setRowCount(LimitedLib.GetCount());
	for(AlgorithmLibraryList *L=LimitedLib.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*ABase = GetLayersBase()->GetAlgorithmBase(L->GetLibType());
		if(ABase!=NULL && ABase->GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	SrcLib(ABase);
			if(ABase->GetLibraryContainer()->GetLibrary(L->GetLibID(),SrcLib)==true){
				DotColorMatchingLibrary	*DLib=(DotColorMatchingLibrary	*)SrcLib.GetLibrary();
				if(DLib!=NULL){
					DLibDim[LibNumb].LibID			=L->GetLibID();
					DLibDim[LibNumb].PriorityToShow	=DLib->PriorityToShow;
					LibNumb++;
				}
			}
		}
	}
	qsort(DLibDim,LibNumb,sizeof(DLibDim[0]),FuncDLib);

	AlgorithmLibraryList	**ALibDim=new AlgorithmLibraryList	*[LimitedLib.GetCount()];
	AlgorithmLibraryList *pL;
	int	k=0;
	while((pL=LimitedLib.GetFirst())!=NULL){
		LimitedLib.RemoveList(pL);
		ALibDim[k]=pL;
		k++;
	}

	UsedLimitedMaskContainer	MaskCounter;
	{
		IntegrationCmdReqMaskCount	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationCmdAckMaskCount	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			MaskCounter=ACmd.MaskContainer;
		}
	}

	int	Row=0;
	for(int i=0;i<LibNumb;i++){
		AlgorithmLibraryList *L=NULL;
		for(int t=0;t<k;t++){
			if(ALibDim[t]!=NULL){
				if(ALibDim[t]->GetLibID()==DLibDim[i].LibID){
					L=ALibDim[t];
					ALibDim[t]=NULL;
					break;
				}
			}
		}
		if(L!=NULL){
			LimitedLib.AppendList(L);

			::SetDataToTable(ui->tableWidgetLimited,0,Row ,QString::number(L->GetLibID()));
			::SetDataToTable(ui->tableWidgetLimited,1,Row ,L->GetLibName());

			int	Count=0;
			for(UsedLimitedMask *a=MaskCounter.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Layer==0
				&& a->Effective==true
				&& a->SelAreaID.IsInclude(L->GetLibType(),L->GetLibID())==true){
					Count+=a->Count;
				}
			}
			if(Count!=0){
				::SetDataToTable(ui->tableWidgetLimited,2,Row ,QString::number(Count));
			}
			else{
				::SetDataToTable(ui->tableWidgetLimited,2,Row ,QString(/**/""));
			}

			AlgorithmBase	*ABase = GetLayersBase()->GetAlgorithmBase(L->GetLibType());
			QColor	LibColor;
			if(ABase!=NULL && ABase->GetLibraryContainer()!=NULL){
				AlgorithmLibraryLevelContainer	SrcLib(ABase);
				if(ABase->GetLibraryContainer()->GetLibrary(L->GetLibID(),SrcLib)==true){
					LibColor=SrcLib.GetLibColor();
					if(LibColor.isValid()==true){
						::SetTableColor(ui->tableWidgetLimited, 0, Row, LibColor);
						::SetTableColor(ui->tableWidgetLimited, 1, Row, LibColor);
					}
				}
			}
			Row++;
		}
	}
	delete	[]DLibDim;
	delete	[]ALibDim;

	ui->tableWidgetLimited->setVisible(false);
	if(ui->toolButtonEffective->isChecked()==true){
		ui->tableWidgetLimited->setVisible(true);
	}
	::SetColumnWidthInTable(ui->tableWidgetLimited,0, 20);
	::SetColumnWidthInTable(ui->tableWidgetLimited,1, 60);
	::SetColumnWidthInTable(ui->tableWidgetLimited,2, 20);

	::SetCurrentRow(ui->tableWidgetLimited,CurrentRow);
}

void EasyPropertyMaskingForm::SlotTableRightClicked(QTableWidgetItem *item)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if(MaskingBase==NULL)
		return;

	int	Row=item->row();
	if(Row<0)
		return;
	
	AlgorithmLibraryList *L=LimitedLib[Row];
	if(L!=NULL){
		QColor	LibColor;
		AlgorithmLibraryLevelContainer	SrcLib(MaskingBase);
		if(MaskingBase->GetLibraryContainer()->GetLibrary(L->GetLibID(),SrcLib)==true){
			LibColor=SrcLib.GetLibColor();
		
			QColor Col=QColorDialog::getColor(LibColor, nullptr
											, LangSolver.GetString(EasyPropertyMaskingForm_LS,LID_4)/*"Library color"*/);
			if(Col.isValid()==true){
				SrcLib.SetLibColor(Col);
				MaskingBase->GetLibraryContainer()->Update(SrcLib);
				ShowLimitTable();
			}
		}
	}
}

void EasyPropertyMaskingForm::on_horizontalSlider_valueChanged(int value)
{
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
		int	MachineCode=m->GetMachineCode();
		GUIFormBase *RetGUI[100];
		int	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint" ,/**/"EasyMaskingImagePanel" ,RetGUI ,sizeof(RetGUI)/sizeof(RetGUI[0]));
		for(int i=0;i<N;i++){
			IntegrationAlgoSimpleImagePanel	*a=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(RetGUI[i]);
			if(a!=NULL){
				if(a->MachineCode==MachineCode){
					a->Repaint();
				}
			}
		}
	}
}

void EasyPropertyMaskingForm::on_toolButtonMakeEffectiveFromCAD_clicked()
{
	IntegrationMakeEffectiveFromCAD	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.ShrinkDot=ui->spinBoxShrinkDotForCAD->value();
	RCmd.Send(NULL,SlaveNo,0);
	BroadcastRepaintAll();
}

void EasyPropertyMaskingForm::on_spinBoxShrinkDotForCAD_valueChanged(int arg1)
{
	if(ReEntrant==false){
		ReEntrant=true;
		EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(ThisM!=NULL){
			int		ShrinkDot	=ui->spinBoxShrinkDotForCAD->value();
			double	ShrinkDotMM	=ThisM->TransformPixelToUnit(ShrinkDot);
			ui->doubleSpinBoxShrinkDotForCADMM->setValue(ShrinkDotMM);
		}
		ReEntrant=false;
	}
}

void EasyPropertyMaskingForm::on_doubleSpinBoxShrinkDotForCADMM_valueChanged(double arg1)
{
	if(ReEntrant==false){
		ReEntrant=true;
		EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(ThisM!=NULL){
			double	ShrinkDotMM	=ui->doubleSpinBoxShrinkDotForCADMM->value();
			int		ShrinkDot	=ThisM->TransformUnitToPixel(ShrinkDotMM);
			ui->spinBoxShrinkDotForCAD->setValue(ShrinkDot);
		}
		ReEntrant=false;
	}
}
void	EasyPropertyMaskingForm::StartInitial(void)
{
	ShowLimitTable();
}


void EasyPropertyMaskingForm::on_toolButtonMakeOutlineArea_clicked()
{
	CreateOutlineDialog	D(GetLayersBase());
	if(D.exec()==true){
		IntegrationGenerateOutlineArea	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.LimitedLib	=D.GetSelectedList();
		RCmd.Expansion	=D.Expansion ;
		RCmd.InsideDot	=D.InsideDot ;
		RCmd.OutsideDot	=D.OutsideDot;
		RCmd.Send(NULL,SlaveNo,0);
		BroadcastRepaintAll();
	}
}

void EasyPropertyMaskingForm::on_toolButtonMakePatternEdge_clicked()
{
	CreatePatternEdgeDialog	D(GetLayersBase());
	if(D.exec()==true){
		IntegrationCreatePatternEdge	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.LimitedLib		=D.GetSelectedList();
		RCmd.BoundaryDiff	=D.BoundaryDiff ;
		RCmd.WidthDot		=D.WidthDot ;
		RCmd.Send(NULL,SlaveNo,0);
		BroadcastRepaintAll();
	}
}

void EasyPropertyMaskingForm::on_tableWidgetLimited_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetLimited->currentRow();
	if(Row>=0){
		AlgorithmLibraryList	*L=LimitedLib.GetItem(Row);
		if(L!=NULL){
			IntegrationSetItemSelection	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.Effective		=ui->toolButtonEffective->isChecked();
			RCmd.LimitedLib.AppendList(new AlgorithmLibraryList(*L));
			RCmd.Send(NULL,SlaveNo,0);
		}
	}
}
void EasyPropertyMaskingForm::on_toolButtonShowOnlyLibID_clicked()
{
	BroadcastRepaintAll();
}



//============================================================================
IntegrationCmdAutoPickup::IntegrationCmdAutoPickup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	MaskAutoPickupRL		=0;
	MaskAutoPickupRH		=0;
	MaskAutoPickupGL		=0;
	MaskAutoPickupGH		=0;
	MaskAutoPickupBL		=0;
	MaskAutoPickupBH		=0;
	MaskAutoLayer			=0;
	MaskAutoMinPickupSize	=0;
	MaskAutoMaxPickupSize	=0;
	MaskAutoMinPickupDots	=0;
	MaskAutoMaxPickupDots	=0;
	MaskAutoErosion			=0;
	LocalX					=0;
	LocalY					=0;
	BladeHoleMinArea		=0;
	BladeHoleErosionDot		=0;
	MaskAutoExcludeLeftX	=0;
	MaskAutoExcludeRightX	=0;
	MaskNoisePinhole 		=0;
	MaskNoiseSmallDot		=0;

	Mask2AutoPickupRL = 0;
	Mask2AutoPickupRH = 0;
	Mask2AutoPickupGL = 0;
	Mask2AutoPickupGH = 0;
	Mask2AutoPickupBL = 0;
	Mask2AutoPickupBH = 0;
	Mask2AutoMinPickupSize = 0;
	Mask2AutoMaxPickupSize = 0;
	Mask2AutoMinPickupDots = 0;
	Mask2AutoMaxPickupDots = 0;
	Mask2AutoErosion = 0;
	Mask2AutoOutsideXPos=0;
	Mask2AutoOutsideYPos=0;
	Mask2NoisePinhole 	=0;
	Mask2NoiseSmallDot	=0;

	Mask3AutoPickupRL = 0;
	Mask3AutoPickupRH = 0;
	Mask3AutoPickupGL = 0;
	Mask3AutoPickupGH = 0;
	Mask3AutoPickupBL = 0;
	Mask3AutoPickupBH = 0;
	Mask3AutoMinPickupSize = 0;
	Mask3AutoMaxPickupSize = 0;
	Mask3AutoMinPickupDots = 0;
	Mask3AutoMaxPickupDots = 0;
	Mask3AutoErosion = 0;
	Mask3AutoOutsideXPos=0;
	Mask3AutoOutsideYPos=0;
	Mask3NoisePinhole 	=0;
	Mask3NoiseSmallDot	=0;

	Mask4AutoPickupRL = 0;
	Mask4AutoPickupRH = 0;
	Mask4AutoPickupGL = 0;
	Mask4AutoPickupGH = 0;
	Mask4AutoPickupBL = 0;
	Mask4AutoPickupBH = 0;
	Mask4AutoMinPickupSize = 0;
	Mask4AutoMaxPickupSize = 0;
	Mask4AutoMinPickupDots = 0;
	Mask4AutoMaxPickupDots = 0;
	Mask4AutoErosion = 0;
	Mask4AutoOutsideXPos=0;
	Mask4AutoOutsideYPos=0;
	Mask4NoisePinhole 	=0;
	Mask4NoiseSmallDot	=0;
	BladeAreaX1	=0;
	BladeAreaY1	=0;
	BladeAreaX2	=99999999;
	BladeAreaY2	=99999999;
}
bool	IntegrationCmdAutoPickup::Load(QIODevice *f)
{
	if(::Load(f,MaskAutoPickupRL		)==false)	return false;
	if(::Load(f,MaskAutoPickupRH		)==false)	return false;
	if(::Load(f,MaskAutoPickupGL		)==false)	return false;
	if(::Load(f,MaskAutoPickupGH		)==false)	return false;
	if(::Load(f,MaskAutoPickupBL		)==false)	return false;
	if(::Load(f,MaskAutoPickupBH		)==false)	return false;
	if(::Load(f,MaskAutoLayer			)==false)	return false;
	if(::Load(f,MaskAutoMinPickupSize	)==false)	return false;
	if(::Load(f,MaskAutoMaxPickupSize	)==false)	return false;
	if(::Load(f,MaskAutoMinPickupDots	)==false)	return false;
	if(::Load(f,MaskAutoMaxPickupDots	)==false)	return false;
	if(::Load(f,MaskAutoErosion			)==false)	return false;
	if(::Load(f,LocalX					)==false)	return false;
	if(::Load(f,LocalY					)==false)	return false;
	if(::Load(f,MaskAutoExcludeLeftX	)== false)	return false;
	if(::Load(f,MaskAutoExcludeRightX	)== false)	return false;
	if(::Load(f,BladeHoleMinArea		)==false)	return false;
	if(::Load(f,BladeHoleErosionDot		)==false)	return false;
	if(::Load(f,MaskNoisePinhole		)==false)	return false;
	if(::Load(f,MaskNoiseSmallDot		)==false)	return false;
	if(LimitedLib.Load(f)==false)	return false;

	if(::Load(f,Mask2AutoPickupRL		)==false)	return false;
	if(::Load(f,Mask2AutoPickupRH		)==false)	return false;
	if(::Load(f,Mask2AutoPickupGL		)==false)	return false;
	if(::Load(f,Mask2AutoPickupGH		)==false)	return false;
	if(::Load(f,Mask2AutoPickupBL		)==false)	return false;
	if(::Load(f,Mask2AutoPickupBH		)==false)	return false;
	if(::Load(f,Mask2AutoMinPickupSize	)==false)	return false;
	if(::Load(f,Mask2AutoMaxPickupSize	)==false)	return false;
	if(::Load(f,Mask2AutoMinPickupDots	)==false)	return false;
	if(::Load(f,Mask2AutoMaxPickupDots	)==false)	return false;
	if(::Load(f,Mask2AutoErosion		)==false)	return false;
	if(::Load(f,Mask2AutoOutsideXPos	)==false)	return false;
	if(::Load(f,Mask2AutoOutsideYPos	)==false)	return false;
	if(::Load(f,Mask2NoisePinhole		)==false)	return false;
	if(::Load(f,Mask2NoiseSmallDot		)==false)	return false;

	if(::Load(f,Mask3AutoPickupRL		)==false)	return false;
	if(::Load(f,Mask3AutoPickupRH		)==false)	return false;
	if(::Load(f,Mask3AutoPickupGL		)==false)	return false;
	if(::Load(f,Mask3AutoPickupGH		)==false)	return false;
	if(::Load(f,Mask3AutoPickupBL		)==false)	return false;
	if(::Load(f,Mask3AutoPickupBH		)==false)	return false;
	if(::Load(f,Mask3AutoMinPickupSize	)==false)	return false;
	if(::Load(f,Mask3AutoMaxPickupSize	)==false)	return false;
	if(::Load(f,Mask3AutoMinPickupDots	)==false)	return false;
	if(::Load(f,Mask3AutoMaxPickupDots	)==false)	return false;
	if(::Load(f,Mask3AutoErosion		)==false)	return false;
	if(::Load(f,Mask3AutoOutsideXPos	)==false)	return false;
	if(::Load(f,Mask3AutoOutsideYPos	)==false)	return false;
	if(::Load(f,Mask3NoisePinhole		)==false)	return false;
	if(::Load(f,Mask3NoiseSmallDot		)==false)	return false;

	if(::Load(f,Mask4AutoPickupRL		)==false)	return false;
	if(::Load(f,Mask4AutoPickupRH		)==false)	return false;
	if(::Load(f,Mask4AutoPickupGL		)==false)	return false;
	if(::Load(f,Mask4AutoPickupGH		)==false)	return false;
	if(::Load(f,Mask4AutoPickupBL		)==false)	return false;
	if(::Load(f,Mask4AutoPickupBH		)==false)	return false;
	if(::Load(f,Mask4AutoMinPickupSize	)==false)	return false;
	if(::Load(f,Mask4AutoMaxPickupSize	)==false)	return false;
	if(::Load(f,Mask4AutoMinPickupDots	)==false)	return false;
	if(::Load(f,Mask4AutoMaxPickupDots	)==false)	return false;
	if(::Load(f,Mask4AutoErosion		)==false)	return false;
	if(::Load(f,Mask4AutoOutsideXPos	)==false)	return false;
	if(::Load(f,Mask4AutoOutsideYPos	)==false)	return false;
	if(::Load(f,Mask4NoisePinhole		)==false)	return false;
	if(::Load(f,Mask4NoiseSmallDot		)==false)	return false;

	if (::Load(f, OmitX1	) == false)	return false;
	if (::Load(f, OmitY1	) == false)	return false;
	if (::Load(f, OmitX2	) == false)	return false;
	if (::Load(f, OmitY2	) == false)	return false;

	if (::Load(f, BladeAreaX1) == false)	return false;
	if (::Load(f, BladeAreaY1) == false)	return false;
	if (::Load(f, BladeAreaX2) == false)	return false;
	if (::Load(f, BladeAreaY2) == false)	return false;
	return true;
}
bool	IntegrationCmdAutoPickup::Save(QIODevice *f)
{
	if(::Save(f,MaskAutoPickupRL		)==false)	return false;
	if(::Save(f,MaskAutoPickupRH		)==false)	return false;
	if(::Save(f,MaskAutoPickupGL		)==false)	return false;
	if(::Save(f,MaskAutoPickupGH		)==false)	return false;
	if(::Save(f,MaskAutoPickupBL		)==false)	return false;
	if(::Save(f,MaskAutoPickupBH		)==false)	return false;
	if(::Save(f,MaskAutoLayer			)==false)	return false;
	if(::Save(f,MaskAutoMinPickupSize	)==false)	return false;
	if(::Save(f,MaskAutoMaxPickupSize	)==false)	return false;
	if(::Save(f,MaskAutoMinPickupDots	)==false)	return false;
	if(::Save(f,MaskAutoMaxPickupDots	)==false)	return false;
	if(::Save(f,MaskAutoErosion			)==false)	return false;
	if(::Save(f,LocalX					)==false)	return false;
	if(::Save(f,LocalY					)==false)	return false;
	if(::Save(f,MaskAutoExcludeLeftX	)==false)	return false;
	if(::Save(f,MaskAutoExcludeRightX	)==false)	return false;
	if(::Save(f,BladeHoleMinArea		)==false)	return false;
	if(::Save(f,BladeHoleErosionDot		)==false)	return false;
	if(::Save(f,MaskNoisePinhole		)==false)	return false;
	if(::Save(f,MaskNoiseSmallDot		)==false)	return false;
	if(LimitedLib.Save(f)==false)	return false;

	if(::Save(f,Mask2AutoPickupRL		)==false)	return false;
	if(::Save(f,Mask2AutoPickupRH		)==false)	return false;
	if(::Save(f,Mask2AutoPickupGL		)==false)	return false;
	if(::Save(f,Mask2AutoPickupGH		)==false)	return false;
	if(::Save(f,Mask2AutoPickupBL		)==false)	return false;
	if(::Save(f,Mask2AutoPickupBH		)==false)	return false;
	if(::Save(f,Mask2AutoMinPickupSize	)==false)	return false;
	if(::Save(f,Mask2AutoMaxPickupSize	)==false)	return false;
	if(::Save(f,Mask2AutoMinPickupDots	)==false)	return false;
	if(::Save(f,Mask2AutoMaxPickupDots	)==false)	return false;
	if(::Save(f,Mask2AutoErosion		)==false)	return false;
	if(::Save(f,Mask2AutoOutsideXPos	)==false)	return false;
	if(::Save(f,Mask2AutoOutsideYPos	)==false)	return false;
	if(::Save(f,Mask2NoisePinhole		)==false)	return false;
	if(::Save(f,Mask2NoiseSmallDot		)==false)	return false;

	if(::Save(f,Mask3AutoPickupRL		)==false)	return false;
	if(::Save(f,Mask3AutoPickupRH		)==false)	return false;
	if(::Save(f,Mask3AutoPickupGL		)==false)	return false;
	if(::Save(f,Mask3AutoPickupGH		)==false)	return false;
	if(::Save(f,Mask3AutoPickupBL		)==false)	return false;
	if(::Save(f,Mask3AutoPickupBH		)==false)	return false;
	if(::Save(f,Mask3AutoMinPickupSize	)==false)	return false;
	if(::Save(f,Mask3AutoMaxPickupSize	)==false)	return false;
	if(::Save(f,Mask3AutoMinPickupDots	)==false)	return false;
	if(::Save(f,Mask3AutoMaxPickupDots	)==false)	return false;
	if(::Save(f,Mask3AutoErosion		)==false)	return false;
	if(::Save(f,Mask3AutoOutsideXPos	)==false)	return false;
	if(::Save(f,Mask3AutoOutsideYPos	)==false)	return false;
	if(::Save(f,Mask3NoisePinhole		)==false)	return false;
	if(::Save(f,Mask3NoiseSmallDot		)==false)	return false;

	if(::Save(f,Mask4AutoPickupRL		)==false)	return false;
	if(::Save(f,Mask4AutoPickupRH		)==false)	return false;
	if(::Save(f,Mask4AutoPickupGL		)==false)	return false;
	if(::Save(f,Mask4AutoPickupGH		)==false)	return false;
	if(::Save(f,Mask4AutoPickupBL		)==false)	return false;
	if(::Save(f,Mask4AutoPickupBH		)==false)	return false;
	if(::Save(f,Mask4AutoMinPickupSize	)==false)	return false;
	if(::Save(f,Mask4AutoMaxPickupSize	)==false)	return false;
	if(::Save(f,Mask4AutoMinPickupDots	)==false)	return false;
	if(::Save(f,Mask4AutoMaxPickupDots	)==false)	return false;
	if(::Save(f,Mask4AutoErosion		)==false)	return false;
	if(::Save(f,Mask4AutoOutsideXPos	)==false)	return false;
	if(::Save(f,Mask4AutoOutsideYPos	)==false)	return false;
	if(::Save(f,Mask4NoisePinhole		)==false)	return false;
	if(::Save(f,Mask4NoiseSmallDot		)==false)	return false;

	if(::Save(f,OmitX1	) == false)	return false;
	if(::Save(f,OmitY1	) == false)	return false;
	if(::Save(f,OmitX2	) == false)	return false;
	if(::Save(f,OmitY2	) == false)	return false;
	if(::Save(f, BladeAreaX1) == false)	return false;
	if(::Save(f, BladeAreaY1) == false)	return false;
	if(::Save(f, BladeAreaX2) == false)	return false;
	if(::Save(f, BladeAreaY2) == false)	return false;

	return true;
}

void	IntegrationCmdAutoPickup::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyMaskingForm",/**/"");
	if(Form!=NULL){
		if(LocalX>=0 && LocalY>=0){
			CmdPourAreaPacket	Cmd(GetLayersBase());

			IntList	LayerList;
			for(int Layer=0;Layer<GetLayersBase()->GetMaxLayerNumb();Layer++){
				LayerList.Add(Layer);
			}

			Cmd.LayerList	=LayerList;
			Cmd.PickupRL	=MaskAutoPickupRL;
			Cmd.PickupRH	=MaskAutoPickupRH;
			Cmd.PickupGL	=MaskAutoPickupGL;
			Cmd.PickupGH	=MaskAutoPickupGH;
			Cmd.PickupBL	=MaskAutoPickupBL;
			Cmd.PickupBH	=MaskAutoPickupBH;
			Cmd.LocalX		=LocalX;
			Cmd.LocalY		=LocalY;
			Cmd.Effective	=true;
			Cmd.Exclusive	=true;

			Cmd.ExpandedDot	=MaskAutoErosion;
			Cmd.MinDot		=MaskAutoMinPickupDots;
			Cmd.MinSize		=MaskAutoMinPickupSize;
			Cmd.LimitedLib	=LimitedLib;
			Cmd.OmitX1		=OmitX1;
			Cmd.OmitY1		=OmitY1;
			Cmd.OmitX2		=OmitX2;
			Cmd.OmitY2		=OmitY2;
			Cmd.NoisePinhole	=MaskNoisePinhole	;
			Cmd.NoiseSmallDot	=MaskNoiseSmallDot	;

			Form->TransmitDirectly(&Cmd);
		}
		else{
			CmdPickupAreaPacket	Cmd(GetLayersBase());

			IntList	LayerList;
			for(int Layer=0;Layer<GetLayersBase()->GetMaxLayerNumb();Layer++){
				LayerList.Add(Layer);
			}

			Cmd.LayerList	=LayerList;
			Cmd.PickupRL	=MaskAutoPickupRL;
			Cmd.PickupRH	=MaskAutoPickupRH;
			Cmd.PickupGL	=MaskAutoPickupGL;
			Cmd.PickupGH	=MaskAutoPickupGH;
			Cmd.PickupBL	=MaskAutoPickupBL;
			Cmd.PickupBH	=MaskAutoPickupBH;
			Cmd.Effective	=true;
			Cmd.ExpandedDot	=MaskAutoErosion;
			Cmd.MinSize		=MaskAutoMinPickupSize;
			//Cmd.MinDot		=MaskAutoMinPickupDots;
			Cmd.LimitedLib	=LimitedLib;
			Cmd.HoleMinArea		=BladeHoleMinArea	;
			Cmd.HoleErosionDot	=BladeHoleErosionDot;
			//Cmd.NoisePinhole	=MaskNoisePinhole	;
			//Cmd.NoiseSmallDot	=MaskNoiseSmallDot	;
			Cmd.AreaX1		=BladeAreaX1;
			Cmd.AreaY1		=BladeAreaY1;
			Cmd.AreaX2		=BladeAreaX2;
			Cmd.AreaY2		=BladeAreaY2;

			Form->TransmitDirectly(&Cmd);
		}
	}
}

IntegrationCmdReqLibrary::IntegrationCmdReqLibrary(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationCmdReqLibrary::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckLibrary	*SendBack=GetSendBackIntegration(IntegrationCmdAckLibrary,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(ABase!=NULL && ABase->GetLibraryContainer()!=NULL){
		ABase->GetLibraryContainer()->EnumLibrary(SendBack->LibContainer);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckLibrary::IntegrationCmdAckLibrary(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdAckLibrary::Load(QIODevice *f)
{
	if(LibContainer.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationCmdAckLibrary::Save(QIODevice *f)
{
	if(LibContainer.Save(f)==false)
		return false;
	return true;
}
//============================================================================
IntegrationDeleteAllMask::IntegrationDeleteAllMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationDeleteAllMask::Load(QIODevice *f)
{
	if(::Load(f,DeleteManualItems	)==false)	return false;
	if(::Load(f,DeleteCADItems		)==false)	return false;
	return true;
}
bool	IntegrationDeleteAllMask::Save(QIODevice *f)
{
	if(::Save(f,DeleteManualItems	)==false)	return false;
	if(::Save(f,DeleteCADItems		)==false)	return false;
	return true;
}

void	IntegrationDeleteAllMask::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection",/**/"MaskingImagePanel",/**/"");
	if(f!=NULL){
		{
			QStringList Args;
			bool ExeReturn;
			Args.append(/**/"true");
			Args.append((DeleteManualItems==true)?/**/"true":/**/"false");
			Args.append((DeleteCADItems==true)?/**/"true":/**/"false");
			Args.append(/**/"false");
			f->ExecuteMacro(/**/"SelectItems", Args, ExeReturn);
		}
		{
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"DeleteItems", Args, ExeReturn);
		}
	}
	SendAck(slaveNo);
}
//============================================================================
IntegrationDeleteOnlyCADMask::IntegrationDeleteOnlyCADMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}


void	IntegrationDeleteOnlyCADMask::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection",/**/"MaskingImagePanel",/**/"");
	if(f!=NULL){
		{
			QStringList Args;
			bool ExeReturn;
			Args.append(/**/"false");
			Args.append(/**/"false");
			Args.append(/**/"true");
			Args.append(/**/"false");
			f->ExecuteMacro(/**/"SelectItems", Args, ExeReturn);
		}
		{
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"DeleteItems", Args, ExeReturn);
		}
	}
}
//============================================================================
IntegrationCmdReqMaskCount::IntegrationCmdReqMaskCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationCmdReqMaskCount::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckMaskCount	*SendBack=GetSendBackIntegration(IntegrationCmdAckMaskCount,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyMaskingForm",/**/"");
	if(f!=NULL){
		CmdReqUsedLimitedMaskCount	RCmd(GetLayersBase());
		f->TransmitDirectly(&RCmd);
		SendBack->MaskContainer=RCmd.MaskContainer;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckMaskCount::IntegrationCmdAckMaskCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdAckMaskCount::Load(QIODevice *f)
{
	if(MaskContainer.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationCmdAckMaskCount::Save(QIODevice *f)
{
	if(MaskContainer.Save(f)==false)
		return false;
	return true;
}
//============================================================================
IntegrationMakeEffectiveFromCAD::IntegrationMakeEffectiveFromCAD(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationMakeEffectiveFromCAD::Load(QIODevice *f)
{
	if(::Load(f,ShrinkDot)==false)
		return false;
	return true;
}
bool	IntegrationMakeEffectiveFromCAD::Save(QIODevice *f)
{
	if(::Save(f,ShrinkDot)==false)
		return false;
	return true;
}
void	IntegrationMakeEffectiveFromCAD::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyDXFOperation",/**/"");
	if(f!=NULL){
		CmdMakeEffectiveMask	RCmd(GetLayersBase());
		RCmd.ShrinkDot	=ShrinkDot;
		f->TransmitDirectly(&RCmd);
	}
}

//============================================================================

IntegrationGenerateOutlineArea::IntegrationGenerateOutlineArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationGenerateOutlineArea::Load(QIODevice *f)
{
	if(::Load(f,Expansion)==false)
		return false;
	if(::Load(f,InsideDot)==false)
		return false;
	if(::Load(f,OutsideDot)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationGenerateOutlineArea::Save(QIODevice *f)
{
	if(::Save(f,Expansion)==false)
		return false;
	if(::Save(f,InsideDot)==false)
		return false;
	if(::Save(f,OutsideDot)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	return true;
}

void	IntegrationGenerateOutlineArea::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DisplayImageWithAlgorithm	*h=(DisplayImageWithAlgorithm *)GetLayersBase()->FindByName(/**/"Inspection",/**/"MaskingImagePanel",/**/"");
	if(h!=NULL){
		h->SlotSelectAll();
	}

	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyMaskingForm",/**/"");
	if(f!=NULL){
		CmdGenerateMaskOnSelectedItemsEdge		RCmd(GetLayersBase());
		RCmd.Effective	=true;
		RCmd.LimitedLib	=LimitedLib	;
		RCmd.Expansion	=Expansion	;
		RCmd.InsideDot	=InsideDot	;
		RCmd.OutsideDot	=OutsideDot	;
		f->TransmitDirectly(&RCmd);
	}
}
//============================================================================

IntegrationCreatePatternEdge::IntegrationCreatePatternEdge(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCreatePatternEdge::Load(QIODevice *f)
{
	if(::Load(f,BoundaryDiff)==false)
		return false;
	if(::Load(f,WidthDot)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationCreatePatternEdge::Save(QIODevice *f)
{
	if(::Save(f,BoundaryDiff)==false)
		return false;
	if(::Save(f,WidthDot)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	return true;
}

void	IntegrationCreatePatternEdge::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DisplayImageWithAlgorithm	*h=(DisplayImageWithAlgorithm *)GetLayersBase()->FindByName(/**/"Inspection",/**/"MaskingImagePanel",/**/"");
	if(h!=NULL){
		h->SlotSelectAll();
	}

	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyMaskingForm",/**/"");
	if(f!=NULL){
		CmdGeneratePatternEdgeOnSelected		RCmd(GetLayersBase());
		RCmd.Effective	=true;
		RCmd.LimitedLib	=LimitedLib	;
		RCmd.BoundaryDiff	=BoundaryDiff	;
		RCmd.WidthDot		=WidthDot	;
		f->TransmitDirectly(&RCmd);
	}
}

//============================================================================

IntegrationSetItemSelection::IntegrationSetItemSelection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationSetItemSelection::Load(QIODevice *f)
{
	if(::Load(f,Effective)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationSetItemSelection::Save(QIODevice *f)
{
	if(::Save(f,Effective)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	return true;
}

void	IntegrationSetItemSelection::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyMaskingForm",/**/"");
	if(f!=NULL){
		CmdSetItemSelection		RCmd(GetLayersBase());
		RCmd.Effective	=true;
		RCmd.LimitedLib	=LimitedLib	;
		f->TransmitDirectly(&RCmd);
	}
}
