#include "ShowLEDControl16GForm.h"
#include "ui_ShowLEDControl16GForm.h"
#include <QFile>
#include "XTypeDef.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XCommToTrigger.h"

QString     SettingFileName="LightSetting.dat";

ShowLEDControl16GForm::ShowLEDControl16GForm(LEDControl16GPrnRasPi *p,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowLEDControl16GForm)
    ,Server(this)
    ,Parent(p)
{
    ui->setupUi(this);

    WriteInitial();
    Server.StartListen();
}

ShowLEDControl16GForm::~ShowLEDControl16GForm()
{
    delete ui;
}

void    ShowLEDControl16GForm::WriteInitial(void)
{
    int data;
    int DipSWTable[MaxDipSW];
    BoardCount=0;
    WriteRegisterData(0xFF);
    for(int dipsw=0;dipsw<MaxDipSW;dipsw++){
        data=ReadBoardID(dipsw);
        if(data==1){
            BoardData[BoardCount].DipSW=dipsw;
            DipSWTable[BoardCount]=dipsw;
            BoardCount++;
        }
        else{
            DipSWTable[BoardCount]=-1;
        }
    }
    for(int Brd=0;Brd<BoardCount;Brd++){
        GetBoardName(Brd,BoardData[Brd].DipSW);
    }

    for(int Brd=0;Brd<BoardCount;Brd++){
        BoardData[Brd].SetTestLED(true);
        BoardData[Brd].SetTestLED(false);
        BoardData[Brd].SetTestLED(true);
    }

    for(int Brd=0;Brd<BoardCount;Brd++){
        BoardData[Brd].SetAllON(false);
    }

    ui->listWidgetDipSW->clear();
    for(int Brd=0;Brd<BoardCount;Brd++){
        ui->listWidgetDipSW->addItem (QString::number(BoardData[Brd].DipSW));
    }

    QFile   File(SettingFileName);
    if(File.open(QIODevice::ReadOnly)==true){
        Load(&File);
    }

    for(int Brd=0;Brd<BoardCount;Brd++){
        BoardData[Brd].SetAllON(BoardData[Brd].AllON);
        BoardData[Brd].GetCurrentValue();
    }
    for(int Brd=0;Brd<BoardCount;Brd++){
        if(BoardData[Brd].AllON==true)
            ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::red);
        else
            ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::white);
    }
    if(BoardCount>0){
        ui->listWidgetDipSW->setCurrentRow(0);
    }
}

void ShowLEDControl16GForm::on_listWidgetDipSW_itemSelectionChanged()
{
    int Brd=ui->listWidgetDipSW->currentRow();
    if(Brd<0)
        return;
    ui->tableWidget->setRowCount(MaxCountLines);
    int PatternNo=ui->spinBoxPatternNo->value();
    BoardData[Brd].GetLightData(PatternNo);
    BoardData[Brd].GetCurrentValue();
    for(int Row=0;Row<MaxCountLines;Row++){
        long    int V=BoardData[Brd].LineInfo[Row].TargetValue[PatternNo];
        ::SetDataToTable(ui->tableWidget ,0 ,Row ,QString::number(V));
        long    int A=BoardData[Brd].LineInfo[Row].CurrentValue;
        ::SetDataToTable(ui->tableWidget ,1 ,Row ,QString::number(A));
    }
}

void ShowLEDControl16GForm::on_spinBoxPatternNo_valueChanged(int arg1)
{
    int PatternNo=ui->spinBoxPatternNo->value();
    for(int Brd=0;Brd<BoardCount;Brd++){
        BoardData[Brd].SetCurrentPatternNo(PatternNo);
    }
    on_listWidgetDipSW_itemSelectionChanged();
}

