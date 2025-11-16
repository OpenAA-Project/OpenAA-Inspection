#include "ButtonShowConfirmResource.h"
#include "ConfirmPropColorDifferenceForm.h"
#include "ui_ConfirmPropColorDifferenceForm.h"
#include "ConfirmForm.h"
#include "XIntegrationBase.h"
#include "XConfirmPacket.h"
#include "XColorDifferenceLibrary.h"
#include "XColorDifference.h"
#include "XPropPacketColorDifference.h"

ConfirmPropColorDifferenceForm::ConfirmPropColorDifferenceForm(ConfirmForm *p ,QWidget *parent) :
    ConfirmAlgorithm(p)
    ,ServiceForLayers(p->GetLayersBase())
   ,ui(new Ui::ConfirmPropColorDifferenceForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
}

ConfirmPropColorDifferenceForm::~ConfirmPropColorDifferenceForm()
{
    delete ui;
}

QString	ConfirmPropColorDifferenceForm::GetButtonName(void)
{
    return LangSolver.GetString(ConfirmPropColorDifferenceForm_LS,LID_10)/*"濶ｲ蟾ｮ"*/;
}
int		ConfirmPropColorDifferenceForm::GetLibType(void)
{   
    return DefLibTypeColorDifference;
}
void	ConfirmPropColorDifferenceForm::SetDrawAttr(AlgorithmLibTypeWithAttrDataContainer &s)
{
    s.Add(DefLibTypeColorDifference,false,true,true);
}

void	ConfirmPropColorDifferenceForm::InitialShow(void)
{
}
void	ConfirmPropColorDifferenceForm::AlgoMouseLDownWithShift(int ux ,int uy)
{
	GetItemsByPoint(ux, uy);
	ShowItemData();
	SetSelectItems();
	ShowResult();
}
void	ConfirmPropColorDifferenceForm::CanvasSlotDrawEnd(FlexArea &Area)
{
	ConfirmAlgorithm::CanvasSlotDrawEnd(Area);

	int	SlaveNo=GetSlaveNo();
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
    if(m!=NULL){
		GetItemsByArea(-1,Area);
		ShowItemData();
		SetSelectItems();
		ShowResult();
	}
}
void	ConfirmPropColorDifferenceForm::SetProperty(void)
{
	for(ListPhasePageLayerItem	*t=SelectedItems.GetFirst();t!=NULL;t=t->GetNext()){
		int	SlaveNo=GetSlaveNo();
		IntegrationReqColorDifferenceItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckColorDifferenceItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.LibType=GetLibType();
		RCmd.ItemIndex=*t;
		if(RCmd.Send(SlaveNo ,t->Data.Page,ACmd)==true){
			CmdCreateColorDifferenceThreshold	Cmd(GetLayersBase());
			AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
			if(ABase!=NULL){
				ABase->TransmitDirectly(&Cmd);
				QBuffer	Buff(&ACmd.ThresholdData);
				Buff.open(QIODevice::ReadWrite);
				Cmd.Threshold->Load(&Buff);
				GetThresholdFromWindow(Cmd.Threshold);
				Buff.seek(0);
				Cmd.Threshold->Save(&Buff);

				IntegrationSetColorDifferenceItemThresholdData	SCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				SCmd.LibType=GetLibType();
				SCmd.ItemIndex=*t;
				SCmd.ThresholdData=Buff.buffer();
				OutputConstantlyInItem=ACmd.OutputConstantlyInItem;
				SCmd.Send(NULL,SlaveNo ,t->Data.Page);
			}
		}
	}
}

void    ConfirmPropColorDifferenceForm::ShowThreshold(int LibID,ColorDifferenceThreshold *s)
{
	OnChanging=true;
    ui->doubleSpinBoxColorDifferenceAdoptedRate ->setValue(s->AdoptedRate);
    ui->checkBoxColorDifferenceOutputConstantly ->setChecked(OutputConstantlyInItem);
    ui->comboBoxColorDifferenceJudgeMethod      ->setCurrentIndex(s->JudgeMethod);

    ui->frameDeltaE ->setEnabled((s->JudgeMethod==1)?true:false);
    ui->frameHSV    ->setEnabled((s->JudgeMethod==2)?true:false);

    ui->doubleSpinBoxColorDifferenceTHDeltaE->setValue(s->THDeltaE);
    ui->doubleSpinBoxColorDifferencedH      ->setValue(s->dH);
    ui->doubleSpinBoxColorDifferencedSL     ->setValue(s->dSL);
    ui->doubleSpinBoxColorDifferencedSH     ->setValue(s->dSH);
    ui->doubleSpinBoxColorDifferencedVL     ->setValue(s->dVL);
    ui->doubleSpinBoxColorDifferencedVH     ->setValue(s->dVH);
	OnChanging=false;
}
void    ConfirmPropColorDifferenceForm::ShowItemData(void)
{
	ListPhasePageLayerItem	*t=SelectedItems.GetFirst();
	if(t!=NULL){
		int	SlaveNo=GetSlaveNo();
		IntegrationReqColorDifferenceItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckColorDifferenceItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.LibType=GetLibType();
		RCmd.ItemIndex=*t;
		if(RCmd.Send(SlaveNo ,t->Data.Page,ACmd)==true){
			CmdCreateColorDifferenceThreshold	Cmd(GetLayersBase());
			AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
			if(ABase!=NULL){
				ABase->TransmitDirectly(&Cmd);
				QBuffer	Buff(&ACmd.ThresholdData);
				Buff.open(QIODevice::ReadWrite);
				Cmd.Threshold->Load(&Buff);
                OutputConstantlyInItem=ACmd.OutputConstantlyInItem;
				ShowThreshold(ACmd.LibID,Cmd.Threshold);
			}
		}
	}
}

