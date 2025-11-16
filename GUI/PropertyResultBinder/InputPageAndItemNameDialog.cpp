#include "PropertyResultBinderFormResource.h"
#include "InputPageAndItemNameDialog.h"
#include "ui_InputPageAndItemNameDialog.h"

InputPageAndItemNameDialog::InputPageAndItemNameDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::InputPageAndItemNameDialog)
{
    ui->setupUi(this);

	for(int page=0;page<GetPageNumb();page++){
		ui->comboBoxPage->addItem(LangSolver.GetString(InputPageAndItemNameDialog_LS,LID_13)/*"Layer "*/+QString::number(page));
	}
	InstallOperationLog(this);
}

InputPageAndItemNameDialog::~InputPageAndItemNameDialog()
{
    delete ui;
}

void	InputPageAndItemNameDialog::Initial(const QString &ItemName)
{
	ui->lineEditItemName->setText(ItemName);
}
void InputPageAndItemNameDialog::on_pushButtonOK_clicked()
{
	Page	=ui->comboBoxPage->currentIndex();
	ItemName=ui->lineEditItemName->text();
	done(true);
}

void InputPageAndItemNameDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
