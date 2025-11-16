#include "SetAlignmentOffsetForm.h"
#include "ui_SetAlignmentOffsetForm.h"
#include "ButtonAlignmentOffset.h"

extern  const	char	*sRoot;
extern  const	char	*sName;

SetAlignmentOffsetForm::SetAlignmentOffsetForm(LayersBase *base ,ButtonAlignmentOffset *p,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(base)
    ,Parent(p)
    ,ui(new Ui::SetAlignmentOffsetForm)
{
    ui->setupUi(this);

    if(GetPageNumb()<=1){
        delete  ui->labelPage;
        ui->labelPage=NULL;
        delete  ui->listWidgetPageList;
        ui->listWidgetPageList=NULL;
    }

    ui->horizontalSliderX->setMinimum(-Parent->MaxOffsetXDot);
    ui->horizontalSliderX->setMaximum( Parent->MaxOffsetXDot);
    ui->spinBoxOffsetX  ->setMinimum(-Parent->MaxOffsetXDot);
    ui->spinBoxOffsetX  ->setMaximum( Parent->MaxOffsetXDot);
    double  UnitMMX=GetParamGlobal()->TransformPixelToUnit(-1,Parent->MaxOffsetXDot);
    ui->doubleSpinBoxOffsetXMM->setMinimum(-UnitMMX);
    ui->doubleSpinBoxOffsetXMM->setMaximum( UnitMMX);

    ui->verticalSliderY->setMinimum(-Parent->MaxOffsetYDot);
    ui->verticalSliderY->setMaximum( Parent->MaxOffsetYDot);
    ui->spinBoxOffsetY  ->setMinimum(-Parent->MaxOffsetXDot);
    ui->spinBoxOffsetY  ->setMaximum( Parent->MaxOffsetXDot);
    double  UnitMMY=GetParamGlobal()->TransformPixelToUnit(-1,Parent->MaxOffsetYDot);
    ui->doubleSpinBoxOffsetYMM->setMinimum(-UnitMMY);
    ui->doubleSpinBoxOffsetYMM->setMaximum( UnitMMY);

    ui->labelUnitX  ->setText(GetParamGlobal()->UnitName);
    ui->labelUnitY  ->setText(GetParamGlobal()->UnitName);

    ReqOffset(0);
}

SetAlignmentOffsetForm::~SetAlignmentOffsetForm()
{
    delete ui;
}

void SetAlignmentOffsetForm::on_horizontalSliderX_valueChanged(int value)
{
    int Page=ui->listWidgetPageList->currentRow();
    ui->spinBoxOffsetX          ->blockSignals(true);
    ui->doubleSpinBoxOffsetXMM  ->blockSignals(true);
    ui->horizontalSliderX       ->blockSignals(true);

    int v=ui->horizontalSliderX ->value();
    ui->spinBoxOffsetX          ->setValue(v);   
    ui->doubleSpinBoxOffsetXMM  ->setValue(GetParamGlobal()->TransformPixelToUnit(Page,v));

    ui->spinBoxOffsetX          ->blockSignals(false);
    ui->doubleSpinBoxOffsetXMM  ->blockSignals(false);
    ui->horizontalSliderX       ->blockSignals(false);
    SendOffset();
}


void SetAlignmentOffsetForm::on_spinBoxOffsetX_valueChanged(int arg1)
{
    int Page=ui->listWidgetPageList->currentRow();
    ui->spinBoxOffsetX          ->blockSignals(true);
    ui->doubleSpinBoxOffsetXMM  ->blockSignals(true);
    ui->horizontalSliderX       ->blockSignals(true);

    int v=ui->spinBoxOffsetX    ->value();
    ui->horizontalSliderX       ->setValue(v);   
    ui->doubleSpinBoxOffsetXMM  ->setValue(GetParamGlobal()->TransformPixelToUnit(Page,v));

    ui->spinBoxOffsetX          ->blockSignals(false);
    ui->doubleSpinBoxOffsetXMM  ->blockSignals(false);
    ui->horizontalSliderX       ->blockSignals(false);
    SendOffset();
}


void SetAlignmentOffsetForm::on_doubleSpinBoxOffsetXMM_valueChanged(double arg1)
{
    int Page=ui->listWidgetPageList->currentRow();
    ui->spinBoxOffsetX          ->blockSignals(true);
    ui->doubleSpinBoxOffsetXMM  ->blockSignals(true);
    ui->horizontalSliderX       ->blockSignals(true);

    double v=ui->doubleSpinBoxOffsetXMM->value();
    int Dot=GetParamGlobal()->TransformUnitToPixel(Page,v);
    ui->spinBoxOffsetX      ->setValue(Dot);
    ui->horizontalSliderX   ->setValue(Dot);

    ui->spinBoxOffsetX          ->blockSignals(false);
    ui->doubleSpinBoxOffsetXMM  ->blockSignals(false);
    ui->horizontalSliderX       ->blockSignals(false);
    SendOffset();
}


void SetAlignmentOffsetForm::on_verticalSliderY_valueChanged(int value)
{
    int Page=ui->listWidgetPageList->currentRow();
    ui->spinBoxOffsetY          ->blockSignals(true);
    ui->doubleSpinBoxOffsetYMM  ->blockSignals(true);
    ui->verticalSliderY         ->blockSignals(true);

    int v=ui->verticalSliderY   ->value();
    ui->spinBoxOffsetY          ->setValue(v);   
    ui->doubleSpinBoxOffsetYMM  ->setValue(GetParamGlobal()->TransformPixelToUnit(Page,v));

    ui->spinBoxOffsetY          ->blockSignals(false);
    ui->doubleSpinBoxOffsetYMM  ->blockSignals(false);
    ui->verticalSliderY         ->blockSignals(false);
    SendOffset();
}


void SetAlignmentOffsetForm::on_spinBoxOffsetY_valueChanged(int arg1)
{
    int Page=ui->listWidgetPageList->currentRow();
    ui->spinBoxOffsetY          ->blockSignals(true);
    ui->doubleSpinBoxOffsetYMM  ->blockSignals(true);
    ui->verticalSliderY         ->blockSignals(true);

    int v=ui->spinBoxOffsetY    ->value();
    ui->verticalSliderY         ->setValue(v);   
    ui->doubleSpinBoxOffsetYMM  ->setValue(GetParamGlobal()->TransformPixelToUnit(Page,v));

    ui->spinBoxOffsetY          ->blockSignals(false);
    ui->doubleSpinBoxOffsetYMM  ->blockSignals(false);
    ui->verticalSliderY         ->blockSignals(false);
    SendOffset();
}


void SetAlignmentOffsetForm::on_doubleSpinBoxOffsetYMM_valueChanged(double arg1)
{
    int Page=ui->listWidgetPageList->currentRow();
    ui->spinBoxOffsetY          ->blockSignals(true);
    ui->doubleSpinBoxOffsetYMM  ->blockSignals(true);
    ui->verticalSliderY         ->blockSignals(true);

    double v=ui->doubleSpinBoxOffsetYMM->value();
    int Dot=GetParamGlobal()->TransformUnitToPixel(Page,v);
    ui->spinBoxOffsetY      ->setValue(Dot);
    ui->verticalSliderY     ->setValue(Dot);

    ui->spinBoxOffsetY          ->blockSignals(false);
    ui->doubleSpinBoxOffsetYMM  ->blockSignals(false);
    ui->verticalSliderY         ->blockSignals(false);
    SendOffset();
}


void SetAlignmentOffsetForm::on_pushButtonOK_clicked()
{
    Parent->Window=NULL;
    close();
}


void SetAlignmentOffsetForm::on_listWidgetPageList_itemSelectionChanged()
{
    int Page=ui->listWidgetPageList->currentRow();
    ReqOffset(Page);
}


void SetAlignmentOffsetForm::on_listWidgetPageList_clicked(const QModelIndex &index)
{
    int Page=ui->listWidgetPageList->currentRow();
    ReqOffset(Page);
}

void    SetAlignmentOffsetForm::ReqOffset(int Page)
{
	GUICmdReqAlignmentOffset	RCmd(GetLayersBase(),sRoot,sName,Page);
	GUICmdAckAlignmentOffset    ACmd(GetLayersBase(),sRoot,sName,Page);

	if(RCmd.Send(Page,0,ACmd)==true){
		ui->spinBoxOffsetX->setValue(ACmd.OffsetX);
        on_spinBoxOffsetX_valueChanged(0);
		ui->spinBoxOffsetY->setValue(ACmd.OffsetY);
        on_spinBoxOffsetY_valueChanged(0);
    }
}

void    SetAlignmentOffsetForm::SendOffset(void)
{
    if(GetPageNumb()<=1){
        SendOffset(0);
    }
    else{
        int Page=ui->listWidgetPageList->currentRow();
        SendOffset(Page);
    }
}

void    SetAlignmentOffsetForm::SendOffset(int Page)
{
    GUICmdSetAlignmentOffset	SCmd(GetLayersBase(),sRoot,sName,Page);
    SCmd.OffsetX    =ui->spinBoxOffsetX->value();
    SCmd.OffsetY    =ui->spinBoxOffsetY->value();
    SCmd.Send(NULL,Page,0);
}
