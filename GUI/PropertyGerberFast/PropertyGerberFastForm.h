#ifndef PROPERTYGERBERFASTFORM_H
#define PROPERTYGERBERFASTFORM_H

#include <QWidget>
#include <QDialog>
#include <QScrollArea>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"
#include "XServiceForLayers.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XGUIGerberPacket.h"

namespace Ui {
class PropertyGerberFastForm;
}

class	GerberLayerListOnScreen			;
class	GerberCompositeLayerListOnScreen;
class	AutoMatchShiftableLayerOnScreen;
class	MakeAlgorithmUpperDialog;
class	MakeAlgorithmSimpleDialog;

class PropertyGerberFastForm : public GUIFormBase
{
    Q_OBJECT

	friend class MakeAlgorithmUpperDialog;
	friend class MakeAlgorithmSimpleDialog;

	QScrollArea	FrameArea;
	QWidget		FrameAreaInside;

	QScrollArea	CompositeArea;
	QWidget		CompositeAreaInside;

	mtFrameDraw::DrawingMode	PanelModeAlignment;

	QScrollArea	AutoMatchFrameArea;
	QWidget		AutoMatchFrameAreaInside;

	QScrollArea	AutoMatchCompositeArea;
	QWidget		AutoMatchCompositeAreaInside;

	AutoMatchShiftableLayerOnScreen		*AutoMatchShiftableLayer[MaxGerberLayer];
	AutoMatchShiftableLayerOnScreen		*AutoMatchShiftableComposite[MaxGerberLayer];
    
	AlgoGenerationalContainer		MakeAlgoAllList;

	int		tTransDot;
	double	tRoughMatchAreaWidthRate;
	double	tRoughMatchAreaHeightRate;
	int		tSearchAreaRoughMatch;
	int		tSearchAreaParallelMatch;
	int		tSearchAreaRotateMatch;
	int		tSearchAreaZoomMatch;
	int		tSearchAreaMatchDetail;
	int		tDataIsolation;
	int		tNearByPattern;
	double	tMatchingRateToNeighbor;
	bool	LoadedGerber;	

public:
	bool	EnableMatching;
	bool	EnableAlgorithm;

	GerberLayerListOnScreen				*child[MaxGerberLayer];
	GerberCompositeLayerListOnScreen	*CompChild[MaxGerberLayer];

    explicit PropertyGerberFastForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyGerberFastForm();

	virtual	void	Prepare(void)		override;
	virtual	void	ReadyParam(void)	override;
	GerberFastBase	*GetGerberFastBase(void);
	QColor	GetLayerColor(int number);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)				override;
	virtual void	SetupLibFolder(int LibFolderID,int originalLibFolder)	override;
	virtual void	ShowInEdit	(void)	override;
    virtual void	BuildForShow(void)	override;

	void	CommandLoadGerber(void);
	void	CommandGerberClear(void);
	void	CommandCreateAutoMatchArea(int DotForRoughSearch,int DotForMoveSearch,int DotForRotationSearch,int DotForZoomSearch,int DotForDetailSearch,bool BrighterInPattern
										,QString &LayerFileName);
	void	CommandStartAutoMatch(void);
	void	CommandStartAutoMatch(int DotForRoughSearch,int DotForMoveSearch,int DotForRotationSearch,int DotForZoomSearch,int DotForDetailSearch,bool BrighterInPattern);
	void	CommandMoveOtherAlgorithm(void);
	void	CommandBuildAlgorithm(void);
	void	CommandMoveItems(double Dx,double Dy);
	void	CommandRotateItems(double Angle);
	void	CommandRotateItems(double Angle ,double Cx ,double Cy);
	void	CommandShearXItems(double Angle);
	void	CommandShearYItems(double Angle);
	void	CommandZoomItems(double ZoomX,double ZoomY);
	void	CommandZoomItems(double ZoomX,double ZoomY ,double Cx ,double Cy);
	void	CommandRoughMatch(QString &LayerFileName);
	void	CommandSetGerberFile(QString &GerberFileName,int LineNo);
	void	CommandMoveByMouse(void);
	void	CommandRotateByMouse(void);
	void	CommandZoomByMouse(void);
	void	CommandMirrorX(void);
	void	CommandMirrorY(void);
	void	CommandMakeImageToMaster(IntList &LayerLineNo,IntList &CompoLineNo);
	void	CommandMakeBitImageToMaster(IntList &LayerLineNo,IntList &CompoLineNo);
	void	CommandSetLayerType(int GerberLineNumber,int LayerType);
	void	CommandInitialAlgorithm(void);
	void	CommandClearLibraryInMakeAlgorithmLine(int GerberLineNumber,int GenerationType);
	void	CommandAppendLibraryInMakeAlgorithmLine(int GerberLineNumber,int GenerationType ,const QString &DLLRoot,const QString &DLLName,int LibID);
	void	CommandCreateCluster(int GLayerNumber);

	void	SendShowingState(void);
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	void	SetAutoMatchInfo(void);

