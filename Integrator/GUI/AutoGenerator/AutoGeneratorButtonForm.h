/*
 * Copyright (C) 2024
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

#ifndef AUTOGENERATORBUTTONFORM_H
#define AUTOGENERATORBUTTONFORM_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XAutoGenerator.h"


namespace Ui {
class AutoGeneratorButtonForm;
}

class AutoGeneratorForm;
class	SignalOperandInt;
class	SignalOperandBit;

class AutoGeneratorButtonForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

    AutoGeneratorForm   *Window;
    SignalOperandBit	*iEnableRunning;
    SignalOperandBit	*iAlarm;
    GUIFormBase	        *FormRun;
public:
    ListAutoGeneratorContainer  ListContainer;
    QString                     DefaultListFileName;
    int32                       RegNumberEnableRunning;
    int32                       RegNumberAlarm;
    ListAutoGenerator           CurrentList;    //Don't set pointer fot editting list

    explicit AutoGeneratorButtonForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~AutoGeneratorButtonForm();

    virtual void	Prepare(void)		override;
    virtual void	AfterStartSequence(void)    override;

    virtual	void	TransmitDirectly(GUIDirectMessage *packet)  override;
    virtual	void	BuildForShow(void)  override;

    void    SaveListContainer(void);
    void	SetRun(bool StateRun);
    void	SetInspectionRunOnly(bool StateRun);

private slots:
    void on_PushButtonRun_clicked();
    void on_PushButtonSetting_clicked();
    void on_PushButtonSelect_clicked();

private:
    Ui::AutoGeneratorButtonForm *ui;
};

#endif // AUTOGENERATORBUTTONFORM_H