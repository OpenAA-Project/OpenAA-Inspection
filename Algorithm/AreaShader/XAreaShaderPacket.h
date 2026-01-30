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



#ifndef XAREAFILTERPACKET_H
#define XAREAFILTERPACKET_H

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"

class	AreaShaderLibrary;
class	AreaFilterItem;
class	GUICmdSendAddManualAreaShader : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	IntList		LayerList;
	int		CellSize;
	double	AdoptRate;	//�̗p��
	bool	Fixed;
	double	Average;
	double	Sigma;		//�W���΍�

	GUICmdSendAddManualAreaShader(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdCreateAreaShaderPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;
	int								LocalPage;
	IntList							LayerList;

	CmdCreateAreaShaderPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateAreaShaderPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestAreaShaderPacket : public GUIDirectMessage
{
public:
	IntList					LayerList;
	//AreaShaderLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;

	CmdPickupTestAreaShaderPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestAreaShaderPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestAreaShaderPacket : public GUIDirectMessage
{
public:
	CmdClearTestAreaShaderPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestAreaShaderPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif