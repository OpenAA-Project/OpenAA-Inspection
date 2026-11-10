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

#include "NList.h"
#include <QIODevice>
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ColorBlockInfoList : public NPList<ColorBlockInfoList>
{
public:
	int		LibID;
	int		ColorBlockCount;

	int		GetLibID(void){		return LibID;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	ColorBlockInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,ColorBlockCount)==false)
		return false;
	return true;
}
inline	bool	ColorBlockInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,ColorBlockCount)==false)
		return false;
	return true;
}



class	CmdColorBlockDrawModePacket : public GUIDirectMessage
{
public:
	enum	DrawMode{
		_None
		,_LibTest
		,_CreatedBlock
	}Mode;
	enum	DrawType{
		_Area
		,_Edge
		,_Inside
	}DType;

	CmdColorBlockDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdColorBlockDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ColorBlockDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	CmdColorBlockDrawModePacket::DrawMode	Mode;
	CmdColorBlockDrawModePacket::DrawType	DType;
	QColor		ColorPickup	;
	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;

	ColorBlockDrawAttr(void):ServiceForLayers(NULL){}
	ColorBlockDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	ColorBlockDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel
				, QColor pickupcol ,int ptranparentLevel
				, QColor &blockColor0
				, QColor &blockColor1
				, QColor &blockColor2
				, QColor &blockColor3
				, QColor &blockColor4
				, QColor &blockColor5
				, QColor &blockColor6
				, QColor &blockColor7);

	void	Initial(void);

	ColorBlockDrawAttr	&operator=(ColorBlockDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	ColorBlockDrawAttr	&ColorBlockDrawAttr::operator=(ColorBlockDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);
	Mode		=src.Mode;
	ColorPickup	=src.ColorPickup;
	BlockColor0	=src.BlockColor0;
	BlockColor1	=src.BlockColor1;
	BlockColor2	=src.BlockColor2;
	BlockColor3	=src.BlockColor3;
	BlockColor4	=src.BlockColor4;
	BlockColor5	=src.BlockColor5;
	BlockColor6	=src.BlockColor6;
	BlockColor7	=src.BlockColor7;
	return *this;
}
inline	bool	ColorBlockDrawAttr::Save(QIODevice *f)
{
	if(f->write((const char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Save(f,ColorPickup)==false)
		return false;
	return true;
}
inline	bool	ColorBlockDrawAttr::Load(QIODevice *f)
{
	if(f->read((char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Load(f,ColorPickup)==false)
		return false;
	return true;
}
