#include "ServiceLibResource.h"
#include "ShowThresholdHistgramForm.h"
#include "ui_ShowThresholdHistgramForm.h"
#include "XHistgramByParam.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"
#include "SelectLibraryOneDialog.h"


ShowThresholdHistgramForm::ShowThresholdHistgramForm(LayersBase *Base ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,LGraph(parent)
    ,ui(new Ui::ShowThresholdHistgramForm)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);

    ThresholdA	=0.0;
    ThresholdB	=0.0;
    HistDiv		=1.0;

    Average		=0.0;
    Dispersion	=0.0;
    HistDiv		=0.0;

    Phase		=-1;
    GlobalPage	=-1;
    Layer		=-1;
    ItemID		=-1;
    LibID		=-1;
    HistID		=-1;

    LGraph.setParent(ui->frame);
    LGraph.SetScaleTypeY(mtLineGraph::mtLog);
    LGraph.move(0,0);
    LGraph.resize(ui->frame->width(),ui->frame->height());

    GraphHistgram	.SetLineColor(GetParamGlobal()->HistgramGraphColor);
    GraphHistgram	.SetLineWidth(1);
    GraphHistgram	.SetOffsetX(0);
    GraphThresh		.SetLineColor(GetParamGlobal()->HistgramThreshColor);
    GraphThresh		.SetLineWidth(1);
    GraphThresh		.SetOffsetX(2);

    LGraph.AddGraph(&GraphHistgram);
    LGraph.AddGraph(&GraphThresh);
    connect(&LGraph,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClick(int ,int )));

    InstallOperationLog(this);
}

ShowThresholdHistgramForm::~ShowThresholdHistgramForm()
{
    delete ui;
}

bool	ShowThresholdHistgramForm::Initial(int _Phase ,int _GlobalPage ,int _Layer ,int _ItemID ,int _HistID
                                            ,const QString &_AlgoRoot ,const QString &_AlgoName )
{
    Phase		=_Phase;
    GlobalPage	=_GlobalPage;
    Layer		=_Layer;
    ItemID		=_ItemID;
    HistID		=_HistID;
    AlgoRoot	=_AlgoRoot;
    AlgoName	=_AlgoName;

    GUICmdReqHistgram	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY" ,GlobalPage);
    GUICmdAckHistgram	SCmd(GetLayersBase(),/**/"ANY",/**/"ANY" ,GlobalPage);

    RCmd.ItemID		=ItemID;
    RCmd.AlgoRoot	=AlgoRoot;
    RCmd.AlgoName	=AlgoName;
    RCmd.Phase		=Phase;
    RCmd.Layer		=Layer;
    RCmd.HistID		=HistID;

    if(RCmd.Send(GlobalPage,0,SCmd)==true){
        GraphData=SCmd.HistData;
    }
    Average		=GraphData.GetAverage();
    Dispersion	=GraphData.GetDispersion();

    ui->lineEditNumCenter	->setText(QString::number(Average));
    ui->lineEditNumDev		->setText(QString::number(sqrt(Dispersion)));

    GUICmdReqInfoForHistgram	InfoRCmd(GetLayersBase(),/**/"ANY",/**/"ANY" ,GlobalPage);
    GUICmdAckInfoForHistgram	InfoSCmd(GetLayersBase(),/**/"ANY",/**/"ANY" ,GlobalPage);

    InfoRCmd.ItemID		=ItemID;
    InfoRCmd.AlgoRoot	=AlgoRoot;
    InfoRCmd.AlgoName	=AlgoName;
    InfoRCmd.Phase		=Phase;
    InfoRCmd.Layer		=Layer;
    InfoRCmd.HistID		=HistID;

    if(InfoRCmd.Send(GlobalPage,0,InfoSCmd)==true){
        ui->lineEditLibID	->setText(QString::number(InfoSCmd.LibID));
        AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
        if(ABase!=NULL && InfoSCmd.LibID>0){
            ui->lineEditLibID	->setVisible(true);
            ui->lineEditLibName	->setVisible(true);
            QString	LibName=ABase->GetLibraryContainer()->GetLibraryName(InfoSCmd.LibID);
            ui->lineEditLibName	->setText(LibName);
        }
        else{
            ui->lineEditLibID	->setVisible(false);
            ui->lineEditLibName	->setVisible(false);
        }
        ui->lineEditHistName->setText(InfoSCmd.HistName);
    }

    ShowGrah();
    return true;
}

