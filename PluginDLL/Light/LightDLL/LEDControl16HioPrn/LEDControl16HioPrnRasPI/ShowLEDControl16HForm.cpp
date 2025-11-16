#include "ShowLEDControl16HForm.h"
#include "ui_ShowLEDControl16HForm.h"
#include <QFile>
#include "XTypeDef.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XCommToTrigger.h"

QString     SettingFileName="LightSetting.dat";


ShowLEDControl16HForm::ShowLEDControl16HForm(LEDControl16HioPrnRasPIMain *p,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowLEDControl16HForm)
    ,Server(this)
    ,Parent(p)
{
    ui->setupUi(this);
    
    Server.StartListen();
}

ShowLEDControl16HForm::~ShowLEDControl16HForm()
{
    delete ui;
}
void    ShowLEDControl16HForm::WriteInitial(void)
{
    int data=0;
    int DipSWTable[MaxDipSW];
    BoardCount=0;
    //WriteRegisterData(0xFF);
    for(int dipsw=0;dipsw<MaxDipSW;dipsw++){
        //data=ReadBoardID(dipsw);
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

void ShowLEDControl16HForm::on_listWidgetDipSW_itemSelectionChanged()
{

}

void ShowLEDControl16HForm::on_spinBoxPatternNo_valueChanged(int arg1)
{

}

void ShowLEDControl16HForm::on_listWidgetDipSW_doubleClicked(const QModelIndex &index)
{

}

void ShowLEDControl16HForm::on_toolButtonAllON_clicked()
{

}

void ShowLEDControl16HForm::on_toolButtonSave_clicked()
{

}

void ShowLEDControl16HForm::on_pushButtonUpdate_clicked()
{

}
//-------------------------------------------------------------------
bool    ShowLEDControl16HForm::Save(QIODevice *f)
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

bool    ShowLEDControl16HForm::Load(QIODevice *f)
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

void	ShowLEDControl16HForm::SetTestLED(int DipSW ,bool b)
{
    for(int brd=0;brd<BoardCount;brd++){
        if(BoardData[brd].DipSW==DipSW){
            BoardData[brd].SetTestLED(b);
        }
    }
}
void	ShowLEDControl16HForm::SetAllOn(int DipSW ,bool OnMode)
{
    for(int brd=0;brd<BoardCount;brd++){
        if(BoardData[brd].DipSW==DipSW){
            BoardData[brd].AllON=OnMode;
            BoardData[brd].SetAllON(OnMode);
        }
    }
}
void	ShowLEDControl16HForm::SetAllCurrentPattern(int DipSW ,int PatternNo)
{
    for(int brd=0;brd<BoardCount;brd++){
        if(BoardData[brd].DipSW==DipSW){
            BoardData[brd].SetCurrentPatternNo(PatternNo);
        }
    }
}
void    ShowLEDControl16HForm::GetBoardName(int n,int DipSW)
{
}
