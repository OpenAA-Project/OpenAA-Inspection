#include "SettingLightBowl240RGBDialog.h"
#include "ui_SettingLightBowl240RGBDialog.h"
#include <QBuffer>

SettingLightBowl240RGBDialog::SettingLightBowl240RGBDialog(LightBowl240RGBW *p,LayersBase *base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,Parent(p)
    ,ui(new Ui::SettingLightBowl240RGBDialog)
{
    ui->setupUi(this);

    EnableButtons   =true;
    CurrentDimRow        =-1;
    CountOfLightDataDim  =0;

    connect(ui->toolButtonLightAngle0_1R,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle0_1G,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle0_1B,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle0_1W,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle0_2R,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle0_2G,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle0_2B,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle0_2W,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle0_3R,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle0_3G,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle0_3B,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle0_3W,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));

    connect(ui->toolButtonLightAngle90_1R,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle90_1G,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle90_1B,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle90_1W,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle90_2R,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle90_2G,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle90_2B,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle90_2W,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle90_3R,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle90_3G,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle90_3B,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle90_3W,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));

    connect(ui->toolButtonLightAngle180_1R,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle180_1G,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle180_1B,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle180_1W,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle180_2R,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle180_2G,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle180_2B,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle180_2W,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle180_3R,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle180_3G,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle180_3B,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle180_3W,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));

    connect(ui->toolButtonLightAngle270_1R,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle270_1G,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle270_1B,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle270_1W,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle270_2R,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle270_2G,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle270_2B,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle270_2W,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle270_3R,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle270_3G,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle270_3B,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));
    connect(ui->toolButtonLightAngle270_3W,SIGNAL(clicked()),this,SLOT(on_toolLight_clicked()));

    ui->pushButtonModifyPattern->setEnabled(false);
    ui->pushButtonDeletePattern->setEnabled(false);
}

SettingLightBowl240RGBDialog::~SettingLightBowl240RGBDialog()
{
    delete ui;
}

void    SettingLightBowl240RGBDialog::SetInitial(LightBowl240RGBW *s)
{
    for(int i=0;i<MaxDimCountLightBowl240RGBW;i++){
        LightDataDim[i]=s->LightDataDim[i];
    }
    CountOfLightDataDim =s->CountOfLightDataDim;
    CurrentDimRow       =s->CurrentIndex;

    ShowList();
    if(CurrentDimRow>=0){
        ui->listWidgetPatternList->setCurrentRow(CurrentDimRow);
        LightData=LightDataDim[CurrentDimRow];
        SetDataToWindow();
    }
    ui->toolButtonONMode->setChecked(s->ONMode);

    IPAddress=s->IPAddress;
    ui->lineEditIPAddress->setText(IPAddress);
}