bool	ShowThresholdHistgramForm::Initial(int _Phase ,int _GlobalPage ,int _Layer ,int _HistID
                                            ,const QString &_AlgoRoot ,const QString &_AlgoName )
{
    Phase		=_Phase;
    GlobalPage	=_GlobalPage;
    Layer		=_Layer;
    HistID		=_HistID;
    AlgoRoot	=_AlgoRoot;
    AlgoName	=_AlgoName;

    GUICmdReqAlgorithmUsageLib	RCmdLib(GetLayersBase(),/**/"ANY",/**/"ANY" ,GlobalPage);
    GUICmdAckAlgorithmUsageLib	SCmdLib(GetLayersBase(),/**/"ANY",/**/"ANY" ,GlobalPage);

    RCmdLib.AlgoRoot	=AlgoRoot;
    RCmdLib.AlgoName	=AlgoName;
    RCmdLib.Phase		=Phase;
    RCmdLib.Layer		=Layer;

    if(RCmdLib.Send(GlobalPage,0,SCmdLib)==false){
        return false;
    }
    if(SCmdLib.LibList.GetCount()==0){
        return false;
    }
    LibID=-1;
    if(SCmdLib.LibList.GetCount()>1){
        AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(_AlgoRoot ,_AlgoName);
        if(ABase==NULL){
            return false;
        }
        SelectLibraryOneDialog	Dlg(GetLayersBase(),ABase->GetLibType(),SCmdLib.LibList);
        if(Dlg.exec()==true){
            LibID=Dlg.SelectedLibID;
        }
    }
    else{
        LibID=SCmdLib.LibList[0];
    }
    if(LibID<0){
        return false;
    }

    GUICmdReqHistgramLib	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY" ,GlobalPage);
    GUICmdAckHistgramLib	SCmd(GetLayersBase(),/**/"ANY",/**/"ANY" ,GlobalPage);

    RCmd.LibID		=LibID;
    RCmd.AlgoRoot	=AlgoRoot;
    RCmd.AlgoName	=AlgoName;
    RCmd.Phase		=Phase;
    RCmd.Layer		=Layer;
    RCmd.HistID		=HistID;

    if(RCmd.Send(GlobalPage,0,SCmd)==true){
        GraphData=SCmd.HistData;
    }
    Average		=GraphData.GetAverage();
    Dispersion	=GraphData.GetDispersion();

    ui->lineEditNumCenter	->setText(QString::number(Average));
    ui->lineEditNumDev		->setText(QString::number(sqrt(Dispersion)));

    ui->lineEditLibID	->setText(QString::number(LibID));
    AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
    if(ABase!=NULL && LibID>0){
        ui->lineEditLibID	->setVisible(true);
        ui->lineEditLibName	->setVisible(true);
        QString	LibName=ABase->GetLibraryContainer()->GetLibraryName(LibID);
        ui->lineEditLibName	->setText(LibName);
    }
    else{
        ui->lineEditLibID	->setVisible(false);
        ui->lineEditLibName	->setVisible(false);
    }
    ui->lineEditHistName->setText(SCmd.HistName);

    ShowGrah();
    return true;
}
void ShowThresholdHistgramForm::ShowGrah(void)
{
    GraphHistgram.DeleteXY();
    GraphThresh.DeleteXY();

    for(int i=0;i<GraphData.GetDimCount();i++){
        GraphHistgram.AddXY(GraphData.GetMinData()+i*GraphData.GetStep(),GraphData.GetHistData(i));
    }
    GraphThresh.AddXY(ThresholdA,GraphData.GetMaxData());
    GraphThresh.AddXY(ThresholdB,GraphData.GetMaxData());
}

void ShowThresholdHistgramForm::ShowCalculated(void)
{
    ui->lineEditThresh1->setText(QString::number(ThresholdA));
    ui->lineEditThresh2->setText(QString::number(ThresholdB));

    //lineEditNumPercent
}

void	ShowThresholdHistgramForm::SlotLineGraphDClick(int X,int Y)
{
    if(ui->toolButtonThreshold1->isChecked()==true){
        ThresholdA=X;
    }
    else if(ui->toolButtonThreshold2->isChecked()==true){
        ThresholdB=X;
    }
    if(ThresholdA>ThresholdB){
        swap(ThresholdA,ThresholdB);
    }
    ShowCalculated();
    ShowGrah();
    LGraph.repaint();
}

void ShowThresholdHistgramForm::on_pushButtonClose_clicked()
{
    if(dynamic_cast<GeneralDialog *>(parent())!=NULL){
        emit	SignalClose();
    }
    else{
        close();
    }
}

