#include "EasyPropertyMeasureResource.h"
#include "SetSearchDotDialog.h"
#include "ui_SetSearchDotDialog.h"
#include "EasyPropertyMeasureForm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

SetSearchDotDialog::SetSearchDotDialog(LayersBase *Base ,EasyPropertyMeasureForm *p
                                ,int SearchDot ,int _Page
								,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,Parent(p)
    ,Page(_Page)
    ,ui(new Ui::SetSearchDotDialog)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    OnChanging=false;

    ui->spinBoxSearchDot->setValue(SearchDot);
    on_spinBoxSearchDot_valueChanged(0);
}

SetSearchDotDialog::~SetSearchDotDialog()
{
    delete ui;
}

void SetSearchDotDialog::on_spinBoxSearchDot_valueChanged(int arg1)
{
    if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixLength=ui->spinBoxSearchDot->value();
	ui->doubleSpinBoxSearchDotMM->setValue(GetParamGlobal()->TransformPixelToUnit(Page,PixLength));
	OnChanging=false;
}

void SetSearchDotDialog::on_doubleSpinBoxSearchDotMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixLength=GetParamGlobal()->TransformUnitToPixel(Page,ui->doubleSpinBoxSearchDotMM->value());
	ui->spinBoxSearchDot->setValue(PixLength);
	OnChanging=false;
}

void SetSearchDotDialog::on_pushButtonOK_clicked()
{
    RetSearchDot=ui->spinBoxSearchDot->value();
    done(1);
}

void SetSearchDotDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

void SetSearchDotDialog::on_pushButtonOKAll_clicked()
{
    RetSearchDot=ui->spinBoxSearchDot->value();
    done(2);
}
