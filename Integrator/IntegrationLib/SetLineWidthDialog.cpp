#include "ServiceLibResource.h"
#include "SetLineWidthDialog.h"
#include "ui_SetLineWidthDialog.h"
#include "XRememberer.h"

SetLineWidthDialog::SetLineWidthDialog(LayersBase *base ,int _SlaveNo
                                        ,int _LineWidth,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,SlaveNo(_SlaveNo)
    ,ui(new Ui::SetLineWidthDialog)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);
    ReEntrant   =false;
    LineWidth=_LineWidth;
    ui->spinBoxLineWidth    ->setValue(LineWidth);
}

SetLineWidthDialog::~SetLineWidthDialog()
{
    delete ui;
}

void SetLineWidthDialog::on_spinBoxLineWidth_valueChanged(int arg1)
{
    if(ReEntrant==true)
        return;
    ReEntrant=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
        int PixelCount=ui->spinBoxLineWidth->value();
        ui->doubleSpinBoxLineWidthMM->setValue(m->TransformPixelToUnit(PixelCount));
    }
    ReEntrant=false;
}


void SetLineWidthDialog::on_doubleSpinBoxLineWidthMM_valueChanged(double arg1)
{
    if(ReEntrant==true)
        return;
    ReEntrant=true;
    EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
        double UnitCount=ui->doubleSpinBoxLineWidthMM->value();
        ui->spinBoxLineWidth->setValue(m->TransformUnitToPixel(UnitCount));
    }
    ReEntrant=false;
}


void SetLineWidthDialog::on_pushButtonOK_clicked()
{
    LineWidth=ui->spinBoxLineWidth->value();
    done(true);
}


void SetLineWidthDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

