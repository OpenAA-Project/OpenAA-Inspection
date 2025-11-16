#include "SearchLotDialog.h"
#include "ui_SearchLotDialog.h"
#include "PQSystemService.h"

SearchLotDialog::SearchLotDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::SearchLotDialog)
{
    ui->setupUi(this);

	LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
	ui->pushButtonTitleLotID	->setText(LBase->GetParamPQSystem()->TitleLotID);
	ui->pushButtonTitleLotNumber->setText(LBase->GetParamPQSystem()->TitleLotNumber);
	ui->pushButtonTitleSubCode	->setText(LBase->GetParamPQSystem()->TitleSubCode);
}

SearchLotDialog::~SearchLotDialog()
{
    delete ui;
}

void SearchLotDialog::on_pushButtonSelect_clicked()
{
	SelectedLotID		=ui->lineEditLotID		->text();
	SelectedLotNumber	=ui->lineEditLotNumber	->text();
	SelectedSubCode	    =ui->lineEditSubCode	->text();

	done(true);
}
