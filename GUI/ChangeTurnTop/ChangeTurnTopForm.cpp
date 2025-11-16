#include "ChangeTurnTopForm.h"
#include "ui_ChangeTurnTopForm.h"

ChangeTurnTopForm::ChangeTurnTopForm(LayersBase *Base ,QWidget *parent)
    :GUIFormBase(Base,parent),
    ui(new Ui::ChangeTurnTopForm)
{
    ui->setupUi(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ChangeTurnTopForm::~ChangeTurnTopForm()
{
    delete ui;
}

void	ChangeTurnTopForm::Prepare(void)
{
	ui->listWidget->clear();
	for(int page=0;page<GetPageNumb();page++){
		ui->listWidget->addItem(QString::number(page));
	}
}
void	ChangeTurnTopForm::BuildForShow(void)
{
	if(ui->listWidget->count()!=GetPageNumb()){
		ui->listWidget->clear();
		for(int page=0;page<GetPageNumb();page++){
			ui->listWidget->addItem(QString::number(page));
		}
	}
}
void ChangeTurnTopForm::on_listWidget_currentRowChanged(int currentRow)
{
	if(currentRow<0)
		return;
	DataInPage	*Dp=GetLayersBase()->GetPageData(currentRow);
	GetLayersBase()->SetTopInPage(Dp);

	for(int i=0;i<RelatedPanels.count();i++){
		QString	str=RelatedPanels.value(i);
		GUIFormBase		*r=GetFormByName(str);
		if(r==NULL)
			continue;
		r->Repaint();
	}
}
void	ChangeTurnTopForm::ResizeAction()
{
	ui->listWidget->resize(width(),height());
}
