#include "CommonGUIDLLResource.h"
#include "SelectOnePage.h"
#include "ui_SelectOnePage.h"

SelectOnePage::SelectOnePage(LayersBase *pbase ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(pbase)
    ,ui(new Ui::SelectOnePage)
{
    ui->setupUi(this);

	for(int page=0;page<GetPageNumb();page++){
		ui->listWidgetPage->addItem(QString(/**/"Page ")+QString::number(page));
		PageList.Add(page);
	}
	InstallOperationLog(this);
}

SelectOnePage::SelectOnePage(LayersBase *pbase ,const IntList &pageList,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(pbase)
    ,ui(new Ui::SelectOnePage)
{
    ui->setupUi(this);

	for(IntClass *c=pageList.GetFirst();c!=NULL;c=c->GetNext()){
		int	page=c->GetValue();
		ui->listWidgetPage->addItem(QString(/**/"Page ")+QString::number(page));
		PageList.Add(page);
	}
	InstallOperationLog(this);
}
SelectOnePage::~SelectOnePage()
{
    delete ui;
}

void SelectOnePage::on_listWidgetPage_doubleClicked(const QModelIndex &index)
{
	int	n=ui->listWidgetPage->currentRow();
	SelectedPage=PageList[n];
	done(true);
}

void SelectOnePage::on_pushButtonOK_clicked()
{
	int	n=ui->listWidgetPage->currentRow();
	SelectedPage=PageList[n];
	done(true);
}
