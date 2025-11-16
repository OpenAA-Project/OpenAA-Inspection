#include "ShowThresholdSlideBarForm.h"
#include "ui_ShowThresholdSlideBarForm.h"

extern   const	char	*sRoot;
extern   const	char	*sName;

ShowThresholdSlideBarForm::ShowThresholdSlideBarForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowThresholdSlideBarForm)
{
    ui->setupUi(this);

    Title   =/**/"XXX";
    Layer   =0;
    LibID   =0;
    MinimumValue    =-5;
    MaximumValue    =5;
    EnableChange    =true;
    ModeDisplayUnit =_None;
}

ShowThresholdSlideBarForm::~ShowThresholdSlideBarForm()
{
    delete ui;
}

void	ShowThresholdSlideBarForm::ReadyParam(void)
{
    ABase   =GetLayersBase()->GetAlgorithmBase(AlgoDLLRoot,AlgoDLLName);

    ui->labelTitle      ->setText(Title);
    ui->spinBoxValue    ->setMinimum(MinimumValue);
    ui->spinBoxValue    ->setMaximum(MaximumValue);
    ui->horizontalSlider->setMinimum(MinimumValue);
    ui->horizontalSlider->setMaximum(MaximumValue);

    if(DisplayUnitStr==/**/"None")
        ModeDisplayUnit=_None;
    else
    if(DisplayUnitStr==/**/"D1")
        ModeDisplayUnit=_D1;
    else
    if(DisplayUnitStr==/**/"D2")
        ModeDisplayUnit=_D2;
    else
    if(DisplayUnitStr==/**/"D3")
        ModeDisplayUnit=_D3;

    if(ModeDisplayUnit==_None){
        ui->labelExplain    ->setVisible(false);
        ui->labelUnit       ->setVisible(false);
    }
    else{
        ui->labelExplain    ->setVisible(true);
        ui->labelUnit       ->setVisible(true);
    }
}

void	ShowThresholdSlideBarForm::BuildForShow(void)
{
    EnableChange=false;
    for(int page=0;page<GetPageNumb();page++){
        int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
        GUICmdReqThresholdSlider    RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
        GUICmdAckThresholdSlider    ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
        RCmd.AlgoDLLRoot    =AlgoDLLRoot;
        RCmd.AlgoDLLName    =AlgoDLLName;
        RCmd.Layer          =Layer;
        RCmd.LibID          =LibID;
        RCmd.MemberID       =MemberID;
        if(RCmd.Send(GlobalPage,0,ACmd)==true){
            ui->horizontalSlider->setValue(ACmd.ValueInt);
            ui->spinBoxValue    ->setValue(ACmd.ValueInt);
            ShowUnit(ACmd.ValueInt);
           break;
        }
    }
    EnableChange=true;
}

void ShowThresholdSlideBarForm::on_horizontalSlider_valueChanged(int value)
{
    if(EnableChange==true){
        EnableChange=false;
        int d=ui->horizontalSlider->value();
        ui->spinBoxValue    ->setValue(d);
        ShowUnit(d);
        for(int page=0;page<GetPageNumb();page++){
            int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
            GUICmdSetThresholdSlider    RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
            RCmd.AlgoDLLRoot    =AlgoDLLRoot;
            RCmd.AlgoDLLName    =AlgoDLLName;
            RCmd.Layer          =Layer;
            RCmd.LibID          =LibID;
            RCmd.MemberID       =MemberID;
            RCmd.ValueInt       =d;
            RCmd.Send(NULL,GlobalPage,0);
        }
    }
    EnableChange=true;
}


void ShowThresholdSlideBarForm::on_spinBoxValue_valueChanged(int arg1)
{
    if(EnableChange==true){
        EnableChange=false;
        int d=ui->spinBoxValue  ->value();
        ui->horizontalSlider    ->setValue(d);
        ShowUnit(d);
        for(int page=0;page<GetPageNumb();page++){
            int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
            GUICmdSetThresholdSlider    RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
            RCmd.AlgoDLLRoot    =AlgoDLLRoot;
            RCmd.AlgoDLLName    =AlgoDLLName;
            RCmd.Layer          =Layer;
            RCmd.LibID          =LibID;
            RCmd.MemberID       =MemberID;
            RCmd.ValueInt       =d;
            RCmd.Send(NULL,GlobalPage,0);
        }
    }
    EnableChange=true;
}

void ShowThresholdSlideBarForm::ShowUnit(int d)
{
    if(DisplayUnitStr==/**/"None"){
    }
    else
    if(DisplayUnitStr==/**/"D1"){
        ui->labelExplain    ->setText(QString::number(GetParamGlobal()->TransformPixelToUnit(0,d),'f',2));
        ui->labelUnit       ->setText(GetParamGlobal()->UnitName);
    }
    else
    if(DisplayUnitStr==/**/"D2"){
        ui->labelExplain    ->setText(QString::number(GetParamGlobal()->TransformPixelToUnitSquare(0,d),'f',2));
        ui->labelUnit       ->setText(GetParamGlobal()->UnitSquareName);
    }
    else
    if(DisplayUnitStr==/**/"D3"){
    }
}

