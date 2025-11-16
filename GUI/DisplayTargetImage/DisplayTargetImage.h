/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayTargetImage\DisplayTargetImage.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef DISPLAYTARGETIMAGE_H
#define DISPLAYTARGETIMAGE_H

#include "displaytargetimage_global.h"
#include "XDisplayImage.h"
#include "XStatistic.h"
#include "NListComp.h"
#include "XDataAlgorithm.h"
#include "XDataAlgorithmList.h"

class	GUICmdSendTargetItemsBmp;
class	GUICmdReqTargetItemsBmp;

class	DisplayTargetImage : public DisplayImage
{
	Q_OBJECT

	QString	emitterRoot;
	QString	emitterName;
	int	GlobalX1;
	int	GlobalY1;
	int	GlobalX2;
	int	GlobalY2;
	GUIFormBase	*TargetImageControlToolsProp;

	int							ItemsBmpCounts;
	GUICmdSendTargetItemsBmp	**ItemsBmpReceiver;
	GUICmdReqTargetItemsBmp		**ItemsBmpRequester;
	StackForAverage				TimeStocker;
	mtImageToolButtonWithBalloon	*MultiItemSelectionBtn;
	mtFrameDraw::DrawingMode		MultiItemShapeMode;
public:
	int							Mergin;
	bool						ZoomForEveryInspection;
	bool						ShiftLeftClicked;
	bool						ShiftRightClicked;
	bool						tModeShowOnlyTopTurn;
	bool						MultiItemSelection;

	DisplayTargetImage(LayersBase *Base ,QWidget *parent);
	~DisplayTargetImage(void);

	virtual void	Prepare(void) override;
	virtual void	ReadyParam(void) override;
	virtual	void	GetActiveLayerList(IntList &LayerList)		const	override;
	virtual	void	DrawAfterImage(QPainter &pnt ,QImage &PntImage)		override;
			void	DrawAfterImageOnePage(QPainter &pnt ,QImage &PntImage);
	virtual	void	BuildForShow(void)						override;
	virtual	void	ShowInPlayer(int64 shownInspectionID)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
protected:
	//virtual	void	SlotMouseLDownWithShift(int globalX,int globalY);
	//virtual	void	SlotMouseRDownWithShift(int globalX,int globalY);
	virtual	void	ExecuteMouseLDownWithShift(int globalX ,int globalY)	override;
	virtual	void	ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;
	virtual	void	CanvasSlotOnPaint(QPainter &pnt)						override;
	virtual	void	SetDrawPosition(int datax1 ,int datay1 , int datax2 ,int datay2)	override;
private slots:
	void	MultiItemSelectionBtnDown();
	void	SlotItemsSelectDrawShape(QMouseEvent * event );
	void	SlotItemsSelectRectangle();
	void	SlotItemsSelectEllipseCenter();
	void	SlotItemsSelectEllipse4Points();
	void	SlotItemsSelectLongCircle();
	void	SlotItemsSelectRotatedRect();
	void	SlotItemsSelectRing();
	void	SlotItemsSelectPolygon();
	void	SlotItemsSelectFreeHand();
};

//============================================================================================
class	GUICmdReqTargetItemsBmp : public GUICmdPacketBase
{
	DisplayTargetImage	*Form;
public:
#pragma	pack(push)
#pragma	pack(1)
	struct	GUIReqBmpStruct
	{
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
		int32	MoveGlobalDx;
		int32	MoveGlobalDy;
		bool	ShowNGItemButton;
		bool	ShowAllItemsButton;
	}Data;
#pragma	pack(pop)

	IntList		LayerList;
	QString		InstName;
	AlgorithmBase	*SelectedAlgorithm;

	GUICmdReqTargetItemsBmp( LayersBase *Base ,DisplayTargetImage *Form
							,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdReqTargetItemsBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendTargetItemsBmp : public GUICmdPacketBase
{
public:
	QImage		*IData;
	QPainter	*PntFromIData;

	GUICmdSendTargetItemsBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendTargetItemsBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

	void	MakeImage(IntList &LayerList					 
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int Dx1,int Dy1 ,int Dx2,int Dy2
					 ,int MovX,int MovY, double ZoomRate
					 ,int localPage
					 ,int MoveGlobalDx ,int MoveGlobalDy
					 ,DisplayTargetImage	*A
					 ,AlgorithmBase	*L
					 ,LayersBase &LocalLBase);
	void	MakeImageAll(IntList &LayerList					 
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int Dx1,int Dy1 ,int Dx2,int Dy2
					 ,int MovX,int MovY, double ZoomRate
					 ,int localPage
					 ,int MoveGlobalDx ,int MoveGlobalDy
					 ,DisplayTargetImage	*A
					 ,AlgorithmBase	*L
					 ,LayersBase &LocalLBase);
};

class	GUICmdReqTargetNGBmp : public GUICmdPacketBase
{
	DisplayTargetImage	*Form;
public:
#pragma	pack(push)
#pragma	pack(1)
	struct	GUIReqBmpStruct
	{
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
		int32	MoveGlobalDx;
		int32	MoveGlobalDy;
		bool	ShowNGItemButton;
		bool	ShowAllItemsButton;
	}Data;
#pragma	pack(pop)
	IntList		LayerList;
	QString		InstName;
	AlgorithmBase	*SelectedAlgorithm;

	GUICmdReqTargetNGBmp( LayersBase *Base ,DisplayTargetImage *Form
							,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdReqTargetNGBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendTargetNGBmp : public GUICmdPacketBase
{
public:
	QImage		*IData;
	QPainter	*PntFromIData;

	GUICmdSendTargetNGBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendTargetNGBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

	void	MakeImage(IntList &LayerList					 
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int Dx1,int Dy1 ,int Dx2,int Dy2
					 ,int MovX,int MovY, double ZoomRate
					 ,int localPage
					 ,int MoveGlobalDx ,int MoveGlobalDy
					 ,DisplayTargetImage	*A
					 ,AlgorithmBase	*L
					 ,LayersBase &LocalLBase);
	void	MakeImageAll(IntList &LayerList					 
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int Dx1,int Dy1 ,int Dx2,int Dy2
					 ,int MovX,int MovY, double ZoomRate
					 ,int localPage
					 ,int MoveGlobalDx ,int MoveGlobalDy
					 ,DisplayTargetImage	*A
					 ,AlgorithmBase	*L
					 ,LayersBase &LocalLBase);
};


class	GUICmdReqItemsZone : public GUICmdPacketBase
{
public:

	GUICmdReqItemsZone( LayersBase *Base
							,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendItemsZone : public GUICmdPacketBase
{
public:
	int	X1,Y1,X2,Y2;

	GUICmdSendItemsZone( LayersBase *Base
							,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//================================================================

class	GUICmdReqMultiItemsByArea : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	GUICmdReqMultiItemsByArea( LayersBase *Base
							,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSendMultiItemsByArea : public GUICmdPacketBase
{
public:
	ItemsByAlgorithmContainer	Container;

	GUICmdSendMultiItemsByArea( LayersBase *Base
							,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // DISPLAYTARGETIMAGE_H
