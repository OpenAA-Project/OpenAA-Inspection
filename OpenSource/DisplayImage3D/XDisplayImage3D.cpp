#include "XDisplayImage3D.h"
#include "XGUIDLL.h"
#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "XCriticalFunc.h"
#include "XDisplayImage3DPacket.h"

DisplayImage3DAlgo::DisplayImage3DAlgo(LayersBase *Base
										,const QString &algoRoot ,const QString &algoName
										,const QString &emitterRoot ,const QString &emitterName
										,QWidget *parent)
:GUIFormBase(Base,parent) ,DisplayImageHooked(this)
{
	qRegisterMetaType<ListPageLayerIDPack *>(/**/"ListPageLayerIDPack *");

	int	LanguageCode=GetLayersBase()->GetFRegistry()->LoadRegInt(/**/"Language",0);
	//LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),LanguageCode);

	ReEntrant						=false;
	//PainterInIdle					=NULL;
	ShowFixedPhase					=-1;
	ErrorOccurs						=false;
	IconSize						=32;
	BtnW							=IconSize+8;
	BtnH							=IconSize+2;
	CountOfMaskPaint				=0;
	BmpReceiver						=NULL;
	BmpRequester					=NULL;
	AllocedBmp						=0;
	IdlePainter						=NULL;
	ScaleColor						=Qt::yellow;
	MaxZoomRate						=100;
	MinZoomRate						=0.001;

	PastedItems						=NULL;
	DrawingMode						=_Normal;
	RedCircleMode					=true;
	Connected						=false;
	Option.ZoomInButton				=true;
	Option.ZoomRectButton			=true;
	Option.ZoomWholeButton			=true;
	Option.PickColorButton			=true;
	Option.ToolManuButton			=true;
	Option.DrawColorMessage			=true;
	Option.MeasureButton			=true;
	Option.DrawCrossLineButton		=false;
	Option.UndoButton				=true;
	Option.RedoButton				=false;
	Option.ModeShowScale			=_ScalePositionNoShow;
	StrModeShowScale				=/**/"_ScalePositionNoShow";

	ViewWindowStyle.EnableMeasure	=true;
	ViewWindowStyle.EnableToolArea	=true;
	ViewWindowStyle.EnableVScroller	=true;
	ViewWindowStyle.EnableHScroller	=true;
	ViewWindowStyle.EnableZoom		=true;
	ViewWindowStyle.EnableMove		=true;

	FrameColor=Qt::red;

	MainCanvas				=NULL;
	NoneBtn					=NULL;
	ZoomInBtn				=NULL;
	ZoomRectBtn				=NULL;
	ZoomWholeBtn			=NULL;
	ToolMenuBtn				=NULL;
	MeasureBtn				=NULL;
	LabelColorMessage		=NULL;
	XPosLabel				=NULL;
	YPosLabel				=NULL;
	ZPosLabel				=NULL;
	DrawCrossLineBtn		=NULL;
	UndoBtn					=NULL;
	RedoBtn					=NULL;

	EmitterRoot	=emitterRoot;
	EmitterName	=emitterName;
	PickedColor.setRgb(0,0,0);
	IBar.setParent(this);
	IBar.move(0,0);

	resize(200,200);
	ClientTop=0;

	SetKeyGrab(true);

	ImageTunableList.append(/**/"ZoomIn");
	ImageTunableList.append(/**/"ZoomRect");
	ImageTunableList.append(/**/"ZoomWhole");
	ImageTunableList.append(/**/"PickColor");
	ImageTunableList.append(/**/"ToolMenu");
	ImageTunableList.append(/**/"Measure");
	ImageTunableList.append(/**/"DrawCrossLine");
	ImageTunableList.append(/**/"Undo");
	ImageTunableList.append(/**/"Redo");

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	GetTopParent()->installEventFilter(this);


	AlgoRoot		=algoRoot;
	AlgoName		=algoName;
	ItemNoneBtn			=NULL;
	ItemDrawBtn			=NULL;
	ItemSelectBtn		=NULL;
	ItemSelectMenuBtn	=NULL;
	ItemMoveItemBtn		=NULL;
	ItemDeleteBtn		=NULL;
	ItemLockBtn			=NULL;
	ItemGroupBtn		=NULL;
	ItemCopyBtn			=NULL;
	ItemPasteBtn		=NULL;
	ItemVisibleMenuBtn	=NULL;
	ItemRotateBtn		=NULL;
	ItemMirrorBtn		=NULL;

	ActionSelectAll	=NULL;
	ActionCopy		=NULL;
	ActionPaste		=NULL;
	ActionDelete	=NULL;

	AlgoOptions.DrawBtn			=true;
	AlgoOptions.SelectBtn		=true;
	AlgoOptions.SelectMenuBtn	=true;
	AlgoOptions.MoveItemBtn		=true;
	AlgoOptions.DeleteBtn		=true;
	AlgoOptions.LockBtn			=true;
	AlgoOptions.GroupBtn		=true;
	AlgoOptions.CopyBtn			=true;
	AlgoOptions.PasteBtn		=true;
	AlgoOptions.VisibleMenuBtn	=true;
	AlgoOptions.RotateBtn		=true;
	AlgoOptions.MirrorBtn		=true;


	WBar.setParent(this);
	WBar.move(0,0);

	ItemTunableList.append(/**/"DrawBtn");
	ItemTunableList.append(/**/"SelectBtn");
	ItemTunableList.append(/**/"SelectMenuBtn");
	ItemTunableList.append(/**/"MoveItemBtn");
	ItemTunableList.append(/**/"DeleteBtn");
	ItemTunableList.append(/**/"LockBtn");
	ItemTunableList.append(/**/"GroupBtn");
	ItemTunableList.append(/**/"CopyBtn");
	ItemTunableList.append(/**/"PasteBtn");
	ItemTunableList.append(/**/"VisibleMenuBtn");
	ItemTunableList.append(/**/"RotateBtn");
	ItemTunableList.append(/**/"MirrorBtn");

	LastDrawnTime	=::GetComputerMiliSec();
}

