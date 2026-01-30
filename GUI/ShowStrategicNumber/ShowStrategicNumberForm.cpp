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

#include "ShowStrategicNumberResource.h"

#include "ShowStrategicNumberForm.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"

ShowStrategicNumberForm::ShowStrategicNumberForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

ShowStrategicNumberForm::~ShowStrategicNumberForm()
{

}

void	ShowStrategicNumberForm::Prepare(void)
{
	connect(GetLayersBase(),SIGNAL(SignalChangeCurrentStrategicNumber())	,this,SLOT(SlotChangeCurrentStrategicNumber())		,Qt::QueuedConnection);
	connect(GetLayersBase(),SIGNAL(SignalChangeCurrentStrategicNumberSeq())	,this,SLOT(SlotChangeCurrentStrategicNumberSeq())	,Qt::QueuedConnection);
}

void	ShowStrategicNumberForm::ShowInPlayer(int64 shownInspectionID)
{
	int	n=GetLayersBase()->GetCurrentStrategicNumber();
	ui.spinBoxNumber->setValue(n);
}

void ShowStrategicNumberForm::on_spinBoxNumber_valueChanged(int)
{
	int	n=ui.spinBoxNumber->value();
	GetLayersBase()->SetCurrentStrategicNumber(n);
	
	n=GetLayersBase()->GetCurrentStrategicNumber();
	ui.spinBoxNumber->setValue(n);
}

void	ShowStrategicNumberForm::BuildForShow(void)
{
	ShowInPlayer(-1);
}

void	ShowStrategicNumberForm::SlotChangeCurrentStrategicNumber()
{
	ShowInPlayer(-1);
}
void	ShowStrategicNumberForm::SlotChangeCurrentStrategicNumberSeq()
{
	ShowInPlayer(-1);
}