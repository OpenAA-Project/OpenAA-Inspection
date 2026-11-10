#pragma once

#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QIODevice>

class	CmdSaveMatrixCellFile	:public GUIDirectMessage
{
public:
	QIODevice	*FL;
	CmdSaveMatrixCellFile(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdLoadMatrixCellFile	:public GUIDirectMessage
{
public:
	QIODevice	*FL;
	CmdLoadMatrixCellFile(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdCreateMatrixCell	:public GUIDirectMessage
{
public:
	CmdCreateMatrixCell(LayersBase *base):GUIDirectMessage(base){}
};

