#include "SelectLayerDialog.h"
#include "ui_SelectLayerDialog.h"
#include "ImageControlTools.h"

const	int	wButtonW=72;
const	int	wButtonH=40;

SelectLayerDialog::SelectLayerDialog(ImageControlTools *p,LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,Parent(p)
    ,ui(new Ui::SelectLayerDialog)
{
    ui->setupUi(this);

	LNumb=0;
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	QWidget	*w=ui->scrollArea->widget();
    LButtonList=new mtToolButtonColored*[LayerNumb];
	for(int Layer=0;Layer<LayerNumb;Layer++){
		LButtonList[LNumb]=new mtToolButtonColored(false);
		LButtonList[LNumb]->setMessage("Layer "+QString::number(Layer));
		//LButtonList[LNumb]->setText(LangSolver.GetString(ImageControlToolsForm_LS,LID_9)/*"Ly"*/+QString::number(Layer));
		LButtonList[LNumb]->setText("Ly "+QString::number(Layer));
		LButtonList[LNumb]->setAutoExclusive(false);
		LButtonList[LNumb]->setCheckable(true);
		LButtonList[LNumb]->setAutoRaise(true);
		LButtonList[LNumb]->setChecked(Parent->LButtonList[Layer]->isChecked());
		LButtonList[LNumb]->setColor(Qt::gray);
		LButtonList[LNumb]->setPressedColor(GetLayersBase()->GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LButtonList[LNumb]->resize(wButtonW,wButtonH);
		LButtonList[LNumb]->setParent(w);

		connect(LButtonList[LNumb],SIGNAL(clicked(bool)),this,SLOT(LayerClicked(bool)));
		
		LNumb++;			
	}
	QScrollBar *V=ui->scrollArea->verticalScrollBar();
	connect(V,SIGNAL(valueChanged(int)),this,SLOT(SlotValueChanged(int)));
}

SelectLayerDialog::~SelectLayerDialog()
{
    delete ui;
}

void SelectLayerDialog::on_pushButtonOK_clicked()
{
	done(true);
}

void SelectLayerDialog::resizeEvent(QResizeEvent *event)
{
    ui->frame->setGeometry(0,height()-ui->frame->height(),width(),ui->frame->height());
    ui->pushButtonOK->move((width()-ui->pushButtonOK->width())/2,4);
    ui->scrollArea->resize(width()-2,height()-ui->frame->height());

	int	WNumb=(ui->scrollArea->width()-20)/wButtonW;
	if(WNumb==0)
		WNumb=1;
	int	HNumb=(LNumb+WNumb-1)/WNumb;
	QWidget	*w=ui->scrollArea->widget();
	w->setGeometry(0,0,WNumb*wButtonW+1,HNumb*wButtonH+1);

	for(int i=0;i<LNumb;i++){
		int	xn=i%WNumb;
		int	yn=i/WNumb;
		LButtonList[i]->move(xn*wButtonW,yn*wButtonH);
	}
	w->show();
	w->update();
	QScrollBar *V=ui->scrollArea->verticalScrollBar();
	V->setMaximum(HNumb*wButtonH+1);
	V->setValue(0);
	V->setPageStep(wButtonH);
}

void SelectLayerDialog::LayerClicked(bool checked)
{
	for(int i=0;i<LNumb;i++){
		Parent->LButtonList[i]->setChecked(LButtonList[i]->isChecked());
	}
	Parent->LayerClicked(checked);
}

void SelectLayerDialog::on_pushButtonAllON_clicked()
{
	for(int i=0;i<LNumb;i++){
		LButtonList[i]->setChecked(true);
	}
	LayerClicked(true);
}


void SelectLayerDialog::on_pushButtonAllOFF_clicked()
{
	for(int i=0;i<LNumb;i++){
		LButtonList[i]->setChecked(false);
	}
	LayerClicked(false);
}

void SelectLayerDialog::SlotValueChanged(int value)
{
	for(int i=0;i<LNumb;i++){
		LButtonList[i]->repaint();
	}
}
