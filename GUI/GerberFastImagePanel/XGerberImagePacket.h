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


#ifndef XGERBERIMAGEPACKET_H
#define XGERBERIMAGEPACKET_H

#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XYCross.h"
#include "XGerberFast.h"
#include "XServiceForLayers.h"
#include "mtFrameDataType.h"

class	GUICmdGerberDrawMode : public GUICmdPacketBase
{
public:
	bool	MoveMode;
	bool	RotateMode;
	bool	SlopeXMode;
	bool	SlopeYMode;
	bool	ExtendMode;
	bool	AlignmentMode;
	bool	AutoMatchingMode;
	DisplayImage::__DrawingShapeMode	Mode;
	int		LastPosX,LastPosY;
	int		MoveStartPosX,MoveStartPosY;
	int		RotateCenterXOnData	,RotateCenterYOnData;
	int		RotateFirstX		,RotateFirstY;
	double	RotateAngle;
	int		ExtendCenterXOnData	,ExtendCenterYOnData;
	int		ExtendFirstX		,ExtendFirstY;
	int		SlopeXCenterXOnData	,SlopeXCenterYOnData;
	int		SlopeXFirstX		,SlopeXFirstY;
	double	SlopeXAngle;
	int		SlopeYCenterXOnData	,SlopeYCenterYOnData;
	int		SlopeYFirstX		,SlopeYFirstY;
	double	SlopeYAngle;
	DoublePoint	ImagePoint[MaxGerberPointNumb];
	DoublePoint	CadPoint[MaxGerberPointNumb];

	DoublePoint	AMImagePoint[100];
	DoublePoint	AMCadPoint[100];

	GUICmdGerberDrawMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMsgGerberSelectAll: public GUICmdPacketBase
{
public:
	GUICmdMsgGerberSelectAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f)	{	return true;	}
	bool	Load(QIODevice *f)	{	return true;	}

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


class	GUICmdGerberDraw: public GUICmdPacketBase
{
public:
	BoolList	ButtonsToShowLayer;
	BoolList	ButtonsToOperateLayer;

	int		GlobalX;
	int		GlobalY;

	GUICmdGerberDraw(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMsgGerberExtendWithCenter : public GUICmdPacketBase
{
public:
	double	RateX,RateY;
	double	Cx,Cy;

	GUICmdMsgGerberExtendWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMsgGerberRotateWithCenter : public GUICmdPacketBase
{
public:
	double	Radian;
	double	Cx,Cy;

	GUICmdMsgGerberRotateWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMsgGerberSlopeXWithCenter : public GUICmdPacketBase
{
public:
	double	Radian;
	double	Cx,Cy;

	GUICmdMsgGerberSlopeXWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMsgGerberSlopeYWithCenter : public GUICmdPacketBase
{
public:
	double	Radian;
	double	Cx,Cy;

	GUICmdMsgGerberSlopeYWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


class	GUICmdMsgGerberPaste : public GUICmdPacketBase
{
public:
	int index;	//���� PasteGerberForm�ł�currentRow();
	int	x,y;

	GUICmdMsgGerberPaste(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdGerberDrawWithPoints: public GUICmdPacketBase
{
public:
	DotListContainer	Dots;

	GUICmdGerberDrawWithPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSelectItemsGerberFast: public GUICmdPacketBase
{
public:
	FlexArea	Area;
	bool		MultiSelect;
	BoolList	ButtonsToOperateLayer;

	GUICmdSelectItemsGerberFast(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif