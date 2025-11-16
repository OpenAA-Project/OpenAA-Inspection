#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "EditItemNameDialog.h"
#include "ui_EditItemNameDialog.h"
#include "XDataInLayer.h"

EditItemNameDialog::EditItemNameDialog(LayersBase *base ,const QString &itemname ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EditItemNameDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
	LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);

	InstallOperationLog(this);

	ItemName	=itemname;
	ui->lineEditItemName	->setText(ItemName);
}

EditItemNameDialog::~EditItemNameDialog()
{
    delete ui;
}

void EditItemNameDialog::on_pushButtonChange_clicked()
{
	ItemName	=ui->lineEditItemName	->text();
	done(true);
}

void EditItemNameDialog::on_pushButtonClose_clicked()
{
	done(false);
}