void	SettingLightBowl240RGBDialog::GetDataFromWindow(void)
{
    LightData.PatternName   =ui->lineEditPatternName->text();

    //bool    MainSW=ui->toolButtonMainON->isChecked();
    LightData.TopR   =ui->toolButtonLightTopR->isChecked();
    LightData.TopG   =ui->toolButtonLightTopG->isChecked();
    LightData.TopB   =ui->toolButtonLightTopB->isChecked();
    
    LightData.LightAngle0.Light1R=((ui->toolButtonLightAngle0_1R->isChecked()==true))?255:0;
    LightData.LightAngle0.Light1G=((ui->toolButtonLightAngle0_1G->isChecked()==true))?255:0;
    LightData.LightAngle0.Light1B=((ui->toolButtonLightAngle0_1B->isChecked()==true))?255:0;
    LightData.LightAngle0.Light1W=((ui->toolButtonLightAngle0_1W->isChecked()==true))?255:0;
    LightData.LightAngle0.Light2R=((ui->toolButtonLightAngle0_2R->isChecked()==true))?255:0;
    LightData.LightAngle0.Light2G=((ui->toolButtonLightAngle0_2G->isChecked()==true))?255:0;
    LightData.LightAngle0.Light2B=((ui->toolButtonLightAngle0_2B->isChecked()==true))?255:0;
    LightData.LightAngle0.Light2W=((ui->toolButtonLightAngle0_2W->isChecked()==true))?255:0;
    LightData.LightAngle0.Light3R=((ui->toolButtonLightAngle0_3R->isChecked()==true))?255:0;
    LightData.LightAngle0.Light3G=((ui->toolButtonLightAngle0_3G->isChecked()==true))?255:0;
    LightData.LightAngle0.Light3B=((ui->toolButtonLightAngle0_3B->isChecked()==true))?255:0;
    LightData.LightAngle0.Light3W=((ui->toolButtonLightAngle0_3W->isChecked()==true))?255:0;
    
    LightData.LightAngle90.Light1R=((ui->toolButtonLightAngle90_1R->isChecked()==true))?255:0;
    LightData.LightAngle90.Light1G=((ui->toolButtonLightAngle90_1G->isChecked()==true))?255:0;
    LightData.LightAngle90.Light1B=((ui->toolButtonLightAngle90_1B->isChecked()==true))?255:0;
    LightData.LightAngle90.Light1W=((ui->toolButtonLightAngle90_1W->isChecked()==true))?255:0;
    LightData.LightAngle90.Light2R=((ui->toolButtonLightAngle90_2R->isChecked()==true))?255:0;
    LightData.LightAngle90.Light2G=((ui->toolButtonLightAngle90_2G->isChecked()==true))?255:0;
    LightData.LightAngle90.Light2B=((ui->toolButtonLightAngle90_2B->isChecked()==true))?255:0;
    LightData.LightAngle90.Light2W=((ui->toolButtonLightAngle90_2W->isChecked()==true))?255:0;
    LightData.LightAngle90.Light3R=((ui->toolButtonLightAngle90_3R->isChecked()==true))?255:0;
    LightData.LightAngle90.Light3G=((ui->toolButtonLightAngle90_3G->isChecked()==true))?255:0;
    LightData.LightAngle90.Light3B=((ui->toolButtonLightAngle90_3B->isChecked()==true))?255:0;
    LightData.LightAngle90.Light3W=((ui->toolButtonLightAngle90_3W->isChecked()==true))?255:0;
    
    LightData.LightAngle180.Light1R=((ui->toolButtonLightAngle180_1R->isChecked()==true))?255:0;
    LightData.LightAngle180.Light1G=((ui->toolButtonLightAngle180_1G->isChecked()==true))?255:0;
    LightData.LightAngle180.Light1B=((ui->toolButtonLightAngle180_1B->isChecked()==true))?255:0;
    LightData.LightAngle180.Light1W=((ui->toolButtonLightAngle180_1W->isChecked()==true))?255:0;
    LightData.LightAngle180.Light2R=((ui->toolButtonLightAngle180_2R->isChecked()==true))?255:0;
    LightData.LightAngle180.Light2G=((ui->toolButtonLightAngle180_2G->isChecked()==true))?255:0;
    LightData.LightAngle180.Light2B=((ui->toolButtonLightAngle180_2B->isChecked()==true))?255:0;
    LightData.LightAngle180.Light2W=((ui->toolButtonLightAngle180_2W->isChecked()==true))?255:0;
    LightData.LightAngle180.Light3R=((ui->toolButtonLightAngle180_3R->isChecked()==true))?255:0;
    LightData.LightAngle180.Light3G=((ui->toolButtonLightAngle180_3G->isChecked()==true))?255:0;
    LightData.LightAngle180.Light3B=((ui->toolButtonLightAngle180_3B->isChecked()==true))?255:0;
    LightData.LightAngle180.Light3W=((ui->toolButtonLightAngle180_3W->isChecked()==true))?255:0;
    
    LightData.LightAngle270.Light1R=((ui->toolButtonLightAngle270_1R->isChecked()==true))?255:0;
    LightData.LightAngle270.Light1G=((ui->toolButtonLightAngle270_1G->isChecked()==true))?255:0;
    LightData.LightAngle270.Light1B=((ui->toolButtonLightAngle270_1B->isChecked()==true))?255:0;
    LightData.LightAngle270.Light1W=((ui->toolButtonLightAngle270_1W->isChecked()==true))?255:0;
    LightData.LightAngle270.Light2R=((ui->toolButtonLightAngle270_2R->isChecked()==true))?255:0;
    LightData.LightAngle270.Light2G=((ui->toolButtonLightAngle270_2G->isChecked()==true))?255:0;
    LightData.LightAngle270.Light2B=((ui->toolButtonLightAngle270_2B->isChecked()==true))?255:0;
    LightData.LightAngle270.Light2W=((ui->toolButtonLightAngle270_2W->isChecked()==true))?255:0;
    LightData.LightAngle270.Light3R=((ui->toolButtonLightAngle270_3R->isChecked()==true))?255:0;
    LightData.LightAngle270.Light3G=((ui->toolButtonLightAngle270_3G->isChecked()==true))?255:0;
    LightData.LightAngle270.Light3B=((ui->toolButtonLightAngle270_3B->isChecked()==true))?255:0;
    LightData.LightAngle270.Light3W=((ui->toolButtonLightAngle270_3W->isChecked()==true))?255:0;
}
void	SettingLightBowl240RGBDialog::SetDataToWindow(void)
{
    ui->lineEditPatternName->setText(LightData.PatternName);

    ui->toolButtonLightTopR->setChecked(LightData.TopR);
    ui->toolButtonLightTopG->setChecked(LightData.TopG);
    ui->toolButtonLightTopB->setChecked(LightData.TopB);

    ui->toolButtonLightAngle0_1R->setChecked((LightData.LightAngle0.Light1R==0)?false:true);
    ui->toolButtonLightAngle0_1G->setChecked((LightData.LightAngle0.Light1G==0)?false:true);
    ui->toolButtonLightAngle0_1B->setChecked((LightData.LightAngle0.Light1B==0)?false:true);
    ui->toolButtonLightAngle0_1W->setChecked((LightData.LightAngle0.Light1W==0)?false:true);
    ui->toolButtonLightAngle0_2R->setChecked((LightData.LightAngle0.Light2R==0)?false:true);
    ui->toolButtonLightAngle0_2G->setChecked((LightData.LightAngle0.Light2G==0)?false:true);
    ui->toolButtonLightAngle0_2B->setChecked((LightData.LightAngle0.Light2B==0)?false:true);
    ui->toolButtonLightAngle0_2W->setChecked((LightData.LightAngle0.Light2W==0)?false:true);
    ui->toolButtonLightAngle0_3R->setChecked((LightData.LightAngle0.Light3R==0)?false:true);
    ui->toolButtonLightAngle0_3G->setChecked((LightData.LightAngle0.Light3G==0)?false:true);
    ui->toolButtonLightAngle0_3B->setChecked((LightData.LightAngle0.Light3B==0)?false:true);
    ui->toolButtonLightAngle0_3W->setChecked((LightData.LightAngle0.Light3W==0)?false:true);

    ui->toolButtonLightAngle90_1R->setChecked((LightData.LightAngle90.Light1R==0)?false:true);
    ui->toolButtonLightAngle90_1G->setChecked((LightData.LightAngle90.Light1G==0)?false:true);
    ui->toolButtonLightAngle90_1B->setChecked((LightData.LightAngle90.Light1B==0)?false:true);
    ui->toolButtonLightAngle90_1W->setChecked((LightData.LightAngle90.Light1W==0)?false:true);
    ui->toolButtonLightAngle90_2R->setChecked((LightData.LightAngle90.Light2R==0)?false:true);
    ui->toolButtonLightAngle90_2G->setChecked((LightData.LightAngle90.Light2G==0)?false:true);
    ui->toolButtonLightAngle90_2B->setChecked((LightData.LightAngle90.Light2B==0)?false:true);
    ui->toolButtonLightAngle90_2W->setChecked((LightData.LightAngle90.Light2W==0)?false:true);
    ui->toolButtonLightAngle90_3R->setChecked((LightData.LightAngle90.Light3R==0)?false:true);
    ui->toolButtonLightAngle90_3G->setChecked((LightData.LightAngle90.Light3G==0)?false:true);
    ui->toolButtonLightAngle90_3B->setChecked((LightData.LightAngle90.Light3B==0)?false:true);
    ui->toolButtonLightAngle90_3W->setChecked((LightData.LightAngle90.Light3W==0)?false:true);

    ui->toolButtonLightAngle180_1R->setChecked((LightData.LightAngle180.Light1R==0)?false:true);
    ui->toolButtonLightAngle180_1G->setChecked((LightData.LightAngle180.Light1G==0)?false:true);
    ui->toolButtonLightAngle180_1B->setChecked((LightData.LightAngle180.Light1B==0)?false:true);
    ui->toolButtonLightAngle180_1W->setChecked((LightData.LightAngle180.Light1W==0)?false:true);
    ui->toolButtonLightAngle180_2R->setChecked((LightData.LightAngle180.Light2R==0)?false:true);
    ui->toolButtonLightAngle180_2G->setChecked((LightData.LightAngle180.Light2G==0)?false:true);
    ui->toolButtonLightAngle180_2B->setChecked((LightData.LightAngle180.Light2B==0)?false:true);
    ui->toolButtonLightAngle180_2W->setChecked((LightData.LightAngle180.Light2W==0)?false:true);
    ui->toolButtonLightAngle180_3R->setChecked((LightData.LightAngle180.Light3R==0)?false:true);
    ui->toolButtonLightAngle180_3G->setChecked((LightData.LightAngle180.Light3G==0)?false:true);
    ui->toolButtonLightAngle180_3B->setChecked((LightData.LightAngle180.Light3B==0)?false:true);
    ui->toolButtonLightAngle180_3W->setChecked((LightData.LightAngle180.Light3W==0)?false:true);

    ui->toolButtonLightAngle270_1R->setChecked((LightData.LightAngle270.Light1R==0)?false:true);
    ui->toolButtonLightAngle270_1G->setChecked((LightData.LightAngle270.Light1G==0)?false:true);
    ui->toolButtonLightAngle270_1B->setChecked((LightData.LightAngle270.Light1B==0)?false:true);
    ui->toolButtonLightAngle270_1W->setChecked((LightData.LightAngle270.Light1W==0)?false:true);
    ui->toolButtonLightAngle270_2R->setChecked((LightData.LightAngle270.Light2R==0)?false:true);
    ui->toolButtonLightAngle270_2G->setChecked((LightData.LightAngle270.Light2G==0)?false:true);
    ui->toolButtonLightAngle270_2B->setChecked((LightData.LightAngle270.Light2B==0)?false:true);
    ui->toolButtonLightAngle270_2W->setChecked((LightData.LightAngle270.Light2W==0)?false:true);
    ui->toolButtonLightAngle270_3R->setChecked((LightData.LightAngle270.Light3R==0)?false:true);
    ui->toolButtonLightAngle270_3G->setChecked((LightData.LightAngle270.Light3G==0)?false:true);
    ui->toolButtonLightAngle270_3B->setChecked((LightData.LightAngle270.Light3B==0)?false:true);
    ui->toolButtonLightAngle270_3W->setChecked((LightData.LightAngle270.Light3W==0)?false:true);
}

