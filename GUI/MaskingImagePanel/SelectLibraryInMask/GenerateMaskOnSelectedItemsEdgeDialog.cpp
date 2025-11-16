#include "GenerateMaskOnSelectedItemsEdgeDialog.h"
#include "ui_GenerateMaskOnSelectedItemsEdgeDialog.h"
#include "SelectLibrariesForAnyType.h"
#include "XParamDatabase.h"
#include "XDLLOnly.h"
#include "XRememberer.h"

GenerateMaskOnSelectedItemsEdgeDialog::GenerateMaskOnSelectedItemsEdgeDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
	,ui(new Ui::GenerateMaskOnSelectedItemsEdgeDialog)
{
    ui->setupUi(this);

	OnChanging=false;

	Libs=new SelectLibrariesForAnyType(Base,this);
	Libs->setParent(ui->frameLibrary);
	Libs->setGeometry(0,0,ui->frameLibrary->width(),ui->frameLibrary->height());

	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Load(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);

	ui->labelMM1->setText(GetParamGlobal()->UnitName);
	ui->labelMM2->setText(GetParamGlobal()->UnitName);

	ui->spinBoxExpansion	->setValue(ControlRememberer::GetInt(ui->spinBoxExpansion));
	ui->spinBoxInsideDot	->setValue(ControlRememberer::GetInt(ui->spinBoxInsideDot));
	ui->spinBoxOutsideDot	->setValue(ControlRememberer::GetInt(ui->spinBoxOutsideDot));

	InstallOperationLog(this);
}

GenerateMaskOnSelectedItemsEdgeDialog::~GenerateMaskOnSelectedItemsEdgeDialog()
{
    delete ui;
}
void GenerateMaskOnSelectedItemsEdgeDialog::resizeEvent(QResizeEvent *event)
{
	ui->frame->setGeometry(0,height()-ui->frame->height()
							,width(),ui->frame->height());
	ui->frameLibrary->resize(width(),height()-ui->frame->height());

	Libs->setGeometry(0,0,ui->frameLibrary->width(),ui->frameLibrary->height());
}

void GenerateMaskOnSelectedItemsEdgeDialog::on_spinBoxInsideDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	double	m=GetParamGlobal()->TransformPixelToUnit(-1,ui->spinBoxInsideDot->value());
	ui->doubleSpinBoxInsideMM->setValue(m);
	OnChanging=false;
}

void GenerateMaskOnSelectedItemsEdgeDialog::on_doubleSpinBoxInsideMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	double	m=GetParamGlobal()->TransformUnitToPixel(-1,ui->doubleSpinBoxInsideMM->value());
	ui->spinBoxInsideDot->setValue((int)m);
	OnChanging=false;
}

void GenerateMaskOnSelectedItemsEdgeDialog::on_spinBoxOutsideDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	double	m=GetParamGlobal()->TransformPixelToUnit(-1,ui->spinBoxOutsideDot->value());
	ui->doubleSpinBoxOutsideMM->setValue(m);
	OnChanging=false;
}

void GenerateMaskOnSelectedItemsEdgeDialog::on_doubleSpinBoxOutsideMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	double	m=GetParamGlobal()->TransformUnitToPixel(-1,ui->doubleSpinBoxOutsideMM->value());
	ui->spinBoxOutsideDot->setValue((int)m);
	OnChanging=false;
}

void GenerateMaskOnSelectedItemsEdgeDialog::on_ButtonEffective_clicked()
{
	Effective=true;
	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Save(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);

	Expansion	=ControlRememberer::SetValue(ui->spinBoxExpansion);
	InsideDot	=ControlRememberer::SetValue(ui->spinBoxInsideDot);
	OutsideDot	=ControlRememberer::SetValue(ui->spinBoxOutsideDot);

	done(true);
}

void GenerateMaskOnSelectedItemsEdgeDialog::on_ButtonNotEffective_clicked()
{
	Effective=false;
	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Save(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);

	Expansion	=ControlRememberer::SetValue(ui->spinBoxExpansion);
	InsideDot	=ControlRememberer::SetValue(ui->spinBoxInsideDot);
	OutsideDot	=ControlRememberer::SetValue(ui->spinBoxOutsideDot);

	done(true);
}

void GenerateMaskOnSelectedItemsEdgeDialog::on_ButtonCancel_clicked()
{
	done(false);
}

AlgorithmLibraryListContainer	GenerateMaskOnSelectedItemsEdgeDialog::GetSelectedList(void)
{
	return Libs->SelectedList;
}