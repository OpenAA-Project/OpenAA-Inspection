/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\XDisplayImage.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef DISPLAYIMAGE_H
#define DISPLAYIMAGE_H


#include <QSpinBox>
#include <QToolButton>
#include <QPushButton>
#include <QThread>
#include <QToolBar>
#include <QBitmap>
#include <QLineEdit>
#include "mtGraphicUnit.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "mtPushButtonWithBalloon.h"
#include "mtToolButtonColored.h"
#include "mtFrameDraw.h"
#include "XAlgorithmLibrary.h"
#include "XDot.h"
#include "XMainSchemeMemory.h"
#include "XIntClass.h"
#include "XDirectCommPacket.h"
#include "XFlexAreaImage.h"
#include "XDisplayImageHook.h"
#include "XVector.h"
#include "XGUIFormBase.h"
#include "XArrangementFromFile.h"

class	LayersBase;
class	GUICmdSendBmp;
class	GUICmdReqBmp;
class	ExpandedPasteForm;
//class	DisplayImageCopyStructureMemoryList;
class	DisplayImageCopyStructure;
class	GUICmdSendClippedImage;
class	GUICmdReqClearTemporaryItems;
class	GUICmdReqTemporaryItems;
class	GUICmdAckTemporaryItems;
class	ExportFuncForMacro;
class	LensWindowForm;

#define	CmdDerivePosition	10
const	int	DefIconSize=32;

class	mtImageToolButtonColored;
class	mtImageToolButtonWithBalloon;
class	mtImageButtonWithBalloon;

class	SaveImageOnPointDialog;
class	SelectImageFormatForm;
class	DisplayImage;
class	ListLayerAndIDPack;


class	DisplayImage : public GUIFormBase,public DisplayImageHooked	//画像表示ウインドウの基本クラス
{
	Q_OBJECT
	friend	class SaveImageOnPointDialog;
	friend	class SelectImageFormatForm;

	QImage			PainterInIdle;
	//QPixmap			PixmapInIdle;
	bool			ReEntrant;
	QStringList		ShownButtons;
	DWORD			WorkingTime;

private:
	mtImageToolButtonWithBalloon	*NoneBtn;
	mtImageToolButtonWithBalloon	*ZoomInBtn;
	mtImageToolButtonWithBalloon	*ZoomRectBtn;
	mtImageToolButtonWithBalloon	*ZoomWholeBtn;
	mtImageToolButtonWithBalloon	*CopyRectBtn;
	mtImageToolButtonWithBalloon	*PasteBtn;
	mtImageToolButtonColored		*PickColorBtn;
	mtImageToolButtonWithBalloon	*DrawRectBtn;
	mtImageToolButtonWithBalloon	*DrawDotBtn;
	mtImageToolButtonWithBalloon	*MeasureBtn;
	mtImageToolButtonWithBalloon	*ExpandedPasteBtn;
	mtImageToolButtonWithBalloon	*ToolMenuBtn;
	mtImageToolButtonWithBalloon	*SaveImageOnRectBtn;
	mtImageToolButtonWithBalloon	*SaveImageOnPointBtn;
	mtImageToolButtonWithBalloon	*RegulateBrightnessBtn;
	mtImageToolButtonWithBalloon	*WheelBarrowBtn;
	mtImageToolButtonWithBalloon	*RegistColorLibBtn;
	mtImageToolButtonWithBalloon	*DrawCrossLineBtn;
	mtImageToolButtonWithBalloon	*LensBtn;
	mtImageToolButtonWithBalloon	*UndoBtn;
	mtImageToolButtonWithBalloon	*RedoBtn;

	QColor					PickedColor;
	QLabel					*LabelColorMessage;
	QLineEdit				*XPosLabel;
	QLineEdit				*YPosLabel;
	DWORD					LastDrawnTime;
	int32					CurrentMasterNo;
	QColor					ScaleColor;

	GUICmdSendBmp	**BmpReceiver;
	GUICmdReqBmp	**BmpRequester;
	ExpandedPasteForm	*FloatingExpandedPasteForm;
	int				AllocedBmp;
	bool			Connected;
	DWORD			ClickedMilisec;
	RGBStock		RGBStockData;
	bool			FirstDraw;
	mtFrameDraw::DrawingMode		DrawRectMode;
    int			PourPickupBrightness;
    int			PourExpandedDot;
protected:
	int			CountOfMaskPaint;
	int			ClientTop;
	QToolBar	IBar;

protected:
	QString	EmitterRoot;
	QString	EmitterName;
	mtGraphicUnit			*MainCanvas;
	int	TopOfAll;
	ClipboardAlgorithm		*PastedItems;
	int32					PastedLayer;
	int32					StartGlobalX ,StartGlobalY;
	int32					StartDx		 ,StartDy	  ;
	int32					StartMovx,StartMovy;
	int32					MoveStartGlobalX ,MoveStartGlobalY;
	int32					MoveCurrentGlobalX ,MoveCurrentGlobalY;
	mtFrameDraw::DrawingMode	ModeFromOther;
	int32					MeasureStartGlobalX		,MeasureStartGlobalY;
	int32					MeasureCurrentGlobalX	,MeasureCurrentGlobalY;
	QString					SavedFileName;
	int32					IconSize;
	int32					BtnW;
	int32					BtnH;
	QAction					*ActionScrollUp;
	QAction					*ActionScrollDown;
	bool					ErrorOccurs;
	int32					MinInterval;
	DWORD					LastTimeToDraw;
	DWORD					LastTimeToPaint;

	//QList<QImage>			TestImage;
public:
	class	ExpandedPasteOperation
	{
	public:
		double	ExpandedPasteZoomY;
		double	ExpandedPasteZoomX;
		double	ExpandedPasteRotate;
		double	ExpandedPasteMovX;
		double	ExpandedPasteMovY;
		ExpandedPasteOperation(void);
		void	Initial(void);
		ExpandedPasteOperation	&operator=(ExpandedPasteOperation &src);
	};
	class	ExpandedPasteXY
	{
	public:
		double	X,Y;
		ExpandedPasteXY(void):X(0.0),Y(0.0){}
		ExpandedPasteXY(const ExpandedPasteXY &src){
			X=src.X;
			Y=src.Y;
		}
		ExpandedPasteXY	&operator=(ExpandedPasteXY &src);
		ExpandedPasteXY	&operator=(const ExpandedPasteXY &src)
		{
			X=src.X;
			Y=src.Y;
			return *this;
		}
		void	Build(ExpandedPasteOperation &ope,double cx,double cy);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	int32					ExpandedPasteStartGlobalX	,ExpandedPasteStartGlobalY;
	int32					ExpandedPasteCurrentGlobalX	,ExpandedPasteCurrentGlobalY;
	class	ExpandedItemPos : public NPList<ExpandedItemPos>
	{
	public:
		ExpandedPasteXY	Pos[4];