void SettingLightBowl240RGBDialog::on_toolLight_clicked()
{
    LightTransaction();
}

void    SettingLightBowl240RGBDialog::LightTransaction(void)
{
    GetDataFromWindow();

    bool    OnMode=ui->toolButtonONMode->isChecked();
    Parent->Transfer(LightData ,OnMode);
    
}

void SettingLightBowl240RGBDialog::on_listWidgetPatternList_clicked(const QModelIndex &index)
{
    int Row=ui->listWidgetPatternList->currentRow();
    if(Row<0)
        return;
    //GetDataFromWindow();
    //if(CurrentDimRow>=0){
    //    LightDataDim[CurrentDimRow]=LightData;
    //}
    CurrentDimRow=Row;
    LightData=LightDataDim[Row];
    SetDataToWindow();

    ui->pushButtonModifyPattern->setEnabled(true);
    ui->pushButtonDeletePattern->setEnabled(true);
}


void SettingLightBowl240RGBDialog::on_pushButtonAll_clicked()
{
    EnableButtons=false;
    bool    LCkecked=false;
    if(ui->toolButtonLightTopR->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightTopG->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightTopB->isChecked()==true) LCkecked=true;

    if(ui->toolButtonLightAngle0_1R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_1G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_1B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_1W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_2R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_2G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_2B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_2W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_3R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_3G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_3B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_3W->isChecked()==true) LCkecked=true;

    if(ui->toolButtonLightAngle90_1R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_1G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_1B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_1W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_2R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_2G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_2B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_2W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_3R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_3G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_3B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_3W->isChecked()==true) LCkecked=true;

    if(ui->toolButtonLightAngle180_1R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_1G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_1B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_1W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_2R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_2G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_2B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_2W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_3R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_3G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_3B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_3W->isChecked()==true) LCkecked=true;

    if(ui->toolButtonLightAngle270_1R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_1G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_1B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_1W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_2R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_2G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_2B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_2W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_3R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_3G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_3B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_3W->isChecked()==true) LCkecked=true;

    LCkecked=!LCkecked;
    ui->toolButtonLightTopR->setChecked(LCkecked);
    ui->toolButtonLightTopG->setChecked(LCkecked);
    ui->toolButtonLightTopB->setChecked(LCkecked);

    ui->toolButtonLightAngle0_1R->setChecked(LCkecked);
    ui->toolButtonLightAngle0_1G->setChecked(LCkecked);
    ui->toolButtonLightAngle0_1B->setChecked(LCkecked);
    ui->toolButtonLightAngle0_1W->setChecked(LCkecked);
    ui->toolButtonLightAngle0_2R->setChecked(LCkecked);
    ui->toolButtonLightAngle0_2G->setChecked(LCkecked);
    ui->toolButtonLightAngle0_2B->setChecked(LCkecked);
    ui->toolButtonLightAngle0_2W->setChecked(LCkecked);
    ui->toolButtonLightAngle0_3R->setChecked(LCkecked);
    ui->toolButtonLightAngle0_3G->setChecked(LCkecked);
    ui->toolButtonLightAngle0_3B->setChecked(LCkecked);
    ui->toolButtonLightAngle0_3W->setChecked(LCkecked);

    ui->toolButtonLightAngle90_1R->setChecked(LCkecked);
    ui->toolButtonLightAngle90_1G->setChecked(LCkecked);
    ui->toolButtonLightAngle90_1B->setChecked(LCkecked);
    ui->toolButtonLightAngle90_1W->setChecked(LCkecked);
    ui->toolButtonLightAngle90_2R->setChecked(LCkecked);
    ui->toolButtonLightAngle90_2G->setChecked(LCkecked);
    ui->toolButtonLightAngle90_2B->setChecked(LCkecked);
    ui->toolButtonLightAngle90_2W->setChecked(LCkecked);
    ui->toolButtonLightAngle90_3R->setChecked(LCkecked);
    ui->toolButtonLightAngle90_3G->setChecked(LCkecked);
    ui->toolButtonLightAngle90_3B->setChecked(LCkecked);
    ui->toolButtonLightAngle90_3W->setChecked(LCkecked);

    ui->toolButtonLightAngle180_1R->setChecked(LCkecked);
    ui->toolButtonLightAngle180_1G->setChecked(LCkecked);
    ui->toolButtonLightAngle180_1B->setChecked(LCkecked);
    ui->toolButtonLightAngle180_1W->setChecked(LCkecked);
    ui->toolButtonLightAngle180_2R->setChecked(LCkecked);
    ui->toolButtonLightAngle180_2G->setChecked(LCkecked);
    ui->toolButtonLightAngle180_2B->setChecked(LCkecked);
    ui->toolButtonLightAngle180_2W->setChecked(LCkecked);
    ui->toolButtonLightAngle180_3R->setChecked(LCkecked);
    ui->toolButtonLightAngle180_3G->setChecked(LCkecked);
    ui->toolButtonLightAngle180_3B->setChecked(LCkecked);
    ui->toolButtonLightAngle180_3W->setChecked(LCkecked);

    ui->toolButtonLightAngle270_1R->setChecked(LCkecked);
    ui->toolButtonLightAngle270_1G->setChecked(LCkecked);
    ui->toolButtonLightAngle270_1B->setChecked(LCkecked);
    ui->toolButtonLightAngle270_1W->setChecked(LCkecked);
    ui->toolButtonLightAngle270_2R->setChecked(LCkecked);
    ui->toolButtonLightAngle270_2G->setChecked(LCkecked);
    ui->toolButtonLightAngle270_2B->setChecked(LCkecked);
    ui->toolButtonLightAngle270_2W->setChecked(LCkecked);
    ui->toolButtonLightAngle270_3R->setChecked(LCkecked);
    ui->toolButtonLightAngle270_3G->setChecked(LCkecked);
    ui->toolButtonLightAngle270_3B->setChecked(LCkecked);
    ui->toolButtonLightAngle270_3W->setChecked(LCkecked);

    EnableButtons=true;
    LightTransaction();
}


