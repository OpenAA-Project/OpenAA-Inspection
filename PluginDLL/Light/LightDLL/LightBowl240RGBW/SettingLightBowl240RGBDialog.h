#ifndef SETTINGLIGHTBOWL240RGBDIALOG_H
#define SETTINGLIGHTBOWL240RGBDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QString>
#include "XParamRobot.h"
#include "XServiceForLayers.h"
#include "LightBowl240RGBW.h"

namespace Ui {
class SettingLightBowl240RGBDialog;
}

class	LightBowl240RGBW;

class SettingLightBowl240RGBDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    LightBowl240RGBW    *Parent;
public:
    QString     IPAddress;
    int         CountOfLightDataDim;
    ParamLightInfo  LightDataDim[MaxDimCountLightBowl240RGBW];
    ParamLightInfo  LightData;
    bool        EnableButtons;
    int         CurrentDimRow;
public:
    explicit SettingLightBowl240RGBDialog(LightBowl240RGBW *p,LayersBase *base,QWidget *parent = nullptr);
    ~SettingLightBowl240RGBDialog();

    void    SetInitial(LightBowl240RGBW *s);

private slots:
    void on_listWidgetPatternList_clicked(const QModelIndex &index);
    void on_pushButtonAll_clicked();
    void on_pushButtonTop_clicked();
    void on_pushButtonStep1_clicked();
    void on_pushButtonStep2_clicked();
    void on_pushButtonStep3_clicked();
    void on_pushButtonAngle0_clicked();
    void on_pushButtonAngle90_clicked();
    void on_pushButtonAngle180_clicked();
    void on_pushButton270_clicked();
    void on_pushButtonAddPattern_clicked();
    void on_pushButtonModifyPattern_clicked();
    void on_pushButtonDeletePattern_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_toolLight_clicked();

    void on_toolButtonONMode_clicked();

private:
    Ui::SettingLightBowl240RGBDialog *ui;

    void	GetDataFromWindow(void);
    void	SetDataToWindow(void);
    void    LightTransaction(void);
    void    ShowList(void);
};

#endif // SETTINGLIGHTBOWL240RGBDIALOG_H
