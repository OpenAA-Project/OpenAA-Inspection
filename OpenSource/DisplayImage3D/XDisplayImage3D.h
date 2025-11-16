#pragma once

#include <QSpinBox>
#include <QToolButton>
#include <QPushButton>
#include <QThread>
#include <QToolBar>
#include <QBitmap>
#include <QLineEdit>
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "mtPushButtonWithBalloon.h"
#include "mtImageToolButtonWithBalloon.h"
#include "mtImageToolButtonColored.h"
#include "mtToolButtonColored.h"
#include "mtFrameDraw3D.h"
#include "XAlgorithmLibrary.h"
#include "XDot.h"
#include "XGUIFormBase.h"
#include "XMainSchemeMemory.h"
#include "XIntClass.h"
#include "XDirectCommPacket.h"
#include "XFlexAreaImage.h"
#include "XDisplayImageHook.h"
#include "XVector.h"
#include "XGUIFormBase.h"
#include "XArrangementFromFile.h"

class	LayersBase;

const	int	DefIconSize3D=32;

class	mtImageToolButtonColored;
class	mtImageToolButtonWithBalloon;
class	mtImageButtonWithBalloon;
class	GUICmdSendBmp3D	;
class	GUICmdReqBmp3D	;
class	DisplayImage;



//---------------------------------------------------------------------

class	DisplayImage3DAlgo : public GUIFormBase,public DisplayImageHooked	//画像表示ウインドウの基本クラス
{
	Q_OBJECT

	QImage			PainterInIdle;
	bool			ReEntrant;

private:
	QStringList						ShownButtons;
	mtImageToolButtonWithBalloon	*NoneBtn;
	mtImageToolButtonWithBalloon	*ZoomInBtn;
	mtImageToolButtonWithBalloon	*ZoomRectBtn;
	mtImageToolButtonWithBalloon	*ZoomWholeBtn;
	mtImageToolButtonWithBalloon	*MeasureBtn;
	mtImageToolButtonWithBalloon	*ToolMenuBtn;
	mtImageToolButtonWithBalloon	*DrawCrossLineBtn;
	mtImageToolButtonWithBalloon	*UndoBtn;
	mtImageToolButtonWithBalloon	*RedoBtn;

protected:
	QStringList						ShownItemButtons;
	mtImageToolButtonWithBalloon	*ItemNoneBtn	;
	mtImageToolButtonWithBalloon	*ItemDrawBtn	;
	mtImageToolButtonWithBalloon	*ItemSelectBtn	;
	mtImageToolButtonWithBalloon	*ItemSelectMenuBtn;
	mtImageToolButtonWithBalloon	*ItemMoveItemBtn;
	mtImageToolButtonWithBalloon	*ItemDeleteBtn	;
	mtImageToolButtonWithBalloon	*ItemLockBtn	;
	mtImageToolButtonWithBalloon	*ItemGroupBtn	;
	mtImageToolButtonWithBalloon	*ItemCopyBtn	;
	mtImageToolButtonWithBalloon	*ItemPasteBtn	;
	mtImageToolButtonWithBalloon	*ItemVisibleMenuBtn;
	mtImageToolButtonWithBalloon	*ItemRotateBtn	;
	mtImageToolButtonWithBalloon	*ItemMirrorBtn	;
;

	QColor					PickedColor;
	QLabel					*LabelColorMessage;
	QLineEdit				*XPosLabel;
	QLineEdit				*YPosLabel;
	QLineEdit				*ZPosLabel;
	QColor					ScaleColor;

	GUICmdSendBmp3D	**BmpReceiver;
	GUICmdReqBmp3D	**BmpRequester;

	int				AllocedBmp;
	bool			Connected;
	DWORD			ClickedMilisec;
	mtFrameDraw3D::DrawingMode		CanvasDrawMode;
	QColor	FrameColor;

protected:
	int			CountOfMaskPaint;
	int			ClientTop;
	QToolBar	IBar;
	QToolBar	WBar;

protected:
	QString		EmitterRoot;
	QString		EmitterName;
	mtFrameDraw3D			*MainCanvas;

	ClipboardAlgorithm		*PastedItems;
	int32					PastedLayer;
	int32					StartGlobalX ,StartGlobalY;
	int32					StartDx		 ,StartDy	  ;
	int32					StartMovx,StartMovy;
	int32					MoveStartGlobalX ,MoveStartGlobalY;
	int32					MoveCurrentGlobalX ,MoveCurrentGlobalY;
	int32					MeasureStartGlobalX		,MeasureStartGlobalY;
	int32					MeasureCurrentGlobalX	,MeasureCurrentGlobalY;
	QString					SavedFileName;
	int32					IconSize;
	int32					BtnW;
	int32					BtnH;
	bool					ErrorOccurs;