void SettingLightBowl240RGBDialog::on_pushButtonTop_clicked()
{
    EnableButtons=false;
    bool    LCkecked=false;
    if(ui->toolButtonLightTopR->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightTopG->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightTopB->isChecked()==true) LCkecked=true;

    LCkecked=!LCkecked;
    ui->toolButtonLightTopR->setChecked(LCkecked);
    ui->toolButtonLightTopG->setChecked(LCkecked);
    ui->toolButtonLightTopB->setChecked(LCkecked);

    EnableButtons=true;
    LightTransaction();
}


void SettingLightBowl240RGBDialog::on_pushButtonStep1_clicked()
{
    EnableButtons=false;
    bool    LCkecked=false;

    if(ui->toolButtonLightAngle0_1R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_1G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_1B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_1W->isChecked()==true) LCkecked=true;

    if(ui->toolButtonLightAngle90_1R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_1G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_1B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_1W->isChecked()==true) LCkecked=true;

    if(ui->toolButtonLightAngle180_1R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_1G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_1B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_1W->isChecked()==true) LCkecked=true;

    if(ui->toolButtonLightAngle270_1R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_1G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_1B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_1W->isChecked()==true) LCkecked=true;

    LCkecked=!LCkecked;
    ui->toolButtonLightAngle0_1R->setChecked(LCkecked);
    ui->toolButtonLightAngle0_1G->setChecked(LCkecked);
    ui->toolButtonLightAngle0_1B->setChecked(LCkecked);
    ui->toolButtonLightAngle0_1W->setChecked(LCkecked);
    ui->toolButtonLightAngle90_1R->setChecked(LCkecked);
    ui->toolButtonLightAngle90_1G->setChecked(LCkecked);
    ui->toolButtonLightAngle90_1B->setChecked(LCkecked);
    ui->toolButtonLightAngle90_1W->setChecked(LCkecked);
    ui->toolButtonLightAngle180_1R->setChecked(LCkecked);
    ui->toolButtonLightAngle180_1G->setChecked(LCkecked);
    ui->toolButtonLightAngle180_1B->setChecked(LCkecked);
    ui->toolButtonLightAngle180_1W->setChecked(LCkecked);
    ui->toolButtonLightAngle270_1R->setChecked(LCkecked);
    ui->toolButtonLightAngle270_1G->setChecked(LCkecked);
    ui->toolButtonLightAngle270_1B->setChecked(LCkecked);
    ui->toolButtonLightAngle270_1W->setChecked(LCkecked);

    EnableButtons=true;
    LightTransaction();
}


