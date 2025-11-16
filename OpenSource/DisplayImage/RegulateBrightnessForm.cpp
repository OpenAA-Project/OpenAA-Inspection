#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "RegulateBrightnessForm.h"
#include "ui_RegulateBrightnessForm.h"
#include "XGeneralFunc.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XDataInLayer.h"

RegulateBrightnessForm::RegulateBrightnessForm(	IntList &EffectiveLayerList
                                                ,HistgramListContainer		&_HistDatas
                                                ,AvrVarListByLayerContainer	&_AvrDatas
                                                ,LayersBase *base
                                                ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,LGraph(parent)
    ,ui(new Ui::RegulateBrightnessForm)
    
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    SetWidgetCenter(this);

    HistDatas	=_HistDatas;
    AvrDatas	=_AvrDatas;

    LGraph.setParent(ui->frameGraph);
    LGraph.SetScaleTypeY(mtLineGraph::mtLog);
    LGraph.move(0,0);
    LGraph.resize(ui->frameGraph->width(),ui->frameGraph->height());
    LayerBar.setParent(ui->frameLayer);
    LayerBar.move(0,0);
    LayerBar.resize(ui->frameLayer->width(),ui->frameLayer->height());
    int	ANumb=AvrDatas.GetNumber();
    int	HNumb=HistDatas.GetNumber();
    LNumb=min(ANumb,HNumb);
    LButtonList=new mtToolButtonColored*[LNumb];
    LastLayer=-1;

    for(int Layer=0;Layer<LNumb;Layer++){
        LButtonList[Layer]=new mtToolButtonColored(false);
        LButtonList[Layer]->setText(GetParamGlobal()->GetLayerName(Layer));
        LButtonList[Layer]->setAutoExclusive(true);
        LButtonList[Layer]->setCheckable(true);
        LButtonList[Layer]->setAutoRaise(true);
        if((EffectiveLayerList.IsEmpty()==false) && EffectiveLayerList.IsInclude(Layer)==false){
            LButtonList[Layer]->setEnabled(false);
        }
        LButtonList[Layer]->resize(48,32);
        LButtonList[Layer]->setColor(Qt::gray);
        LButtonList[Layer]->setPressedColor(GetParamGlobal()->GetOneGraphLayerColor(Layer));
        LayerBar.addWidget(LButtonList[Layer]);
        connect(LButtonList[Layer],SIGNAL(clicked()),this,SLOT(SlotLayerClicked()));
    }
    IntClass	*Ly=EffectiveLayerList.GetFirst();
    if(Ly!=NULL){
        LButtonList[Ly->GetValue()]->setChecked(true);
    }
    else{
        LButtonList[0]->setChecked(true);
    }

    QColor	MasterColor=Qt::green;

    GraphCol	.SetLineColor(MasterColor);
    GraphCol	.SetLineWidth(1);
    GraphCol	.SetOffsetX(0);

    LGraph.AddGraph(&GraphCol);
    ShowData();

    InstallOperationLog(this);
}

RegulateBrightnessForm::~RegulateBrightnessForm()
{
    delete ui;
}

void RegulateBrightnessForm::on_pushButtonOk_clicked()
{
    int	No=GetCurrentNo();
    GetData(No);
    BlockSize=ui->spinBoxBlockSize->value();

    done((int)true);
}

void RegulateBrightnessForm::on_pushButtonCancel_clicked()
{
    done((int)false);
}

void RegulateBrightnessForm::ShowData(void)
{
    GraphCol.DeleteXY();

    int	No=GetCurrentNo();
    AvrVarListByLayer	*A=AvrDatas.GetItem(No);
    HistgramList		*H=HistDatas.GetItem(No);

    YMax=0;
    for(int i=0;i<256;i++){
        YMax=max(YMax,H->BrightList[i]);
        GraphCol.AddXY(i,H->BrightList[i]);
    }
    LGraph.repaint ();
    ui->doubleSpinBoxAverage->setValue(A->Average);
    ui->doubleSpinBoxDeviation->setValue(A->Dispersion);
}
int	RegulateBrightnessForm::GetCurrentNo(void)
{
    for(int i=0;i<LNumb;i++){
        if(LButtonList[i]->isChecked()==true){
            return i;
        }
    }
    return -1;
}

void RegulateBrightnessForm::GetData(int No)
{
    AvrVarListByLayer	*A=AvrDatas.GetItem(No);

    A->Average		=ui->doubleSpinBoxAverage->value();
    A->Dispersion	=ui->doubleSpinBoxDeviation->value();
}

void	RegulateBrightnessForm::SlotLayerClicked()
{
    if(LastLayer>=0){
        GetData(LastLayer);
    }
    ShowData();
    LastLayer=GetCurrentNo();
}
