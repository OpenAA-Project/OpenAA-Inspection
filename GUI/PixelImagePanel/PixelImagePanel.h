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


#ifndef PIXELIMAGEPANEL_H
#define PIXELIMAGEPANEL_H

#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"


enum	PanelMode
{
	_MasterImage	=1
	,_TargetImage	=2
	,_DarkImage		=3
	,LightImage		=4
};

class	PixelInspectionImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	PixelInspectionImagePanel(LayersBase *Base ,QWidget *parent);
	~PixelInspectionImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	MouseMoveEvent(int globalX ,int globalY)	override;
	virtual void	StartPage	(void)	override;

private slots:

};

//=========================================================
class	GUICmdReqBmpPix : public GUICmdReqBmp
{
	PanelMode	PanelModeData;
public:
	int32	ShowFixedPhase;

	GUICmdReqBmpPix(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,DisplayImage::DisplayType dtype ,int globalPage=-1);
	GUICmdReqBmpPix(LayersBase *Base,QString className ,const QString &emitterRoot ,const QString &emitterName,DisplayImage::DisplayType dtype ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendBmpPix : public GUICmdSendBmp
{
public:
	GUICmdSendBmpPix(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);
	GUICmdSendBmpPix(LayersBase *Base,QString className ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	void	MakeImage(PanelMode	PanelModeData
					 ,DisplayImage::DisplayType dtype 
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int Dx1,int Dy1 ,int Dx2,int Dy2
					 ,int MovX,int MovY, double ZoomRate
					 ,int localPage
					 ,LayersBase &LocalLBase
					 ,int MasterNo
					 ,IntList &LayerList
					 ,bool RedCircleMode
					 ,int32 ShowFixedPhase);
};

class	GUICmdReqPixelInspectionBmp : public GUICmdPacketBase
{
public:
	struct	GUIReqBmpStruct
	{
		DisplayImage::DisplayType	DType;
		int32	Gx1;
		int32	Gy1;
		int32	Gx2;
		int32	Gy2;
		int32	Dx1;
		int32	Dy1;
		int32	Dx2;
		int32	Dy2;
		double	ZoomRate;
		int32	MovX;
		int32	MovY;
		int32	GlobalPage;
		int32	CurrentGlobalX;
		int32	CurrentGlobalY;
	}Data;
	IntList	LayerList;

	GUICmdReqPixelInspectionBmp(QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendPixelInspectionBmp : public GUICmdPacketBase
{
public:
	QImage		*IData;

	GUICmdSendPixelInspectionBmp(const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendPixelInspectionBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

	void	MakeImage(DisplayImage::DisplayType dtype
					 ,IntList &LayerList
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int Dx1,int Dy1 ,int Dx2,int Dy2
					 ,int MovX,int MovY, double ZoomRate
					 ,int localPage
					 ,LayersBase &LocalLBase);
};

//=========================================================

#endif // PIXELIMAGEPANEL_H