void SettingLightBowl240RGBDialog::on_pushButtonStep2_clicked()
{
    EnableButtons=false;
    bool    LCkecked=false;
    if(ui->toolButtonLightAngle0_2R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_2G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_2B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_2W->isChecked()==true) LCkecked=true;

    if(ui->toolButtonLightAngle90_2R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_2G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_2B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_2W->isChecked()==true) LCkecked=true;

    if(ui->toolButtonLightAngle180_2R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_2G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_2B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_2W->isChecked()==true) LCkecked=true;

    if(ui->toolButtonLightAngle270_2R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_2G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_2B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_2W->isChecked()==true) LCkecked=true;

    LCkecked=!LCkecked;
    ui->toolButtonLightAngle0_2R->setChecked(LCkecked);
    ui->toolButtonLightAngle0_2G->setChecked(LCkecked);
    ui->toolButtonLightAngle0_2B->setChecked(LCkecked);
    ui->toolButtonLightAngle0_2W->setChecked(LCkecked);
    ui->toolButtonLightAngle90_2R->setChecked(LCkecked);
    ui->toolButtonLightAngle90_2G->setChecked(LCkecked);
    ui->toolButtonLightAngle90_2B->setChecked(LCkecked);
    ui->toolButtonLightAngle90_2W->setChecked(LCkecked);
    ui->toolButtonLightAngle180_2R->setChecked(LCkecked);
    ui->toolButtonLightAngle180_2G->setChecked(LCkecked);
    ui->toolButtonLightAngle180_2B->setChecked(LCkecked);
    ui->toolButtonLightAngle180_2W->setChecked(LCkecked);
    ui->toolButtonLightAngle270_2R->setChecked(LCkecked);
    ui->toolButtonLightAngle270_2G->setChecked(LCkecked);
    ui->toolButtonLightAngle270_2B->setChecked(LCkecked);
    ui->toolButtonLightAngle270_2W->setChecked(LCkecked);

    EnableButtons=true;
    LightTransaction();
}


