/*
 * Copyright (C) 2013
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

#if	!defined(XDISPALYOLDIMAGEPANEL_H)
#define	XDISPALYOLDIMAGEPANEL_H

#include "NListComp.h"
#include "XFlexArea.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	NamingInfo : public NPListSaveLoad<NamingInfo>
{
public:
	FlexArea		NamingArea;
	//XYClassCluster	NamingOutline;
	QString			AreaName;
	int				GlobalPage;
	int				ItemID;

	NamingInfo(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	NamingInfoContainer : public NPListPackSaveLoad<NamingInfo>
{
public:
	NamingInfoContainer(void){}

	virtual	NamingInfo	*Create(void)	{	return new NamingInfo();	}
};

//============================================================================

class	GUICmdReqNamingInfo : public GUICmdPacketBase
{
public:
	int	Phase;

	GUICmdReqNamingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNamingInfo : public GUICmdPacketBase
{
public:
	NamingInfoContainer	NamingData;

	GUICmdSendNamingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};
//===========================================================================


#endif