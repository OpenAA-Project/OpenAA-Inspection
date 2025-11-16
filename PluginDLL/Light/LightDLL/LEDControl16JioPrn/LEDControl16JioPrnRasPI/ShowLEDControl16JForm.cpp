#include "ShowLEDControl16JForm.h"
#include "ui_ShowLEDControl16JForm.h"
#include <QFile>
#include "XTypeDef.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XCommToTrigger.h"
#include "LEDControl16JioPrnRasPIMain.h"

QString     SettingFileName="LightSetting.dat";


ShowLEDControl16JForm::ShowLEDControl16JForm(LEDControl16JioPrnRasPIMain *p,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowLEDControl16JForm)
    ,Server(this)
    ,Parent(p)
{
    ui->setupUi(this);
    
    Server.StartListen();
}

ShowLEDControl16JForm::~ShowLEDControl16JForm()
{
    delete ui;
}
void    ShowLEDControl16JForm::WriteInitial(void)
{
    int data=0;
    int DipSWTable[MaxDipSW];
    BoardCount=0;
    //WriteRegisterData(0xFF);
    for(int n=0;n<MaxDipSW;n++){
        int dipsw=ReadBoardID(n);
        if(dipsw>=0){
            BoardData[BoardCount].DipSW=dipsw;
            BoardData[BoardCount].Brd=n;
            DipSWTable[BoardCount]=dipsw;
            BoardCount++;
        }
        else{
            DipSWTable[BoardCount]=-1;
        }
    }

    for(int Brd=0;Brd<BoardCount;Brd++){
        Parent->SendLightTestLEDON(Brd,true);
        Parent->SendLightTestLEDON(Brd,false);
        Parent->SendLightTestLEDON(Brd,true);
    }

    for(int Brd=0;Brd<BoardCount;Brd++){
        Parent->SendLightBoardON(Brd,false);
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
        BoardData[Brd].SetAllON(Parent,BoardData[Brd].AllON);
        BoardData[Brd].GetCurrentValue(Parent);
    }
    for(int Brd=0;Brd<BoardCount;Brd++){
        if(BoardData[Brd].AllON==true)
            ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::red);
        else
            ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::white);
    }
    CurrentBrdNo=-1;
    if(BoardCount>0){
        CurrentBrdNo=0;
        ui->listWidgetDipSW->setCurrentRow(CurrentBrdNo);
    }
    ShowGrid();
}

void ShowLEDControl16JForm::ShowGrid(void)
{
    int BrdNo=ui->listWidgetDipSW->currentRow();
    if(BrdNo<0)
        return;

    for(int L=0;L<MaxCountLines;L++){
        ::SetDataToTable(ui->tableWidget,0,L,BoardData[BrdNo].LineInfo[0].TargetValue[L],Qt::ItemIsEditable);
        ::SetDataToTable(ui->tableWidget,1,L,BoardData[BrdNo].CurrentValue[L]);
    }
}
void ShowLEDControl16JForm::GetFromGrid(void)
{
    int BrdNo=CurrentBrdNo;

    for(int L=0;L<MaxCountLines;L++){
        QString s=::GetDataToTable(ui->tableWidget,0,L);
        BoardData[BrdNo].LineInfo[0].TargetValue[L]=s.toInt();
    }
    CurrentBrdNo=ui->listWidgetDipSW->currentRow();
}

void ShowLEDControl16JForm::on_listWidgetDipSW_itemSelectionChanged()
{
    GetFromGrid();
    ShowGrid();
}

void ShowLEDControl16JForm::on_spinBoxPatternNo_valueChanged(int arg1)
{

}

void ShowLEDControl16JForm::on_listWidgetDipSW_doubleClicked(const QModelIndex &index)
{

}

void ShowLEDControl16JForm::on_toolButtonAllON_clicked()
{
    bool    B=ui->toolButtonAllON->isChecked();
    for(int Brd=0;Brd<BoardCount;Brd++){
        BoardData[Brd].SetAllON(Parent,B);
    }
}

void ShowLEDControl16JForm::on_toolButtonSave_clicked()
{

}

void ShowLEDControl16JForm::on_pushButtonUpdate_clicked()
{

}
int	ShowLEDControl16JForm::ReadBoardID(int n)
{
    return Parent->ReadLightBoardID(n);
}
//-------------------------------------------------------------------
bool    ShowLEDControl16JForm::Save(QIODevice *f)
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

bool    ShowLEDControl16JForm::Load(QIODevice *f)
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

void	ShowLEDControl16JForm::SetTestLED(int DipSW ,bool b)
{
    for(int brd=0;brd<BoardCount;brd++){
        if(BoardData[brd].DipSW==DipSW){
            BoardData[brd].SetTestLED(Parent,b);
        }
    }
}
void	ShowLEDControl16JForm::SetAllOn(int DipSW ,bool OnMode)
{
    for(int brd=0;brd<BoardCount;brd++){
        if(BoardData[brd].DipSW==DipSW){
            BoardData[brd].AllON=OnMode;
            BoardData[brd].SetAllON(Parent,OnMode);
        }
    }
}
void	ShowLEDControl16JForm::SetAllCurrentPattern(int DipSW ,int PatternNo)
{
    for(int brd=0;brd<BoardCount;brd++){
        if(BoardData[brd].DipSW==DipSW){
            BoardData[brd].SetCurrentPatternNo(Parent,PatternNo);
        }
    }
}