void SettingLightBowl240RGBDialog::on_pushButtonStep3_clicked()
{
    EnableButtons=false;
    bool    LCkecked=false;
    if(ui->toolButtonLightAngle0_3R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_3G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_3B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_3W->isChecked()==true) LCkecked=true;

    if(ui->toolButtonLightAngle90_3R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_3G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_3B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_3W->isChecked()==true) LCkecked=true;

    if(ui->toolButtonLightAngle180_3R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_3G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_3B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_3W->isChecked()==true) LCkecked=true;

    if(ui->toolButtonLightAngle270_3R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_3G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_3B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_3W->isChecked()==true) LCkecked=true;

    LCkecked=!LCkecked;
    ui->toolButtonLightAngle0_3R->setChecked(LCkecked);
    ui->toolButtonLightAngle0_3G->setChecked(LCkecked);
    ui->toolButtonLightAngle0_3B->setChecked(LCkecked);
    ui->toolButtonLightAngle0_3W->setChecked(LCkecked);
    ui->toolButtonLightAngle90_3R->setChecked(LCkecked);
    ui->toolButtonLightAngle90_3G->setChecked(LCkecked);
    ui->toolButtonLightAngle90_3B->setChecked(LCkecked);
    ui->toolButtonLightAngle90_3W->setChecked(LCkecked);
    ui->toolButtonLightAngle180_3R->setChecked(LCkecked);
    ui->toolButtonLightAngle180_3G->setChecked(LCkecked);
    ui->toolButtonLightAngle180_3B->setChecked(LCkecked);
    ui->toolButtonLightAngle180_3W->setChecked(LCkecked);
    ui->toolButtonLightAngle270_3R->setChecked(LCkecked);
    ui->toolButtonLightAngle270_3G->setChecked(LCkecked);
    ui->toolButtonLightAngle270_3B->setChecked(LCkecked);
    ui->toolButtonLightAngle270_3W->setChecked(LCkecked);

    EnableButtons=true;
    LightTransaction();
}