void	DisplayImage3DAlgo::GetZoomRate(double &ZoomRateX ,double &ZoomRateY)	const
{	
	MainCanvas->GetZoomRate(ZoomRateX,ZoomRateY);
}
bool		DisplayImage3DAlgo::GetMovxy(double &movx ,double &movy)	const
{	
	return MainCanvas->GetMovxy(movx,movy);
}
void	DisplayImage3DAlgo::AllUpImagePanel(void)
{
	if(NoneBtn!=NULL){
		NoneBtn->setChecked(true);
		NoneButtonDown();
	}
}

void	DisplayImage3DAlgo::AllUpToolButton(void)
{
	if(ItemNoneBtn!=NULL){
		ItemNoneBtn->setChecked(true);
	}
}
	
void	DisplayImage3DAlgo::SetCursor(mtFrameDraw3D::DrawingMode mode)
{
	if(MainCanvas!=NULL){
		MainCanvas->SetCursor(mode);
	}
}

void	DisplayImage3DAlgo::SetCursor(DisplayImage3DAlgo::__DrawingMode mode)
{
	if(mode==_MeasureFirst || mode==_MeasureSecond){
		setCursor(QCursor(QPixmap(/**/":/Resources/Meassure1.PNG"),0,0));
	}
}

void	DisplayImage3DAlgo::ViewRefreshInPlayer(int64 shownInspectionID)
{
	//MainCanvas->repaint (0, 0, MainCanvas->GetCanvasWidth(), MainCanvas->GetCanvasHeight() );
	if(MainCanvas!=NULL){
		MainCanvas->RepaintAll();
	}
}
void	DisplayImage3DAlgo::ViewRefreshInEdit(void)
{
	//MainCanvas->repaint (0, 0, MainCanvas->GetCanvasWidth(), MainCanvas->GetCanvasHeight() );
	if(MainCanvas!=NULL){
		MainCanvas->RepaintAll();
	}
}
void	DisplayImage3DAlgo::SetMode(mtFrameDraw3D::DrawingMode mode ,const QColor &color)
{
	MainCanvas->SetFrameColor(color);
	MainCanvas->SetMode(mode);
}

void	DisplayImage3DAlgo::BroadcastDraw(void)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;

	if(MainCanvas!=NULL){
		QRect	rect;
		double	movx ,movy;
		GetMovxy(movx ,movy);
		rect.setLeft(-movx);
		rect.setTop (-movy);

		double	ZoomRateX ,ZoomRateY;
		GetZoomRate(ZoomRateX ,ZoomRateY);
		rect.setWidth (GetCanvasWidth() /ZoomRateX);
		rect.setHeight(GetCanvasHeight()/ZoomRateY);
	}
	emit	SignalDraw(this);

	ReEntrant=false;
}

void	DisplayImage3DAlgo::AllocInnerBuff(void)
{
	if(GetPageNumb()==AllocedBmp){
		return;
	}
	if(AllocedBmp!=0){
		for(int i=0;i<AllocedBmp;i++){
			delete	BmpRequester[i];
			delete	BmpReceiver[i];
		}
		delete	[]BmpRequester;
		delete	[]BmpReceiver;
	}
	BmpReceiver=new GUICmdSendBmp3D*[GetLayersBase()->GetPageNumb()];
	BmpRequester=new GUICmdReqBmp3D*[GetLayersBase()->GetPageNumb()];
	AllocedBmp=0;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		BmpReceiver[page]=new GUICmdSendBmp3D(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]=new GUICmdReqBmp3D(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		AllocedBmp++;
	}
}

void	DisplayImage3DAlgo::ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy)	const
{
	double	movx ,movy;
	GetMovxy(movx ,movy);
	double	ZoomRateX ,ZoomRateY;
	GetZoomRate(ZoomRateX ,ZoomRateY);

	if(MainCanvas!=NULL){
		Gx=(Dx+movx)*ZoomRateX;
		Gy=(Dy+movy)*ZoomRateY;
	}
}
void	DisplayImage3DAlgo::ChangeGxy2Dxy(int Gx,int Gy ,int &Dx ,int &Dy)	const
{
	double	movx ,movy;
	GetMovxy(movx ,movy);
	double	ZoomRateX ,ZoomRateY;
	GetZoomRate(ZoomRateX ,ZoomRateY);

	if(MainCanvas!=NULL){
		Dx=Gx/ZoomRateX - movx;
		Dy=Gy/ZoomRateY - movy;
	}
}
AlgorithmBase	*DisplayImage3DAlgo::GetAlgorithmBase(void)
{
	return GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
}