QString	ConvertColorToStr(PreciseColor &Col)
{
	return	 QString::number(Col.GetRed(),'f',1)
			+QString(/**/",")
			+QString::number(Col.GetGreen(),'f',1)
			+QString(/**/",")
			+QString::number(Col.GetBlue(),'f',1);
}
QString	ConvertColorToStr(double x, double y ,double z)
{
	return   QString::number(x,'f',1)
			+QString(/**/",")
			+QString::number(y,'f',1)
			+QString(/**/",")
			+QString::number(z,'f',1);
}
void	ConfirmPropColorDifferenceForm::ForceDraw(void)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void    ConfirmPropColorDifferenceForm::ShowResult(void)
{
   EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ListPhasePageLayerItem	*t=SelectedItems.GetFirst();
		if(t!=NULL){
			int	SlaveNo=GetSlaveNo();
			IntegrationReqColorDifferenceItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationAckColorDifferenceItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.LibType=GetLibType();
			RCmd.ItemIndex=*t;
			if(RCmd.Send(SlaveNo ,t->Data.Page,ACmd)==true){
				CmdCreateColorDifferenceThreshold	Cmd(GetLayersBase());
				AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
				if(ABase!=NULL){
					ABase->TransmitDirectly(&Cmd);
					QBuffer	Buff(&ACmd.ThresholdData);
					Buff.open(QIODevice::ReadWrite);
					Cmd.Threshold->Load(&Buff);
					GetThresholdFromWindow(Cmd.Threshold);

					Buff.seek(0);
					Cmd.Threshold->Save(&Buff);

					IntegrationReqColorDifferenceTryResult	RTryCmd(GetLayersBase(),sRoot,sName,SlaveNo);
					IntegrationAckColorDifferenceTryResult	ATryCmd(GetLayersBase(),sRoot,sName,SlaveNo);
					RTryCmd.ThresholdData=Buff.buffer();
					RTryCmd.ItemIndex=*t;
					if(RTryCmd.Send(SlaveNo ,t->Data.Page,ATryCmd)==true){

						ui->lineEditColorDifferenceDeltaE	->setText(QString::number(ATryCmd.DeltaE,'f',3));
						::SetDataToTable(ui->tableWidgetColorDifferenceResult,0,0,ConvertColorToStr(ATryCmd.ReferenceColor1));
						::SetDataToTable(ui->tableWidgetColorDifferenceResult,0,1,ConvertColorToStr(ATryCmd.ReferenceColor2));
						::SetDataToTable(ui->tableWidgetColorDifferenceResult,0,2,ConvertColorToStr(ATryCmd.MasterColor));
						::SetDataToTable(ui->tableWidgetColorDifferenceResult,0,3,ConvertColorToStr(ATryCmd.TargetColor));
						double	H,S,V;
						RGB2HSV(H,S,V	,ATryCmd.ReferenceColor1.GetRed()
										,ATryCmd.ReferenceColor1.GetGreen()
										,ATryCmd.ReferenceColor1.GetBlue());
						::SetDataToTable(ui->tableWidgetColorDifferenceResult,1,0,ConvertColorToStr(H,S,V));

						RGB2HSV(H,S,V	,ATryCmd.ReferenceColor2.GetRed()
										,ATryCmd.ReferenceColor2.GetGreen()
										,ATryCmd.ReferenceColor2.GetBlue());
						::SetDataToTable(ui->tableWidgetColorDifferenceResult,1,1,ConvertColorToStr(H,S,V));

						RGB2HSV(H,S,V	,ATryCmd.MasterColor.GetRed()
										,ATryCmd.MasterColor.GetGreen()
										,ATryCmd.MasterColor.GetBlue());
						::SetDataToTable(ui->tableWidgetColorDifferenceResult,1,2,ConvertColorToStr(H,S,V));
						//RGB2HSV(H,S,V ,R->TargetColor.GetRed(),R->TargetColor.GetGreen(),R->TargetColor.GetBlue());
						::SetDataToTable(ui->tableWidgetColorDifferenceResult,1,3,ConvertColorToStr( ATryCmd.StatisticData.TargetH
																									,ATryCmd.StatisticData.TargetS
																									,ATryCmd.StatisticData.TargetV));

						double	X,Y,Z;
						double	L,A,B;
						RGB2XYZ( ATryCmd.ReferenceColor1.Red.GetFloat()
								,ATryCmd.ReferenceColor1.Green.GetFloat()
								,ATryCmd.ReferenceColor1.Blue.GetFloat()
								,X ,Y ,Z);
						XYZ2LAB(X ,Y ,Z,L,A ,B);
						::SetDataToTable(ui->tableWidgetColorDifferenceResult,2,0,ConvertColorToStr(L,A,B));
						RGB2XYZ( ATryCmd.ReferenceColor2.Red.GetFloat()
								,ATryCmd.ReferenceColor2.Green.GetFloat()
								,ATryCmd.ReferenceColor2.Blue.GetFloat()
								,X ,Y ,Z);
						XYZ2LAB(X ,Y ,Z,L,A ,B);
						::SetDataToTable(ui->tableWidgetColorDifferenceResult,2,1,ConvertColorToStr(L,A,B));
						RGB2XYZ( ATryCmd.MasterColor.Red.GetFloat()
								,ATryCmd.MasterColor.Green.GetFloat()
								,ATryCmd.MasterColor.Blue.GetFloat()
								,X ,Y ,Z);
						XYZ2LAB(X ,Y ,Z,L,A ,B);
						::SetDataToTable(ui->tableWidgetColorDifferenceResult,2,2,ConvertColorToStr(L,A,B));
						RGB2XYZ( ATryCmd.TargetColor.Red.GetFloat()
								,ATryCmd.TargetColor.Green.GetFloat()
								,ATryCmd.TargetColor.Blue.GetFloat()
								,X ,Y ,Z);
						XYZ2LAB(X ,Y ,Z,L,A ,B);
						::SetDataToTable(ui->tableWidgetColorDifferenceResult,2,3,ConvertColorToStr(L,A,B));
					}
				}
			}
		}
	}
}