void SettingLightBowl240RGBDialog::on_pushButtonAngle0_clicked()
{
    EnableButtons=false;
    bool    LCkecked=false;
    if(ui->toolButtonLightAngle0_1R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_1G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_1B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_1W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_2R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_2G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_2B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_2W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_3R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_3G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_3B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle0_3W->isChecked()==true) LCkecked=true;

    LCkecked=!LCkecked;
    ui->toolButtonLightAngle0_1R->setChecked(LCkecked);
    ui->toolButtonLightAngle0_1G->setChecked(LCkecked);
    ui->toolButtonLightAngle0_1B->setChecked(LCkecked);
    ui->toolButtonLightAngle0_1W->setChecked(LCkecked);
    ui->toolButtonLightAngle0_2R->setChecked(LCkecked);
    ui->toolButtonLightAngle0_2G->setChecked(LCkecked);
    ui->toolButtonLightAngle0_2B->setChecked(LCkecked);
    ui->toolButtonLightAngle0_2W->setChecked(LCkecked);
    ui->toolButtonLightAngle0_3R->setChecked(LCkecked);
    ui->toolButtonLightAngle0_3G->setChecked(LCkecked);
    ui->toolButtonLightAngle0_3B->setChecked(LCkecked);
    ui->toolButtonLightAngle0_3W->setChecked(LCkecked);

    EnableButtons=true;
    LightTransaction();
}


void SettingLightBowl240RGBDialog::on_pushButtonAngle90_clicked()
{
    EnableButtons=false;
    bool    LCkecked=false;
    if(ui->toolButtonLightAngle90_1R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_1G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_1B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_1W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_2R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_2G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_2B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_2W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_3R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_3G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_3B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle90_3W->isChecked()==true) LCkecked=true;

    LCkecked=!LCkecked;
    ui->toolButtonLightAngle90_1R->setChecked(LCkecked);
    ui->toolButtonLightAngle90_1G->setChecked(LCkecked);
    ui->toolButtonLightAngle90_1B->setChecked(LCkecked);
    ui->toolButtonLightAngle90_1W->setChecked(LCkecked);
    ui->toolButtonLightAngle90_2R->setChecked(LCkecked);
    ui->toolButtonLightAngle90_2G->setChecked(LCkecked);
    ui->toolButtonLightAngle90_2B->setChecked(LCkecked);
    ui->toolButtonLightAngle90_2W->setChecked(LCkecked);
    ui->toolButtonLightAngle90_3R->setChecked(LCkecked);
    ui->toolButtonLightAngle90_3G->setChecked(LCkecked);
    ui->toolButtonLightAngle90_3B->setChecked(LCkecked);
    ui->toolButtonLightAngle90_3W->setChecked(LCkecked);

    EnableButtons=true;
    LightTransaction();
}


