#include "EasyPropertyMaskingResource.h"
#include "CreateOutlineDialog.h"
#include "ui_CreateOutlineDialog.h"
#include "SelectLibrariesForAnyType.h"
#include "XParamDatabase.h"
#include "XDLLOnly.h"
#include "XRememberer.h"

CreateOutlineDialog::CreateOutlineDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::CreateOutlineDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
	LangSolver.SetUI(this);

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

CreateOutlineDialog::~CreateOutlineDialog()
{
    delete ui;
}
void CreateOutlineDialog::resizeEvent(QResizeEvent *event)
{
	ui->frame->setGeometry(0,height()-ui->frame->height()
							,width(),ui->frame->height());
	ui->frameLibrary->resize(width(),height()-ui->frame->height());

	Libs->setGeometry(0,0,ui->frameLibrary->width(),ui->frameLibrary->height());
}

void CreateOutlineDialog::on_pushButtonGenerate_clicked()
{
	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Save(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);

	Expansion	=ControlRememberer::SetValue(ui->spinBoxExpansion);
	InsideDot	=ControlRememberer::SetValue(ui->spinBoxInsideDot);
	OutsideDot	=ControlRememberer::SetValue(ui->spinBoxOutsideDot);

	done(true);
}


void CreateOutlineDialog::on_pushButtonCancel_clicked()
{
	done(false);
}


AlgorithmLibraryListContainer	CreateOutlineDialog::GetSelectedList(void)
{
	return Libs->SelectedList;
}

void CreateOutlineDialog::on_spinBoxInsideDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	double	m=GetParamGlobal()->TransformPixelToUnit(-1,ui->spinBoxInsideDot->value());
	ui->doubleSpinBoxInsideMM->setValue(m);
	OnChanging=false;
}


void CreateOutlineDialog::on_doubleSpinBoxInsideMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	double	m=GetParamGlobal()->TransformUnitToPixel(-1,ui->doubleSpinBoxInsideMM->value());
	ui->spinBoxInsideDot->setValue((int)m);
	OnChanging=false;
}


void CreateOutlineDialog::on_spinBoxOutsideDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	double	m=GetParamGlobal()->TransformPixelToUnit(-1,ui->spinBoxOutsideDot->value());
	ui->doubleSpinBoxOutsideMM->setValue(m);
	OnChanging=false;
}


void CreateOutlineDialog::on_doubleSpinBoxOutsideMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	double	m=GetParamGlobal()->TransformUnitToPixel(-1,ui->doubleSpinBoxOutsideMM->value());
	ui->spinBoxOutsideDot->setValue((int)m);
	OnChanging=false;
}

