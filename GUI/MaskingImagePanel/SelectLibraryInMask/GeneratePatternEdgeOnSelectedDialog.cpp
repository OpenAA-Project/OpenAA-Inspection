#include "GeneratePatternEdgeOnSelectedDialog.h"
#include "ui_GeneratePatternEdgeOnSelectedDialog.h"
#include "SelectLibrariesForAnyType.h"
#include "XParamDatabase.h"
#include "XDLLOnly.h"
#include "XRememberer.h"

GeneratePatternEdgeOnSelectedDialog::GeneratePatternEdgeOnSelectedDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::GeneratePatternEdgeOnSelectedDialog)
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

	ui->spinBoxBoundaryDiff	->setValue(ControlRememberer::GetInt(ui->spinBoxBoundaryDiff));
	ui->spinBoxWidthDot		->setValue(ControlRememberer::GetInt(ui->spinBoxWidthDot));

	InstallOperationLog(this);
}

GeneratePatternEdgeOnSelectedDialog::~GeneratePatternEdgeOnSelectedDialog()
{
    delete ui;
}
void GeneratePatternEdgeOnSelectedDialog::resizeEvent(QResizeEvent *event)
{
	ui->frame->setGeometry(0,height()-ui->frame->height()
							,width(),ui->frame->height());
	ui->frameLibrary->resize(width(),height()-ui->frame->height());

	Libs->setGeometry(0,0,ui->frameLibrary->width(),ui->frameLibrary->height());
}
void GeneratePatternEdgeOnSelectedDialog::on_ButtonEffective_clicked()
{
	Effective=true;
	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Save(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);

	BoundaryDiff=ControlRememberer::SetValue(ui->spinBoxBoundaryDiff);
	WidthDot	=ControlRememberer::SetValue(ui->spinBoxWidthDot);

	done(true);
}


void GeneratePatternEdgeOnSelectedDialog::on_ButtonNotEffective_clicked()
{
	Effective=false;
	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Save(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);

	BoundaryDiff=ControlRememberer::SetValue(ui->spinBoxBoundaryDiff);
	WidthDot	=ControlRememberer::SetValue(ui->spinBoxWidthDot);

	done(true);
}


void GeneratePatternEdgeOnSelectedDialog::on_ButtonCancel_clicked()
{
	done(false);
}

AlgorithmLibraryListContainer	GeneratePatternEdgeOnSelectedDialog::GetSelectedList(void)
{
	return Libs->SelectedList;
}

void GeneratePatternEdgeOnSelectedDialog::on_spinBoxWidthDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	double	m=GetParamGlobal()->TransformPixelToUnit(-1,ui->spinBoxWidthDot->value());
	ui->doubleSpinBoxWidthMM->setValue(m);
	OnChanging=false;
}


void GeneratePatternEdgeOnSelectedDialog::on_doubleSpinBoxWidthMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	double	m=GetParamGlobal()->TransformUnitToPixel(-1,ui->doubleSpinBoxWidthMM->value());
	ui->spinBoxWidthDot->setValue((int)m);
	OnChanging=false;
}

