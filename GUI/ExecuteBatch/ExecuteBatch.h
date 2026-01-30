/*
 * Copyright (C) 2016
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

#ifndef EXECUTEBATCH_H
#define EXECUTEBATCH_H

#include "executebatch_global.h"
#include "XGUIPacketForDLL.h"

class	CmdLoadBatchFile : public GUIDirectMessage
{
public:
	QString	FileName;
	CmdLoadBatchFile(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadBatchFile(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReplaceCommandParam : public GUIDirectMessage
{
public:
	QString	Keyword;
	QString	ReplacedStr;

	CmdReplaceCommandParam(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceCommandParam(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExecuteBatch: public GUIDirectMessage
{
public:
	QString	FileName;
	CmdExecuteBatch(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteBatch(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCheckExecuteStatus: public GUIDirectMessage
{
public:
	bool	Executing;
	int		CurrentLine;
	bool	ExecutingWithStop;

	CmdCheckExecuteStatus(LayersBase *base):GUIDirectMessage(base){}
	CmdCheckExecuteStatus(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetArgParameter: public GUIDirectMessage
{
public:
	QString	DLLRoot;
	QString	DLLName;
	QString	CommandStr;
	QString	ArgName;
	QString	NewParam;
	int		Turn;

	CmdSetArgParameter(LayersBase *base):GUIDirectMessage(base){	Turn=-1;	}
	CmdSetArgParameter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Turn=-1;	}
};

class	CmdSetParameterInNumber: public GUIDirectMessage
{
public:
	int		ParamNumber;
	QString	NewParam;

	CmdSetParameterInNumber(LayersBase *base):GUIDirectMessage(base){}
	CmdSetParameterInNumber(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif // EXECUTEBATCH_H