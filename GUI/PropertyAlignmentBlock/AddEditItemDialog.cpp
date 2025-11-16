#include "AddEditItemDialog.h"
#include "ui_AddEditItemDialog.h"
#include "XDataInLayer.h"
#include "XAlignmentBlockLibrary.h"

AddEditItemDialog::AddEditItemDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::AddEditItemDialog)
{
    ui->setupUi(this);

    GetLayersBase()->InstallOperationLog(this);
}

AddEditItemDialog::~AddEditItemDialog()
{
    delete ui;
}

void AddEditItemDialog::Initial(AlgorithmLibrary *Lib)
{
    AlignmentBlockLibrary   *ALib=dynamic_cast<AlignmentBlockLibrary *>(Lib);
    if(ALib!=NULL){
        ui->spinBoxSearchDot		->setValue(ALib->SearchDot	);
        ui->doubleSpinBoxMaxDegree	->setValue(ALib->MaxDegree	);
        ui->spinBoxLineLength		->setValue(ALib->LineLength	);
        ui->doubleSpinBoxMinVar	    ->setValue(ALib->MinVar		);
    }
}

void AddEditItemDialog::on_pushButtonOK_clicked()
{
	SearchDot		=ui->spinBoxSearchDot		->value();
	MaxDegree		=ui->doubleSpinBoxMaxDegree	->value();
	LineLength		=ui->spinBoxLineLength		->value();
	MinVar			=ui->doubleSpinBoxMinVar	->value();

    done(true);
}