		ExpandedItemPos(void){}
		ExpandedItemPos(const ExpandedItemPos &src){
			Pos[0]=src.Pos[0];
			Pos[1]=src.Pos[1];
			Pos[2]=src.Pos[2];
			Pos[3]=src.Pos[3];
		}
		ExpandedItemPos	&operator=(ExpandedItemPos &src);
		void	GetCenter(double &Cx ,double &Cy);
		double	GetWidth(void);
		double	GetHeight(void);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	class	ExpandedItemPosContainer : public NPListPack<ExpandedItemPos>
	{
	public:
		ExpandedItemPosContainer(void){}
		ExpandedItemPosContainer	&operator=(ExpandedItemPosContainer &src);
		ExpandedItemPosContainer	&operator=(const ExpandedItemPosContainer &src);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	class	ExpandedPasteData
	{
	public:
		ExpandedPasteXY		ExpandedPasteFrame[4];
		ExpandedItemPosContainer	ExpandedItems;
		ExpandedSelectedItemListContainer	SelectedItemLists;

		ExpandedPasteData(void){}
		ExpandedPasteData(const ExpandedPasteData &src){
			ExpandedPasteFrame[0]=src.ExpandedPasteFrame[0];
			ExpandedPasteFrame[1]=src.ExpandedPasteFrame[1];
			ExpandedPasteFrame[2]=src.ExpandedPasteFrame[2];
			ExpandedPasteFrame[3]=src.ExpandedPasteFrame[3];
			ExpandedItems		=src.ExpandedItems;
			SelectedItemLists	=src.SelectedItemLists;
		}
		ExpandedPasteData	&operator=(ExpandedPasteData &src);
		void	GetCenter(double &cx ,double &cy) const;
		void	Draw(DisplayImage *Parent ,QPainter &pnt ,const QColor &FrameColor 
					,double movx ,double movy ,double ZoomRate
					,int ImageWidth ,int ImageHeight);
		bool	IsEffective(void);
		void	Clear(void){	ExpandedItems.RemoveAll();	}
	};
protected:
	ExpandedPasteData		ExpandedPasteStart;
	ExpandedPasteData		ExpandedPasteEachStart;
	ExpandedPasteData		ExpandedPasteCurrent;
	ExpandedPasteOperation	ExpandedPasteOpe;
	ExpandedPasteOperation	ExpandedPasteOpeCurrent;

	NPListPack<ArrangementItem> ExpandedArrangementList;

	int32	SaveImageX,SaveImageY;
	int32	SaveImageSizeXDot;
	int32	SaveImageSizeYDot;
	int32	SaveImageXCount;
	int32	SaveImageYCount;
	QString	ImgFormat;

	class	eDummyClassForStatus : public GUIFormBase
	{
		DisplayImage	*Parent;
	public:
		eDummyClassForStatus(LayersBase *_LayersBasePoint,DisplayImage *p ,QWidget *parent=NULL);
		virtual	~eDummyClassForStatus(void);

		virtual	QString	GetDLLRoot(void)	const	override	{	return QString(/**/"DisplayImage");		}
		virtual	QString	GetDLLName(void)	const	override	{	return QString(/**/"Panel");			}
	}*DummyClassForStatus;

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
		,_ExtendMoveWait		=11
		,_ExtendMoveStart		=12
		,_ExtendMoving			=13
		,_DraggingScroll		=14
		,_MeasureFirst			=15
		,_MeasureSecond			=16
		,_MeasureDone			=17
		,_ExpandedPaste			=18
		,_ExpandedPasteMove		=19
		,_ExpandedPasteZoom01	=20
		,_ExpandedPasteZoom12	=21
		,_ExpandedPasteZoom23	=22
		,_ExpandedPasteZoom30	=23
		,_ExpandedPasteRotate0	=24
		,_ExpandedPasteRotate1	=25
		,_ExpandedPasteRotate2	=26
		,_ExpandedPasteRotate3	=27
		,_SaveImageOnPoint		=28
		,_SaveImageOnRect		=29
		,_RegulateBrightness	=30
		,_WheelBarrow			=31
		,_RegistColorLib		=32
		,_PasteForImage			=33
		,_DrawUncoveredArea		=34
		,_CutByShape			=35
		,_CutByShapePreStart	=36
		,_SlopeXMoveWait		=37
		,_SlopeXMoveAngleStart	=38
		,_SlopeXMoveAngling		=39
		,_SlopeYMoveWait		=40
		,_SlopeYMoveAngleStart	=41
		,_SlopeYMoveAngling		=42
		,_Pour					=43
		,_ReplaceColor			=44
		,_ReparateItemByShape	=45
		,_Other					=100
	}DrawingMode,SavedDrawingMode;

	struct	_Option{
		bool	ZoomInButton;
		bool	ZoomRectButton;
		bool	ZoomWholeButton;
		bool	CopyRectButton;
		bool	PasteButton;
		bool	PickColorButton;
		bool	DrawRectButton;
		bool	DrawDotButton;
		bool	ToolManuButton;
		bool	DrawColorMessage;
		bool	SaveImageOnRectButton;
		bool	SaveImageOnPointButton;
		bool	RegulateBrightnessButton;
		bool	WheelBarrowButton;
		bool	MeasureButton;
		bool	ExpandedPasteButton;
		bool	RegistColorLibButton;
		bool	DrawCrossLineButton;
		bool	UndoButton;
		bool	RedoButton;
		bool	LensButton;
		__ScalePosition	ModeShowScale;
	}Option;

	QString		StrModeShowScale;
	QStringList	ImageTunableList;

	struct	_IconImages{
		QImage	NoneIcon;
		QImage	ZoomInIcon;
		QImage	ZoomRectIcon;
		QImage	ZoomWholeIcon;
		QImage	CopyRectIcon;
		QImage	PasteIcon;
		QImage	PickColorIcon;
		QImage	DrawRectIcon;
		QImage	DrawDotIcon;
		QImage	ToolManuIcon;
		QImage	DrawColorMessageIcon;
		QImage	SaveImageOnRectIcon;
		QImage	SaveImageOnPointIcon;
		QImage	RegulateBrightnessIcon;
		QImage	WheelBarrowIcon;
		QImage	MeasureIcon;
		QImage	ExpandedPasteIcon;
		QImage	RegistColorLibIcon;
		QImage	DrawCrossLineIcon;
		QImage	UndoIcon;
		QImage	RedoIcon;
		QImage	LensIcon;
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