void SettingLightBowl240RGBDialog::on_pushButtonAngle180_clicked()
{
    EnableButtons=false;
    bool    LCkecked=false;
    if(ui->toolButtonLightAngle180_1R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_1G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_1B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_1W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_2R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_2G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_2B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_2W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_3R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_3G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_3B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle180_3W->isChecked()==true) LCkecked=true;

    LCkecked=!LCkecked;
    ui->toolButtonLightAngle180_1R->setChecked(LCkecked);
    ui->toolButtonLightAngle180_1G->setChecked(LCkecked);
    ui->toolButtonLightAngle180_1B->setChecked(LCkecked);
    ui->toolButtonLightAngle180_1W->setChecked(LCkecked);
    ui->toolButtonLightAngle180_2R->setChecked(LCkecked);
    ui->toolButtonLightAngle180_2G->setChecked(LCkecked);
    ui->toolButtonLightAngle180_2B->setChecked(LCkecked);
    ui->toolButtonLightAngle180_2W->setChecked(LCkecked);
    ui->toolButtonLightAngle180_3R->setChecked(LCkecked);
    ui->toolButtonLightAngle180_3G->setChecked(LCkecked);
    ui->toolButtonLightAngle180_3B->setChecked(LCkecked);
    ui->toolButtonLightAngle180_3W->setChecked(LCkecked);

    EnableButtons=true;
    LightTransaction();
}


void SettingLightBowl240RGBDialog::on_pushButton270_clicked()
{
    EnableButtons=false;
    bool    LCkecked=false;
    if(ui->toolButtonLightAngle270_1R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_1G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_1B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_1W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_2R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_2G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_2B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_2W->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_3R->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_3G->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_3B->isChecked()==true) LCkecked=true;
    if(ui->toolButtonLightAngle270_3W->isChecked()==true) LCkecked=true;

    LCkecked=!LCkecked;
    ui->toolButtonLightAngle270_1R->setChecked(LCkecked);
    ui->toolButtonLightAngle270_1G->setChecked(LCkecked);
    ui->toolButtonLightAngle270_1B->setChecked(LCkecked);
    ui->toolButtonLightAngle270_1W->setChecked(LCkecked);
    ui->toolButtonLightAngle270_2R->setChecked(LCkecked);
    ui->toolButtonLightAngle270_2G->setChecked(LCkecked);
    ui->toolButtonLightAngle270_2B->setChecked(LCkecked);
    ui->toolButtonLightAngle270_2W->setChecked(LCkecked);
    ui->toolButtonLightAngle270_3R->setChecked(LCkecked);
    ui->toolButtonLightAngle270_3G->setChecked(LCkecked);
    ui->toolButtonLightAngle270_3B->setChecked(LCkecked);
    ui->toolButtonLightAngle270_3W->setChecked(LCkecked);

    EnableButtons=true;
    LightTransaction();
}

void    SettingLightBowl240RGBDialog::ShowList(void)
{
    ui->listWidgetPatternList->clear();
    for(int i=0;i<CountOfLightDataDim && i<MaxDimCountLightBowl240RGBW;i++){
        ui->listWidgetPatternList->addItem(LightDataDim[i].PatternName);
    }
}

void SettingLightBowl240RGBDialog::on_pushButtonAddPattern_clicked()
{
    CurrentDimRow=CountOfLightDataDim;
    if(CurrentDimRow<MaxDimCountLightBowl240RGBW){
        GetDataFromWindow();
        LightDataDim[CurrentDimRow]=LightData;
        CountOfLightDataDim++;
        ShowList();
        ui->listWidgetPatternList->setCurrentRow(CurrentDimRow);
    }
}


void SettingLightBowl240RGBDialog::on_pushButtonModifyPattern_clicked()
{
    int Row=ui->listWidgetPatternList->currentRow();
    if(Row<0)
        return;

    GetDataFromWindow();
    LightDataDim[Row]=LightData;
    ShowList();
    ui->listWidgetPatternList->setCurrentRow(Row);
}


void SettingLightBowl240RGBDialog::on_pushButtonDeletePattern_clicked()
{
    int Row=ui->listWidgetPatternList->currentRow();
    if(Row<0)
        return;
    for(int i=Row;i<CountOfLightDataDim-1;i++){
        LightDataDim[i]=LightDataDim[i+1];
    }
    CountOfLightDataDim--;
    ShowList();
    if(CountOfLightDataDim>0){
        if(Row<CountOfLightDataDim)
            ui->listWidgetPatternList->setCurrentRow(Row);
        else
            ui->listWidgetPatternList->setCurrentRow(Row-1);
    }
}


void SettingLightBowl240RGBDialog::on_pushButtonOK_clicked()
{
    IPAddress=ui->lineEditIPAddress->text();
    done(true);
}


void SettingLightBowl240RGBDialog::on_pushButtonCancel_clicked()
{
    done(false);
}


void SettingLightBowl240RGBDialog::on_toolButtonONMode_clicked()
{
    LightTransaction();
}