private slots:
    void on_pushButtonAutoFile_clicked();
    void on_pushButtonLoadGerber_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonMove_clicked();
    void on_pushButtonRotate_clicked();
    void on_pushButtonZoom_clicked();
    void on_pushButtonShear_clicked();
    void on_toolButtonMove_clicked();
    void on_toolButtonRotate_clicked();
    void on_toolButtonZoom_clicked();
    void on_pushButtonMirrorX_clicked();
    void on_pushButtonMirrorY_clicked();
    void on_pushButtonEditLayerType_clicked();
    void on_pushButtonEditCompositeDef_clicked();
    void on_pushButtonClearSelectLayer_clicked();
    void on_pushButtonClearSelectComposite_clicked();
	void	DataChanged(int layerNo);
	void	CompDataChanged(int layerNo);
	void	SlotShowRedrawImage();
    void on_toolButtonShearX_clicked();
    void on_toolButtonShearY_clicked();
    void on_pushButtonToImage_clicked();
    void on_pushButtonToAlgo_clicked();
    void on_pushButtonMaxEnlarge_clicked();
    void on_pushButtonMaxShrink_clicked();
    void on_pushButtonShiftable_clicked();
    void on_pushButtonUnstableZone_clicked();
    void on_pushButtonClearImage_clicked();
    void on_toolButtonMatchPoints_clicked();
    void on_pushButtonToAutoMatch_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_pushButtonClearMatchPoints_clicked();
    void on_pushButtonStartMoveToMatch_clicked();
    void on_tabWidgetProperty_currentChanged(int index);
    void on_tabWidgetOperation_currentChanged(int index);
    void on_tableWidgetAlignments_clicked(const QModelIndex &index);
    void on_tableWidgetCrossedLayer_doubleClicked(const QModelIndex &index);
    void on_pushButtonMakeAutoMatchArea_clicked();
    void on_pushButtonClearAutoMatchArea_clicked();
    void on_toolButtonShowAutoMatchArea_clicked();
    void on_toolButtonShowAutoMatchImage_clicked();
    void on_pushButtonInitialAlgo_clicked();

	void	SlotClickedSelected(int n);
	void	CompClickedSelected(int n);
	void	GerberApertureSetting(int n);

	void	SlotCenterizeFit();
	void	SlotCenterizeOnly();

    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonStableZone_clicked();
    void on_pushButtonToNormalImage_clicked();
    void on_pushButtonMoveOtherAlgorithm_clicked();

    void on_tableWidgetAMManualPoints_doubleClicked(const QModelIndex &index);
    void on_pushButtonAMClearPoints_clicked();
    void on_pushButtonAMAllocate_clicked();
    void on_pushButtonSaveAlgoGen_clicked();
    void on_pushButtonLoadAlgoGen_clicked();
    void on_pushButtonMergeLoadAlgoGen_clicked();

	void	SlotCrossedLayerSimple();
	void	SlotCrossedLayerComlicated();
	void	SlotClearMakeAlgorithmLine();
	void	SlotMakeAlgorithmLine();

    void on_pushButtonCenterize_clicked();
    void on_pushButtonMatchRoughly_clicked();
    void on_pushButtonSetFlushMatrix_clicked();
    void on_toolButtonDraw_clicked();
    void on_pushButtonClearFIleList_clicked();

    void on_pushButtonSetForAutoMatch_clicked();
    void on_toolButtonAreaForParallel_clicked();
    void on_toolButtonAreaForRotate_clicked();
    void on_toolButtonAreaForZoom_clicked();
    void on_comboBoxUseLayerToAutoMatch_currentIndexChanged(int index);
    void on_pushButtonGenerateOutline_clicked();
    void on_pushButtonEchingFactor_clicked();
    void on_pushButtonClearOutline_clicked();
    void on_pushButtonDraw_clicked();

	void	SlotSelectLine(int LayerNo);
	void	SlotRemoveLine(int LayerNo);
	void	SlotSwapNext(int LayerNo);
	void	SlotDuplicateLine(int LayerNo);
	void	SlotAddLayer(int LayerNo);

    void on_toolButtonCreateLine_clicked();
    void on_toolButtonCreateArc_clicked();
    void on_toolButtonCreatePolygon_clicked();
    void on_pushButtonClearDrawLayer_clicked();

    void on_pushButtonClearCompositeDrawLayer_clicked();
    void on_pushButtonGenerateCenter_clicked();
    void on_pushButtonGenerateAlgorithmFromOutline_clicked();
    void on_pushButtonToBitImage_clicked();
    void on_pushButtonMakeCluster_clicked();
    void on_pushButtonSetLibFolder_clicked();

	void	ResizeAction();

