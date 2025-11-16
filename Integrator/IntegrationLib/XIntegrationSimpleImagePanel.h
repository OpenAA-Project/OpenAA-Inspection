#if	!defined(XIntegrationSimpleImagePanel_H)
#define	XIntegrationSimpleImagePanel_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDataInLayer.h"
#include "mtGraphicUnit.h"
#include "XIntegrationPacketComm.h"
#include <QToolButton>
#include <QPushButton>

class	IntegrationSimpleImagePanel;
class	IntegrationReqPanelImage;
class	IntegrationAckPanelImage;
class	IntegrationReqAlgorithmPanelImage;
class	IntegrationAckAlgorithmPanelImage;
class	SelectedItemsInfoContainer;

class	MainImagePanel : public mtGraphicUnit,public ServiceForLayers
{
	Q_OBJECT

	friend	class	IntegrationSimpleImagePanel;

	IntegrationSimpleImagePanel	*Parent;
	IntegrationReqPanelImage	**RCmdImage;
	IntegrationAckPanelImage	**ACmdImage;

protected:
	QImage	*Img;
	int		CurrentPhase;
	bool	Dirty;
	double	LastZoomRate;
	int		LastMoveX,LastMoveY;
public:
	QString	FileName;

	MainImagePanel(LayersBase *Base,IntegrationSimpleImagePanel *parent);
	virtual	~MainImagePanel(void);

	void	Prepare(void);
	void	SetDirty(bool b)	{	Dirty=b;	}
signals:
	void	SignalCanvasMouseMove (int globalX ,int globalY);
	void	SignalCanvasMouseLDown(int globalX ,int globalY);
	void	SignalCanvasMouseRDown(int globalX ,int globalY);
	void	SignalCanvasMouseLDoubleClick(int ,int);
	void	SignalCanvasMouseRDoubleClick(int ,int);

private slots:
	void	SlotOnPaint(QPainter &pnt);
	void	SlotMouseMove(int ,int);
	void	SlotMouseLDown(int ,int);
	void	SlotMouseRDown(int ,int);
	void	SlotMouseLDoubleClick(int ,int);
	void	SlotMouseRDoubleClick(int ,int);
	void	SlotMouseWheel(int delta ,int globalX,int globalY);
	void	SlotShiftAll(void);
};


class	IntegrationSimpleImagePanel : public GUIFormBase
{
	Q_OBJECT

	friend	class	MainImagePanel;

	QToolButton		ModeButton;		//Add item / Select item / Zoom 
	QPushButton		DeleteButton;
	QPushButton		DrawWhole;
	QPushButton		UndoButton;
	QPushButton		CopyButton;

	ButtonRightClickEnabler	*RModeButtonEnabler;

	MainImagePanel	MainCanvas;
protected:
	bool	UseSelectionDialog;
	int64	MinDrawArea;
	int		MinDrawSize;
	int64	MaxDrawArea;
	int		MaxDrawSize;

public:
	enum	Mode
	{
		 Mode_AddItem
		,Mode_AddRect
		,Mode_AddLine
		,Mode_Select
		,Mode_CutItem
		,Mode_ZoomIn
		,Mode_ZoomOut
	}CurrentMode;
	QFont	ButtonFont;
	int32	MachineCode;
	bool	ModeThoughNet;
	bool	RedrawMode;

	struct ButtonModeStruct
	{
		bool	Enabled_AddItem	:1;
		bool	Enabled_AddRect	:1;
		bool	Enabled_AddLine	:1;
		bool	Enabled_Select	:1;
		bool	Enabled_CutItem	:1;
		bool	Enabled_ZoomIn	:1;
		bool	Enabled_ZoomOut	:1;
	}EnableButtons;
	int	LineWidth;

	IntegrationSimpleImagePanel(LayersBase *Base ,QWidget *parent = 0);

	virtual	void	Prepare(void)	override;
	virtual	int		SetPropertyInDLL(PropertyClass Data[] ,WORD	maxDataDim);
	void	SetCanvasSize(int XLen,int YLen);
	virtual void	BuildForShow(void)	override;

	void	SetDirty(bool b)	{	MainCanvas.SetDirty(b);					}
	void	SetLineWidth(int w);
	int	GetCanvasWidth(void)		const	{	return MainCanvas.GetCanvasWidth();		}
	int	GetCanvasHeight(void)		const	{	return MainCanvas.GetCanvasHeight();	}
	double	GetZoomRate(void)		const	{	return MainCanvas.GetZoomRate();		}
	int		GetMovx(void)			const	{	return MainCanvas.GetMovx();			}
	int		GetMovy(void)			const	{	return MainCanvas.GetMovy();			}
	double	GetMaxZoomValue(void)	const	{	return MainCanvas.GetMaxZoomRate();	}
	double	GetMinZoomValue(void)	const	{	return MainCanvas.GetMinZoomRate();	}
	void	SetMode(mtFrameDraw::DrawingMode mode);
	void	SetMode(Mode d);
	void	SetMode(void);