	QStringList	RelatedItems;
	enum	DisplayType
	{
		__NoImage		=0
		,__Master		=0x0001
		,__Master2		=0x0080
		,__Target		=0x0002
		,__BackGround	=0x0100
		,__GrayLower	=3
		,__GrayUpper	=4
		,__DelayedView	=0x0004
		,__BitBuff		=0x0008
		,__RawTarget	=0x0010
		,__CamTarget	=0x0020
		,__TargetTR		=0x0040
		,__TrialTarget	=0x0100
	}DType;
	QColor	FrameColor;
	QString	ImageControlToolsName;

	class	DrawingState
	{
	public:
		bool		Altered;
		int		Movx,Movy;
		double	ZoomRate;
		DisplayType	DType;
		IntList		LayerList;

		DrawingState(void){	Altered=false;	Movx=0;	Movy=0;	ZoomRate=1.0;	DType=__Master;	}
		DrawingState(DrawingState &src);
		DrawingState	&operator=(DrawingState &src);
		DrawingState	&operator=(const DrawingState &src);
		bool	operator==(DrawingState &src) const;
		bool	operator!=(DrawingState &src) const{	return !operator==(src);	}
	};
	DrawingState	LastState;
	DrawingState	CurrentState;
	bool			RedCircleMode;
	int32			TransparentLevelInBitBuff;
	bool			ModeShowOnlyTopTurn;
	IntList			LayerList;
	bool			ModeToMakeImageInThread;
	QPainter		*IdlePainter;
	bool			ShowNGMarkInTarget;

	NPListPack<DisplayImageCopyStructure>	ClippedImageStructure;
	int32						ClippedImageGlobalPosX	,ClippedImageGlobalPosY;
	int32						ClippedImageGlobalCx	,ClippedImageGlobalCy;
	GUICmdSendClippedImage		*CmdSendClippedImage;
	QImage						ClippedImage;
	int32						ShowFixedPhase;	//-1: Any phase (current phase)
	double						Yz;
	int32						ShowOnePage;
	bool						ModeDrawOutOfView;
	bool						RepaintContinuously;	//Show half draw to accelarate
	bool						FModeRepaintOnMouseMove;

	DisplayImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,DisplayType dtype ,QWidget *parent);
	virtual	~DisplayImage(void);

	virtual	void	InitialPrepare(void)override;
	virtual void	Prepare(void)		override;
	virtual void	AfterPrepare(void)	override;
	virtual	void	CreatedInEditMode(GUIFormBase *PutTop)	override;
	void	ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy)	const;
	void	ChangeGxy2Dxy(int Gx,int Gy ,int &Dx ,int &Dy)	const;
	void	SetMeterOffset(int OffsetX ,int OffsetY)	{	MainCanvas->SetMeterOffset(OffsetX ,OffsetY);	}
	void	GetMeterMatrix(int GlobalX ,int GlobalY ,int &MeterX ,int &MeterY)	const;

	virtual	void	SetModeByOthers(mtFrameDraw::DrawingMode mode ,const QColor &lineColor);
	QColor	GetDrawColor(void)					const	{	return MainCanvas->GetFrameColor();	}
	mtFrameDraw::DrawingMode GetDrawMode(void)	const	{	return(MainCanvas->GetCanvas()->GetMode());	}

	int32	GetTransparentLevelInBitBuff(void)	const	{	return TransparentLevelInBitBuff;	}
	void	SetTransparentLevelInBitBuff(int n)			{	TransparentLevelInBitBuff=n;		}

	void	SetCursor(mtFrameDraw::DrawingMode mode);
	void	SetCursor(__DrawingMode mode);

	void	ChangeDisplayType(DisplayImage::DisplayType dtype);
	DisplayImage::DisplayType	GetDisplayType(void)const	{	return DType;	}
	int32	GetCurrentMasterNo(void)				const	{	return CurrentMasterNo;		}
	void	SetCurrentMasterNo(int masterNo)				{	CurrentMasterNo=masterNo;	}
	virtual	void	SetDrawPosition(int datax1 ,int datay1 , int datax2 ,int datay2);
	virtual	void	SetDrawPosition(int datax1 ,int datay1);
	virtual	void	SetTopPosition(int top);
	virtual	void	SetAreaSize(void)	override;
	virtual	void	Repaint(void)		override;
	void	GetIdentity(QString &emitterRoot ,QString &emitterName)	const;
	virtual	void	SetMouseCursorPos(int XonG, int YonG);
	virtual	void	SetDrawingMode(__DrawingMode mode);
	virtual	__DrawingMode	GetImageDrawingMode(void)	const	{	return DrawingMode;	}
	bool	PastedItemsDraw(int localPage ,int dx ,int dy ,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor Col);
	QColor	GetPickedColor(void)	const	{	return PickedColor;					}
	RGBStock	&GetRGBStock(void)	const	{	return (RGBStock &)RGBStockData;	}
	virtual	GUIFormBase	*GetImageControlTools(void)	const;
	void	SetFModeRepaintOnMouseMove(bool b);

	DrawingState	GetDrawingState(void)	const;
	virtual void	SetAlterSomething(void);
	virtual bool	ShouldDrawBuild(void);
	virtual void	BuildForShow(void)							override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	virtual void	ShowInEdit(void)							override;
	virtual	void	ReleaseHook(FunctionServerClass *f)			override;
	virtual	void	StartPage(void)								override;
	virtual	void	LeavePage(void)								override;

	double	GetZoomRate(void)			const	{	return MainCanvas->GetZoomRate();		}
	mtGraphicUnit	*GetCanvas(void)	const	{	return MainCanvas;						}
	int		GetMovx(void)				const	{	return(MainCanvas->GetMovx());			}
	int		GetMovy(void)				const	{	return(MainCanvas->GetMovy());			}
	int		GetCanvasWidth(void)		const	{	return(MainCanvas->GetCanvasWidth());	}
	int		GetCanvasHeight(void)		const	{	return(MainCanvas->GetCanvasHeight());	}
	void	SetMovXY(int mx ,int my)			{	MainCanvas->SetMovXY(mx,my);			}
	double	GetZoomRateForWhole(void)	const	{	return MainCanvas->GetZoomRateForWhole();	}	
	double	GetZoomRateForFit(void)		const	{	return MainCanvas->GetZoomRateForFit();	}
	void	SetZoomRate(double ZoomRate)		{	MainCanvas->SetZoomRate(ZoomRate);		}
	double	GetMaxZoomValue(void)		const	{	return MainCanvas->GetMaxZoomRate();	}
	double	GetMinZoomValue(void)		const	{	return MainCanvas->GetMinZoomRate();	}
	void	SetMaxZoomValue(double d)			{	MainCanvas->SetMaxZoomRate(d);			}
	void	SetMinZoomValue(double d)			{	MainCanvas->SetMinZoomRate(d);			}
	void	SetLineWidth(double width)			{	MainCanvas->SetLineWidth(width);	}
	double	GetLineWidth(void)			const	{	return MainCanvas->GetLineWidth();	}