	//QList<QImage>			TestImage;
public:

	enum	__ScalePosition{
		 _ScalePositionNoShow		=0
		,_ScalePositionLeftTop		=1
		,_ScalePositionRightTop		=2
		,_ScalePositionLeftBottom	=3
		,_ScalePositionRightBottom	=4
		};
	enum	__DrawingMode{
		_Normal					=0
		,_PasteMovePreStart		=1
		,_PasteMove				=2
		,_PasteFixed			=3
		,_PasteCreateShapeStart	=4
		,_PasteCreateShape		=5
		,_ItemMoveWait			=6
		,_ItemMove				=7
		,_RotateMoveWait		=8
		,_RotateMoveAngleStart	=9
		,_RotateMoveAngling		=10
		,_DraggingScroll		=14
		,_MeasureFirst			=15
		,_MeasureSecond			=16
		,_MeasureDone			=17
		,_SlopeXMoveWait		=37
		,_SlopeXMoveAngleStart	=38
		,_SlopeXMoveAngling		=39
		,_SlopeYMoveWait		=40
		,_SlopeYMoveAngleStart	=41
		,_SlopeYMoveAngling		=42
		,_Other					=100
	}DrawingMode,SavedDrawingMode;

	struct	_Option{
		bool	ZoomInButton;
		bool	ZoomRectButton;
		bool	ZoomWholeButton;
		bool	PickColorButton;
		bool	ToolManuButton;
		bool	DrawColorMessage;
		bool	MeasureButton;
		bool	DrawCrossLineButton;
		bool	UndoButton;
		bool	RedoButton;
		__ScalePosition	ModeShowScale;
	}Option;

	QString		StrModeShowScale;
	QStringList	ImageTunableList;

	struct	_IconImages{
		QImage	NoneIcon;
		QImage	ZoomInIcon;
		QImage	ZoomRectIcon;
		QImage	ZoomWholeIcon;
		QImage	PickColorIcon;
		QImage	ToolManuIcon;
		QImage	DrawColorMessageIcon;
		QImage	MeasureIcon;
		QImage	DrawCrossLineIcon;
		QImage	UndoIcon;
		QImage	RedoIcon;
	}IconImages;

	struct	_ViewWindowStyle
	{
		bool	EnableMeasure;
		bool	EnableToolArea;
		bool	EnableVScroller;
		bool	EnableHScroller;
		bool	EnableZoom;
		bool	EnableMove;
	}ViewWindowStyle;

	QString	ImageControlToolsName;

	//Canvas3D	LastCanvasState;
	//Canvas3D	CurrentCanvasState;
	bool		RedCircleMode;

	IntList		LayerList;

	QImage						ClippedImage;
	int32						ShowFixedPhase;	//-1: Any phase (current phase)
	QPainter		*IdlePainter;

	QAction	*ActionSelectAll;
	QAction	*ActionCopy	;
	QAction	*ActionPaste;
	QAction	*ActionDelete;
	DWORD					LastDrawnTime;

	double	MaxZoomRate;
	double	MinZoomRate;

public:
	enum	ButtonPushedButton
	{
		Mode_None
		,Mode_DrawBtn		
		,Mode_MoveItemBtn	
		,Mode_RegistAreaBtn
		,Mode_SeparateItemBtn
	};

protected:
	QString AlgoRoot;
	QString AlgoName;
public:
	struct	_AlgoOptions{
		bool	DrawBtn				;
		bool	SelectBtn			;
		bool	SelectMenuBtn		;
		bool	MoveItemBtn			;
		bool	DeleteBtn			;
		bool	LockBtn				;
		bool	GroupBtn			;
		bool	CopyBtn				;
		bool	PasteBtn			;
		bool	VisibleMenuBtn		;
		bool	RotateBtn			;
		bool	MirrorBtn			;
	}AlgoOptions;
	QStringList	ItemTunableList;

	struct	_IconItemImages{
		QImage	NoneItemIcon;
		QImage	DrawItemIcon		;
		QImage	SelectItemIcon		;
		QImage	SelectMenuItemIcon	;
		QImage	MoveItemIcon		;
		QImage	DeleteItemIcon		;
		QImage	LockItemIcon		;
		QImage	GroupItemIcon		;
		QImage	CopyItemIcon		;
		QImage	PasteItemIcon		;
		QImage	VisibleMenuItemIcon	;
		QImage	RotateItemIcon		;
		QImage	MirrorItemIcon		;
	}IconItemImages;


	DisplayImage3DAlgo(LayersBase *Base
						,const QString &AlgoRoot ,const QString &AlgoName
						,const QString &emitterRoot ,const QString &emitterName
						,QWidget *parent);
	virtual	~DisplayImage3DAlgo(void);