private:
    Ui::PropertyGerberFastForm *ui;

	void	SetCompositeDef2ComboBox(void);
	void	RepaintImage(void);
	void	GetCenterGerber(double &MinX ,double &MinY ,double &MaxX ,double &MaxY);
	void	TransferGerberInfo(void);
	void	MakeImageToMaster(void);
	void	MakeBitImage(void);
	
	void	SendShowingStateLayer		(BoolList &ButtonsToShowLayer ,BoolList &ButtonsToOperateLayer);
	void	SendShowingStateComposite	(BoolList &ButtonsToShowLayer ,IntList &OperateCompositeIDList);

	OperationMode	GetCurrentOperationMode(void);
	GUIFormBase	*GetImagePanel(void);
	void	GetOperationalButton(BoolList &ButtonsToOperateLayer , IntList &OperateCompositeIDList);

	void	UpdateAlignment(void);
	void	GoNextStepAlignment(void);
	void	GoNextStepForAddAlignment(void);
	int		GetInputTypeAlignment(void);
	int		GetInputNumberAlignment(void);

	int		GetAMInputTypeAlignment(void);
	int		GetAMInputNumberAlignment(void);
	void	UpdateAMAlignment(void);
	void	GoNextStepAMAlignment(void);
	void	UpdateAutoList(void);

	bool	SaveAlgoGen(QIODevice *f);
	bool	LoadAlgoGen(QIODevice *f);
	bool	MergeLoadAlgoGen(QIODevice *f);
	void	ShowMakeAlgoAllList(void);
	void	ShowAutoMatchInfo(void);

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
	virtual	void	showEvent ( QShowEvent * )	override;

public:
	AlgoGenerationalContainer	AlgoGenAllCombination;
};

//-------------------------------------------------------------------

class	mtToolButtonColoredWithRightClick : public mtToolButtonColored
{
	Q_OBJECT
public:
	mtToolButtonColoredWithRightClick(QWidget *parent=0):mtToolButtonColored(false,parent){}

	virtual	void mousePressEvent(QMouseEvent * event )	override;
signals:
	void	ClickRight();
};


class	GerberLayerListOnScreen : public GerberInLayerBase ,public NPList<GerberLayerListOnScreen>,public ServiceForLayers
{
	Q_OBJECT
	
	int	FileLayerNo;

public:
	class	ScreenDataInPhase
	{
	public:
		int		LibID;
		bool	Selected;
		bool	Operation;
		QString	FileName;
		QString	Remark;

		ScreenDataInPhase(void);

		ScreenDataInPhase	&operator=(ScreenDataInPhase &src);

		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
private:
	ScreenDataInPhase	*DataInPhase;
	int					AllocatedPhaseCount;
	int					LastCurrentPhase;
	int					PosY;

public:
	PropertyGerberFastForm	*FormParent;

	mtToolButtonColoredWithRightClick		ButtonSelected;
	QCheckBox				CheckBoxOperation;
	QLineEdit				EditLibID;
	QLineEdit				EditLibName;
	QPushButton				ButtonChooseLib;
	QLineEdit				EditFileName;
	QPushButton				ButtonChooseFile;
	QLineEdit				EditRemark;
	QPushButton				ButtonGerber;
	bool					SignalEnabled;

	GerberLayerListOnScreen(int layerNo,PropertyGerberFastForm *formbase,QWidget *parent=NULL);
	virtual	~GerberLayerListOnScreen(void);

	void	SetComboBLayerType(void);
	int		ShowPosition(int Y);
	void	Resize(void);

	//void	SetData(GerberBase::GerberLayerList &Data);
	//void	GetData(GerberBase::GerberLayerList &Data);

	bool	SaveContent(QIODevice *f);
	bool	LoadContent(QIODevice *f);

	GerberLayerListOnScreen	&operator=(GerberLayerListOnScreen &src);
	void	Swap(GerberLayerListOnScreen &src);

	void	StoreFromWindow(void);
	void	StoreToWindow(void);
	void	DeliverAllPhases(int SrcPhase);

	int			GetLibID(void)	;
	void		SetLibID(int id);
	void		ClearLibID(void);
	QString		GetLibName(void);
	QColor		GetColor(void);
	void		SetColor(QColor &Col);
	void		SetEmpty(void);

	void		SetFileLayerNo(int n);
	int			GetFileLayerNo(void);