	struct mtFrameDraw::_ShapeData *GetRawSDataPoint(void)	const	{	return &MainCanvas->GetCanvas()->SData;	}
	virtual	void	GetPointList(DotListContainer &Dots ,double d=2)	const;
	void	GetDrawingArea(int &GlobalX1,int &GlobalY1,int &GlobalX2,int &GlobalY2)	const;

	virtual	void	DrawAfterImage(QPainter &pnt ,QImage &PntImage);
	virtual	void	DrawEndAfterOperation(FlexArea &area);
	virtual	void	MouseMoveEvent(int globalX ,int globalY);
	virtual	bool	ZoomRect(int globalX1, int globalY1, int globalX2, int globalY2);
	virtual	bool	ShowCenter(int globalCx, int globalCy,double ZoomRate=1.0);
	virtual	void	AllUpImagePanel(void);
	virtual	void	AllUpToolButton(void){}
	virtual	void	PushDrawItemButton(void){}
	void	SetEnableShiftImage(bool b);
	bool	GetEnableShiftImage(void)	const;

	virtual	void			SetModeShowScale(__ScalePosition b);
	virtual	__ScalePosition	GetModeShowScale(void)	const	{	return Option.ModeShowScale;	}
	virtual	QColor	GetScaleColor(void)	const				{	return ScaleColor;	}
	virtual	void	SetScaleColor(const QColor &col)		{	ScaleColor=col;		}

	int		GetButtonIndex(const QString &IconStr)	const;
	void	InsertIconButton(const QString &BeforeIcon,QWidget *b);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	void	keyPressEvent ( QKeyEvent * event )				override;
	virtual	void	ExecutePaste(int localPage ,int Dx ,int Dy,bool SamePage=false,int _PastedLayer=-1){}
	virtual	void	ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName){}
	virtual	void	ExecutePasteForImage(const QString &OriginRoot ,const QString &OriginName){}
	virtual	void	ExecutePasteCreateWithShape(int localPage ,QByteArray &Buff
												,const QString &OriginRoot ,const QString &OriginName
												,int ItemClass){}
	virtual	void	ExecuteMove(void){}

	virtual	void	ExecuteMouseLDown(int globalX ,int globalY){}
	virtual	void	ExecuteMouseRDown(int globalX ,int globalY){}
	virtual	void	ExecuteMouseLDoubleClick(int globalX ,int globalY){}
	virtual	void	ExecuteMouseRDoubleClick(int globalX ,int globalY){}
	virtual	void	ExecuteMouseLDownWithShift(int globalX ,int globalY){}
	virtual	void	ExecuteMouseRDownWithShift(int globalX ,int globalY){}

	virtual	void	GetActiveLayerList(IntList &LayerList)	const;
	virtual	void	SetActiveLayerList(IntList &LayerList);

	virtual	bool	IsMoveModeButtonDown(void)			const;
	virtual	void	MoveStart(int globalX ,int globalY);
	virtual	void	MoveStart(void);
	virtual	void	MovingNow(int globalX ,int globalY);
	virtual	void	MoveCancel(void);
	virtual	void	MoveFinish(void);

	virtual	void	RotateStart(void);								//Changing mode Only inside
	virtual	void	RotateFixedCenter(int globalX ,int globalY){}	//Nothing inside
	virtual	void	RotateStartAngle(int globalX ,int globalY){}	//Nothing inside
	virtual	void	RotateAngling(int globalX ,int globalY){}		//Nothing inside
	virtual	void	RotateCancel(void){}							//Nothing inside
	virtual	void	RotateFinish(void){}							//Nothing inside

	virtual	void	ExtendStart(void);								//Changing mode Only inside
	virtual	void	ExtendFixedCenter(int globalX ,int globalY){}	//Nothing inside
	virtual	void	ExtendingStart(int globalX ,int globalY){}		//Nothing inside
	virtual	void	ExtendingNow(int globalX ,int globalY){}		//Nothing inside
	virtual	void	ExtendCancel(void){}							//Nothing inside
	virtual	void	ExtendFinish(void){}							//Nothing inside

	void	SetExpandedPaste(int XNumb,int YNumb,int XDot,int YDot);
	virtual	void	ExpandedPasteExecute(ExpandedItemPosContainer &ExpandedItems);
	virtual	void	ExpandedPasteExecuteInSameAlgorithm(ExpandedItemPosContainer &ExpandedItems){}
	virtual	void	DrawInsideExpandedPaste( QPainter &pnt ,double movx,double movy,double ZoomRate
											,ExpandedSelectedItemListContainer &SelectedItemLists
											,ExpandedItemPosContainer &ExpandedItems
											,int ImageWidth ,int ImageHeight
											,int SourceCenterX ,int SourceCenterY){}
	/*
										    ,int SrcX ,int SrcY
											,int Dx,int Dy
											,int Page, int Layer, int ItemID
											,int ItemWidth ,int ItemHeight){}
											*/
	virtual	void	GetSelectedLists(void){}
	void	SetPastedLayer(int Layer)	{	PastedLayer=Layer;	}

	void    GetPoints(XYClassCluster &XYArea)	const;
	virtual	int		SetPropertyInDLL(struct	PropertyClass Data[] ,WORD	maxDataDim);
	static	void	InitialDisplayImageInDLL(GUICmdPacketBasePointerListContainer &GUICmdPacketContainer
											,LayersBase *Base
											,const QString &sRoot ,const QString &sName 
											,DisplayImage::DisplayType DType);
	virtual	bool	DynamicPickupColor(int globalX,int globalY ,QColor &Ret);

	virtual	bool	ExecuteClickButton(const QString &ButtonName);