	virtual void	Prepare(void)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void){	return new AlgorithmDrawAttr();	}

	virtual	void	AllUpImagePanel(void);
	virtual	void	AllUpToolButton(void);
	virtual	void	SetDrawingMode(__DrawingMode mode)	{	DrawingMode=mode;	}
	virtual	void	SetMode(mtFrameDraw3D::DrawingMode mode ,const QColor &color);
	virtual void	SetAlterSomething(void){}
	virtual	void	AddMenuToolMenuBtn(QMenu &menu)	{}

	mtFrameDraw3D	*GetCanvas(void)	const	{	return MainCanvas;						}
	void	GetZoomRate(double &ZoomRateX ,double &ZoomRateY)	const;
	bool	GetMovxy(double &movx ,double &movy)				const;
	int		GetCanvasWidth(void)		const	{	return(MainCanvas->GetCanvasWidth());	}
	int		GetCanvasHeight(void)		const	{	return(MainCanvas->GetCanvasHeight());	}
	
	void	ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy)	const;
	void	ChangeGxy2Dxy(int Gx,int Gy ,int &Dx ,int &Dy)	const;
	//void	SetMovXY(int mx ,int my)			{	MainCanvas->SetMovXY(mx,my);			}
	//double	GetZoomRateForWhole(void)	const	{	return MainCanvas->GetZoomRateForWhole();	}	
	//double	GetZoomRateForFit(void)		const	{	return MainCanvas->GetZoomRateForFit();	}
	//void	SetZoomRate(double ZoomRate)		{	MainCanvas->SetZoomRate(ZoomRate);		}
	
	double	GetMaxZoomValue(void)		const	{	return MaxZoomRate;	}
	double	GetMinZoomValue(void)		const	{	return MinZoomRate;	}
	void	SetMaxZoomValue(double d)			{	MaxZoomRate=d;			}
	void	SetMinZoomValue(double d)			{	MinZoomRate=d;			}
	void	SetLineWidth(double width)			{	MainCanvas->SetLineWidth(width);	}
	double	GetLineWidth(void)			const	{	return MainCanvas->GetLineWidth();	}

	struct mtFrameDraw3D::_ShapeData *GetRawSDataPoint(void)	const	{	return &MainCanvas->SData;	}
	virtual	void	GetPointList(DotListContainer &Dots ,double d=2)	const;
	void    GetPoints(XYClassCluster &XYArea)	const;

	virtual	void			SetModeShowScale(__ScalePosition b);
	virtual	__ScalePosition	GetModeShowScale(void)	const	{	return Option.ModeShowScale;	}
	virtual	QColor	GetScaleColor(void)	const				{	return ScaleColor;	}
	virtual	void	SetScaleColor(const QColor &col)		{	ScaleColor=col;		}

	void	LockPaintMutex(void)	{	MainCanvas->LockPaintMutex();	}
	void	UnlockPaintMutex(void)	{	MainCanvas->UnlockPaintMutex();	}

	int		SetPropertyInDLL(struct	PropertyClass Data[] ,WORD	maxDataDim);
	void	InitialDisplayImageInDLL(GUICmdPacketBasePointerListContainer &GUICmdContainer
								   ,LayersBase *Base 
								   ,const QString &sRoot ,const QString &sName);

	virtual	bool OnIdle(void)		override;
	virtual	void	DrawAfterImage(QPainter &pnt ,QImage &PntImage){}

	virtual	void	AddMenuSelectMenuBtn(QMenu &menu)	{}
	virtual	void	AddMenuLockBtn		(QMenu &menu)	{}

protected:
	void	SetCursor(mtFrameDraw3D::DrawingMode mode);
	void	SetCursor(__DrawingMode mode);
	void	DrawInsideFunc(QPainter &pnt ,QImage &PntImage ,IntList &_LayerList);
	void	AllocInnerBuff(void);

signals:
	void	SignalButtonClicked(const QString &ButtonObjectName);
	void	SignalChangedDrawingPosition();
	void	SignalDraw(DisplayImage3DAlgo *target);
	void	SignalReleaseAllSelection();

public slots:
	void	NoneButtonDown();
	void	ZoomInButtonDown();
	void	ZoomRectButtonDown();
	void	WholeButtonDown();
	void	FitButtonDown();
	void	MeasureButtonDown(bool);
	void	ToolMenuBtnDown();
	void	SlotMouseMove(int X,int Y);

	virtual	void	CanvasSlotOnPaint(QPainter &pnt);
private:
	void	ViewRefreshInPlayer(int64 shownInspectionID);
	void	ViewRefreshInEdit(void);
	void	ResizeAction();
private slots:
	void	SlotKeyPress(int key ,int XonG, int YonG ,bool &Accept);
	void	UndoButtonDown();
	void	RedoButtonDown();

