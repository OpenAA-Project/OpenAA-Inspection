/*
 * Copyright (C) 2022
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SHOWLEDCONTROL16HFORM_H
#define SHOWLEDCONTROL16HFORM_H

#include <QWidget>
#include <QModelIndex>
#include "LightDeviceStruct.h"
#include <QMutex>
#include "NListRPi.h"
#include "DeviceStruct.h"
#include "XLightControlToPC.h"

namespace Ui {
class ShowLEDControl16HForm;
}
class LEDControl16HioPrnRasPIMain;

class ShowLEDControl16HForm : public QWidget
{
    Q_OBJECT
public:
    LEDControl16HioPrnRasPIMain   *Parent;
    LightBoard  BoardData[MaxBoardCount];
    int         BoardCount;
    LightControlToPCServer  Server;
    char     BoardName[MaxBoardCount][30];
public:
    explicit ShowLEDControl16HForm(LEDControl16HioPrnRasPIMain *p, QWidget *parent = nullptr);
    ~ShowLEDControl16HForm();
    
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
    Ui::ShowLEDControl16HForm *ui;
    
    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
    void    GetBoardName(int n,int DipSW);
};

#endif // SHOWLEDCONTROL16HFORM_H