#ifndef SHOWLEDCONTROL16GFORM_H
#define SHOWLEDCONTROL16GFORM_H

#include <QWidget>
#include <QModelIndex>
#include "LightDeviceStruct.h"
#include <QMutex>
#include "NListRPi.h"
#include "DeviceStruct.h"
#include "XLightControlToPC.h"

namespace Ui {
class ShowLEDControl16GForm;
}

#define MaxDipSW    16

class ShowLEDControl16GForm : public QWidget
{
    Q_OBJECT
    
public:
    LightBoard  BoardData[MaxBoardCount];
    int         BoardCount;
    LightControlToPCServer  Server;
    char     BoardName[MaxBoardCount][30];
public:
    explicit ShowLEDControl16GForm(QWidget *parent = 0);
    ~ShowLEDControl16GForm();
    
    void    WriteInitial(void);
    void	SetTestLED(int DipSW ,bool b);
    void	SetAllOn(int DipSW ,bool OnMode);
    void	SetAllCurrentPattern(int DipSW ,int PatternNo);

private slots:
    void on_listWidgetDipSW_itemSelectionChanged();
    void on_spinBoxPatternNo_valueChanged(int arg1);
    void on_listWidgetDipSW_doubleClicked(const QModelIndex &index);
    void on_toolButtonAllON_clicked();
    void on_toolButtonSave_clicked();
    void on_pushButtonUpdate_clicked();

private:
    Ui::ShowLEDControl16GForm *ui;

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
    void    GetBoardName(int n,int DipSW);
};

#endif // SHOWLEDCONTROL16GFORM_H
