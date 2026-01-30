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

#ifndef INTEGRATIONOUTPUTCONTROLBUTTONFORM_H
#define INTEGRATIONOUTPUTCONTROLBUTTONFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationPacketComm.h"
#include "..\ResultKidaOutput\ResultKidaOutput.h"

namespace Ui {
class IntegrationOutputControlButtonForm;
};


class IntegrationOutputControlButtonForm : public GUIFormBase
{
    Q_OBJECT
    
	bool	ReEntrant;
public:
	_OutputControlMode	CurrentMode;

    explicit IntegrationOutputControlButtonForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationOutputControlButtonForm();
	virtual void	ReadyParam(void)	override;
private slots:
	void	ResizeAction();

private:
    Ui::IntegrationOutputControlButtonForm *ui;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
};

class	GUICmdIntegrationSetControlOutput: public IntegrationCmdPacketBase
{
public:
	_OutputControlMode		ControlMode;

	GUICmdIntegrationSetControlOutput(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // INTEGRATIONOUTPUTCONTROLBUTTONFORM_H