#ifndef SHOWLEDCONTROL16JForm_H
#define SHOWLEDCONTROL16JForm_H

#include <QWidget>
#include <QModelIndex>
#include "LightDeviceStruct.h"
#include <QMutex>
#include "NListRPi.h"
#include "DeviceStruct.h"
#include "XLightControlToPC.h"

namespace Ui {
class ShowLEDControl16JForm;
}
class LEDControl16JioPrnRasPIMain;


class ShowLEDControl16JForm : public QWidget
{
    Q_OBJECT
public:
    LEDControl16JioPrnRasPIMain   *Parent;
    LightBoard  BoardData[MaxBoardCount];
    int         BoardCount;
    LightControlToPCServer  Server;
    char     BoardName[MaxBoardCount][30];
    int     CurrentBrdNo;
public:
    explicit ShowLEDControl16JForm(LEDControl16JioPrnRasPIMain *p, QWidget *parent = nullptr);
    ~ShowLEDControl16JForm();
    
    void    WriteInitial(void);
    void	SetTestLED(int DipSW ,bool b);
    void	SetAllOn(int DipSW ,bool OnMode);
    void	SetAllCurrentPattern(int DipSW ,int PatternNo);
    int     ReadBoardID(int n);
private slots:
    void on_listWidgetDipSW_itemSelectionChanged();
    void on_spinBoxPatternNo_valueChanged(int arg1);
    void on_listWidgetDipSW_doubleClicked(const QModelIndex &index);
    void on_toolButtonAllON_clicked();
    void on_toolButtonSave_clicked();
    void on_pushButtonUpdate_clicked();

private:
    Ui::ShowLEDControl16JForm *ui;
    
    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
    void    GetBoardName(int n,int DipSW);

    void ShowGrid(void);
    void GetFromGrid(void);
};

#endif // SHOWLEDCONTROL16JForm_H