	virtual	bool	SaveSetting(QIODevice *f);
	virtual	bool	LoadSetting(QIODevice *f);
	virtual	QString	GetSettingFileName(void)		const	{	return QString("ConfigImagePanel.dat");	}
	static	int32	RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer);

	virtual	bool	ExeZoomIn(int globalX,int globalY);
	virtual	bool	ExeZoomOut(int globalX,int globalY);
	virtual	bool	ExeSetZoom(int globalX,int globalY , double _ZoomRate);
	virtual	void	ExeCopyRect(FlexArea &Area);
			void	ExeCopyRect(FlexArea &Area ,int page);
	virtual	void	ExePasteImage(int dx,int dy);
			void	ExePasteImage(int page ,int dx,int dy);
	virtual	void	ExePickupColor(int globalX,int globalY);
	virtual	void	ExeDrawRect(FlexArea &Area);
			void	ExeDrawRect(FlexArea &Area ,int page);
	virtual	void	ExeMoveImage(int dx ,int dy ,bool FlagMaster,bool FlagTarget);
	virtual	void	ExeRotateImage(double Angle,bool FlagMaster,bool FlagTarget);
	virtual	void	ExeMirrorImage(bool FlagMaster,bool FlagTarget ,bool MirrorX ,bool MirrorY);
	virtual	void	ExeCopyImageInPhases(bool FlagMaster,bool FlagTarget,int SrcPhase,int DstPhase);
	virtual	void	ExeDrawDot(int globalX,int globalY);
			void	ExeDrawDot(int page ,int globalX,int globalY);
	virtual	void	ExePourImage(int globalX,int globalY);
	virtual	void	ExeReplaceColorImage(int globalX,int globalY);
	virtual	void	ExeUndo(void);
	virtual	void	ExeRedo(void);

	virtual	void	SlopeXStart(void);								//Changing mode Only inside
	virtual	void	SlopeXFixedCenter(int globalX ,int globalY){}	//Nothing inside
	virtual	void	SlopeXStartAngle(int globalX ,int globalY){}	//Nothing inside
	virtual	void	SlopeXAngling(int globalX ,int globalY){}		//Nothing inside
	virtual	void	SlopeXCancel(void){}							//Nothing inside
	virtual	void	SlopeXFinish(void){}							//Nothing inside

	virtual	void	SlopeYStart(void);								//Changing mode Only inside
	virtual	void	SlopeYFixedCenter(int globalX ,int globalY){}	//Nothing inside
	virtual	void	SlopeYStartAngle(int globalX ,int globalY){}	//Nothing inside
	virtual	void	SlopeYAngling(int globalX ,int globalY){}		//Nothing inside
	virtual	void	SlopeYCancel(void){}							//Nothing inside
	virtual	void	SlopeYFinish(void){}							//Nothing inside

	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)						override;
	virtual	void	StartMenu(QToolButton *Btn ,QMenu *menu){}

	virtual	void	AddMenuToolMenuBtn(QMenu &menu)	{}

	void	SetMaskPaint(int n)	{	CountOfMaskPaint=n;	}
	void	ExpandedPasteButtonOff(void);
	LensWindowForm	*ShowLensWindow(bool b ,const QString &WindowTitle=QString(/**/"Lens"));

	bool	SetCrossLineMode(bool b,const QColor &Col=Qt::yellow);

	void	DrawInsideFunc(QPainter &pnt ,QImage &PntImage ,IntList &_LayerList);
	void	StartDrawInBack(void);
	int32	GetShowOnePage(void)	const	{	return ShowOnePage;	}

	void	LockPaintMutex(void)	{	MainCanvas->LockPaintMutex();		}
	void	UnlockPaintMutex(void)	{	MainCanvas->UnlockPaintMutex();	}
	virtual	void	ExecuteReleaseAllSelection(void);
	virtual	bool OnIdle(void)		override;

	DWORD	GetLastDrawnTime(void)		const	{	return LastDrawnTime;	}
	DWORD	GetLastTimeToDraw(void)		const	{	return LastTimeToDraw;	}
	DWORD	GetLastTimeToPaint(void)	const	{	return LastTimeToPaint;	}

private:
	bool	OnIdleFunc(void);

public slots:
	void	NoneButtonDown();
	void	ZoomInButtonDown();
	void	ZoomRectButtonDown();
	void	CopyRectButtonDown();
	void	PasteButtonDown();
	void	PickColorButtonDown();
	void	DrawRectButtonDown();
	void	DrawDotButtonDown();
	void	WholeButtonDown();
	void	FitButtonDown();
	void	MeasureButtonDown(bool);
	void	ToolMenuBtnDown();
	void	ExpandedPasteBtnDown(bool);
	void	SlotMouseMove(int X,int Y);
public:
	void	ViewRefreshInPlayer(int64 shownInspectionID);
	void	ViewRefreshInEdit(void);
public slots:
	void	ResizeAction();
	void	SlotKeyPress(int key ,int XonG, int YonG ,bool &Accept);
	void	UndoButtonDown();
	void	RedoButtonDown();
	virtual	void	SlotCancelDraw();

	void	SlotMoveImage();
	void	SlotRotateImage();
	void	SlotMirrorImage();
	void	SlotSwapImage();
	void	SlotNegPosImage();
	void	SlotCopyImageToTarget();
	void	SlotCopyImageToMaster();
	void	SlotCopyImageToBackGround();
	void	SlotTranspositionTarget();
	void	SlotClearMasterImage();
	void	SlotClearBackGroundImage();
	void	SlotClearTargetImage();
	void	SlotCopyImageInPhases();
	void	SlotCopyTargetToMasterBuffN();
	void	SlotCopyMasterToMasterBuffN();
	void	SlotSwapMasterBuffN();
	void	SlotClearBitBuffer();
	void	SlotMirrorX();
	void	SlotMirrorY();

	void	SaveImageOnRectBtnDown(bool);
	void	SaveImageOnPointBtnDown(bool);
	void	RegulateBrightnessBtnDown(bool);
	void	WheelBarrowBtnDown(bool);
	void	RegistColorLibBtnDown(bool);
	void	DrawCrossLineBtnDown(bool);
	void	LensBtnDown(bool);

	void	SaveImageOnRectRClick(QMouseEvent * event );
	void	SaveImageOnPointRClick(QMouseEvent * event );

	void	SlotCopyRawToTarget(void);
	void	SlotSwapRawToTarget(void);
	void	XYLabelEditingFinished ();

	void	SlotDrawFromOutside(QStringList &data);
	void	SlotChangeCurrentPhase();

private slots:
	void	SlotPickColorBtn(QMouseEvent *);
	void	SlotSelectDrawShape(QMouseEvent * event );
	void	SlotSelectRectangle();
	void	SlotSelectLine();
	void	SlotSelectEllipseCenter();
	void	SlotSelectEllipse4Points();
	void	SlotSelectLongCircle();
	void	SlotSelectRotatedRect();
	void	SlotSelectRing();
	void	SlotSelectPolygon();
	void	SlotSelectFreeHand();
	void	SlotSelectPour();
	void	SlotSelectReplaceColor();

