#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "SelectPhasePageLayerDialog.h"
#include "ui_SelectPhasePageLayerDialog.h"
#include <QListWidgetItem>
#include "XParamGlobal.h"
#include "XDataInLayer.h"

SelectPhasePageLayerDialog::SelectPhasePageLayerDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SelectPhasePageLayerDialog)
{
    ui->setupUi(this);
	LangLibSolver.SetUI(this);

	SelectPhase	=0;
	SelectPage	=0;
	SelectLayer	=0;
	int	LineHeight=30;

	int	Left=0;
	int	Right=0;
	int	Bottom=0;
	if(GetPhaseNumb()<=1){
		delete	ui->labelPhase;
		ui->labelPhase=NULL;
		delete	ui->listWidgetPhase1;
		ui->listWidgetPhase1=NULL;
	}
	else{
		Left+=10;
		ui->labelPhase			->move(Left,ui->labelPhase		->geometry().y());
		ui->listWidgetPhase1	->move(Left,ui->listWidgetPhase1->geometry().y());
		Left+=ui->listWidgetPhase1->width();
		for(int phase=0;phase<GetPhaseNumb();phase++){
			ui->listWidgetPhase1->addItem(QString(/**/"Phase")+QString::number(phase+1));
		}
		ui->listWidgetPhase1->resize(ui->listWidgetPhase1->width(),GetPhaseNumb()*LineHeight);
		int	B=GetPhaseNumb()*LineHeight+ui->listWidgetPhase1->geometry().y();
		if(B>Bottom)
			Bottom=B;
	}

	if(GetPageNumb()<=1){
		delete	ui->labelPage;
		ui->labelPage=NULL;
		delete	ui->listWidgetPage1;
		ui->listWidgetPage1=NULL;
	}
	else{
		Left+=10;
		ui->labelPage		->move(Left,ui->labelPage		->geometry().y());
		ui->listWidgetPage1	->move(Left,ui->listWidgetPage1	->geometry().y());
		Left+=ui->listWidgetPage1->width();
		for(int Page=0;Page<GetPageNumb();Page++){
			ui->listWidgetPage1->addItem(QString(/**/"Page")+QString::number(Page+1));
		}
		ui->listWidgetPage1->resize(ui->listWidgetPage1->width(),GetPageNumb()*LineHeight);
		int	B=GetPageNumb()*LineHeight+ui->listWidgetPage1->geometry().y();
		if(B>Bottom)
			Bottom=B;
	}

	if(GetLayersBase()->GetMaxLayerNumb()<=1){
		delete	ui->labelLayer;
		ui->labelLayer=NULL;
		delete	ui->listWidgetLayer1;
		ui->listWidgetLayer1=NULL;
	}
	else{
		Left+=10;
		ui->labelLayer			->move(Left,ui->labelLayer		->geometry().y());
		ui->listWidgetLayer1	->move(Left,ui->listWidgetLayer1->geometry().y());
		Left+=ui->listWidgetLayer1->width();
		for(int Layer=0;Layer<GetLayersBase()->GetMaxLayerNumb();Layer++){
			ui->listWidgetLayer1->addItem(GetParamGlobal()->GetLayerName(Layer)+QString(/**/" (Ly ")+QString::number(Layer+1)+QString(/**/") "));
		}
		ui->listWidgetLayer1->resize(ui->listWidgetLayer1->width(),GetLayersBase()->GetMaxLayerNumb()*LineHeight);
		int	B=GetLayersBase()->GetMaxLayerNumb()*LineHeight+ui->listWidgetLayer1->geometry().y();
		if(B>Bottom)
			Bottom=B;
	}
	if(Left==0)
		done(true);
	Right=Left+10;
	int	BW=ui->pushButtonSelect1->width() + ui->pushButtonCancel1->width();
	if(Right<BW){
		Right=BW+30;
	}
	int	BMergin=(Right-BW)/3;
	ui->pushButtonSelect1->move(BMergin,Bottom+10);
	ui->pushButtonCancel1->move(BMergin+ui->pushButtonSelect1->width()+BMergin,Bottom+10);

	resize(Right,Bottom+20+ui->pushButtonSelect1->height());
	InstallOperationLog(this);
}

SelectPhasePageLayerDialog::~SelectPhasePageLayerDialog()
{
    delete ui;
}

void SelectPhasePageLayerDialog::on_listWidgetPhase1_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect1_clicked();
}

void SelectPhasePageLayerDialog::on_listWidgetPage1_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect1_clicked();
}

void SelectPhasePageLayerDialog::on_listWidgetLayer1_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect1_clicked();
}

void SelectPhasePageLayerDialog::on_pushButtonSelect1_clicked()
{
	if(ui->listWidgetPhase1!=NULL)
		SelectPhase=ui->listWidgetPhase1->currentRow();
	if(ui->listWidgetPage1!=NULL)
		SelectPage =ui->listWidgetPage1->currentRow();
	if(ui->listWidgetLayer1!=NULL)
		SelectLayer=ui->listWidgetLayer1->currentRow();
	done(true);
}

void SelectPhasePageLayerDialog::on_pushButtonCancel1_clicked()
{
	done(false);
}
