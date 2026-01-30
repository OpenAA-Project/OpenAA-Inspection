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

#include "XGUIPacketForDLL.h"
#include "XReplaceImage.h"
#include "XIntClass.h"
#include "XReplaceImage.h"

class	LayersBase;

class	CmdReplaceImageDrawAttr: public GUIDirectMessage
{
public:
	bool	ShowIsoMask;

	CmdReplaceImageDrawAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImageDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReplaceImageDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;

	GUICmdReplaceImageDrawEnd(LayersBase *base) :GUIDirectMessage(base) {}
	GUICmdReplaceImageDrawEnd(GUICmdPacketBase *gbase) :GUIDirectMessage(gbase) {}
};

class	GUICmdReplaceImageAddMaskArea : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	GUICmdReplaceImageAddMaskArea(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageAckMaskArea : public GUICmdPacketBase
{
public:
	QColor	AverageColor;

	GUICmdReplaceImageAckMaskArea(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdReplaceImageAddMaskImage : public GUICmdPacketBase
{
public:
	QImage	Image;

	GUICmdReplaceImageAddMaskImage(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageCalcMask: public GUICmdPacketBase
{
public:
	GUICmdReplaceImageCalcMask(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageMouseLDown : public GUICmdPacketBase
{
public:
	int	X,Y;

	GUICmdReplaceImageMouseLDown(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReplaceImageSetCompositeColor : public GUICmdPacketBase
{
public:
	QColor	Color;

	GUICmdReplaceImageSetCompositeColor(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageSetCompositeImage : public GUICmdPacketBase
{
public:
	QImage	Image;

	GUICmdReplaceImageSetCompositeImage(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageSetCompositePage : public GUICmdPacketBase
{
public:
	int	CompPage;

	GUICmdReplaceImageSetCompositePage(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageReqDraw : public GUICmdPacketBase
{
public:
	struct DataDrawInfo
	{
		int	movx;
		int	movy;
		double	ZoomRate;
		int		CanvasWidth;
		int		CanvasHeight;
		bool	ShowIsoMask;
	}Data;

	GUICmdReplaceImageReqDraw(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageAckDraw : public GUICmdPacketBase
{
public:
	QImage	Image;

	GUICmdReplaceImageAckDraw(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};


class	GUICmdReplaceImageProcessMode : public GUICmdPacketBase
{
public:
	ReplaceImageThreshold::OperateComposite	CompMode;
	bool	CompositeInside;

	GUICmdReplaceImageProcessMode(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageMaskMode : public GUICmdPacketBase
{
public:
	ReplaceImageThreshold::OperateIsolation	OpeMode;

	GUICmdReplaceImageMaskMode(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReplaceImageMakeAreaMask : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	GUICmdReplaceImageMakeAreaMask(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};