signals:
	void	SignalMeasure(double length);
	void	SignalPointColor(int meterX, int meterY ,QColor &col);
	void	SignalDrawMessage(const QStringList &title ,const QStringList &msg);
	void	SignalJustMouseLPress  (int UniversalDx,int UniversalDy);
	void	SignalJustMouseRPress  (int UniversalDx,int UniversalDy);
	void	SignalJustMouseLRelease(int UniversalDx,int UniversalDy);
	void	SignalJustMouseRRelease(int UniversalDx,int UniversalDy);
	void	SignalReleaseAllSelection();
	void	SignalDraw(DisplayImage *target);
	void	SignalChangedDrawingPosition();
	void	SignalButtonClicked(const QString &ButtonObjectName);
	void	SignalDrawEndAfterOperation(FlexArea &area);
	void	SignalDrawFunc(QPainter &pnt ,QImage &PntImage ,const IntList &_LayerList);

	void	SignalMouseLDown(int globalX,int globalY);
	void	SignalMouseRDown(int globalX,int globalY);
	void	SignalMouseLDownWithShift(int globalX,int globalY);
	void	SignalMouseRDownWithShift(int globalX,int globalY);
	void	SignalMouseLDoubleClick(int globalX,int globalY);
	void	SignalMouseRDoubleClick(int globalX,int globalY);

protected slots:
	virtual	void	CanvasSlotDrawEnd(void);
	virtual	void	CanvasSlotOnPaint(QPainter &pnt);

	virtual	void	SlotMouseLDown(int globalX,int globalY);
	virtual	void	SlotMouseRDown(int globalX,int globalY);
	virtual	void	SlotMouseLDownWithShift(int globalX,int globalY);
	virtual	void	SlotMouseRDownWithShift(int globalX,int globalY);
	virtual	void	SlotScrollDraw();
	virtual	void	SlotMouseLDoubleClick(int globalX,int globalY);
	virtual	void	SlotMouseRDoubleClick(int globalX,int globalY);
	void	SlotMouseWheel(int delta ,int globalX,int globalY);
	void	SlotExpandedPasteExecute(void);
	void	SlotExecuteOkInSameAlgorithm(void);
	void	SlotExpandedPasteCancel(void);
	void	SlotExecuteMatrix(void);
	void	SlotShiftAll(void);
	void	SlotDrawing(mtFrameDraw::DrawingMode mode,int stage);
	void	SlotFitZoom();
private slots:
	void	SlotJustMouseLPress  (int UniversalDx,int UniversalDy);
	void	SlotJustMouseRPress  (int UniversalDx,int UniversalDy);
	void	SlotJustMouseLRelease(int UniversalDx,int UniversalDy);
	void	SlotJustMouseRRelease(int UniversalDx,int UniversalDy);

	virtual	void	SlotScrollUp();
	virtual	void	SlotScrollDown();
	void	SlotDrawMessage(const QStringList &title ,const QStringList &msg);

public:
	static	void    ToFlexArea( struct mtFrameDraw::_ShapeData &SData
                                ,FlexArea &resultarea);
	static	void    ColPointToArea(NPListPack<ShapePoint> &cdata
                                ,FlexArea &resultarea);
	static	VectorLineBase	*ToVectorLine( struct mtFrameDraw::_ShapeData &SData);
	VectorLineBase	*GetVectorLineBase(void)	{	return ToVectorLine(*GetRawSDataPoint());	}
protected:
	void	BroadcastDraw(void);
	void	BroadcastShiftAll(void);

	void	DrawERotateArrow(QPainter &pnt ,bool Selected ,double globalCx,double globalCy ,double globalPx ,double globalPy);
	void	DrawEZooomArrow(QPainter &pnt ,bool Selected ,double globalX, double globalY,double sita);
	void	SetExpandedPasteFrame(int globalX ,int globalY);
	void	BuildCurrentExpandedPaste(ExpandedPasteOperation &ope);

	virtual	bool	DrawImage			(QPainter &pnt ,QImage &PntImage,IntList &LayerList);
	virtual	bool	DrawImageOnePage	(QPainter &pnt ,QImage &PntImage,IntList &LayerList);
	virtual	void	DrawMeasure			(QPainter &pnt ,QImage &PntImage);
	virtual	void	DrawExpandedPaste	(QPainter &pnt ,QImage &PntImage);
	virtual	void	DrawPaste			(QPainter &pnt ,QImage &PntImage);
	virtual	void	DrawSaveImageOnPoint(QPainter &pnt ,QImage &PntImage);
	virtual	void	DrawScale			(QPainter &pnt);
public:
	void	DrawScale(QPainter &pnt
					,int CanvasWidth ,int CanvasHeight
					,int LMovX, int LMovY ,double LZoomRate);
protected:
	virtual	void	AllocInnerBuff(void);
	void	SetModeToImagePanelTools(mtFrameDraw::DrawingMode mode ,const QColor &lineColor);
	virtual	QImage	GetSaveImage(int gx1, int gy1, int gx2 ,int gy2);
	virtual	bool	SaveImage(int gx1, int gy1, int gx2 ,int gy2 ,int xn ,int yn);
	virtual	void	ExeRegulateBrightness(FlexArea &TmpArea);
	virtual	void	ExeRegistColorLib(FlexArea &Area);
	virtual	void	ExecuteMatrix(void){}
	bool eventFilter(QObject *obj, QEvent *event)	override;
	void	resizeEvent ( QResizeEvent * event )	override;
	virtual	void moveEvent ( QMoveEvent * event )	override;
	virtual	double	GetScaleLen(double RealLen);

	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)	override;
	virtual	bool	InsertPage(int IndexPage)	override;	//Create page before Indexed page
	virtual	bool	RemovePage(int IndexPage)	override;

};

class	GUICmdSendItemsBmp;
class	GUICmdReqItemsBmp;

class	DisplayImageWithAlgorithm : public DisplayImage	//アルゴリズム（アイテム）表示のできる画像表示ウインドウ
{
	Q_OBJECT

	QStringList				ShownButtons;
protected:
	mtImageToolButtonWithBalloon	*NoneBtn	;
	mtImageToolButtonWithBalloon	*DrawBtn	;
	mtImageToolButtonWithBalloon	*SelectBtn	;
	mtImageToolButtonWithBalloon	*SelectMenuBtn;
	mtImageToolButtonWithBalloon	*CutItemBtn	;
	mtImageToolButtonWithBalloon	*MoveItemBtn;
	mtImageToolButtonWithBalloon	*DeleteBtn	;
	mtImageToolButtonWithBalloon	*LockBtn	;
	mtImageToolButtonWithBalloon	*GroupBtn	;
	mtImageToolButtonWithBalloon	*CopyBtn	;
	mtImageToolButtonWithBalloon	*PasteBtn	;
	mtImageToolButtonWithBalloon	*RegistAreaBtn;
	mtImageToolButtonWithBalloon	*VisibleMenuBtn;
	mtImageToolButtonWithBalloon	*RotateBtn	;
	mtImageToolButtonWithBalloon	*MirrorBtn	;
	mtImageToolButtonWithBalloon	*ItemMenuBtn;
	mtImageToolButtonWithBalloon	*UncoveredBtn;
	mtImageToolButtonWithBalloon	*MultiSelectBtn;
	mtImageToolButtonWithBalloon	*SeparateItemBtn	;