	bool		IsValidLine(void);
	QString		GetTypeName(void);
	QString		GetFileName(void);
	bool		IsOperational(void);
	void		SetOperational(bool b);
	void		SetSelection(bool b);

	ScreenDataInPhase	*GetDataInPhase(int phase)	{	return &DataInPhase[phase];		}

	virtual	void	DragTransferDirently(GUIDirectMessage *packet)	override;

private:
	virtual	void	mousePressEvent(QMouseEvent *event)			override;
	virtual	void	mouseReleaseEvent ( QMouseEvent * event )	override;
	virtual	void	resizeEvent(QResizeEvent *event)			override;
signals:
	void	DataChanged(int layerNo);
	void	ShowRedrawImage(void);
	void	ChangedColor(int LayerNo ,QColor &Col);
	void	ClickedSelected(int LayerNo);
	void	ClickedApertured(int LayerNo);
	void	SignalSelectLine(int LayerNo);
	void	SignalRemoveLine(int LayerNo);
	void	SignalSwapNext(int LayerNo);
	void	SignalDuplicateLine(int LayerNo);
	void	SignalAddLayer(int LayerNo);
private slots:
	void	SlotSelectedButtonClicked();
	void	SlotSelectedButtonRightClicked();
	void	SlotCheckBoxOperationClicked();
	void	SlotChooseFileClicked();
	void	SlotButtonGerberClicked();
	void	SlotButtonChooseLibClicked();

	void	SlotSelectLine();
	void	SlotRemoveLine();
	void	SlotSwapNext();
	void	SlotDuplicate();
	void	SlotAddLayer();
public slots:
	void	EditFilenameChanged(const QString &);
};

class	GerberCompositeLayerListOnScreen : public GerberInLayerBase ,public NPList<GerberCompositeLayerListOnScreen>,public ServiceForLayers
{
	Q_OBJECT
	
public:
	class	ScreenDataInPhase
	{
	public:
		int		CompositeID;
		bool	Selected;
		bool	Operation;
		QString	Remark;

		ScreenDataInPhase(void);

		ScreenDataInPhase	&operator=(ScreenDataInPhase &src);

		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	ScreenDataInPhase	*DataInPhase;
	int					AllocatedPhaseCount;
	int					LastCurrentPhase;

	PropertyGerberFastForm	*FormParent;
	mtToolButtonColoredWithRightClick		ButtonSelected;
	QCheckBox				ButtonOperation;
	QComboBox				ComboBComposite;
	QLineEdit				EditRemark;
	int						LayerNo;
	bool					SignalEnabled;
	int						PosY;

	GerberCompositeLayerListOnScreen(int layerNo,PropertyGerberFastForm *formbase ,QWidget *parent=NULL);
	~GerberCompositeLayerListOnScreen(void);
	int		ShowPosition(int Y);
	void	Resize(void);

	//void	GetData(GerberCompositeLayer &Data);
	//void	SetData(GerberCompositeLayer &Data);
	QString		GetLibName(void);
	QColor		GetColor(void);
	void		SetColor(QColor &Col);

	void	StoreFromWindow(void);
	void	StoreToWindow(void);

	bool	SaveContent(QIODevice *f);
	bool	LoadContent(QIODevice *f);

	bool		IsValidLine(void);
	QString		GetCompositeName(void);
	bool		IsOperational(void);
	void		SetOperational(bool b);
	ScreenDataInPhase	*GetDataInPhase(int phase)	{	return &DataInPhase[phase];		}

	virtual	void	DragTransferDirently(GUIDirectMessage *packet)	override {}

private:
	virtual	void	resizeEvent(QResizeEvent *event)			override;
signals:
	void	DataChanged(int layerNo);
	void	ChangedColor(int LayerNo ,QColor &Col);
	void	ClickedSelected(int LayerNo);
private slots:
	void	SlotSelectedButtonClicked();
	void	SlotSelectedButtonRightClicked();
	void	SlotSelectedOperationalButtonClicked();
	void	CompositeIndexChanged (int);
public slots:
	void	EditFilenameChanged(const QString &);
};

class	AutoMatchShiftableLayerOnScreen : public QWidget ,public ServiceForLayers
{
public:
	PropertyGerberFastForm	*FormParent;
	QCheckBox			ButtonOperation;
	QLineEdit			BLayerType;
	QLineEdit			EditName;
	int					LayerNo;

	AutoMatchShiftableLayerOnScreen(int layerNo,PropertyGerberFastForm *formbase ,QWidget *parent=NULL);

	int		ShowPosition(int Y);
	bool	SaveContent(QIODevice *f);
	bool	LoadContent(QIODevice *f);
};



#endif // PROPERTYGERBERFASTFORM_H
