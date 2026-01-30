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

#ifndef SETTHRESHOLDLEVELFORM_H
#define SETTHRESHOLDLEVELFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SetThresholdLevelForm;
}

class SetThresholdLevelForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
    IntList ThresholdLevelIDs;
    bool    ReflectDirectly;
    int     CurrentThresholdLevelID;
public:
    explicit SetThresholdLevelForm(LayersBase *base ,bool ReflectDirectly=true,QWidget *parent = 0);
    ~SetThresholdLevelForm();
    
    void    SetCurrentThresholdLevelID(int32 ThresholdLevelID);
    int     GetCurrentThresholdLevelID(void);
signals:
	void	SignalReqChangeLevelParent();
    void    SignalChangeThresholdLevelID(int ThresholdLevelID);

private slots:
    void on_horizontalSlider_valueChanged(int value);
	void	SlotChangeThresholdLevel(int OldLevel ,int NewLevel);

    void on_pushButtonParent_clicked();

private:
    Ui::SetThresholdLevelForm *ui;

    virtual	void showEvent(QShowEvent *event)       override;
	virtual	void resizeEvent(QResizeEvent *event)	override;
    void    ShowCurrentThresholdInfo(void);
};

#endif // SETTHRESHOLDLEVELFORM_H