//=================================================================================================
GUICmdReqThresholdSlider::GUICmdReqThresholdSlider(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqThresholdSlider::Load(QIODevice *f)
{
    if(::Load(f,AlgoDLLRoot )==false)    return false;
    if(::Load(f,AlgoDLLName )==false)    return false;
    if(::Load(f,Layer       )==false)    return false;
    if(::Load(f,LibID       )==false)    return false;
    if(::Load(f,MemberID    )==false)    return false;
    return true;
}
bool	GUICmdReqThresholdSlider::Save(QIODevice *f)
{
    if(::Save(f,AlgoDLLRoot )==false)    return false;
    if(::Save(f,AlgoDLLName )==false)    return false;
    if(::Save(f,Layer       )==false)    return false;
    if(::Save(f,LibID       )==false)    return false;
    if(::Save(f,MemberID    )==false)    return false;
    return true;
}

struct StructThresholdSliderFunc
{
    int32   LibID;
    int32   MemberID;
    int32   ValueInt;
    bool    Ret;
};

static  void ThresholdSliderScanFunc(void *caller,AlgorithmItemRoot *item)
{
    struct StructThresholdSliderFunc    *p=(struct StructThresholdSliderFunc *)caller;
    if(item->GetLibID()==p->LibID){
        const   AlgorithmThreshold  *Thr=item->GetThresholdBaseReadable();
        int32   RetAddedValue;
        if(Thr->GetModifierAdded(p->MemberID ,RetAddedValue)==true){
            p->ValueInt=RetAddedValue;
            p->Ret=true;
        }
    }
}

void	GUICmdReqThresholdSlider::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
    GUICmdAckThresholdSlider	*SendBack=GetSendBack(GUICmdAckThresholdSlider,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

    struct StructThresholdSliderFunc    D;
    D.LibID     =LibID;
    D.MemberID  =MemberID;
    D.Ret=false;
    AlgorithmBase   *ABase   =GetLayersBase()->GetAlgorithmBase(AlgoDLLRoot,AlgoDLLName);
    AlgorithmInPageRoot *Ap=ABase->GetPageData(localPage);
    Ap->ScanItems(Layer ,&D,ThresholdSliderScanFunc);
    if(D.Ret==true){
        SendBack->ValueInt=D.ValueInt;
    }
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdAckThresholdSlider::GUICmdAckThresholdSlider(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckThresholdSlider::Load(QIODevice *f)
{
    if(::Load(f,ValueInt )==false)    return false;
    return true;
}
bool	GUICmdAckThresholdSlider::Save(QIODevice *f)
{
    if(::Save(f,ValueInt )==false)    return false;
    return true;
}


GUICmdSetThresholdSlider::GUICmdSetThresholdSlider(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetThresholdSlider::Load(QIODevice *f)
{
    if(::Load(f,AlgoDLLRoot )==false)    return false;
    if(::Load(f,AlgoDLLName )==false)    return false;
    if(::Load(f,Layer       )==false)    return false;
    if(::Load(f,LibID       )==false)    return false;
    if(::Load(f,MemberID    )==false)    return false;
    if(::Load(f,ValueInt    )==false)    return false;
    return true;
}
bool	GUICmdSetThresholdSlider::Save(QIODevice *f)
{
    if(::Save(f,AlgoDLLRoot )==false)    return false;
    if(::Save(f,AlgoDLLName )==false)    return false;
    if(::Save(f,Layer       )==false)    return false;
    if(::Save(f,LibID       )==false)    return false;
    if(::Save(f,MemberID    )==false)    return false;
    if(::Save(f,ValueInt    )==false)    return false;
    return true;
}


static  void ThresholdSetSliderFunc(void *caller,AlgorithmItemRoot *item)
{
    struct StructThresholdSliderFunc    *p=(struct StructThresholdSliderFunc *)caller;
    if(item->GetLibID()==p->LibID){
        AlgorithmThreshold  *Thr=item->GetThresholdBaseWritable();
        Thr->SetModifierAdded(p->MemberID ,p->ValueInt);
    }
}

void	GUICmdSetThresholdSlider::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
    struct StructThresholdSliderFunc    D;
    D.LibID     =LibID;
    D.MemberID  =MemberID;
    D.ValueInt  =ValueInt;
    D.Ret=false;
    AlgorithmBase   *ABase   =GetLayersBase()->GetAlgorithmBase(AlgoDLLRoot,AlgoDLLName);
    for(int page=0;page<GetPageNumb();page++){
        AlgorithmInPageRoot *Ap=ABase->GetPageData(page);
        Ap->ScanItems(Layer ,&D,ThresholdSetSliderFunc);
    }
}