void    ConfirmPropColorDifferenceForm::GetThresholdFromWindow(ColorDifferenceThreshold *s)
{
    s->AdoptedRate          =ui->doubleSpinBoxColorDifferenceAdoptedRate ->value();
    OutputConstantlyInItem  =ui->checkBoxColorDifferenceOutputConstantly ->isChecked();
    s->JudgeMethod          =ui->comboBoxColorDifferenceJudgeMethod      ->currentIndex();

    if(s->JudgeMethod==1){
        s->THDeltaE =ui->doubleSpinBoxColorDifferenceTHDeltaE->value();
    }
    if(s->JudgeMethod==2){
        s->dH   =ui->doubleSpinBoxColorDifferencedH  ->value();
        s->dSL  =ui->doubleSpinBoxColorDifferencedSL ->value();
        s->dSH  =ui->doubleSpinBoxColorDifferencedSH ->value();
        s->dVL  =ui->doubleSpinBoxColorDifferencedVL ->value();
        s->dVH  =ui->doubleSpinBoxColorDifferencedVH ->value();
    }
}

void ConfirmPropColorDifferenceForm::on_doubleSpinBoxColorDifferenceAdoptedRate_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropColorDifferenceForm::on_checkBoxColorDifferenceOutputConstantly_clicked()
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropColorDifferenceForm::on_comboBoxColorDifferenceJudgeMethod_currentIndexChanged(int index)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropColorDifferenceForm::on_doubleSpinBoxColorDifferenceTHDeltaE_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropColorDifferenceForm::on_doubleSpinBoxColorDifferencedH_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropColorDifferenceForm::on_doubleSpinBoxColorDifferencedSL_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropColorDifferenceForm::on_doubleSpinBoxColorDifferencedSH_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropColorDifferenceForm::on_doubleSpinBoxColorDifferencedVL_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropColorDifferenceForm::on_doubleSpinBoxColorDifferencedVH_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}
void	ConfirmPropColorDifferenceForm::ShowConfirmItem(ConfirmItemList *Item)
{
	SelectedItems.RemoveAll();
	SelectedItems.Add(Item->Phase ,Item->Page ,Item->Layer,Item->ItemID);
	OnChanging=true;
	ShowItemData();
	ShowResult();
	OnChanging=false;
}