public:
	static	void    ToFlexArea( struct mtFrameDraw3D::_ShapeData &SData
                                ,FlexArea &resultarea);
	static	void    ColPointToArea(NPListPack<ShapePoint3D> &cdata
                                ,FlexArea &resultarea);
	static	VectorLineBase	*ToVectorLine( struct mtFrameDraw3D::_ShapeData &SData);
	//VectorLineBase	*GetVectorLineBase(void)	{	return ToVectorLine(*GetRawSDataPoint());	}

protected:
	void	BroadcastDraw(void);

	virtual	bool	DrawImage			(QPainter &pnt ,QImage &PntImage,IntList &LayerList);
	virtual	void	DrawMeasure			(QPainter &pnt ,QImage &PntImage);
	virtual	void	DrawScale			(QPainter &pnt);
public:
	void	DrawScale(QPainter &pnt
					,int CanvasWidth ,int CanvasHeight
					,int LMovX, int LMovY ,double LZoomRate ,double ZoomRateY);
protected:

	bool eventFilter(QObject *obj, QEvent *event)	override;
	void	resizeEvent ( QResizeEvent * event )	override;
	virtual	void moveEvent ( QMoveEvent * event )	override;
	virtual	double	GetScaleLen(double RealLen);

	AlgorithmBase	*GetAlgorithmBase(void);

public slots:
	virtual	void	DrawNoneBtnBtnDown();
	virtual	void	ItemDrawBtnDown();
	virtual	void	ItemSelectBtnDown();
	virtual	void	ItemSelectMenuBtnDown();
	virtual	void	ItemMoveItemBtnDown();
	virtual	void	ItemDeleteBtnDown();
	virtual	void	ItemLockBtnDown();
	virtual	void	ItemGroupBtnDown();
	virtual	void	ItemVisibleMenuBtnDown();
	virtual	void	ItemRotateBtnDown();
	virtual	void	ItemMirrorBtnDown();
	
	virtual	void	ItemSlotSelectAll();
	virtual	void	ItemSlotSelectLocked();
	virtual	void	ItemSlotSelectLibrary();
	virtual	void	ItemSlotSelectByPage();
	virtual	void	ItemSlotSelectByOrigin();
	virtual	void	ItemSlotSelectManualCreature();
	virtual	void	ItemSlotEditItemName();
	virtual	void	ItemSlotShrinkItem();
	virtual	void	ItemSlotSelectByItemIDName();
	virtual	void	ItemSlotChangeLibItem();

	virtual	void	SlotVisibleAll();
	virtual	void	SlotInvisibleAll();
	virtual	void	SlotInvisibleSelected();

	virtual	void	SlotLockBtnDown();
	virtual	void	SlotUnlockBtnDown();

	virtual	void	CanvasSlotDrawEnd(void);

public:
	virtual	void	ButtonExecuteDraw(void);
	virtual	void	ButtonExecuteSelectArea(void);
	virtual	void	ButtonExecuteSelectByPage(int globalPage);
	virtual	void	ButtonExecuteDeleteSelected(void);
	virtual	void	ButtonExecuteLockSelected(void);
	virtual	void	ButtonExecuteUnlockAll(void);
	virtual	void	ButtonExecuteGroupSelected(void);
	virtual	void	ButtonExecuteCopySelected(bool EnableDup);
	virtual	void	ExecuteReleaseAllSelection(void);
	virtual	void	ButtonExecutePasteInSameAlgorithm(void);
	virtual	void	ButtonExecutePasteInSameAlgorithmSamePos(void);
	virtual	void	ButtonExecutePasteInFixedPos(void);
	virtual	void	ExecuteSelectItemsByOriginType	(struct	OriginTypeSelection &SelectMode);

	virtual	void	ExecuteAfterDrawEnd(void);
	virtual	void	ButtonExecutePaste(void);


	void	PutRectangle(int x1,int y1 ,int x2,int y2);
	void	PutEndlessLine(int x ,int y ,double s);
	void	PutLine(int x1,int y1 ,int x2,int y2);
	void	PutHalfLine(int x ,int y ,double s ,double length);
	void	PutEllipse(int cx, int cy, int rx ,int ry);
	void	PutCircle(int cx, int cy, int r);
	void	PutLongCircle(int cx1, int cy1, int cx2, int cy2, int r);
	void	PutRotRectangle(int cx, int cy ,int width ,int height ,double s);
	void	PutRotEllipse(int cx, int cy, int rx ,int ry ,double s);
	void	PutArc(int cx, int cy, int rx ,int ry ,double StartS ,double EndS);
	void	PutRing(int cx, int cy, int rx1 ,int ry1 , int rx2 ,int ry2);

public:
	virtual	void	ExecuteActiveOnItemXY(int globalX ,int globalY);
	virtual	void	ExecuteActiveOnItem(int globalPage ,int layer ,int itemID);
private:

};
