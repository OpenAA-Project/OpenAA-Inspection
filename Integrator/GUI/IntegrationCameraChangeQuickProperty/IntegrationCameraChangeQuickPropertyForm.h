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

#ifndef INTEGRATIONCAMERACHANGEQUICKPROPERTYFORM_H
#define INTEGRATIONCAMERACHANGEQUICKPROPERTYFORM_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
//#include "mtPushButtonColored.h"
#include "XCameraCommon.h"

namespace Ui {
class IntegrationCameraChangeQuickPropertyForm;
}

class IntegrationCameraChangeQuickPropertyForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT
    
    CameraQuickProperty Attr;
    int                 VValue;
public:
    int		MachineCode;
    QString CameraQuickPropertyStr;

    explicit IntegrationCameraChangeQuickPropertyForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationCameraChangeQuickPropertyForm();
     virtual	void	ReadyParam(void)	override;

private slots:
    void on_toolButtonDown_clicked();
    void on_toolButtonUp_clicked();

private:
    Ui::IntegrationCameraChangeQuickPropertyForm *ui;
};
//===========================================================================

class	IntegrationCmdCameraChangeQuickProperty: public IntegrationCmdPacketBase
{
public:
    CameraQuickProperty Attr;
    int                 VValue;

	IntegrationCmdCameraChangeQuickProperty(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // INTEGRATIONCAMERACHANGEQUICKPROPERTYFORM_H