	void	ZoomDraw(int movx, int movy, double zoomrate);
	bool	ZoomIn(int XonG, int YonG);
	bool	ZoomOut(int XonG, int YonG);
	bool	SetZoom(int XonG, int YonG , double ZoomRate);
	bool    ZoomRectG(int Gx1 ,int Gy1 ,int Gx2 ,int Gy2);
	bool    ZoomRectU(int Ux1 ,int Uy1 ,int Ux2 ,int Uy2);

	MainImagePanel	*GetCanvas(void)	const	{	return (MainImagePanel	*)&MainCanvas;	}
	void	SetFrameColor(const QColor &col)	{	GetCanvas()->SetFrameColor(col);	}
	QColor	GetFrameColor(void)	const	{	return(GetCanvas()->GetFrameColor());	}
	QPoint	GetCursorPos(void)	const	{	return 	GetCanvas()->GetCursorPos();	}
	bool	IsIncludeInCanvas(QPoint &P);
	void	SetMouseCursorPos(int XonG, int YonG);
	void	SetEnableShiftImage(bool b);
	bool	GetEnableShiftImage(void);
	virtual	void	Repaint(void) override;
	int		GetSlaveNo(void)	const;
	void	ResetDraw(void);
	void	SetCancelDraw(void);
	virtual	void	RefreshCache(void)	override{		MainCanvas.SetDirty(true);		}

private slots:
	virtual	void	ResizeAction();
	virtual	void	SlotClickedModeButton	();	
	virtual	void	SlotRightClickeddModeButton(QAbstractButton *obj);
	virtual	void	SlotClickedDeleteButton	();
	virtual	void	SlotClickedDrawWhole	();
	virtual	void	SlotClickedUndoButton	();
	virtual	void	SlotClickedCopyButton	(){}
	virtual	void	SlotDrawEnd(void);
protected slots:
	virtual	void	SlotCanvasMouseMove (int globalX ,int globalY);
	virtual	void	SlotCanvasMouseLDown(int globalX ,int globalY);
	virtual	void	SlotCanvasMouseRDown(int globalX ,int globalY);
	virtual	void	SlotMouseLDoubleClick(int ,int);
	virtual	void	SlotMouseRDoubleClick(int ,int);
	virtual	void	SlotJustMouseLPress  (int UniversalDx,int UniversalDy);
	virtual	void	SlotJustMouseRPress  (int UniversalDx,int UniversalDy);
	virtual	void	SlotJustMouseLRelease(int UniversalDx,int UniversalDy);
	virtual	void	SlotJustMouseRRelease(int UniversalDx,int UniversalDy);
	
private:
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	void    ToFlexArea( struct mtFrameDraw::_ShapeData &SData ,FlexArea &resultarea);
	void    ColPointToArea(NPListPack<ShapePoint> &cdata ,FlexArea &resultarea);
	void    GetPoints(XYClassCluster &XYArea);
	void	GetPointList(DotListContainer &Dots ,double d);
	VectorLineBase	*ToVectorLine( struct mtFrameDraw::_ShapeData &SData);

signals:
	void	SignalModeChanged();
	void	SignalJustMouseLPress  (int UniversalDx,int UniversalDy);
	void	SignalJustMouseRPress  (int UniversalDx,int UniversalDy);
	void	SignalJustMouseLRelease(int UniversalDx,int UniversalDy);
	void	SignalJustMouseRRelease(int UniversalDx,int UniversalDy);
	void	SignalDrawEndAfterOperation(FlexArea &ResultArea);
	void	SignalChangedItems();

protected:
	struct mtFrameDraw::_ShapeData *GetRawSDataPoint(void){	return &MainCanvas.GetCanvas()->SData;	}

	virtual	void	PaintFunc(QPainter &Pnt ,double ZoomRate , int movx , int movy){}

	virtual	void	DrawEndAfterOperationAddItem	(FlexArea &ResultArea,QByteArray &SomethingData){}
	virtual	void	DrawEndAfterOperationCutItem	(FlexArea &ResultArea,QByteArray &SomethingData){}
	virtual	void	DrawEndAfterOperationSelectArea	(FlexArea &ResultArea,QByteArray &SomethingData){}
	virtual	void	ReleaseSelection(void){}
	virtual	void	CancelSelectionMode(void){}
	virtual	bool	event(QEvent *event)	override;

	virtual	void	CreateCallInfoInAddItem(QByteArray &RetData){}
	virtual	void	CreateCallInfoInCut(QByteArray &RetData)	{}
	virtual	void	CreateCallInfoInSelect(QByteArray &RetData)	{}
	virtual	void	CreateCallInfoInDelete(QByteArray &RetData)	{}
};

class	IntegrationAlgoSimpleImagePanel : public IntegrationSimpleImagePanel
{
	Q_OBJECT
	friend	class	IntegrationReqAlgorithmPanelImage;
	friend	class	IntegrationAckAlgorithmPanelImage;

