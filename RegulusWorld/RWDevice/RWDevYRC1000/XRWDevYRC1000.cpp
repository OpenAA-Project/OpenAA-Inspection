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

#include "RWDevYRC1000.h"
#include "SettingDialog.h"

RWDevYRC1000::RWDevYRC1000(LayersBase *base ,const QString &Parameter ,QWidget *parent)
	:RWDeviceBaseClass(base,parent)
{
}
RWDevYRC1000::~RWDevYRC1000(void)
{
}

void	RWDevYRC1000::Prepare(void)
{
}

void	RWDevYRC1000::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	RWDevYRC1000::LoopOnIdle(void)
{
}

bool	RWDevYRC1000::Save(QIODevice *f)
{
	return true;
}
bool	RWDevYRC1000::Load(QIODevice *f)
{
	return true;
}

bool	RWDevYRC1000::ShowSettingDialog(QWidget *parent)
{
	SettingDialog	D(GetLayersBase(),this);
	D.exec();
	return true;
}