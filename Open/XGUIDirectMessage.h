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

#if	!defined(XGUIDirectMessage_h)
#define	XGUIDirectMessage_h

#include <QIODevice>
#include "XTypeDef.h"
#include "NList.h"
#include "XErrorCode.h"
#include "XUndo.h"
#include "XServiceForLayers.h"

class	LayersBase;
class	ParamGlobal;
class	ParamComm;
class	GUICmdPacketBase;
class	IntegrationCmdPacketBase;

class	GUIDirectMessage
{
protected:
	int32	IDForUndo;
public:
	explicit	GUIDirectMessage(int32 idForUndo):IDForUndo(idForUndo){}
	explicit	GUIDirectMessage(LayersBase *base);
	explicit	GUIDirectMessage(GUICmdPacketBase *base);

	virtual ~GUIDirectMessage(void){}

	int32	GetIDForUndo(void)		{	return IDForUndo;	}
	void	SetIDForUndo(int32 d)	{	IDForUndo=d;		}

	virtual	bool	Save(QIODevice *f){	return true;	}
	virtual	bool	Load(QIODevice *f){	return true;	}
};

#endif