	QToolBar	WBar;
	int					ItemsBmpCounts;
	GUICmdSendItemsBmp	**ItemsBmpReceiver;
	GUICmdReqItemsBmp	**ItemsBmpRequester;
	GUICmdReqTemporaryItems			**CmdReqTemporaryItems;
	GUICmdAckTemporaryItems			**CmdAckTemporaryItems;

	QAction	*ActionSelectAll;
	QAction	*ActionCopy	;
	QAction	*ActionPaste;
	QAction	*ActionDelete;
	
	DirectCmdPacketBaseContainer	DirectCmdPacketContainer;
	bool	EnableOutsideItems;
public:
	enum	ButtonPushedButton
	{
		Mode_None
		,Mode_DrawBtn		
		,Mode_CutItemBtn	
		,Mode_MoveItemBtn	
		,Mode_RegistAreaBtn
		,Mode_SeparateItemBtn
	};

private:
	ButtonPushedButton	LastMode;

	struct	_EnableMultiSelection
	{
		bool	EnableMultiSelectInDraw		:1;
		bool	EnableMultiSelectInCut		:1;
		bool	EnableMultiSelectInMove		:1;
		bool	EnableMultiSelectInDelete	:1;
		bool	EnableMultiSelectInLock		:1;
		bool	EnableMultiSelectInCopy		:1;
		bool	EnableMultiSelectInRotate	:1;
		bool	EnableMultiSelectInMirror	:1;
	}EnableMultiSelection;

protected:
	QString AlgoRoot;
	QString AlgoName;
public:
	struct	_AlgoOptions{
		bool	DrawBtn				;
		bool	SelectBtn			;
		bool	SelectMenuBtn		;
		bool	CutItemBtn			;
		bool	MoveItemBtn			;
		bool	DeleteBtn			;
		bool	LockBtn				;
		bool	GroupBtn			;
		bool	CopyBtn				;
		bool	PasteBtn			;
		bool	RegistAreaBtn		;
		bool	VisibleMenuBtn		;
		bool	RotateBtn			;
		bool	MirrorBtn			;
		bool	UncoveredBtn		;
		bool	ItemMenuBtn			;
		bool	MultiSelectBtn		;
		bool	SeparateItemBtn		;
	}AlgoOptions;
	QStringList	ItemTunableList;

	struct	_IconItemImages{
		QImage	NoneItemIcon;
		QImage	DrawItemIcon		;
		QImage	SelectItemIcon		;
		QImage	SelectMenuItemIcon	;
		QImage	CutItemItemIcon		;
		QImage	MoveItemIcon		;
		QImage	DeleteItemIcon		;
		QImage	LockItemIcon		;
		QImage	GroupItemIcon		;
		QImage	CopyItemIcon		;
		QImage	PasteItemIcon		;
		QImage	RegistAreaItemIcon	;
		QImage	VisibleMenuItemIcon	;
		QImage	RotateItemIcon		;
		QImage	MirrorItemIcon		;
		QImage	UncoveredItemIcon	;
		QImage	ItemMenuIcon		;
		QImage	MultiSelectIcon		;
		QImage	SeparateItemIcon	;
	}IconItemImages;

	DisplayImageWithAlgorithm(LayersBase *Base
							,const QString &AlgoRoot ,const QString &AlgoName
							,const QString &emitterRoot ,const QString &emitterName,DisplayType dtype
							,QWidget *parent);
	virtual	~DisplayImageWithAlgorithm(void);

	void	Initial(const QString &GUIRoot,const QString &GUIName);
	virtual void	Prepare(void)			override;
	virtual	void	AllUpToolButton(void)	override;
	virtual	void	PushDrawItemButton(void)override;
	virtual	void	MouseMoveEvent(int globalX ,int globalY)	override;

	int		GetButtonIndex(const QString &IconStr)	const;
	void	InsertIconButton(const QString &BeforeIcon,QWidget *b);

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void){	return new AlgorithmDrawAttr();	}
	virtual	AlgorithmBase	*GetAlgorithmBase(void)		const;
	virtual	int				GetLibType(void)			const;
	virtual	void			GetAlgorithm(QString &_AlgoRoot,QString &_AlgoName)	const	{	_AlgoRoot=AlgoRoot;	_AlgoName=AlgoName;	}
	void	SetPasteMode(int PastedLayer ,const XDateTime &CopiedID ,DisplayImage::__DrawingMode DMode);
	void	SetPasteForImage(const QColor &Color,const XDateTime &SelectTimeIndex);
	void	ExecuteCutItemsByPasted(int dx,int dy);

	virtual	void	ExecutePaste(int localPage ,int Dx ,int Dy,bool SamePage=false,int _PastedLayer=-1)	override;
	virtual	void	ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName)				override;
	virtual	void	ExecutePasteForImage(const QString &OriginRoot ,const QString &OriginName)			override;

	virtual	void	ExecutePasteCreateWithShape(int localPage ,QByteArray &Buff 
												,const QString &OriginRoot ,const QString &OriginName
												,int ItemClass)	override;
	virtual	void	ExecuteMove(void)	override;
	virtual	void	ExecuteMove(int dx ,int dy);
	virtual	void	ExecuteRotate(int AngleDegree);
	virtual	void	ExecuteMirror(AlgorithmItemRoot::_MirrorMode MirrorMode);

	virtual	void	ExecuteMouseLDown(int globalX ,int globalY)				override;
	virtual	void	ExecuteMouseRDown(int globalX ,int globalY)				override;
	virtual	void	ExecuteMouseLDownWithShift(int globalX ,int globalY)	override;

	virtual	void	MoveFinish(void)							override;
	virtual	__DrawingMode	GetImageDrawingMode(void)	const	override;
	ButtonPushedButton		GetButtonPushedButton(void)	const;
	bool	GetEnableOutsideItems(void)					const	{	return EnableOutsideItems;	}
	virtual	void	ExecuteChangeItemName(const QString &itemname);

	virtual	void	RotateStart(void)	override;
	virtual	void	SlopeXStart(void)	override;
	virtual	void	SlopeYStart(void)	override;
	virtual	void	ExtendStart(void)	override;

	virtual	void	SetMultiSelect(bool b);
	virtual	bool	GetMultiSelect(void);
	virtual	void	ExeSelectItemsByLib(int LibID);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	static	void	InitialDisplayImageWithAlgorithmInDLL(GUICmdPacketBasePointerListContainer &GUICmdPacketContainer
														,LayersBase *Base
														,const QString &sRoot ,const QString &sName 
														,DisplayImage::DisplayType DType);
	virtual	int		SetPropertyInDLL(struct	PropertyClass Data[] ,WORD	maxDataDim)	override;

	virtual	bool	ExecuteClickButton(const QString &ButtonName)	override;
	virtual	void	SelectArea(IntList &LayerList, FlexArea &Area);
	virtual	void	ExpandedPasteExecuteInSameAlgorithm(ExpandedItemPosContainer &ExpandedItems)	override;

	virtual	void	DrawInsideExpandedPaste( QPainter &pnt ,double movx,double movy,double ZoomRate
											,ExpandedSelectedItemListContainer &SelectedItemLists
											,ExpandedItemPosContainer &ExpandedItems
											,int ImageWidth ,int ImageHeight
											,int SourceCenterX ,int SourceCenterY)	override;

	virtual	void	GetSelectedLists(void)	override;
	static	int32	RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer);

	virtual	void	ExeSelectItems(FlexArea &Area);
	virtual	void	ExeCutItems(FlexArea &Area);
	virtual	void	SeparateItems(FlexArea &Area);

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

	virtual	void	GetMenuInfo(MenuInfoContainer &Info)		override;
	virtual	void	ExecuteMenu(int ID)							override;
	virtual	void	AddMenuSelectMenuBtn(QMenu &menu)	{}
	virtual	void	AddMenuItemMenuBtn	(QMenu &menu)	{}
	virtual	void	AddMenuLockBtn		(QMenu &menu)	{}
	virtual	void	AddMenuVisibleMenuBtn(QMenu &menu)	{}

	bool			SelectOneItem(int globalX ,int globalY
								 ,ListLayerAndID &SelectedItem);

	virtual	void	SetActivateItem(int globalpage ,int layer, int itemID);
	virtual	void	ClearActivattionItems(void);
	virtual	void	MoveStart(void)						override;
	virtual	void	MoveStart(int globalX ,int globalY)	override;
	virtual	int		ReturnItemClassForShapePaste(void)	{	return 0;	}