void ShowLEDControl16GForm::on_listWidgetDipSW_doubleClicked(const QModelIndex &index)
{
    int Brd=ui->listWidgetDipSW->currentRow();

    BoardData[Brd].AllON=!BoardData[Brd].AllON;
    BoardData[Brd].SetAllON(BoardData[Brd].AllON);

    if(BoardData[Brd].AllON==true)
        ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::red);
    else
        ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::white);
}

void ShowLEDControl16GForm::on_toolButtonAllON_clicked()
{
    bool    b=ui->toolButtonAllON->isChecked();
    for(int Brd=0;Brd<BoardCount;Brd++){
        BoardData[Brd].AllON=b;
        BoardData[Brd].SetAllON(BoardData[Brd].AllON);
    }
    for(int Brd=0;Brd<BoardCount;Brd++){
        if(BoardData[Brd].AllON==true)
            ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::red);
        else
            ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::white);
    }
    for(int Brd=0;Brd<BoardCount;Brd++){
        BoardData[Brd].GetCurrentValue();
    }
    on_listWidgetDipSW_itemSelectionChanged();
}

void ShowLEDControl16GForm::on_toolButtonSave_clicked()
{
    QFile   File(SettingFileName);
    if(File.open(QIODevice::WriteOnly)==true){
        Save(&File);
    }
}

void ShowLEDControl16GForm::on_pushButtonUpdate_clicked()
{
    on_listWidgetDipSW_itemSelectionChanged();
}
//-------------------------------------------------------------------
bool    ShowLEDControl16GForm::Save(QIODevice *f)
{
    BYTE    Ver=1;

    if(::Save(f,Ver)==false)
        return false;
    int32 N=sizeof(BoardData)/sizeof(BoardData[0]);

    if(::Save(f,N)==false)
        return false;
    for(int i=0;i<N;i++){
        if(BoardData[i].Save(f)==false){
            return false;
        }
    }
    return true;
}

bool    ShowLEDControl16GForm::Load(QIODevice *f)
{
    BYTE    Ver;

    if(::Load(f,Ver)==false)
        return false;
    int32 N=sizeof(BoardData)/sizeof(BoardData[0]);
    int32   iN;

    if(::Load(f,iN)==false)
        return false;
    for(int i=0;i<N && i<iN;i++){
        if(BoardData[i].Load(f)==false){
            return false;
        }
    }
    return true;
}

//-------------------------------------------------------------------

void	ShowLEDControl16GForm::SetTestLED(int DipSW ,bool b)
{
    for(int brd=0;brd<BoardCount;brd++){
        if(BoardData[brd].DipSW==DipSW){
            BoardData[brd].SetTestLED(b);
        }
    }
}
void	ShowLEDControl16GForm::SetAllOn(int DipSW ,bool OnMode)
{
    for(int brd=0;brd<BoardCount;brd++){
        if(BoardData[brd].DipSW==DipSW){
            BoardData[brd].AllON=OnMode;
            BoardData[brd].SetAllON(OnMode);
        }
    }
}
void	ShowLEDControl16GForm::SetAllCurrentPattern(int DipSW ,int PatternNo)
{
    for(int brd=0;brd<BoardCount;brd++){
        if(BoardData[brd].DipSW==DipSW){
            BoardData[brd].SetCurrentPatternNo(PatternNo);
        }
    }
}
void    ShowLEDControl16GForm::GetBoardName(int n,int DipSW)
{
    WriteRegisterData(0xFD);
    int Data[100];
    ReadRegister4Bit(DipSW ,Data ,2);

    int Len=(Data[0]&0xF) + ((Data[1]&0xF)<<4);

    if(0<=Len && Len<30){
        WriteRegisterData(0xFC);
        ReadRegister4Bit(DipSW ,Data ,Len*2);
        for(int i=0;i<Len;i++){
            BoardName[n][i]=(Data[i*2]&0xF) + ((Data[i*2+1]&0xF)<<4);
        }
        BoardName[n][Len]=0;
    }
}
void    ShowLEDControl16GForm::ResetCounter(void)
{
    Server.ResetCounter();
}