	IntegrationReqAlgorithmPanelImage	**RCmdImage;
	IntegrationAckAlgorithmPanelImage	**ACmdImage;
	BYTE								**TransferedImage;
	BYTE								**TRansferedBuffer;
	int									*CanvasWidthDim ;
	int									*CanvasHeightDim;
	int									*CanvasCountOfLayer;
	int									AllocatedCount;
	QImage								CurrentImage;

	int		CurrentPhase;
	//bool	OnSelection;
	bool	OnMoving;
	int		StartSelectionX;
	int		StartSelectionY;
	int		EndSelectionX;
	int		EndSelectionY;
public:
	QString	AlgoDLLRoot;
	QString	AlgoDLLName;
	QColor	DrawLineColor;
	QColor	MoveSelectionColor;

	IntegrationAlgoSimpleImagePanel(LayersBase *Base ,const QString &AlgoRoot , const QString &AlgoName ,QWidget *parent = 0);
	~IntegrationAlgoSimpleImagePanel(void);

	virtual	int		SetPropertyInDLL(PropertyClass Data[] ,WORD	maxDataDim)	override;
	virtual	void	Prepare(void)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void);
	virtual	void				GetActiveLayer(IntList &LayerList)	const;

	virtual	void				MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data){}
	virtual	void				AddItemInAlgorithm			(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &LocalArea ,QByteArray &Data,QByteArray &SomethingData){}
	virtual	void				CutItemInAlgorithm			(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &LocalArea ,QByteArray &SomethingData);
	virtual	void				DelSelectedItemsInAlgorithm	(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList,QByteArray &SomethingData);

	virtual	void	DrawImage(QImage &Image
							,double ZoomRate ,int MovX ,int MovY 
							,int Phase ,IntList &LayerList
							,QByteArray	&DrawAtterData
							,QString &_AlgoDLLRoot ,QString &_AlgoDLLName
							,bool tOnSelection
							,bool tOnMoving
							,int tSelectionDx,int tSelectionDy);
	void	MakeImageBuff(BYTE *ImageBuff 
							,int CanvasWidth,int CanvasHeight,int CountOfLayer
							,double ZoomRate ,int MovX ,int MovY 
							,int Phase ,IntList &LayerList
							,QByteArray	&DrawAtterData
							,QString &_AlgoDLLRoot ,QString &_AlgoDLLName
							,bool tOnSelection
							,bool tOnMoving
							,int tSelectionDx,int tSelectionDy);

	virtual	void	Repaint(void)	override	{	repaint();	}
	AlgorithmBase	*GetAlgorithmBase(void)	const;
	virtual	void	SelectItem(int Phase,IntList &LayerList, FlexArea &Area,SelectedItemsInfoContainer &RetSelectedContainer,QByteArray &SomethingData);
	virtual	void	SelectItem(SelectedItemsInfoContainer &SelectedContainer);
	virtual	void	ExecuteMoveItems(const QString &AlgoDLLRoot ,const QString &AlgoDLLName ,int GlobalDx ,int GlobalDy);

	void	CopyFromSlave(int SlaveNo);
	void	CopyToSlave(IntList &DestSlaveList,bool ClearBeforeCopy=false);

	virtual	void	MakeCopyToSlaveInfo(QByteArray &RetInfo){}
	virtual	bool	LoadCopyToSlaveInfo(QByteArray &InfoData,AlgorithmInPageRoot *Ap,QByteArray &RetData){	return false;	}
	virtual	bool	SaveCopyToSlaveInfo(QByteArray &InfoData,AlgorithmInPageRoot *Ap,TransformBase	*Param ,bool ClearBeforeCopy);

protected:
	virtual	void	PaintFunc(QPainter &Pnt ,double ZoomRate , int movx , int movy)	override;

	virtual	void	DrawEndAfterOperationAddItem(FlexArea &ResultArea	,QByteArray &SomethingData)	override;
	virtual	void	DrawEndAfterOperationCutItem(FlexArea &ResultArea	,QByteArray &SomethingData)	override;
	virtual	void	DrawEndAfterOperationSelectArea(FlexArea &ResultArea,QByteArray &SomethingData)	override;
	virtual	void	ReleaseSelection(void)									override;
	virtual	void	CancelSelectionMode(void)								override{	/*OnSelection=false;*/	}
protected slots:
	virtual	void	SlotClickedDeleteButton	()						override;
	virtual	void	SlotCanvasMouseLDown(int globalX ,int globalY)	override;
	virtual	void	SlotCanvasMouseRDown(int globalX ,int globalY)	override;
	virtual	void	SlotCanvasMouseMove (int globalX ,int globalY)	override;
	virtual	void	SlotTempSelectItem(const SelectedItemsInfoContainer &src);
	virtual	void	SlotTempSelectCancel();
	virtual	void	SlotClickedCopyButton()	override;
private:
	virtual	bool	HasSelectedItem(void);
};

#endif