signals:
	void	TouchItems(ListPageLayerIDPack *);
	void	SignalReleaseAllSelection();

public slots:
	virtual	void	DrawNoneBtnBtnDown();
	virtual	void	DrawBtnDown();
	virtual	void	SelectBtnDown();
	virtual	void	SelectMenuBtnDown();
	virtual	void	CutItemBtnDown();
	virtual	void	MoveItemBtnDown();
	virtual	void	DeleteBtnDown();
	virtual	void	LockBtnDown();
	virtual	void	GroupBtnDown();
	virtual	void	CopyBtnDown();
	virtual	void	PasteBtnDown();
	virtual	void	PasteBtnDownFromShortcut();
	virtual	void	RegistAreaBtnDown();
	virtual	void	VisibleMenuBtnDown();
	virtual	void	RotateBtnDown();
	virtual	void	MirrorBtnDown();
	virtual	void	UncoveredBtnDown();
	virtual	void	ItemMenuBtnDown();
	virtual	void	MultiSelectBtnDown();
	virtual	void	SeparateItemBtnDown();
	
	virtual	void	SlotSelectAll();
	virtual	void	SlotSelectLocked();
	virtual	void	SlotSelectLibrary();
	virtual	void	SlotSelectByPage();
	virtual	void	SlotSelectByOrigin();
	virtual	void	SlotSelectManualCreature();
	virtual	void	SlotEditItemName();
	virtual	void	SlotShrinkItem();
	virtual	void	SlotSelectByItemIDName();
	virtual	void	SlotChangeLibItem();
	virtual	void	SlotAlgorithmComponentWindow();
	virtual	void	SlotMakeOutlineItem();

	virtual	void	SlotVisibleAll();
	virtual	void	SlotInvisibleAll();
	virtual	void	SlotInvisibleSelected();

	virtual	void	SlotLockBtnDown();
	virtual	void	SlotUnlockBtnDown();

	virtual	void	CanvasSlotDrawEnd(void)	override;
	//virtual	void	CanvasSlotOnPaint(QPainter &pnt);

public:
	virtual	void	ButtonExecuteDraw(void);
	virtual	void	ButtonExecuteSelectArea(void);
	virtual	void	ButtonExecuteSelectByPage(int globalPage);
	virtual	void	ButtonExecuteCutItem(void);
	virtual	void	ButtonExecuteDeleteSelected(void);
	virtual	void	ButtonExecuteLockSelected(void);
	virtual	void	ButtonExecuteUnlockAll(void);
	virtual	void	ButtonExecuteGroupSelected(void);
	virtual	void	ButtonExecuteCopySelected(bool EnableDup);
	virtual	void	ExecuteReleaseAllSelection(void)	override;
	virtual	void	ButtonExecutePasteInSameAlgorithm(void);
	virtual	void	ButtonExecutePasteInSameAlgorithmSamePos(void);
	virtual	void	ButtonExecutePasteInFixedPos(void);
	virtual	void	ButtonExecuteCutByShape(void);
	virtual	void	ExecuteSelectItemsByOriginType	(struct	OriginTypeSelection &SelectMode);

	virtual	void	DrawAfterImage(QPainter &pnt ,QImage &PntImage) override;
	virtual	void	DrawItems(DisplayImage *Target,QPainter &pnt ,double ZoomRate ,int Movx ,int Movy);
	virtual	void	DrawItemsOnePage(DisplayImage *Target,QPainter &pnt ,double ZoomRate ,int Movx ,int Movy);
	virtual	void	ExecuteAfterDrawEnd(void);
	virtual	void	ButtonExecutePaste(void);

	virtual	void	AllocInnerBuffWithAlgorithm(void);

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
	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	virtual	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	virtual	bool	RemovePage(int IndexPage);

protected:
	virtual	void	ExecuteMatrix(void)	override;
};


//============================================================================================

class	DisplayImagePointer : public NPList<DisplayImagePointer>
{
	DisplayImage	*ImagePanel;
public:
	DisplayImagePointer(DisplayImage *s):ImagePanel(s){}

	DisplayImage	*GetPanel(void)	const	{	return ImagePanel;	}
};

class	DisplayImagePointerContainer : public NPListPack<DisplayImagePointer>
{
public:
	DisplayImagePointerContainer(void){}

	void	Add(DisplayImage *s)	{	AppendList(new DisplayImagePointer(s));	}
	void	Repaint(void);
};


//============================================================================================

#endif