void ShowThresholdHistgramForm::on_pushButtonCalc_clicked()
{
    bool	ok;
    double	d1=ui->lineEditThresh1->text().toDouble(&ok);
    if(ok==true){
        ThresholdA=d1;
    }
    double	d2=ui->lineEditThresh2->text().toDouble(&ok);
    if(ok==true){
        ThresholdB=d2;
    }
    double	d=GraphData.RealPercentage(ThresholdA,ThresholdB);
    ui->lineEditNumPercent->setText(QString::number(d*100.0));
}
void ShowThresholdHistgramForm::on_pushButtonCalc2_clicked()
{
    double	DRate=0;
    bool	ok;
    double	d1=ui->lineEditNumPercent->text().toDouble(&ok)/100.0;
    if(ok==true){
        DRate=d1;
    }
    GraphData.GetRealThreshold((1.0-DRate)/2.0,(1.0-DRate)/2.0
                                ,ThresholdA,ThresholdB);
    ui->lineEditThresh1->setText(QString::number(ThresholdA));
    ui->lineEditThresh2->setText(QString::number(ThresholdB));
    ShowGrah();
}

void ShowThresholdHistgramForm::on_pushButtonCalcD_clicked()
{
    bool	ok;
    double	d1=ui->lineEditThresh1->text().toDouble(&ok);
    if(ok==true){
        ThresholdA=d1;
    }
    double	d2=ui->lineEditThresh2->text().toDouble(&ok);
    if(ok==true){
        ThresholdB=d2;
    }
    double	d=GraphData.IdealPercentage(ThresholdA,ThresholdB);
    ui->lineEditNumPercent->setText(QString::number(d*100.0));
}

void ShowThresholdHistgramForm::on_pushButtonCalcU_clicked()
{
    double	DRate=0;
    bool	ok;
    double	d1=ui->lineEditNumPercent->text().toDouble(&ok)/100.0;
    if(ok==true){
        DRate=d1;
    }
    GraphData.GetIdealThreshold(DRate/2.0,DRate/2.0
                                ,ThresholdA,ThresholdB);
    ui->lineEditThresh1->setText(QString::number(ThresholdA));
    ui->lineEditThresh2->setText(QString::number(ThresholdB));
    ShowGrah();
}

void ShowThresholdHistgramForm::on_pushButtonSave_clicked()
{
    QString	FileName=QFileDialog::getSaveFileName(NULL
                                                ,"Save file name"
                                                ,QString(/**/"")
                                                ,QString(tr(/**/"CSV(*.csv);;All files (*.*)")));
    if(FileName.isEmpty()==false){
        QFile	File(FileName);
        if(File.open(QIODevice::WriteOnly)==true){
            GUICmdReqInfoForHistDirect	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY" ,GlobalPage);
            GUICmdAckInfoForHistDirect	SCmd(GetLayersBase(),/**/"ANY",/**/"ANY" ,GlobalPage);

            RCmd.ItemID		=ItemID;
            RCmd.LibID		=LibID;
            RCmd.AlgoRoot	=AlgoRoot;
            RCmd.AlgoName	=AlgoName;
            RCmd.Phase		=Phase;
            RCmd.Layer		=Layer;
            RCmd.HistID		=HistID;

            if(RCmd.Send(GlobalPage,0,SCmd)==true){
                //GraphData=SCmd.HistData;
                SCmd.Data->SaveText(&File);
            }
        }
    }
}

void ShowThresholdHistgramForm::on_pushButtonSetThreshold_clicked()
{
    bool	ok;
    double	d1=ui->lineEditThresh1->text().toDouble(&ok);
    if(ok==false){
        return;
    }
    ThresholdA=d1;

    double	d2=ui->lineEditThresh2->text().toDouble(&ok);
    if(ok==false){
        return;
    }
    ThresholdB=d2;

    for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
        int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

        GUICmdReqSetThreshold	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY" ,GlobalPage);

        RCmd.LibID		=LibID;
        RCmd.AlgoRoot	=AlgoRoot;
        RCmd.AlgoName	=AlgoName;
        RCmd.Phase		=Phase;
        RCmd.Layer		=Layer;
        RCmd.HistID		=HistID;
        if(ui->toolButtonThreshold1->isChecked()==true){
            RCmd.ThresholdA	=ThresholdA;
            RCmd.ThresholdB	=ThresholdB;
        }
        else{
            RCmd.ThresholdA	=ThresholdB;
            RCmd.ThresholdB	=ThresholdA;
        }

        RCmd.Send(NULL,GlobalPage,0);
    }
    on_pushButtonClose_clicked();
}
