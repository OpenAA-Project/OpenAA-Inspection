#include "CommonGUIDLLResource.h"
#include "SelectHistgramName.h"
#include "ui_SelectHistgramName.h"
#include <QStringList>

SelectHistgramName::SelectHistgramName(AlgorithmBase *abase ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectHistgramName)
{
    ui->setupUi(this);

	ABase=abase ;

	QStringList HistNames;
	ABase->EnumHistgram(HistNames);
	ui->listWidgetHistName->addItems(HistNames);
	HistgramID=-1;

	abase->GetLayersBase()->InstallOperationLog(this);
}

SelectHistgramName::~SelectHistgramName()
{
    delete ui;
}

void SelectHistgramName::on_pushButtonSelect_clicked()
{
	int	Row=ui->listWidgetHistName->currentRow();
	if(Row<0)
		return;
	HistgramID=ABase->GetHistgramID(Row);
}

void SelectHistgramName::on_listWidgetHistName_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}
