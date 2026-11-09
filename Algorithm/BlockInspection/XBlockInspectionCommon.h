#pragma once
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

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XBlockLibrary.h"
#include "XBlockSearchWay.h"
#include "XResult.h"
#include "XLineInBlock.h"
#include "XStandardCommand.h"
#include "XGeneralFunc.h"


class	BlockInfoList : public NPList<BlockInfoList>
{
public:
	int		LibID;
	IntList	BlockCount;
	int		Page;

	BlockInfoList(void){}

	int		GetLibID(void){		return LibID;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	BlockInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(BlockCount.Save(f)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	return true;
}
inline	bool	BlockInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(BlockCount.Load(f)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	return true;
}

//===================================================================================

class	SetThresholdBlockInfo
{
public:
	int	Mergin;
	int	Shift;
	int	NGSize1;	//Broad
	int	NGSize2;	//Narrow

	int	CenterBright;
	int	AdjustL,AdjustH;
	int	BBrightL,BBrightH;
	int	NBrightL,NBrightH;

	SetThresholdBlockInfo(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	SetThresholdBlockInfo::SetThresholdBlockInfo(void)
{
	Mergin			=-1;
	Shift			=-1;
	NGSize1			=-1;
	NGSize2			=-1;

	CenterBright	=-1;
	AdjustL			=-1;
	AdjustH			=-1;
	BBrightL		=-1;
	BBrightH		=-1;
	NBrightL		=-1;
	NBrightH		=-1;
}

inline	bool	SetThresholdBlockInfo::Save(QIODevice *f)
{
	if(::Save(f,Mergin)==false)
		return false;
	if(::Save(f,Shift)==false)
		return false;
	if(::Save(f,NGSize1)==false)
		return false;
	if(::Save(f,NGSize2)==false)
		return false;
	if(::Save(f,CenterBright)==false)
		return false;
	if(::Save(f,AdjustL)==false)
		return false;
	if(::Save(f,AdjustH)==false)
		return false;
	if(::Save(f,BBrightL)==false)
		return false;
	if(::Save(f,BBrightH)==false)
		return false;
	if(::Save(f,NBrightL)==false)
		return false;
	if(::Save(f,NBrightH)==false)
		return false;
	return true;
}
inline	bool	SetThresholdBlockInfo::Load(QIODevice *f)
{
	if(::Load(f,Mergin)==false)
		return false;
	if(::Load(f,Shift)==false)
		return false;
	if(::Load(f,NGSize1)==false)
		return false;
	if(::Load(f,NGSize2)==false)
		return false;
	if(::Load(f,CenterBright)==false)
		return false;
	if(::Load(f,AdjustL)==false)
		return false;
	if(::Load(f,AdjustH)==false)
		return false;
	if(::Load(f,BBrightL)==false)
		return false;
	if(::Load(f,BBrightH)==false)
		return false;
	if(::Load(f,NBrightL)==false)
		return false;
	if(::Load(f,NBrightH)==false)
		return false;
	return true;
}

class	BlockLibraryWithThresholdList : public NPListSaveLoad<BlockLibraryWithThresholdList>
{
public:
	int		LibID;
	SetThresholdBlockInfo	ThresholdInfo;

	BlockLibraryWithThresholdList(void)	{	LibID=-1;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	BlockLibraryWithThresholdContainer : public NPListPackSaveLoad<BlockLibraryWithThresholdList>
{
public:
	virtual	BlockLibraryWithThresholdList	*Create(void)	{	return new BlockLibraryWithThresholdList();	}
};

inline	bool	BlockLibraryWithThresholdList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(ThresholdInfo.Save(f)==false)
		return false;
	return true;
}

inline	bool	BlockLibraryWithThresholdList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(ThresholdInfo.Load(f)==false)
		return false;
	return true;
}

//-----------------------------------------------------------------------------------------------
class	CmdRemoveAllOriginalBlockItems : public GUIDirectMessage
{
public:
	int		GeneratedOrigin;

	CmdRemoveAllOriginalBlockItems(LayersBase *base):GUIDirectMessage(base)			{	GeneratedOrigin=-1;	}
	CmdRemoveAllOriginalBlockItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	GeneratedOrigin=-1;	}
};

class	CmdUpdateBlockCommon : public GUIDirectMessage
{
public:
	int		LibID;
	SetThresholdBlockInfo	ThresholdInfo;

	CmdUpdateBlockCommon(LayersBase *base):GUIDirectMessage(base)		{	LibID=-1;	}
	CmdUpdateBlockCommon(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	LibID=-1;	}
};

class	CmdGenerateBlockCommon : public GUIDirectMessage
{
public:
	BlockLibraryWithThresholdContainer	Infos;

	CmdGenerateBlockCommon(LayersBase *base):GUIDirectMessage(base)		{}
	CmdGenerateBlockCommon(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	UpdateBlockLibrary: public GUIDirectMessage
{
public:
	int	LibID;
	int	SpaceToOutline;		//-1:Ineffective

	UpdateBlockLibrary(LayersBase *base):GUIDirectMessage(base)			{		}
	UpdateBlockLibrary(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{		}
};

class	ChangeBlocksThresholdCommon : public GUIDirectMessage
{
public:
	int			BlockLibID;
	QByteArray	InfosData;

	ChangeBlocksThresholdCommon(LayersBase *base):GUIDirectMessage(base)		{}
	ChangeBlocksThresholdCommon(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//===================================================================================

class	CmdBlockDrawModePacket : public GUIDirectMessage
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
		,_BeforeShrink
	}DType;
	bool	DrawDirUp;
	bool	DrawDirLeft;
	bool	DrawDirRight;
	bool	DrawDirBottom;
	bool	DrawDirSkip;
	bool	DrawOmitMatchLineArea;

	CmdBlockDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdBlockDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	BlockDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	CmdBlockDrawModePacket::DrawMode	Mode;
	CmdBlockDrawModePacket::DrawType	DType;
	bool	DrawDirUp;
	bool	DrawDirLeft;
	bool	DrawDirRight;
	bool	DrawDirBottom;
	bool	DrawDirSkip;
	bool	DrawOmitMatchLineArea;

	QColor		ColorPickup;
	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;

	BlockDrawAttr(void):ServiceForLayers(NULL){}
	BlockDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	BlockDrawAttr(LayersBase *Base
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

	BlockDrawAttr	&operator=(BlockDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	BlockDrawAttr	&BlockDrawAttr::operator=(BlockDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);
	Mode			=src.Mode;
	DrawDirUp		=src.DrawDirUp		;
	DrawDirLeft		=src.DrawDirLeft	;	
	DrawDirRight	=src.DrawDirRight	;
	DrawDirBottom	=src.DrawDirBottom	;
	DrawDirSkip		=src.DrawDirSkip	;
	ColorPickup		=src.ColorPickup;
	BlockColor0		=src.BlockColor0;
	BlockColor1		=src.BlockColor1;
	BlockColor2		=src.BlockColor2;
	BlockColor3		=src.BlockColor3;
	BlockColor4		=src.BlockColor4;
	BlockColor5		=src.BlockColor5;
	BlockColor6		=src.BlockColor6;
	BlockColor7		=src.BlockColor7;
	return *this;
}
inline	bool	BlockDrawAttr::Save(QIODevice *f)
{
	if(f->write((const char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Save(f,ColorPickup)==false)
		return false;
	if(::Save(f,DrawDirUp)==false)
		return false;
	if(::Save(f,DrawDirLeft)==false)
		return false;
	if(::Save(f,DrawDirRight)==false)
		return false;
	if(::Save(f,DrawDirBottom)==false)
		return false;
	if(::Save(f,DrawDirSkip)==false)
		return false;
	return true;
}
inline	bool	BlockDrawAttr::Load(QIODevice *f)
{
	if(f->read((char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Load(f,ColorPickup)==false)
		return false;
	if(::Load(f,DrawDirUp)==false)
		return false;
	if(::Load(f,DrawDirLeft)==false)
		return false;
	if(::Load(f,DrawDirRight)==false)
		return false;
	if(::Load(f,DrawDirBottom)==false)
		return false;
	if(::Load(f,DrawDirSkip)==false)
		return false;
	return true;
}