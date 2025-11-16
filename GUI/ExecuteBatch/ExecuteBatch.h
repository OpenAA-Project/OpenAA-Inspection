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
