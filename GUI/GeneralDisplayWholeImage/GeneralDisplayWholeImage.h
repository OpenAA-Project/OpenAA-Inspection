/*
 * Copyright (C) 2024
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


#ifndef GENERALDISPLAYWHOLEIMAGE_H
#define GENERALDISPLAYWHOLEIMAGE_H

#include "generaldisplaywholeimage_global.h"
#include "mtFrameDraw.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"

class	DisplayImage;
class	GUICmdSendWholeBmp;
class	GUICmdReqWholeBmp;
class	GeneralDisplayWholeImage;

class	GeneralDisplayWholeImageDisplayImage : public DisplayImage
{
	GeneralDisplayWholeImage	*Parent;
public:
	GeneralDisplayWholeImageDisplayImage(GeneralDisplayWholeImage *parent,LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,DisplayType dtype);

	virtual	bool	HookedExecutePaintFirst		(QPainter &pnt ,QImage &PntImage);
	virtual	bool	HookedExecutePaintLast		(QPainter &pnt ,QImage &PntImage);

};

class GeneralDisplayWholeImage : public GUIFormBase ,public DisplayImageHooked
{
	Q_OBJECT
	mtFrameDraw		MainCanvas;
	QRect			RealPos;
	bool			BlinkOn;
	QTimer			TM;
	DWORD			LastPaintTime;
	int32			LastWidth,LastHeight;
	GUICmdSendWholeBmp	**BmpReceiver ;
	GUICmdReqWholeBmp	**BmpRequester;
	int				AllocatedPageNumb;
	DisplayImage	*LastFocusPanel;

	int				PhaseNumbInPixMap;
	int				PageNumbInPixMap;
	QPixmap			***MasterPixMap;
	QImage			PntImage;
	QPainter		*RPnt;
	GeneralDisplayWholeImageDisplayImage	*RelatedPanelPointer;
	QPixmap			DrawMap;
public:
	QColor		FrameColor;
	QColor		ZoneColor;
	QStringList	RelatedPanel;
	QStringList	RelatedOperations;
	bool		Mastered;
	bool		ShowNG;
	bool		BlinkNG;
	int32		ShowFixedPhase;
	bool		FollowImagePanel;
	int32		ShowOnePage;
	int32		MinUpdateSpanMilisec;

    GeneralDisplayWholeImage(LayersBase *Base ,QWidget *parent);
    ~GeneralDisplayWholeImage();

	virtual void	Prepare(void)		override;
	virtual void	ReadyParam(void)	override;
	virtual	QStringList	GetRelatedForm(void)	override	{	return RelatedPanel;	}

	void	ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy);
	void	ChangeGxy2Dxy(int Gx,int Gy ,int &Dx ,int &Dy);
	
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit	(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
	double	GetZoomRate(void);
	virtual	void	Repaint(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;

	virtual	void	SetHookInPaintFirst(FunctionServerClass *Obj	,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,QPainter &pnt ,QImage &PntImage),bool Highest)	override;
	virtual	void	SetHookInPaintLast(FunctionServerClass *Obj		,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,QPainter &pnt ,QImage &PntImage),bool Highest)	override;

private slots:
	void	SlotDrawEnd(void);
	void	SlotOnPaint(QPainter &pnt);
	void	ResizeAction();
	void	SlotTimeout();
	void	SlotDraw(DisplayImage *target);
	void	SlotChangedXY();
	void	SlotChangedPhasePageLayer();
	void	SlotMemoryChanged();
	void	SlotChangeCurrentPhase();
	void	SlotChangedMasterImage(int Phase ,int Page ,int Layer);
private:
	void			AllocatePacketMap(void);
	DisplayImage	*GetCurrentImagePanel(void);
	void			SetConnectionInMasterBuff(void);
	void			ReleaseMasterPixMap(void);
	void			AllocatePixmap(void);
};

//---------------------------------------------------------
class	GUICmdReqWholeBmp : public GUICmdPacketBase
{
public:
	double	ZoomRate;
	bool	Mastered;
	bool	ShowNG;
	int32		ShowFixedPhase;

	GUICmdReqWholeBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendWholeBmp : public GUICmdPacketBase
{
public:
	QImage		*IData;

	GUICmdSendWholeBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendWholeBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

	bool	MakeImage(bool Mastered ,double ZoomRate
					 ,int localPage
					 ,LayersBase &LocalLBase
					 ,bool ShowNG
					 ,int32	ShowFixedPhase);
};
//---------------------------------------------------------
class	CmdGetZoomRate	:public GUIDirectMessage
{
public:
	double	ZoomRate;

	CmdGetZoomRate(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdSetRealPosition	:public GUIDirectMessage
{
public:
	QRect			RealPos;

	CmdSetRealPosition(LayersBase *base):GUIDirectMessage(base){}
};

//---------------------------------------------------------

#endif // GENERALDISPLAYWHOLEIMAGE_H