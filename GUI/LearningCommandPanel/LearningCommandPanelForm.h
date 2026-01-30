/*
 * Copyright (C) 2023
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

#ifndef LEARNINGCOMMANDPANELFORM_H
#define LEARNINGCOMMANDPANELFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include <QTcpSocket>

namespace Ui {
class LearningCommandPanelForm;
}

class LearningCommandPanelForm : public GUIFormBase
{
    Q_OBJECT

    QTcpSocket  *Sock;
public:
    QString ServerIP;
    bool    ReflectAfterMasterLoad;
    bool    ModeShowExecuteButton ;
    bool    ModeShowReflectButton ;

    explicit LearningCommandPanelForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~LearningCommandPanelForm();

    virtual void	Prepare(void) override;
    virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)  override;
private slots:
    void on_pushButtonReqExecute_clicked();
    void on_pushButtonReflectFromServer_clicked();

    void    SlotReadyReadFromServer();
private:
    Ui::LearningCommandPanelForm *ui;

    bool    ConnectToServer(void);
};

#endif // LEARNINGCOMMANDPANELFORM_H