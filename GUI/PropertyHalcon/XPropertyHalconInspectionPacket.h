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


#if	!defined(XPROPERTYHALCONINSPECTIONPACKET_H)
#define	XPROPERTYHALCONINSPECTIONPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XHalconInspection.h"

class	GUICmdGenerateHalconInspection : public GUICmdPacketBase
{
public:
	GUICmdGenerateHalconInspection(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);
	~GUICmdGenerateHalconInspection(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdHalconInsMouseMove : public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;
};

class	CmdGetHalconInsDataFromGlobalPoint: public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;
	int	CurrentIndex;
//	HalconInsData	PData;
};

class	CmdAddItem : public GUIDirectMessage
{
public:
};

class	CmdDelItem : public GUIDirectMessage
{
public:
	int	CurrentIndex;
};

#endif