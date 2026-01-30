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

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XRasterInspection.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XReferencePDF.h"
#include <QColor>

class	RasterInspectionImagePanel;
class	CmdRasterInspectionDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	RasterInspectionImagePanel	*ImagePanelPoint;

	CmdRasterInspectionDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterInspectionDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterInspectionDrawAttr: public GUIDirectMessage
{
public:
	bool	ModeShowPDF;
	bool	ModeShowItemImage;

	CmdRasterInspectionDrawAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterInspectionDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	GUICmdSendAddManualRasterInspection : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int			LibID;

	GUICmdSendAddManualRasterInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedRasterInspection : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	IntList		LayerList;

	GUICmdSendModifySelectedRasterInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqReferencePDFData : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	GUICmdReqReferencePDFData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckReferencePDFData : public GUICmdPacketBase
{
public:
	ReferencePDF	Data;

	GUICmdAckReferencePDFData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};


class	GUICmdSendReferencePDFData : public GUICmdPacketBase
{
public:
	ReferencePDF	Data;

	GUICmdSendReferencePDFData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdGenerateRasterInspection : public GUICmdPacketBase
{
public:
	IntList			LibList;

	GUICmdGenerateRasterInspection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqRasterInspectionInfoList : public GUICmdPacketBase
{
public:
	GUICmdReqRasterInspectionInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendRasterInspectionInfoList : public GUICmdPacketBase
{
public:
	ListPhasePageLayerLibIDPack	ItemIDList;

	GUICmdSendRasterInspectionInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};