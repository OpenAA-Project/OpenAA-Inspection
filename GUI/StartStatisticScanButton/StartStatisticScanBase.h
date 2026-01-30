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


#ifndef STARTSTATISTICSCANBASE_H
#define STARTSTATISTICSCANBASE_H

#include "XGUIFormBase.h"
#include <QToolButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"

class StartStatisticScanBase : public ServiceForLayers
{
	bool	Started;
public:
public:
	StartStatisticScanBase(LayersBase *Base);

	void	SlotToggledInside(bool checked);

protected:
	virtual	void OnIdleFunc(void);
	virtual	void OnIdleEnd(void){}
	virtual	void OnToggled(void){}

};
//==============================================================
class	GUICmdStartStatisticScan : public GUICmdPacketBase
{
public:
	int32		Layer;

	GUICmdStartStatisticScan(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdStartStatisticScan(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplyStatisticScan : public GUICmdPacketBase
{
public:

	GUICmdReplyStatisticScan(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdReplyStatisticScan(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif
