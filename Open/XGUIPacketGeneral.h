/*
 * Copyright (C) 2021
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

#if	!defined(XGUIPacketGeneral_h)
#define	XGUIPacketGeneral_h

#include "XGUIPacketForDLL.h"

class	GUICmdReleaseSelectImagePanel : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;

	GUICmdReleaseSelectImagePanel(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSelectByLibs : public GUICmdPacketBase	//���C�u�����ɂ����A�C�e���I���v���R�}���h
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	SelectLibListContainer	SelectedList;

	GUICmdSelectByLibs(AlgorithmBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif