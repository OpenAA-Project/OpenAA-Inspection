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

#include "RWDev3DMouse.h"
#include "RWDev3DMouseForm.h"

RWDev3DMouse::RWDev3DMouse(LayersBase *base ,const QString &Parameter ,QWidget *parent)
	:RWDeviceBaseClass(base,parent)
{
	Form=nullptr;
}
RWDev3DMouse::~RWDev3DMouse(void)
{
	if(Form!=NULL){
		Form->deleteLater();
		Form=NULL;
	}
}

void	RWDev3DMouse::Prepare(void)
{
}

void	RWDev3DMouse::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	RWDev3DMouse::LoopOnIdle(void)
{
}

bool	RWDev3DMouse::Save(QIODevice *f)
{
	return true;
}
bool	RWDev3DMouse::Load(QIODevice *f)
{
	return true;
}

bool	RWDev3DMouse::ShowSettingDialog(QWidget *parent)
{
	if(Form==NULL){
		Form=new RWDev3DMouseForm(this);
	}
	Form->show();
	return true;
}