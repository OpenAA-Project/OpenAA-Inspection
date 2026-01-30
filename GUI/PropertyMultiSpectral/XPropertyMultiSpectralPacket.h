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

#pragma once

#include "XGUIPacketForDLL.h"
#include "XMultiSpectral.h"

class	CmdMultiSpectralDrawAttr: public GUIDirectMessage
{
public:
	CmdMultiSpectralDrawAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdMultiSpectralDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdMultiSpectralDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;

	GUICmdMultiSpectralDrawEnd(LayersBase *base) :GUIDirectMessage(base) {}
	GUICmdMultiSpectralDrawEnd(GUICmdPacketBase *gbase) :GUIDirectMessage(gbase) {}
};

class GUICmdSendAddMultiSpectralUsageAreaItem : public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;
	int			LibID;

	GUICmdSendAddMultiSpectralUsageAreaItem(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName);
};